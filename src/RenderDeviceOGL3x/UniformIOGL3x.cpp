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

	void UniformI::setValue(int* val, int size)
	{
		if(m_size >= size)
		{
			if(m_dirty)
			{
				m_dirty = true;
				m_observer->notifyDirty(this);
			}
			memcpy(m_val, val, size);
		}
		else
		{
			LOG_FATAL("Du hast richtig scheiﬂe gebaut!");
		}
	}
}