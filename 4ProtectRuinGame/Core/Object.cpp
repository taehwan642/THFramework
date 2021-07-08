#include "DXUT.h"
#include "Object.h"

D3DXMATRIX Object::GetMatrix()
{
	D3DXMATRIX result;

	D3DXMatrixTransformation2D(&result, nullptr, 0, &scale, nullptr, rotation, &position);

	return result;
}
