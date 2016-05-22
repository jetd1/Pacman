/*
* Edited By Jet, Moriarty, weaZen
* 2016/05/10 22:39
* AI XXXXX
*
* Pacman 样例程序
* 作者：zhouhy
* 时间：2016/3/22 15:32:51
* 最后更新：2016/4/22 16:18
*/

#include <fstream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <stdexcept>
#include <vector>
#include <list>
#include <set>
#include <climits>
#include "jsoncpp/json.h"

#define FIELD_MAX_HEIGHT 20
#define FIELD_MAX_WIDTH 20
#define MAX_HOTSPOT_COUNT 32
#define MAX_GENERATOR_COUNT 4 // 每个象限1
#define MAX_PLAYER_COUNT 4
#define MAX_TURN 100
#define TIME_LIMIT 0.95
#define QUEUE_MAX 121
#define MAX_INT 0x3fffffff
#define DEFAULT_DEPTH 1
#define MAX_DEPTH 20
#define DEATH_EVAL -1000000
#define INVALID_EVAL -9999999

//#define DEBUG
#define PROFILING
#define SAVEDATA

// 你也可以选用 using namespace std; 但是会污染命名空间
using std::cin;
using std::cout;
using std::endl;
using std::swap;
using std::string;
using std::getline;
using std::to_string;
using std::runtime_error;


// 用于调试
namespace Debug
{
	auto printInfo = false;
	string presetString;
#ifdef DEBUG
	//presetString = R"*({"requests":[{"GENERATOR_INTERVAL":20,"LARGE_FRUIT_DURATION":10,"LARGE_FRUIT_ENHANCEMENT":10,"content":[[0,16,16,32,0,16,0,32,16,16,0],[0,0,1,0,0,0,0,0,2,0,0],[16,0,0,0,16,0,16,0,0,0,16],[0,0,16,0,0,0,0,0,16,0,0],[16,16,0,0,0,0,0,0,0,16,16],[16,16,0,0,0,0,0,0,0,16,16],[0,0,16,0,0,0,0,0,16,0,0],[16,0,0,0,16,0,16,0,0,0,16],[0,0,4,0,0,0,0,0,8,0,0],[0,16,16,32,0,16,0,32,16,16,0]],"height":10,"id":3,"seed":1462548363,"static":[[2,10,13,5,5,1,5,5,7,10,8],[8,6,9,5,1,4,1,5,3,12,2],[4,5,6,9,6,31,12,3,12,5,4],[1,7,9,6,13,1,7,12,3,13,1],[8,5,0,1,5,4,5,1,0,5,2],[8,5,0,4,5,1,5,4,0,5,2],[4,7,12,3,13,4,7,9,6,13,4],[1,5,3,12,3,31,9,6,9,5,1],[8,3,12,5,4,1,4,5,6,9,2],[2,10,13,5,5,4,5,5,7,10,8]],"width":11},{"0":{"action":1},"1":{"action":2},"2":{"action":1},"3":{"action":0}},{"0":{"action":1},"1":{"action":1},"2":{"action":1},"3":{"action":1}},{"0":{"action":2},"1":{"action":1},"2":{"action":0},"3":{"action":1}},{"0":{"action":3},"1":{"action":1},"2":{"action":3},"3":{"action":1}},{"0":{"action":2},"1":{"action":3},"2":{"action":0},"3":{"action":3}},{"0":{"action":3},"1":{"action":1},"2":{"action":3},"3":{"action":1}},{"0":{"action":2},"1":{"action":3},"2":{"action":0},"3":{"action":3}},{"0":{"action":3},"1":{"action":1},"2":{"action":3},"3":{"action":1}},{"0":{"action":3},"1":{"action":3},"2":{"action":3},"3":{"action":3}},{"0":{"action":0},"1":{"action":1},"2":{"action":2},"3":{"action":1}},{"0":{"action":3},"1":{"action":3},"2":{"action":3},"3":{"action":3}},{"0":{"action":2},"1":{"action":1},"2":{"action":0},"3":{"action":1}},{"0":{"action":3},"1":{"action":3},"2":{"action":3},"3":{"action":3}},{"0":{"action":3},"1":{"action":1},"2":{"action":3},"3":{"action":1}},{"0":{"action":0},"1":{"action":3},"2":{"action":2},"3":{"action":3}},{"0":{"action":3},"1":{"action":1},"2":{"action":3},"3":{"action":1}},{"0":{"action":0},"1":{"action":3},"2":{"action":2},"3":{"action":3}},{"0":{"action":3},"1":{"action":1},"2":{"action":3},"3":{"action":1}},{"0":{"action":0},"1":{"action":3},"2":{"action":2},"3":{"action":3}},{"0":{"action":3},"1":{"action":1},"2":{"action":3},"3":{"action":1}},{"0":{"action":3},"1":{"action":3},"2":{"action":3},"3":{"action":3}},{"0":{"action":2},"1":{"action":1},"2":{"action":1},"3":{"action":1}},{"0":{"action":0},"1":{"action":3},"2":{"action":2},"3":{"action":3}},{"0":{"action":1},"1":{"action":1},"2":{"action":-1},"3":{"action":1}},{"0":{"action":1},"1":{"action":3},"2":{"action":3},"3":{"action":3}},{"0":{"action":3},"1":{"action":1},"2":{"action":3},"3":{"action":1}},{"0":{"action":0},"1":{"action":3},"2":{"action":-1},"3":{"action":3}},{"0":{"action":1},"1":{"action":1},"2":{"action":-1},"3":{"action":1}},{"0":{"action":1},"1":{"action":3},"2":{"action":1},"3":{"action":3}},{"0":{"action":1},"1":{"action":1},"2":{"action":-1},"3":{"action":1}},{"0":{"action":3},"1":{"action":3},"2":{"action":1},"3":{"action":3}}],"responses":[{"action":0,"tauntText":""},{"action":1,"tauntText":""},{"action":1,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""},{"action":1,"tauntText":""},{"action":3,"tauntText":""}]})*";
#endif

	Json::Value debugData;
	auto timeOutFlag = false;
	auto startTime = clock();

	inline double TimeThrough(clock_t stt = startTime)
	{
		return double(clock() - stt) / CLOCKS_PER_SEC;
	}

	inline bool TimeOut()
	{
#ifdef DEBUG
		return false;
#endif
		if (timeOutFlag)
			return true;
		if (TimeThrough() > TIME_LIMIT)
		{
			debugData["profiling"]["TimeOut"] = true;
			return timeOutFlag = true;
		}
		return false;
	}
}

//把枚举扩展收起来
namespace EnumExt
{
	// 让枚举也可以用这些运算了（不加会编译错误）
	template<typename T>
	inline T operator |=(T &a, const T &b)
	{
		return a = static_cast<T>(static_cast<int>(a) | static_cast<int>(b));
	}
	template<typename T>
	inline T operator |(const T &a, const T &b)
	{
		return static_cast<T>(static_cast<int>(a) | static_cast<int>(b));
	}
	template<typename T>
	inline T operator &=(T &a, const T &b)
	{
		return a = static_cast<T>(static_cast<int>(a) & static_cast<int>(b));
	}
	template<typename T>
	inline T operator &(const T &a, const T &b)
	{
		return static_cast<T>(static_cast<int>(a) & static_cast<int>(b));
	}
	template<typename T>
	inline T operator ++(T &a)
	{
		return a = static_cast<T>(static_cast<int>(a) + 1);
	}
	template<typename T>
	inline T operator ~(const T &a)
	{
		return static_cast<T>(~static_cast<int>(a));
	}
}

// 平台提供的吃豆人相关逻辑处理程序
namespace Pacman
{
	using namespace EnumExt;

