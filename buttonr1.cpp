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

#include <\Users\James\Dropbox\My Programs\C++\headers\clickable_object.h>
#include <\Users\James\Dropbox\My Programs\C++\headers\glutPrint.h>
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

class button : public clickable_object
{

    public:
    char* name;

    int number;
    double width, height;
    int solidity;
    color current_color;
    int clicks,new_clicks;
    bool down;
    int value,new_value;
    bool on;
    bool states[2];

    bool highlighted()
    {
        if(cursor1.passive.x<xmax && cursor1.passive.x>xmin && cursor1.passive.y<ymax && cursor1.passive.y>ymin )
        return true;
        else
        return false;
    }

    void select()
    {
        if(cursor1.left_click && left_clicked())
        selected=true;
        if(cursor1.left_click && !left_clicked())
        selected=false;
    }

    void increment()
    {
        if(left_clicked())
        new_value=1;

        if(!cursor1.left_click)
        {
            value=value+new_value;
            new_value=0;
        }

    }

    void decrement()
    {
        if(left_clicked())
        new_value=1;

        if(!cursor1.left_click)
        {
            value=value-new_value;
            new_value=0;
        }

    }

    void count_clicks()
    {
        if(left_clicked())
        new_clicks=1;
        if(!cursor1.left_click)
        {
            clicks=clicks+new_clicks;
            new_clicks=0;
        }
    }

    void reset()
    {
        value=0;
        clicks=0;
    }

    void highlight()
    {
        if(highlighted() && !left_clicked())
        {
            current_color.set(YELLOW);
        }
    }

    void highlight(color c)
    {
        if(highlighted() && !left_clicked())
        {
            current_color.set(c);
        }
    }

    void onoff()
    {
        if(left_clicked() && on)
        {
            states[0]=false;
        }

        if(left_clicked() && !on)
        {
            states[0]=true;
        }

        if(!cursor1.left_click)
        {
            on=states[0];
        }
    }

    void function()
    {
        if(left_clicked() || on)
        {
            current_color.set(GREEN);

        }
        else
        {
            current_color.set(RED);
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

    void render()//draws the actual button
    {
        glColor3f(current_color.r,current_color.g,current_color.b);
        glBegin(GL_POLYGON);

        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner

        glEnd();
    }
    button()//button constructor
    {
        name="square button";
        object_no++;

        number=object_no;
        clicks=0;
        current.x=320;
        current.y=160;
        width=50.0;
        height=25.0;
        value=0;
        current_color.set(RED);
        set_boundaries();
    }

    button(float x, float y)
    {

        current.x=x;
        current.y=y;
        width=50.0;
        height=25.0;
        value=0;;
        current_color.set(RED);
    }

    button(float x, float y, color c)
    {

        current.x=x;
        current.y=y;
        width=50.0;
        height=25.0;
        value=0;;
        current_color.set(c);
    }


    button(float x, float y, float w, float h, color background_color)
    {
        current.x=x;
        current.y=y;
        width=w;
        height=h;
        clicks=0;
        value=0;
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
            sprintf(text,"value:%d",value);
            glutPrint (xmin+width/16,ymin+height/2, GLUT_BITMAP_HELVETICA_12, text, text_color.r,text_color.g,text_color.b, 0.5f);

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
        render_text();
    }

    text_button()
    {
        current_color.set(0.5,0.5,0.5);
        text_color.set(BLACK);
    }

    text_button(float x,float y)
    {
        current.x=x;
        current.y=y;
        width=50.0;
        height=25.0;
        current_color.set(0.5,0.5,0.5);
        text_color.set(BLACK);
    }

    text_button(float x,float y, color c)
    {
        current.x=x;
        current.y=y;
        width=50.0;
        height=25.0;
        current_color.set(c);
        text_color.set(BLACK);
    }

};

//create new button
text_button button1;
button button2(100,100,75,50,RED);
button button3(100,200,75,50,RED);
text_button button4(400,160);
button button5(400,100,75,50,RED);
button button6(400,200,75,50,RED);


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

    sprintf(text2,"button1=%.3f , %.3f",button1.current.x,button1.current.y);
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
