#pragma once


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


//////////////////////
//  COLLISION ARGS  //
//////////////////////
class CollisionArgs
{
public:
	CollisionArgs();
};
