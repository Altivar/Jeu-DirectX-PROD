#include "args.h"


///////////////////
//  UPDATE ARGS  //
///////////////////
UpdateArgs::UpdateArgs(float deltaTime)
	: _deltaTime (deltaTime)
{
}

float UpdateArgs::GetDeltaTime()
{
	return _deltaTime;
}

