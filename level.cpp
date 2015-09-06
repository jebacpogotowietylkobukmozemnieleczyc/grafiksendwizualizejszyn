#include <GL/gl.h>
#include <GL/glut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "level.hpp"
#include "iostream"

    Level::Level(std::function<void()> mfunction,
          int t,
          float startx,
          float startz,
          float endx,
          float endz,
          float divx,
          float divz) :
        t(t),
        startx(startx),
        startz(startz),
        endx(endx),
        endz(endz),
        divx(divx),
        divz(divz)
    {

int v =0;
float stepx = (endx - startx) / divx;
float stepz = (endz - startz) / divz;
    for (int i = 0; i <= divz; ++i) {
        for (int j = 0; j <= divx; ++j) {
           int x =startx + j*stepx;
           int z =startz + i * stepz;
           vec.push_back(x);
           vec.push_back(t*(cos(glm::radians(static_cast<float>(x*15)))+sin(glm::radians(static_cast<float>(z*15))))-2.0);
           //vec.push_back(t*(cos(degtrad(x*15))+sin(degtrad(z*15))));
           vec.push_back(z);
           std::cout <<  x<< ' ' << -1  << ' ' << z<< std::endl;

           if(i<divz && j < divx){
           vecind.push_back(v);
           vecind.push_back(v+divx+1);
           vecind.push_back(v+divx+2);
           vecind.push_back(v+1);
           std::cout <<  v<< "www" << v+divx+1  << ' ' << v+divx+2<< ' ' << v+1 << std::endl;
           }

           veccolor.push_back(0);
           veccolor.push_back(0);
           veccolor.push_back(1);
           ++v;
        }
    }

    std::cout << "^^start";
for(auto it  = getVec().begin(); it != getVec().end(); ++it) {
    std::cout << *it << " ";
}
    }

    void Level::DrawLevel(){

        std::vector<float> inverse;
        for(auto it = vec.begin();it!=vec.end();++it){
            inverse.push_back( -(*(it)) );
        }
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3,GL_FLOAT,0,vec.data());
    glColorPointer(3,GL_FLOAT,0,veccolor.data());

    glDrawElements(GL_QUADS,vecind.size(),GL_UNSIGNED_INT,vecind.data());
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    }
