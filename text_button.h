class text_button: public button
{
    public:
    char text[10];
    color text_color;

    void print_value()
    {
        sprintf(text,"value:%i",value);
    }

    void print_clicks()
    {
        sprintf(text,"clicks:%i",clicks);
    }

    void print_label(char* label)
    {
        sprintf(text,label);
    }

    void render_text()
        {
            //this is supposed to be text within the button
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
        clicks=0;
        value=0;
        current_color.set(0.5,0.5,0.5);
        text_color.set(BLACK);
        sprintf(text,"button #%i",number);
    }

    text_button(char* label)
    {

        clicks=0;
        value=0;
        current_color.set(0.5,0.5,0.5);
        text_color.set(BLACK);
        sprintf(text,label);
    }

    text_button(char* label,float x,float y)
    {
        current.set(x,y);
        clicks=0;
        value=0;
        current_color.set(0.5,0.5,0.5);
        text_color.set(BLACK);
        sprintf(text,label);
    }

    text_button(float x,float y)
    {
        value=0;
        clicks=0;
        current.x=x;
        current.y=y;
        width=50.0;
        height=25.0;
        current_color.set(0.5,0.5,0.5);
        text_color.set(BLACK);
        sprintf(text,"button #%i",number);
    }

    text_button(float x,float y, color c)
    {
        current.x=x;
        current.y=y;
        width=50.0;
        height=25.0;
        current_color.set(c);
        text_color.set(BLACK);
        sprintf(text,"button #%i",number);
    }

    text_button(float x, float y, float w, float h, color c)
    {
        current.x=x;
        current.y=y;
        width=w;
        height=h;
        clicks=0;
        value=0;
        text_color.set(BLACK);
        current_color.set(c);
        sprintf(text,"button #%i",number);
    }

};
