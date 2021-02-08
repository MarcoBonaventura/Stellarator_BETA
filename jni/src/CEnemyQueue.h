#ifndef _CENEMYQUEUE_H_
#define _CENEMYQUEUE_H_

#include <vector>

//==============================================================================
enum 
{
	ENEMY_SXM	= 0,
	ENEMY_SX1	= 1,
	ENEMY_SX2	= 2,
	ENEMY_SX3	= 3,
	ENEMY_SX4   = 4,
	ENEMY_MM1	= 5,
	ENEMY_MM2	= 6,
	ENEMY_MM3	= 7,
	ENEMY_MM4	= 8,
	ENEMY_MM5	= 9,
	ENEMY_BOSS	= 10	
};

//==============================================================================
class CEnemyQueue {

	public:

		//static std::vector<CEnemyQueue> EnemyList;
		static std::vector<std::vector<CEnemyQueue>> EnemyList;

		int     EnemySize;
		int     EnemyTimer;
		int		DeltaA;
		int		DeltaB;

	public:
		CEnemyQueue();

};

//==============================================================================
#endif
