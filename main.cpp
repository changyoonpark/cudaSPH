
#include <iostream>
#include "particleSystem.h"
#include "displayFunctions.h"
#include "particleSolver.cuh"
#include "particleSystem_cuda.cuh"


#include <GL/freeglut.h>


// MemoryOperations memOp;
// SolverFunctions solverFunctions;
// SimulationParameters simParams;
ParticleSystem *pSys;

DisplayFunctions dispFunc;

using namespace std;

// Glut Callback Functions.
void cleanup(){

}

void display(){

//DEMO CODE//DEMO CODE//DEMO CODE
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glBegin(GL_QUADS);                      // Draw A Quad
 //        glVertex3f(-0.1f, 0.1f, 1.f);              // Top Left
 //        glVertex3f( 0.1f, 0.1f, -1.f);              // Top Right
 //        glVertex3f( 0.1f,-0.1f, -1.f);              // Bottom Right
 //        glVertex3f(-0.1f,-0.1f, 1.f);              // Bottom Left
	// glEnd();
	//     glutSwapBuffers();
//DEMO CODE//DEMO CODE//DEMO CODE

	
	// // //update the cuda array.
	// // //map the cuda array to vbo.
    pSys->timeStep(); 
    dispFunc.numParticles = pSys->numParticles;
	dispFunc.posVbo = pSys->posVbo;    
	// dispFunc.posVbo = pSys->devicePosVbo;
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Display Mode Settings

    glColor3f(1.0, 1.0, 1.0);
    glutWireCube(1.0);


    dispFunc.setRenderMode();
    glutSwapBuffers();

}

void reshape(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 100.0);
    // gluPerspective(40.0, 1, 0.1, 100.0);
	glTranslatef(0.0, 0.0, -2.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);

}

void idle(void){
    glutPostRedisplay();
}

void createParticleSystem(){
	//This call 
	//1. creates particles on the host
	//2. allocates memory on GPU
	//3. registers the vbo with CUDA
	//The reference to the position is in 
	//   >> pSys->devicePosReference

	pSys = new ParticleSystem(1000);
	dispFunc.maxParticleDiameter = pSys->maxParticleDiameter;
}

int main ( int argc, char** argv ){	
	setenv("DISPLAY",":0",0);

	//initiate the opengl context.
	dispFunc.glutInitialize( &argc, argv );
	createParticleSystem();


    cout << "Done" << endl;
    // MemoryOperations::printVector(foo);

	//in the display callback, 
	//we update device memory for the next frame,
	//map the device memory to a vbo,

//DEMO CODE//DEMO CODE//DEMO CODE
	// glutInit(&argc, argv);
	// glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	// glutInitWindowPosition(100,100);
	// glutInitWindowSize(320,320);
	// glutCreateWindow("Lighthouse3D - GLUT Tutorial");
//DEMO CODE//DEMO CODE//DEMO CODE

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// glutIdleFunc(idle);
	// glutCloseFunc(cleanup);
	
	glutMainLoop();


	// pSys->devMem.cleanUpDevice();
	// cout << "Sequence Finished." << endl;



	return 1;
}
