//
// Created by germanzvezdin on 22.03.2022.
//

#include "grid.h"

void MarkedList::stream() {
    switch (_listType) {
        case translateDirection::LEFT:
            std::rotate(_data.begin(), std::next(_data.begin()), _data.end());
            break;
        case translateDirection::STUB:
            break;
        case translateDirection::RIGHT:
            std::rotate(_data.begin(), std::prev(_data.end()), _data.end());
            break;
    }
}

Grid::Grid(GridInputData & data) {
    _size = data._dataRight.size();
    for(auto it : data._dataLeft) {
        _g[0]._data.push_back(it);
    }
    for(auto it : data._dataStub) {
        _g[1]._data.push_back(it);
    }
    for(auto it : data._dataRight) {
        _g[2]._data.push_back(it);
    }
    _g[0]._listType = translateDirection::LEFT;
    _g[1]._listType = translateDirection::STUB;
    _g[2]._listType = translateDirection::RIGHT;
}

void Grid::StreamStep() {
    for(int i = 0; i < 3; i++) {
        _g[i].stream();
    }
}

std::ostream& operator<<(std::ostream & out, Grid & grid) {
    std::vector left(grid._g[0]._data.begin(), grid._g[0]._data.end());
    std::vector stub(grid._g[1]._data.begin(), grid._g[1]._data.end());
    std::vector right(grid._g[2]._data.begin(), grid._g[2]._data.end());

    for (int i = 0; i < grid._size; i++) {
        out << left.at(i) << " ";
    }
    out << std::endl;
    for (int i = 0; i < grid._size; i++) {
        out << stub.at(i) << " ";
    }
    out << std::endl;
    for (int i = 0; i < grid._size; i++) {
        out << right.at(i) << " ";
    }
    out << std::endl;


    return out;
}