#include "args.h"

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG 

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

