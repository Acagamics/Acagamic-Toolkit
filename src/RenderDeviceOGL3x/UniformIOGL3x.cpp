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
			m_arrayLength = 1 * count;
			m_val = new int[m_arrayLength];
			break;
		case(UniformDatatype::IntVector2):
			m_arrayLength = 2 * count;
			m_val = new int[m_arrayLength];
			break;
		case(UniformDatatype::IntVector3):
			m_arrayLength = 3 * count;
			m_val = new int[m_arrayLength];
			break;
		case(UniformDatatype::IntVector4):
			m_arrayLength = 4 * count;
			m_val = new int[m_arrayLength];
			break;
		default:
			LOG_FATAL("UniformDatatype does not exist");
			break;
		}
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
		default:
			LOG_FATAL("UniformDatatype does not exist");
			break;
		}
	}
}