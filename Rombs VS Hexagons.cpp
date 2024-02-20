#include "lab_m1/Rombs VS Hexagons/Rombs VS Hexagons.h"

#include <vector>
#include <iostream>
#include <cstdlib>

#include "lab_m1/Rombs VS Hexagons/object2D.h"
#include "lab_m1/Rombs VS Hexagons/transform2D.h"
#include "lab_m1/Rombs VS Hexagons/functions.h"

using namespace std;
using namespace m1;


R_VS_H::R_VS_H()
{
}


R_VS_H::~R_VS_H()
{
}


void R_VS_H::Init()
{
    srand((unsigned)time(NULL));

    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, resolution.x, 0, resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 120;

    cx = corner.x + squareSide / 2;
    cy= corner.y + squareSide / 2;

    mouseTurret = 0;
    bank = 5;
    lifePoints = 3;
    runTime = 0;

    reloadTime = glm::mat3(0);

    std::vector<glm::vec3> colors = {
        glm::vec3(1,(float)25 / 51,0),
        glm::vec3(0,0,1),
        glm::vec3(1,1,0),
        glm::vec3((float)30 / 51,0,1)
    };
    //Color Vector: Orange,Blue,Yellow,Purple

    vector<Mesh*> turrets;
    string tur = "turret";
    vector<Mesh*> enemies;
    string en = "enemy";
    vector<Mesh*> projectiles;
    string proj = "projectile";

    grid = glm::mat3(0);

    for (int i = 0;i <= 3;i++) {
        turrets.push_back(object2D::CreateTurret(tur + to_string(i+1), corner, squareSide, colors[i]));

        enemies.push_back(object2D::CreateEnemy(en+to_string(i + 1), corner, squareSide, colors[i]));

        projectiles.push_back(object2D::CreateStar(proj+to_string(i + 1), corner + glm::vec3(0, 0, 1), squareSide, colors[i]));

    }

    for (int i = 0;i <= 3;i++) {
        AddMeshToList(turrets[i]);
        AddMeshToList(enemies[i]);
        AddMeshToList(projectiles[i]);
    }

    Mesh* lifebar = object2D::CreateSq("lifebar", corner, squareSide, glm::vec3(1, 0, 0),true);
    AddMeshToList(lifebar);

    Mesh* outline = object2D::CreateSq("outline", corner, squareSide, glm::vec3(0, 0, 0));
    AddMeshToList(outline);

    Mesh* tile = object2D::CreateSq("tile", corner + glm::vec3(0, 0, -1), squareSide, glm::vec3(0, 1, 0),true);
    AddMeshToList(tile);

    Mesh* costStar = object2D::CreateStar("costStar", corner, squareSide/2, glm::vec3((float)11/17, (float)11 / 17, (float)11 / 17));
    AddMeshToList(costStar);

    Mesh* clickStar = object2D::CreateStar("clickStar", corner, squareSide, glm::vec3(1, 0, (float)4/5));
    AddMeshToList(clickStar);

}


