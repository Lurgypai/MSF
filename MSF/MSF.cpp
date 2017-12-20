// MSF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "MVector.h"
#include "GameObject.h"
#include "Scene.h"
#include "Game.h"
#include "Settings.h"
#include <iostream>
#include <vector>
#include <fstream>

//remember the rvalue references may be bad in MVector
//also, getGroup lazily guarded (no else return);
int main()
{
	msf::Scene scene1;
	msf::GameObject thing1{scene1, 1.0, 0.0,  msf::GameObject::Physics };
	msf::GameObject thing2{scene1, 2.0, 0.0, msf::GameObject::Physics | msf::GameObject::Graphics | msf::GameObject::Input };

	msf::GameObject thing3{scene1, 3.0, 0.0,  msf::GameObject::Audio };

	msf::Game game{ "game",{ {"scene1", scene1} }, msf::Settings{{"width", 720}, {"height", 480}} };
	game.start("scene1");
	scene1.updateAll();
	return 0;
}

