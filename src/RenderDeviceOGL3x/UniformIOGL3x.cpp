#pragma once
#include "UniformOGL3x.h"
#include "GL\glew.h"
#include <string>
#include "ACTK.h"

namespace ACTK
{
	UniformI::UniformI(int location, UniformDatatype datatype, int count, ICleanableObserver* observer) : UniformOGL3x(location, datatype, count, observer)
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

	UniformI::~UniformI()
	{
		delete[] m_val;
	}

	void UniformI::clean()
	{
		switch(Datatype)
		{
		case(UniformDatatype::Int):
			glUniform1iv(Location, m_count, m_val);
			break;
		case(UniformDatatype::IntVector2):
			glUniform2iv(Location, m_count, m_val);
			break;
		case(UniformDatatype::IntVector3):
			glUniform3iv(Location, m_count, m_val);
			break;
		case(UniformDatatype::IntVector4):
			glUniform4iv(Location, m_count, m_val);
			break;
		}
	}

	void UniformI::setValue(float* val, int size)
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
		memset(m_val,0,m_size*sizeof(int));
		for (int i = 0; i < size; i++)
		{
			m_val[i] = static_cast<int>(val[i]);
		}
	}

	void UniformI::setValue(unsigned int* val, int size)
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
		memset(m_val,0,m_size*sizeof(int));
		for (int i = 0; i < size; i++)
		{
			m_val[i] = static_cast<int>(val[i]);
		}
	}

	void UniformI::setValue(int* val, int size)
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
		memset(m_val,0,m_size*sizeof(int));
		for (int i = 0; i < size; i++)
		{
			m_val[i] = static_cast<int>(val[i]);
		}
	}
}