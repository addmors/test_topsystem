#pragma once
#include <glm/glm.hpp>

struct Point {
    glm::vec3 position;
    glm::vec3 normal;
};

static std::istream& operator >> (std::istream& in, Point& point)
{
    std::string name;
    unsigned age;
    in >> point.position.x >> point.position.y >> point.position.z;
    in >> point.normal.x >> point.normal.y >> point.normal.z;
    float last_param;
    in >> last_param;
    return in;
}