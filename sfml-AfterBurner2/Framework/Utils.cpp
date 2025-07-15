#include "stdafx.h"
#include "Utils.h"

float Utils::Clamp(float value, float min, float max)
{ //이동 후 위치를 min, max로 강제함
    if (value < min) return min;
    else if (value > max) return max;
}
