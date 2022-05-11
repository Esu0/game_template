#pragma once
#include<exception>

class get_handle_failed : public std::exception
{
public:
	get_handle_failed()noexcept : std::exception("画像、音楽、フォントなどの読み込み失敗", 1)
	{}
};