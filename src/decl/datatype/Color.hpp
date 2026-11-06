#pragma once

#include <glm/vec3.hpp>

class Color
{
public:

	/**
	Create a blank (black) color
	@return The color black
	*/
	Color();

	Color(float S);

	/**
	Create a color from a range of 0 to 1
	@param The R, G and B values of the color
	@return A color made from the specified RGB values
	*/
	Color(float R, float G, float B);

	float R = 0.f, G = 0.f, B = 0.f;

	Color operator*(const Color& other) const
	{
		return Color(
			this->R * other.R,
			this->G * other.G,
			this->B * other.B
		);
	}

	Color operator*(float other) const
	{
		return Color(
			this->R * other,
			this->G * other,
			this->B * other
		);
	}

	Color operator+(const Color& other) const
	{
		return Color(
			R + other.R,
			G + other.G,
			B + other.B
		);
	}

	Color operator-(const Color& other) const
	{
		return Color(
			R - other.R,
			G - other.G,
			B - other.B
		);
	}

	bool operator == (const Color& Other) const
	{
		return (R == Other.R) && (G == Other.G) && (B == Other.B);
	}

	bool operator != (const Color& Other) const
	{
		return !((*this) == Other);
	}

	operator glm::vec3() const
	{
		return { R, G, B };
	}
};
