#include <GL/glew.h>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glx.h>


#include <math.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include <iostream>

extern const GLchar *_vertexShader;
extern const GLchar *_spherePixelShader;

using namespace std;

#ifndef M_PI
	#define M_PI    3.1415926535897932384626433832795
#endif

#ifndef GL_FUNC_DEFS
#define GL_FUNC_DEFS
#define USE_GL_FUNC(name, proto) extern proto name
    USE_GL_FUNC(glBindBuffer, PFNGLBINDBUFFERPROC);
    USE_GL_FUNC(glGenBuffers, PFNGLGENBUFFERSPROC);
    USE_GL_FUNC(glBufferData, PFNGLBUFFERDATAPROC);
    USE_GL_FUNC(glCreateShader, PFNGLCREATESHADERPROC);
    USE_GL_FUNC(glCompileShader, PFNGLCOMPILESHADERPROC);
    USE_GL_FUNC(glCreateProgram, PFNGLCREATEPROGRAMPROC);
    USE_GL_FUNC(glAttachShader, PFNGLATTACHSHADERPROC);
    USE_GL_FUNC(glLinkProgram, PFNGLLINKPROGRAMPROC);
    USE_GL_FUNC(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC);    
    USE_GL_FUNC(glDeleteProgram, PFNGLDELETEPROGRAMPROC);
    USE_GL_FUNC(glGetProgramiv, PFNGLGETPROGRAMIVPROC);
	USE_GL_FUNC(glUniform1f, PFNGLUNIFORM1FPROC);
    USE_GL_FUNC(glUseProgram, PFNGLUSEPROGRAMPROC);
    USE_GL_FUNC(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC);
    USE_GL_FUNC(glShaderSource, PFNGLSHADERSOURCEPROC);

	#ifndef GLX_EXTENSION_NAME
	    USE_GL_FUNC(glActiveTexture, PFNGLACTIVETEXTUREPROC);
	    USE_GL_FUNC(glClientActiveTexture, PFNGLACTIVETEXTUREPROC);
	#endif
#endif

class DisplayFunctions{
private:


	void findDevice();

public:
	DisplayFunctions();

	uint numParticles;
	uint shaderProgram;
	uint height;
	uint width;

	uint posVbo;
	uint colorVbo;

	float maxParticleDiameter;

	static uint _compileProgram(const char *vsource, const char *fsource);
	static void unmapGLBufferObject(cudaGraphicsResource_t *cuda_vbo_resource);
	static void* mapGLBufferObject(cudaGraphicsResource_t *cuda_vbo_resource);

	void _drawPoints();
	void setRenderMode();
	void glutInitialize(int*,char**);
	// void setVertexBuffer(uint vbo);
	// vi

	static uint createVbo(uint size);
	static void assignPosVBO(uint);

	// void assignColorVBO(uint);

};