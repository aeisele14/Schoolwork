// Alex Eisele
// Code for my CGameSquare Class 

#include "StdAfx.h"
#include "GameSquare.h"

#pragma region Construction

CGameSquare::CGameSquare(void)
{
	int iTribe;
	
	mbWall = false;
	mbCritter = false;
	miFood = 0;
	meTribeCount = gcnew array < int, 1 >( ciNumTribes );

	// Set all values in array to 0
	for ( iTribe = 0; iTribe < ciNumTribes; iTribe++ )
		meTribeCount[ iTribe ] = 0;
}

#pragma endregion

#pragma region Wall Functions

// Lets board know if a square has a wall
bool	CGameSquare::HasWall()
{
	return mbWall;
}

// Sets a Wall on the square
void	CGameSquare::SetWall( bool bWall )
{
	mbWall = bWall;
}

#pragma endregion

#pragma region Food Functions

// Adjusts food on that square
void	CGameSquare::AdjustFood( int iFood )
{
	miFood += iFood;

	if ( miFood <= 0 )
		miFood = 0;
}

// Returns food value on that square
int		CGameSquare::GetFood()
{
	return miFood;
}

// Sets a food value on that square
void	CGameSquare::SetFood( int iFood )
{
	if ( iFood > 0 )
		miFood = iFood;
	else 
		miFood = 0;
}

#pragma endregion

#pragma region Tribe Functions

// Tells if that square has an enemy tribe
bool	CGameSquare::HasEnemyTribe( Tribe eTribe )
{
	int i;

	for ( i = 0; i < ciNumTribes; i++ )
	{
		if ( i != eTribe )
			if( meTribeCount[ i ] > 0 )
				return true;
	}	

	return false;
}

// Tells if the square has an ally tribe
bool	CGameSquare::HasTribe( Tribe eTribe )
{
	 if (meTribeCount[ eTribe ] > 0)
		return true;
	 else 
		 return false;
}	

// Updates the count of a tribe on that square
void	CGameSquare::UpdateCount( Tribe eTribe, int iChange )
{
	meTribeCount[ eTribe ] += iChange;
}

#pragma endregion

#pragma region String Functions

// Returns info about that square
String^	CGameSquare::ToString()
{
	return "Food: " + miFood + "\r\nTribeCount: " + meTribeCount;
}

#pragma endregion




#pragma region Notes

//bool	CGameSquare::HasCritter()
//{
//	return mbCritter;
//}
//
//void	CGameSquare::SetCritter( bool bCritter )
//{
//	mbCritter = bCritter;
//}

#pragma endregion