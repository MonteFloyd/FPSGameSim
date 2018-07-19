#pragma once
#ifndef VECTOR_UTIL_HPP
#define VECTOR_UTIL_HPP
#include <SFML/Graphics.hpp>


inline float Distance(sf::Vector2f a, sf::Vector2f b) {
	return std::sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

inline bool lineIntersect2D(sf::Vector2f A,
	sf::Vector2f B,
	sf::Vector2f C,
	sf::Vector2f D)
{
	double rTop = (A.y - C.y)*(D.x - C.x) - (A.x - C.x)*(D.y - C.y);
	double sTop = (A.y - C.y)*(B.x - A.x) - (A.x - C.x)*(B.y - A.y);

	double Bot = (B.x - A.x)*(D.y - C.y) - (B.y - A.y)*(D.x - C.x);

	if (Bot == 0)//parallel
	{
		return false;
	}

	double invBot = 1.0 / Bot;
	double r = rTop * invBot;
	double s = sTop * invBot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	{
		//lines intersect
		return true;
	}

	//lines do not intersect
	return false;
}


inline bool getIntersection(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f D, float &distance, sf::Vector2f& intersection) {

	float rTop = (A.y - C.y)*(D.x - C.x) - (A.x - C.x)*(D.y - C.y);
	float sTop = (A.y - C.y)*(B.x - A.x) - (A.x - C.x)*(B.y - A.y);

	float Bot = (B.x - A.x)*(D.y - C.y) - (B.y - A.y)*(D.x - C.x);

	if (Bot == 0)//parallel
	{
		return false;
	}

	float invBot = 1.0f / Bot;
	float r = rTop * invBot;
	float s = sTop * invBot;


	if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	{
		intersection = A + r * (B - A);
		distance = Distance(A, B) * r;
		return true;
	}

	return false;


}

inline bool getIntersectionRaycast(const sf::Vector2f& r1, const sf::Vector2f& r2, const sf::Vector2f& s1, const sf::Vector2f& s2,float &distance, sf::Vector2f& intersection) {



	float r_dx = r2.x - r1.x;
	float r_dy = r2.y - r1.y;


	float s_dx = s2.x - s1.x;
	float s_dy = s2.y - s1.y;
		

	float r_Magnitude = std::sqrtf(r_dx * r_dx + r_dy * r_dy);
	float s_Magnitude = std::sqrtf(s_dx * s_dx + s_dy * s_dy);



	if ( (r_dx / r_Magnitude) == (s_dx / s_Magnitude) && (r_dy/ r_Magnitude ) == (s_dy / s_Magnitude)  ) {
		return false;
	}

	float T2 = (r_dx * (s1.y - r1.y) + r_dy*(r1.x - s1.x)) / (s_dx * r_dy - s_dy * r_dx);
	float T1 = (s1.x + s_dx * T2 - r1.x) / r_dx;

	if (T1 < 0) {
		return false;
	}

	if (T2 < 0 || T2 > 1) {
		return false;
	}

	intersection.x = r1.x + r_dx * T1;
	intersection.y = r1.y + r_dy * T1;
	distance = T1;

	return true;
}





#endif