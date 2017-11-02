/* 
 * File:   GLFWApplication.h
 * Author: stuetzlec
 *
 * Created on October 10, 2017, 3:31 PM
 * 
 * Code taken from and altered from: 
 * _CSC5210_Unit4_PerspectiveCameraCode
 * (Class Example)
 */

#ifndef GLFWAPPLICATION_H
#define GLFWAPPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shader.hpp"
#include "Camera.h"

#include "DrawableObject.h"

using glm::vec3;
using glm::vec2;
using glm::mat4;
using std::vector;

class GLFWApplication
{
public:
    GLFWApplication();
    GLFWApplication(const GLFWApplication& orig);
    virtual ~GLFWApplication();

    // General Initialization Function
    int initializeApplication(int, int, int, string, int, int);
    void initiateDrawLoop();

    // Add a drawable object to the list
    void addDrawableObject(DrawableObject*);
    void setShaderProgram(Shader*);// Set the current shader program

    // Functions to set up the callbacks

    bool setKeyCallback(void (*func)(GLFWwindow*, int, int, int, int))
    {
	keyFunc = func;
	return true;
    }

    bool setMouseClickCallback(void (*func)(GLFWwindow*, int, int, int))
    {
	clickFunc = func;
	return true;
    }

    bool setMouseMotionCallback(void (*func)(GLFWwindow*, double, double))
    {
	mouseMoveFunc = func;
	return true;
    }
    void initializeCallbacks();

    // Set the camera and the shader

    void setCamera(Camera* c)
    {
	camera = c;
    }

    void setShader(Shader* s)
    {
	shader = s;
    }
private:
    vector< DrawableObject* > drawables;// The list of everything to draw
    double curTime;// The current time in the system
    Shader* shader;// The current shader program
    Camera* camera;
    GLFWwindow* window;// The OpenGL context window

    void draw();// Draw all of the drawable objects

    // Callback functions using some function pointers
    void (*keyFunc)(GLFWwindow*, int, int, int, int);
    void (*clickFunc)(GLFWwindow*, int, int, int);
    void (*mouseMoveFunc)(GLFWwindow*, double, double);

};

#endif /* GLFWAPPLICATION_H */

