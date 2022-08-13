#pragma once

class QItem {
public:
    int row;
    int colm;
    int dist;
    QItem(int x, int y, int w)
        : row(x), colm(y), dist(w) {}
};