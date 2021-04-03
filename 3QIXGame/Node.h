#pragma once
class Node // 객체 (물체) 가 가지고 있을 정보들
{
public:
	Node() {};
	virtual ~Node() {};

	// 조심해야 하는 실수
	// scale은 무조건 1 0이면 안보인다
	// color 잘 선택해야한다. alpha가 0이면 안보인다.
	// Renderer에게 잘 넘겨줘야하고
	// 메인 루프 속에서 함수가 잘 호출되는지 봐야하고
	// Matrix (행렬) 설정을 제대로 했는지 확인해본다.

	Vec2 position = { 0,0 };
	Vec2 scale = { 1,1 };
	Vec2 pivot = { 0.5f,0.5f };
	int layer = 0; // 클수록 앞에 온다!
	float rotation = 0;
	bool isactive = true; // 살아있나? 죽었나?
	Color color = Color(1, 1, 1, 1);
	RECT imageRect;

	virtual void Update() {};
	virtual void Draw() {};

	D3DXMATRIX GetMatrix();
};

