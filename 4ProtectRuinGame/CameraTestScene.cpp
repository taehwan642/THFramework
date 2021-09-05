#include "DXUT.h"
#include "CameraTestScene.h"

void CameraTestScene::Init()
{
	Camera& cam = Camera::GetInstance();
	cam.Initialize();

	sp = new Sprite;
	sp->SetTexture(L"hurt (1).png");
	sp->position = { screenwidth / 2, screenheight / 2 };
	
	
	std::cout << "asdf" << std::endl;
}

void CameraTestScene::Update()
{
	Camera& cam = Camera::GetInstance();
	POINT p; // 스크린 좌표
	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);

	// 물체의 position은 월드 좌표
	// 월드 좌표에 스크린 좌표를 넣었다.

	// 카메라 영역, 스크린 영역을 따로 놔서 기억하시고
	// 카메라의 위치가 0 0일때 보이는 영역은 -sw /2, -sh/2부터 sw/2, sh/2까지.
	// 이거로 구하시면 됩니다.
	sp->position = cam.camPos + Vec2(-screenwidth / 2, -screenheight / 2) + Vec2(p.x, p.y);

	// 근데 월드 좌표는 뷰 (카메라)를 통해 변화되고, 그 뒤 프로젝션을 통해서 또 바뀐다.
	// 

	if (DXUTIsKeyDown('W'))
		cam.camPos.y -= 10.f;
	if (DXUTIsKeyDown('A'))
		cam.camPos.x -= 10.f;
	if (DXUTIsKeyDown('S'))
		cam.camPos.y += 10.f;
	if (DXUTIsKeyDown('D'))
		cam.camPos.x += 10.f;

	std::cout << p.x << " " << p.y << std::endl;
	std::cout << "CAMPOS : " << cam.camPos.x << " " << cam.camPos.y << std::endl;

}

void CameraTestScene::Exit()
{
	std::cout << "exit" << std::endl;
}
