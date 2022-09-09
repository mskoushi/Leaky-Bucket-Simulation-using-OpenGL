#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int k,n,iter=0;
int pkt[30];
int outputed=0;
int a[100];
int flag=0;
int start=0;
int overflow=0;
int temp=0,change=0;
int res=0;
void drawBitmapText( float x, float y, float z,char *string)
{
    char *c;
    glRasterPos3f(x, y, z);

    for (c = string; *c != '\0'; c++)
    {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

int *compute()
{
 int c=0,total=0;
 int op,bucketsize,i;
 printf("enter out op:\n");
 scanf("%d",&op);
 printf("enter the bucket size \n");
 scanf("%d",&bucketsize);
	 printf("enter the number of packets\n");
	 scanf("%d",&n);

	 for(i=0;i<n;i++)
	 {
		printf("Enter packet bandwidth %d :  ",i+1);
		scanf("%d",&pkt[i]);
	 }


	   for(int j=0;j<n;j++)
	   {

            total += pkt[j];
           if(total <= bucketsize)
           {
               a[j]=1;
             printf("\nInput from line %d with op %d is added to the bucket\nCurrent bucket size(Mb) is %d",(j+1),pkt[j],total);

           }
           else
           {
               a[j]=0;
            total -= pkt[j];
            printf("\nInput from line %d with op %d is dropped from the bucket\nCurrent bucket size(Mb) is %d",(j+1),pkt[j],total);

           }
           }

        if(total <= op)
         {
            printf("packet sent to outputline at op %d" ,total);
            outputed++;
            total = 0;
            printf("current bucket size is %d", total);
         }
        else
        {
            total -= op;
            printf("\n---------------------------------");
            printf("\npacket sent to output line at op %d \n Current bucket size(Mb)is %d",op,total);
            outputed++;
	   }


return a;
}

void setpoint(GLint x,GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

int round1(double number)
{
	return (number>=0) ? (int)(number+0.5):(int)(number-0.5);
}
void LineWithDDA(int x0,int y0,int x1,int y1)
{
	int dy=y1-y0;
	int dx=x1-x0;
	int steps,i;
	float xinc,yinc,x=x0,y=y0;
	if(abs(dx)>abs(dy))
	{
		steps=abs(dx);
	}
	else
	{
		steps=abs(dy);
	}
	xinc=(float)dx/(float)steps;
	yinc=(float)dy/(float)steps;
	setpoint(round1(x),round1(y));
	for(i=0;i<steps;i++)
	{
		x+=xinc;
		y+=yinc;
		setpoint(round1(x),round1(y));
	}
	glPointSize(5);
	glutSwapBuffers();
}
void Circle(int r,int xCenter,int yCenter)
{

	int x=0,y=r;
	int d = 3/2 - r;
	glColor3f( 0 ,0, 1);
	while(x<=y)
	{
		setpoint(xCenter+x,yCenter+y);
		setpoint(xCenter+y,yCenter+x);
		setpoint(xCenter-x,yCenter+y);
		setpoint(xCenter+y,yCenter-x);
		setpoint(xCenter-x,yCenter-y);
		setpoint(xCenter-y,yCenter-x);
		setpoint(xCenter+x,yCenter-y);
		setpoint(xCenter-y,yCenter+x);

		if (d<0)
			d+=(2*x)+3;
		else
		{
			d+=(2*(x-y))+5;
			y-=1;
		}
		x++;
	}
	glFlush();
}
void ke(unsigned char key,int x,int y)
{
	switch(key)
	{
	case's':{ start=1;flag=1;

		break;
	}
			case 'c':
				{
					if(start!=0)
						start=2;
					if(change==0)
						glClearColor(1,1,1,1);
					else if(change==1)
						glClearColor(0,0,0,0);
					else if(change==2)
						glClearColor(0.5,0.5,0.5,0);
					change++;
					if(change>2)
						change=change-3;
					break;
				}
	case 'E':exit(1);
		break;
	}
		glutPostRedisplay();
}
void draw()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	if(start==0)
	{

		int const w = glutGet(GLUT_WINDOW_WIDTH);
		int const h = glutGet(GLUT_WINDOW_HEIGHT);

		glColor3f(0,0,1);
		drawBitmapText(3*w/10,5*h/6,0.0,"VIVEKANANDA COLLEGE OF ENGINEERING AND TECHNOLOGY,PUTTUR");
		glColor3f(0.7,0,1);
		drawBitmapText(3*w/10-20,4*h/6+30,0.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
		glColor3f(1,0.5,0);
		drawBitmapText(4*w/10,7*h/12,0.0,"A MINI PROJECT ON:");
		glColor3f(1,0,0);
		drawBitmapText(4*w/10,5*h/12+30,0.0,"Leaky Bucket Algorithm");
		glColor3f(1,0.5,0);
		drawBitmapText(10,180,0.0,"BY:");
		glColor3f(0.5,0,0.5);
		drawBitmapText(20,155,0.0,"NAME: Chethan B M      (USN:4VP19CS020)");
		drawBitmapText(20,130,0.0,"NAME: Koushik M S                    (USN:4VP19CS047)");

		glColor3f(0.5,0.2,0.2);
		drawBitmapText(7*w/10+10,150,0.0,"GUIDE NAME: Mr.Krishna Mohan A J ");

		glColor3f(1,0.1,1);
		drawBitmapText(8*w/10,50,0.0,"PRESS 'S' TO START");
		glMatrixMode(GL_MODELVIEW);

	}
	else if(start==1)
     {





		int const w = glutGet(GLUT_WINDOW_WIDTH);
		int const h = glutGet(GLUT_WINDOW_HEIGHT);
		int *arr1;

		glTranslatef(600,0,0);
		glRotatef(180,0,1,0);
		glScalef(2.0,2.0,0);

		if(flag==1)
			arr1=compute();

for(int in=0;in<n;in++)
{

		Circle(3,102,183);
		Circle(1,102,183);
		//pipe
		glColor3f( 1.0 ,0.0, 0.0);
		LineWithDDA(40,180,100,180);
		LineWithDDA(40,185,100,185);
		//st.line
		glColor3f( 1.0 ,0.0, 0.0);
		LineWithDDA(40,60,40,250);
		//bucket
		glColor3f( 0.0 ,1.0, 0.0);
		LineWithDDA(75,60,125,60);
		LineWithDDA(125,60,125,120);
		LineWithDDA(75,120,75,60);






		int i=0;
		glColor3f( 0 ,0, 255);

		while(i<13)
		{
			k=0;
			while(k<10000)
			{
				int j=0;
				while(j<10000)
				{
					j++;
				}
				k++;
			}
			Circle(3,102,183-(10*i));
			Circle(1,102,183-(10*i));

			i++;
		}
		//overflow
		if(arr1[in]==0)
		{

			int i=0;
			glColor3f( 0 ,0, 255);
			LineWithDDA(76,61,124,61);
			while(i<60)
			{
				k=0;
				while(k<1000)
				{
					int j=0;
					while(j<10000)
					{
						j++;
					}
					k++;
				}

				LineWithDDA(76,61+i,124,61+i);
				i++;
			}


			glClearColor(0,0,0,0);
			glColor3f(1,0,0);
			drawBitmapText(200,100,0.0,"BUCKET OVERFLOW");




		}



		if(arr1[in]==1)
		{
		    glClear(GL_COLOR_BUFFER_BIT);
		    int t=0;
		    t=t+pkt[in];
		i=0;
		glColor3f( 0 ,0, 255);
		LineWithDDA(76,61,124,61);
		while(i<=t)
		{
			k=0;
			while(k<1000)
			{
				int j=0;
				while(j<10000)
				{
					j++;
				}
				k++;
			}

			LineWithDDA(76,61+i,124,61+i);
			i++;
		}


		}

		}




	res=1;
	flag=0;

glColor3f( 0 ,0, 200/255.0);
		Circle(1,102,63);
		int i=0;

		while(i<(outputed+1))
		{
			k=0;
			while(k<10000)
			{
				int j=0;
				while(j<10000)
				{
					j++;
				}
				k++;
			}
			Circle(1,102,63-(10*i));

			i++;

	}




	}

	glutSwapBuffers();
	glFlush();

}
void reshape(int w, int h)
{

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w,0,h);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	if(res==1)
		start=2;
	glutPostRedisplay();
}

int main(int argc,char **argv)
{

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(1000,480);
	glutCreateWindow("Leaky Bucket");
	glutKeyboardFunc(ke);

	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutMainLoop();

}
