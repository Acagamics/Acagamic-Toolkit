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