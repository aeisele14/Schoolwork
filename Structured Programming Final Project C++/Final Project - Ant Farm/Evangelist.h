// Header File for Evangelist Subclass

#pragma once
#include "critter.h"
#include "Brainstack.h"
#include "CritterList.h"

ref class CEvangelist :
public CCritter
{

// Data Members
		CCritterList^	mpCritterList;
		int				miCount;

// Methods
public:
	CEvangelist(void);
	CEvangelist( CGameBoard^ Board, CCritterList^ pCritterList, int iRow, int iCol, Tribe eTribe );

	// Action Functions
	virtual void	Move() override;
	void			Evangelize( int iEnemyRow, int iEnemyCol );
};
