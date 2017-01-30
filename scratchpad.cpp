#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glx.h>

using namespace std;

extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;

int main ( void ){
	// setenv("DISPLAY",":0",0);
	int argc = 1;
  	char *argv[1] = {(char*)"something"};
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");
	glEnable(GL_DEPTH_TEST);

	GLenum err = glewInit();
	if (GLEW_OK!=err){
		cout << glewGetErrorString(err) << endl;
	}	// // cout << G;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint foo = glCreateProgram();

	return 0;
}