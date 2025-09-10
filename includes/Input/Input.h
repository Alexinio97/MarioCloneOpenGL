#pragma once

class Input {
public:
	static bool Keys[1024];
	static bool KeysUp[1024];

	static bool GetKey(int key);

	static bool GetKeyDown(int key);	
};