#include "detailed_cube.h"

float *dcVertices;
float *dcTexCoords;
float *dcNormals;
int dcVertexCount;

void quad(int subdiv,int i1, int i2, float x, float y, float back, float nx, 
	float ny, float s,float t,int pos){
		dcVertices[i1*subdiv*3*4+i2*3*4+0+pos*3]=x;
		dcVertices[i1*subdiv*3*4+i2*3*4+1+pos*3]=y;
		dcVertices[i1*subdiv*3*4+i2*3*4+2+pos*3]=-back;
		dcNormals[i1*subdiv*3*4+i2*3*4+0+pos*3]=nx;
		dcNormals[i1*subdiv*3*4+i2*3*4+1+pos*3]=ny;
		dcNormals[i1*subdiv*3*4+i2*3*4+2+pos*3]=-1.0/3;
		dcTexCoords[i1*subdiv*2*4+i2*2*4+0+pos*2]=s;
		dcTexCoords[i1*subdiv*2*4+i2*2*4+1+pos*2]=t;
}

void initCube() {
	int subdiv=100; float back=1;
	float dn=(2.0/3)/subdiv;
	float nx=-1.0/3; float ny=-1.0/3;
	float s=0; float t=0;
	float dst=1.0/subdiv;
	float x=-back; float y=-back;
	float dp=(float)2*back/subdiv;

	dcVertices=new float[4*3*subdiv*subdiv];dcTexCoords=new float[4*2*subdiv*subdiv];
	dcNormals=new float[4*3*subdiv*subdiv];dcVertexCount=4*subdiv*subdiv;
	for (int i1=0;i1<subdiv;i1++) {
		for (int i2=0;i2<subdiv;i2++) {
			quad(subdiv,i1,i2,x,y,back,nx,ny,s,t,0);
			quad(subdiv,i1,i2,x+dp,y,back,nx+dn,ny,s+dst,t,1);
			quad(subdiv,i1,i2,x+dp,y+dp,back,nx+dn,ny+dn,s+dst,t+dst,2);
			quad(subdiv,i1,i2,x,y+dp,back,nx,ny+dn,s,t+dst,3);
			nx+=dn;x+=dp;s+=dst;
		}
		nx=-1.0/3;x=-back;s=0;
		ny+=dn;y+=dp;t+=dst;
	}
}

void wall() {
	glEnable(GL_NORMALIZE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,dcVertices);
	glNormalPointer(GL_FLOAT,0,dcNormals);
	glTexCoordPointer(2,GL_FLOAT,0,dcTexCoords);
	glDrawArrays(GL_QUADS,0,dcVertexCount);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void drawCube() {
	glPushMatrix();
	wall();
	glRotatef(90,1,0,0);
	wall();
	glRotatef(90,1,0,0);
	wall();
	glRotatef(90,1,0,0);
	wall();
	glRotatef(90,1,0,0);
	glRotatef(90,0,1,0);
	wall();
	glRotatef(180,0,1,0);
	wall();
	glPopMatrix();
}

void freeCube() {
	delete []dcVertices;
	delete []dcTexCoords;
	delete []dcNormals;
}