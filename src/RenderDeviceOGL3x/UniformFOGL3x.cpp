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
			m_arrayLength = 1 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatVector2):
			m_arrayLength = 2 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatVector3):
			m_arrayLength = 3 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatVector4):
			m_arrayLength = 4 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatMatrix22):
			m_arrayLength = 4 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatMatrix23):
			m_arrayLength = 6 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatMatrix24):
			m_arrayLength = 8 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatMatrix32):
			m_arrayLength = 6 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatMatrix33):
			m_arrayLength = 9 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatMatrix34):
			m_arrayLength = 12 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatMatrix42):
			m_arrayLength = 8 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatMatrix43):
			m_arrayLength = 12 * count;
			m_val = new float[m_arrayLength];
			break;
		case(UniformDatatype::FloatMatrix44):
			m_arrayLength = 16 * count;
			m_val = new float[m_arrayLength];
			break;
		}
		memset(m_val, 0, m_arrayLength*sizeof(float));
	}

	void UniformF::clean()
	{
		switch(Datatype)
		{
		case(UniformDatatype::Float):
			glUniform1fv(Location, m_count, m_val);
			break;
		case(UniformDatatype::FloatVector2):
			glUniform2fv(Location, m_count, m_val);
			break;
		case(UniformDatatype::FloatVector3):
			glUniform3fv(Location, m_count, m_val);
			break;
		case(UniformDatatype::FloatVector4):
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
}