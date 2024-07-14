#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <string>

class BoundingBox {
public:
    BoundingBox(int x1, int y1, int x2, int y2);

    int getX1() const { return m_x1; }
    int getY1() const { return m_y1; }
    int getX2() const { return m_x2; }
    int getY2() const { return m_y2; }

    // Other getters
    int getTrackId() const { return m_trackId; }
    const std::string& getType() const { return m_type; }
    float getTruncated() const { return m_truncated; }
    int getOccluded() const { return m_occluded; }
    float getAlpha() const { return m_alpha; }
    float getHeight() const { return m_height; }
    float getWidth() const { return m_width; }
    float getLength() const { return m_length; }
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getZ() const { return m_z; }
    float getRotationY() const { return m_rotationY; }

private:
    int m_x1, m_y1, m_x2, m_y2;
    int m_trackId;
    std::string m_type;
    float m_truncated;
    int m_occluded;
    float m_alpha;
    float m_height, m_width, m_length;
    float m_x, m_y, m_z;
    float m_rotationY;
};

#endif // BOUNDINGBOX_HPP
