#include <iostream>
#include <grid.h>

int main() {
    Grid grid(100, 1.51);
    grid.init();
    for (int i = 0; i < 1000; i++) {
        grid.forceStep(i);
        grid.collisionStep();
        grid.streamStep();
        grid.pushCurrentData();
    }
    std::cout << grid;
    grid.dump();
    return 0;
}
