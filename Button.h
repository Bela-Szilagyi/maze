#pragma once
#include <SDL_render.h>

enum Buttons {
	next,
	restart
};

class Button {
public:
	SDL_Rect sdl_rect;

	Button(SDL_Texture *activeTexture, SDL_Texture *inactiveTexture, bool isActive);
	void render(SDL_Renderer* renderer);
	const SDL_Rect &getSdl_rect() const;
	void setClicked(bool isClicked);
	bool isActive() const;
	void setActive(bool isActive);
	void setPosInArray(int posInArray);

protected:
	SDL_Texture *activeTexture = nullptr;
	SDL_Texture *inactiveTexture = nullptr;
	bool active;
	bool clicked = false;
	int posInArray;
	// TODO: set these values in constructor instread of hard-coding it
	int x = 900; int y = 100;
};

