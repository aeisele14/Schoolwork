// Alex Eisele
// Code for Evangelist

#include "StdAfx.h"
#include "Evangelist.h"
#include "stdlib.h"

#pragma region Constructors

CEvangelist::CEvangelist(void)
{
}
CEvangelist::CEvangelist( CGameBoard^ Board, CCritterList^ pCritterList, int iRow, int iCol, Tribe eTribe )
{
	mpCritterList = pCritterList;	
	miCount = 0;
	
	mbGoHome = false;
	miRow = iRow;
	miCol = iCol;
	miDelRow = 0;
	miDelCol = 0;
	miMaxFood = 60;
	miFoodSteps = 15;
	miTotalSteps = 0;
	meType = EVANGELIST;
	meTribe = eTribe;
	mBoard = Board;

	miFood = 20;	
	mBrain = gcnew CBrainStack();	
	
	mBoard->UpdateCount(miRow, miCol, meTribe, 1);
}

#pragma endregion

#pragma region Action Functions

// Tells Evangelist how to move
void CEvangelist::Move()
{
	int			i, j;
	bool		bEvangelize;

	bEvangelize = false;

	if( miFood > 0)
	{
		if(mbGoHome)
			GoHome();
		else 
		{
			for( i = -1; i < 2; i++)
				for(j = -1; j < 2; j++)						
					if ( mBoard->HasEnemyTribe( miRow + i, miCol + j, meTribe ) && !mpCritterList->HasMamma( miRow + i, miCol + j ) )
					{
						bEvangelize = true;
						miDelRow = i;
						miDelCol = j;
					}
			if (!bEvangelize)
			{
				if (( rand() % 3 == 0 ) || ( mBoard->HasWall( miRow + miDelRow, miCol + miDelCol ) )
					|| ( ( miDelRow == 0 ) && ( miDelCol == 0 ) ) )
				{
					do
					{
						miDelRow = rand()% 3 - 1;
						miDelCol = rand() % 3 - 1;
					}while( mBoard->HasWall( miRow + miDelRow, miCol + miDelCol ) );
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

		if(miTotalSteps % miFoodSteps == 0)
		{
			miFood -= 1;
			if(miFood <= (miMaxFood /5))
				mbGoHome = true;
		}
		
		if (bEvangelize)
			Evangelize( miRow, miCol );

		if (mBoard->GetFood( miRow, miCol ) > 0)
			Eat();
	}
}

// Converts the enemy critter
void CEvangelist::Evangelize( int iEnemyRow, int iEnemyCol )
{
	int i;
	CCritter^	pCritter;

	for ( i = 0; i <= mpCritterList->Length(); i++ )
	{
		pCritter = mpCritterList->GetCritter( i );

		//miCount++;

		if ( (pCritter->GetRow() == iEnemyRow ) && (pCritter->GetCol() == iEnemyCol) && (pCritter->GetType() != MAMMA) )
			pCritter->SetTribe( meTribe );

		/*if ( pCritter == nullptr )
			miCount = 0;*/
	}
}

#pragma endregion
