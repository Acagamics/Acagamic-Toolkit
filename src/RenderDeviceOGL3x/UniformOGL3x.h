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

		// Weiß nicht, ob ich das darf.
		//~UniformOGL3x(){}//~UniformOGL3x();

		//TODO: Set Value Funktion definieren
		template <typename T> void setValue(T* val, int size);

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
		UniformI(int location, UniformDatatype datatype, int count, ICleanableObserver* observer);
		~UniformI();

		void clean();
		void setValue(int* val, int size);
		void setValue(unsigned int* val, int size);
		void setValue(float* val, int size);

	private:
		int m_size;
		int* m_val;
	};

	class UniformF : public UniformOGL3x
	{
	public:
		UniformF(int location, UniformDatatype datatype, int count, ICleanableObserver* observer);
		~UniformF();

		void clean();
		void setValue(int* val, int size);
		void setValue(unsigned int* val, int size);
		void setValue(float* val, int size);

	private:
		int m_size;
		float* m_val;
	};

	class UniformUI : public UniformOGL3x
	{
	public:
		UniformUI(int location, UniformDatatype datatype, int count, ICleanableObserver* observer);
		~UniformUI();

		void clean();
		void setValue(int* val, int size);
		void setValue(unsigned int* val, int size);
		void setValue(float* val, int size);

	private:
		int  m_size;
		unsigned int* m_val;
	};
}