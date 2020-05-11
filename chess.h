#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include "game.h"
#include "connect.h"
#include "cmd_console_tools.h"

//	���̵Ĵ�С
static const int Chess_H = 13;
static const int Chess_W = 5;

class Movement;
class Coord;
class Connect;
extern const int ROLE_BLANK;
extern const int ROLE_LOWER;
extern const int ROLE_UPPER;

//�ȼ��ж���Ҫ
const char RANK[] = "AJSVTYLPGF";
const char BLANK = ' ';

#define UNDER -1
#define ABOVE 1
#define SAME_RANK 0


/*
�洢��ʽ����Word��һ���������ô�д��������Сд��
*/
class Chess
{
private:
	std::vector<std::vector<char> >  Board;
	int Rank_Judgement(char a, char b);
public:
	Chess()
	{
		Board.resize(Chess_H);
		for (int i = 0; i < Chess_H; i++)
			Board[i].resize(Chess_W);
	}
	Chess(std::vector<std::vector<char> >  board_data)
	{
		Board.resize(Chess_H);
		for (int i = 0; i < Chess_H; i++) {
			Board[i].resize(Chess_W);
			Board[i] = board_data[i];
		}
	}
	bool Is_Over(const int& Role);
	int Evaluate_Chess(const int& Role);
	std::vector<Movement>  Search_Movement(const int& State);
	Chess Apply_Move(const Movement& V);
	void Display();
	bool Is_Movable(Movement M);

	void Set_Board(int x, int y, int ch);
};

const int frontEndPos = 7;	//	ǰ��λ��
//	����������Ӧλ�õ���ɫ
inline int isColor(int linePos);
//	������
inline void common_draw_background(const Coord sizeofall, bool border, bool solid, bool display, const Coord cursor);
//	������
inline void Display_Chess(std::vector<std::vector<char> >  Board, class Coord sizeofall, bool border, bool display);


//	��·λ��
const bool Railway[Chess_H][Chess_W]{
	{0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
	{1, 0, 1, 0, 1},
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0}
};

//	��Ӫλ��
const bool Station[Chess_H][Chess_W]{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
};


//	���������ĸ�����
const int HV_DirectX[4] = { 1,0,0,-1 };
const int HV_DirectY[4] = { 0,1,-1,0 };

//	�ԽǷ���
const int Cross_DirectX[4] = { 1,1,-1,-1 };
const int Cross_DirectY[4] = { 1,-1,1,-1 };


//	��·λ��
//	��·��ͨ����
enum class HighwayConn { full, half, none };

//	·����ͨ����
enum class ConnWay { Railway, Highway, none };


//	˾��*1������*1��ʦ��*2���ó�*2���ų�*2��Ӫ��*2������*3���ų�*3������*3������*3��ը��*2������*1�� ��25ö
const int chessClassNum = 12;
enum class chessClass { none, zhadan, dilei, junqi, gongbing, pai, lian, ying, tuan, lv, shi, jun, siling };


//	�ַ�

const std::map<char, chessClass> chessMap{
	{BLANK,chessClass::none},
	{'a',chessClass::siling},
	{'A',chessClass::siling},
	{'j',chessClass::jun},
	{'J',chessClass::jun},
	{'s',chessClass::shi},
	{'S',chessClass::shi},
	{'v',chessClass::lv},
	{'V',chessClass::lv},
	{'t',chessClass::tuan},
	{'T',chessClass::tuan},
	{'y',chessClass::ying},
	{'Y',chessClass::ying},
	{'l',chessClass::lian},
	{'L',chessClass::lian},
	{'p',chessClass::pai},
	{'P',chessClass::pai},
	{'g',chessClass::gongbing},
	{'G',chessClass::gongbing},
	{'d',chessClass::dilei},
	{'D',chessClass::dilei},
	{'z',chessClass::zhadan},
	{'Z',chessClass::zhadan},
	{'f',chessClass::junqi},
	{'F',chessClass::junqi}
};







//	���̸�������
enum class BoardClass {
	camp,		//	��ͨ��Ӫ
	frontline,		//	ǰ��
	station,		//	��Ӫ
	headquarter,		//	��Ӫ
	empty,		//	���������򣬳��Ӻ���֮��
};

//	���̲���
const int Field[Chess_H][Chess_W] = {
	{(int)BoardClass::camp, (int)BoardClass::headquarter,(int)BoardClass::camp,(int)BoardClass::headquarter,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::frontline, (int)BoardClass::empty,(int)BoardClass::frontline,(int)BoardClass::empty,(int)BoardClass::frontline},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::station,(int)BoardClass::camp,(int)BoardClass::station,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp,(int)BoardClass::camp},
	{(int)BoardClass::camp, (int)BoardClass::headquarter,(int)BoardClass::camp,(int)BoardClass::headquarter,(int)BoardClass::camp}
};
