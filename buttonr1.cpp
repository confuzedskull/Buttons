#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <\Users\James\Dropbox\My Programs\C\color.h>
#include <\Users\James\Dropbox\My Programs\C\glutPrint.h>
//Button
//By James Nakano
//This program demonstrates simple mouse-object interactivity that could be used for creating buttons
//It sets up a truly 2d environment (as apposed to 2d figures drawn in a 3d modelview) thankyou glOrtho

//changelog
//started using my own header files for the first time ever.
//changed float color to color current_color in button class
//overloaded button constructor
//created text_button class of super class object
//removed right click control from mouse_func

//width and height of program window
int window_width=640;
int window_height=320;

int random1 = rand() % 50;
int random2 = rand() % 50;

int object_no=0;

struct point {float x; float y;};
struct vect {float x; float y;};
char text1[30];
char text2[30];

float lastx, lasty;
//left click coordinates (global variable)
int mouse_x;
int mouse_y;
//right click coordinates (global variable)
int mouse2_x;
int mouse2_y;

class button
{

    public:
    char* name;

    int number;
    point current;
    point resting;
    double width, height;
    int solidity;
    float xmin,xmax,ymin,ymax;
    color current_color;
    bool clicked()
    {
        if(mouse_x<xmax && mouse_x>xmin && mouse_y<ymax && mouse_y>ymin)
        return true;
        else
        return false;
    }

    bool selected;
    void function()//
    {
        if(clicked()==true)
        {
            if(current_color.r==1 && current_color.g==0 && current_color.b==0)
            current_color.set(GREEN);
            selected=true;
        }
        else
        current_color.set(RED);

    }
    void set_coordinates(float a,float b)
    {
        current.x=a;
        current.y=b;
    }
    void set_boundaries()//calculates the limits of the button based on its coordinates and size
    {
        xmin= current.x-(width/2);
        xmax= current.x+(width/2);
        ymin= current.y-(height/2);
        ymax= current.y+(height/2);
    }

    void render()//draws the actual button
    {
        glColor3f(current_color.r,current_color.g,current_color.b);
        glBegin(GL_POLYGON);

        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner

        glEnd();
        glFlush();
    }
    button()//button constructor
    {
        name="square button";
        object_no++;

        number=object_no;

        current.x=320;
        current.y=160;
        width=50.0;
        height=25.0;
        current_color.set(RED);

    }

    button(float x, float y)
    {
        current.x=x;
        current.y=y;
        width=50.0;
        height=25.0;
        current_color.set(RED);
    }

    button(float x, float y, double w, double h, color background_color)
    {
        current.x=x;
        current.y=y;
        width=w;
        height=h;
        current_color=background_color;
    }

};


class text_button: public button
{
    public:
    char text[10];
    color text_color;

    void render_text()
        {
            //this is supposed to be text within the button
            sprintf(text,"Button %d",number);
            glutPrint (current.x,current.y, GLUT_BITMAP_HELVETICA_12, text, text_color.r,text_color.g,text_color.b, 0.5f);

        }
    void render()//draws the actual button
    {
        render_text();
        glColor3f(current_color.r,current_color.g,current_color.b);
        glBegin(GL_POLYGON);

        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner

        glEnd();
        glFlush();
    }

    text_button()
    {
        text_color.set(BLUE);

    }
};
//create new button
text_button button1;

//not used yet
float distance(float x1, float y1, float x2, float y2)
{
    return (sqrt(pow((x2 - x1),2) + pow((y2 - y1),2)));
}

//handles window resizing
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();
        //set an Orthographic view
	glOrtho(0.0,(GLdouble)w,0.0,(GLdouble)h, -1.0,1.0);

    // Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	// Set the correct perspective.
	//gluPerspective(45.0f, ratio, 1, 100);
	window_width=w;
    window_height=h;

}




void mouse_enter(int state)
{
    if (state==GLUT_ENTERED)
    glutWarpPointer(window_width / 2, window_height / 2);
}
//handles mouse actions
void mouse_func( int button, int state, int x, int y )
{
	if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
	{
	    mouse_x=x;
	    mouse_y=window_height-y;
	}


}
//not used yet
void mouseMovement(int x, int y) {
    int diffx=x-lastx; //check the difference between the current x and the last x position
    int diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position

}
//takes care of the text on screen
void text ()
{
    sprintf(text1,"mouse=%i , %i",mouse_x,mouse_y);
    glutPrint (0.0,10.0, GLUT_BITMAP_HELVETICA_12, text1, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text2,"button1=%.3f , %.3f",button1.current.x,button1.current.y);
    glutPrint (0.0,0.0, GLUT_BITMAP_HELVETICA_12, text2, 1.0f,0.0f,0.0f, 0.5f);


}

//draws the main scene
void renderScene(void) {

//render the objects
    glClear(GL_COLOR_BUFFER_BIT);
    text();
    glutPostRedisplay();

    button1.set_boundaries();
    button1.function();
    button1.render();

	glutSwapBuffers();
}
//preliminary settings that set up drawing environment
void initializeWindow()
{
    glClearColor (0.0, 0.0, 0.0, 0.5);//background color
    glViewport(0,0,window_width,window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble) window_width , 0.0, (GLdouble) window_height , -1.0, 1.0);

    glClearColor (0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

}
//used this in mouse motion function
void mouse(int x, int y)
{

    mouse2_x=x;
    mouse2_y=window_height-y;
}

int main(int argc, char **argv) {
    /* initialize random seed: */
    srand ( time(NULL) );
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(window_width,window_height);
	printf("window size: %dX%d\n", window_width, window_height);
	glutCreateWindow("Button");
	initializeWindow();
	glutReshapeFunc(changeSize);

    //glutEntryFunc(mouse_enter);
    glutMouseFunc(mouse_func);
    //glutMotionFunc(mouse);
    //glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	// enter GLUT event processing cycle
	glutDisplayFunc(renderScene);
	printf("rendering...\n");
	glutMainLoop();


}
