// Header File for Killer Subclass

#pragma once

#include "critter.h"
#include "Brainstack.h"
#include "CritterList.h"

ref class CKiller :
public CCritter
{
//data members
	CCritterList^	mpCritterList;

// Methods
public:
	//Constructors
	CKiller(void);
	CKiller( CGameBoard^ Board, CCritterList^ pCritterList, int iRow, int iCol, Tribe eTribe );

	// Action Functions
	virtual void	Move() override;
	void			Kill(int iEnemyRow, int iEnemyCol);

};

