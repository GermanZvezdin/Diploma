//
// Created by germanzvezdin on 22.03.2022.
//
#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <ostream>

enum class translateDirection { LEFT = 0, STUB = 1, RIGHT = 2 };

struct MarkedList {
    translateDirection _listType;
    std::list<double> _data;
    MarkedList(): _listType(translateDirection::STUB) {};
    MarkedList(translateDirection type): _listType(type) {};
    void stream();
};

struct GridInputData {
    std::vector<double> _dataLeft;
    std::vector<double> _dataStub;
    std::vector<double> _dataRight;
};

class Grid {
    std::array<MarkedList, 3> _g;
    int _size;
public:
    Grid(GridInputData & data);
    void StreamStep();
    friend std::ostream& operator<<(std::ostream & out, Grid & grid);
};
