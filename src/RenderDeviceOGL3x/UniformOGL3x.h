#pragma once
#include "ICleanableObserver.h"
#include "GL\glew.h"

namespace ACTK
{
	enum class UniformDatatype : char
	{
		Int,
        Float,
        FloatVector2,
        FloatVector3,
        FloatVector4,
        IntVector2,
        IntVector3,
        IntVector4,
        Bool,
        BoolVector2,
        BoolVector3,
        BoolVector4,
        FloatMatrix22,
        FloatMatrix33,
        FloatMatrix44,
		FloatMatrix23,
        FloatMatrix24,
        FloatMatrix32,
        FloatMatrix34,
        FloatMatrix42,
        FloatMatrix43,
		
        Sampler1D,
        Sampler2D,
        Sampler2DRectangle,
        Sampler2DRectangleShadow,
        Sampler3D,
        SamplerCube,
        Sampler1DShadow,
        Sampler2DShadow,
        Sampler1DArray,
        Sampler2DArray,
        Sampler1DArrayShadow,
        Sampler2DArrayShadow,
        SamplerCubeShadow,
        IntSampler1D,
        IntSampler2D,
        IntSampler2DRectangle,
        IntSampler3D,
        IntSamplerCube,
        IntSampler1DArray,
        IntSampler2DArray,
        UnsignedIntSampler1D,
        UnsignedIntSampler2D,
        UnsignedIntSampler2DRectangle,
        UnsignedIntSampler3D,
        UnsignedIntSamplerCube,
        UnsignedIntSampler1DArray,
        UnsignedIntSampler2DArray
	};

	// ToDo: Uniform ableitungen definieren. Die ableitungen enthalten die Definition der Clear-Funktion und
	// die SetValue implementierung und speichern den Wert zwischen.
	// Meins! (Grigori)

	class UniformOGL3x : public ICleanable
	{
	public:
		// Update method
		UniformOGL3x(int location, UniformDatatype datatype, int count, ICleanableObserver* observer) : 
			m_dirty(false),
			Location(location),
			Datatype(datatype),
			m_count(count),
			m_observer(observer)
		{
		}

		~UniformOGL3x();

		// implemented by derivative
		virtual void clean() = 0;

		const int				Location;
		const UniformDatatype	Datatype;

	protected:
		const int m_count;

		bool m_dirty;
		ICleanableObserver*	const m_observer;
	};

	class UniformI : public UniformOGL3x
	{
	public:
		UniformI(int location, UniformDatatype datatype, int count, ICleanableObserver* observer) : UniformOGL3x(location, datatype, count, observer)
		{
			switch (Datatype)
			{
			case(UniformDatatype::Int):
				m_val = new int[1*count];
				m_size = 1 * count * sizeof(int);
				break;
			case(UniformDatatype::IntVector2):
				m_val = new int[2*count];
				m_size = 2 * count * sizeof(int);
				break;
			case(UniformDatatype::IntVector3):
				m_val = new int[3*count];
				m_size = 3 * count * sizeof(int);
				break;
			case(UniformDatatype::IntVector4):
				m_size = 4 * count * sizeof(int);
				m_val = new int[4*count];
				break;
			}
			memset(m_val, 0, m_size);
		}

		~UniformI()
		{
			delete[] m_val;
		}

		void clean()
		{
			glUniform1iv(Location, m_count, m_val);
		}

		void setValue(int val)
		{
			setValue(&val, sizeof(int));
		}

	private:
		void setValue(int* val, int size)
		{
			if(m_dirty)
			{
				m_dirty = true;
				m_observer->notifyDirty(this);
			}
			memcpy(m_val, val, size);
		}

		int m_size;
		int* m_val;
	};

	class UniformF : public UniformOGL3x
	{
	public:
		UniformF(int location, UniformDatatype datatype, int count, ICleanableObserver* observer) : UniformOGL3x(location, datatype, count, observer)
		{
			switch (Datatype)
			{
			case(UniformDatatype::Float):
				m_val = new float[1*count];
				break;
			case(UniformDatatype::FloatVector2):
				m_val = new float[2*count];
				break;
			case(UniformDatatype::FloatVector3):
				m_val = new float[3*count];
				break;
			case(UniformDatatype::FloatVector4):
				m_val = new float[4*count];
				break;
			case(UniformDatatype::FloatMatrix22):
				m_val = new float[4*count];
				break;
			case(UniformDatatype::FloatMatrix23):
				m_val = new float[6*count];
				break;
			case(UniformDatatype::FloatMatrix24):
				m_val = new float[8*count];
				break;
			case(UniformDatatype::FloatMatrix32):
				m_val = new float[6*count];
				break;
			case(UniformDatatype::FloatMatrix33):
				m_val = new float[9*count];
				break;
			case(UniformDatatype::FloatMatrix34):
				m_val = new float[12*count];
				break;
			case(UniformDatatype::FloatMatrix42):
				m_val = new float[8*count];
				break;
			case(UniformDatatype::FloatMatrix43):
				m_val = new float[12*count];
				break;
			case(UniformDatatype::FloatMatrix44):
				m_val = new float[16*count];
				break;
			}
		}

		~UniformF()
		{
			delete[] m_val;
		}

		void clean()
		{
			glUniform1fv(Location, m_count, m_val);
		}

		void setValueI(int val)
		{
			*m_val = val;
		}

	private:
		float* m_val;
	};
}