void R_VS_H::FrameStart()
{
    glClearColor(0.20f, 0.20f, 0.20f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    resolution = window->GetResolution();

    shapeDifX = max(0.f, resolution.x - 16.f * min(resolution.y,720.f) / 9.f);
    shapeDifY = max(0.f, resolution.y - 9.f * min(resolution.x,1280.f) / 16.f);

    allignDifX = 1280.f / resolution.x + shapeDifX / (resolution.x - shapeDifX);
    allignDifY = 720.f / resolution.y + shapeDifY / (resolution.y - shapeDifY);

    glViewport(shapeDifX/2, shapeDifY/2, resolution.x-shapeDifX, resolution.y-shapeDifY);  //Maintains 1280:720 game scene
}


void R_VS_H::Update(float deltaTimeSeconds)
{
    string tur = "turret";
    string en = "enemy";
    string proj = "projectile";
    //Colored objects strings

    for (int i = 0;i < enemyDrones.size();i++) {
        if(enemyDrones[i].x == 0) {
            lifePoints--;
            enemyDrones.erase(enemyDrones.begin() + i);
            i--;
            continue;
        }
        if (enemyDrones[i].w != 0) {
            for (int j = 0;j < 3;j++) {
                if (grid[enemyDrones[i].y][j] != 0) {
                    if (enemyDrones[i].x <= 580 && fmod(grid[enemyDrones[i].y][j], 1.0) == 0) {
                        if (fun::Collision2D(120 + 160 * j + cx, 0, enemyDrones[i].x + cx, 0, 80))
                            grid[enemyDrones[i].y][j] += 0.9;
                    } //Check collision turrets
                    if (grid[enemyDrones[i].y][j] == enemyDrones[i].z && 280 + 160 * j < enemyDrones[i].x) {
                        if (reloadTime[enemyDrones[i].y][j] == 0) {
                            allyProjectile.push_back(glm::vec4(200 + 160 * j, (int)enemyDrones[i].y, (int)enemyDrones[i].z, 0.f));
                            reloadTime[enemyDrones[i].y][j] = 107;
                        }
                        else
                            reloadTime[enemyDrones[i].y][j] -= 1;
                    } //Generate projectiles
                }
            }

            for (int j = 0;j < allyProjectile.size();j++) {
                if (enemyDrones[i].y == allyProjectile[j].y && enemyDrones[i].z == allyProjectile[j].z)
                    if (fun::Collision2D(enemyDrones[i].x + cx, 0, allyProjectile[j].x + cx, 0, 80)) {
                        enemyDrones[i].w -= 1;
                        allyProjectile.erase(allyProjectile.begin() + j);
                        if (enemyDrones[i].w == 0)
                            enemyDrones[i].z += 0.9;
                        break;
                    }
            } //Check collision projectiles
        }

        if (enemyDrones[i].z == 0) {
            enemyDrones.erase(enemyDrones.begin() + i);
            i--;
        }
        else{
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(enemyDrones[i].x, 340 - 160 * enemyDrones[i].y);
            if (fmod(enemyDrones[i].z, 1.0) != 0)
                modelMatrix *= fun::Fade(enemyDrones[i].z, cx, cy);
            else
                enemyDrones[i].x -= 1;
            RenderMesh2D(meshes[en + to_string((int)enemyDrones[i].z)], shaders["VertexColor"], modelMatrix);
        } //Render hexagons
    } //Enemy hexagons

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(20, 20);
    modelMatrix *= transform2D::Scale(0.5f, (float)11/3);
    RenderMesh2D(meshes["lifebar"], shaders["VertexColor"], modelMatrix);
    //Red bar render

    if (mouseTurret != 0) {
        glm::ivec2 mousecoords = window->GetCursorPosition();
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate((mousecoords.x - shapeDifX / 2.f) * allignDifX - cx, (-mousecoords.y + resolution.y - shapeDifY / 2.f) * allignDifY - cy);
        RenderMesh2D(meshes[tur + to_string(mouseTurret)], shaders["VertexColor"], modelMatrix);
    }  //Picked up turret render

    for (int i = 0;i < 3;i++)
        for (int j = 0;j < 3;j++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(120 + 160 * j, 340 - 160 * i);
            RenderMesh2D(meshes["tile"], shaders["VertexColor"], modelMatrix);
            if (grid[i][j] != 0) {
                if (fmod(grid[i][j], 1.0) != 0) {
                    modelMatrix *= fun::Fade(grid[i][j], cx, cy);
                }
                RenderMesh2D(meshes[tur + to_string((int)grid[i][j])], shaders["VertexColor"], modelMatrix);
            }
        }
    //Turret render

    for (int i = 0;i < clickStars.size();i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(clickStars[i].x, clickStars[i].y);
        RenderMesh2D(meshes["clickStar"], shaders["VertexColor"], modelMatrix);
    } //Pink stars render

    for (int i = 0;i <= 3;i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(75+195*i, 580);
        RenderMesh2D(meshes["outline"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes[tur+to_string(i + 1)], shaders["VertexColor"], modelMatrix);
        //Shop turrets render

        for (int j = 0;j <= i;j++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(65 + 195 * i+40*j, 520);
            RenderMesh2D(meshes["costStar"], shaders["VertexColor"], modelMatrix);
            if (i-2*j <= 0)
                break;
        } //Price render
    }

    for (int i = 0;i < bank;i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(871 + 40 * i, 560);
        RenderMesh2D(meshes["costStar"], shaders["VertexColor"], modelMatrix);
    } //Stored stars render

    for (int i = 0;i < lifePoints;i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(881 + 120 * i, 620);
        modelMatrix *= transform2D::Scale((float)2/ 3, (float)2 / 3);
        RenderMesh2D(meshes["lifebar"], shaders["VertexColor"], modelMatrix);
    } //HP render

    for (int i = 0;i < allyProjectile.size();i++) {
        if (allyProjectile[i].x >= 1160) {
            allyProjectile.erase(allyProjectile.begin() + i);
            i--;
            continue;
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(allyProjectile[i].x + cx, 340 - 160 * allyProjectile[i].y + cy);
        modelMatrix *= transform2D::Rotate(allyProjectile[i].w);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        RenderMesh2D(meshes[proj + to_string((int)allyProjectile[i].z)], shaders["VertexColor"], modelMatrix);
        allyProjectile[i].x += 4;
        allyProjectile[i].w -= 0.04;
    } //Projectile stars render

    if (enemyDrones.size() * 10 + (int)rand() % 10000 < 40) {
        enemyDrones.push_back(glm::vec4(1280, rand() % 3, 1 + rand() % 4, 3));
    } //Random turret appearence (<4)

    if (fmod(10.f+ runTime+deltaTimeSeconds, 15.f) < fmod(10.f + runTime, 15.f))
        for(int i=0;i<3;i++)
            clickStars.push_back(glm::vec2(20 + rand() % 1141, 20 + rand() % 581));
    //3 pink stars every 15s
    runTime += deltaTimeSeconds;
}

void R_VS_H::FrameEnd()
{
    if (lifePoints == 0)
        exit(0);
    //ded
}


void R_VS_H::OnInputUpdate(float deltaTime, int mods)
{
}


void R_VS_H::OnKeyPress(int key, int mods)
{
}


void R_VS_H::OnKeyRelease(int key, int mods)
{
}


void R_VS_H::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void R_VS_H::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        if (mouseTurret == 0)
            for (int i = 0;i <= 3;i++) {
                if (fun::Collision2D((mouseX - shapeDifX / 2.f) * allignDifX, (-mouseY + resolution.y - shapeDifY / 2.f) * allignDifY, 75 + 195 * i + cx, 580 + cy, 60.f*sqrt(2))&&bank>=i-i/3) {
                    mouseTurret = i + 1;
                    break;
                }
            }
        //Pick up turret
        for(int i=0;i<clickStars.size();i++)
            if (fun::Collision2D((mouseX - shapeDifX / 2.f) * allignDifX, (-mouseY + resolution.y - shapeDifY / 2.f) * allignDifY, clickStars[i].x+60, clickStars[i].y+60, 40.f)) {
                bank++;
                clickStars.erase(clickStars.begin() + i);
                break;
            }
        //Collect pink star
    }
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        for (int i = 0;i < 3;i++)
            for (int j = 0;j < 3;j++) {
                if(grid[i][j]!=0&&fmod(grid[i][j],1.0)==0)
                    if (fun::Collision2D((mouseX - shapeDifX / 2.f) * allignDifX, (-mouseY + resolution.y - shapeDifY / 2.f) * allignDifY, 120 + 160 * j + cx, 340 - 160 * i + cy, 60.f*sqrt(2))) {
                        grid[i][j] += 0.9;
                    }
            }
    } //Remove turret
}


void R_VS_H::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        if (mouseTurret != 0) {
            for (int i = 0;i < 3;i++)
                for (int j = 0;j < 3;j++) {
                    if (fun::Collision2D((mouseX - shapeDifX / 2.f) * allignDifX, (-mouseY + resolution.y - shapeDifY / 2.f) * allignDifY, 120 + 160 * j + cx, 340 - 160 * i + cy, 60 * sqrt(2))&& grid[i][j] == 0) {
                        grid[i][j] = mouseTurret;
                        bank = bank - (mouseTurret - mouseTurret / 3);
                        goto jump;                   //yes,am folosit goto
                    }
                }
        jump:
            mouseTurret = 0;
        }
    } //Place turret if mouse above a tile, else drop turret
}


void R_VS_H::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void R_VS_H::OnWindowResize(int width, int height)
{
}
