/* 
 * File:   GLFWApplication.cpp
 * Author: stuetzlec
 * 
 * Created on October 10, 2017, 3:31 PM
 * 
 * Code taken from and altered from: 
 * _CSC5210_Unit4_PerspectiveCameraCode
 * (Class Example)
 * 
 */

//#include "GLFWApplication.h"
#include "GLFWApplication.h"

GLFWApplication::GLFWApplication()
{

}

GLFWApplication::GLFWApplication(const GLFWApplication& orig)
{

}

GLFWApplication::~GLFWApplication()
{
}

int GLFWApplication::initializeApplication(int aaValue, // anti-aliasing level 
					   int minorVersion, // OpenGL version
					   int majorVersion,
					   string winTitle, // The title of the window
					   int winWidth, // Width and height of the window
					   int winHeight)
{
    // Initialize GLFW3
    if(!glfwInit())
    {
	cerr<<"Failed to initialize GLFW\n"<<endl;
	return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, aaValue); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Create the window
    window=glfwCreateWindow(winWidth, winHeight, winTitle.c_str(), NULL, NULL);
    if(window==NULL)
    {
		cerr<<"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n"<<endl;
		glfwTerminate();
		return -1;
    }
    // Need to make the window the "current context" before we use GLEW
    glfwMakeContextCurrent(window); // Initialize GLEW

    // To be safe, we’re using glew’s experimental stuff.
    glewExperimental=GL_TRUE;
    // Initialize and error check GLEW
    GLenum err=glewInit();
    if(GLEW_OK!=err)
    {
		// If something went wrong, print the error message
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);


    // Initialize the time
    glfwSetTime(0.0);
    curTime=glfwGetTime();

    printf("It did a thing! Maybe???????\n");
    return 1;
}

void GLFWApplication::initiateDrawLoop()
{
    while(!glfwWindowShouldClose(window))
    {
		draw();
    }
}

void GLFWApplication::draw()
{
    // Now, set the "delta time"
    double dt=glfwGetTime()-curTime;
    curTime=glfwGetTime();

    camera -> setDeltaTime(dt);

    // Clears the given framebuffer (in this case, color)
    // Could set color to clear to with glClearColor, default is black
    // Also clears the depth buffer, IMPORTANT because we're now in 3D
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Update the camera
    mat4 projectionMatrix=camera -> getPerspectiveMatrix();
    mat4 viewMatrix=camera -> getViewMatrix();
	//mat4 viewMatrix=camera -> getWhatAmIviewingMatrix();
    mat4 modelMatrix;
    mat4 PVMMatrix;
    GLint PVMid;

    // Draw everything
    for(int i=0; i<drawables.size(); i++)
    {
		if(drawables[i])
		{
			modelMatrix=drawables[i] -> getModelMatrix();
			PVMMatrix=projectionMatrix*viewMatrix * modelMatrix;
			PVMid=shader -> GetVariable("PVM");
			shader -> SetMatrix4(PVMid, 1, false, &PVMMatrix[0][0]);
			drawables[i] -> draw(shader);
		}
    }

    // Force OpenGL commands to begin execution
    glfwSwapBuffers(window);
    glfwPollEvents();
}


// Set up the internal callbacks

void GLFWApplication::initializeCallbacks()
{
	//frame_buffer_size_callback was added by Emma Theberge
	//found it in some code in early class room examples
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	
    //Setup the 'input mode'
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Set up the callbacks
    glfwSetKeyCallback(window, keyFunc);

    // Mouse input callback would be here:
    glfwSetMouseButtonCallback(window, clickFunc);

    // When the cursor moves
    glfwSetCursorPosCallback(window, mouseMoveFunc);
}

// Add a drawable object to the class

void GLFWApplication::addDrawableObject(DrawableObject* o)
{
    drawables.push_back(o);
}
