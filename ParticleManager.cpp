#include <vector>
#include <SDL.h>
#include "Particle.h"
#include "Utils.h"
#include <chrono>
#include <stdio.h>

class ParticleManager {
public:
	std::vector<Particle> particles;

	void add(Particle particle) {
		particles.push_back(particle);
	}
	void update(float passedTime) {
		if (particles.size() == 0) {
			return;
		}
		else {
			passedTime = passedTime / CLOCKS_PER_SEC;
			
			for (auto& part : particles) {
				part.update(passedTime);
			}
			for (int i = 0; i < particles.size(); i++) {
				for (int j = i + 1; j < particles.size(); j++) {
					Particle &a = particles.at(i);
					Particle &b = particles.at(j);
					float dist = sqrt(powf(a.position.X - b.position.X, 2) + powf(a.position.Y - b.position.Y, 2));
					int rad = a.radius + b.radius;
					if (dist < rad) {
						Vec2 VelANew = b.velocity;
						Vec2 VelBNew = a.velocity;

						float dp1 = (a.velocity - b.velocity).X * (a.position - b.position).X + -(a.velocity - b.velocity).Y * (a.position - b.position).Y;
						float dp2 = (b.velocity - a.velocity).X * (b.position - a.position).X + -(b.velocity - a.velocity).Y * (b.position - a.position).Y;

						float ambMag = sqrt(powf(b.position.X - a.position.X, 2) + powf(b.position.Y - a.position.Y, 2));
						float bmaMag = sqrt(powf(a.position.X - b.position.X, 2) + powf(a.position.Y - b.position.Y, 2));

						VelBNew = a.velocity - (a.position - b.position) * (dp1 / (ambMag * ambMag));
						VelANew = b.velocity - (b.position - a.position) * (dp2 / (bmaMag * bmaMag));

						a.velocity = VelANew * 0.8f;
						b.velocity = VelBNew * 0.8f;
					}
				}
			}
		}
	}
	void draw(SDL_Renderer* renderer) {
		if (particles.size() == 0) {
			return;
		}
		else {
			for (auto& part : particles) {
				part.draw(renderer);
			}
		}
	}
};