	const auto seed = time(nullptr);
	const int dx[] = { 0, 1, 0, -1, 1, 1, -1, -1 }, dy[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
	const string dirStr[] = { "stay" ,"up","right","down","left","ur","dr","dl","ul" };

	// 枚举定义；使用枚举虽然会浪费空间（sizeof(GridContentType) == 4），但是计算机处理32位的数字效率更高

	// 每个格子可能变化的内容，会采用“或”逻辑进行组合
	enum GridContentType
	{
		empty = 0, // 其实不会用到
		player1 = 1, // 1号玩家
		player2 = 2, // 2号玩家
		player3 = 4, // 3号玩家
		player4 = 8, // 4号玩家
		playerMask = 1 | 2 | 4 | 8, // 用于检查有没有玩家等
		smallFruit = 16, // 小豆子
		largeFruit = 32 // 大豆子
	};

	// 用玩家ID换取格子上玩家的二进制位
	GridContentType playerID2Mask[] = { player1, player2, player3, player4 };
	string playerID2str[] = { "0", "1", "2", "3" };

	// 每个格子固定的东西，会采用“或”逻辑进行组合
	enum GridStaticType
	{
		emptyWall = 0, // 其实不会用到
		wallNorth = 1, // 北墙（纵坐标减少的方向）
		wallEast = 2, // 东墙（横坐标增加的方向）
		wallSouth = 4, // 南墙（纵坐标增加的方向）
		wallWest = 8, // 西墙（横坐标减少的方向）
		generator = 16 // 豆子产生器
	};

	// 用移动方向换取这个方向上阻挡着的墙的二进制位
	GridStaticType direction2OpposingWall[] = { wallNorth, wallEast, wallSouth, wallWest };

	// 方向，可以代入dx、dy数组，同时也可以作为玩家的动作
	enum Direction
	{
		stay = -1,
		up = 0,
		right = 1,
		down = 2,
		left = 3,
		// 下面的这几个只是为了产生器程序方便，不会实际用到
		ur = 4, // 右上
		dr = 5, // 右下
		dl = 6, // 左下
		ul = 7 // 左上
	};

	// 场地上带有坐标的物件
	struct FieldProp
	{
		int row, col;
		FieldProp(int i = 0, int j = 0) : row(i), col(j) {}
		bool operator==(const FieldProp &a)const { return (row == a.row && col == a.col); }
		bool operator!=(const FieldProp &a)const { return (row != a.row || col != a.col); }
		bool operator>(const FieldProp &a)const { return (row == a.row ? col > a.col : row > a.row); }
		bool operator<(const FieldProp &a)const { return (row == a.row ? col < a.col : row < a.row); }
	};

	struct PathInfoType : FieldProp
	{
		bool isImpasse;
		bool isExit;
		int fleeLength;//到死路出口的距离
		int impasseDepth;//死路最大深度
		PathInfoType * pExit;
		PathInfoType(int y = 0, int x = 0) : FieldProp(y, x), isImpasse(false), isExit(false), fleeLength(0), impasseDepth(0), pExit(nullptr) {}
	};

	struct GenInfoType : FieldProp
	{
		bool isBesideGen;
		int fruitClusterCount;
		GenInfoType(int y = 0, int x = 0) : FieldProp(y, x), isBesideGen(false), fruitClusterCount(0) {}
	};

	// 场地上的玩家
	struct Player : FieldProp
	{
		int strength;
		int powerUpLeft;
		bool dead;
	};

	// 回合新产生的豆子的坐标
	struct NewFruits
	{
		FieldProp newFruits[MAX_GENERATOR_COUNT * 8];
		int newFruitCount;
	} newFruits[MAX_TURN];
	int newFruitsCount = 0;

	// 状态转移记录结构
	struct TurnStateTransfer
	{
		enum StatusChange // 可组合
		{
			none = 0,
			ateSmall = 1,
			ateLarge = 2,
			powerUpCancel = 4,
			die = 8,
			error = 16
		};

		// 玩家选定的动作
		Direction actions[MAX_PLAYER_COUNT];

		// 此回合该玩家的状态变化
		StatusChange change[MAX_PLAYER_COUNT];

		// 此回合该玩家的力量变化
		int strengthDelta[MAX_PLAYER_COUNT];
	};

	// 游戏主要逻辑处理类，包括输入输出、回合演算、状态转移，全局唯一
	class GameField
	{
		// 为了方便，大多数属性都不是private的
		// 记录每回合的变化（栈）
		TurnStateTransfer backtrack[MAX_TURN];

		// 这个对象是否已经创建
		static bool constructed;

	public:
		// 场地的长和宽
		int height, width;
		int generatorCount, hotSpotCount;
		int GENERATOR_INTERVAL, LARGE_FRUIT_DURATION, LARGE_FRUIT_ENHANCEMENT;

		//道路信息
		PathInfoType pathInfo[FIELD_MAX_HEIGHT][FIELD_MAX_WIDTH];
		FieldProp hotSpot[MAX_HOTSPOT_COUNT];
		GenInfoType genInfo[FIELD_MAX_HEIGHT][FIELD_MAX_WIDTH];
		int maxCluster;

		// 场地格子固定的内容
		GridStaticType fieldStatic[FIELD_MAX_HEIGHT][FIELD_MAX_WIDTH];

		// 场地格子会变化的内容
		GridContentType fieldContent[FIELD_MAX_HEIGHT][FIELD_MAX_WIDTH];
		int generatorTurnLeft; // 多少回合后产生豆子
		int aliveCount; // 有多少玩家存活
		int smallFruitCount;
		FieldProp generators[MAX_GENERATOR_COUNT]; // 有哪些豆子产生器
		Player players[MAX_PLAYER_COUNT]; // 有哪些玩家
		int turnID;
		Direction actions[MAX_PLAYER_COUNT]; // 玩家选定的动作
		bool hasNext; // weaZen：省得每次查一遍

					  // 恢复到上次场地状态。可以一路恢复到最开始。
					  // 恢复失败（没有状态可恢复）返回false
		char distance[FIELD_MAX_HEIGHT][FIELD_MAX_WIDTH][FIELD_MAX_HEIGHT][FIELD_MAX_WIDTH]{};

		bool PopState()
		{
			hasNext = true;
			if (turnID <= 0)
				return false;

			const auto &bt = backtrack[--turnID];

			// 倒着来恢复状态
			for (int playerID = 0; playerID < MAX_PLAYER_COUNT; playerID++)
			{
				auto &player = players[playerID];
				auto &content = fieldContent[player.row][player.col];
				auto change = bt.change[playerID];

				if (!player.dead)
				{
					// 5. 大豆回合恢复
					if (player.powerUpLeft || change & TurnStateTransfer::powerUpCancel)
						player.powerUpLeft++;

					// 4. 吐出豆子
					if (change & TurnStateTransfer::ateSmall)
					{
						content |= smallFruit;
						smallFruitCount++;
					}
					else if (change & TurnStateTransfer::ateLarge)
					{
						content |= largeFruit;
						player.powerUpLeft -= LARGE_FRUIT_DURATION;
					}
				}

				// 2. 魂兮归来
				if (change & TurnStateTransfer::die)
				{
					player.dead = false;
					aliveCount++;
					content |= playerID2Mask[playerID];
				}

				// 1. 移形换影
				if (!player.dead && bt.actions[playerID] != stay)
				{
					fieldContent[player.row][player.col] &= ~playerID2Mask[playerID];
					player.row = (player.row - dy[bt.actions[playerID]] + height) % height;
					player.col = (player.col - dx[bt.actions[playerID]] + width) % width;
					fieldContent[player.row][player.col] |= playerID2Mask[playerID];
				}

				// 0. 救赎不合法的灵魂
				if (change & TurnStateTransfer::error)
				{
					player.dead = false;
					aliveCount++;
					content |= playerID2Mask[playerID];
				}

				// *. 恢复力量
				if (!player.dead)
					player.strength -= bt.strengthDelta[playerID];
			}

			// 3. 收回豆子
			if (generatorTurnLeft == GENERATOR_INTERVAL)
			{
				generatorTurnLeft = 1;
				auto &fruits = newFruits[--newFruitsCount];
				for (int i = 0; i < fruits.newFruitCount; i++)
				{
					fieldContent[fruits.newFruits[i].row][fruits.newFruits[i].col] &= ~smallFruit;
					smallFruitCount--;
				}
			}
			else
				generatorTurnLeft++;

			return true;
		}

		// Jet:把PopState包装了一下 方便一些
		void RollBack(int turnCount = -1)
		{
#ifdef PROFILING
			auto&& startTime = clock();
#endif
			if (turnCount < 0)
				// ReSharper disable once CppPossiblyErroneousEmptyStatements
				while (PopState());
			else
				for (int i = 0; i < turnCount; i++)
					if (!PopState())
						break;
#ifdef PROFILING
			auto& d = Debug::debugData["profiling"]["RollBack()"];
			d = d.asDouble() + double(clock() - startTime) / CLOCKS_PER_SEC;
#endif
		}

		// 判断指定玩家向指定方向移动是不是合法的（没有撞墙且没有踩到豆子产生器）
		inline bool ActionValid(int playerID, const Direction &dir) const
		{
			if (dir == stay)
				return true;
			const auto &p = players[playerID];
			const auto &s = fieldStatic[p.row][p.col];
			return dir >= -1 && dir < 4 && !(s & direction2OpposingWall[dir]);
		}

		// 在向actions写入玩家动作后，演算下一回合局面，并记录之前所有的场地状态，可供日后恢复。
		// 是终局的话就返回false
		bool NextTurn()
		{
#ifdef PROFILING
			auto&& startTime = clock();
#endif
			auto &bt = backtrack[turnID];
			memset(&bt, 0, sizeof bt);

			// 0. 杀死不合法输入
			for (int playerID = 0; playerID < MAX_PLAYER_COUNT; playerID++)
			{
				auto &player = players[playerID];
				if (!player.dead)
				{
					auto &action = actions[playerID];
					if (action == stay)
						continue;

					if (!ActionValid(playerID, action))
					{
						bt.strengthDelta[playerID] += -player.strength;
						bt.change[playerID] = TurnStateTransfer::error;
						fieldContent[player.row][player.col] &= ~playerID2Mask[playerID];
						player.strength = 0;
						player.dead = true;
						aliveCount--;
					}
					else
					{
						// 遇到比自己强♂壮的玩家是不能前进的
						const auto& target = fieldContent
							[(player.row + dy[action] + height) % height]
						[(player.col + dx[action] + width) % width];
						if (target & playerMask)
							for (int i = 0; i < MAX_PLAYER_COUNT; i++)
								if (target & playerID2Mask[i] && players[i].strength > player.strength)
									action = stay;
					}
				}
			}

			// 1. 位置变化
			for (int playerID = 0; playerID < MAX_PLAYER_COUNT; playerID++)
			{
				auto &player = players[playerID];
				if (player.dead)
					continue;

				bt.actions[playerID] = actions[playerID];

				if (actions[playerID] == stay)
					continue;

				// 移动
				fieldContent[player.row][player.col] &= ~playerID2Mask[playerID];
				player.row = (player.row + dy[actions[playerID]] + height) % height;
				player.col = (player.col + dx[actions[playerID]] + width) % width;
				fieldContent[player.row][player.col] |= playerID2Mask[playerID];
			}

			// 2. 玩家互殴
			for (int playerID = 0; playerID < MAX_PLAYER_COUNT; playerID++)
			{
				auto &player = players[playerID];
				if (player.dead)
					continue;

				// 判断是否有玩家在一起
				int containedCount = 0;
				int containedPlayers[MAX_PLAYER_COUNT];
				for (int i = 0; i < MAX_PLAYER_COUNT; i++)
					if (fieldContent[player.row][player.col] & playerID2Mask[i])
						containedPlayers[containedCount++] = i;

				if (containedCount > 1)
				{
					// NAIVE
					for (int i = 0; i < containedCount; i++)
						for (int j = 0; j < containedCount - i - 1; j++)
							if (players[containedPlayers[j]].strength < players[containedPlayers[j + 1]].strength)
								swap(containedPlayers[j], containedPlayers[j + 1]);

					int begin;
					for (begin = 1; begin < containedCount; begin++)
						if (players[containedPlayers[begin - 1]].strength > players[containedPlayers[begin]].strength)
							break;

					// 这些玩家将会被杀死
					int lootedStrength = 0;
					for (int i = begin; i < containedCount; i++)
					{
						int id = containedPlayers[i];
						Player &p = players[id];

						// 从格子上移走
						fieldContent[p.row][p.col] &= ~playerID2Mask[id];
						p.dead = true;
						int drop = p.strength / 2;
						bt.strengthDelta[id] += -drop;
						bt.change[id] |= TurnStateTransfer::die;
						lootedStrength += drop;
						p.strength -= drop;
						aliveCount--;
					}

					// 分配给其他玩家
					auto inc = lootedStrength / begin;
					for (int i = 0; i < begin; i++)
					{
						auto id = containedPlayers[i];
						auto &p = players[id];
						bt.strengthDelta[id] += inc;
						p.strength += inc;
					}
				}
			}

			// 3. 产生豆子
			if (--generatorTurnLeft == 0)
			{
				generatorTurnLeft = GENERATOR_INTERVAL;
				auto &fruits = newFruits[newFruitsCount++];
				fruits.newFruitCount = 0;
				for (int i = 0; i < generatorCount; i++)
					for (auto d = up; d < 8; ++d)
					{
						// 取余，穿过场地边界
						int r = (generators[i].row + dy[d] + height) % height, c = (generators[i].col + dx[d] + width) % width;
						if (fieldStatic[r][c] & generator || fieldContent[r][c] & (smallFruit | largeFruit))
							continue;
						fieldContent[r][c] |= smallFruit;
						fruits.newFruits[fruits.newFruitCount].row = r;
						fruits.newFruits[fruits.newFruitCount++].col = c;
						smallFruitCount++;
					}
			}

			// 4. 吃掉豆子
			for (int playerID = 0; playerID < MAX_PLAYER_COUNT; playerID++)
			{
				auto &player = players[playerID];
				if (player.dead)
					continue;

				auto &content = fieldContent[player.row][player.col];

				// 只有在格子上只有自己的时候才能吃掉豆子
				if (content & playerMask & ~playerID2Mask[playerID])
					continue;

				if (content & smallFruit)
				{
					content &= ~smallFruit;
					player.strength++;
					bt.strengthDelta[playerID]++;
					smallFruitCount--;
					bt.change[playerID] |= TurnStateTransfer::ateSmall;
				}
				else if (content & largeFruit)
				{
					content &= ~largeFruit;
					if (player.powerUpLeft == 0)
					{
						player.strength += LARGE_FRUIT_ENHANCEMENT;
						bt.strengthDelta[playerID] += LARGE_FRUIT_ENHANCEMENT;
					}
					player.powerUpLeft += LARGE_FRUIT_DURATION;
					bt.change[playerID] |= TurnStateTransfer::ateLarge;
				}
			}

			// 5. 大豆回合减少
			for (int playerID = 0; playerID < MAX_PLAYER_COUNT; playerID++)
			{
				auto &player = players[playerID];
				if (player.dead)
					continue;

				if (player.powerUpLeft > 0 && --player.powerUpLeft == 0)
				{
					player.strength -= LARGE_FRUIT_ENHANCEMENT;
					bt.change[playerID] |= TurnStateTransfer::powerUpCancel;
					bt.strengthDelta[playerID] += -LARGE_FRUIT_ENHANCEMENT;
				}
			}

			++turnID;
#ifdef PROFILING
			auto&& d = Debug::debugData["profiling"]["NextTurn()"];
			d = d.asDouble() + double(clock() - startTime) / CLOCKS_PER_SEC;
#endif
			// 是否只剩一人？
			if (aliveCount <= 1)
			{
				for (int playerID = 0; playerID < MAX_PLAYER_COUNT; playerID++)
					if (!players[playerID].dead)
					{
						bt.strengthDelta[playerID] += smallFruitCount;
						players[playerID].strength += smallFruitCount;
					}
				return hasNext = false;
			}

			// 是否回合超限？
			if (turnID >= 100)
				return hasNext = false;
			return hasNext = true;
		}

		// 获取row, col位置的水果估值
		inline char GetFruitValue(int row, int col)const
		{
			char v = 0;
			if (fieldContent[row][col] & smallFruit)
				v += 1;
			if (fieldContent[row][col] & largeFruit)
				v += isSmallMap() ? 10 : 3;
			return v;
		}

		inline bool isSmallMap()const
		{
			return height + width <= 15;
		}

		// weaZen: 双向
		// Jet: 用cc的改的
		char step[FIELD_MAX_HEIGHT][FIELD_MAX_WIDTH];
		char Distance(const FieldProp& startPos, const FieldProp& endPos)
		{
#ifdef PROFILING
			auto startTime = clock();
#endif
			if (startPos == endPos)
				return distance[startPos.row][startPos.col][endPos.row][endPos.col] = 0;

			if (distance[startPos.row][startPos.col][endPos.row][endPos.col])
				return distance[startPos.row][startPos.col][endPos.row][endPos.col];

			if (distance[endPos.row][endPos.col][startPos.row][startPos.col])
				return distance[startPos.row][startPos.col][endPos.row][endPos.col]
				= distance[endPos.row][endPos.col][startPos.row][startPos.col];

			//对死路的优化
			if (pathInfo[startPos.row][startPos.col].isImpasse
				&& !pathInfo[endPos.row][endPos.col].isImpasse)
				return distance[startPos.row][startPos.col][endPos.row][endPos.col]
				= Distance(*pathInfo[startPos.row][startPos.col].pExit, endPos)
				+ pathInfo[startPos.row][startPos.col].fleeLength;

			if (!pathInfo[startPos.row][startPos.col].isImpasse
				&& pathInfo[endPos.row][endPos.col].isImpasse)
				return distance[startPos.row][startPos.col][endPos.row][endPos.col]
				= Distance(startPos, *pathInfo[endPos.row][endPos.col].pExit)
				+ pathInfo[endPos.row][endPos.col].fleeLength;

			if (pathInfo[startPos.row][startPos.col].isImpasse
				&& pathInfo[startPos.row][startPos.col].isImpasse
				&& pathInfo[startPos.row][startPos.col].pExit != pathInfo[startPos.row][startPos.col].pExit)
				return distance[startPos.row][startPos.col][endPos.row][endPos.col]
				= Distance(*pathInfo[startPos.row][startPos.col].pExit, *pathInfo[endPos.row][endPos.col].pExit)
				+ pathInfo[endPos.row][endPos.col].fleeLength
				+ pathInfo[startPos.row][startPos.col].fleeLength;

			//初始化广搜数组
			memset(step, 0, FIELD_MAX_HEIGHT * FIELD_MAX_WIDTH * sizeof(char));

			step[startPos.row][startPos.col] = 1;
			step[endPos.row][endPos.col] = -1;

			//初始化广搜队列
			Pacman::FieldProp queue[QUEUE_MAX];
			queue[0] = startPos;
			queue[1] = endPos;
			auto nowFlag = 0, endFlag = 1;
			auto hasFound = false;
			auto ret = 0;

			while (nowFlag <= endFlag && !hasFound)
			{
				const auto &curGrid = fieldStatic[queue[nowFlag].row][queue[nowFlag].col];
				for (auto dir = Pacman::up; dir < 4; ++dir)
				{
					if (!(curGrid & Pacman::direction2OpposingWall[dir]))
					{
						auto newPos = queue[nowFlag];
						newPos.row = (newPos.row + Pacman::dy[dir] + height) % height;
						newPos.col = (newPos.col + Pacman::dx[dir] + width) % width;
						if (step[queue[nowFlag].row][queue[nowFlag].col] > 0)
						{
							if (step[newPos.row][newPos.col] > step[queue[nowFlag].row][queue[nowFlag].col] + 1 || step[newPos.row][newPos.col] == 0) //新的点是好的
							{
								step[newPos.row][newPos.col] = step[queue[nowFlag].row][queue[nowFlag].col] + 1;
								distance[startPos.row][startPos.col][newPos.row][newPos.col] = step[newPos.row][newPos.col] - 1;
								queue[++endFlag] = newPos;
							}
							if (step[newPos.row][newPos.col] < 0)
							{
								hasFound = true;
								ret = step[queue[nowFlag].row][queue[nowFlag].col] - step[newPos.row][newPos.col] - 1;
							}
						}
						if (step[queue[nowFlag].row][queue[nowFlag].col] < 0)
						{
							if (step[newPos.row][newPos.col] < step[queue[nowFlag].row][queue[nowFlag].col] - 1 || step[newPos.row][newPos.col] == 0) //新的点是好的
							{
								step[newPos.row][newPos.col] = step[queue[nowFlag].row][queue[nowFlag].col] - 1;
								distance[endPos.row][endPos.col][newPos.row][newPos.col] = -step[newPos.row][newPos.col] - 1;
								queue[++endFlag] = newPos;
							}
							if (step[newPos.row][newPos.col] > 0)
							{
								hasFound = true;
								ret = -step[queue[nowFlag].row][queue[nowFlag].col] + step[newPos.row][newPos.col] - 1;
							}
						}
					}
				}
				++nowFlag;
			}

#ifdef PROFILING
			auto&& d = Debug::debugData["profiling"]["Distance()"];
			d = d.asDouble() + double(clock() - startTime) / CLOCKS_PER_SEC;
#endif
			return distance[startPos.row][startPos.col][endPos.row][endPos.col] = ret;
		}

		// Moriartycc: 牢记位运算优先级
		int Distance(int alphaID, int betaID)
		{
			return Distance(players[alphaID], players[betaID]);
		}

		// weaZen: 返回distance<<3 + dir + 1以便决策
		// Jet: 改写了个模版
		Direction dirInfo[FIELD_MAX_HEIGHT][FIELD_MAX_WIDTH];
		template <typename __Pred>
		unsigned char GetTo(int myID, __Pred pr, char forbiddenDirs = '\0')
		{
#ifdef PROFILING
			auto&& startTime = clock();
#endif

			auto startPos = players[myID];
			if (pr(*this, startPos) && !(forbiddenDirs & 1))
				return 0;

			std::vector<std::pair<FieldProp, int> > targetList;

			int initMinDis = MAX_INT;
			int minDis = MAX_INT;
			int tryDis[4] = { MAX_INT,MAX_INT,MAX_INT,MAX_INT };

			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
				{
					if (i == startPos.row && j == startPos.col)
						continue;
					if (pr(*this, FieldProp(i, j)))
					{
						int tmp = int(Distance(startPos, FieldProp(i, j)));
						if (tmp >= initMinDis + 2)
							continue;
						targetList.push_back(std::make_pair(FieldProp(i, j), tmp));
						initMinDis = std::min(initMinDis, tmp);
					}
				}

			if (targetList.empty())
				return ur + 1;

			for (auto i = targetList.begin(); i != targetList.end();)
			{
				if ((*i).second >= initMinDis + 2)
					i = targetList.erase(i);
				else
					++i;
			}

			for (auto d = up; d <= left; ++d)
			{
				if (fieldStatic[startPos.row][startPos.col] & direction2OpposingWall[d])
					continue;
				FieldProp checkPos((startPos.row + dy[d] + height) % height, (startPos.col + dx[d] + width) % width);
				for (auto i = targetList.begin(); i != targetList.end(); ++i)
					tryDis[d] = std::min(tryDis[d], int(Distance(checkPos, (*i).first)));
				minDis = std::min(minDis, tryDis[d]);
			}

			int tmp = 1;
			auto tmpDir = stay;
			for (auto d = up; d <= left; ++d)
				if (tryDis[d] == minDis && !(forbiddenDirs & (1 << (d + 1))))
					tmpDir = tmpDir == stay ? d : ((rand() % ++tmp) ? tmpDir : d);

			if (tmpDir != stay)
			{
#ifdef PROFILING
				auto&& d = Debug::debugData["profiling"]["GetTo()"];
				d = d.asDouble() + double(clock() - startTime) / CLOCKS_PER_SEC;
#endif
				return (minDis << 3) + tmpDir + 1;
			}


			//初始化广搜数组
			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
					dirInfo[i][j] = Pacman::stay;

			memset(step, 31, FIELD_MAX_HEIGHT * FIELD_MAX_WIDTH * sizeof(char));
			step[startPos.row][startPos.col] = 0;

			//初始化广搜队列
			FieldProp queue[QUEUE_MAX];
			queue[0] = startPos;
			char nowFlag = 0, endFlag = 0;
			char dis = 0;
			bool hasEaten = false;

			//初始化随机方向
			Direction randomDir[4];
			for (int i = 0; i < 4; ++i)
				randomDir[i] = Direction(i);

			//禁止的方向设为已经访问
			for (int i = 0; i < 4; ++i)
				if ((forbiddenDirs & (1 << (i + 1))) && !(fieldStatic[startPos.row][startPos.col] & direction2OpposingWall[i]))
					dirInfo[(startPos.row + dy[i] + height) % height][(startPos.col + dx[i] + width) % width] = up;

			while (nowFlag <= endFlag && !hasEaten)
			{
				const auto &curGrid = fieldStatic[queue[nowFlag].row][queue[nowFlag].col];
				for (int i = 0; i < 4; ++i)
					swap(randomDir[rand() % 4], randomDir[rand() % 4]);
				Direction dir;
				for (int i = 0; i < 4; ++i)
				{
					dir = randomDir[i];
					if (!(curGrid & direction2OpposingWall[dir]))
					{
						auto newPos = queue[nowFlag];
						newPos.row = (newPos.row + dy[dir] + height) % height;
						newPos.col = (newPos.col + dx[dir] + width) % width;
						if (dirInfo[newPos.row][newPos.col] == -1 && newPos != startPos)
						{
							if (step[newPos.row][newPos.col] > step[queue[nowFlag].row][queue[nowFlag].col] + 1)
								step[newPos.row][newPos.col] = step[queue[nowFlag].row][queue[nowFlag].col] + 1;
							dirInfo[newPos.row][newPos.col] = dir;
							queue[++endFlag] = newPos;
							if (pr(*this, newPos))
							{
								hasEaten = true;
								dis = step[queue[endFlag].row][queue[endFlag].col];
								break;
							}
						}
					}
				}
				++nowFlag;
			}
			if (!hasEaten)
				return ur + 1;

			//回溯
			auto dir = stay;
			auto curPos = queue[endFlag];
			while (curPos != startPos)
			{
				dir = dirInfo[curPos.row][curPos.col];
				curPos.row = (curPos.row - dy[dir] + height) % height;
				curPos.col = (curPos.col - dx[dir] + width) % width;
			}

#ifdef PROFILING
			auto&& d = Debug::debugData["profiling"]["GetTo()"];
			d = d.asDouble() + double(clock() - startTime) / CLOCKS_PER_SEC;
#endif

			return (dis << 3) + dir + 1;
		}

		//weaZen:照着cc的广搜写了个寻找方向 target是GridContentType里的组合 可以试一下吃人了//ω\\)
		unsigned char GetToTarget(int myID, int target, char forbiddenDirs = '\0')
		{
			if (target == 0)
				return ur + 1;
			return GetTo(myID,
				([target](const GameField& gameField, const FieldProp& pos)
			{
				return gameField.fieldContent[pos.row][pos.col] & target;
			})
				, forbiddenDirs);
		}

		unsigned char GetToTarget(int myID, Pacman::FieldProp target, char forbiddenDirs = '\0')
		{
			if (target.row == -1)
				return ur + 1;
			return GetTo(myID,
				([target](const GameField& gameField, const FieldProp& pos)
			{
				return (pos.row == target.row && pos.col == target.col);
			})
				, forbiddenDirs);
		}

		//weaZen: 把判断是不是在生成器旁边的函数单独拿出来 搜索有用
		// Jet: 没豆子吃的时候去生成器旁边等着
		bool atHotSpot(const FieldProp& pos)
		{
			for (int i = 0; i < hotSpotCount; i++)
				if (pos == hotSpot[i])
					return true;
			return false;
		}

		bool atMaxCluster(const FieldProp& pos)
		{
			return genInfo[pos.row][pos.col].fruitClusterCount == maxCluster;
		}


		unsigned char GetToNearbyGenerator(int myID, char forbiddenDirs = '\0')
		{
			return GetTo(myID, [](const GameField& gameField, const FieldProp& pos)
			{
				return gameField.genInfo[pos.row][pos.col].isBesideGen;
			}, forbiddenDirs);
		}

		unsigned char GetToHotSpot(int myID, char forbiddenDirs = '\0')
		{
			return GetTo(myID, [](const GameField& gameField, const FieldProp& pos)
			{
				for (int i = 0; i < gameField.hotSpotCount; i++)
					if (pos == gameField.hotSpot[i])
						return true;
				return false;
			}, forbiddenDirs);
		}

		unsigned char GetToMaxCluster(int myID, char forbiddenDirs = '\0')
		{
			return  GetTo(myID, [](const GameField& gameField, const FieldProp& pos)
			{
				if (gameField.genInfo[pos.row][pos.col].fruitClusterCount == gameField.maxCluster)
					return true;
				return false;
			}, forbiddenDirs);
		}

		bool isGenerator(const FieldProp& pos)const
		{
			for (int i = 0; i < generatorCount; i++)
				if (pos == generators[generatorCount])
					return true;
			return false;
		}

		bool isBeside(const FieldProp& pos1, const FieldProp& pos2)
		{
			return Distance(pos1, pos2) == 1;
		}

		//weaZen: 地图分析
		//Jet: 分析HOTSPOT
		void MapAnalyze()
		{
#ifdef PROFILING
			auto&& startTime = clock();
#endif
			//分析PathInfo
			FieldProp deadSpot[40];
			int degree[FIELD_MAX_HEIGHT][FIELD_MAX_HEIGHT];
			auto dCount = 0;
			PathInfoType * ptmpExit = nullptr;

			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					pathInfo[y][x].row = y;
					pathInfo[y][x].col = x;
					auto degreeCount = 0;
					for (auto dir = up; dir < 4; ++dir)
						if (!(fieldStatic[y][x] & direction2OpposingWall[dir]))
							++degreeCount;
					degree[y][x] = degreeCount;
					if (degreeCount == 1)
					{
						pathInfo[y][x].isImpasse = true;
						deadSpot[dCount].row = y;
						deadSpot[dCount++].col = x;
					}
				}
			}
			for (int i = 0; i < dCount; ++i)
			{
				auto startPos = deadSpot[i];
				FieldProp queue[QUEUE_MAX];
				queue[0] = startPos;
				auto nowFlag = 0, endFlag = 0;
				while (nowFlag <= endFlag)
				{
					const auto &curGrid = fieldStatic[queue[nowFlag].row][queue[nowFlag].col];
					for (auto dir = up; dir < 4; ++dir)
						if (!(curGrid & direction2OpposingWall[dir]))
						{
							auto newPos = queue[nowFlag];
							newPos.row = (newPos.row + dy[dir] + height) % height;
							newPos.col = (newPos.col + dx[dir] + width) % width;
							--degree[newPos.row][newPos.col];
							if (degree[newPos.row][newPos.col] == 1 && !pathInfo[newPos.row][newPos.col].isImpasse)
							{
								pathInfo[newPos.row][newPos.col].isExit = false;
								pathInfo[newPos.row][newPos.col].isImpasse = true;
								queue[++endFlag] = newPos;
							}
							if (degree[newPos.row][newPos.col] > 1)
							{
								pathInfo[newPos.row][newPos.col].isExit = true;
								pathInfo[newPos.row][newPos.col].pExit = ptmpExit = &pathInfo[newPos.row][newPos.col];
								pathInfo[newPos.row][newPos.col].fleeLength = 0;
							}
						}
					++nowFlag;
				}
				for (auto j = 0; j <= endFlag; ++j)
				{
					pathInfo[queue[j].row][queue[j].col].fleeLength = endFlag - j + 1;
					pathInfo[queue[j].row][queue[j].col].pExit = ptmpExit;
				}
				(*ptmpExit).impasseDepth = endFlag + 1;
			}
			for (auto y = 0; y < height; ++y)
			{
				for (auto x = 0; x < width; ++x)
				{
					if (pathInfo[y][x].isImpasse)
					{
						ptmpExit = pathInfo[y][x].pExit;
						while (ptmpExit != ptmpExit->pExit)
						{
							ptmpExit->pExit->impasseDepth = std::max(ptmpExit->pExit->impasseDepth, ptmpExit->impasseDepth + ptmpExit->fleeLength);
							ptmpExit->impasseDepth = 0;
							pathInfo[y][x].pExit = ptmpExit->pExit;
							pathInfo[y][x].fleeLength += ptmpExit->fleeLength;
							ptmpExit = pathInfo[y][x].pExit;
						}
					}
				}
			}

			//weaZen正在尝试精确分析hotspot
			maxCluster = 0;
			int fruitSpotsCount = 0;
			FieldProp fruitSpots[4 * 8];
			for (int i = 0; i < generatorCount; i++)
				for (auto d = up; d < 8; ++d)
				{
					int tmpy = (generators[i].row + dy[d] + height) % height;
					int tmpx = (generators[i].col + dx[d] + width) % width;
					if ((fieldStatic[tmpy][tmpx] & generator) || genInfo[tmpy][tmpx].isBesideGen)
						continue;
					genInfo[tmpy][tmpx].isBesideGen = true;
					fruitSpots[fruitSpotsCount].row = tmpy;
					fruitSpots[fruitSpotsCount++].col = tmpx;
				}
			for (int i = 0; i < fruitSpotsCount; ++i)
			{
				if (genInfo[fruitSpots[i].row][fruitSpots[i].col].fruitClusterCount > 0)
					continue;
				FieldProp cluster[32];
				int clusterCount = 1;
				cluster[0] = fruitSpots[i];
				genInfo[fruitSpots[i].row][fruitSpots[i].col].fruitClusterCount = 1;
				int nowFlag = 0, endFlag = 0;
				while (nowFlag <= endFlag)
				{
					for (int checkSpot = i + 1; checkSpot < fruitSpotsCount; ++checkSpot)
					{
						if (genInfo[fruitSpots[checkSpot].row][fruitSpots[checkSpot].col].fruitClusterCount == 0 && Distance(cluster[nowFlag], fruitSpots[checkSpot]) <= 3)
						{
							genInfo[fruitSpots[checkSpot].row][fruitSpots[checkSpot].col].fruitClusterCount = 1;
							cluster[++endFlag] = fruitSpots[checkSpot];
							++clusterCount;
						}
					}
					++nowFlag;
				}
				for (int j = 0; j < clusterCount; ++j)
					genInfo[cluster[j].row][cluster[j].col].fruitClusterCount = clusterCount;
				maxCluster = std::max(maxCluster, clusterCount);
			}
#ifdef DEBUG
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					cout << genInfo[i][j].fruitClusterCount << '\t';
				}
				cout << endl;
			}
