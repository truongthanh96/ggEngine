#pragma once
#include <ggEngine.h>
#include "ManagerBase.h"
#include "AxeKnight.h"
#include "Medusa.h"
using namespace ggEngine;
class EnemyManager : ManagerBase {
public:
	EnemyManager(CVGame *cvGame);
	~EnemyManager();

	void PreloadAll();
	AxeKnight* AddAxeKnight(double x, double y, Group *group);
	Medusa* AddMedusa(double x, double y, Group *group);

private:
};