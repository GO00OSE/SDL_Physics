#include <SDL.h>

#ifndef SCREEN_CONSTS
#define SCREEN_CONSTS
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
#endif // SCREEN_CONSTS

#ifndef STRUCTS_H
#define STRUCTS_H

struct Vec2 {
	float X = 0;
	float Y = 0;

	Vec2(float x, float y) {
		X = x;
		Y = y;
	}
	Vec2() {
		X = 0.0f;
		Y = 0.0f;
	}

	Vec2 operator+(Vec2 const& obj) {
		Vec2 res;
		res.X = X + obj.X;
		res.Y = Y + obj.Y;
		return res;
	}
	Vec2 operator-(Vec2 const& obj) {
		Vec2 res;
		res.X = X - obj.X;
		res.Y = Y - obj.Y;
		return res;
	}
	Vec2 operator*(float const& obj) {
		Vec2 res;
		res.X = X * obj;
		res.Y = Y * obj;
		return res;
	}
};
#endif // !VEC2_H

/*
#ifndef DRAW_CIRCLE
#define DRAW_CICRCLE
void Draw1Circle(SDL_Renderer* gRenderer, int center_x, int center_y, int r) {
	for (int i = 0; i <= 360; i++) {
		int y = r * sin(i);
		int x = r * cos(i);

		SDL_RenderDrawPoint(gRenderer, x + center_x, y + center_y);
	}
}
#endif
*/