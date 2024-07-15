#include "BoundingBox.hpp"

BoundingBox::BoundingBox(int x1, int y1, int x2, int y2)
    : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2) {}

int BoundingBox::getX1() const { return m_x1; }
int BoundingBox::getY1() const { return m_y1; }
int BoundingBox::getX2() const { return m_x2; }
int BoundingBox::getY2() const { return m_y2; }