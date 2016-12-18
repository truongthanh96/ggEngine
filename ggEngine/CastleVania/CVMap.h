#pragma once
#include <ggEngine.h>
#include "Simon.h"
using namespace ggEngine;
class CVGame;
class CVAdd;
class InfoPanel;
class SimonGroup;
class CVStage;
class CVCamera;
class CVBlock;
class CVMap : public Group {
public:
	CVMap(CVGame *cvGame);
	virtual ~CVMap();
	void BuildMap(const char* jsonChar);
	void Draw() override;
	void Update() override;
	void UpdatePhysics() override;
	void LoadSimon(InfoPanel *infoPanel, GameOverScreen *goScreen, Simon *simon = nullptr);
	TileMap *tileMapGroup;
	QuadTree *quadTreeGroup;
	CameraActiveGroup* cameraActiveGroup;
	SimonGroup *simonGroup;
	Simon* simon;
	void SetStage(int stageNumber,int blockNumber = 0);
	void SetBlock(int blockNumber);
private:
	CVStage* currentStage = nullptr;
	CVBlock* currentBlock = nullptr;
	InfoPanel *infoPanel;
	Add* add;
	CVAdd* cvAdd;
	CVGame* cvGame;
	CVCamera* camera;
	std::vector<CVStage*> stageList;
};