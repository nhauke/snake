#include <GLFW/glfw3.h>
#include <winix/time.h>
#include <winix/rand.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
int main(int argc,char**argv){
	glfwInit();
	GLFWwindow*wnd=glfwCreateWindow(512,512,0,0,0);
	glfwMakeContextCurrent(wnd);
	glOrtho(0,512,512,0,1,-1);
	initrand();
	union{struct{uint16_t x,y;};uint32_t z;}tail[7396];
	die:;
	int tlen=1,apx=tail->x=256,apy=tail->y=256,dir=0;
	for(;;){
		glClear(GL_COLOR_BUFFER_BIT);
		int dx=glfwGetKey(wnd,GLFW_KEY_RIGHT)-glfwGetKey(wnd,GLFW_KEY_LEFT),dy=glfwGetKey(wnd,GLFW_KEY_DOWN)-glfwGetKey(wnd,GLFW_KEY_UP);
		if(!dx!=!dy){
			int d=dx?1-dx:2-dy;
			if((d&1)!=(dir&1))dir=d;
		}
		memmove(tail+1,tail,(tlen-1)*4);
		switch(dir){
		case 0:tail->x+=8;
		break;case 1:tail->y+=8;
		break;case 2:tail->x-=8;
		break;case 3:tail->y-=8;
		break;default:__builtin_unreachable();
		}
		if(tail->z&33554944)goto die;
		glColor3ub(0,255,0);
		for(int i=0;i<tlen;i++){
			if(i>2&&abs(tail[i].x-tail->x)<12&&abs(tail[i].y-tail->y)<12)goto die;
			glRecti(tail[i].x-8,tail[i].y-8,tail[i].x+8,tail[i].y+8);
			if(abs(tail[i].x-apx)<20&&abs(tail[i].y-apy)<20){
				do apx=rand()&511; while(apx<32||apx>480);
				do apy=rand()&511; while(apy<32||apy>480);
				tail[tlen]=tail[tlen-1];
				tlen++;
			}
		}
		glColor3ub(255,0,0);
		glRecti(apx-12,apy-12,apx+12,apy+12);
		glfwSwapBuffers(wnd);
		endframe(50);
		glfwPollEvents();
		if(glfwGetKey(wnd,GLFW_KEY_ESCAPE)||glfwWindowShouldClose(wnd))return 0;
	}
}