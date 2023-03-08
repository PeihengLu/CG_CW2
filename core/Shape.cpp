/*
 * Shape.cpp
 *
 */
#pragma 1

#include "Shape.h"


namespace rt{

    Shape::Shape():material(nullptr), textured(false), texture_height(0), texture_width(0){}
	Shape::Shape(Material* material, ShapeType type):material(material), textured(false), texture_height(0), texture_width(0), shapeType(type), textures(new Vec3f[texture_width * texture_height]){}
	Shape::Shape(Material* material, ShapeType type, int const texture_width, int const texture_height, Vec3f* textures):material(material), textured(true), texture_height(texture_height), texture_width(texture_width), shapeType(type), textures(textures){}

    // to be overwritten
    Vec3f Shape::getTexture(Vec3f intersection) {
        return Vec3f();
    }

    // to be overwritten
    BoundingBox* Shape::getBoundingBox() {
        return new BoundingBox(Vec3f(), Vec3f());
    }

    float pointToLineDist(Vec3f point, Vec3f v0, Vec3f v1){
        Vec3f ab = v1 - v0;
        Vec3f ap = point - v0;
        float proj = ap.dotProduct(ab) / ab.dotProduct(ab);
        Vec3f q = v0 + proj * ab;
        // std::cout<<"proj ray direction: <"<<std::to_string(q.x)<<"," <<std::to_string(q.y) <<"," <<std::to_string(q.z) << ">\n";
        float distance = (point - q).length();
        return distance;
    }

    BoundingBox* compute_bounding_box(const std::vector<Shape*>& shapes){
        BoundingBox* bbox = nullptr;
        
        for (auto shape: shapes) {
            if (bbox == nullptr) {
                bbox = shape->getBoundingBox();
            } else {
                bbox = bbox->extend_bounding_box(shape->getBoundingBox());
            }
        }

        return bbox;
    }

} //namespace rt

