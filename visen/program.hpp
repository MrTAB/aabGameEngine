/**
*
*	program.hpp
*
*	Use for rendering to a texture
**/

#if !defined(AAB_VISEN_PROGRAM_CLASS)
#define AAB_VISEN_PROGRAM_CLASS
#include"shader.hpp"
#include<string>
namespace aab	{
namespace visen	{

namespace simple_component_type
{
  extern const signed int 
  byte_type,
  unsigned_byte_type,
  short_type,
  unsigned_short_type,
  int_type,
  unsigned_int_type;
}

namespace component_type
{
  extern const unsigned int 
  byte_type,
  unsigned_byte_type,
  short_type,
  unsigned_short_type,
  int_type,
  unsigned_int_type,
  half_float_type,
  float_type,
  double_type,
  fixed_type,
  int_2_10_10_10_rev_type,
  unsigned_int_2_10_10_10_rev_type,
  unsigned_int_10f_11f_11f_rev_type;
}

namespace pack_type
{
  extern const signed int 
  int_2_10_10_10_rev_type,
  unsigned_int_2_10_10_10_rev_type,
  unsigned_int_10f_11f_11f_rev_type;
}

class Program
{
	private:

        unsigned int glId;
        
        Program(const Program&);

	public:
	
	typedef signed int SimpleComponentType; // signed difference provides some warning if used in exchange of each other.
	typedef unsigned int ComponentType;
	
	typedef unsigned int PackType;	
	typedef unsigned int Location;
	


    unsigned int getId()const
    {
        return glId;
    }

    Program();
    
    Program(std::string vertexShaderFilename, std::string fragmentShaderfilename);

    ~Program();

    void attachShader(Shader&shader);

    void detachShader(Shader&shader); // not: shaders can be detached and deleted after linking if they are not required anymore.

    void link();

    void activate();

    std::string getInfoLog()const;

    std::string&getInfoLog(std::string&infoLog)const;
    
    bool validate()const;
    bool validate(std::string&out)const;

    int countShaders()const;
    int countActiveAttributes()const;
    int countActiveUniforms()const;
    
    Location getAttributeLocation(std::string name)const;
    Location getUniformLocation(std::string name)const;

    void setAttrib(Location location, const float value);
    void setAttrib(Location location, const float a, const float b);
    void setAttrib(Location location, const float a, const float b, const float c);
    void setAttrib(Location location, const float a, const float b, const float c, const float d);

    void setAttrib(Location location, const short value);
    void setAttrib(Location location, const short a, const short b);
    void setAttrib(Location location, const short a, const short b, const short c);
    void setAttrib(Location location, const short a, const short b, const short c, const short d);

    void setAttrib(Location location, const double value);
    void setAttrib(Location location, const double a, const double b);
    void setAttrib(Location location, const double a, const double b, const double c);
    void setAttrib(Location location, const double a, const double b, const double c, const double d);

    void setAttrib1fv(Location location, const float*value);
    void setAttrib2fv(Location location, const float*value);
    void setAttrib3fv(Location location, const float*value);
    void setAttrib4fv(Location location, const float*value);

    void setAttrib1sv(Location location, const short*value);
    void setAttrib2sv(Location location, const short*value);
    void setAttrib3sv(Location location, const short*value);
    void setAttrib4sv(Location location, const short*value);

    void setAttrib1dv(Location location, const double*value);
    void setAttrib2dv(Location location, const double*value);
    void setAttrib3dv(Location location, const double*value);
    void setAttrib4dv(Location location, const double*value);
     
