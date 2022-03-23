//
// Created by germanzvezdin on 22.03.2022.
//

#include "grid.h"

TranslationVectors::TranslationVectors() {
    _translationDirection = translateDirection::STUB;
    _offset = 0;
}

TranslationVectors::TranslationVectors(std::vector<double> &initialData, translateDirection mode): _f(initialData), _translationDirection(mode) {};

bool TranslationVectors::stream() {
    _offset++;
    return false;
}

double TranslationVectors::operator[](int i) const  {
    int idx;
    int N = _f.size();
    switch (_translationDirection) {
        case translateDirection::STUB:
            idx = i;
            break;
        case translateDirection::RIGHT:
            idx = (N - i + _offset - 1) % N;
            break;
        case translateDirection::LEFT:
            idx = (i + _offset) % N;
            break;
    }
    return _f[idx];
}
double& TranslationVectors::operator[](int i) {
    int idx;
    int N = _f.size();
    switch (_translationDirection) {
        case translateDirection::STUB:
            idx = i;
            break;
        case translateDirection::RIGHT:
            idx = (N - i + _offset - 1) % N;
            break;
        case translateDirection::LEFT:
            idx = (i + _offset) % N;
            break;
    }
    return _f[idx];
}

std::ostream& operator<<(std::ostream& out, TranslationVectors& data) {
    for(int i = 0; i < data._f.size(); i++) {
        out << data[i] << " ";
    }
    out << std::endl;
    return out;
}

Grid::Grid(std::array<TranslationVectors, 3> inputData, int size): _grid(inputData), _size(size) {};

bool Grid::streamStep() {
    for (auto& it : _grid) {
        it.stream();
    }
    return false;
}

std::array<double, 3> Grid::operator[](int i) {
    return std::array<double, 3>{_grid[0][i], _grid[1][i], _grid[2][i]};
}

bool Grid::collisionStep() {
    std::array<double, 3> w = {0.25, 0.5, 0.25};
    for (int i = 0; i < _size; i++) {
        auto curF = this->operator[](i);
        double rho = curF[0] + curF[1] + curF[2];
        double u = curF[2] - curF[0];
        std::array<double, 3> feq;
        feq[0] = w[0] * rho * (1.0 - 3.0 * u + 4.5 * u * u - 1.5 * u * u);
        feq[1] = w[1] * rho * (1.0 - 1.5 * u * u);
        feq[2] = w[2] * rho * (1.0 + 3.0 * u + 4.5 * u * u - 1.5 * u * u);

        for (int j = 0; j < 3; j++) {
            _grid[j][i] = curF[j] - 0.001 * (curF[j] - feq[j]);
        }
        _rho.push_back(rho);
        _u.push_back(u);
    }

    return false;

}

std::ostream& operator<<(std::ostream & out, Grid & grid) {
    for (auto it : grid._grid) {
        for (int i = 0; i < grid._size; i++) {
            out << it[i] << " ";
        }
        out << std::endl;
    }
    return out;
}

bool Grid::dump() {
    std::ofstream rho;
    rho.open("./rho.txt");
    for(int i = 0; i < _rho.size(); i++) {
        rho << _rho[i] << std::endl;
    }
    rho.close();
    std::ofstream v;
    v.open("./v.txt");
    for(int i = 0; i < _u.size(); i++) {
        v << _u[i] << std::endl;
    }
    v.close();
    return false;

}
