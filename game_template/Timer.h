#pragma once
#include<DxLib.h>
#include"global_config.h"

//同期式タイマー
class Timer
{
private:
	unsigned long long _configured = 0;
	unsigned long long _remaining = 0;
	bool _stop = true;
public:

	Timer(unsigned long long frames) : _configured(frames), _remaining(frames), _stop(false)
	{}

	void setf(unsigned long long frames)noexcept
	{
		_configured = frames;
		_stop = true;
	}

	void sets(double sec)noexcept
	{
		_configured = (unsigned long long)(sec * CtrGlobal.GetFPS());
		_stop = true;
	}

	void start()noexcept
	{
		_remaining = _configured;
		_stop = false;
	}

	void restart()noexcept
	{
		_stop = false;
	}

	void end()noexcept
	{
		_remaining = 0;
		_stop = true;
	}

	void reset()noexcept
	{
		_remaining = _configured;
		_stop = true;
	}

	void clock()noexcept
	{
		if (!_stop && !_remaining)
			--_remaining;
	}

	unsigned long long remaining()noexcept
	{
		return _remaining;
	}

	bool alert()noexcept
	{
		return _remaining == 0;
	}
};

//非同期式タイマー
class nSyncTimer
{
	
};