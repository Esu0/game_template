#pragma once
#include<exception>
#include<DxLib.h>

class get_handle_failed : public std::exception
{
public:
	get_handle_failed()noexcept : std::exception("�摜�A���y�A�t�H���g�Ȃǂ̓ǂݍ��ݎ��s", 1)
	{}
};

void expect(int e);