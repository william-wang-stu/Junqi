#include <iostream>
#include <vector>
#include <cassert>
#include "game.h"
#include "connect.h"

const int ROLE_UPPER = 1;
const int ROLE_LOWER = 0;
const int ROLE_BLANK = -1;

/*
input:
例如: Junqi.exe –-role 1 –-time 60
	注： 参数role：0表示红方、1表示黑方。
		参数time：表示单步决策时间，单位秒。

output:

function:
	设置Game类中的Role和Time_Limit
*/

void Game::Arg_Init(int argc, char* argv[])
{
	Role = atoi(argv[2]);
	Time_Limit = atoi(argv[4]);
}


/*
input:
	depth	搜索深度

output:
	Move	最优下子方案

function:
	进行搜索确定最优下子方案
*/
Movement Game::Search(Chess Board, int Depth)
{

	int alpha = -INF;
	int beta = INF;

	Eval_Move Ret = _Search(Board, Depth, alpha, beta, PlayerType::MaximizingPlayer, Role);


	return Ret.second.back();
}



/*
input:
	Cur_Role	执子方

output:
	Opp_Role	交换执子方

function:

	返回交换执子状态
*/

static int Oppsite_Role(int Cur_Role)
{
	int Opp_Role = 0;

	if (!Cur_Role)
		Opp_Role = 1;

	return Opp_Role;
}

/*
input:
	Cur_Board	当前棋盘
	Depth		当前深度
	Alpha		Alpha参数
	Beta		Beta参数
	Player		PlayerType MaximizingPlayer/MinimizingPlayer
	Cur_Role		执子方

output:
	Eval_Move		_Search函数返回值
		Eval		当前估值
		Move_His	当前最优的移动路径

function:
	进行mimmax搜索，并使用alpha-beta剪枝，返回最优的下子路径，和最优的解
*/
Eval_Move Game::_Search(Chess Cur_Board, int Depth, int Alpha, int Beta, PlayerType Player, int Cur_Role)
{
	if (Depth == 0 || Cur_Board.Is_Over(Cur_Role))
	{
		//	Eval函数始终返回的机器执子方的最优解
		return std::make_pair(Cur_Board.Evaluate_Chess(this->Role), std::vector<Movement>());
	}

	Connect Con;

	//	std::cout << "Depth" << Depth << "Alpha" << Alpha << "Beta" << Beta << std::endl;
	//	极大化当前Eval的Player
	if (Player == PlayerType::MaximizingPlayer)
	{
		int Max_Eval = -INF;
		std::vector<Movement> Best_Move;
		std::vector<Movement> Move = Cur_Board.Search_Movement(Cur_Role, Player);

		for (std::vector<Movement>::iterator iter = Move.begin(); iter != Move.end(); iter++)
		{
			Movement V = *iter;
			//	Con.Send_Move(V);测试用
			Chess Next_Board = Cur_Board.Apply_Move(V);
			//std::cout << "Eval:" << (Next_Board.Evaluate_Chess(Role)) << std::endl;
			Eval_Move Ret = _Search(Next_Board, Depth - 1, Alpha, Beta, PlayerType::MinimizingPlayer, Oppsite_Role(Cur_Role));

			int Eval = Ret.first;
			std::vector<Movement> Move_His = Ret.second;

			if (Depth == 4)
			{
				std::cout << "Depth == 4 " << (char)('A' + 12 - V.From.x) << V.From.y << " " << (char)('A' + 12 - V.To.x) << V.To.y << " " << Eval << std::endl;;
				//getchar(); getchar();
				//Cur_Board.Display();
			}


			if (Eval > Max_Eval)
			{
				Max_Eval = Eval;
				Best_Move = Move_His;
				Best_Move.push_back(V);

				Alpha = (Eval > Alpha) ? Eval : Alpha;
				if (Beta <= Alpha)
					break;
			}
		}
		return std::make_pair(Max_Eval, Best_Move);
	}
	//	极小化当前Eval的Player
	if (Player == PlayerType::MinimizingPlayer)
	{
		int Min_Eval = INF;
		std::vector<Movement> Best_Move;
		std::vector<Movement> Move = Cur_Board.Search_Movement(Cur_Role,Player);

		for (std::vector<Movement>::iterator iter = Move.begin(); iter != Move.end(); iter++)
		{
			Movement V = *iter;
			//	Con.Send_Move(V);测试用
			Chess Next_Board = Cur_Board.Apply_Move(V);
			Eval_Move Ret = _Search(Next_Board, Depth - 1, Alpha, Beta, PlayerType::MaximizingPlayer, Oppsite_Role(Cur_Role));

			int Eval = Ret.first;
			std::vector<Movement> Move_His = Ret.second;



			if (Eval < Min_Eval)
			{
				Min_Eval = Eval;
				Best_Move = Move_His;
				Best_Move.push_back(V);

				Beta = (Eval < Beta) ? Eval : Beta;
				if (Beta <= Alpha)
					break;
			}
		}
		return std::make_pair(Min_Eval, Best_Move);
	}


	//	non-existent situation
	assert(false);
	return std::make_pair(0, std::vector<Movement>());
}


