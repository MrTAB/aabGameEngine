/**
*
*	program.cpp
*
**/

#include"program.hpp"
#include"_include_opengl.hpp"
#include<stdexcept>
#include<sstream>
#include<cassert>
namespace aab	{
namespace visen	{

// Thoughts - make methods like setUniform and getUniformLocation accessed only by another object of which there is only one - therefore the activated program is switched into it when doing so.

namespace simple_component_type
{
  const signed int 
  byte_type = GL_BYTE,
  unsigned_byte_type = GL_UNSIGNED_BYTE,
  short_type = GL_SHORT,
  unsigned_short_type = GL_UNSIGNED_SHORT,
  int_type = GL_INT,
  unsigned_int_type = GL_UNSIGNED_INT;
}

namespace component_type
{
  const unsigned int 
  byte_type = GL_BYTE,
  unsigned_byte_type = GL_UNSIGNED_BYTE,
  short_type = GL_SHORT,
  unsigned_short_type = GL_UNSIGNED_SHORT,
  int_type = GL_INT,
  unsigned_int_type = GL_UNSIGNED_INT,
  half_float_type = GL_HALF_FLOAT,
  float_type = GL_FLOAT,
  double_type = GL_DOUBLE,
  fixed_type = GL_FIXED,
  int_2_10_10_10_rev_type = GL_INT_2_10_10_10_REV,
  unsigned_int_2_10_10_10_rev_type = GL_UNSIGNED_INT_2_10_10_10_REV,
  unsigned_int_10f_11f_11f_rev_type = GL_UNSIGNED_INT_10F_11F_11F_REV;
}

namespace pack_type
{
  const signed int 
  int_2_10_10_10_rev_type = GL_INT_2_10_10_10_REV,
  unsigned_int_2_10_10_10_rev_type = GL_UNSIGNED_INT_2_10_10_10_REV,
  unsigned_int_10f_11f_11f_rev_type = GL_UNSIGNED_INT_10F_11F_11F_REV;
}




Program::Program()
{
    glId = glCreateProgram();
    
    if(!glId)
    {
        throw std::runtime_error("aab::visen::Program::\tglCreateProgram() failed.");
    }
}

Program::Program(std::string vertexShaderFilename, std::string fragmentShaderfilename)
{
    glId = glCreateProgram();
    
    if(!glId)
    {
        throw std::runtime_error("aab::visen::Program::\tglCreateProgram() failed.");
    }
        
    Shader fShader(shader_type::fragment);
    Shader vShader(shader_type::vertex);
    
    attachShader(fShader);
    attachShader(vShader);    
    
    fShader.loadFromFile(fragmentShaderfilename);
    vShader.loadFromFile(vertexShaderFilename);
        
    link();
    
    detachShader(fShader);
    detachShader(vShader);
    
}

Program::~Program()
{
    glDeleteProgram(glId);
}

void Program::attachShader(Shader &shader)
{
    glAttachShader(getId(), shader.getId());
}

void Program::detachShader(Shader &shader)
{
    glDetachShader(getId(), shader.getId());
}


void Program::link()
{
    glLinkProgram(glId);
    
    GLint status;
    glGetProgramiv(glId,GL_LINK_STATUS, &status);
    
    if(GL_TRUE != status)
    {
        std::string infoLog;
        std::stringstream error;
        error << "Shader program failed to link: " << getInfoLog(infoLog);        
        throw std::logic_error(error.str());
    }
}

void Program::activate()
{
    glUseProgram(glId);
}

std::string Program::getInfoLog()const
{
    GLint log_length;
    glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &log_length);
    std::string infoLog(log_length,'_');
    glGetProgramInfoLog(glId, log_length,&log_length,const_cast<char*>(infoLog.data()));
    
