#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

class BoundingBox {
public:
    BoundingBox(int x1, int y1, int x2, int y2);
    virtual ~BoundingBox();
    int getX1() const;
    int getY1() const;
    int getX2() const;
    int getY2() const;

private:
    int m_x1, m_y1, m_x2, m_y2;
};

#endif // BOUNDINGBOX_HPP
