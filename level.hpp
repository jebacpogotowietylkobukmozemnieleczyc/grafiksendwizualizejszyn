#ifndef LEVEL_HPP
#define LEVEL_HPP
#include<functional>
#include<vector>
class Level
{
public:
    Level(std::function<void()> mfunction,
          int t,
          float startx,
          float startz,
          float endx,
          float endz,
          float divx,
          float divz) ;


    void DrawLevel();
    const std::vector<float>& getVec() const{return vec;}
    auto getDivx() {return divx;}
    auto getDivz() {return divz;}
private:
float startx = -20;
float startz = -20;
float endx =20;
float endz =20;
float divx = 16;
float divz = 16;
int t =2;
std::vector<float> vec;
std::vector<unsigned int > vecind;
std::vector<float> veccolor;
    std::function<void()> mfunction;
};

#endif // LEVEL_HPP
