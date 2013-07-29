#pragma once
#include "Critter.h"
#include "Brainstack.h"
#include "CritterList.h"

ref class CCrusher :
public CCritter
{
//data members
	CCritterList^	mpCritterList;

public:
	CCrusher(void);
	CCrusher( CGameBoard^ Board, CCritterList^ pCritterList, int iRow, int iCol, Tribe eTribe );

	virtual void	Move() override;	
};
