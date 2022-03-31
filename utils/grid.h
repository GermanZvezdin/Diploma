//
// Created by germanzvezdin on 22.03.2022.
//
#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <ostream>
#include <fstream>
#include <cmath>

enum class translateDirection { LEFT = -1, STUB = 0, RIGHT = 1 };

class TranslationVectors {
    std::vector<double> _f;
    translateDirection _translationDirection;
    int _offset = 0;
public:
    TranslationVectors();
    TranslationVectors(int size, translateDirection mode);
    bool stream();
    bool init(translateDirection type, int size);
    bool resize(int newSize);
    double operator[](int i)const;
    double & operator[](int i);
    friend std::ostream& operator<<(std::ostream& out, TranslationVectors& data);
};

class Grid {
    std::vector<TranslationVectors> _grid;
    int _size;
    std::vector<double> _rhoData;
    std::vector<double> _u;
    const double _tau; // 0.5+..1.0
    const double _inverseTau;
    std::array<double, 3> _w = {1.0 / 6.0, 2.0 / 3.0, 1.0 / 6.0};
public:
    Grid(int size, double tau);
    bool streamStep();
    bool collisionStep();
    bool forceStep(double t);
    bool init();
    std::array<double, 3> operator[](int i);
    friend std::ostream& operator<<(std::ostream & out, Grid & grid);
    bool dump();
    bool pushCurrentData();
};
