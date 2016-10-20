

#include<sdl.h>
#include<iostream>
#include<string>


int main (int argc, char** argv)
{
	using std::cout;
	using std::cin;
	using std::endl;

	SDL_Init (SDL_INIT_EVERYTHING);

	SDL_Surface * screen = SDL_SetVideoMode (640, 480, 0, SDL_DOUBLEBUF);
	//SDL_SetClear (screen, 0x000000);

	SDL_Event event;

	bool quit = false;
	int mouseX = 640/2;
	int mouseY = 480/2;

	SDL_Rect mouseRect = {0, 0, 20, 20};
	Uint32 mouseRectColor = 0x05B3C0;

	cout << "beginning program";

	while (! quit)
	{

		bool processEvents = SDL_PollEvent (&event);


		if (processEvents)
		{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				quit = true;
			}
			break;

			case SDL_KEYDOWN:
			{
			}
			break;

			case SDL_KEYUP:
			{
				unsigned int code = event.key.keysym.sym;
				switch (code)
				{
					case SDLK_SPACE: cout <<" "; break;
					case SDLK_RETURN: cout <<"\n"; break;
					default:
						if (code >= 'a' && code <= 'z')
						{
								cout << static_cast <char> (code);
						}
						else
						{
							cout << "key:\t" << SDL_GetKeyName (event.key.keysym.sym) << "\n";
						}
				}
			}
			break;

			case SDL_MOUSEBUTTONDOWN:
			{

			}
			break;

			case SDL_MOUSEBUTTONUP:
			{

			}
			break;

			case SDL_MOUSEMOTION:
			{
				mouseX = event.motion.x;
				mouseY = event.motion.y;
			}
			break;

			default:
			{
			}
		}
		}


		mouseRect.w = 20;
		mouseRect.h = 20;
		mouseRect.x = mouseX - mouseRect.w/2;
		mouseRect.y = mouseY - mouseRect.h/2;
		SDL_FillRect (screen, &mouseRect, mouseRectColor);


		SDL_Delay (10);

		SDL_Flip (screen);
		SDL_FillRect (screen, NULL, 0x000000);
	}


	SDL_Quit ();

	return 0;
}
