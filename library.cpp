#define _CRT_SECURE_NO_WARNINGS
#define ERROR_FILE_OPEN -3
#include "SDL.h"
#include "stdlib.h"
#include <SDL_ttf.h>
#include <cstring>
#include <iostream>
SDL_Rect TEMP;
fpos_t pos1 = SEEK_SET;
int step = 0;
using namespace std;

//Вывод текста
void draw_text(SDL_Surface* gameBackground, const char* text, const char* font, int size, SDL_Color clr, SDL_Rect placing)
{
	TTF_Init();
	atexit(TTF_Quit);
	TTF_Font* fnt = TTF_OpenFont(font, size);
	SDL_Surface* sText = TTF_RenderText_Blended(fnt, text, clr);
	SDL_BlitSurface(sText, NULL, gameBackground, &placing);
	SDL_FreeSurface(sText);
	TTF_CloseFont(fnt);
	TTF_Quit();
}

//Удаление всех созданных текстур
void DestroyTexture(SDL_Surface* background, SDL_Surface* gameBackground, SDL_Surface* brick1_model, SDL_Surface* Brick1,
	SDL_Surface* brick2_model, SDL_Surface* Brick2, SDL_Surface* brick3_model, SDL_Surface* Brick3)
{
	SDL_FreeSurface(background); SDL_FreeSurface(gameBackground);
	SDL_FreeSurface(brick1_model); SDL_FreeSurface(Brick1);
	SDL_FreeSurface(brick2_model); SDL_FreeSurface(Brick2);
	SDL_FreeSurface(brick3_model); SDL_FreeSurface(Brick3);

}

//Вывод всех текстур на экран
void Move_Brick(SDL_Window* MainWindow, SDL_Surface* background, SDL_Surface* gameBackground, SDL_Rect BackgroundPos,
	SDL_Surface* brick1_model, SDL_Surface* Brick1, SDL_Rect Brick1_Rect,
	SDL_Surface* brick2_model, SDL_Surface* Brick2, SDL_Rect Brick2_Rect,
	SDL_Surface* brick3_model, SDL_Surface* Brick3, SDL_Rect Brick3_Rect)
{
	SDL_BlitSurface(background, NULL, gameBackground, &BackgroundPos);
	SDL_BlitSurface(brick1_model, NULL, Brick1, &Brick1_Rect);
	SDL_BlitSurface(brick2_model, NULL, Brick2, &Brick2_Rect);
	SDL_BlitSurface(brick3_model, NULL, Brick3, &Brick3_Rect);
	SDL_UpdateWindowSurface(MainWindow);
}

//Открывает доступ для перестоновки
bool access_brick(int core, SDL_Rect brick, SDL_Rect brick2, SDL_Rect brick3)
{
	if (core == 1) return true;

	if ((core > 1) && ((brick.y > brick2.y) || (brick.y > brick3.y)))
		return false;
	else
		return true;
}

//сверяет ширину перекладываемого блока,с уже имеющимися на стержне; flag - на какой стержень хотим переставить
//core - количество дисков на этом стержне; brick - параметры блока, который хотим переставить
//brick2 и brick3 параметры остальных двух дисков; flag2 и flag3 номера стержней, на которых они находятся соответственно
bool access_width(int flag, int core, SDL_Rect brick, SDL_Rect brick2, SDL_Rect brick3, int flag2, int flag3)
{
	if (core == 0)
		return true;
	if (core == 1)
	{
		if ((flag == flag2) && (brick.w > brick2.w))
			return false;
		else
			if ((flag == flag3) && (brick.w > brick3.w))
				return false;
			else
				return true;
	}

	if ((core == 2) && ((brick.w > brick2.w) || ((brick.w > brick3.w))))
		return false;
	else
		return true;
}

//Определяет у координату блока при перетаскивании; core - количество дисков на каждом стержне
//flag стержень, на который хотим переставить
int count(int core1, int core2, int core3, int flag)
{
	if (flag == 1)
	{
		if (core1 == 0) return 535;
		if (core1 == 1) return 500;
		if (core1 == 2) return 465;
	}

	if (flag == 2)
	{
		if (core2 == 0) return 535;
		if (core2 == 1) return 500;
		if (core2 == 2) return 465;
	}

	if (flag == 3)
	{
		if (core3 == 0) return 535;
		if (core3 == 1) return 500;
		if (core3 == 2) return 465;
	}

}
/*
void self_assembly(int n, int k, int m, int first_core, int second_core, int third_core,
	SDL_Window* MainWindow, SDL_Surface* background, SDL_Surface* gameBackground, SDL_Rect BackgroundPos,
	SDL_Surface* brick1_model, SDL_Surface* Brick1, SDL_Rect Brick1_Rect,
	SDL_Surface* brick2_model, SDL_Surface* Brick2, SDL_Rect Brick2_Rect,
	SDL_Surface* brick3_model, SDL_Surface* Brick3, SDL_Rect Brick3_Rect)
{
	int core1 = 155;
	int core2 = 405;
	int core3 = 655;
	if (n == 1)
	{
		TEMP.x = Brick3_Rect.x;
		TEMP.y = Brick3_Rect.y;
		TEMP.w = Brick3_Rect.w;
		TEMP.h = Brick3_Rect.h;
	}
	if (n == 2)
	{
		TEMP.x = Brick2_Rect.x;
		TEMP.y = Brick2_Rect.y;
		TEMP.w = Brick2_Rect.w;
		TEMP.h = Brick2_Rect.h;
	}
	if (n == 3)
	{
		TEMP.x = Brick1_Rect.x;
		TEMP.y = Brick1_Rect.y;
		TEMP.w = Brick1_Rect.w;
		TEMP.h = Brick1_Rect.h;
	}
	if (n == 1)
	{
		TEMP.x = core2 - TEMP.w / 2;
	}
	else
	{
		int tmp = 6 - k - m;
		self_assembly(n - 1, k, tmp, first_core, second_core, third_core,
			MainWindow, background, gameBackground, BackgroundPos,
			brick1_model, Brick1, Brick1_Rect,
			brick2_model, Brick2, Brick2_Rect,
			brick3_model, Brick3, Brick3_Rect);


		self_assembly(n - 1, tmp, k, first_core, second_core, third_core,
			MainWindow, background, gameBackground, BackgroundPos,
			brick1_model, Brick1, Brick1_Rect,
			brick2_model, Brick2, Brick2_Rect,
			brick3_model, Brick3, Brick3_Rect);
	}
}*/

