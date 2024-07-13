#include "BoundingBox.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor
BoundingBox::BoundingBox() : m_loaded(false) {}

// Destructor
BoundingBox::~BoundingBox() {}

void BoundingBox::loadBoundingBoxes(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        m_loaded = false;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int frame, track_id;
        std::string object_type;
        float truncation, occlusion, alpha, bbox_left, bbox_top, bbox_right, bbox_bottom, dimensions_x, dimensions_y, dimensions_z, location_x, location_y, location_z, rotation_y;
        if (!(iss >> frame >> track_id >> object_type >> truncation >> occlusion >> alpha >> bbox_left >> bbox_top >> bbox_right >> bbox_bottom >> dimensions_x >> dimensions_y >> dimensions_z >> location_x >> location_y >> location_z >> rotation_y)) {
            continue;
        }
        if (object_type == "DontCare") {
            continue;
        }
        Box box;
        box.m_x = static_cast<int>(bbox_left);
        box.m_y = static_cast<int>(bbox_top);
        box.m_width = static_cast<int>(bbox_right - bbox_left);
        box.m_height = static_cast<int>(bbox_bottom - bbox_top);
        box.m_label = object_type;
        m_boundingBoxes[frame].push_back(box);
        // Debug-Ausgabe
        std::cout << "Loaded BoundingBox: Frame " << frame << " [" << box.m_x << ", " << box.m_y << ", " << box.m_width << ", " << box.m_height << "] " << box.m_label << std::endl;
    }
    m_loaded = true;
}

bool BoundingBox::areLoaded() const {
    return m_loaded;
}

void BoundingBox::checkLoad() const {
    if (!areLoaded()) {
        std::cerr << "Failed to load bounding boxes." << std::endl;
        exit(-1);
    }
}

const std::vector<BoundingBox::Box>& BoundingBox::getBoundingBoxes(int frame) const {
    static std::vector<Box> empty;
    auto it = m_boundingBoxes.find(frame);
    if (it != m_boundingBoxes.end()) {
        return it->second;
    }
    return empty;
}
