#include <includes/Input/Input.h>


bool Input::Keys[1024];


bool Input::GetKey(int key)
{
	return Input::Keys[key];
}
