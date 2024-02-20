#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class R_VS_H : public gfxc::SimpleScene
    {
     public:
         R_VS_H();
        ~R_VS_H();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        float rad;
        glm::mat3 modelMatrix;
        glm::mat3 grid;
        glm::mat3 reloadTime;
        int mouseTurret;
        int bank;
        int lifePoints;
        std::vector<glm::vec2> clickStars;
        std::vector<glm::vec4> enemyDrones;
        std::vector<glm::vec4> allyProjectile;
        glm::vec2 resolution;
        float shapeDifX,shapeDifY;
        float allignDifX, allignDifY;
        float runTime,currentTime;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
