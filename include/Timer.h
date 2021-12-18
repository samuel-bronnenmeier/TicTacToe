#ifndef SDL_H
#define SDL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif

#ifndef TIMER_H
#define TIMER_H

class LTimer
{
	public:
		//Initialize variables
		LTimer();

		//the various timer options
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets timer's time
		Uint32 getTicks();

		//Checks status of the timer
		bool isStarted();
		bool isPaused();

	private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

#endif