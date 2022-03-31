//
// Created by germanzvezdin on 22.03.2022.
//

#include "grid.h"

TranslationVectors::TranslationVectors() {
    _translationDirection = translateDirection::STUB;
    _offset = 0;
}

TranslationVectors::TranslationVectors(int size, translateDirection mode): _translationDirection(mode) {
    _f.resize(size);
};

bool TranslationVectors::stream() {
    _offset++;
    return false;
}

bool TranslationVectors::resize(int newSize) {
    _f.resize(newSize);
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

bool TranslationVectors::init(translateDirection type, int size) {
    _f.resize(size);
    _translationDirection = type;
    return false;
}

std::ostream& operator<<(std::ostream& out, TranslationVectors& data) {
    for(int i = 0; i < data._f.size(); i++) {
        out << data[i] << " ";
    }
    out << std::endl;
    return out;
}

Grid::Grid(int size, double tau): _size(size), _tau(tau), _inverseTau(1.0 / _tau) {
    for(int i = static_cast<int>(translateDirection::LEFT); i <= static_cast<int>(translateDirection::RIGHT); i++) {
        TranslationVectors f(size, static_cast<translateDirection>(i));
        _grid.push_back(f);
    }
};

bool Grid::streamStep() {
    for (auto& it : _grid) {
        it.stream();
    }
    return false;
}

std::array<double, 3> Grid::operator[](int i) {
    return std::array<double, 3>{_grid[0][i], _grid[1][i], _grid[2][i]};
}

bool Grid::forceStep(double t) {
    double F = sin(t * 0.1);
    for (int i = 0; i < _size; i++) {
        auto curF = this->operator[](i);
        double rho = curF[0] + curF[1] + curF[2];
        double u = (curF[2] - curF[0]) / rho;
        double a = F / rho;
        double deltaU = a * 1.0f;
        std::array<double, 3> deltaFq;
        deltaFq[0] = _w[0] * rho * ((3.0 * (-1.0 - u) + 9.0 * u) * deltaU + (4.5 * deltaU * deltaU - 1.5 * deltaU * deltaU));
        deltaFq[1] = _w[1] * rho * (3.0 * (-u) * deltaU - 1.5 * deltaU * deltaU);
        deltaFq[2] = _w[2] * rho * ((3.0 * (1.0 - u) + 9.0 * u) * deltaU + (4.5 * deltaU * deltaU - 1.5 * deltaU * deltaU));

        for (int j = 0; j < 3; j++) {
            _grid[j][i] = curF[j] + deltaFq[j];
        }
    }

    return false;
}

bool Grid::collisionStep() {
    for (int i = 0; i < _size; i++) {
        auto curF = this->operator[](i);
        double rho = curF[0] + curF[1] + curF[2];
        double u = (curF[2] - curF[0]) / rho;
        std::array<double, 3> feq;
        feq[0] = _w[0] * rho * (1.0 - 3.0 * u + 4.5 * u * u - 1.5 * u * u);
        feq[1] = _w[1] * rho * (1.0 - 1.5 * u * u);
        feq[2] = _w[2] * rho * (1.0 + 3.0 * u + 4.5 * u * u - 1.5 * u * u);

        for (int j = 0; j < 3; j++) {
            _grid[j][i] = curF[j] - _inverseTau * (curF[j] - feq[j]);
        }
    }

    return false;

}

std::ostream& operator<<(std::ostream & out, Grid & grid) {
    for (int i = 0; i < grid._size; i++) {
        double rho = 0.0;
        for (auto it : grid._grid) {
            out << it[i] << " ";
            rho += it[i];
        }
        out << rho << std::endl;
    }
    return out;
}

bool Grid::dump() {
    std::ofstream rho;
    rho.open("./rho.txt");
    for(int i = 0; i < _rhoData.size(); i++) {
        rho << _rhoData[i] << std::endl;
    }
    rho.close();
    /*
    std::ofstream v;
    v.open("./v.txt");
    for(int i = 0; i < _u.size(); i++) {
        v << _u[i] << std::endl;
    }
    v.close();
     */
    return false;

}

bool Grid::init() {
    for (int i = 0; i < _size; i++) {
        double rho = (i > (_size / 2)) ? 1.001 : 1.0;
        double u = 0.0;
        std::array<double, 3> feq;
        feq[0] = _w[0] * rho * (1.0 - 3.0 * u + 4.5 * u * u - 1.5 * u * u);
        feq[1] = _w[1] * rho * (1.0 - 1.5 * u * u);
        feq[2] = _w[2] * rho * (1.0 + 3.0 * u + 4.5 * u * u - 1.5 * u * u);
        auto directionVectorsCount = static_cast<int>(translateDirection::RIGHT) - static_cast<int>(translateDirection::LEFT) + 1;
        for (int j = 0; j < directionVectorsCount; j++) {
            _grid[j][i] = feq[j];
        }
    }
    return false;
}

bool Grid::pushCurrentData() {
    for (int i = 0; i < _size; i++) {
        double rho = 0.0;
        for (auto it : _grid) {
            rho += it[i];
        }
        _rhoData.push_back(rho);
    }
}
