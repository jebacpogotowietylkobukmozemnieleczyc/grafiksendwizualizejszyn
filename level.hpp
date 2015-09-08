#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <functional>
#include <vector>
class Level {
public:
  Level(int t, float startx, float startz, float endx, float endz, float divx,
        float divz);

  void DrawLevel();
  const auto& getVec() const { return vec; }
  auto getDivx() { return divx; }
  auto getDivz() { return divz; }
  void ToggleDebug() {
    if (debugnormal == true)
      debugnormal = false;
    else
      debugnormal = true;
  }

private:
  float startx = -20;
  float startz = -20;
  float endx = 20;
  float endz = 20;
  float divx = 16;
  float divz = 16;
  int t = 2;
  bool debugnormal;
  std::vector<float> vec;
  std::vector<unsigned int> vecind;
  std::vector<float> texcoord;
  std::vector<float> vecnorm;
};

#endif // LEVEL_HPP
