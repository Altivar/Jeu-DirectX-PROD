#pragma once
#include <iostream>

///////////////////
//  UPDATE ARGS  //
///////////////////
class UpdateArgs
{
public:
	UpdateArgs(float deltaTime);

	float GetDeltaTime();

private:
	float _deltaTime;

};


//////////////////
//  EVENT ARGS  //
//////////////////
class EventArgs
{
public:
	int intArgs;
	float floatArgs;
	std::string strArgs;
	//Peut etre rajouter un Point3 ?
};