#include <GL/gl.h>
#include <GL/glut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "level.hpp"
#include "iostream"

Level::Level(int t, float startx, float startz, float endx, float endz,
             float divx, float divz)
    : t(t),
      startx(startx),
      startz(startz),
      endx(endx),
      endz(endz),
      divx(divx),
      divz(divz),
      debugnormal(false) {

  int v = 0;
  float stepx = (endx - startx) / divx;
  float stepz = (endz - startz) / divz;
  for (int i = 0; i <= divz; ++i) {
    for (int j = 0; j <= divx; ++j) {
      int x = startx + j * stepx;
      int z = startz + i * stepz;
      vec.push_back(x);
      vec.push_back(t * (cos(glm::radians(static_cast<float>(x * 15))) +
                         sin(glm::radians(static_cast<float>(z * 15)))) -
                    2.0);
      vec.push_back(z);

      if (i < divz && j < divx) {
        vecind.push_back(v);
        vecind.push_back(v + divx + 1);
        vecind.push_back(v + divx + 2);
        vecind.push_back(v + 1);

        texcoord.push_back(0);
        texcoord.push_back(0);
        texcoord.push_back(1);
        texcoord.push_back(0);
        texcoord.push_back(1);
        texcoord.push_back(1);
        texcoord.push_back(0);
        texcoord.push_back(1);
      }

      ++v;
    }
  }
  int x = 0;
  int z = 0;
  for (auto it = vec.begin(); it != vec.end(); it += 3) {
    if (x >= divx) {
      ++z;
      x = 0;
      continue;
    }
    if (z >= divz)
      break;
    glm::vec3 vec1(*(it), *(it + 1), *(it + 2));
    glm::vec3 vec2(*(it + (3 * (divx + 1))), *(it + (3 * (divx + 1)) + 1),
                   *(it + (3 * (divx + 1)) + 2));
    glm::vec3 vec3(*(it + 3), *(it + 4), *(it + 5));
    glm::vec3 norm = glm::cross((vec2 - vec1), (vec3 - vec1));
    vecnorm.push_back(norm.x);
    vecnorm.push_back(norm.y);
    vecnorm.push_back(norm.z);
    vecnorm.push_back(norm.x);
    vecnorm.push_back(norm.y);
    vecnorm.push_back(norm.z);
    vecnorm.push_back(norm.x);
    vecnorm.push_back(norm.y);
    vecnorm.push_back(norm.z);
    vecnorm.push_back(norm.x);
    vecnorm.push_back(norm.y);
    vecnorm.push_back(norm.z);
    ++x;
 }
}

void Level::DrawLevel() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vec.data());
  glNormalPointer(GL_FLOAT, 0, vecnorm.data());
  glTexCoordPointer(2, GL_FLOAT, 0, texcoord.data());

  glDrawElements(GL_QUADS, vecind.size(), GL_UNSIGNED_INT, vecind.data());
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  if (debugnormal == false)
    return;
  auto it2 = vecnorm.begin();
  float m = 1.f;
  int x = 0;
  int z = 0;
  for (auto it = vec.begin(); it != vec.end(); it += 3) {
    if (x >= divx) {
      ++z;
      x = 0;
      continue;
    }
    if (z >= divz)
      break;
    glBegin(GL_LINES);
    glVertex3f(*(it), *(it + 1), *(it + 2));
    glVertex3f(*(it)+m * (*(it2)), *(it + 1) + m * (*(it2 + 1)),
               *(it + 2) + m * (*(it2 + 2)));
    glEnd();
    it2 += 3;
    glBegin(GL_LINES);
    glVertex3f(*(it + (3 * (divx + 1))), *(it + (3 * (divx + 1)) + 1),
               *(it + (3 * (divx + 1)) + 2));
    glVertex3f((*(it + (3 * (divx + 1)))) + m * (*(it2)),
               (*(it + (3 * (divx + 1))) + 1) + m * (*(it2 + 1)),
               (*(it + (3 * (divx + 1))) + 2) + m * (*(it2 + 2)));
    glEnd();
    it2 += 3;
    glBegin(GL_LINES);
    glVertex3f(*(it + (3 * (divx + 1)) + 3), *(it + (3 * (divx + 1)) + 4),
               *(it + (3 * (divx + 1)) + 5));
    glVertex3f(*(it + (3 * (divx + 1)) + 3) + m * (*(it2)),
               *(it + (3 * (divx + 1)) + 4) + m * (*(it2 + 1)),
               *(it + (3 * (divx + 1)) + 5) + m * (*(it2 + 2)));
    glEnd();
    it2 += 3;
    glBegin(GL_LINES);
    glVertex3f(*(it + 3), *(it + 4), *(it + 5));
    glVertex3f(*(it + 3) + m * (*(it2)), *(it + 4) + m * (*(it2 + 1)),
               *(it + 5) + m * (*(it2 + 2)));
    glEnd();
    it2 += 3;
    ++x;
  }
}
