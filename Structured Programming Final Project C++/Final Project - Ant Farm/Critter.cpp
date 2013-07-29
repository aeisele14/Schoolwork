// Alex Eisele
// Code for Critter

#include "StdAfx.h"
#include "Critter.h"
#include "stdlib.h" // Allows the use of the Random function

#pragma region Constructors

// Constructors
CCritter::CCritter(void)
{
	mbGoHome = false;
	miRow = 0;
	miCol = 0;
	miDelRow = 0;
	miDelCol = 0;
	miMaxFood = 60;	
	miFoodSteps = 15;
	miTotalSteps = 0;		
	mBoard = gcnew CGameBoard();

	miFood = 60;
	mBrain = nullptr;
}
CCritter::CCritter( CGameBoard^ Board, int iRow, int iCol )
{
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
	mBoard = Board;

	miFood = 60;	
	mBrain = nullptr;
}

#pragma endregion

# pragma region Moving Functions

// moves the creature around the board - randomly (1 row &&/|| 1 col)
void CCritter::Move()
{	
}

// Tells the Critter how to Go Home
void CCritter::GoHome()
{
	int	iHomeFood;

	miDelRow = mBrain->GetDelRow();
	miDelCol = mBrain->GetDelCol();
	iHomeFood = 0;
	
	// First see if the critter is home already
	if (  ( miDelRow == 0 ) && (miDelCol == 0) )
	{
		mbGoHome = false;		
		
		iHomeFood = (miMaxFood / 2) - miFood;
		if ( iHomeFood > mBoard->GetFood( miRow, miCol ) )
			iHomeFood = mBoard->GetFood( miRow, miCol );

		//mBoard->AdjustFood( miRow, miCol, -iHomeFood );
		miFood += iHomeFood;
	}
	else
	{
		mBrain = mBrain->Pop();
	}
}

#pragma endregion

#pragma region Location Functions

// Provides access to Critters Row
int		CCritter::GetRow()
{
	return miRow;
}

// Provides access to Critters Column
int		CCritter::GetCol()
{
	return miCol;
}

// passed integers by reference
void	CCritter::GetRowCol( int& iRow, int& iCol )
{
	iRow = miRow;
	iCol = miCol;
}

#pragma endregion

#pragma region Food Functions

// Allows critter to eat
void CCritter::Eat()
{
	int iDelFood;

	if ( (miMaxFood - miFood) <= mBoard->GetFood(miRow, miCol) )
	{
		iDelFood = miMaxFood - miFood;
		mbGoHome = true;
	}
	else
		iDelFood = mBoard->GetFood(miRow, miCol);

	miFood += iDelFood;
	mBoard->AdjustFood(miRow, miCol, -iDelFood);
}

// Access to the critters food amount
int		CCritter::CheckFood()
{
	return miFood;
}

// Kills the critter by taking away all food
void	CCritter::SetFood( int iFood )
{
	miFood = iFood;
}

#pragma endregion

#pragma region Type and Tribe Functions

// Access to the Critters Type
CritterType CCritter::GetType()
{
	return meType;
}

// Changes critter's type to verified type
void		CCritter::SetType(CritterType eType)
{
	meType = eType;
}

// Access to Critters Tribe
Tribe		CCritter::GetTribe()
{
	return meTribe;
}

// Changes Critters Tribe
void		CCritter::SetTribe( Tribe eTribe )
{
	meTribe = eTribe;
}

#pragma endregion

#pragma region String Functions

// Info about the critter
String^	CCritter::ToString()
{
	if( mbGoHome )
		return "Going Home";
	else
		return "\r\nCFood " + miFood + "; " + mBrain->ToString();
}

#pragma endregion




#pragma region Notes

// Notes

// Hungry
//miFood <= ( miMaxFood / 5 )

// Satisfied and can leave home with energy
//( miFood > (miMaxFood / 2) )

#pragma endregion