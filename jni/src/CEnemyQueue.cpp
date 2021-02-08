//==============================================================================
#include "CEnemyQueue.h"

std::vector<std::vector<CEnemyQueue>> CEnemyQueue::EnemyList;

//==============================================================================
CEnemyQueue::CEnemyQueue() {

	EnemySize	= 0;
	EnemyTimer	= 0;
	DeltaA		= 0;
	DeltaB		= 0;

}

//==============================================================================