    void setAttribute(Location location, int v0);
    void setAttribute(Location location, unsigned int v0);
    void setAttribute(Location location, int v0, int v1);
    void setAttribute(Location location, unsigned int v0, unsigned int v1);
    void setAttribute(Location location, int v0, int v1, int v2);
    void setAttribute(Location location, unsigned int v0, unsigned int v1, unsigned int v2);
    void setAttributeNormalised(Location location, unsigned char v0,unsigned char v1,unsigned char v2,unsigned char v3);
    void setAttribute(Location location, int v0,int v1, int v2, int v3);
    void setAttribute(Location location, unsigned int v0,unsigned int v1,unsigned int v2,unsigned int v3);
    void setAttributeL(Location location, double v0);
    void setAttributeL(Location location, double v0, double v1);
    void setAttributeL(Location location, double v0, double v1, double v2);
    void setAttributeL(Location location, double v0, double v1, double v2, double v3);
    void setAttribute1v(Location location, const int * v);
    void setAttribute1v(Location location, const unsigned int * v);
    void setAttribute2v(Location location, const int * v);
    void setAttribute2v(Location location, const unsigned int * v);
    void setAttribute3v(Location location, const int *v);
    void setAttribute3v(Location location, const unsigned int *v);
    void setAttribute4v(Location location, const int * v);
    void setAttribute4v(Location location, const signed char * v);
    void setAttribute4v(Location location, const unsigned char * v);
    void setAttribute4v(Location location, const unsigned short * v);
    void setAttribute4v(Location location, const unsigned int * v);
    void setAttribute4vNormalised(Location location, const signed char *v);
    void setAttribute4vNormalised(Location location, const short * v);
    void setAttribute4vNormalised(Location location, const int * v);
    void setAttribute4vNormalised(Location location, const unsigned char * v);
    void setAttribute4vNormalised(Location location, const unsigned short * v);
    void setAttribute4vNormalised(Location location, const unsigned int * v);
    void setAttributeI4v(Location location, const signed char * v);
    void setAttributeI4v(Location location, const unsigned char * v);
    void setAttributeI4v(Location location, const short * v);
    void setAttributeI4v(Location location, const unsigned short * v);
    void setAttributeI4v(Location location, const int * v);
    void setAttributeI4v(Location location, const unsigned int * v);
    void setAttributeL1v(Location location, const double*);
    void setAttributeL2v(Location location, const double*);
    void setAttributeL3v(Location location, const double*);
    void setAttributeL4v(Location location, const double*);
    void setAttributePacked1(Location location, PackType type, bool normalised, unsigned int value);
    void setAttributePacked2(Location location, PackType type, bool normalised, unsigned int value);
    void setAttributePacked3(Location locatio, PackType type, bool normalised, unsigned int valuen);
    void setAttributePacked4(Location location, PackType type, bool normalised, unsigned int value);


    // SET UNIFORM
    void setUniform(Location location, const float value);
    void setUniform(Location location, const float a, const float b);
    void setUniform(Location location, const float a, const float b, const float c);
    void setUniform(Location location, const float a, const float b, const float c, const float d);

    void setUniform(Location location, const int value);
    void setUniform(Location location, const int a, const int b);
    void setUniform(Location location, const int a, const int b, const int c);
    void setUniform(Location location, const int a, const int b, const int c, const int d);

    void setUniform(Location location, const unsigned int value);
    void setUniform(Location location, const unsigned int a, const unsigned int b);
    void setUniform(Location location, const unsigned int a, const unsigned int b, const unsigned int c);
    void setUniform(Location location, const unsigned int a, const unsigned int b, const unsigned int c, const unsigned int d);

    void setUniform1fv(Location location, const unsigned int count, const float*value);
    void setUniform2fv(Location location, const unsigned int count, const float*value);
    void setUniform3fv(Location location, const unsigned int count, const float*value);
    void setUniform4fv(Location location, const unsigned int count, const float*value);

    void setUniform1iv(Location location, const unsigned int count, const int*value);
    void setUniform2iv(Location location, const unsigned int count, const int*value);
    void setUniform3iv(Location location, const unsigned int count, const int*value);
    void setUniform4iv(Location location, const unsigned int count, const int*value);

    void setUniform1uiv(Location location, const unsigned int count, const unsigned int*value);
    void setUniform2uiv(Location location, const unsigned int count, const unsigned int*value);
    void setUniform3uiv(Location location, const unsigned int count, const unsigned int*value);
    void setUniform4uiv(Location location, const unsigned int count, const unsigned int*value);

    void setUniformMatrix2fv(Location location, const unsigned int count, const bool transpose, const float*value);
    void setUniformMatrix3fv(Location location, const unsigned int count, const bool transpose, const float*value);
    void setUniformMatrix4fv(Location location, const unsigned int count, const bool transpose, const float*value);
    void setUniformMatrix2x3fv(Location location, const unsigned int count, const bool transpose, const float*value);
    void setUniformMatrix3x2fv(Location location, const unsigned int count, const bool transpose, const float*value);
    void setUniformMatrix2x4fv(Location location, const unsigned int count, const bool transpose, const float*value);
    void setUniformMatrix4x2fv(Location location, const unsigned int count, const bool transpose, const float*value);
    void setUniformMatrix3x4fv(Location location, const unsigned int count, const bool transpose, const float*value);
    void setUniformMatrix4x3fv(Location location, const unsigned int count, const bool transpose, const float*value);


    //todo - make these 3 private and provide larger wrappers that do the vertex array binding?

    void setAttributePointer(const Location location,
                          const int componentsPerVertex,
                          const ComponentType componentType,
                          const bool normaliseValues,
                          const size_t componentStride,
                          const void * pointer);
    void setAttributePointer(const Location location,
                          const int componentsPerVertex,
                          const SimpleComponentType componentType,
                          const size_t componentStride,
                          const void * pointer);
    void setAttributePointer(const Location location,
                          const int componentsPerVertex,
                          const size_t componentStride,
                          const void * pointer);


    void enableAttributeArray(const Location location);
    void disableAttributeArray(const Location location);
  
};




}		//	visen
}		//	aab
#endif //AAB_VISEN_FRAME_BUFFER_CLASS
