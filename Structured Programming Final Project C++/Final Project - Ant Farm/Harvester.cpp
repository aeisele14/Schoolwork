// Alex Eisele
// Code for Harvester

#include "StdAfx.h"
#include "Harvester.h"
#include "stdlib.h"

#pragma region Constructors

CHarvester::CHarvester(void)
{
}

CHarvester::CHarvester( CGameBoard^ Board, CCritterList^ pCritterList, int iRow, int iCol, Tribe eTribe )
{
	mpCritterList = pCritterList;
	
	mbGoHome = false;
	miRow = iRow;
	miCol = iCol;
	miDelRow = 0;
	miDelCol = 0;

	miHomeRow = iRow;
	miHomeCol = iCol;

	miMaxFood = 60;
	miFoodSteps = 15;
	miTotalSteps = 0;
	meType = HARVESTER;
	meTribe = eTribe;
	mBoard = Board;
	
	miFood = 20;
	mBrain = gcnew CBrainStack();
	
	mBoard->UpdateCount( miRow, miCol, meTribe, 1 );
}

#pragma endregion

#pragma region Movement Functions

// Tells Harvester how to move
void CHarvester::Move()
{	
	int			i, j;
	bool		bFood;

	bFood = false;

	if ( miFood > 0 )
	{
		if ( mbGoHome )
			GoHome();
		else
		{
			// See if there is food in an adjacent square, if so and if the critter is hungry, move to it
			if ( miFood < miMaxFood )
				for( i = -1; i < 2; i++)
					for(j = -1; j < 2; j++)							
						if( ( mBoard->GetFood( miRow + i, miCol + j ) > 0 ) && !WillBeHome( i, j ) &&  !mBoard->HasEnemyTribe( miRow + i, miCol + j, meTribe ) && !mpCritterList->HasMamma( miRow + i, miCol + j)  )
						{
								bFood = true;
								miDelRow = i;
								miDelCol = j;
						}

			if ( !bFood )
			{
				// Higher probability
				if ( ( rand() % 3 == 0 ) || ( mBoard->HasWall( miRow + miDelRow, miCol + miDelCol ) )
					|| ( ( miDelRow == 0 ) && ( miDelCol == 0 ) ) || WillBeHome( miDelRow, miDelCol ) || mBoard->HasEnemyTribe( miRow + miDelRow, miCol + miDelCol, meTribe ) ) 
				{	
					do
					{
						miDelRow = rand()% 3 - 1;
						miDelCol = rand() % 3 - 1;
					} while( mBoard->HasEnemyTribe( miRow + miDelRow, miCol + miDelCol, meTribe ) || (mBoard->HasWall( miRow + miDelRow, miCol + miDelCol )) || (WillBeHome( miDelRow, miDelCol )) );
				}
			}
			
			if ( ( miDelRow != 0 ) || (miDelCol != 0) )
				mBrain = mBrain->Push( -miDelRow, -miDelCol );
		}

		mBoard->UpdateCount( miRow, miCol, meTribe, -1 );
		miRow += miDelRow;
		miCol += miDelCol;
		miTotalSteps += 1;
		mBoard->UpdateCount( miRow, miCol, meTribe, 1 );

		if ( miTotalSteps % miFoodSteps == 0 )
		{
			miFood -= 1;
			if ( miFood <= miMaxFood / 5 )
				mbGoHome = true;
		}

		if ( bFood )
			Eat();
	}
}

// Tells Critter how to go home ( I think this is the same as the one in the Critter
void CHarvester::GoHome()
{
	int	iHomeFood;

	miDelRow = mBrain->GetDelRow();
	miDelCol = mBrain->GetDelCol();
	iHomeFood = 0;

	if (  ( miDelRow == 0 ) && (miDelCol == 0) )
	{
		mbGoHome = false;		
		
		iHomeFood = (miMaxFood / 2) - miFood;
		if ( iHomeFood > mBoard->GetFood( miRow, miCol ) )
			iHomeFood = mBoard->GetFood( miRow, miCol );

		mBoard->AdjustFood( miRow, miCol, -iHomeFood );
		miFood += iHomeFood;
	}
	else
	{
		mBrain = mBrain->Pop();
	}
}

// tells the Harvester if they will be home so it won't bounce back and forth between home and first step
bool	CHarvester::WillBeHome( int iDelRow, int iDelCol )
{
	if ( (miRow + iDelRow == miHomeRow) && ( miCol + iDelCol == miHomeCol ) )
		return true;
	else
		return false;
}

#pragma endregion

#pragma region String Functions

// String for info about harvester
String^	CHarvester::ToString()
{
	if( mbGoHome )
		return "Going Home";
	else
		return "\r\nCFood " + miFood + "; " + mBrain->ToString();
}

#pragma endregion