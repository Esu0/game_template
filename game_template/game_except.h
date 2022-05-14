#pragma once
#include<exception>
#include<DxLib.h>

class get_handle_failed : public std::exception
{
public:
	get_handle_failed()noexcept : std::exception("画像、音楽、フォントなどの読み込み失敗", 1)
	{}
};

void expect(int e);