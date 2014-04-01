#pragma once
#include "UniformOGL3x.h"
#include "GL\glew.h"
#include <string>
#include "ACTK.h"

namespace ACTK
{
	UniformUI::UniformUI(int location, UniformDatatype datatype, int count, ICleanableObserver* observer) : UniformOGL3x(location, datatype, count, observer)
	{
		switch (Datatype)
		{
		case(UniformDatatype::Int):
			m_val = new unsigned int[1*count];
			m_size = 1 * count * sizeof(int);
			break;
		case(UniformDatatype::IntVector2):
			m_val = new unsigned int[2*count];
			m_size = 2 * count * sizeof(int);
			break;
		case(UniformDatatype::IntVector3):
			m_val = new unsigned int[3*count];
			m_size = 3 * count * sizeof(int);
			break;
		case(UniformDatatype::IntVector4):
			m_size = 4 * count * sizeof(int);
			m_val = new unsigned int[4*count];
			break;
		}
		memset(m_val, 0, m_size);
	}

	UniformUI::~UniformUI()
	{
		delete[] m_val;
	}

	void UniformUI::clean()
	{
		switch(Datatype)
		{
		case(UniformDatatype::UnsignedInt):		   glUniform1uiv(Location, m_count, m_val);
			break;
		case(UniformDatatype::UnsignedIntVector2): glUniform2uiv(Location, m_count, m_val);
			break;
		case(UniformDatatype::UnsignedIntVector3): glUniform3uiv(Location, m_count, m_val);
			break;
		case(UniformDatatype::UnsignedIntVector4): glUniform4uiv(Location, m_count, m_val);
			break;
		}
	}

	void UniformUI::setValue(float* val, int size)
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
		memset(m_val,0,m_size*sizeof(unsigned int));
		for (int i = 0; i < size; i++)
		{
			m_val[i] = static_cast<unsigned int>(val[i]);
		}
	}

	void UniformUI::setValue(unsigned int* val, int size)
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
		memset(m_val,0,m_size*sizeof(unsigned int));
		for (int i = 0; i < size; i++)
		{
			m_val[i] = static_cast<unsigned int>(val[i]);
		}
	}

	void UniformUI::setValue(int* val, int size)
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
		memset(m_val,0,m_size*sizeof(unsigned int));
		for (int i = 0; i < size; i++)
		{
			m_val[i] = static_cast<unsigned int>(val[i]);
		}
	}
};