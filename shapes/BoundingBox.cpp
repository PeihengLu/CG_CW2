/*
 * BoundingBox.h
 *
 *
 */

#include "shapes/BoundingBox.h"

namespace rt{

BoundingBox::BoundingBox(const Vec3f min_point, const Vec3f max_point) {
    this->min_point = min_point;
    this->max_point = max_point;
}

// cheap intersection function
bool BoundingBox::intersect(Vec3f rayOrigin, Vec3f rayDirection) const {
    float tx1 = (min_point.x - rayOrigin.x) / rayDirection.x;
    float tx2 = (max_point.x - rayOrigin.x) / rayDirection.x;
    float ty1 = (min_point.y - rayOrigin.y) / rayDirection.y;
    float ty2 = (max_point.y - rayOrigin.y) / rayDirection.y;
    float tz1 = (min_point.z - rayOrigin.z) / rayDirection.z;
    float tz2 = (max_point.z - rayOrigin.z) / rayDirection.z;

    float tmin = std::max(std::max(std::min(tx1, tx2), std::min(ty1, ty2)), std::min(tz1, tz2));
    float tmax = std::min(std::min(std::max(tx1, tx2), std::max(ty1, ty2)), std::max(tz1, tz2));

    return tmax >= tmin && tmax >= 0;
}

BoundingBox* BoundingBox::extend_bounding_box(BoundingBox* box) {
    std::vector<BoundingBox*> boxes;
    boxes.push_back(this);
    boxes.push_back(box);
    return merge_bounding_box(boxes);
}




BoundingBox* merge_bounding_box(const std::vector<BoundingBox*>& boxes) {
    Vec3f min_point(1000000.0f);
    Vec3f max_point(-1000000.0f);
    for (const auto& box : boxes) {
        min_point.x = std::min(min_point.x, box->min_point.x);
        max_point.x = std::max(max_point.x, box->max_point.x);
        min_point.y = std::min(min_point.x, box->min_point.y);
        max_point.y = std::max(max_point.x, box->max_point.y);
        min_point.z = std::min(min_point.x, box->min_point.z);
        max_point.z = std::max(max_point.x, box->max_point.z);
    }
    return new BoundingBox(min_point, max_point);
}
}

