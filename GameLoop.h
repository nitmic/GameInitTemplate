#pragma once
class IScene;

/*
*@class GameLoop
*�@�ˑ��@SceneHandler
*/

//namespace DXAdapter{
	class GameLoop{
	public:
		GameLoop(std::shared_ptr<IScene> startScene);
		bool update();
		void draw();
	private:
		struct Impl;
		std::shared_ptr<Impl> __impl__;
	};
//};