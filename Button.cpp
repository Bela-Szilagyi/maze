#include "Button.h"



#include "Button.h"


Button::Button(SDL_Texture *activeTexture, SDL_Texture *inactiveTexture, bool isActive)
	: activeTexture(activeTexture),
	inactiveTexture(inactiveTexture),
	active(isActive) {
	sdl_rect.x = x;
	sdl_rect.y = y;
	sdl_rect.w = 10;
	sdl_rect.h = 10;
}

void Button::render(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_Rect r;
	//r.x = x;
	//r.y = y;
	//r.w = sdl_rect.w;
	//r.h = sdl_rect.h;
	SDL_RenderFillRect(renderer, &sdl_rect);
	SDL_RenderCopy(renderer, (active ? activeTexture : inactiveTexture), NULL, &sdl_rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

const SDL_Rect &Button::getSdl_rect() const {
	return sdl_rect;
}

void Button::setClicked(bool isClicked) {
	if (!active) {
		clicked = isClicked;
	}
}

bool Button::isActive() const {
	return active;
}

void Button::setActive(bool isActive) {
	Button::active = isActive;
}

void Button::setPosInArray(int posInArray) {
	Button::posInArray = posInArray;
}