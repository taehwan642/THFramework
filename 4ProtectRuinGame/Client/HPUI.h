#pragma once
#include "AniSprite.h"
class HPUI :
    public AniSprite
{
    // 특정 객체에게 부착되어야 하고
    // imgrect를 사용해서 HP가 닳는걸 표현
    // HPBar, HPUI 두개로 분리해야하고 (Texture)
    // 최대 체력, 현재 체력 정보를 알아야 함.
};

