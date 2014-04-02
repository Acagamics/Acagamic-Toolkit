#pragma once
#include "ICleanableObserver.h"
#include "GL\glew.h"

namespace ACTK
{
	enum class UniformDatatype : char
	{
		Int,
		UnsignedInt,
        Float,
        FloatVector2,
        FloatVector3,
        FloatVector4,
        IntVector2,
        IntVector3,
        IntVector4,
		UnsignedIntVector2,
        UnsignedIntVector3,
        UnsignedIntVector4,
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

	// ToDo: Uniform Ableitung für unsigned definieren.
	// Meins! (Grigori)

	class IUniformOGL3x : public ICleanable
	{
	public:
		// Update method
		IUniformOGL3x(int location, UniformDatatype datatype, int count, ICleanableObserver* observer) : 
			m_dirty(false),
			Location(location),
			Datatype(datatype),
			m_count(count),
			m_observer(observer)
		{
		}

		// implemented by derivative
		virtual void clean() = 0;

		const int				Location;
		const UniformDatatype	Datatype;

	protected:
		const int m_count;

		bool m_dirty;
		ICleanableObserver*	const m_observer;
	};

	template<class T> 
	class UniformOGL3x : public IUniformOGL3x
	{
	public:
		UniformOGL3x(int location, UniformDatatype datatype, int count, ICleanableObserver* observer) :
			IUniformOGL3x(location, datatype, count, observer)
		{
		}
		~UniformOGL3x()
		{
			delete[] m_val;
		}

		// implemented by derivative
		virtual void clean() = 0;
		
		template <class A>
		void setValue(A* val, int size)
		{
			if(m_size < size)
			{
				size = m_size;
				LOG_ERROR("Uniformsize überschritten!");
			}

			if(m_dirty)
			{
				m_dirty = true;
				m_observer->notifyDirty(this);
			}
			memset(m_val,0,m_size*sizeof(float));
			for (int i = 0; i < size; i++)
			{
				m_val[i] = static_cast<T>(val[i]);
			}
		}

	protected:
		int  m_size;
		T* m_val;
	};

	class UniformI : public UniformOGL3x<int>
	{
	public:
		UniformI(int location, UniformDatatype datatype, int count, ICleanableObserver* observer);
		~UniformI();

		void clean();
	};

	class UniformF : public UniformOGL3x<float>
	{
	public:
		UniformF(int location, UniformDatatype datatype, int count, ICleanableObserver* observer);
		~UniformF();

		void clean();
	};

	class UniformUI : public UniformOGL3x<unsigned int>
	{
	public:
		UniformUI(int location, UniformDatatype datatype, int count, ICleanableObserver* observer);
		~UniformUI();

		void clean();
	};
}