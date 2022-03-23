#include <iostream>
#include <grid.h>

int main() {
    std::vector<double> dataLeft = {1, 0, 0, 0, 0, 0, 1};
    std::vector<double> dataStub = {0, 0, 0, 2, 0, 0, 0};
    std::vector<double> dataRight ={3, 0, 0, 0, 0, 0, 3};

    TranslationVectors L(dataLeft, translateDirection::LEFT), S(dataStub, translateDirection::STUB), R(dataRight, translateDirection::RIGHT);
    std::array<TranslationVectors, 3> f = {L, S, R};
    Grid grid(f, dataLeft.size());

    for (int i = 0; i < 30; i++) {

        grid.collisionStep();
        grid.streamStep();

    }
    std::cout << grid;
    std::cout << std::endl;
    grid.dump();
    return 0;
}
