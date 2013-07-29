// Header file for the Critters class
#pragma once

#include "GameBoard.h"
#include "Brainstack.h"

using namespace System;

ref class CCritter
{

// data members
protected:
	bool			mbGoHome;
	int				miRow;
	int				miCol;
	int				miDelRow;
	int				miDelCol;
	int				miHomeRow;
	int				miHomeCol;
	int				miMaxFood;
	int				miFoodSteps;
	int				miTotalSteps;
	CritterType		meType;
	Tribe			meTribe;	
	CGameBoard^		mBoard;

public:
	int				miFood;
	CBrainStack^	mBrain;

// methods
public:
	// constructors
	CCritter(void);
	CCritter( CGameBoard^ Board, int iRow, int iCol );

	// Moving Functions
	virtual void	Move();
	void			GoHome();

	// Location Functions
	int				GetRow();
	int				GetCol();
		// passed integers by reference
		void			GetRowCol( int& iRow, int& iCol );

	// Food Functions
	void			Eat();
	int				CheckFood();
	void			SetFood( int iFood );

	// Type and Tribe Functions
	CritterType		GetType();
	void			SetType(CritterType eType);
	Tribe			GetTribe();
	void			SetTribe( Tribe eTribe );

	// String Functions
	virtual String^	 ToString() override;
};
