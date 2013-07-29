// Alex Eisele
// Code for my GameBoard class

#include "StdAfx.h"
#include "GameBoard.h"

#pragma region Construction

// Construction
CGameBoard::CGameBoard(void)
{
	int iRow, iCol;

	mBoard = gcnew array< CGameSquare^, 2 >(ciNumRows, ciNumCols);

	// Puts a gamesquare in each slot of the 2D array
	for ( iRow = 0; iRow < ciNumRows; iRow++ )
		for ( iCol = 0; iCol < ciNumCols; iCol++ )
			mBoard[iRow, iCol] = gcnew CGameSquare();
}

#pragma endregion

#pragma region Wall Functions

bool	CGameBoard::HasWall( int iRow, int iCol )
{
	if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
		return mBoard[ iRow, iCol]->HasWall();
	else 
		return true;
}

void	CGameBoard::SetWall( int iRow, int iCol, bool bWall )
{
	if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
		mBoard[ iRow, iCol]->SetWall( bWall );
}

#pragma endregion

#pragma region Food Functions

void	CGameBoard::AdjustFood(int iRow, int iCol, int iFood )
{
	if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
		mBoard[ iRow, iCol]->AdjustFood( iFood );
}

void	CGameBoard::SetFood( int iRow, int iCol, int iFood )
{
	if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
		mBoard[ iRow, iCol]->SetFood( iFood );
}

int		CGameBoard::GetFood( int iRow, int iCol )
{
	if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
		return mBoard[ iRow, iCol ]->GetFood();
	else
		return 0;
}

#pragma endregion

#pragma region Tribe Functions

void	CGameBoard::UpdateCount( int iRow, int iCol, Tribe eTribe, int iChange )
{
	if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
		mBoard[ iRow, iCol ]->UpdateCount( eTribe, iChange );
}

bool	CGameBoard::HasEnemyTribe( int iRow, int iCol, Tribe eTribe )
{
	if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
		return mBoard[ iRow, iCol]->HasEnemyTribe( eTribe );
	else 
		return false;
}

bool	CGameBoard::HasTribe( int iRow, int iCol, Tribe eTribe )
{
	if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
		return mBoard[ iRow, iCol]->HasTribe( eTribe );
	else 
		return false;
}

#pragma endregion

#pragma region String Functions

String^	CGameBoard::ToString( int iRow, int iCol )
{
	if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
		return mBoard[iRow, iCol]->ToString();
}

#pragma endregion




#pragma region Notes

//bool	CGameBoard::HasCritter( int iRow, int iCol )
//{
//	if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
//		return mBoard[ iRow, iCol]->HasCritter();
//	else 
//		return true;
//}
//
//void	CGameBoard::SetCritter(int iRow, int iCol, bool bCritter)
//{
//		if ( (iRow >= 0) && (iRow < ciNumRows) && (iCol >= 0) && (iCol < ciNumCols) )
//		mBoard[ iRow, iCol]->SetCritter( bCritter );
//}

#pragma endregion