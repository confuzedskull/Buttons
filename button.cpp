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
//Button
//By James Nakano
//This program demonstrates simple mouse-object interactivity that could be used for creating buttons
//It sets up a truly 2d environment (as apposed to 2d figures drawn in a 3d modelview) thankyou glOrtho

//changelog
//09/15/12
//started experimenting on moving the button with right click


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

//This is like printf but prints to gl window at given coordinates and color values
void glutPrint(float x, float y, LPVOID font, char* text, float r, float g, float b, float a)
{
    if(!text || !strlen(text)) return;
    bool blending = false;
    if(glIsEnabled(GL_BLEND)) blending = true;
    glEnable(GL_BLEND);
    glColor4f(r,g,b,a);
    glRasterPos2f(x,y);


    while (*text)
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
    if(!blending) glDisable(GL_BLEND);
}


class button
{

    public:
    char* name;
    char text[10];
    int number;
    point current;
    point resting;
    double width, height;
    int solidity;
    float xmin,xmax,ymin,ymax;
    float color[3];//RGB values
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
            if(color[1]==1 && color[2]==0 && color[3]==0)
            set_color(0.0,1.0,0.0);
            selected=true;
        }
        else
        set_color(1.0,0.0,0.0);

        if(selected==true)
        {
            current.x=mouse2_x;
            current.y=mouse2_y;
        }

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
    void set_color(float R,float G,float B)
    {
        color[1]=R;
        color[2]=G;
        color[3]=B;
    }


    void render()//draws the actual button
    {
        glColor3f(color[1],color[2],color[3]);
        glBegin(GL_POLYGON);

        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner

        glEnd();

        //this is supposed to be text within the button
        sprintf(text,"Button %d",number);
        glutPrint ((xmin+1),current.y, GLUT_BITMAP_HELVETICA_12, text, 0.0f,0.0f,0.0f, 0.5f);

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
        set_color(1.0,0.0,0.0);


        printf("object: %s no.%d initialized\n", name, number);//prints to terminal window
    }

};
//create new button
button button1;

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

	/*	if ( button==GLUT_LEFT_BUTTON && state==GLUT_UP )
	{

	}*/



	if ( button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN )
	{
        mouse2_x=x;
        mouse2_y=window_height-y;
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
    glClearColor (0.0, 0.0, 0.0, 1.0);//background color
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
