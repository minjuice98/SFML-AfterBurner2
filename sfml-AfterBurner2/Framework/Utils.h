#pragma once
class Utils
{
public:
	//Clamp
	static float Clamp(float value, float min, float max);

	//길이의 제곱
	static float SqrMagnitude(const sf::Vector2f& vec);
	//벡터의 길이
	static float Magnitude(const sf::Vector2f vec);
	//정규화
	static void Normalize(sf::Vector2f& vec);
	//정규화된 벡터 반환
	static sf::Vector2f GetNormal(const sf::Vector2f& vec);
};