    return infoLog;
}

std::string&Program::getInfoLog(std::string&infoLog)const
{
    GLint log_length;
    glGetProgramiv(glId, GL_INFO_LOG_LENGTH, &log_length);
    infoLog.assign(log_length,'_');
    glGetProgramInfoLog(glId, log_length,&log_length,const_cast<char*>(infoLog.data()));
    
    return infoLog;
}

bool Program::validate()const
{
    GLint validateStatus;
    glValidateProgram(glId);
    glGetProgramiv(glId, GL_VALIDATE_STATUS, &validateStatus);    
    return validateStatus;
}
bool Program::validate(std::string&out)const
{
    bool validateStatus = validate();
    getInfoLog(out);
    return validateStatus;
}

int Program::countShaders()const
{
    GLint shader_count;
    glGetProgramiv(glId, GL_ATTACHED_SHADERS, &shader_count);  
    return shader_count;
}

int Program::countActiveAttributes()const
{
    GLint active_attributes;
    glGetProgramiv(glId, GL_ACTIVE_ATTRIBUTES, &active_attributes);  
    return active_attributes;
}

int Program::countActiveUniforms()const
{
    GLint active_uniforms;
    glGetProgramiv(glId, GL_ACTIVE_UNIFORMS, &active_uniforms);  
    return active_uniforms;
}

Program::Location Program::getAttributeLocation(std::string name)const
{
    const Location location =  glGetAttribLocation(glId,name.c_str());
    
    #if NDEBUG
    if(-1 == location)
    {
        std::stringstream error;
        error << "Invalid attribute: " << name;
        throw std::logic_error(error.str());
    }
    #endif
    return location;
}

Program::Location Program::getUniformLocation(std::string name)const
{
    const Location location =  glGetUniformLocation(glId,name.c_str());
    
    #if NDEBUG
    if(-1 == location)
    {
        std::stringstream error;
        error << "Invalid uniform: " << name;
        throw std::logic_error(error.str());
    }
    #endif
    return location;
}


// SET ATTRIBUTE
//todo - make these statics so that it is more obvious that they work on the currently active program only?
//alternatively add asserts to test this case?

void Program::setAttrib(Location location, const float value)
{
    glVertexAttrib1f(location, value);
}
void Program::setAttrib(Location location, const float a, const float b)
{
    glVertexAttrib2f(location, a, b);
}
void Program::setAttrib(Location location, const float a, const float b, const float c)
{
    glVertexAttrib3f(location, a, b, c);
}
void Program::setAttrib(Location location, const float a, const float b, const float c, const float d)
{
    glVertexAttrib4f(location, a, b, c, d);
}

void Program::setAttrib(Location location, const short value)
{
    glVertexAttrib1s(location, value);
}
void Program::setAttrib(Location location, const short a, const short b)
{
    glVertexAttrib2s(location, a, b);
}
void Program::setAttrib(Location location, const short a, const short b, const short c)
{
    glVertexAttrib3s(location, a, b, c);
}
void Program::setAttrib(Location location, const short a, const short b, const short c, const short d)
{
    glVertexAttrib4s(location, a, b, c, d);
}

void Program::setAttrib(Location location, const double value)
{
    glVertexAttrib1d(location, value);
}
void Program::setAttrib(Location location, const double a, const double b)
{
    glVertexAttrib2d(location, a, b);
}
void Program::setAttrib(Location location, const double a, const double b, const double c)
{
    glVertexAttrib3d(location, a, b, c);
}
void Program::setAttrib(Location location, const double a, const double b, const double c, const double d)
{
    glVertexAttrib4d(location, a, b, c, d);
}


void Program::setAttrib1fv(Location location, const float*value)
{
    glVertexAttrib1fv(location, value);
}
void Program::setAttrib2fv(Location location, const float*value)
{
    glVertexAttrib2fv(location, value);
}
void Program::setAttrib3fv(Location location, const float*value)
{
    glVertexAttrib3fv(location, value);
}
void Program::setAttrib4fv(Location location, const float*value)
{
    glVertexAttrib4fv(location, value);
}

void Program::setAttrib1sv(Location location, const short*value)
{
    glVertexAttrib1sv(location, value);
}
void Program::setAttrib2sv(Location location, const short*value)
{
    glVertexAttrib2sv(location, value);
}
void Program::setAttrib3sv(Location location, const short*value)
{
    glVertexAttrib3sv(location, value);
}
void Program::setAttrib4sv(Location location, const short*value)
{
    glVertexAttrib4sv(location, value);
}

void Program::setAttrib1dv(Location location, const double*value)
{
    glVertexAttrib1dv(location, value);
}
void Program::setAttrib2dv(Location location, const double*value)
{
    glVertexAttrib2dv(location, value);
}
void Program::setAttrib3dv(Location location, const double*value)
{
    glVertexAttrib3dv(location, value);
}
void Program::setAttrib4dv(Location location, const double*value)
{
    glVertexAttrib4dv(location, value);
}
 
void Program::setAttribute(Location location, int v0)
{	
	glVertexAttribI1i(	location, 	v0);
}
void Program::setAttribute(Location location, unsigned int v0)
{
	glVertexAttribI1ui(	location, 	v0);
}
void Program::setAttribute(Location location, int v0, int v1)
{
	glVertexAttribI2i(	location, 	v0, 	v1);
}
void Program::setAttribute(Location location, unsigned int v0, unsigned int v1)
{
	glVertexAttribI2ui(	location, 	v0, 	v1);
}
void Program::setAttribute(Location location, int v0, int v1, int v2)
{
	glVertexAttribI3i(	location, 	v0, 	v1, 	v2);
}
void Program::setAttribute(Location location, unsigned int v0, unsigned int v1, unsigned int v2)
{
	glVertexAttribI3ui(	location, v0, v1,v2);
}
void Program::setAttributeNormalised(Location location, unsigned char v0,unsigned char v1,unsigned char v2,unsigned char v3)
{
	glVertexAttrib4Nub(	location, v0, v1,v2,v3);
}
void Program::setAttribute(Location location, int v0,int v1, int v2, int v3)
{
	glVertexAttribI4i(	location, v0, v1,v2,v3);
}
void Program::setAttribute(Location location, unsigned int v0,unsigned int v1,unsigned int v2,unsigned int v3)
{
	glVertexAttribI4ui(	location, v0, v1,v2,v3);
}
void Program::setAttributeL(Location location, double v0)
{
	glVertexAttribL1d(	location, 	v0);
}
void Program::setAttributeL(Location location, double v0, double v1)
{
	glVertexAttribL2d(	location, 	v0, 	v1);
}
void Program::setAttributeL(Location location, double v0, double v1, double v2)
{
	glVertexAttribL3d(	location, 	v0, 	v1, 	v2);
}
void Program::setAttributeL(Location location, double v0, double v1, double v2, double v3)
{
	glVertexAttribL4d(	location, 	v0, 	v1, 	v2, 	v3);
}
void Program::setAttribute1v(Location location, const int * v)
{
	glVertexAttribI1iv(	location, 	v); 
}
void Program::setAttribute1v(Location location, const unsigned int * v)
{
	glVertexAttribI1uiv(	location, v);
}
void Program::setAttribute2v(Location location, const int * v)
{
	glVertexAttribI2iv(	location, 	v);
}
void Program::setAttribute2v(Location location, const unsigned int * v)
{
	glVertexAttribI2uiv(	location, 	v);
}
void Program::setAttribute3v(Location location, const int *v)
{
	glVertexAttribI3iv(	location, 	v);
}
void Program::setAttribute3v(Location location, const unsigned int *v)
{
	glVertexAttribI3uiv(	location, 	v);
}
void Program::setAttribute4v(Location location, const int * v)
{
	glVertexAttrib4iv(	location, 	v);
}
void Program::setAttribute4v(Location location, const signed char * v)
{
	glVertexAttrib4bv(	location, 	v);
}
void Program::setAttribute4v(Location location, const unsigned char * v)
{
	glVertexAttrib4ubv(	location, 	v);
}
void Program::setAttribute4v(Location location, const unsigned short * v)
{
	glVertexAttrib4usv(	location, 	v);
}
void Program::setAttribute4v(Location location, const unsigned int * v)
{
	glVertexAttrib4uiv(	location, 	v);
}
void Program::setAttribute4vNormalised(Location location, const signed char *v)
{
	glVertexAttrib4Nbv(	location, 	v);
}
void Program::setAttribute4vNormalised(Location location, const short * v)
{
	glVertexAttrib4Nsv(	location, 	v);
}
void Program::setAttribute4vNormalised(Location location, const int * v)
{
	glVertexAttrib4Niv(	location, 	v);
}
void Program::setAttribute4vNormalised(Location location, const unsigned char * v)
{
	glVertexAttrib4Nubv(	location, 	v);
}
void Program::setAttribute4vNormalised(Location location, const unsigned short * v)
{
	glVertexAttrib4Nusv(	location, 	v);
}
void Program::setAttribute4vNormalised(Location location, const unsigned int * v)
{
	glVertexAttrib4Nuiv(	location, 	v);
}
void Program::setAttributeI4v(Location location, const signed char * v)
{
	glVertexAttribI4bv(	location, 	v);
}
void Program::setAttributeI4v(Location location, const unsigned char * v)
{
	glVertexAttribI4ubv(	location, 	v);
}
void Program::setAttributeI4v(Location location, const short * v)
{
	glVertexAttribI4sv(	location, 	v);
}
void Program::setAttributeI4v(Location location, const unsigned short * v)
{
	glVertexAttribI4usv(	location, 	v);
}
void Program::setAttributeI4v(Location location, const int * v)
{
	glVertexAttribI4iv(	location, 	v);
}
void Program::setAttributeI4v(Location location, const unsigned int*v)
{
	glVertexAttribI4uiv(	location, 	v);
}
void Program::setAttributeL1v(Location location, const double*v)
{
	glVertexAttribL1dv(	location, 	v);
}
void Program::setAttributeL2v(Location location, const double*v)
{
	glVertexAttribL2dv(	location, 	v);
}
void Program::setAttributeL3v(Location location, const double*v)
{
	glVertexAttribL3dv(	location, 	v);
}
void Program::setAttributeL4v(Location location, const double*v)
{
	glVertexAttribL4dv(	location, 	v);
}
void Program::setAttributePacked1(Location location, PackType type, bool normalised, unsigned int value)
{
	glVertexAttribP1ui(	location, 	type, 	normalised, 	value);
}
void Program::setAttributePacked2(Location location, PackType type, bool normalised, unsigned int value)
{
	glVertexAttribP2ui(	location, 	type, 	normalised, 	value);
}
void Program::setAttributePacked3(Location location, PackType type, bool normalised, unsigned int value)
{
	glVertexAttribP3ui(	location, 	type, 	normalised, 	value);
}
void Program::setAttributePacked4(Location location, PackType type, bool normalised, unsigned int value)
{
	glVertexAttribP4ui(	location, 	type, 	normalised, 	value);
}

// SET UNIFORM
void Program::setUniform(Location location, const float value)
{
    glUniform1f(location, value);
}
void Program::setUniform(Location location, const float a, const float b)
{
    glUniform2f(location, a, b);
}
void Program::setUniform(Location location, const float a, const float b, const float c)
{
    glUniform3f(location, a, b, c);
}
void Program::setUniform(Location location, const float a, const float b, const float c, const float d)
{
    glUniform4f(location, a, b, c, d);
}

void Program::setUniform(Location location, const int value)
{
    glUniform1i(location, value);
}
void Program::setUniform(Location location, const int a, const int b)
{
    glUniform2i(location, a, b);
}
void Program::setUniform(Location location, const int a, const int b, const int c)
{
    glUniform3i(location, a, b, c);
}
void Program::setUniform(Location location, const int a, const int b, const int c, const int d)
{
    glUniform4i(location, a, b, c, d);
}

void Program::setUniform(Location location, const unsigned int value)
{
    glUniform1ui(location, value);
}
void Program::setUniform(Location location, const unsigned int a, const unsigned int b)
{
    glUniform2ui(location, a, b);
}
void Program::setUniform(Location location, const unsigned int a, const unsigned int b, const unsigned int c)
{
    glUniform3ui(location, a, b, c);
}
void Program::setUniform(Location location, const unsigned int a, const unsigned int b, const unsigned int c, const unsigned int d)
{
    glUniform4ui(location, a, b, c, d);
}

void Program::setUniform1fv(Location location, const unsigned int count, const float*value)
{
    glUniform1fv(location, count, value);
}
void Program::setUniform2fv(Location location, const unsigned int count, const float*value)
{
    glUniform2fv(location, count, value);
}
void Program::setUniform3fv(Location location, const unsigned int count, const float*value)
{
    glUniform3fv(location, count, value);
}
void Program::setUniform4fv(Location location, const unsigned int count, const float*value)
{
    glUniform4fv(location, count, value);
}

void Program::setUniform1iv(Location location, const unsigned int count, const int*value)
{
    glUniform1iv(location, count, value);
}
void Program::setUniform2iv(Location location, const unsigned int count, const int*value)
{
    glUniform2iv(location, count, value);
}
void Program::setUniform3iv(Location location, const unsigned int count, const int*value)
{
    glUniform3iv(location, count, value);
}
void Program::setUniform4iv(Location location, const unsigned int count, const int*value)
{
    glUniform4iv(location, count, value);
}

void Program::setUniform1uiv(Location location, const unsigned int count, const unsigned int*value)
{
    glUniform1uiv(location, count, value);
}
void Program::setUniform2uiv(Location location, const unsigned int count, const unsigned int*value)
{
    glUniform2uiv(location, count, value);
}
void Program::setUniform3uiv(Location location, const unsigned int count, const unsigned int*value)
{
    glUniform3uiv(location, count, value);
}
void Program::setUniform4uiv(Location location, const unsigned int count, const unsigned int*value)
{
    glUniform4uiv(location, count, value);
}

void Program::setUniformMatrix2fv(Location location, const unsigned int count, const bool transpose, const float*value)
{
    glUniformMatrix2fv(location, count, transpose, value);
}
void Program::setUniformMatrix3fv(Location location, const unsigned int count, const bool transpose, const float*value)
{
    glUniformMatrix3fv(location, count, transpose, value);
}
void Program::setUniformMatrix4fv(Location location, const unsigned int count, const bool transpose, const float*value)
{
    glUniformMatrix4fv(location, count, transpose, value);
}
void Program::setUniformMatrix2x3fv(Location location, const unsigned int count, const bool transpose, const float*value)
{
    glUniformMatrix2x3fv(location, count, transpose, value);
}
void Program::setUniformMatrix3x2fv(Location location, const unsigned int count, const bool transpose, const float*value)
{
    glUniformMatrix3x2fv(location, count, transpose, value);
}
void Program::setUniformMatrix2x4fv(Location location, const unsigned int count, const bool transpose, const float*value)
{
    glUniformMatrix2x4fv(location, count, transpose, value);
}
void Program::setUniformMatrix4x2fv(Location location, const unsigned int count, const bool transpose, const float*value)
{
    glUniformMatrix4x2fv(location, count, transpose, value);
}
void Program::setUniformMatrix3x4fv(Location location, const unsigned int count, const bool transpose, const float*value)
{
    glUniformMatrix3x4fv(location, count, transpose, value);
}
void Program::setUniformMatrix4x3fv(Location location, const unsigned int count, const bool transpose, const float*value)
{
    glUniformMatrix4x3fv(location, count, transpose, value);
}


//todo - make these 3 private and provide larger wrappers that do the vertex array binding?
//Essentially, would make a VBO object for the various sizes and provide a method to enable.
// See http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_03

void Program::setAttributePointer(const Location location,
                      const int componentsPerVertex,
                      const ComponentType componentType,
                      const bool normaliseValues,
                      const size_t componentStride,
                      const void * pointer)
{
    glVertexAttribPointer(location,
        componentsPerVertex,
        componentType,
        normaliseValues,
        componentStride,
        pointer);
}

void Program::setAttributePointer(const Location location,
                      const int componentsPerVertex,
                      const SimpleComponentType componentType,
                      const size_t componentStride,
                      const void * pointer)  
{                    
    glVertexAttribIPointer(	location,
        componentsPerVertex,
        componentType,
        componentStride,
        pointer);
}

void Program::setAttributePointer(const Location location,
                      const int componentsPerVertex,
                      const size_t componentStride,
                      const void * pointer)
{
    glVertexAttribLPointer(	location,
        componentsPerVertex,
        GL_DOUBLE,
        componentStride,
        pointer);
}

void Program::enableAttributeArray(const Location location)
{
    glEnableVertexAttribArray(location);
}

void Program::disableAttributeArray(const Location location)
{
    glDisableVertexAttribArray(location);
}


//https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml

//https://www.opengl.org/sdk/docs/man/html/glVertexAttrib.xhtml
//DO THIS:  https://www.opengl.org/sdk/docs/man/html/glVertexAttribPointer.xhtml
  
  
//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glBindAttribLocation.xml
    
}		//	visen
}		//	aab


