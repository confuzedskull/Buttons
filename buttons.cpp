#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "glutPrint.h"
#include "clickable_object.h"
#include "button.h"
#include "text_button.h"

//Button
//By James Nakano
//This program demonstrates simple mouse-object interactivity that could be used for creating buttons
//It sets up a truly 2d environment (as apposed to 2d figures drawn in a 3d modelview) thankyou glOrtho

//width and height of program window
int window_width=640;
int window_height=320;

int random1 = rand() % 50;
int random2 = rand() % 50;

float mousex;
float mousey;

char text1[30];
char text2[50];
char text3[40];
char text4[100];
char text5[3];

//create new button
text_button button1;
button button2(100,100,75,50,RED);
button button3(100,200,75,50,RED);
text_button button4(400,160);
button button5(400,100,75,50,RED);
text_button button6(400,200,75,50,RED);
text_button button7("click me",320,100);

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
	    cursor1.left_down.x=x;
	    cursor1.left_down.y=window_height-y;
	    cursor1.left_click=true;
	}
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
        cursor1.left_click=false;
	}
}

//takes care of the text on screen
void text ()
{
    sprintf(text1,"mouse=%.3f , %.3f",cursor1.passive.x,cursor1.passive.y);
    glutPrint (0.0,10.0, GLUT_BITMAP_HELVETICA_12, text1, 0.0f,0.0f,0.0f, 0.5f);

    sprintf(text2,"button=%.3f , %.3f",button1.current.x,button1.current.y);
    glutPrint (0.0,0.0, GLUT_BITMAP_HELVETICA_12, text2, 0.0f,0.0f,0.0f, 0.5f);

    sprintf(text3,"Buttons!");
    glutPrint (300,300, GLUT_BITMAP_HELVETICA_18, text3, 0.0f,0.0f,0.0f, 1.0f);

    sprintf(text4,"Hovering over a button makes it yellow. Clicking turns it green.");
    glutPrint (25,280, GLUT_BITMAP_HELVETICA_12, text4, 0.0f,0.0f,0.0f, 0.5f);
}

//draws the main scene
void renderScene(void) {

//render the objects

    glClear(GL_COLOR_BUFFER_BIT); //apparently this is what causes the flickering
    text();
    glutPostRedisplay();

    button1.function();
    button1.set_boundaries();
    button1.highlight();
    button1.increment();
    button1.print_value();
    button1.render();

    button2.function();
    button2.set_boundaries();
    button2.highlight();
    button2.render();

    button3.function();
    button3.highlight();
    button3.set_boundaries();
    button3.render();

    button4.function();
    button4.highlight();
    button4.decrement();
    button4.print_value();
    button4.set_boundaries();
    button4.render();

    button5.function();
    button5.highlight();
    button5.set_boundaries();
    button5.render();

    button6.function();
    button6.highlight();
    button6.set_boundaries();
    button6.render();

    button7.function();
    button7.set_boundaries();
    button7.render();

    glFlush();
}
//preliminary settings that set up drawing environment
void initializeWindow()
{
    glClearColor (1.0, 1.0, 1.0, 1.0);//background color
    glViewport(0,0,window_width,window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble) window_width , 0.0, (GLdouble) window_height , -1.0, 1.0);
    glFlush();
}
//used this in mouse motion function
void mouse_move(int x, int y)
{
    cursor1.passive.x=x;
    cursor1.passive.y=window_height-y;
    mousex=x;
    mousey=window_height-y;
}

int main(int argc, char **argv) {
    /* initialize random seed: */
    srand ( time(NULL) );
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(window_width,window_height);
	printf("window size: %dX%d\n", window_width, window_height);
	glutCreateWindow("Buttons");
	initializeWindow();
	glutReshapeFunc(changeSize);
	//glutIdleFunc(renderScene);

    //glutEntryFunc(mouse_enter);
    glutMouseFunc(mouse_func);
    //glutMotionFunc(mouse_drag);
    glutPassiveMotionFunc(mouse_move); //check for mouse movement
	// enter GLUT event processing cycle
	glutDisplayFunc(renderScene);
	printf("rendering...\n");
	glutMainLoop();

    button2.current.x=100;
    button2.current.y=100;


}
