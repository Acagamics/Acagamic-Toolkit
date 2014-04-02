#pragma once
#include "UniformOGL3x.h"
#include "GL\glew.h"
#include <string>
#include "ACTK.h"

namespace ACTK
{
	UniformUI::UniformUI(int location, UniformDatatype datatype, int count, ICleanableObserver* observer) : UniformOGL3x<unsigned int>(location, datatype, count, observer)
	{
		switch (Datatype)
		{
		case(UniformDatatype::Int):
			m_arrayLength = 1 * count;
			m_val = new unsigned int[m_arrayLength];
			break;
		case(UniformDatatype::IntVector2):
			m_arrayLength = 2 * count;
			m_val = new unsigned int[m_arrayLength];
			break;
		case(UniformDatatype::IntVector3):
			m_arrayLength = 3 * count;
			m_val = new unsigned int[m_arrayLength];
			break;
		case(UniformDatatype::IntVector4):
			m_arrayLength = 4 * count;
			m_val = new unsigned int[m_arrayLength];
			break;
		}
		memset(m_val, 0, m_arrayLength*sizeof(unsigned int));
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
};