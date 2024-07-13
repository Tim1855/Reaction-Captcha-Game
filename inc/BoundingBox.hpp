#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <vector>
#include <string>
#include <map>

class BoundingBox {
public:
    struct Box {
        int m_x, m_y, m_width, m_height;
        std::string m_label;
    };

    // Constructor
    BoundingBox();

    // Destructor
    ~BoundingBox();

    // Load bounding boxes from a file
    void loadBoundingBoxes(const std::string& filePath);

    // Check if bounding boxes were loaded successfully
    bool areLoaded() const;

    // Verify the loaded bounding boxes and handle errors
    void checkLoad() const;

    // Get the loaded bounding boxes for a specific frame
    const std::vector<Box>& getBoundingBoxes(int frame) const;

private:
    std::map<int, std::vector<Box>> m_boundingBoxes;
    bool m_loaded;
};

#endif // BOUNDINGBOX_HPP
