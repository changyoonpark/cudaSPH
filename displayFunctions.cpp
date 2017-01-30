#include "displayFunctions.h"

#define STRINGIFY(A) #A

const GLchar *_vertexShader = STRINGIFY(
                               uniform float pointRadius;  // point size in world space
                               uniform float pointScale;   // scale to calculate size in pixels
                               uniform float densityScale;
                               uniform float densityOffset;
                               void main()
{    
    // calculate window-space point size
    vec3 posEye = vec3(gl_ModelViewMatrix * vec4(gl_Vertex.xyz, 1.0)) + vec3(0,0,-2.0f);
    float dist = length(posEye);
    gl_PointSize = pointRadius * (pointScale / dist) * gl_Vertex.w;
    // gl_PointSize = pointRadius;

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz, 1.0);

    gl_FrontColor = gl_Color;
}
                           );

// pixel shader for rendering points as shaded spheres
const GLchar *_spherePixelShader = STRINGIFY(
                                    void main()
{
    const vec3 lightDir = vec3(0.577, 0.577, 0.577);

    // calculate normal from texture coordinates
    vec3 N;
    N.xy = gl_TexCoord[0].xy*vec2(2.0, -2.0) + vec2(-1.0, 1.0);
    float mag = dot(N.xy, N.xy);

    if (mag > 1.0) discard;   // kill pixels outside circle

    N.z = sqrt(1.0-mag);

    // calculate lighting
    float diffuse = max(0.0, dot(lightDir, N));

    gl_FragColor = gl_Color * diffuse;
}
                                );

DisplayFunctions::DisplayFunctions(){
}

void DisplayFunctions::setRenderMode(){

    glEnable(GL_POINT_SPRITE_ARB);
    glTexEnvi(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(shaderProgram);

    //Scale the particles according to the prespective
    glUniform1f(glGetUniformLocation(shaderProgram, "pointScale"), (float)height / tanf(60.0*0.5f*(float)M_PI/180.0f)); //60.0 is the FOV
    glUniform1f(glGetUniformLocation(shaderProgram, "pointRadius"), maxParticleDiameter / 2.0f);

    glColor3f(1, 1, 1);

    //Draw the particles on the screen.
    _drawPoints();

    glUseProgram(0);
    glDisable(GL_POINT_SPRITE_ARB);    
}

void DisplayFunctions::findDevice(){
    cudaGLSetGLDevice(0);
    cudaSetDevice(0);
}

uint DisplayFunctions::createVbo(uint size){
    uint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

// void DisplayFunctions::assignPosVBO(uint numParticles){
//     _numParticles = numParticles;
//     posVbo = createVBO(sizeof(float) * 4 * numParticles);
//     cudaGraphicsGLRegisterBuffer(&devicePosVbo, posVbo, cudaGraphicsMapFlagsNone);
// }

// void DisplayFunctions::assignColorVBO(uint numParticles){
//     colorVbo = createVBO(sizeof(float) * 4 * numParticles);
//     cudaGraphicsGLRegisterBuffer(&deviceColorVbo, colorVbo, cudaGraphicsMapFlagsNone);
// }
void DisplayFunctions::unmapGLBufferObject(cudaGraphicsResource_t *cuda_vbo_resource_pointer)
{
    cudaGraphicsUnmapResources(1, cuda_vbo_resource_pointer, 0);
}

void* DisplayFunctions::mapGLBufferObject(cudaGraphicsResource_t* cuda_vbo_resource_pointer)
{
    void *ptr;
    cout << "Resource Pointer : " << *cuda_vbo_resource_pointer << endl;
    cudaGraphicsMapResources(1, cuda_vbo_resource_pointer, 0);
    size_t num_bytes;
    cudaGraphicsResourceGetMappedPointer((void **)&ptr, &num_bytes, *cuda_vbo_resource_pointer);
    cout << "Num Bytes : " << num_bytes / (sizeof(float)) << endl;
    return ptr;
}


uint DisplayFunctions::_compileProgram(const char *vsource, const char *fsource){
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vsource, 0);
    glShaderSource(fragmentShader, 1, &fsource, 0);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLuint _program = glCreateProgram();

    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fragmentShader);

    glLinkProgram(_program);

    // check if program linked
    int success = 0;
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success)
    {        
        char temp[256];
        glGetProgramInfoLog(_program, 256, 0, temp);
        cout << "Failed to link program: " << temp;
        glDeleteProgram(_program);
        _program = 0;
    } else{
        cout << "Shader Program linked." << endl;
    }

    return _program;
    // return 0;
}


void DisplayFunctions::glutInitialize(int* argc, char** argv){
    width = 600;
    height = 600;
    //OpenGL Initialization
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCreateWindow("Particles");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.25, 0.25, 0.25, 1.0);    
    glutReportErrors(); 
    //
    GLenum err = glewInit();
    if (GLEW_OK!=err){
        cout << glewGetErrorString(err) << endl;
    }

    shaderProgram = _compileProgram(_vertexShader, _spherePixelShader);
    findDevice();
}

void DisplayFunctions::_drawPoints()
{
    // glBegin(GL_POINTS);
    // {
    //     glVertex3f(0.5,0.5,0.5);
    // }
    // glEnd();

    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glVertexPointer(4, GL_FLOAT, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    // glDrawArrays(GL_POINTS, 0, numParticles);
    glDrawArrays(GL_POINTS, 0, 1000);

    // if (m_colorVBO)
    // {
    //     glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
    //     glColorPointer(4, GL_FLOAT, 0, 0);
    //     glEnableClientState(GL_COLOR_ARRAY);
    // }


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

