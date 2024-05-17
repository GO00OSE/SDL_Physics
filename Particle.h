#include "Utils.h"
#include <stdio.h>
#include <SDL.h>

#ifndef PARTICLE_H
#define PARTICLE_H
class Particle {
public:
	int radius;
	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;

	Particle(int rad, Vec2 pos, Vec2 vel, Vec2 acc) {
		radius = rad;
		position = pos;
		velocity = vel;
		acceleration = acc;
	}

	Particle() {
		radius = 20;
		position = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
		velocity = Vec2();
		acceleration = Vec2(0, 100);
	}

	void update(float passedTime) {
		Vec2 new_postion;
		Vec2 new_velocity;
		new_postion.Y = position.Y + (passedTime * (velocity.Y + passedTime * acceleration.Y/2));
		new_velocity.Y = velocity.Y + (acceleration.Y * passedTime);

		new_postion.X = position.X + (velocity.X * passedTime) + (acceleration.X * passedTime * passedTime)/2;
		new_velocity.X = velocity.X + (acceleration.X * passedTime);

		if (new_postion.Y > SCREEN_HEIGHT) {
			new_velocity.Y *= -0.8f;
			new_postion.Y = position.Y;
		}

		position = new_postion;
		velocity = new_velocity;
	}

	void draw(SDL_Renderer* renderer) {
		Uint8 velocityMag = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y);
		//printf("%d\n", velocityMag);
		
		SDL_SetRenderDrawColor(renderer, velocityMag, 0x90, 0xFF-velocityMag, 0xFF);
		for (int i = 0; i <= 360; i++) {
			int y = radius * sin(i);
			int x = radius * cos(i);

			SDL_RenderDrawPoint(renderer, x + position.X, y + position.Y);
		}
	}
};
#endif