#endif // DEBUG

			//分析HotSpot
			std::set<FieldProp> fruits;
			for (int i = 0; i < generatorCount; i++)
				for (auto d = up; d < 8; ++d)
					fruits.insert(FieldProp((generators[i].row + dy[d] + height) % height, (generators[i].col + dx[d] + width) % width));

			FieldProp tmp;
			int heatMap[FIELD_MAX_HEIGHT][FIELD_MAX_WIDTH]{};
			char tmpDis;
			auto min = MAX_INT;
			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
				{
					tmp.row = i, tmp.col = j;
					if (isGenerator(tmp))
					{
						heatMap[i][j] = -255;
						continue;
					}
					for (auto fruit : fruits)
					{
						tmpDis = Distance(tmp, fruit);
						tmpDis = tmpDis >= 4 ? 8 : tmpDis;
						tmpDis = tmpDis == 0 ? -2 * generatorCount : tmpDis + generatorCount;
						heatMap[i][j] += tmpDis;
					}
					if (heatMap[i][j] <= 0)
						continue;

					if (heatMap[i][j] < min)
					{
						min = heatMap[i][j];
						hotSpotCount = 0;
						hotSpot[hotSpotCount++] = tmp;
					}
					else if (heatMap[i][j] == min)
						hotSpot[hotSpotCount++] = tmp;
				}

			auto minmin = min;
			min += 2;
			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
				{
					tmp.row = i, tmp.col = j;

					if (heatMap[i][j] <= min && heatMap[i][j] > minmin)
					{
						min = heatMap[i][j];
						hotSpot[hotSpotCount++] = tmp;
					}
				}
			


