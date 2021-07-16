#include "DXUT.h"
#include "GameObjectState.h"

void* TestIdleState::handleInput()
{
	if (DXUTIsKeyDown('A')
		|| DXUTIsKeyDown('D'))
		return CASTVOIDPNT(TestState::RUN);
	std::cout << "??" << std::endl;
	return CASTVOIDPNT(TestState::IDLE);
}

void* TestRunState::handleInput()
{
	if (DXUTIsKeyDown('A'))
	{
		keys[0] = 1;
	}
	else keys[0] = 0;

	if (DXUTIsKeyDown('D'))
	{
		keys[1] = 1;
	}
	else keys[1] = 0;

	int result = keys[0] + keys[1];
	std::cout << "!!" << std::endl;

	if (result == 0)
		return CASTVOIDPNT(TestState::IDLE);
	return CASTVOIDPNT(TestState::RUN);
}
