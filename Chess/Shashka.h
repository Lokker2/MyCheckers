#pragma once

ref class Shashka
{
public:
	Shashka();

	void setData(int, int, bool);
	void setCoord(int, int);
	int getX();
	int getY();

	void setSelected(bool);
	bool getSelected();

	bool getColor();
	
	bool getCheck();
	void setCheck(bool);

	bool getDamka();
	void setDamka(bool);
	
private:
	int x;
	int y;
	bool color;
	bool damka;
	bool check;
	bool selected;
};


Shashka::Shashka()
{
	x = 0;
	y = 0;
	color = 0;
	damka = 0;
	check = 1;
	selected = 0;
}

void Shashka::setData(int X, int Y, bool Color)
{
	x = X;
	y = Y;
	color = Color;
}

void Shashka::setCoord(int X, int Y)
{
	x = X;
	y = Y;
}

int Shashka::getX()
{
	return x;
}

int Shashka::getY()
{
	return y;
}

bool Shashka::getSelected()
{
	return selected;
}

bool Shashka::getColor()
{
	return color;
}

void Shashka::setSelected(bool flag)
{
	selected = flag;
}

bool Shashka::getCheck()
{
	return check;
}

void Shashka::setCheck(bool f)
{
	check = f;
}

bool Shashka::getDamka()
{
	return damka;
}

void Shashka::setDamka(bool f)
{
	damka = f;
}
