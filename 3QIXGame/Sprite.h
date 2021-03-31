#pragma once
#include "Texture.h"
#include "Director.h"
#include "Renderer.h"
#include "Node.h"
class Sprite : // 텍스쳐를 가지고 실제로 그려주는 클래스.
    // 디렉터의 스프라이트를 가져오고, 렌더러에게 정보를 넘겨준다.
    public Node
{
private:
    float deltatime = 0.0f;
public:
    int frame = 0;
    Sprite();
    virtual ~Sprite();

    Texture* texture; // 스프라이트의 텍스쳐

    void SetTexture(wstring path);

    RECT GetRect();

    float GetDistance(Vec2 obj);
    float Look(Vec2 obj);

    bool Animation(wstring path, float t, int f);

    void Draw() override;
};

