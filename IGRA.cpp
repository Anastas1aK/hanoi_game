#define _CRT_SECURE_NO_WARNINGS
#define ERROR_FILE_OPEN -3
#include "SDL.h"
#include "stdlib.h"
#include <SDL_ttf.h>
#include <cstring>
#include "library.h"
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* MainWindow = SDL_CreateWindow(u8"Ханойская башня", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	SDL_Rect BackgroundPos;
	BackgroundPos.x = 0;
	BackgroundPos.y = 0;

	SDL_Color color = { 0,0,0,0 };
	SDL_Rect min_move_placing = {170,0,0,0};
	SDL_Rect your_move_placing = { 170, 30,0,0 };
	SDL_Rect move_placing = { 450,30,0,0 };
	int size_text = 25;
	const char bin[] = "1.bin";
	const char font[] = "Text.ttf";
	const char min_moves[] = "minimum count of moves: 7";
	char your_moves[] = "your count of moves: ";
	char char_move[3];
	int move = 0;

	SDL_Rect Brick1_Rect = { 55, 535, 200,35 };
	SDL_Rect Brick2_Rect = { 65, 500, 180,35 };
	SDL_Rect Brick3_Rect = { 75, 465, 160,35 };

	SDL_Surface* background = SDL_LoadBMP("hanoy.BMP");
	SDL_Surface* gameBackground = SDL_GetWindowSurface(MainWindow);
	SDL_BlitSurface(background, NULL, gameBackground, &BackgroundPos);

	SDL_Surface* Menu_model = SDL_LoadBMP("menu.BMP");
	SDL_Surface* menu = SDL_GetWindowSurface(MainWindow);
	SDL_BlitSurface(Menu_model, NULL, menu, &BackgroundPos);

	SDL_Surface* brick1_model = SDL_LoadBMP("brick1.BMP");
	SDL_Surface* Brick1 = SDL_GetWindowSurface(MainWindow);
	SDL_BlitSurface(brick1_model, NULL, Brick1, &Brick1_Rect);

	SDL_Surface* brick2_model = SDL_LoadBMP("brick2.BMP");
	SDL_Surface* Brick2 = SDL_GetWindowSurface(MainWindow);
	SDL_BlitSurface(brick2_model, NULL, Brick2, &Brick2_Rect);

	SDL_Surface* brick3_model = SDL_LoadBMP("brick3.BMP");
	SDL_Surface* Brick3 = SDL_GetWindowSurface(MainWindow);
	SDL_BlitSurface(brick3_model, NULL, Brick3, &Brick3_Rect);

	_itoa_s(move, char_move, 3, 10);
	draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
	draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
	draw_text(gameBackground, char_move, font, size_text, color, move_placing);

	SDL_UpdateWindowSurface(MainWindow);

	SDL_Event event;
	bool quit = true;
	
	//на каком стержне находится диск
	int flag1 = 1;
	int flag2 = 1;
	int flag3 = 1;

	//Отвечает за нажание на диск 0 - на диск нажали, 1 - диск не активен для перестоновки 
	int activation1 = 1;
	int activation2 = 1;
	int activation3 = 1;

	//на какой стержень хотим переставить диск
	int flag01 = 1;
	int flag02 = 1;
	int flag03 = 1;

	//количество дисков на каждом стержне
	int core1 = 3;
	int core2 = 0;
	int core3 = 0;

	int start0 = 0;
	bool access_move = false;
	bool width = false;
	bool start = false;
	int record = 0;

	while (quit)
	{

		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			quit = false;
		if ((!start))
		{
			start0 = 0;
			SDL_BlitSurface(Menu_model, NULL, menu, &BackgroundPos);
			SDL_UpdateWindowSurface(MainWindow);
			if ((event.button.y > 268) && (event.button.y < 320) && (event.button.x > 300) && (event.button.x < 500) && (event.button.button == SDL_BUTTON_LEFT)) 
			{
				start = true;
				start0 = 1;
			}
			if ((event.button.y > 345) && (event.button.y < 400) && (event.button.x > 300) && (event.button.x < 500) && (event.button.button == SDL_BUTTON_LEFT))
			{
				output_bin(bin,MainWindow, background, gameBackground, BackgroundPos,
					brick1_model, Brick1, Brick1_Rect,
					brick2_model, Brick2, Brick2_Rect,
					brick3_model, Brick3, Brick3_Rect);
			}
			if ((event.button.y > 425) && (event.button.y < 490) && (event.button.x > 300) && (event.button.x < 500) && (event.button.button == SDL_BUTTON_LEFT))
			{
				quit = false;
			}
		}
		else
		{
			//Запись ходов
			if ((event.key.keysym.sym == SDLK_z) and (event.type == SDL_KEYDOWN))
			{
				record = 1;
				input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
			}

			if (start0 == 1)
			{
				Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
					brick1_model, Brick1, Brick1_Rect,
					brick2_model, Brick2, Brick2_Rect,
					brick3_model, Brick3, Brick3_Rect);
				_itoa_s(move, char_move, 3, 10);
				draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
				draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
				draw_text(gameBackground, char_move, font, size_text, color, move_placing);
				SDL_UpdateWindowSurface(MainWindow);
				start0 = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)) start = false;
			//Рестарт уровня, возвращение блоков на начальную позицию
			if (((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > 770) and (event.button.x < SCREEN_WIDTH) and (event.button.y < 30) and (event.button.y > 0))
				or ((event.type == SDL_KEYDOWN) and (event.key.keysym.sym == SDLK_r)))
			{
				Brick1_Rect.x = 55; Brick1_Rect.y = 535; flag1 = 1;
				Brick2_Rect.x = 65; Brick2_Rect.y = 500; flag2 = 1;
				Brick3_Rect.x = 75; Brick3_Rect.y = 465; flag3 = 1;
				core1 = 3;
				core2 = 0;
				core3 = 0;
				move = 0;
				_itoa_s(move, char_move, 3, 10);
				Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
					brick1_model, Brick1, Brick1_Rect,
					brick2_model, Brick2, Brick2_Rect,
					brick3_model, Brick3, Brick3_Rect);
				draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
				draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
				draw_text(gameBackground, char_move, font, size_text, color, move_placing);
				SDL_UpdateWindowSurface(MainWindow);
				if (record == 1)
					input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
			}

			//нажатие 1го диска
			if ((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > Brick1_Rect.x) and (event.button.x < Brick1_Rect.x + Brick1_Rect.w)
				and (event.button.y > Brick1_Rect.y) and (event.button.y < Brick1_Rect.y + Brick1_Rect.h))
			{
				activation2 = 1;
				activation3 = 1;
				if (flag1 == 1)
					access_move = access_brick(core1, Brick1_Rect, Brick2_Rect, Brick3_Rect);
				if (flag1 == 2)
					access_move = access_brick(core2, Brick1_Rect, Brick2_Rect, Brick3_Rect);
				if (flag1 == 3)
					access_move = access_brick(core3, Brick1_Rect, Brick2_Rect, Brick3_Rect);
				if ((access_move) and (activation2 != 0) and (activation3 != 0))
					activation1 = 0;
				access_move = false;
			}
			//нажитие 2го диска
			if ((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > Brick2_Rect.x) and (event.button.x < Brick2_Rect.x + Brick2_Rect.w)
				and (event.button.y > Brick2_Rect.y) and (event.button.y < Brick2_Rect.y + Brick2_Rect.h))
			{
				activation1 = 1;
				activation3 = 1;
				if (flag2 == 1)
					access_move = access_brick(core1, Brick2_Rect, Brick1_Rect, Brick3_Rect);
				if (flag2 == 2)
					access_move = access_brick(core2, Brick2_Rect, Brick1_Rect, Brick3_Rect);
				if (flag2 == 3)
					access_move = access_brick(core3, Brick2_Rect, Brick1_Rect, Brick3_Rect);
				if ((access_move) and (activation1 != 0) and (activation3 != 0))
					activation2 = 0;
			}
			//нажатие 3го диска
			if ((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > Brick3_Rect.x) and (event.button.x < Brick3_Rect.x + Brick3_Rect.w)
				and (event.button.y > Brick3_Rect.y) and (event.button.y < Brick3_Rect.y + Brick3_Rect.h))
			{
				activation2 = 1;
				activation1 = 1;
				if (flag3 == 1)
					access_move = access_brick(core1, Brick3_Rect, Brick1_Rect, Brick2_Rect);
				if (flag3 == 2)
					access_move = access_brick(core2, Brick3_Rect, Brick1_Rect, Brick2_Rect);
				if (flag3 == 3)
					access_move = access_brick(core3, Brick3_Rect, Brick1_Rect, Brick2_Rect);
				if ((access_move) and (activation2 != 0) and (activation1 != 0))
					activation3 = 0;
			}
			//1й на 1й
			if (((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > 110) and (event.button.x < 200)
				and (event.button.y > 240) and (event.button.y < 570) and (activation1 == 0) and (Brick1_Rect.x != 55)))
			{
				flag01 = 1;
				width = access_width(flag01, core1, Brick1_Rect, Brick2_Rect, Brick3_Rect, flag2, flag3);
				if (width)
				{
					flag1 = 1;
					if (Brick1_Rect.x == 305) core2 -= 1;
					if (Brick1_Rect.x == 555) core3 -= 1;
					Brick1_Rect.x = 55;
					Brick1_Rect.y = count(core1, core2, core3, flag1);
					Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
						brick1_model, Brick1, Brick1_Rect,
						brick2_model, Brick2, Brick2_Rect,
						brick3_model, Brick3, Brick3_Rect);
					move += 1;
					_itoa_s(move, char_move, 3, 10);
					draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
					draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
					draw_text(gameBackground, char_move, font, size_text, color, move_placing);
					SDL_UpdateWindowSurface(MainWindow);
					if (record == 1)
						input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
					core1 += 1;
				}
				width = false;
			}
			//1й на 2й
			if (((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > 360) and (event.button.x < 450)
				and (event.button.y > 240) and (event.button.y < 570) and (activation1 == 0) and (Brick1_Rect.x != 305)))
			{
				flag01 = 2;
				width = access_width(flag01, core2, Brick1_Rect, Brick2_Rect, Brick3_Rect, flag2, flag3);
				if (width)
				{
					flag1 = 2;
					if (Brick1_Rect.x == 55) core1 -= 1;
					if (Brick1_Rect.x == 555) core3 -= 1;
					Brick1_Rect.x = 305;
					Brick1_Rect.y = count(core1, core2, core3, flag1);
					Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
						brick1_model, Brick1, Brick1_Rect,
						brick2_model, Brick2, Brick2_Rect,
						brick3_model, Brick3, Brick3_Rect);
					move += 1;
					_itoa_s(move, char_move, 3, 10);
					draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
					draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
					draw_text(gameBackground, char_move, font, size_text, color, move_placing);
					SDL_UpdateWindowSurface(MainWindow);
					if (record == 1)
						input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
					core2 += 1;
				}
				width = false;
			}
			//1й на 3й
			if (((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > 610) and (event.button.x < 700)
				and (event.button.y > 400) and (event.button.y < 570) and (activation1 == 0) and (Brick1_Rect.x != 555)))
			{
				flag01 = 3;
				width = access_width(flag01, core3, Brick1_Rect, Brick2_Rect, Brick3_Rect, flag2, flag3);
				if (width)
				{
					flag1 = 3;
					if (Brick1_Rect.x == 305) core2 -= 1;
					if (Brick1_Rect.x == 55) core1 -= 1;
					Brick1_Rect.x = 555;
					Brick1_Rect.y = count(core1, core2, core3, flag1);
					Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
						brick1_model, Brick1, Brick1_Rect,
						brick2_model, Brick2, Brick2_Rect,
						brick3_model, Brick3, Brick3_Rect);
					move += 1;
					_itoa_s(move, char_move, 3, 10);
					draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
					draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
					draw_text(gameBackground, char_move, font, size_text, color, move_placing);
					SDL_UpdateWindowSurface(MainWindow);
					if (record == 1)
						input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
					core3 += 1;
				}
				width = false;
			}
			//2й на 1
			if (((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > 110) and (event.button.x < 200)
				and (event.button.y > 240) and (event.button.y < 570) and (activation2 == 0) and (Brick2_Rect.x != 65)))
			{
				flag02 = 1;
				width = access_width(flag02, core1, Brick2_Rect, Brick1_Rect, Brick3_Rect, flag1, flag3);
				if (width)
				{
					flag2 = 1;
					if (Brick2_Rect.x == 315) core2 -= 1;
					if (Brick2_Rect.x == 565) core3 -= 1;
					Brick2_Rect.x = 65;
					Brick2_Rect.y = count(core1, core2, core3, flag2);
					Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
						brick1_model, Brick1, Brick1_Rect,
						brick2_model, Brick2, Brick2_Rect,
						brick3_model, Brick3, Brick3_Rect);
					move += 1;
					_itoa_s(move, char_move, 3, 10);
					draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
					draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
					draw_text(gameBackground, char_move, font, size_text, color, move_placing);
					SDL_UpdateWindowSurface(MainWindow);
					if (record == 1)
						input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
					core1 += 1;
				}
				width = false;
			}
			//2й на 2й
			if (((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > 360) and (event.button.x < 450)
				and (event.button.y > 240) and (event.button.y < 570) and (activation2 == 0) and (Brick2_Rect.x != 315)))
			{
				flag02 = 2;
				width = access_width(flag02, core2, Brick2_Rect, Brick1_Rect, Brick3_Rect, flag1, flag3);
				if (width)
				{
					flag2 = 2;
					if (Brick2_Rect.x == 65) core1 -= 1;
					if (Brick2_Rect.x == 565) core3 -= 1;
					Brick2_Rect.x = 315;
					Brick2_Rect.y = count(core1, core2, core3, flag2);
					Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
						brick1_model, Brick1, Brick1_Rect,
						brick2_model, Brick2, Brick2_Rect,
						brick3_model, Brick3, Brick3_Rect);
					move += 1;
					_itoa_s(move, char_move, 3, 10);
					draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
					draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
					draw_text(gameBackground, char_move, font, size_text, color, move_placing);
					SDL_UpdateWindowSurface(MainWindow);
					if (record == 1)
						input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
					core2 += 1;
				}
				width = false;
			}
			//2й на 3й
			if (((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > 610) and (event.button.x < 700)
				and (event.button.y > 400) and (event.button.y < 570) and (activation2 == 0) and (Brick2_Rect.x != 565)))
			{
				flag02 = 3;
				width = access_width(flag02, core3, Brick2_Rect, Brick1_Rect, Brick3_Rect, flag1, flag3);
				if (width)
				{
					flag2 = 3;
					if (Brick2_Rect.x == 315) core2 -= 1;
					if (Brick2_Rect.x == 65) core1 -= 1;
					Brick2_Rect.x = 565;
					Brick2_Rect.y = count(core1, core2, core3, flag2);
					Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
						brick1_model, Brick1, Brick1_Rect,
						brick2_model, Brick2, Brick2_Rect,
						brick3_model, Brick3, Brick3_Rect);
					move += 1;
					_itoa_s(move, char_move, 3, 10);
					draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
					draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
					draw_text(gameBackground, char_move, font, size_text, color, move_placing);
					SDL_UpdateWindowSurface(MainWindow);
					if (record == 1)
						input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
					core3 += 1;
				}
				width = false;
			}
			//3й на 1й
			if (((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > 110) and (event.button.x < 200)
				and (event.button.y > 240) and (event.button.y < 570) and (activation3 == 0) and (Brick3_Rect.x != 75)))
			{
				flag03 = 1;
				width = access_width(flag03, core1, Brick3_Rect, Brick1_Rect, Brick2_Rect, flag1, flag2);
				if (width)
				{
					flag3 = 1;
					if (Brick3_Rect.x == 325) core2 -= 1;
					if (Brick3_Rect.x == 575) core3 -= 1;
					Brick3_Rect.x = 75;
					Brick3_Rect.y = count(core1, core2, core3, flag3);
					Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
						brick1_model, Brick1, Brick1_Rect,
						brick2_model, Brick2, Brick2_Rect,
						brick3_model, Brick3, Brick3_Rect);
					move += 1;
					_itoa_s(move, char_move, 3, 10);
					draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
					draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
					draw_text(gameBackground, char_move, font, size_text, color, move_placing);
					SDL_UpdateWindowSurface(MainWindow);
					if (record == 1)
						input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
					core1 += 1;
				}
				width = false;
			}
			//3й на 2й
			if (((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > 360) and (event.button.x < 450)
				and (event.button.y > 240) and (event.button.y < 570) and (activation3 == 0) and (Brick3_Rect.x != 325)))
			{
				flag03 = 2;
				width = access_width(flag03, core2, Brick3_Rect, Brick1_Rect, Brick2_Rect, flag1, flag2);
				if (width)
				{
					flag3 = 2;
					if (Brick3_Rect.x == 75) core1 -= 1;
					if (Brick3_Rect.x == 575) core3 -= 1;
					Brick3_Rect.x = 325;
					Brick3_Rect.y = count(core1, core2, core3, flag3);
					Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
						brick1_model, Brick1, Brick1_Rect,
						brick2_model, Brick2, Brick2_Rect,
						brick3_model, Brick3, Brick3_Rect);
					move += 1;
					_itoa_s(move, char_move, 3, 10);
					draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
					draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
					draw_text(gameBackground, char_move, font, size_text, color, move_placing);
					SDL_UpdateWindowSurface(MainWindow);
					if (record == 1)
						input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
					core2 += 1;
				}
				width = false;
			}
			//3й на 3й
			if (((event.button.button == SDL_BUTTON_LEFT) and (event.button.x > 610) and (event.button.x < 700)
				and (event.button.y > 400) and (event.button.y < 570) and (activation3 == 0) and (Brick3_Rect.x != 575)))
			{
				flag03 = 3;
				width = access_width(flag03, core3, Brick3_Rect, Brick1_Rect, Brick2_Rect, flag1, flag2);
				if (width)
				{
					flag3 = 3;
					if (Brick3_Rect.x == 325) core2 -= 1;
					if (Brick3_Rect.x == 75) core1 -= 1;
					Brick3_Rect.x = 575;
					Brick3_Rect.y = count(core1, core2, core3, flag3);
					Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
						brick1_model, Brick1, Brick1_Rect,
						brick2_model, Brick2, Brick2_Rect,
						brick3_model, Brick3, Brick3_Rect);
					move += 1;
					_itoa_s(move, char_move, 3, 10);
					draw_text(gameBackground, min_moves, font, size_text, color, min_move_placing);
					draw_text(gameBackground, your_moves, font, size_text, color, your_move_placing);
					draw_text(gameBackground, char_move, font, size_text, color, move_placing);
					SDL_UpdateWindowSurface(MainWindow);
					if (record == 1)
						input_bin(bin, Brick1_Rect, Brick2_Rect, Brick3_Rect);
					core3 += 1;
				}
				width = false;
			}

		}

	}
	
	SDL_Delay(1000);
	_Exit(quit);

	DestroyTexture(background, gameBackground,brick1_model, Brick1, brick2_model, Brick2, brick3_model, Brick3);
	SDL_DestroyWindow(MainWindow);
	SDL_FreeSurface(Menu_model); SDL_FreeSurface(menu);
	SDL_Quit();
	delete[]font;
	delete[]min_moves;
	delete[]your_moves;
	delete[]char_move;
	return 0;
}