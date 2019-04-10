//Bresenham
void b_draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void b_draw_line(int x1, int x2, int y1, int y2) {
	int m_new=2*(y2 -y1);
	int slope_error_new = m_new - (x2 - x1);
	for (int x = x1, y = y1; x <= x2; x++)
	{
   	draw_pixel(x,y);
	if (slope_error_new <= 0)
	{
	slope_error_new =slope_error_new + m_new;
	}
	else{
    y=y+1
	slope_error_new  =slope_error_new+ m_new -2 * (x2 - x1);
	} } }
void b_display() {
	draw_line(x1, x2, y1, y2);
	glFlush();
}

//Scanline
void sc_drawpixel(int x,int y)
{
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void edgedetect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,int *le,int *re)
{
    float mx,x,temp;
    int i,k;
    if((y2-y1)<0)
    {
        temp=x1;
        x1=x2;
        x2=temp;
        temp=y1;
        y1=y2;
        y2=temp;
    }
    if((y2-y1)!=0)
        mx=(x2-x1)/(y2-y1);
    else
        mx=x2-x1;
    x=x1;
    for(i=(int)y1;i<(int)y2;i++)
    {
        int t=0;       
        if(x<(float)le[i])
        {
            if((float)le[i]!=500)
            {
                le[i]=(int)x;
                for(k=re[i]-1;k>le[i];k--)
                    drawpixel(k, i);
                le[i]=500;
                re[i]=0;
                t=1;
            }
            else
                le[i]=(int)x;
        }
        if(t==0)
        if(x>(float)re[i])
        {
            if((float)re[i]!=0)
            {
                re[i]=(int)x;
                for(k=le[i]+1;k<re[i];k++)
                    drawpixel(k,i);
                le[i]=500;
                re[i]=0;
            }
            else
                re[i]=(int)x;
        }
        x+=mx;
    }
}

void scanfill(GLfloat *x,GLfloat *y)
{
    int le[500],re[500];
    int i;
    for(i=0;i<500;i++)
    {
        le[i]=500;
        re[i]=0;
    }

    for(int k=0;k<n-1;k++)
    {
        edgedetect(x[k],y[k],x[k+1],y[k+1],le,re);

    }
    edgedetect(x[n-1],y[n-1],x[0],y[0],le,re);
}

void sc_display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    for(int k=0;k<n;k++)
    {
        glVertex2f(x[k],y[k]);
    }
    glEnd();

    scanfill(x,y);

    glFlush();
}


//Ellipse
void el_draw_pixel(int x,int y){
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(x+x1,y+y1);
    glEnd();
}
void el_points(int x,int y){
    draw_pixel(x, y);
    draw_pixel(x, -y);
    draw_pixel(-x, -y);
    draw_pixel(-x, y);
    
}
void draw_ellipse(){
    double d2;
    int x=0,y=b;
    int sa=a*a;
    int sb=b*b;
    double d1=sb-sa*b+0.25*sa;
    points(x, y);
    while(sa*(y-0.5)>sb*(x+1)){
        if(d1<0){
            d1+=sb*((x<<1)+3);
        }
        else{
            d1+=sb*((x<<1)+3)+sa*(-(y<<1)+2);
            y--;
        }
        x++;
        points(x, y);
    }
    d2=sb*(x)*(x)+sa*(y)*(y)-sa*sb;
    while(y>0){
        if(d2<0){
            d2+=sb*((x<<1)+2)+sa*(-(y<<1)+3);
            x++;
        }
        else{
            d2+=sa*(-(y<<1)+3);
        }
        y--;
        points(x, y);
    }
    
}
void el_display(void){
    
    draw_ellipse();
    glFlush();
}

//Circle
void circ_plot(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x+pntX1, y+pntY1);
	glEnd();
}
void midPointCircleAlgo()
{
	int x = 0;
	int y = r;
	float decision = 5/4 - r;
	plot(x, y);
	while (y > x)
	{
		if (decision < 0)
		{
			x++;
			decision += 2*x+1;
		}
		else
		{
			y--;
			x++;
			decision += 2*(x-y)+1;
		}
		plot( x,  y);
		plot( x, -y);
		plot(-x,  y);
		plot(-x, -y);
		plot( y,  x);
		plot(-y,  x);
		plot( y, -x);
		plot(-y, -x);
	}
}
void circ_display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	glPointSize(1.0);
	midPointCircleAlgo();
	glFlush ();
}

//Clipping
int code(float x,float y)
{
    int c=0;
    if(y>ymax)c=8;
    if(y<ymin)c=4;
    if(x>xmax)c=c|2;
    if(x<xmin)c=c|1;
    return c;
}
void cohen_Line(float x1,float y1,float x2,float y2,int i)
{
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m=(y2-y1)/(x2-x1);
    while((c1|c2)>0)
    {
        if((c1 & c2)>0)
        {
            xd1[i]=0;
            xd2[i]=0;
           break;
        }
    float xi=x1;
    float yi=y1;
    int c=c1;
    if(c==0)
    {
         c=c2;
         xi=x2;
         yi=y2;
    }
    float x,y;
    if((c & 8)>0)
    {
       y=ymax;
       x=xi+ 1.0/m*(ymax-yi);
    }
    else
      if((c & 4)>0)
      {
          y=ymin;
          x=xi+1.0/m*(ymin-yi);
      }
      else
       if((c & 2)>0)
       {
           x=xmax;
           y=yi+m*(xmax-xi);
       }
       else
       if((c & 1)>0)
       {
           x=xmin;
           y=yi+m*(xmin-xi);
       }

       if(c==c1)
       {
           xd1[i]=x;
           yd1[i]=y;
           c1=code(xd1[i],yd1[i]);
       }

       if(c==c2)
       {
           xd2[i]=x;
           yd2[i]=y;
           c2=code(xd2[i],yd2[i]);
       }
}
 clip_display();
}
void mykey(unsigned char key,int x,int y)
{
    if(key=='c')
    {
        for(int i=0;i<n;i++)
        {
            cohen_Line(xd1[i],yd1[i],xd2[i],yd2[i],i);
        }
        glFlush();
    }
}
void clip_display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    for(int k=0;k<n;k++)
    {
        glVertex2f(x[k],y[k]);
    }
    glEnd();

    scanfill(x,y);

    glFlush();
}

