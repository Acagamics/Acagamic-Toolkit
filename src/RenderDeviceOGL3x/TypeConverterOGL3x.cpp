#pragma once
#include "TypeConverterOGL3x.h"
#include "GL\glew.h"
#include <string>
#include "ACTK.h"

namespace ACTK
{
	using namespace Core;
	using namespace Renderer;

	UniformDatatype TypeConverterOGL3x::ToActiveUniformDatatype(GLenum type)
	{
		switch (type)
		{
			case GL_INT:
				return UniformDatatype::Int;
			case GL_FLOAT:
				return UniformDatatype::Float;
			case GL_FLOAT_VEC2:
				return UniformDatatype::FloatVector2;
			case GL_FLOAT_VEC3:
				return UniformDatatype::FloatVector3;
			case GL_FLOAT_VEC4:
				return UniformDatatype::FloatVector4;
			case GL_INT_VEC2:
				return UniformDatatype::IntVector2;
			case GL_INT_VEC3:
				return UniformDatatype::IntVector3;
			case GL_INT_VEC4:
				return UniformDatatype::IntVector4;
			case GL_BOOL: 
				return UniformDatatype::Bool;
			case GL_BOOL_VEC2: 
				return UniformDatatype::BoolVector2;
			case GL_BOOL_VEC3: 
				return UniformDatatype::BoolVector3;
			case GL_BOOL_VEC4: 
				return UniformDatatype::BoolVector4;
			case GL_FLOAT_MAT2: 
				return UniformDatatype::FloatMatrix22;
			case GL_FLOAT_MAT3: 
				return UniformDatatype::FloatMatrix33;
			case GL_FLOAT_MAT4: 
				return UniformDatatype::FloatMatrix44;
			case GL_SAMPLER_1D: 
				return UniformDatatype::Sampler1D;
			case GL_SAMPLER_2D: 
				return UniformDatatype::Sampler2D;
			case GL_SAMPLER_2D_RECT: 
				return UniformDatatype::Sampler2DRectangle;
			case GL_SAMPLER_2D_RECT_SHADOW: 
				return UniformDatatype::Sampler2DRectangleShadow;
			case GL_SAMPLER_3D: 
				return UniformDatatype::Sampler3D;
			case GL_SAMPLER_CUBE: 
				return UniformDatatype::SamplerCube;
			case GL_SAMPLER_1D_SHADOW: 
				return UniformDatatype::Sampler1DShadow;
			case GL_SAMPLER_2D_SHADOW: 
				return UniformDatatype::Sampler2DShadow;
			case GL_FLOAT_MAT2x3: 
				return UniformDatatype::FloatMatrix23;
			case GL_FLOAT_MAT2x4: 
				return UniformDatatype::FloatMatrix24;
			case GL_FLOAT_MAT3x2: 
				return UniformDatatype::FloatMatrix32;
			case GL_FLOAT_MAT3x4: 
				return UniformDatatype::FloatMatrix34;
			case GL_FLOAT_MAT4x2: 
				return UniformDatatype::FloatMatrix42;
			case GL_FLOAT_MAT4x3: 
				return UniformDatatype::FloatMatrix43;
			case GL_SAMPLER_1D_ARRAY: 
				return UniformDatatype::Sampler1DArray;
			case GL_SAMPLER_2D_ARRAY: 
				return UniformDatatype::Sampler2DArray;
			case GL_SAMPLER_1D_ARRAY_SHADOW: 
				return UniformDatatype::Sampler1DArrayShadow;
			case GL_SAMPLER_2D_ARRAY_SHADOW: 
				return UniformDatatype::Sampler2DArrayShadow;
			case GL_SAMPLER_CUBE_SHADOW: 
				return UniformDatatype::SamplerCubeShadow;
			case GL_INT_SAMPLER_1D: 
				return UniformDatatype::IntSampler1D;
			case GL_INT_SAMPLER_2D: 
				return UniformDatatype::IntSampler2D;
			case GL_INT_SAMPLER_2D_RECT: 
				return UniformDatatype::IntSampler2DRectangle;
			case GL_INT_SAMPLER_3D: 
				return UniformDatatype::IntSampler3D;
			case GL_INT_SAMPLER_CUBE: 
				return UniformDatatype::IntSamplerCube;
			case GL_INT_SAMPLER_1D_ARRAY: 
				return UniformDatatype::IntSampler1DArray;
			case GL_INT_SAMPLER_2D_ARRAY: 
				return UniformDatatype::IntSampler2DArray;
			case GL_UNSIGNED_INT_SAMPLER_1D: 
				return UniformDatatype::UnsignedIntSampler1D;
			case GL_UNSIGNED_INT_SAMPLER_2D: 
				return UniformDatatype::UnsignedIntSampler2D;
			case GL_UNSIGNED_INT_SAMPLER_2D_RECT: 
				return UniformDatatype::UnsignedIntSampler2DRectangle;
			case GL_UNSIGNED_INT_SAMPLER_3D: 
				return UniformDatatype::UnsignedIntSampler3D;
			case GL_UNSIGNED_INT_SAMPLER_CUBE: 
				return UniformDatatype::UnsignedIntSamplerCube;
			case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY: 
				return UniformDatatype::UnsignedIntSampler1DArray;
			case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY: 
				return UniformDatatype::UnsignedIntSampler2DArray;
		}
		LOG_ASSERT(false, "ActiveAttribType does not exist.");
		return UniformDatatype::NONE;
	}

	GLenum TypeConverterOGL3x::To(PrimitiveType type)
	{
		switch (type)
		{
			case PrimitiveType::Lines:
				return GL_LINES;
			case PrimitiveType::LineLoop:
				return GL_LINE_LOOP;
			case PrimitiveType::LineStrip:
				return GL_LINE_STRIP;
			case PrimitiveType::LineStripAdjacency:
				return GL_LINE_STRIP_ADJACENCY;
			case PrimitiveType::LinesAdjacency:
				return GL_LINES_ADJACENCY;
			case PrimitiveType::Points:
				return GL_POINTS;
			case PrimitiveType::Triangles: 
				return GL_TRIANGLES;
			case PrimitiveType::TriangleFan: 
				return GL_TRIANGLE_FAN;
			case PrimitiveType::TriangleStrip: 
				return GL_TRIANGLE_STRIP;
			case PrimitiveType::TriangleStripAdjacency:
				return GL_TRIANGLE_STRIP_ADJACENCY;
			case PrimitiveType::TrianglesAdjacency:
				return GL_TRIANGLES_ADJACENCY;
			case PrimitiveType::Patches:
				return GL_PATCHES;
		}
		LOG_ASSERT(false, "PrimitiveType does not exist.");
		return GL_INVALID_ENUM;
	}
};