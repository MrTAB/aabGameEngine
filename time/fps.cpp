
/**
*
*
*
**/

#include"fps.hpp"
#include"time_method.hpp"
#include<limits> 
namespace aab	{
namespace time	{


Fps::Fps ()
{
	last = getMilliseconds ();
	count = 0;
	fps = 0;
	updates = 0;
	//averageFps = 0.f;
	totalFps = 0.f;
	updateFactor = 1.0f;
}

Fps::~Fps ()// throw ()
{
}

int Fps::update ()
{
	unsigned int now = getMilliseconds ();

	if (now > last + 1000)
	{
		fps = (int) ( (double)count * 1000.0/(double)(now-last));
		last = now;
		count = 0;
	}
	else
	{
		++count;
	}

    //if(updates)
    //{
        //averageFps *= static_cast<float>(updates)/static_cast<float>(updates+1);
        //averageFps += static_cast<float>(fps)/static_cast<float>(updates+1);
    //}
    //else
    //{
        //averageFps = fps;
    //}
    totalFps += updateFactor*fps;
    ++updates;
    
    if (totalFps > std::numeric_limits<float>::max() - 10*getAverageFps())
    {
        updateFactor /= 2.f;
        totalFps /= 2.f;
        updates /= 2;
    }
    
	return fps;
}

int Fps::getFps ()const
{
	return fps;
}

float Fps::getAverageFps()const
{
    //return averageFps;
    return (updates?updateFactor*totalFps/updates:0.f);
}

}		//	time
}		//	aab





