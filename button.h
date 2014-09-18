
class button : public clickable_object
{

    public:
    char* name;
    int number;
    double width, height;
    int clicks,new_clicks;
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
        clicks=0;
        current.set(320,160);
        width=50.0;
        height=25.0;
        value=0;
        current_color.set(RED);
        set_boundaries();
    }

    button(color c)
    {
        name="square button";
        clicks=0;
        current.set(320,160);
        width=50.0;
        height=25.0;
        value=0;
        current_color.set(c);
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
