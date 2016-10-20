/**
*
*	shader.hpp
*
*	Use for rendering to a texture
**/

#if !defined(AAB_VISEN_SHADER_CLASS)
#define AAB_VISEN_SHADER_CLASS
#include<string>
namespace aab	{
namespace visen	{

typedef unsigned int ShaderType;

namespace shader_type
{    
    extern const ShaderType compute;
    extern const ShaderType vertex;
    extern const ShaderType tesselation_control;
    extern const ShaderType tesselation_evaluation;
    extern const ShaderType geometry;
    extern const ShaderType fragment;
};

class Shader
{
	private:

        unsigned int glId;
        
        Shader(const Shader&);

	public:

    unsigned int getId()const
    {
        return glId;
    }

    explicit Shader(const ShaderType);

    ~Shader();

    void loadFromFile(std::string filename);
    void loadFromString(std::string string);    

    std::string getInfoLog()const;

    std::string& getInfoLog(std::string&infoLog)const;

};




}		//	visen
}		//	aab
#endif //AAB_VISEN_FRAME_BUFFER_CLASS