void input_bin(const char* FileName, SDL_Rect brick1, SDL_Rect brick2, SDL_Rect brick3)
{
	FILE* fbin = fopen(FileName, "wb");

	if (fbin == NULL)
	{
		exit(ERROR_FILE_OPEN);
	}
	/*
	fprintf_s(fbin, "%d ", brick1.x);
	fprintf_s(fbin, "%d\n", brick1.y);
	fprintf_s(fbin, "%d ", brick2.x);
	fprintf_s(fbin, "%d\n", brick2.y);
	fprintf_s(fbin, "%d ", brick3.x);
	fprintf_s(fbin, "%d ", brick3.y);*/
	//возвращаемся к указателю на начало массива A[i]
	fsetpos(fbin, &pos1);
	
	fwrite(&brick1.x, sizeof(brick1.x), 1, fbin);
	fwrite(&brick1.y, sizeof(brick1.y), 1, fbin);
	fwrite(&brick2.x, sizeof(brick2.x), 1, fbin);
	fwrite(&brick2.y, sizeof(brick2.y), 1, fbin);
	fwrite(&brick3.x, sizeof(brick3.x), 1, fbin);
	fwrite(&brick3.y, sizeof(brick3.y), 1, fbin);
	step += 1;
	//запоминаем текущее положение указателя
	fgetpos(fbin, &pos1);
	fclose(fbin);
}

void output_bin(const char* FileName, SDL_Window* MainWindow, SDL_Surface* background, SDL_Surface* gameBackground, SDL_Rect BackgroundPos,
	SDL_Surface* brick1_model, SDL_Surface* Brick1, SDL_Rect Brick1_Rect,
	SDL_Surface* brick2_model, SDL_Surface* Brick2, SDL_Rect Brick2_Rect,
	SDL_Surface* brick3_model, SDL_Surface* Brick3, SDL_Rect Brick3_Rect)
{
	FILE* fbin = fopen(FileName, "rb");

	if (fbin == NULL)
	{
		exit(ERROR_FILE_OPEN);
	}

	for (int i = 0; i < step; i++)
	{
		fread(&Brick1_Rect.x, sizeof(Brick1_Rect.x), 1, fbin);
		fread(&Brick1_Rect.y, sizeof(Brick1_Rect.y), 1, fbin);
		fread(&Brick2_Rect.x, sizeof(Brick2_Rect.x), 1, fbin);
		fread(&Brick2_Rect.y, sizeof(Brick2_Rect.y), 1, fbin);
		fread(&Brick3_Rect.x, sizeof(Brick3_Rect.x), 1, fbin);
		fread(&Brick3_Rect.y, sizeof(Brick3_Rect.y), 1, fbin);

		Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
			brick1_model, Brick1, Brick1_Rect,
			brick2_model, Brick2, Brick2_Rect,
			brick3_model, Brick3, Brick3_Rect);
		SDL_Delay(500);
	}
	/*
	while (!feof(fbin))
	{
		/*
		fscanf_s(fbin, "%d", &Brick1_Rect.x);
		fscanf_s(fbin, "%d", &Brick1_Rect.y);
		fscanf_s(fbin, "%d", &Brick2_Rect.x);
		fscanf_s(fbin, "%d", &Brick2_Rect.y);
		fscanf_s(fbin, "%d", &Brick3_Rect.x);
		fscanf_s(fbin, "%d", &Brick3_Rect.y);
		*
		//возвращаемся к указателю на начало массива A[i]
		fread(&Brick1_Rect.x, sizeof(Brick1_Rect.x), 1, fbin);
		fread(&Brick1_Rect.y, sizeof(Brick1_Rect.y), 1, fbin);
		fread(&Brick2_Rect.x, sizeof(Brick2_Rect.x), 1, fbin);
		fread(&Brick2_Rect.y, sizeof(Brick2_Rect.y), 1, fbin);
		fread(&Brick3_Rect.x, sizeof(Brick3_Rect.x), 1, fbin);
		fread(&Brick3_Rect.y, sizeof(Brick3_Rect.y), 1, fbin);
		
		Move_Brick(MainWindow, background, gameBackground, BackgroundPos,
			brick1_model, Brick1, Brick1_Rect,
			brick2_model, Brick2, Brick2_Rect,
			brick3_model, Brick3, Brick3_Rect);
		SDL_Delay(500);
	}*/
	fclose(fbin);
}