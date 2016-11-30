#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVAdd;
class CVPreload;
class Simon;
class ItemManager;
class WeaponManager;
class CVGame : public Game {
public:
	CVGame(HWND hWnd, int width, int height, GameMode mode = GameMode_Windowed, PhysicsMode physicsMode = PhysicsMode_AABB, D3DCOLOR gameColor = D3DCOLOR_XRGB(0, 255, 255));
	virtual ~CVGame();
	CVAdd *cvAdd;
	CVPreload *cvPreload;
	Simon *simon;
	ItemManager *itemManager;
	WeaponManager *weaponManager;
private:
};