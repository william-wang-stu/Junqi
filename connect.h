#pragma once
#include "game.h"
#include "chess.h"

/*
��������ڽ���֮��Ľ�������
*/
class Chess;
class Movement;
class Connect
{
public:
	void Init();
	int Get_Board(Chess &Board);
	void Send_Move(Movement Move);
};