#ifdef PROFILING
			auto&& d = Debug::debugData["profiling"]["MapAnalyze()"];
			d = d.asDouble() + double(clock() - startTime) / CLOCKS_PER_SEC;
#endif 
		}

		// 读取并解析程序输入，本地调试或提交平台使用都可以。
		// 如果在本地调试，程序会先试着读取参数中指定的文件作为输入文件，失败后再选择等待用户直接输入。
		// 本地调试时可以接受多行以便操作，Windows下可以用 Ctrl-Z 或一个【空行+回车】表示输入结束，但是在线评测只需接受单行即可。
		// localFileName 可以为NULL
		// obtainedData 会输出自己上回合存储供本回合使用的数据
		// obtainedGlobalData 会输出自己的 Bot 上以前存储的数据
		// 返回值是自己的 playerID
		int ReadInput(const char *localFileName, Json::Value &obtainedData, Json::Value &obtainedGlobalData)
		{
			string str, chunk;
			if (!Debug::presetString.empty())
				str = Debug::presetString;
			else
			{
#ifdef _BOTZONE_ONLINE
				std::ios::sync_with_stdio(false); //ω\\)
				getline(cin, str);
#else
				if (localFileName)
				{
					std::ifstream fin(localFileName);
					if (fin)
						while (getline(fin, chunk) && chunk != "")
							str += chunk;
					else
						while (getline(cin, chunk) && chunk != "")
							str += chunk;
				}
				else
					while (getline(cin, chunk) && chunk != "")
						str += chunk;
#endif
			}

			Json::Reader reader;
			Json::Value input;
			reader.parse(str, input);

			int len = input["requests"].size();

			// 读取场地静态状况
			auto field = input["requests"][Json::Value::UInt(0)],
				staticField = field["static"], // 墙面和产生器
				contentField = field["content"]; // 豆子和玩家
			height = field["height"].asInt();
			width = field["width"].asInt();
			LARGE_FRUIT_DURATION = field["LARGE_FRUIT_DURATION"].asInt();
			LARGE_FRUIT_ENHANCEMENT = field["LARGE_FRUIT_ENHANCEMENT"].asInt();
			generatorTurnLeft = GENERATOR_INTERVAL = field["GENERATOR_INTERVAL"].asInt();

			PrepareInitialField(staticField, contentField);

			hasNext = true;

			MapAnalyze();

			// 根据历史恢复局面
			for (int i = 1; i < len; i++)
			{
				for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
					if (!players[_].dead)
						actions[_] = Direction(input["requests"][i][playerID2str[_]]["action"].asInt());
				NextTurn();
			}

			obtainedData = input["data"];
			obtainedGlobalData = input["globaldata"];

#ifdef SAVEDATA
			int ind = 0;
			auto&& tmp = input["distance"].asString();
			if (!tmp.empty())
				for (int i = 0; i < height; i++)
					for (int j = 0; j < width; j++)
						for (int k = 0; k < height; k++)
							for (int l = 0; l < width; l++)
								//distance[i][j][k][l] = tmp[i++];
								distance[i][j][k][l] = tmp[i++] - 1;
#endif

			return field["id"].asInt();
		}

		// 根据 static 和 content 数组准备场地的初始状况
		void PrepareInitialField(const Json::Value &staticField, const Json::Value &contentField)
		{
			int r, c, gid = 0;
			generatorCount = 0;
			aliveCount = 0;
			smallFruitCount = 0;
			generatorTurnLeft = GENERATOR_INTERVAL;
			for (r = 0; r < height; r++)
				for (c = 0; c < width; c++)
				{
					auto &content = fieldContent[r][c] = GridContentType(contentField[r][c].asInt());
					auto &s = fieldStatic[r][c] = GridStaticType(staticField[r][c].asInt());
					if (s & generator)
					{
						generators[gid].row = r;
						generators[gid++].col = c;
						generatorCount++;
					}
					if (content & smallFruit)
						smallFruitCount++;
					for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
						if (content & playerID2Mask[_])
						{
							auto &p = players[_];
							p.col = c;
							p.row = r;
							p.powerUpLeft = 0;
							p.strength = 1;
							p.dead = false;
							aliveCount++;
						}
				}
		}

		// 完成决策，输出结果。
		// action 表示本回合的移动方向，stay 为不移动
		// tauntText 表示想要叫嚣的言语，可以是任意字符串，除了显示在屏幕上不会有任何作用，留空表示不叫嚣
		// data 表示自己想存储供下一回合使用的数据，留空表示删除
		// globalData 表示自己想存储供以后使用的数据（替换），这个数据可以跨对局使用，会一直绑定在这个 Bot 上，留空表示删除
		// Jet: debugData为一个Json对象，botzone上不打印，用于本地调试
		void WriteOutput(Direction action, string& tauntText,
			Json::Value& data, Json::Value& globalData, Json::Value& debugData) const
		{
#ifdef PROFILING
			auto&& startTime = clock();
#endif

#ifdef SAVEDATA
			char* tmp = new char[height * width * height * width + 1];
			char* str = tmp;
			for (int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
					for (int k = 0; k < height; k++)
						for (int l = 0; l < width; l++)
							*(tmp++) = distance[i][j][k][l] + 1;
			*tmp = '\0';
			data = str;
#endif

			debugData["seed"] = to_string(seed);

#ifdef PROFILING
			auto&& d = Debug::debugData["profiling"]["WriteOutput()"];
			d = d.asDouble() + double(clock() - startTime) / CLOCKS_PER_SEC;
#endif 

			Json::Value ret;
			ret["response"]["action"] = action;
			ret["response"]["tauntText"] = tauntText;
			ret["data"] = data;
			ret["globaldata"] = globalData;
			if (Debug::printInfo)
				ret["debug"] = debugData;

#ifdef _BOTZONE_ONLINE
			Json::FastWriter writer; // 在线评测的话能用就行……
#else
			Json::StyledWriter writer; // 本地调试这样好看 > <
#endif
			cout << writer.write(ret) << endl;
		}

		// 用于显示当前游戏状态，调试用。
		// 提交到平台后会被优化掉。
		inline void DebugPrint() const
		{
#ifndef _BOTZONE_ONLINE
			printf("回合号【%d】存活人数【%d】| 图例 产生器[G] 有玩家[0/1/2/3] 多个玩家[*] 大豆[o] 小豆[.]\n", turnID, aliveCount);
			for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
			{
				auto& p = players[_];
				printf("[玩家%d(%d, %d)|力量%d|加成剩余回合%d|%s]\n",
					_, p.row, p.col, p.strength, p.powerUpLeft, p.dead ? "死亡" : "存活");
			}
			putchar(' ');
			putchar(' ');
			for (int c = 0; c < width; c++)
				printf("  %d ", c);
			putchar('\n');
			for (int r = 0; r < height; r++)
			{
				putchar(' ');
				putchar(' ');
				for (int c = 0; c < width; c++)
				{
					putchar(' ');
					printf((fieldStatic[r][c] & wallNorth) ? "---" : "   ");
				}
				printf("\n%d ", r);
				for (int c = 0; c < width; c++)
				{
					putchar((fieldStatic[r][c] & wallWest) ? '|' : ' ');
					putchar(' ');
					int hasPlayer = -1;
					for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
						if (fieldContent[r][c] & playerID2Mask[_])
							if (hasPlayer == -1)
								hasPlayer = _;
							else
								hasPlayer = 4;
					if (hasPlayer == 4)
						putchar('*');
					else if (hasPlayer != -1)
						putchar('0' + hasPlayer);
					else if (fieldStatic[r][c] & generator)
						putchar('G');
					else if (fieldContent[r][c] & playerMask)
						putchar('*');
					else if (fieldContent[r][c] & smallFruit)
						putchar('.');
					else if (fieldContent[r][c] & largeFruit)
						putchar('o');
					else
						putchar(' ');
					putchar(' ');
				}
				putchar((fieldStatic[r][width - 1] & wallEast) ? '|' : ' ');
				putchar('\n');
			}
			putchar(' ');
			putchar(' ');
			for (int c = 0; c < width; c++)
			{
				putchar(' ');
				printf((fieldStatic[height - 1][c] & wallSouth) ? "---" : "   ");
			}
			putchar('\n');
#endif
		}

		Json::Value SerializeCurrentTurnChange()
		{
			Json::Value result;
			TurnStateTransfer &bt = backtrack[turnID - 1];
			for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
			{
				result["actions"][_] = bt.actions[_];
				result["strengthDelta"][_] = bt.strengthDelta[_];
				result["change"][_] = bt.change[_];
			}
			return result;
		}

		// 初始化游戏管理器
		GameField()
		{
			if (constructed)
				throw runtime_error("请不要再创建 GameField 对象了，整个程序中只应该有一个对象");
			constructed = true;

			turnID = 0;
		}

		//GameField(const GameField &b) : GameField() { }
	};

	bool GameField::constructed = false;
}

