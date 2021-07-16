#pragma once
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <ostream>
#include <cmath>

constexpr int screenwidth = 1280;
constexpr int screenheight = 720;

using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;
using Color = D3DXCOLOR;
using Matrix = D3DXMATRIX;

#define GAMEON true

#include "GameObjectState.h"
#include "GameObject.h"

#include "PlayerState.h"
#include "Player.h"

