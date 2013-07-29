#include "StdAfx.h"
#include "Crusher.h"
#include "stdlib.h"

CCrusher::CCrusher(void)
{
}
CCrusher::CCrusher( CGameBoard^ Board, CCritterList^ pCritterList, int iRow, int iCol, Tribe eTribe )
{
	mpCritterList = pCritterList;
	
	miRow = iRow;
	miCol = iCol;
	mBoard = Board;
	miMaxFood = 60;
	miFood = 20;
	miDelRow = 0;
	miDelCol = 0;
	miFoodSteps = 15;
	miTotalSteps = 0;
	mbGoHome = false;
	mBrain = gcnew CBrainStack();
	meType = CRUSHER;
	meTribe = eTribe;
	mBoard = Board;
	mBoard->UpdateCount(miRow, miCol, meTribe, 1);
}
void CCrusher::Move()
{
		int		i, j;
		bool	bWall;
		bWall = false;

		if(miFood > 0)
		{
			if(mbGoHome)
				GoHome();
			else
			{
				for(i = -1; i < 2; i++)
					for(j = -1; j < 2; j++)
						if ( (miRow + i >= 0) && (miRow + i < ciNumRows) && (miCol + j >= 0) && (miCol + j < ciNumCols) && !mpCritterList->HasMamma( miRow + i, miCol + j) )
							if( mBoard->HasWall(miRow + i, miCol + j) )
							{
								bWall = true;
								miDelRow = i;
								miDelCol = j;
							}

				if(!bWall)
				{
					if( (rand() % 3 == 0) || ( (miDelRow == 0) && (miDelCol == 0) ) || mBoard->HasWall(miRow + miDelRow, miCol + miDelCol) || mBoard->HasEnemyTribe( miRow + miDelRow, miCol + miDelCol, meTribe ) )
					{ 
						do
						{
							miDelRow = rand()% 3 - 1;
							miDelCol = rand() % 3 - 1;
						} while( mBoard->HasWall( miRow + miDelRow, miCol + miDelCol ) ||  mBoard->HasEnemyTribe( miRow + miDelRow, miCol + miDelCol, meTribe ) );
					}
				}

				if ( ( miDelRow != 0 ) || (miDelCol != 0) )
					mBrain = mBrain->Push( -miDelRow, -miDelCol );
			}
			mBoard->UpdateCount(miRow, miCol, meTribe, -1);
			miRow += miDelRow;
			miCol += miDelCol;
			miTotalSteps += 1;
			mBoard->UpdateCount(miRow, miCol, meTribe, 1);

			if ( miTotalSteps % miFoodSteps == 0 )
			{
				miFood -= 1;
				if ( miFood <= miMaxFood / 5 )
					mbGoHome = true;
			}
			if(mBoard->GetFood(miRow, miCol) > 0)
				Eat();
		}
		// removes the wall
		if(bWall)
		{
			mBoard->SetWall(miRow, miCol, false);
			miFood +=10;
		}	
}
