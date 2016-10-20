
#include"screen.hpp"
#include"texture.hpp"
#include<exception>

int main ()
{
	try
	{

		using namespace aab::visen;


		//puppet (_mask)	iron_giant	darknut



		Screen screen (640, 480);

		screen.setClearColor (255, 0, 0);


		Texture ironGiant	("media/iron_giant.PNG");
		Texture darknut		("media/darknut.PNG", 255, 0, 255);
		Texture puppet		("media/puppet.PNG", "media/puppet_mask.PNG");

		while (1)
		{
			screen.clear ();

			ironGiant.draw	(screen, screen.getWidth()/2, screen.getHeight()/2);
			darknut.draw	(screen, screen.getWidth()/2, screen.getHeight()/2);
			puppet.draw		(screen, screen.getWidth()/2, screen.getHeight()/2);

			screen.update ();
		}

	}
	catch (std::exception e)
	{
	}

	return 0;
}



