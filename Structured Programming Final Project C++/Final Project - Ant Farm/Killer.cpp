//Alex Eisele
// Code for Killer

#include "StdAfx.h"
#include "Killer.h"
#include "stdlib.h"

#pragma region Constructors

CKiller::CKiller(void)
{
}
CKiller::CKiller( CGameBoard^ Board, CCritterList^ pCritterList, int iRow, int iCol, Tribe eTribe )
{
	mpCritterList = pCritterList;
	
	mbGoHome = false;
	miRow = iRow;
	miCol = iCol;
	miDelRow = 0;
	miDelCol = 0;
	miMaxFood = 60;
	miFoodSteps = 15;
	miTotalSteps = 0;
	meType = KILLER;
	meTribe = eTribe;
	mBoard = Board;

	miFood = 20;	
	mBrain = gcnew CBrainStack();	
	
	mBoard->UpdateCount(miRow, miCol, meTribe, 1);
}

#pragma endregion

#pragma region Action Functions

// Tells Killer how to move
void CKiller::Move()
{
	int			i, j;
	bool		bKill;

	bKill = false;

	if( miFood > 0)
	{
		if(mbGoHome)
			GoHome();
		else 
		{
			for( i = -1; i < 2; i++)
				for(j = -1; j < 2; j++)
				{
					if ( mBoard->HasEnemyTribe( miRow + i, miCol + j, meTribe ) && !mpCritterList->HasMamma( miRow + i, miCol + j ) )
					{
						Kill( miRow + i, miCol + j);
						miDelRow = 0;
						miDelCol = 0;
						bKill = true;
						i = 3;
						j = 3;
					}
				}
			
			if (!bKill)
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
				mBrain = mBrain->Push( -miDelRow, -miDelCol ) ;
			
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
		
		if (mBoard->GetFood( miRow, miCol ) > 0)
			Eat();
	}
}

// Kills the enemy critter
void CKiller::Kill( int iEnemyRow, int iEnemyCol )
{
	int i;
	CCritter^	pCritter;

	for ( i = 0; i <= mpCritterList->Length(); i++ )
	{
		pCritter = mpCritterList->GetCritter( i );

		if ( (pCritter->GetRow() == iEnemyRow ) && (pCritter->GetCol() == iEnemyCol) && (pCritter->GetType() != MAMMA) )
		{
			pCritter->SetFood( 0 );
			mBoard->UpdateCount( iEnemyRow, iEnemyCol, pCritter->GetTribe(), -1 );
			miFood += 5;
		}
	}
}

#pragma endregion

#pragma region Notes


/*for ( k = 0; k <= mpCritterList->Length(); k++ )
{
	pCritter = mpCritterList->GetCritter( k );
	
	if ( (pCritter->GetType() != MAMMA) && (pCritter->IsEnemyTribe( pCritter, miRow + i, miCol + j, meTribe ))  )
		Kill( pCritter );
}*/




/*int i;
CCritter^	pCritter;

for ( i = 0; i < mpCritterList->Length() + 1; i++ )
{
	pCritter = mpCritterList->GetCritter( i );
	

	if ( (pCritter->GetRow() == miRow + miDelRow ) && (pCritter->GetCol() == miCol + miDelCol) )
		pCritter->Die();
}*/


/*int		iEnemyRow, iEnemyCol;
CCritter^ pCritter;

iEnemyRow = miRow + miDelRow;
iEnemyCol = miCol + miDelCol;

mpCritterList = mpCritterList->GetFirst();

pCritter = mpCritterList->Victim( iEnemyRow, iEnemyCol );

if(pCritter != nullptr)
{
	pCritter->Die();
	miFood += 5;
}*/

#pragma endregion 