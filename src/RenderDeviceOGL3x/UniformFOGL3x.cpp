#pragma once
#include "UniformOGL3x.h"
#include "GL\glew.h"
#include <string>
#include "ACTK.h"

namespace ACTK
{
	UniformF::UniformF(int location, UniformDatatype datatype, int count, ICleanableObserver* observer) : UniformOGL3x(location, datatype, count, observer)
	{
		switch (Datatype)
		{
		case(UniformDatatype::Float):
			m_val = new float[1*count];
			m_size = 1 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatVector2):
			m_val = new float[2*count];
			m_size = 2 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatVector3):
			m_val = new float[3*count];
			m_size = 3 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatVector4):
			m_val = new float[4*count];
			m_size = 4 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatMatrix22):
			m_val = new float[4*count];
			m_size = 4 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatMatrix23):
			m_val = new float[6*count];
			m_size = 6 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatMatrix24):
			m_val = new float[8*count];
			m_size = 8 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatMatrix32):
			m_val = new float[6*count];
			m_size = 6 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatMatrix33):
			m_val = new float[9*count];
			m_size = 9 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatMatrix34):
			m_val = new float[12*count];
			m_size = 12 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatMatrix42):
			m_val = new float[8*count];
			m_size = 8 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatMatrix43):
			m_val = new float[12*count];
			m_size = 12 * count * sizeof(float);
			break;
		case(UniformDatatype::FloatMatrix44):
			m_val = new float[16*count];
			m_size = 16 * count * sizeof(float);
			break;
		}
	}

	UniformF::~UniformF()
	{
		delete[] m_val;
	}

	void UniformF::clean()
	{
		switch(Datatype)
		{
		case(UniformDatatype::Int):
			glUniform1fv(Location, m_count, m_val);
			break;
		case(UniformDatatype::IntVector2):
			glUniform2fv(Location, m_count, m_val);
			break;
		case(UniformDatatype::IntVector3):
			glUniform3fv(Location, m_count, m_val);
			break;
		case(UniformDatatype::IntVector4):
			glUniform4fv(Location, m_count, m_val);
			break;
		case(UniformDatatype::FloatMatrix22):
			glUniformMatrix2fv(Location, m_count, GL_FALSE, m_val);
			break;
		case(UniformDatatype::FloatMatrix23):
			glUniformMatrix2x3fv(Location, m_count, GL_FALSE, m_val);
			break;
		case(UniformDatatype::FloatMatrix24):
			glUniformMatrix2x4fv(Location, m_count, GL_FALSE, m_val);
			break;
		case(UniformDatatype::FloatMatrix32):
			glUniformMatrix3x2fv(Location, m_count, GL_FALSE, m_val);
			break;
		case(UniformDatatype::FloatMatrix33):
			glUniformMatrix3fv(Location, m_count, GL_FALSE, m_val);
			break;
		case(UniformDatatype::FloatMatrix34):
			glUniformMatrix3x4fv(Location, m_count, GL_FALSE, m_val);
			break;
		case(UniformDatatype::FloatMatrix42):
			glUniformMatrix4x2fv(Location, m_count, GL_FALSE, m_val);
			break;
		case(UniformDatatype::FloatMatrix43):
			glUniformMatrix4x3fv(Location, m_count, GL_FALSE, m_val);
			break;
		case(UniformDatatype::FloatMatrix44):
			glUniformMatrix4fv(Location, m_count, GL_FALSE, m_val);
			break;
		}
	}

	void UniformF::setValue(int* val, int size)
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
			m_val[i] = static_cast<float>(val[i]);
		}
	}

	void UniformF::setValue(float* val, int size)
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
			m_val[i] = static_cast<float>(val[i]);
		}
	}

	void UniformF::setValue(unsigned int* val, int size)
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
			m_val[i] = static_cast<float>(val[i]);
		}
	}
}