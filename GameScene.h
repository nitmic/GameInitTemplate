#include <memory>
#include "IScene.h"

class SceneHandler;

class GameScene : public IScene{
public:
	GameScene();
	void step(
		SceneHandler * sceneHandler
	);
	void draw();
	bool isTransparency(){return false;};
private:
	struct Impl;
	std::shared_ptr<Impl> __impl__;
};