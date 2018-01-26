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
#include <memory>
#include "TestGraphicsComponent.h"
#include "TestPhysicsComponent.h"
#include "TestInputComponent.h"
#include "GameObjectFactory.h"
#include "BoxGraphicsComp.h"
#include "SimpleController.h"
#include "DataInComponent.h"

//remember the rvalue references may be bad in MVector
//also, getGroup lazily guarded (no else return);

//add camera to manipulate window
//add controller
/*add gameobjectfactory
	-takes all the parameters of a gameobject, constructs multiple using the same criteria and returns a vector of handles to them
*/
//the gameobject is incomplete
//virtual destructors
int main()
{
	//the texture file is lost when its copied over. You'll have to create an overrideable clone method to somehow save the texture for the copy
	//use mutexes or atomic vals to protect is looping from concurrency issues
	msf::Game game("BoxT");
	msf::Scene scene1;
	std::shared_ptr<msf::DataObject> dobj = scene1.addDObject();
	dobj->setInput<DataInComponent>(game.getWindow(), &scene1);
	game.setSettings({ {"width", 1080}, {"height", 720} });
	game.getSettings().save("settings.txt");

	SimpleController cont{};
	game.addController<SimpleController>(cont);

	game.addScene(scene1, "scene1");
	game.start("scene1");

	game.stopLoop();
	game.getUpdater()->addCurrentGroup("default");
	game.startLoop();

	return 0;
}