// 一些辅助程序
namespace Helpers
{
	using namespace EnumExt;

	class Solution : public std::pair<Pacman::Direction, int>
	{
	public:
		Solution() { second = MAX_INT; }
		Solution(const std::pair<Pacman::Direction, int>& p) : std::pair<Pacman::Direction, int>(p) {}
		bool operator < (const Solution& o)const { return second < o.second; }
	};


	int randomPlayCount = 0;
	const std::vector<string> jiangXuan =
	{
		u8"赶紧续一秒 +1s",
		u8"人吶就都不知道",
		u8"自己不可以预料",
		u8"一个人的命运啊",
		u8"当然要靠自我的奋斗",
		u8"也要考虑历史的行程",
		u8"作为一个上海市委书记",
		u8"怎么就被调到北京去了",
		u8"我说另请高明吧",
		u8"我实在也不是谦虚",
		u8"中央研究都决定了",
		u8"你来当总书记",
		u8"当时我就念了两句诗",
		u8"苟利国家生死以",
		u8"岂因祸福避趋之",
		u8"我主要的就是三件事情",
		u8"军队一律不得经商",
		u8"这对军队的命运很重要",
		u8"就做了一点微小的工作",
		u8"很惭愧，但是Excited",
		u8"吼啊",
		u8"董先生吼不吼啊",
		u8"按照基本法，选举法",
		u8"最近欧盟出了一份报告",
		u8"内定，硬点的感觉",
		u8"不要见得风就是雨",
		u8"自己也要学会判断",
		u8"无中生有的东西",
		u8"你也有责任，对吧",
		u8"无可奉告！",
		u8"你们又不高兴"
		u8"不是我要钦点他",
		u8"你问我支持不支持",
		u8"我明确地告诉你这一点",
		u8"你们新闻界还要学习",
		u8"西方的那一套理论",
		u8"你们毕竟还too young",
		u8"我是身经百战啦",
		u8"我是见得多啦",
		u8"西方国家我都去过",
		u8"不知道高到哪里去啦",
		u8"我跟他谈笑风生",
		u8"提高自己的知识水平",
		u8"识得唔识得啊？",
		u8"我也替你们着急啊",
		u8"你们有一个好",
		u8"跑得比西方记者还快",
		u8"问来问去的问题啊",
		u8"都too simple",
		u8"sometimes naive",
		u8"我今天是作为一个长者",
		u8"我不是新闻工作者",
		u8"但是我见得太多了",
		u8"告诉你们人生的经验",
		u8"闷声大发财",
		u8"什么都不说是坠好的",
		u8"看到你们这样的热情啊",
		u8"一句话不说又不好",
		u8"报道偏差你们要负责",
		u8"我没有说要硬点",
		u8"没有任何这个意思",
		u8"要要，要要",
		u8"我们的决定权也很重要",
		u8"到那时候我们会表态",
		u8"不要想喜欢弄个大新闻",
		u8"就把我批判一番",
		u8"你们啊，naive",
		u8"我今天算是得罪了你们",
		u8"I'm angry!",
		/*"Congratulations! +1s",
		"Congratulations! +2s",
		"Congratulations! +5s",
		"A man, He not knows",
		"He can't predict",
		"Fen Dou + History",
		"I'm not being modest",
		"I'm a Shanghai mayor",
		"U ask other GAO MING",
		"ZHONGYANG decided!",
		"3 minor things",
		"Army No Bussiness!",
		"Micro work so CanKui!"
		"This thing, Excited!"
		"HO AH",
		"HO BU HO AH?",
		"ZHONGYANG supports!"
		"Read The EU's report",
		"Never heard of",
		"No Feng Is Rain",
		"Judge By Yourself!",
		"You too have ZEREN!",
		"NeiDing, QingDian",
		"WU KE FENG GAO！",
		"We talk, Wind blows",
		"Level of Knowledge",
		"I ZHAOJI FOR U!",
		"U have One Ge good!",
		"You Need Xue One Ge",
		"Hum, Western Theory",
		"You ，Naive！"
		"I SHEN ME YE no say.",
		"This is ZUI HAO DE！",
		"No Any This Meaning",
		"If U Have to ask me",
		"I Will Biao Tai",
		"wanna make BIG NEWS?",
		"sound outta sin(x)?",
		"I'll sing BJ opera",
		"Two Ju Cantonese",
		"I Drive Red Ferrari",
		"YoYo! YoYo!",
		"I'm healthier than u",
		"U Young People",
		"No Future For U"*/
	};

	const std::vector<string> threeWatches =
	{
		u8"始终代表先进生产力的发展要求",
		u8"始终代表先进文化的前进方向",
		u8"始终代表最广大人民的根本利益",
	};

	const std::vector<string> antiCoreValue =
	{
		u8"不富强", u8"不民主", u8"不文明", u8"不和谐",
		u8"不自由", u8"不平等", u8"不公正", u8"不法治",
		u8"不爱国", u8"不敬业", u8"不诚信", u8"不友善"
	};

	inline int RandBetween(int a, int b)
	{
		if (a > b)
			swap(a, b);
		return rand() % (b - a) + a;
	}

	inline int DeltaATK(const Pacman::GameField &gamefield, int id1, int id2)
	{
		return gamefield.players[id1].strength - gamefield.players[id2].strength;
	}

	inline string MoHa()
	{
		return jiangXuan[RandBetween(0, jiangXuan.size())];
	}

	inline string KeepSilentMakeFortune()
	{
		return "";
	}

	inline string ThreeWatches()
	{
		return threeWatches[rand() % 3];
	}

	inline string AntiCoreValue()
	{
		return antiCoreValue[rand() % 12];
	}

	// Jet: 近似算直线距离
	inline int ApprDirectDistance(Pacman::FieldProp startPos, Pacman::FieldProp endPos)
	{
		return (abs(startPos.row - endPos.row) + abs(startPos.col - endPos.col) + 1) / 2;
	}

	// weaZen:简单的危险判断
	bool SimpleDangerJudge(Pacman::GameField &gameField, int myID, Pacman::Direction myDir = Pacman::stay)
	{
		const Pacman::Player & me = gameField.players[myID];
		Pacman::FieldProp myPos;
		if (myDir != Pacman::Direction::stay)
		{
			myPos.row = (me.row + Pacman::dy[myDir] + gameField.height) % gameField.height;
			myPos.col = (me.col + Pacman::dx[myDir] + gameField.width) % gameField.width;
		}
		else
			myPos = me;
		for (int _ = 0; _ < 4; ++_)
		{
			if (DeltaATK(gameField, myID, _) < 0)
				if (gameField.Distance(myPos, gameField.players[_]) <= 1)
					return true;
		}
		return false;
	}

	//weaZen:随便找个不被吃的方向(如果可以)
	//Jet:需要返回随机值的情况大多可以返回AI::RandomAI()代替
	Pacman::Direction SimpleRandom(Pacman::GameField &gameField, int myID, char forbiddenDirs = '\0')
	{
		Pacman::Direction dir;
		int vCount = 0;
		Pacman::Direction valid[5];
		for (Pacman::Direction d = Pacman::stay; d < 4; ++d)
			if (gameField.ActionValid(myID, d) && !(forbiddenDirs & (1 << (d + 1))))
				valid[vCount++] = d;
		if (vCount == 0) return Pacman::Direction::stay;
		dir = valid[RandBetween(0, vCount)];
		return dir;
	}

