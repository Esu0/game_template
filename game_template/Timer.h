#pragma once
#include<DxLib.h>
#include"global_config.h"

//同期式タイマー
class Timer
{
private:
	unsigned long long _configured = 0;
	unsigned long long _started = 0xffffffffffffffff;
public:
	Timer()
	{}

	Timer(unsigned long long frames) : _configured(frames), _started(CtrGlobal.GetFrame())
	{}

	void setf(unsigned long long frames)noexcept
	{
		_configured = frames;
	}

	void sets(double sec)noexcept
	{
		_configured = (unsigned long long)(sec * CtrGlobal.GetFPS());
	}

	void start()noexcept
	{
		_started = CtrGlobal.GetFrame();
	}

	void restart()noexcept
	{
		_started = CtrGlobal.GetFrame();
	}

	void end()noexcept
	{
		_started = 0xffffffffffffffff;
	}

	void reset()noexcept
	{
		_started = 0xffffffffffffffff;
	}

	unsigned long long remaining()noexcept
	{
		if (_started != 0xffffffffffffffff && _started + _configured > CtrGlobal.GetFrame())
			return _configured - CtrGlobal.GetFrame() + _started;
		else return 0;
	}

	bool alert()noexcept
	{
		return _started != 0xffffffffffffffff && _configured <= CtrGlobal.GetFrame() - _started;
	}

	bool Enabled()noexcept
	{
		return _started != 0xffffffffffffffff;
	}
};

//非同期式タイマー
class nSyncTimer
{
	
};