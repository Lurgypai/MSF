// MSF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "MVector.h"
#include "GameObject.h"
#include "Scene.h"
#include <iostream>
#include <vector>

//remember the rvalue references may be bad in MVector
//also, getGroup lazily guarded (no else return);
int main()
{
	msf::GameObject thing1{0.0, 0.0};
	msf::GameObject thing2{ 0.0, 1.0 };

	msf::GameObject thing3{ 0.0, 0.0 };

	msf::Scene scene1;
	msf::Scene scene2;

	scene1.addObject(thing1, "thing1");

	scene2.addGroup("things", { thing1, thing2 });

	std::cout << (thing1 == thing3) << std::endl;
	std::cout << (thing1 != thing3) << std::endl;

	std::cout << (thing1 == thing1) << std::endl;
	std::cout << (thing1 != thing1) << std::endl;

	std::cout << (thing1 == thing2) << std::endl;
	std::cout << (thing1 != thing2) << std::endl;

	std::cout << (scene1 == scene2) << std::endl;
	std::cout << (scene1 == scene1) << std::endl;

	std::cout << (scene1 != scene2) << std::endl;
	std::cout << (scene1 != scene1) << std::endl;


	return 0;
}

