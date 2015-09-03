#include "app.hpp"

int main(int argc, char* argv[]) {
    app = new App(&argc,argv);
    glutMainLoop();
    delete app;
    return 0;
}

