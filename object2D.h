#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSq(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill=false);
    Mesh* CreateTurret(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
    Mesh* CreateEnemy(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
    Mesh* CreateStar(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
}
