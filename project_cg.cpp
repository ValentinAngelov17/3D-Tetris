// project_cg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <GL\GLU.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <GL/freeglut.h>
//#include <SDL.h>


const int gridSizeX = 10;
const int gridSizeY = 20;
const int gridSizeZ = 3;

float rotationAngleX = 0.0;
float rotationAngleY = 0.0;
float zoom = 30.0;  // Initial zoom level

int lastMouseX = -1;
int lastMouseY = -1;

void drawCube(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glutWireCube(1.0);
    glPopMatrix();
}

void drawGrid() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1.0, 1.0, 1.0, 0.5);  // Set grid line color with alpha value

    for (int i = 0; i < gridSizeX; ++i) {
        for (int j = 0; j < gridSizeY; ++j) {
            for (int k = 0; k < gridSizeZ; ++k) {
                // Check if it's an outer grid line
                if (i == 0 || i == gridSizeX - 1 || j == 0 || j == gridSizeY - 1 || k == 0 || k == gridSizeZ - 1) {
                    glColor4f(1.0, 1.0, 1.0, 1.0);  // White and fully opaque
                }
                else {
                    glColor4f(1.0, 1.0, 1.0, 0.5);  // White and semi-transparent
                }

                drawCube(i, j, k);
            }
        }
    }
    


    glDisable(GL_BLEND);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up your camera/viewpoint here gluLookAt(30.0, 30.0, zoom, 5.0, 10.0, 0.0, 0.0, 1.0, 0.0);

    gluLookAt(30.0, 30.0, zoom, 5.0, 10.0, 1.0, 0.0, 1.0, 0.0);

    // Rotate the scene based on user input
    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleY, 0.0, 1.0, 0.0);

    // Draw the grid of cubes
    drawGrid();

    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        rotationAngleX += 5.0;
        break;
    case GLUT_KEY_DOWN:
        rotationAngleX -= 5.0;
        break;
    case GLUT_KEY_LEFT:
        rotationAngleY -= 5.0;
        break;
    case GLUT_KEY_RIGHT:
        rotationAngleY += 5.0;
        break;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        lastMouseX = -1;
        lastMouseY = -1;
    }
}

void motion(int x, int y) {
    if (lastMouseX != -1 && lastMouseY != -1) {
        rotationAngleY += (x - lastMouseX) * 0.1;
        rotationAngleX += (y - lastMouseY) * 0.1;
        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

void mouseWheel(int wheel, int direction, int x, int y) {
    if (direction == -1) {
        zoom += 1.0;
    }
    else if (direction == 1 && zoom > 1.0) {
        zoom -= 1.0;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1100, 800); // Set the initial window size to 800x600
    glutCreateWindow("3D Tetris");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMouseWheelFunc(mouseWheel);  // Function for mouse wheel input

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    gluPerspective(35.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glutMainLoop();

    return 0;
}