	//weaZen:递归统计死路上某一位置之后 一条路径上的最大可能水果数量 给Naive快速判断是否尝试吃人用
	int fruitCount(Pacman::GameField &gameField, Pacman::FieldProp pos)
	{
		if (!gameField.pathInfo[pos.row][pos.col].isImpasse && !gameField.pathInfo[pos.row][pos.col].isExit)
			return 0;
		int max = 0;
		Pacman::FieldProp nextPos;
		for (Pacman::Direction dir = Pacman::up; dir <= Pacman::left; ++dir)
		{
			if (gameField.fieldStatic[pos.row][pos.col] & Pacman::direction2OpposingWall[dir])
				continue;
			nextPos.row = (pos.row + Pacman::dy[dir] + gameField.height) % gameField.height;
			nextPos.col = (pos.col + Pacman::dx[dir] + gameField.width) % gameField.width;
			if (gameField.pathInfo[nextPos.row][nextPos.col].fleeLength == gameField.pathInfo[pos.row][pos.col].fleeLength + 1)
				max = std::max(max, fruitCount(gameField, nextPos));
		}
		if (gameField.fieldContent[pos.row][pos.col] & Pacman::smallFruit)
			++max;
		if (gameField.fieldContent[pos.row][pos.col] & Pacman::largeFruit)
			max += 10;
		return max;
	}

	Solution RandomPlay(Pacman::GameField &gameField, int myID, bool noStay)
	{
		randomPlayCount++;
		int count = 0, myAct = -1;
		while (true)
		{
			// 对每个玩家生成随机的合法动作
			for (int i = 0; i < MAX_PLAYER_COUNT; i++)
			{
				if (gameField.players[i].dead)
					continue;
				Pacman::Direction valid[5]{};
				int vCount = 0;
				for (Pacman::Direction d = Pacman::Direction(-1 + noStay); d < 4; ++d)
					if (gameField.ActionValid(i, d))
						valid[vCount++] = d;
				gameField.actions[i] = valid[RandBetween(0, vCount)];
			}

			if (count == 0)
				myAct = gameField.actions[myID];

			// 演算一步局面变化
			// NextTurn返回true表示游戏没有结束
			bool hasNext = gameField.NextTurn();
			count++;

			if (!hasNext)
				break;
		}

		// 计算分数
		int actionScore,
			total = 0;
		for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
			total += gameField.players[_].strength;

		actionScore = (10000 * gameField.players[myID].strength / total) / 100;

		// 恢复游戏状态到本回合初
		gameField.RollBack(count);

		return std::make_pair(Pacman::Direction(myAct), actionScore);
	}

	inline string depth2String(int depth)
	{
		auto&& str = to_string(depth);
		if (str.length() == 1)
			str.insert(str.begin(), '0');
		return "depth = " + str;
	}
}

namespace AI
{
	using namespace EnumExt;
	using Helpers::Solution;
	static int maxDepth;

	//DangerInfoType: 表示若干回合后会死亡，不合法行为记为0回合(当场死亡)。
	typedef std::pair<Pacman::Direction, int> DangerInfoType;
	typedef std::pair<Pacman::Direction, bool> stepInfoType;

	//tmpSol是给其他时候搜索用的
	//tmpDanger用来判断危险
	//myPath记录自己的路径
	std::vector<Solution> tmpSol(5);
	std::vector<DangerInfoType> tmpDangers(5);
	stepInfoType stepInfo[50]{};
	
	int SimpleSearch(Pacman::GameField &gameField, int myID, int depth,
		Pacman::Direction(*rivalAI)(Pacman::GameField &, int, int), int step = 0, std::vector<Solution>& solutions = tmpSol);

	std::vector<Solution> MCTS_AI(Pacman::GameField &gameField, int myID, bool noStay = false, double timeOut = 0)
	{
		clock_t&& startTime = clock();
		int actionScore[5]{};
		while (Debug::TimeThrough(startTime) < timeOut)
		{
			Solution&& sol = Helpers::RandomPlay(gameField, myID, noStay);
			actionScore[sol.first + 1] += sol.second;
		}

		std::vector<Solution> solutions;
		for (int d = 0; d < 5; d++)
			solutions.push_back(std::make_pair(Pacman::Direction(d - 1), actionScore[d]));
		sort(solutions.begin(), solutions.end());

		return solutions;
	}

	//weaZen: 寻找最容易丢失的果子
	Pacman::FieldProp FruitSelect(Pacman::GameField &gameField, int myID, int targetID)
	{
		std::vector <std::pair< Pacman::FieldProp, int> > myFruits;
		for (int i = 0; i < gameField.height; ++i)
			for (int j = 0; j < gameField.width; ++j)
				if (gameField.fieldContent[i][j] & (Pacman::smallFruit | Pacman::largeFruit))
				{
					int myDis = 0;
					int othersMinDis = MAX_INT;
					Pacman::FieldProp fruit(i, j);
					myDis = 2 * int(gameField.Distance(gameField.players[myID], fruit));
					for (int playerID = 0; playerID < MAX_PLAYER_COUNT; ++playerID)
					{
						if (playerID == myID || gameField.players[playerID].dead)
							continue;
						int otherDis = 2 * int(gameField.Distance(gameField.players[playerID], fruit));
						if (playerID == targetID)
							--otherDis;
						//if (gameField.players[playerID].strength > gameField.players[myID].strength)

						othersMinDis = std::min(othersMinDis, otherDis);
					}
					if (othersMinDis <= myDis - 2)
						continue;
					myFruits.push_back(std::make_pair(Pacman::FieldProp(i, j), othersMinDis - myDis));
				}
		if (myFruits.empty())
			return Pacman::FieldProp(-1, -1);
		Pacman::FieldProp targetFruit;
		for (auto myFruit : myFruits)
		{
			int tmp = 1;
			int minDeltaDis = MAX_INT;
			if (minDeltaDis > myFruit.second)
			{
				minDeltaDis = myFruit.second;
				targetFruit = myFruit.first;
				tmp = 1;
			}
			else
				if (minDeltaDis == myFruit.second && !(rand() % ++tmp))
					targetFruit = myFruit.first;
		}
		return targetFruit;
	}

	//weaZen： 目标优先级：在死路上可能逃不出来的弱AI > 附近在死路出口的弱AI、附近在夹道中被追击的弱AI > 大果子 > 小果子 > 生成器 判断危险用的对手AI
	Pacman::Direction NaiveAttackAI(Pacman::GameField &gameField, int myID, int targetID = -1)
	{
		char largeFruitTarget = Pacman::GridContentType::largeFruit;
		char smallFruitTarget = Pacman::GridContentType::smallFruit;
		char playerTarget = 0;
		char tryPlayerTarget = 0;
		char forbiddenDirs = '\0';
		Pacman::Direction dir;

		for (int i = -1; i < 4; ++i)
		{
			if (!gameField.ActionValid(myID, Pacman::Direction(i)))
			{
				forbiddenDirs |= 1 << (i + 1);
				continue;
			}
			if (Helpers::SimpleDangerJudge(gameField, myID, Pacman::Direction(i)))
				forbiddenDirs |= 1 << (i + 1);
		}
		if (forbiddenDirs == 31)//（基本）必死无疑
			return Helpers::SimpleRandom(gameField, myID);


		for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
		{
			Pacman::Player & rival = gameField.players[_];
			if (rival.dead || _ == myID)
				continue;
			if (Helpers::DeltaATK(gameField, myID, _) > 0 || (Helpers::DeltaATK(gameField, myID, _) == 0 && gameField.Distance(myID, _) <= 2 && gameField.generatorTurnLeft <= 2))
			{
				bool preyFlag = gameField.pathInfo[rival.row][rival.col].isImpasse
					&& gameField.pathInfo[rival.row][rival.col].fleeLength + 2 >= gameField.Distance(gameField.players[myID], *gameField.pathInfo[rival.row][rival.col].pExit);
				bool tryPreyFlag = gameField.pathInfo[rival.row][rival.col].isExit
					&& gameField.Distance(myID, _) <= 2;
			//夹道里被追击的弱AI
				if (!preyFlag && !tryPreyFlag)
				{
					int dirCount = 4;
					for (int i = 0; i < 4; ++i)
					{
						if (gameField.fieldStatic[rival.row][rival.col] & Pacman::direction2OpposingWall[i])
						{
							--dirCount;
							continue;
						}
						Pacman::FieldProp checkPos;
						checkPos.row = (rival.row + Pacman::dy[i] + gameField.height) % gameField.height;
						checkPos.col = (rival.col + Pacman::dx[i] + gameField.width) % gameField.width;
						if (gameField.fieldContent[checkPos.row][checkPos.col] & Pacman::playerMask)
							for (int checkID = 0; checkID < 4; ++checkID)
							{
								if (checkID == myID) continue;
								if (gameField.fieldContent[checkPos.row][checkPos.col] & Pacman::playerID2Mask[checkID]
									&& gameField.players[checkID].strength > rival.strength)
								{
									--dirCount;
									break;
								}
							}
					}
					if (dirCount == 1 && gameField.Distance(myID, _) <= 2)
						tryPreyFlag = true;
				}
				if (preyFlag)
					playerTarget |= Pacman::playerID2Mask[_];
				if (tryPreyFlag)
					tryPlayerTarget |= Pacman::playerID2Mask[_];
			}
		}

		if (targetID != -1)
		{
			if (playerTarget & Pacman::playerID2Mask[targetID] || tryPlayerTarget & Pacman::playerID2Mask[targetID])
			{
				playerTarget = 0;
				tryPlayerTarget = 0;
				playerTarget |= Pacman::playerID2Mask[targetID];
			}
		}

		auto&& smallFruitInfo = gameField.GetToTarget(myID, smallFruitTarget, forbiddenDirs);
		auto&& largeFruitInfo = gameField.GetToTarget(myID, largeFruitTarget, forbiddenDirs);
		auto&& playerInfo = gameField.GetToTarget(myID, playerTarget, forbiddenDirs);
		auto&& tryPlayerInfo = gameField.GetToTarget(myID, tryPlayerTarget, forbiddenDirs);

		//一定概率放弃当前果子
		if (smallFruitInfo == '\0' || largeFruitInfo == '\0')
			if ((gameField.fieldContent[gameField.players[myID].row][gameField.players[myID].col] & Pacman::playerID2Mask[targetID]) && gameField.actions[targetID] != Pacman::stay)
				return Pacman::stay;
		if (smallFruitInfo == '\0' && Helpers::RandBetween(0, 2))
			smallFruitInfo = gameField.GetToTarget(myID, smallFruitTarget, forbiddenDirs | 1);
		if (largeFruitInfo == '\0' && Helpers::RandBetween(0, 2))
			largeFruitInfo = gameField.GetToTarget(myID, largeFruitTarget, forbiddenDirs | 1);
#ifdef DEBUG
				cout << '#' << myID << ' ' << (smallFruitInfo >> 3) << ' ' << Pacman::dirStr[smallFruitInfo & 7] << ' ' << (playerInfo >> 3) << ' ' << Pacman::dirStr[playerInfo & 7] << endl;
#endif // DEBUG
		auto&& smallFruitDirInfo = smallFruitInfo & 7;
		auto&& largeFruitDirInfo = largeFruitInfo & 7;
		auto&& playerDirInfo = playerInfo & 7;
		auto&& tryPlayerDirInfo = tryPlayerInfo & 7;

		int info = (smallFruitDirInfo < 5) + ((largeFruitDirInfo < 5) << 1) + ((tryPlayerDirInfo < 5) << 2) + ((playerDirInfo < 5) << 3);

		if (info >= 8)
			dir = Pacman::Direction(playerDirInfo - 1);
		else
			if (info >= 4)
				dir = Pacman::Direction(tryPlayerDirInfo - 1);
			else
				if (info >= 2)
					//他们对大果子有狂热的爱
					dir = Pacman::Direction(largeFruitDirInfo - 1);
				else
					if ((info >= 1 && (smallFruitInfo >> 3) <= gameField.generatorTurnLeft))
						dir = Pacman::Direction(smallFruitDirInfo - 1);
					else
						dir = Pacman::Direction((gameField.GetToNearbyGenerator(myID, forbiddenDirs) & 7) - 1);

		if (dir != Pacman::Direction::stay && dir != Pacman::Direction::ur)
			return dir;
		//为了能够搜索减少耗时直接随机
		if (Helpers::RandBetween(0, 4) <= 2 && dir == Pacman::Direction::stay)
			return dir;
		else
			return Helpers::SimpleRandom(gameField, myID, forbiddenDirs);
	}

