//Alex Eisele
// Code for Mamma 

#include "StdAfx.h"
#include "Mamma.h"
#include "stdlib.h"

#pragma region Constructors

CMamma::CMamma(void)
{
	mpCritterList = nullptr;
}

CMamma::CMamma( CGameBoard^ Board, int iRow, int iCol, CCritterList^ pCritterList, Tribe eTribe )
{
	mBoard = Board;
	miRow = iRow;
	miCol = iCol;
	mpCritterList = pCritterList;
	meType = MAMMA;
	meTribe = eTribe;

	mBoard->UpdateCount( miRow, miCol, meTribe, 1 );
}

#pragma endregion

#pragma region Action Functions

// Put a new critter in this list when you can
void CMamma::Reproduce()
{
	int			iBorn;
	CCritter^	pCritter;
	
	iBorn = rand() % 4;

	if ( miFood > (miMaxFood / 2) )
	{
		// Harvester Creators
		if ( ( iBorn == 0 ) || ( iBorn == 1 ) )
		{
			pCritter = gcnew CHarvester( mBoard, mpCritterList, miRow, miCol, meTribe );
		}

		// Killer Creator
		else if ( iBorn == 2 )
		{
			pCritter = gcnew CKiller( mBoard, mpCritterList, miRow, miCol, meTribe );
		}

		// Crusher Creator
		else if ( iBorn == 3 )
		{			
			pCritter = gcnew CCrusher( mBoard, mpCritterList, miRow, miCol, meTribe );
		}

		//// Evangelist Creator
		/*else if ( iBorn == 3 )
		{
			pCritter = gcnew CEvangelist( mBoard, mpCritterList, miRow, miCol, meTribe );
		}*/

 		mpCritterList->Append( pCritter );

		miFood -= (miMaxFood / 2);
	}
}

// ovveriding old move for mamma critter
void	CMamma::Move()
{
	// increment steps
	miTotalSteps++;
	if( (miTotalSteps % miFoodSteps == 0) && (miFood > 1) )
	{
		miFood--;
		mBoard->AdjustFood(miRow, miCol, -miFood);
	}
	// this checks if home square has food, so she can eat
	if( mBoard->GetFood(miRow, miCol) > 0 )
		Eat();

	//reproduce
	Reproduce();
}

#pragma endregion

#pragma region List Functions

// Sets list 
void CMamma::SetCritterList( CCritterList^ pCritterList)
{
	mpCritterList = pCritterList;
}

#pragma endregion

