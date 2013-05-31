#pragma once

class IModel{
public:
	virtual bool isValid() = 0;
};

class IDrawer{
public:
	virtual bool isVisible() = 0;
	virtual void draw() = 0;
};

class IAgent{
public:
	virtual bool isAlive() = 0;
	virtual void step() = 0;
};