	//weaZen: 复杂的危险判断
	int DangerJudge(Pacman::GameField &gameField, int myID, std::vector<DangerInfoType> & dangers, int maxDepth = 10)
	{
		dangers.clear();
		for (Pacman::Direction dir = Pacman::stay; dir <= Pacman::left; ++dir)
		{
			if (!gameField.ActionValid(myID, dir))
			{
				dangers.push_back(std::make_pair(dir, 0));
				continue;
			}
			if (Helpers::SimpleDangerJudge(gameField, myID, dir))
			{
				dangers.push_back(std::make_pair(dir, 1));
				continue;
			}
			Pacman::FieldProp nextGrid;
			if (dir != Pacman::Direction::stay)
			{
				nextGrid.row = (gameField.players[myID].row + Pacman::dy[dir] + gameField.height) % gameField.height;
				nextGrid.col = (gameField.players[myID].col + Pacman::dx[dir] + gameField.width) % gameField.width;
			}
			else
				nextGrid = gameField.players[myID];

			if (gameField.pathInfo[nextGrid.row][nextGrid.col].isImpasse)
			{
				int fleeLength = gameField.pathInfo[nextGrid.row][nextGrid.col].fleeLength;
				bool enemyFlag = false;

				//死路出口附近没有其他人时不用搜索了
				for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
				{
					if (_ == myID) continue;
					if (gameField.Distance(gameField.players[_], *gameField.pathInfo[nextGrid.row][nextGrid.col].pExit) <= fleeLength + 1)
						enemyFlag = true;
				}
				if (!enemyFlag) continue;

				//注意只有一个gamefield 模拟其他AI时注意action的还原
				Pacman::Direction tmpDir[MAX_PLAYER_COUNT];
				stepInfoType tmpStepInfo[50];
				for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
					tmpDir[_] = gameField.actions[_];
				for (int i = 0; i < 50; ++i)
					tmpStepInfo[i] = stepInfo[i];
				
				gameField.actions[myID] = dir;
				for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
				{
					if (_ == myID)
						continue;
					if (gameField.players[_].dead)
						continue;
					gameField.actions[_] = NaiveAttackAI(gameField, _, myID);
				}

				
				gameField.NextTurn();
				
				
				int searchDepth = std::min(maxDepth, gameField.pathInfo[nextGrid.row][nextGrid.col].pExit->impasseDepth + fleeLength + 1);
				searchDepth = std::min(searchDepth, 100 - gameField.turnID);

				for (int tmpDepth = 1; tmpDepth <= searchDepth; ++tmpDepth)
				{
					tmpSol.clear();

					if (SimpleSearch(gameField, myID, tmpDepth, NaiveAttackAI) <= DEATH_EVAL)
					{
						dangers.push_back(std::make_pair(dir, tmpDepth + 1));
						break;
					}
				}
				gameField.RollBack(1);
				for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
					gameField.actions[_] = tmpDir[_];
				for (int i = 0; i < 50; ++i)
					stepInfo[i] = tmpStepInfo[i];

			}
		}
		return 0;
	}

	//weaZen： 会回避死亡的高级AI
	Pacman::Direction NaiveThinkAI(Pacman::GameField &gameField, int myID, int targetID = -1)
	{
		char fruitTarget = (Pacman::GridContentType::smallFruit | Pacman::GridContentType::largeFruit);
		char playerTarget = 0;
		char tryPlayerTarget = 0;
		char forbiddenDirs = '\0';
		Pacman::Direction dir;

		DangerJudge(gameField, myID, tmpDangers, 5);

		
		if (tmpDangers.size() == 5)//（基本）必死无疑
		{
			//随机选最晚死的方向
			int tmpMax = 0;
			int maxCount = 1;
			for (auto i = tmpDangers.begin(); i != tmpDangers.end(); ++i)
			{
				if ((*i).second > tmpMax)
				{
					tmpMax = (*i).second;
					dir = (*i).first;
					maxCount = 1;
				}
				else if ((*i).second == tmpMax)
				{
					dir = rand() % ++maxCount ? dir : (*i).first;
				}
			}

			//如果在死路上且敌人在死路外尝试逃离
			if (gameField.pathInfo[gameField.players[myID].row][gameField.players[myID].col].isImpasse)
			{
				//到出口的方向是fleeLength减1的位置
				Pacman::Direction fleeDir;
				for (fleeDir = Pacman::up; fleeDir <= Pacman::left; ++fleeDir)
				{
					int tmpx, tmpy;
					tmpy = (gameField.players[myID].row + Pacman::dy[fleeDir] + gameField.height) % gameField.height;
					tmpx = (gameField.players[myID].col + Pacman::dx[fleeDir] + gameField.width) % gameField.width;
					if (!(gameField.fieldStatic[gameField.players[myID].row][gameField.players[myID].col] & Pacman::direction2OpposingWall[fleeDir]))
						if (gameField.pathInfo[gameField.players[myID].row][gameField.players[myID].col].fleeLength == gameField.pathInfo[tmpy][tmpx].fleeLength + 1)
							break;
				}
				for (auto i = tmpDangers.begin(); i != tmpDangers.end(); ++i)
					if ((*i).first == fleeDir && (*i).second == tmpMax)
					{
						dir = fleeDir;
						break;
					}
			}

			return dir;
		}

		if (tmpDangers.size() == 4)//没得选
		{
			int k = 5; // -1 + 0 + 1 + 2 + 3 
			for (auto i = tmpDangers.begin(); i != tmpDangers.end(); ++i)
				k -= (*i).first;
			return Pacman::Direction(k);
		}

		//记录forbiddenDirs
		for (auto i = tmpDangers.begin(); i != tmpDangers.end(); ++i)
			forbiddenDirs |= (1 << ((*i).first + 1));

		//标记目标AI
		for (int _ = 0; _ < MAX_PLAYER_COUNT; _++)
		{
			Pacman::Player & rival = gameField.players[_];
			if (rival.dead || _ == myID)
				continue;
			if (Helpers::DeltaATK(gameField, myID, _) > 0)
			{
				bool preyFlag = gameField.pathInfo[rival.row][rival.col].isImpasse
					&& (gameField.pathInfo[rival.row][rival.col].fleeLength + 2 >= gameField.Distance(gameField.players[myID], *gameField.pathInfo[rival.row][rival.col].pExit));
				bool tryPreyFlag = gameField.pathInfo[rival.row][rival.col].isExit
					&& gameField.Distance(myID, _) <= 2;

				if (preyFlag || tryPreyFlag)
				{
					int tmpFruitCount = Helpers::fruitCount(gameField, gameField.players[_]);
					//没有水果的死路一般不会走进去吧
					if (tmpFruitCount >= Helpers::DeltaATK(gameField, myID, _) || tmpFruitCount == 0)
						preyFlag = tryPreyFlag = false;
				}
			//夹道里被追击的弱AI
				if (!preyFlag && !tryPreyFlag)
				{
					int dirCount = 4;
					for (int i = 0; i < 4; ++i)
					{
						if (gameField.fieldStatic[rival.row][rival.col] & Pacman::direction2OpposingWall[i])
						{
							--dirCount;
							continue;
						}
						Pacman::FieldProp checkPos;
						checkPos.row = (rival.row + Pacman::dy[i] + gameField.height) % gameField.height;
						checkPos.col = (rival.col + Pacman::dx[i] + gameField.width) % gameField.width;
						if (gameField.fieldContent[checkPos.row][checkPos.col] & Pacman::playerMask)
							for (int checkID = 0; checkID < 4; ++checkID)
							{
								if (checkID == myID) continue;
								if (gameField.fieldContent[checkPos.row][checkPos.col] & Pacman::playerID2Mask[checkID]
									&& gameField.players[checkID].strength > rival.strength)
								{
									--dirCount;
									break;
								}
							}
					}
					if (dirCount == 1 && gameField.Distance(myID, _) <= 2)
						tryPreyFlag = true;
				}
				if (preyFlag)
					playerTarget |= Pacman::playerID2Mask[_];
				if (tryPreyFlag)
					tryPlayerTarget |= Pacman::playerID2Mask[_];
			}
		}
//		auto&& fruitInfo = gameField.GetToTarget(myID, FruitSelect(gameField, myID, targetID), forbiddenDirs);
		auto&& fruitInfo = gameField.GetToTarget(myID, fruitTarget, forbiddenDirs);
		auto&& playerInfo = gameField.GetToTarget(myID, playerTarget, forbiddenDirs);
		auto&& tryPlayerInfo = gameField.GetToTarget(myID, tryPlayerTarget, forbiddenDirs);
		//一定概率放弃当前果子
		if ((gameField.fieldContent[gameField.players[myID].row][gameField.players[myID].col] & Pacman::playerID2Mask[targetID])
			&& gameField.actions[targetID] != Pacman::stay
			&& (gameField.fieldContent[gameField.players[myID].row][gameField.players[myID].col] & fruitTarget))
			return Pacman::stay;
		if (fruitInfo == '\0' && Helpers::RandBetween(0, 2) == 0)
			fruitInfo = gameField.GetToTarget(myID, fruitTarget, forbiddenDirs | 1);
#ifdef DEBUG
		//cout << '#' << myID << ' ' << (fruitInfo >> 3) << ' ' << Pacman::dirStr[fruitInfo & 7] << ' ' << (playerInfo >> 3) << ' ' << Pacman::dirStr[playerInfo & 7] << endl;
#endif // DEBUG
		auto&& fruitDirInfo = fruitInfo & 7;
		auto&& playerDirInfo = playerInfo & 7;
		auto&& tryPlayerDirInfo = tryPlayerInfo & 7;

		int info = (fruitDirInfo < 5) + ((tryPlayerDirInfo < 5) << 1) + ((playerDirInfo < 5) << 2);

		if (info >= 4)
			dir = Pacman::Direction(playerDirInfo - 1);
		else
			if (info >= 2)
				dir = Pacman::Direction(tryPlayerDirInfo - 1);
			else
				if (info >= 1 && (fruitInfo >> 3) <= gameField.generatorTurnLeft)
					dir = Pacman::Direction(fruitDirInfo - 1);
				else
					dir = Pacman::Direction((gameField.GetToHotSpot(myID, forbiddenDirs) & 7) - 1);

		if (dir != Pacman::Direction::stay && dir != Pacman::Direction::ur)
			return dir;
		if (rand() % 2 && dir == Pacman::Direction::stay)
			return dir;
		else
			return Helpers::SimpleRandom(gameField, myID, forbiddenDirs | 1);
	}

	int GreedyEval(Pacman::GameField &gameField, int myID)
	{
#ifdef PROFILING
		auto&& startTime = clock();
#endif
		int minMaxClusterDis = 100;
		int strengthSum = 0;
		if (gameField.players[myID].dead)
			return DEATH_EVAL;

		for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
			strengthSum += gameField.players[i].strength;

		if (!gameField.hasNext)
		{
			int weakCount = 0;
			for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
				if (gameField.players[i].strength < gameField.players[myID].strength)
					++weakCount;
			return int(1000 * float(gameField.players[myID].strength) / strengthSum + (weakCount + 1) * 100);
		}
		int e = 0;

		int strongCount = 0;
		for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
			if (gameField.players[i].strength > gameField.players[myID].strength)
				++strongCount;

		//e -= strongCount * 10;

		if (gameField.generatorCount == 0)
			minMaxClusterDis = 0;
		else
			minMaxClusterDis = int((gameField.GetToMaxCluster(myID)) >> 3);

		if (minMaxClusterDis + 2 >= gameField.generatorTurnLeft)
			e -= (minMaxClusterDis + 2 - gameField.generatorTurnLeft) * 2;


		if (gameField.players[myID].powerUpLeft <= 0)
			e += gameField.players[myID].strength;
		else
			e += gameField.players[myID].strength -gameField.LARGE_FRUIT_ENHANCEMENT;// +gameField.players[myID].powerUpLeft;
#ifdef PROFILING
		auto&& d = Debug::debugData["profiling"]["GreedyEval()"];
		d = d.asDouble() + double(clock() - startTime) / CLOCKS_PER_SEC;
#endif
		return e;
	}
	
