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
	
	msf::Scene scene;
	scene.addObject(thing1);
	scene.createGroup("thingies");
	scene.createGroup("moreThingies", std::vector<std::shared_ptr<msf::GameObject>>(1, std::make_shared<msf::GameObject>(thing1)));
	scene.createGroup("evenMoreThingies", {thing1, thing1});

	return 0;
}

