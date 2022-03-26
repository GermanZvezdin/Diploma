#include <iostream>
#include <grid.h>

int main() {
    Grid grid(100);
    grid.init();
    for (int i = 0; i < 10; i++) {
        grid.streamStep();
        grid.collisionStep();
        if (i % 3 == 0) {
            grid.pushCurrentData();
        }
    }
    std::cout << grid;
    grid.dump();
    return 0;
}
