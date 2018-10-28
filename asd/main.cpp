#include <SFML/Graphics.hpp>
#include <random>
#include <functional>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
const int high = 600;
const int widht = 600;
const double G = 0.00001;
using namespace sf;

class Shar 
{
private:
public:
	CircleShape krug;
	float vx, vy, x, y,rad,ax=0,ay=0;
	float posx, posy;
	Shar(int x, int y,int r,Color color, double speedx, double speedy)
	{	
		vy = speedy;
		vx = speedx;
		krug.setPointCount(30);
		krug.setRadius(r);
		krug.setPosition(x,y);
		krug.setFillColor(color);
		this->x = x;
		this->y = y;
		rad = r;
		posx = widht - 2 * rad;
		posy= high - 2 * rad;
	}//конструктор(коорд. x,коорд. y, радиус, цвет, скорость x, скорость y)
	~Shar()
	{
		krug.setRadius(0);
	}
	void draw(RenderWindow &window)
	{
		window.draw(krug);
	}
	void move(double time )
	{
		krug.move(vx*time,vy*time);
		x = x + vx*time;
		y = y + vy*time;
	}
	void gran()
	{ 
		if (x <= 0) { krug.setPosition(2, y); vx = -vx; };
		if (y <= 0) { krug.setPosition(x, 2); vy = -vy; };
		if (x >= posx) { krug.setPosition(posx-2 , y); vx = -vx; };
		if (y >= posy) { krug.setPosition(x, posy-2 ); vy = -vy; };
		
	}
	void stolk(Shar& d)
	{
		float x1, y1, x2, y2,vx1,vy1,dvx,dvy,pam1,pam2;
		x1 = x + rad; y1 = y + rad;
		x2 = d.x + d.rad; y2 = d.y + d.rad;
		float tet;
		tet = atan(abs((x1 - x2) / (y1 - y2)));
		if ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) <= (d.rad + rad)*(d.rad + rad))
		{		
				pam1 = (vx + vy) / (2 * cos(tet));
				pam2 = (d.vx + d.vy) / (2 * cos(tet));
				vx1 = ((rad - d.rad)*pam1+2*d.rad*pam2)/(d.rad+rad);
				dvx = ((d.rad - rad)*pam2 + 2 * rad*pam1) / (d.rad + rad);
				dvy = (d.vx -d.vy) / (-2*sin(tet));
				vy1  = (vx - vy) / (-2 * sin(tet));
				vx = vx1*cos(tet) - vy1*sin(tet);
				vy  = vx1*cos(tet) + vy1*sin(tet);
				d.vx = dvx*cos(tet) - dvy*sin(tet);
				d.vy = dvx*cos(tet) + dvy*sin(tet);
			}			

		
	}
	void grav(Shar& d)
	{
		double x1, x2,y1,y2;
		x1 = x + rad; y1 = y + rad;
		x2 = d.x + d.rad; y2 = d.y + d.rad;
		double tet = atan(abs( (y1 - y2)/ (x1 - x2)));
		double aa = G*(rad*d.rad)/ (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
		ax = aa*cos(tet)/rad;
		ay = aa*sin(tet) / rad;
		d.ax = aa*cos(tet) / d.rad;
		d.ay = aa*sin(tet) / d.rad;
		if (d.x > x) { vx += ax; d.vx -= d.ax; }	else { vx -= ax; d.vx += d.ax; };
		if (d.y > y) { vy += ay; d.vy -= d.ay; }	else { vy -= ay; d.vy += d.ay; };

		
	}
};
int main()
{
	RenderWindow window(VideoMode(widht, high), "Ska4o4oki");
	Shar s1(100,100,5,Color::Yellow,0.000,0.003);
	Shar s2(300,100,5,Color::Blue,0.00,0.00);
	Shar s3(450,360,5,Color::Green,0.00,0.00);
	Clock clock;
	double time;
	while (window.isOpen())
	{
		time = clock.getElapsedTime().asMicroseconds();
		time /= 10;
		clock.restart();
		s1.grav(s2);
		s1.gran();
		s2.gran();
		s3.gran();
		s1.move(time);
		s2.move(time);
		s3.move(time);
		s1.grav(s2);
		s3.grav(s1);
		s2.grav(s3);
		window.clear();
		s1.draw(window);
		s2.draw(window);
		s3.draw(window);
		window.display();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		
	}

	return 0;
}