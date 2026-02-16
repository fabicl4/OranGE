#pragma once

#include "defines.h"

class Clock
{
public:
	// The constructor does not start the clock.
	// Sets to zero the variables.
	Clock();

	f64 GetStartTime() const noexcept;
	f64 GetElapsed() const noexcept;

	// Updates clock. Should be called just bedore checking elapsed time.
	// Has no effect on non-started clocks.
	void Update();

	// Starts the clock. Resets elapsed time.
	void Start();

	// Stops the clock. Does not reset elapsed time.
	void Stop();

private:
	f64 m_startTime;
	f64 m_elapsed;

	bool m_stopped;
};

