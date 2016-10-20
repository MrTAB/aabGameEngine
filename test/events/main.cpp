

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

	SDL_Event event;

	bool quit = false;
	bool dragging = false;

	bool increaseColor = true;
	SDL_Rect mouseRect = {0, 0, 20, 20};
	Uint32 mouseRectColor = 0;

	cout << "beginning program";

	printf ("MOOOOO");

	while (! quit)
	{

		bool processEvents = SDL_PollEvent (&event);


		if (increaseColor)
		{
			mouseRectColor += 0x02;
			if (mouseRectColor > 0xff - 0x03)
			{
				increaseColor = false;
			}
		}
		else
		{
			mouseRectColor -= 0x2;

			if (mouseRectColor < 0x03)
			{
				increaseColor = true;
			}
		}

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
				//
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
				dragging = true;
			}
			break;

			case SDL_MOUSEBUTTONUP:
			{
				dragging = false;
			}
			break;

			case SDL_ACTIVEEVENT:
			{
				std::string gained = event.active.gain? "gained\n" : "lost\n";
				bool found = false;
				Uint8 state = event.active.state;

				if (state & SDL_APPMOUSEFOCUS)
				{
					cout << "mouse focus " << gained;
					found = true;
				}


				if (state & SDL_APPINPUTFOCUS)
				{
					cout << "keyboard focus " << gained;
					if (found)
					{
						cout << "MULTIPLE\n";
					}
					found = true;
				}


				if (state & SDL_APPACTIVE)
				{
					cout << "window-active focus " << gained;
					if (found)
					{
						cout << "MULTIPLE\n";
					}
					found = true;
				}

				if (! found)
				{
					cout << "unkown type of focus " << gained;
				}

			}
			break;

			default:
			{
			}
		}
		}


		if (dragging)
		{
			mouseRect.x = event.button.x - mouseRect.w/2;
			mouseRect.y = event.button.y - mouseRect.h/2;
			SDL_FillRect (screen, &mouseRect, mouseRectColor);
		}


		//SDL_Delay (100);

		SDL_Flip (screen);
	}


	SDL_Quit ();

	return 0;
}
