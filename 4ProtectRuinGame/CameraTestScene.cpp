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
	POINT p; // ��ũ�� ��ǥ
	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);

	// ��ü�� position�� ���� ��ǥ
	// ���� ��ǥ�� ��ũ�� ��ǥ�� �־���.

	// ī�޶� ����, ��ũ�� ������ ���� ���� ����Ͻð�
	// ī�޶��� ��ġ�� 0 0�϶� ���̴� ������ -sw /2, -sh/2���� sw/2, sh/2����.
	// �̰ŷ� ���Ͻø� �˴ϴ�.
	sp->position = cam.camPos + Vec2(-screenwidth / 2, -screenheight / 2) + Vec2(p.x, p.y);

	// �ٵ� ���� ��ǥ�� �� (ī�޶�)�� ���� ��ȭ�ǰ�, �� �� ���������� ���ؼ� �� �ٲ��.
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
