#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSq(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(leftBottomCorner, color),
        VertexFormat(leftBottomCorner + glm::vec3(length, 0, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(length, length, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateTurret(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(leftBottomCorner + glm::vec3(length/2, length/6, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(2*length / 3, length / 2, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(length / 2, 5 * length / 6, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(length / 3,length / 2, 0), color),
        //romb

        VertexFormat(leftBottomCorner + glm::vec3(length/2, 5*length/12, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(11*length/12, 5 * length / 12, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(11*length/12, 7*length / 12, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(length/2, 7 * length / 12, 0), color),
        //tun
    };
    Mesh* turret = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 2,
        0,2,3,
        //romb
        4,5,6,
        4,6,7
        //tun
    };

    turret->InitFromData(vertices, indices);
    return turret;
}

Mesh* object2D::CreateEnemy(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color)
{
    float inLength = 2* length / 3;
    glm::vec3 inColor(1.f/5.f, 2.f/3.f, 2.f / 3.f);
    float inSpace = (length - inLength) / 2;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(leftBottomCorner + glm::vec3(4*length/15, 4 * length / 15, -1), color),
        VertexFormat(leftBottomCorner + glm::vec3(7*length/12, 7 * length / 40, -1), color),
        VertexFormat(leftBottomCorner + glm::vec3(33*length/40, 5*length/12, -1), color),
        VertexFormat(leftBottomCorner + glm::vec3(11 * length / 15, 11*length/15, -1), color),
        VertexFormat(leftBottomCorner + glm::vec3(5 * length / 12, 33 * length / 40, -1), color),
        VertexFormat(leftBottomCorner + glm::vec3(7 * length / 40, 7 * length / 12, -1), color),
        //outer hex

        VertexFormat(leftBottomCorner + glm::vec3(4 * inLength / 15+inSpace, 4 * inLength / 15+inSpace, 0), inColor),
        VertexFormat(leftBottomCorner + glm::vec3(7 * inLength / 12+inSpace, 7 * inLength / 40+inSpace, 0), inColor),
        VertexFormat(leftBottomCorner + glm::vec3(33 * inLength / 40+inSpace, 5 * inLength / 12+inSpace, 0), inColor),
        VertexFormat(leftBottomCorner + glm::vec3(11 * inLength / 15+inSpace, 11 * inLength / 15+inSpace, 0), inColor),
        VertexFormat(leftBottomCorner + glm::vec3(5 * inLength / 12+inSpace, 33 * inLength / 40+inSpace, 0), inColor),
        VertexFormat(leftBottomCorner + glm::vec3(7 * inLength / 40+inSpace, 7 * inLength / 12+inSpace, 0), inColor),
        //inner hex
    };

    Mesh* hex = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,4,5,
        0,3,4,
        0,1,3,
        1,2,3,
        //outer hex
        6,10,11,
        6,9,10,
        6,7,9,
        7,8,9
        //inner hex
    };

    hex->InitFromData(vertices, indices);
    return hex;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(leftBottomCorner + glm::vec3(22.05*length / 120, 72.65*length / 120, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(3*length / 10, 7*length / 30, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(7*length / 10, 7 * length / 30, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(97.95*length / 120,72.65*length / 120, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(length / 2, 5*length / 6, 0), color),
        //colturi

        VertexFormat(leftBottomCorner + glm::vec3(45.3*length / 120, 55.89*length / 120, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(length / 2, 45.3*length / 120, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(74.7*length / 120, 55.89*length / 120, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(69.12*length / 120, 72.65*length / 120, 0), color),
        VertexFormat(leftBottomCorner + glm::vec3(50.88*length / 120, 72.65 * length / 120, 0), color)
        //intersectii
    };
    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 6, 3,
        1,6,5,
        2,7,6,
        4,9,8
    };

    star->InitFromData(vertices, indices);
    return star;
}