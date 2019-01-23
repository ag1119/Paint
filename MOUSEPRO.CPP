#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<process.h>
#include<graphics.h>

union REGS in,out;
void showmouse_graphics()
{
in.x.ax=1;
int86(0x33,&in,&out);
}


void hide_mouse()
{
in.x.ax=2;
int86(0x33,&in,&out);
}


//function to print which mouse button is pressed.....
void pos(int *x,int *y, int *button)
{
in.x.ax=3;
int86(0x33,&in,&out);
*button=out.x.bx;
*x=out.x.cx;
*y=out.x.dx;
}



void put()
{int i,j=1;
for(i=0;i<=280;i+=20)
{
setcolor(j);
rectangle(580,i,640,i+20);
setfillstyle(1,j);
floodfill(630,i+10,j);
j++;
}
for(i=0;i<=480;i+=62)
{
setcolor(1);
rectangle(i,0,i+62,20);
}
setcolor(10);
outtextxy(0,10,"freehand");
outtextxy(67,10,"circle");
outtextxy(126,10,"brush");
outtextxy(188,10,"rect");
setcolor(1);
line(580,0,580,300);

}

void changecolour(int *x,int *y,int *button,int *i,int *s)
{int p,j=1;
for(p=0;p<=280;p+=20)
{
if(*button==1&&*x>=580&&*x<=640&&*y>=p&&*y<=p+20)
*i=j;
j++;
if(j==16)
j=1;
 }

 for(p=0;p<=480;p+=62)
{
if(*button==1&&*x>=p&&*x<=p+62&&*y>=0&&*y<=20)
*s=j;
if(j==2);
j++;
if(j==8)
j=1;
 }
 }

void drawingshapes(int *x,int *y,int *button,int *i,int *x1, int *y1,int *s)
{
  while(!kbhit())
{
showmouse_graphics();
pos(x,y,button);
*x1=*x,*y1=*y;
changecolour(x,y,button,i,s);

switch(*s)
{case 1:
	while(*button==1&&*x<580&&*y>21)
{
hide_mouse();
setcolor(*i);
setlinestyle(0,1,1);
line(*x,*y,*x1,*y1);
*x=*x1;*y=*y1;
pos(x1,y1,button);
} break;

case 2:
while(*button==1&&*x<580&&*y>21)
{
hide_mouse();
setcolor(*i);
setlinestyle(0,1,1);
circle(*x,*y,30);
//setfillstyle(0,*i);
//floodfill(*x,*y,*i);
*x=*x1;*y=*y1;
pos(x1,y1,button);
}break;

case 3:
	while(*button==1&&*x<580&&*y>21)
{
hide_mouse();
setcolor(*i);
setlinestyle(0,3,3);
circle(*x,*y,4);
setfillstyle(1,*i);
floodfill(*x,*y,*i);
*x=*x1;*y=*y1;
pos(&*x1,&*y1,&*button);
} break;

case 4:

	while(*button==1&&*x<580&&*y>21)
{
hide_mouse();
setcolor(*i);
setlinestyle(0,1,1);
rectangle(*x,*y,*x1+40,*y1+40);
setfillstyle(1,*i);
floodfill(*x,*y,*i);
*x=*x1;*y=*y1;
pos(&*x1,&*y1,&*button);
} break;


}
}
}

void main()
{int gd=DETECT,gm,x,y,x1,y1,button;
int i=15,s=1;
initgraph(&gd,&gm,"c:\\tc\\bgi");
showmouse_graphics();
setbkcolor(8);
put();
drawingshapes(&x,&y,&button,&i,&x1,&y1,&s);
getch();
closegraph();

}
