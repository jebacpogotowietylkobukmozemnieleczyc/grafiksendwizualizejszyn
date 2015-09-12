#ifndef _SOLIDSPHERE_H
#define _SOLIDSPHERE_H
#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cmath>
#include<array>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class CircularAccess {
private:
    const std::vector<bool>& vector_;
public:
    CircularAccess(std::vector<bool>& vector):vector_(vector){}
   auto operator[](int index) {
       return vector_[(index% vector_.size()+vector_.size())%vector_.size()];
   }
};

class SolidSphere {
protected:
  std::vector<GLfloat> vertices;
  std::vector<GLfloat> normals;
  std::vector<GLfloat> texcoords;
  std::vector<GLushort> indices;
  std::vector<GLfloat>& shadow;
  float radius;
  unsigned int rings;
  unsigned int sectors;

public:
  SolidSphere(std::vector<GLfloat>& shadow,float radius, unsigned int rings, unsigned int sectors) :
      shadow(shadow),
 radius(radius),
  rings(rings),
    sectors(sectors)
  {
    float const R = 1. / (float)(rings - 1);
    float const S = 1. / (float)(sectors - 1);
    int r, s;


   glm::vec3 light(0,-200,0);

    vertices.resize(rings * sectors * 3);
    normals.resize(rings * sectors * 3);
    texcoords.resize(rings * sectors * 2);
    std::vector<GLfloat>::iterator v = vertices.begin();
    std::vector<GLfloat>::iterator n = normals.begin();
    std::vector<GLfloat>::iterator t = texcoords.begin();
    for (r = 0; r < rings; r++)
      for (s = 0; s < sectors; s++) {
        float const y = sin(-M_PI_2 + M_PI * r * R);
        float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
        float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

        *t++ = s * S;
        *t++ = r * R;

        *v++ = x * radius;
        *v++ = y * radius;
        *v++ = z * radius;

        *n++ = x;
        *n++ = y;
        *n++ = z;
      }

    indices.resize(rings * sectors * 4);
    std::vector<GLushort>::iterator i = indices.begin();
    for (r = 0; r < rings - 1; r++)
      for (s = 0; s < sectors - 1; s++) {
        *i++ = r * sectors + s;
        *i++ = r * sectors + (s + 1);
        *i++ = (r + 1) * sectors + (s + 1);
        *i++ = (r + 1) * sectors + s;
      }


  }

  void draw(GLfloat x, GLfloat y, GLfloat z) {

    glTranslatef(x, y, z);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normals[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
    glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    std::vector<bool> visibleface;
   glm::vec3 light(0,-200,0);
for(auto it =vertices.begin();it!=vertices.end();it+=3){

       glm::vec3 pos(*(it),*(it+1),*(it+2));
       glm::vec3 lightvec= light - pos;
       if(glm::dot(lightvec,pos/radius) <0){
           visibleface.push_back(true);
       }
       else{
           visibleface.push_back(false);
       }
}

    {
    int a =0;

        auto it = vertices.begin();
        CircularAccess ca(visibleface);
        for(int i = 0; i<visibleface.size();++i,it+=3){
           if(ca[i-1]!=ca[i] ||ca[i+1]!=ca[i] ||ca[i-sectors]!=ca[i] ||ca[i+sectors]!=ca[i] ){
              shadow.push_back(*(it));
              shadow.push_back(*(it+1));
              shadow.push_back(*(it+2));
    }
        }
}
/*
for(auto it = shadowvec.begin()+3;it!=shadowvec.end();it+=3){
std::array<GLfloat,12> shadow{
    *(it-3),*(it-2),*(it-1),
    *(it),*(it+1),*(it+2),
    *(it)-light.x,*(it+1)-light.y,*(it+2)-light.z,
    *(it-3)-light.x,*(it-2)-light.y,*(it-1)-light.z};
}
*/
  }
};

#endif
