#ifndef SCENE_H
#define SCENE_H
#include "graphics.h"
#include "snake.h"
#include <string>
class Scene{
public:
	Scene();
	~Scene();
	void init();
	void start();

private:
	void setDirectionByKeyMsg();
	void reset();
	void failed();
	bool hasFailed;
	bool hasHitKey;
	int speed;
	int score;
	int maxscore;
	Snake snake;
	Apple aApple;

};

#endif
