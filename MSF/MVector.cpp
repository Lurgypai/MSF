#include "stdafx.h"
#include "MVector.h"
#include <math.h>
#include <cmath>
#include <iostream>
#define PI 3.14159265358979323846

using msf::MVector;

MVector::MVector(void) :
	angle(0.0),
	magn(0.0)
{}

MVector::MVector(const double& angle_, const double& magn_) :
	angle(angle_),
	magn(magn_)
{}

msf::MVector::MVector(const sf::Vector2f & pos1_, const sf::Vector2f & pos2_) :
	angle(atan2(pos2_.y - pos1_.y, pos2_.x - pos1_.x) * (180 / PI)),
	magn(sqrt(((pos2_.x - pos1_.x) * (pos2_.x - pos1_.x)) + ((pos2_.y - pos1_.y)* (pos2_.y - pos1_.y)))) {}

MVector::~MVector() {}


MVector && MVector::operator+(const MVector & vec_) const
{
	double xComp{ (cos(angle * (PI / 180)) * magn) + (cos(vec_.angle * (PI / 180)) * vec_.magn) };
	double yComp{ (sin(angle * (PI / 180)) * magn) + (sin(vec_.angle * (PI / 180)) * vec_.magn) };

	return MVector{(atan2(yComp, xComp) * (180 / PI)), sqrt((xComp * xComp) + (yComp * yComp))};
}

MVector && MVector::operator-(const MVector & vec_) const
{
	double xComp{ (cos(angle * (PI / 180)) * magn) - (cos(vec_.angle * (PI / 180)) * vec_.magn) };
	double yComp{ (sin(angle * (PI / 180)) * magn) - (sin(vec_.angle * (PI / 180)) * vec_.magn) };

	return MVector{ (atan2(yComp, xComp) * (180 / PI)), sqrt((xComp * xComp) + (yComp * yComp)) };
}

MVector && MVector::operator+(const double & d) const
{
	return MVector{angle, magn + d};
}

MVector && MVector::operator-(const double & d) const
{
	return MVector{ angle, magn - d};
}

MVector && MVector::operator*(const double & d) const
{
	return MVector(angle, magn * d);
}

MVector && MVector::operator/(const double & d) const
{
	return MVector(angle, magn / d);
}

void MVector::operator+=(const MVector & vec_) {
	double xComp{ (cos(angle * (PI / 180)) * magn) + (cos(vec_.angle * (PI / 180)) * vec_.magn) };
	double yComp{ (sin(angle * (PI / 180)) * magn) + (sin(vec_.angle * (PI / 180)) * vec_.magn) };
	angle = (atan2(yComp, xComp) * (180 / PI));
	magn = sqrt((xComp * xComp) + (yComp * yComp));
}

void MVector::operator-=(const MVector & vec_) {
	double xComp{ (cos(angle * (PI / 180)) * magn) - (cos(vec_.angle * (PI / 180)) * vec_.magn) };
	double yComp{ (sin(angle * (PI / 180)) * magn) - (sin(vec_.angle * (PI / 180)) * vec_.magn) };

	angle = (atan2(yComp, xComp) * (180 / PI));
	magn = sqrt((xComp * xComp) + (yComp * yComp));
}

void MVector::operator+=(const double & d) {
	magn += d;
}

void MVector::operator-=(const double & d) {
	magn -= d;
}

void MVector::operator*=(const double & d) {
	std::cout << "hit, " << magn << std::endl;
	magn *= d;
}

void MVector::operator/=(const double & d) {
	magn /= d;
}

bool && MVector::operator==(const MVector & vec_)
{
	return (angle == vec_.angle && magn == vec_.magn);
}

bool && MVector::operator!=(const MVector & vec_)
{
	return (angle != vec_.angle || magn != vec_.magn);
}

double MVector::xComp() const {
	return (cos(angle * (PI / 180)) * magn);
}

double MVector::yComp() const {
	return (sin(angle * (PI / 180)) * magn);
}

sf::Vector2f && msf::operator+(const sf::Vector2f & vec_, const MVector & mvec_)
{
	return sf::Vector2f{ static_cast<float>((vec_.x + mvec_.xComp())), static_cast<float>(vec_.y + mvec_.yComp()) };
}

void msf::operator+=(sf::Vector2f & vec_, const MVector & mvec_) {
	vec_.x = static_cast<float>(vec_.x + mvec_.xComp());
	vec_.y = static_cast<float>(vec_.y + mvec_.yComp());
}

sf::Vector2f && msf::operator-(const sf::Vector2f & vec_, const MVector & mvec_) {
	return sf::Vector2f{ static_cast<float>((vec_.x - mvec_.xComp())), static_cast<float>(vec_.y - mvec_.yComp()) };
}

void msf::operator-=(sf::Vector2f & vec_, const MVector & mvec_) {
	vec_.x = static_cast<float>(vec_.x - mvec_.xComp());
	vec_.y = static_cast<float>(vec_.y - mvec_.yComp());
}
