#pragma once
#include "transform2D.h"

#include "utils/glm_utils.h"

namespace fun
{
	glm::mat3 Fade(float&,int,int);
	bool Collision2D(int x1, int y1, int x2, int y2, float squareSide);
}
