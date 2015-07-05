#ifndef SNAKE_H
#define SNAKE_H
#include <deque>
#include <graphics.h>
#include <list>

using std::deque;

class Coordinate{
public:
	explicit Coordinate(int newx, int newy) :
		x(newx), y(newy){}
	const int getX() const{ return x; }
	const int getY() const{ return y; }
	void moveUp(int step);
	void moveLeft(int step);
	void moveRight(int step);
	void moveDown(int step);
	void setX(int);
	void setY(int);
private:
	int x;
	int y;
};

class SnakeBody{
public:
	SnakeBody(int x, int y) :location(x, y), isHead_(false){}
	SnakeBody(int x, int y, bool ishead) : location(x, y), isHead_(ishead){}
	const Coordinate& getCoordinate() const { return location;}
	void moveUp();
	void moveLeft();
	void moveRight();
	void moveDown();
	void move(int d);
	void replace(const SnakeBody&);
	void draw();
	void setHead(bool ishead){ isHead_ = ishead; }
	bool isHead() const { return isHead_; }
private:
	bool isHead_;
	static const int step = 20;
	Coordinate location;
};

class Snake{
public:
	friend class Apple;
	enum Direction{ up = 0, down, left, right };
	Snake();
	int getDirection(){
		return direction;
	}
	void setDirection(enum Direction d){
		direction = d;
	}
	void draw();
	void addBody(int x, int y);
	void move();
	void reset();
	bool hasAteFood(const Apple& aApple);
	bool hasBitSelf();
	deque<SnakeBody*> bodys;
	bool hasCrashedIntoWall();
	~Snake();
private:
	
	enum Direction direction;

};

class Apple {
public:
	Apple(const Snake &snake):location(0,0) { newApple(snake); }
	void newApple(const Snake &snake);
	int getX() const  { return location.getX(); }
	int getY() const { return location.getY(); }
	void draw();
private:
	Coordinate location;
};

#endif