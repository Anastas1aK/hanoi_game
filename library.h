
#ifndef DYNARRAY_H

void draw_text(SDL_Surface* gameBackground, const char* text, const char* font, int size, SDL_Color clr, SDL_Rect placing);
void DestroyTexture(SDL_Surface* background, SDL_Surface* gameBackground, SDL_Surface* brick1_model, SDL_Surface* Brick1,
	SDL_Surface* brick2_model, SDL_Surface* Brick2, SDL_Surface* brick3_model, SDL_Surface* Brick3);
void Move_Brick(SDL_Window* MainWindow, SDL_Surface* background, SDL_Surface* gameBackground, SDL_Rect BackgroundPos,
	SDL_Surface* brick1_model, SDL_Surface* Brick1, SDL_Rect Brick1_Rect,
	SDL_Surface* brick2_model, SDL_Surface* Brick2, SDL_Rect Brick2_Rect,
	SDL_Surface* brick3_model, SDL_Surface* Brick3, SDL_Rect Brick3_Rect);
bool access_brick(int core, SDL_Rect brick, SDL_Rect brick2, SDL_Rect brick3);
bool access_width(int flag, int core, SDL_Rect brick, SDL_Rect brick2, SDL_Rect brick3, int flag2, int flag3);
int count(int core1, int core2, int core3, int flag);
void input_bin(const char* FileName, SDL_Rect brick1, SDL_Rect brick2, SDL_Rect brick3);
void output_bin(const char* FileName, SDL_Window* MainWindow, SDL_Surface* background, SDL_Surface* gameBackground, SDL_Rect BackgroundPos,
	SDL_Surface* brick1_model, SDL_Surface* Brick1, SDL_Rect Brick1_Rect,
	SDL_Surface* brick2_model, SDL_Surface* Brick2, SDL_Rect Brick2_Rect,
	SDL_Surface* brick3_model, SDL_Surface* Brick3, SDL_Rect Brick3_Rect);

#endif
#define DYNARRAY_H

