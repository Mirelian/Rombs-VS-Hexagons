#include "functions.h"

glm::mat3 fun::Fade(float& storedScale, int cx, int cy)
{

    float scale = fmod(storedScale, 1.0);

    if (scale < 0.1) {
        storedScale = 0;
        return glm::mat3(1);
    }
    else
        storedScale -= 0.02;

	glm::mat3 matrix;
    matrix = glm::mat3(1);
    matrix *= transform2D::Translate(cx * (1.f - scale), cy * (1.f - scale));
    matrix *= transform2D::Scale(scale,scale);

	return matrix;
}

bool fun::Collision2D(
    int x1,
    int y1,
    int x2,
    int y2,
    float sumRadious)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    float distance = sqrt(dx * dx + dy * dy);

    return  distance < sumRadious;
}