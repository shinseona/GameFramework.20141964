#include<SDL.h>
#include<iostream>
#include"Game.h"
using namespace std;

bool Game::init(const char* title, int xpos, int ypos,
	int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);

		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}
	}
	else {
		return false;
	}

	m_bRunning = true;
	SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);
	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle1.w, &m_sourceRectangle1.h);

	return true;
}

void Game::render()
{
	m_destinationRectangle.x = m_sourceRectangle1.x = 0;
	m_destinationRectangle.y = m_sourceRectangle1.y = 0;
	m_destinationRectangle.w = m_sourceRectangle1.w;
	m_destinationRectangle.h = m_sourceRectangle1.h;

	SDL_RenderClear(m_pRenderer);
	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle1, &m_destinationRectangle);
	SDL_RenderPresent(m_pRenderer);

	

	
}

void Game::clean()
{
	
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}