#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5,0.0,0.0);
    glVertex3f(0.0,0.5,0.0);
    glEnd();

    glutSwapBuffers();
}

void changeSize(int width, int height){
    if(height ==0) height = 1;
    float ratio = width*1.0/height;


    std::cout<<"Resizing with w,h,r: "<<width<<","<<height<<","<<ratio<<std::endl;

    // use the projection matrix
    glMatrixMode(GL_PROJECTION);

    // Reset matrix
    glLoadIdentity();

    // set the viewport to be the entire window
    glViewport(0,0,width,height);

    // set the correct perspective
    gluPerspective(45,ratio,1,1000);
    // get back to the modelview
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("GLUT - Tutorial");

    glutDisplayFunc(display);
    glutReshapeFunc(changeSize);
    glutMainLoop();
    return 0;
}
