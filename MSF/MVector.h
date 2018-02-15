#pragma once
#include <SFML/System.hpp>
//holds velocity in angle (degrees), and magnitude (double) 

namespace msf {

struct MVector {
	MVector(void);
	MVector(double angle_, double magnitude_);
	MVector(const sf::Vector2f& pos1_, const sf::Vector2f& pos2_);
	~MVector();

	void xComp(double d);
	void yComp(double d);
	double xComp() const;
	double yComp() const;

	//operators
	MVector operator+(const MVector& vec_) const;
	MVector operator-(const MVector& vec_) const;
	MVector operator+(double d) const;
	MVector operator-(double d) const;
	MVector operator*(double d) const;
	MVector operator/(double d) const;

	void operator+=(const MVector& vec_);
	void operator-=(const MVector& vec_);
	void operator+=(double d);
	void operator-=(double d);
	void operator*=(double d);
	void operator/=(double d);

	bool operator==(const MVector& vec_) const;
	bool operator!=(const MVector& vec_) const;

	double angle;
	double magn;
};

//operators
sf::Vector2f operator+(const sf::Vector2f& vec_, const MVector& mvec_);
void operator+=(sf::Vector2f& vec_, const MVector& mvec_);


sf::Vector2f operator-(const sf::Vector2f& vec_, const MVector& mvec_);
void operator-=(sf::Vector2f& vec_, const MVector& mvec_);
}