	Solution chooseDir(std::vector<std::vector<Solution> >& solutions, std::vector<DangerInfoType> dangers)
	{
		int evalWeighedAverage[5]{};
		bool deathFlag[5]{};
		int tmp = 0;
		for (auto danger : dangers)
		{
			deathFlag[danger.first + 1] = true;
			evalWeighedAverage[danger.first + 1] = danger.second == 0 ? INVALID_EVAL : DEATH_EVAL + danger.second;
		}
		for (auto sol : solutions)
		{
			++tmp;
			for (int i = 0; i < 5; i++)
			{
				if (sol[i].second == INVALID_EVAL)
					continue;

				//这是为了分出最晚死的方向
				if (sol[i].second == DEATH_EVAL || deathFlag[i])
				{
					if (!deathFlag[i])
					{
						deathFlag[i] = true;
						evalWeighedAverage[i] = DEATH_EVAL + tmp;
					}
					continue;
				}
				evalWeighedAverage[i] += 10 * sol[i].second;
				evalWeighedAverage[i] /= 2;
			}
		}

		int max = INVALID_EVAL;
		auto d = Pacman::Direction::stay;
		for (int i = 0; i < 5; i++)
			if (max < evalWeighedAverage[i])
			{
				max = evalWeighedAverage[i];
				d = Pacman::Direction(i - 1);
				tmp = 1;
			}
			else if (max == evalWeighedAverage[i] && Helpers::RandBetween(0, ++tmp) == 0)
				d = Pacman::Direction(i - 1);

		return std::make_pair(d, max);
	}

	// weaZen:简单的搜索，调用返回最高估值
	int SimpleSearch(Pacman::GameField &gameField, int myID, int depth,
		Pacman::Direction(*rivalAI)(Pacman::GameField &, int, int), int step, std::vector<Solution>& solutions)
	{
		//是不是上一次迭代搜索的解
		bool isShallowSol = !solutions.empty();
		

		int max = DEATH_EVAL;
		int tmp = 0;

		//如果同深度模拟出了比浅搜索时更好的结果舍弃		
		if (isShallowSol && step != 0 && depth == 1 && (GreedyEval(gameField, myID) > solutions[stepInfo[0].first + 1].second))
			return solutions[stepInfo[0].first + 1].second;

		
		//记录现在的力量和增益回合
		int strength = gameField.players[myID].strength;
		int powerUpLeft = gameField.players[myID].powerUpLeft;
		
		//cout << depth << ' ';

		if (Debug::TimeOut() || depth == 0 || !gameField.hasNext)
			return GreedyEval(gameField, myID);
		if (gameField.players[myID].dead)
			return DEATH_EVAL;
		
		for (auto dir = Pacman::stay; dir <= Pacman::left; ++dir)
		{
			//如果已经有死亡危险
			if (step == 0 && isShallowSol && solutions[dir + 1].second <= DEATH_EVAL)
				continue;

			//撞墙
			if (!gameField.ActionValid(myID, dir))
			{
				if (step == 0 && isShallowSol)
					solutions[dir + 1].second = INVALID_EVAL;
				continue;
			}

			//危险
			if (Helpers::SimpleDangerJudge(gameField, myID, dir)) {
				if (step == 0 && isShallowSol)
					solutions[dir + 1].second = DEATH_EVAL;
				continue;
			}

			//方向的限制
			int dy = 0, dx = 0;
			bool returnFlag = false;
			if (dir != Pacman::Direction::stay)
			{
				dy = Pacman::dy[dir];
				dx = Pacman::dx[dir];
			}
			for (int i = step - 1; i >= 0; --i)
			{
				if (stepInfo[i].second == false)
					break;
				if (stepInfo[i].first == Pacman::Direction::stay)
					continue;
				dy += Pacman::dy[stepInfo[i].first];
				dx += Pacman::dx[stepInfo[i].first];
				if (dx == 0 && dy == 0)
				{
					returnFlag = true;
					break;
				}
			}
			if (returnFlag)
				continue;

			//基于以下两点猜测减少搜索量
			//1.没有力量增加或驱逐对手却往反方向跑是无意义的
			//2.不在生成器周围或当前位置没有果子却不动是无意义的
			bool deterFlag = false;
			bool waitFlag = false;
			bool eatFlag = false;

			//是否在驱逐/躲避对手
			for (int playerID = 0; playerID < MAX_PLAYER_COUNT; ++playerID)
			{
				if (playerID == myID)
					continue;
				if (gameField.Distance(myID, playerID) <= 2)
					deterFlag = true;
			}
			
			//是否在等待生成或等待重叠果子
			if (dir == Pacman::Direction::stay && step != 0)
			{
				waitFlag = gameField.genInfo[gameField.players[myID].row][gameField.players[myID].col].isBesideGen && gameField.generatorTurnLeft <= 3;
				waitFlag |= (gameField.fieldContent[gameField.players[myID].row][gameField.players[myID].col] & (Pacman::GridContentType::smallFruit | Pacman::GridContentType::largeFruit));
				if (!waitFlag)
					continue;
			}

			gameField.actions[myID] = dir;

			for (int i = 0; i < MAX_PLAYER_COUNT; i++)
			{
				if (i == myID)
					continue;
				if (gameField.players[i].dead)
					continue;
				gameField.actions[i] = rivalAI(gameField, i, myID);
			}

			
#ifdef DEBUG
			//if (depth == maxDepth && myID == 3) {
				gameField.DebugPrint();
				for (int i = 0; i < MAX_PLAYER_COUNT; ++i)
				{
					cout << "AI " << i << ' ' << Pacman::dirStr[gameField.actions[i] + 1] << endl;
				}
				system("pause");
			//}
#endif // DEBUG

			gameField.NextTurn();
			
			//是否有吃到了什么
			eatFlag = (gameField.players[myID].strength - strength > 0 || gameField.players[myID].powerUpLeft > powerUpLeft);
			//吃到东西同时增益消失的情况
			eatFlag |= (powerUpLeft == 1 && gameField.players[myID].strength > strength - gameField.LARGE_FRUIT_ENHANCEMENT);
			//重叠的情况
			eatFlag |= gameField.fieldContent[gameField.players[myID].row][gameField.players[myID].col] & (Pacman::GridContentType::smallFruit | Pacman::GridContentType::largeFruit);

			stepInfo[step].first = dir;
			//达到三个目标之一就不限制下一步方向
			stepInfo[step].second = !(deterFlag | waitFlag | eatFlag);
			
			

			/*if (dir == Pacman::stay && stepInfo[step].second && step != 0)
			{
				gameField.RollBack(1);
				continue;
			}*/

			tmpSol.clear();

			tmp = SimpleSearch(gameField, myID, depth - 1, rivalAI, step + 1, solutions);
			
			//不在死路上吃到了敌人 因为有风险先还原再说
			if (gameField.players[myID].strength - strength > 1
				&& gameField.players[myID].powerUpLeft - powerUpLeft != gameField.LARGE_FRUIT_DURATION - 1
				&& !gameField.pathInfo[gameField.players[myID].row][gameField.players[myID].col].isImpasse
				&& !gameField.pathInfo[gameField.players[myID].row][gameField.players[myID].col].isExit)
				tmp = tmp - (gameField.players[myID].strength - strength) * depth + 1;

			//吃到大果子稍微加一分
			if (gameField.players[myID].strength - strength > 1
				&& gameField.players[myID].powerUpLeft - powerUpLeft == gameField.LARGE_FRUIT_DURATION - 1)
				++tmp;

			gameField.RollBack(1);

			if (tmp > 0 && depth + gameField.turnID != 100)
				tmp += GreedyEval(gameField, myID);
			if (depth == maxDepth
				&& tmp > 0
				&& dir == Pacman::stay
				&& !(gameField.fieldContent[gameField.players[myID].row][gameField.players[myID].col] & (Pacman::GridContentType::smallFruit | Pacman::GridContentType::largeFruit))
				&& gameField.players[myID].strength - strength == 0)
				tmp = int(tmp * (1 - float(gameField.generatorTurnLeft - 1) / gameField.GENERATOR_INTERVAL));
			
			if (tmp > max)
				max = tmp;
			
			if (step == 0 && isShallowSol)
					solutions[dir + 1].second = tmp;

			// 超时处理
			if (Debug::TimeOut())
				return max;
		}

		return max;
	}

	Pacman::Direction IterativeGreedySearch(Pacman::GameField &gameField, int myID)
	{
		std::vector<Solution> sol(5);
		std::vector<DangerInfoType> dangers(5);
		for (int i = 0; i < 5; i++) {
			sol[i].first = Pacman::Direction(i - 1);
			sol[i].second = MAX_INT;
		}

		std::vector<std::vector<Solution> > solutions{};

		DangerJudge(gameField, myID, dangers);


		for (auto danger : dangers)
		{
			sol[danger.first + 1].second = danger.second == 0 ? INVALID_EVAL : DEATH_EVAL;
		}

		for (int depth = DEFAULT_DEPTH; depth <= std::min(MAX_DEPTH, 100 - gameField.turnID); depth++)
		{
			auto startTime = clock();
			maxDepth = depth;

			SimpleSearch(gameField, myID, depth, NaiveThinkAI, 0, sol);
			if (Debug::TimeOut())
			{
				Debug::debugData[Helpers::depth2String(depth)]["*solution"]["notFinished"] = true;
				break;
			}

			solutions.push_back(sol);
			for (auto i = Pacman::stay; i <= Pacman::left; ++i)
				Debug::debugData[Helpers::depth2String(depth)]["evals"][Pacman::dirStr[i + 1]] = sol[i + 1].second;
			Debug::debugData[Helpers::depth2String(depth)]["timeCosumed"] = double(clock() - startTime) / CLOCKS_PER_SEC;

		}

		cout << endl;
		if (solutions.size() == 0)
		{
			Debug::debugData["*choice"]["NAIVE"] = true;
			return NaiveAttackAI(gameField, myID, -1);
		}

		auto&& finalSol = chooseDir(solutions, dangers);

		Debug::debugData["*choice"]["direction"] = Pacman::dirStr[finalSol.first + 1];
		Debug::debugData["*choice"]["finalEval"] = finalSol.second;

		return finalSol.first;
	}
}

int main()
{
	auto AI = AI::IterativeGreedySearch;
//	auto AI = AI::NaiveThinkAI;
	auto TAUNT = Helpers::KeepSilentMakeFortune;

	Pacman::GameField mainGameField;
	Json::Value data, globalData; // 这是回合之间可以传递的信息
								  // 如果在本地调试，有input.txt则会读取文件内容作为输入
								  // 如果在平台上，则不会去检查有无input.txt
#ifdef _BOTZONE_ONLINE
	Debug::presetString.clear();
#endif

	int myID = mainGameField.ReadInput("input.txt", data, globalData); // 输入，并获得自己ID
	srand(unsigned(Pacman::seed + myID));

	// 输出当前游戏局面状态以供本地调试。注意提交到平台上会自动优化掉，不必担心。
	mainGameField.DebugPrint();

#ifndef _BOTZONE_ONLINE
	Debug::startTime = clock();
	Debug::printInfo = true;
#endif

	// 中央决定一定要卖萌
	auto&& choice = AI(mainGameField, myID); Debug::debugData["profiling"]["TimeUsed"] = Debug::TimeThrough();
	auto&& taunt = TAUNT();// = choice == Pacman::stay ? "吓得本宝宝不敢动 TAT" : TAUNT();
	mainGameField.WriteOutput(choice, taunt, data, globalData, Debug::debugData);

#ifndef _BOTZONE_ONLINE
	system("pause");
#endif
	return 0;
}