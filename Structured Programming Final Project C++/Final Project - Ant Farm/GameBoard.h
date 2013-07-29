// Header for my GameBoard class

#pragma once

#include "GameSquare.h"

using namespace System;

const int	ciNumRows = 15;
const int	ciNumCols = 20;

ref class CGameBoard
{
// Data Members
private:
	array< CGameSquare^, 2>^ mBoard;

// Methods
public:
	// Constructors
	CGameBoard(void);

	// Accessing
	
	// Wall Functions
	bool	HasWall( int iRow, int iCol );
	void	SetWall( int iRow, int iCol, bool bWall );

	// Food Functions
	void	AdjustFood( int iRow, int iCol, int iFood );
	void 	SetFood( int iRow, int iCol, int iFood );
	int		GetFood( int iRow, int iCol );
	
	// Tribe Functions
	bool	HasEnemyTribe( int iRow, int iCol, Tribe eTribe );
	bool	HasTribe( int iRow, int iCol, Tribe eTribe );
	void	UpdateCount( int iRow, int iCol, Tribe eTribe, int iChange );

	// String Functions
	String^	ToString( int iRow, int iCol );


	//bool	HasCritter( int iRow, int iCol );
	//void	SetCritter( int iRow, int iCol, bool bCritter );
};
