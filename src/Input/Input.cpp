#include <includes/Input/Input.h>


bool Input::Keys[1024];
bool Input::KeysUp[1024];

bool Input::GetKey(int key)
{
	return Input::Keys[key];
}

bool Input::GetKeyDown(int key)
{
	if(!KeysUp[key] && Keys[key])
	{
		Input::KeysUp[key] = true;
		return true;
	}
	else
	{
		return false;
	}
}
