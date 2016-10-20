/**
*
*	shader.cpp
*
**/

#include"shader.hpp"
#include"_include_opengl.hpp"
#include<sstream>
#include<stdexcept>
#include<fstream>
#include<cassert>
namespace aab	{
namespace visen	{

namespace shader_type
{    
    const ShaderType compute = GL_COMPUTE_SHADER;
    const ShaderType vertex = GL_VERTEX_SHADER;
    const ShaderType tesselation_control = GL_TESS_CONTROL_SHADER;
    const ShaderType tesselation_evaluation = GL_TESS_EVALUATION_SHADER;
    const ShaderType geometry = GL_GEOMETRY_SHADER;
    const ShaderType fragment = GL_FRAGMENT_SHADER;
};

Shader::Shader(const ShaderType shaderType)
{
    glId = glCreateShader(shaderType);
    
    if(GL_FALSE == glIsShader(glId))
    {
        throw std::runtime_error("failed to create opengl shader.");
    }
}

Shader::~Shader()
{
    if(glId)
    {
        glDeleteShader(glId);
    }
}

void copy_file_to_string(std::ifstream&file, std::string&string)
{
    file.seekg(0,std::ios::end);
    string.reserve(file.tellg());
    file.seekg(0,std::ios::beg);
    string.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());    
}


void Shader::loadFromFile(std::string filename)
{
    std::ifstream file(filename.c_str());
    
    if(! file)
    {
        std::stringstream error;
        error << "Shader file failed to open: " << filename << "\n";
        throw std::runtime_error(error.str());
    }
    
    
    std::string string;
    copy_file_to_string(file, string);                                         
    loadFromString(string);
    file.close();
}

void Shader::loadFromString(std::string string)
{
    char * shader_data = const_cast<char*>(string.c_str());
    glShaderSource(glId,1,(const GLchar **) &shader_data, NULL);    
    
    glCompileShader(glId);
    GLint status;
    glGetShaderiv(glId, GL_COMPILE_STATUS, &status);
    
    if(GL_TRUE != status)
    {
        std::string infoLog;
        std::stringstream error;
        error << "Shader failed to compile: " << getInfoLog(infoLog);
        throw std::logic_error(error.str());
    }
}

std::string Shader::getInfoLog()const
{
    GLint log_length;
    glGetShaderiv(glId, GL_INFO_LOG_LENGTH, &log_length);
    std::string infoLog(log_length,'_');
    glGetShaderInfoLog(glId, log_length,&log_length,const_cast<char*>(infoLog.data()));
    
    return infoLog;
}

std::string&Shader::getInfoLog(std::string&infoLog)const
{
    GLint log_length;
    glGetShaderiv(glId, GL_INFO_LOG_LENGTH, &log_length);
    infoLog.assign(log_length,'_');
    glGetShaderInfoLog(glId, log_length,&log_length,const_cast<char*>(infoLog.data()));
    
    return infoLog;
}

    
 //todo: implement   https://www.khronos.org/opengles/sdk/docs/man/xhtml/glShaderBinary.xml
    
    
}		//	visen
}		//	aab

