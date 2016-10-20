# aabGameEngine
A Game Engine that serves as a basis for creating 2d Games in C++

This engine was developed using TDM-2 mingw32 4.4.1 in Code::Blocks 10.05; the relevant project files are included, and are open readable in text editors to view dependancy orderings.

This engine has a number of dependancies:
  SDL 1.2.14 - Note that versions of SDL past 1.2 are drastically different.
  Glew 1.10.0
  OpenGL 1.3
  SDL_Image 1.2.12
  SDL_Mixer 1.2.12
  libpng15.15
  zlib128
  pugixml 1.2
  PNG_SaveSurf (by Angelo Encelo Theodorou - see http://www.autistici.org/encelo/prog_sdldemos.php)
  Boost 1.49 (using specific components below - libraries system and filesystem)
    boost/filesystem	
    boost/algorithm/string/replace
    boost/smart_ptr.hpp
    boost/pointer_cast.hpp

As an exercise at the time, This Game Engine was made as several smaller libraries which work in unison, but can be partly separated for individual tasks.

See the "driver" folder for examples of use.


