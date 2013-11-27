#include "ACTK.h"
#include "ShaderProgramOGL3x.h"

#include "GL\glew.h"

namespace ACTK
{
	ShaderProgramOGL3x::ShaderProgramOGL3x(const std::string& vertexShaderSource, const std::string& geometryShaderSource, const std::string& fragmentShaderSource):
		m_program(nullptr),
		m_vertexShader(nullptr),
		m_geometryShader(nullptr),
		m_fragmentShader(nullptr)
	{
		// ToDo: Alle Shader laden und kompilieren lassen und dann zu einem Programm zusammenfügen.
		// Dann schön alle fehler ausgeben, falls es welche gibt.
	}

	ShaderProgramOGL3x::~ShaderProgramOGL3x()
	{
		delete m_vertexShader;
		delete m_geometryShader;
		delete m_fragmentShader;
		delete m_program;
	}

	void ShaderProgramOGL3x::Bind()
	{
		glUseProgram(m_program->getHandle());
	}

	unsigned int ShaderProgramOGL3x::GetPogramHandle()
	{
		return m_program->getHandle();
	}

	bool ShaderProgramOGL3x::IsReady()
	{
		return m_ready;
	}

	std::string	ShaderProgramOGL3x::GetProgramInfoLog()
	{
		return m_program->GetInfoLog();
	}
}