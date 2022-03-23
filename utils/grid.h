//
// Created by germanzvezdin on 22.03.2022.
//
#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <ostream>
#include <fstream>

enum class translateDirection { LEFT = -1, STUB = 0, RIGHT = 1 };

class TranslationVectors {
    std::vector<double> _f;
    translateDirection _translationDirection;
    int _offset = 0;
public:
    TranslationVectors();
    TranslationVectors(std::vector<double> & initialData, translateDirection mode);
    bool stream();
    double operator[](int i)const;
    double & operator[](int i);
    friend std::ostream& operator<<(std::ostream& out, TranslationVectors& data);
};

class Grid {
    std::array<TranslationVectors, 3> _grid;
    int _size;
    std::vector<double> _rho;
    std::vector<double> _u;
public:
    Grid(std::array<TranslationVectors, 3> inputData, int size);
    bool streamStep();
    bool collisionStep();
    std::array<double, 3> operator[](int i);
    friend std::ostream& operator<<(std::ostream & out, Grid & grid);
    bool dump();
};
