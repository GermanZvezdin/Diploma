#include <iostream>
#include <grid.h>

int main() {
    std::vector<double> left = {0, 0, 0, 0, 1};
    std::vector<double> stub = {0, 0, 5, 0, 0};
    std::vector<double> right = {0, 0, 0, 0, 2};

    GridInputData input;
    input._dataLeft = left;
    input._dataStub = stub;
    input._dataRight = right;

    Grid g(input);

    for(int i = 0; i < 10; i++) {
        std::cout << g << std::endl;
        g.StreamStep();
    }
}
