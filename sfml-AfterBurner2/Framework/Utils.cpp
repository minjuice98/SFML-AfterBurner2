#include "stdafx.h"
#include "Utils.h"

float Utils::Clamp(float value, float min, float max)
{ //이동 후 위치를 min, max로 강제함
    if (value < min) return min;
    else if (value > max) return max;
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{//길이의 제곱 반환
    return vec.x * vec.x + vec.y + vec.y;
}

float Utils::Magnitude(const sf::Vector2f vec)
{//벡터의 길이
    return std::sqrtf(SqrMagnitude(vec));
}

void Utils::Normalize(sf::Vector2f& vec)
{ //정규화된 벡터 반환
    float mag = Utils::Magnitude(vec);
    if (mag > std::numeric_limits<float>::epsilon())
    {//epsilon() 부동소수점 연산에서 의미 있는 연산을 할 수 있는 최소 단위
        vec /= mag;
    }
}

sf::Vector2f Utils::GetNormal(const sf::Vector2f& vec)
{//벡터 정규화
    float mag = Utils::Magnitude(vec);
    if (mag < std::numeric_limits<float>::epsilon())
    {
        return { 0.f,0.f };
    }
    return vec / mag;
}