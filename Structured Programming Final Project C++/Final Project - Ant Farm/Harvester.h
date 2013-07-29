// Header File for Harvester Subclass

#pragma once
#include "Critter.h"
#include "CritterList.h"
#include "Brainstack.h"

ref class CHarvester :
public CCritter
{

// data members

	CCritterList^	mpCritterList;

protected:
	int				miHomeRow;
	int				miHomeCol;

// methods
public:
	// Constructors
	CHarvester(void);
	CHarvester( CGameBoard^ Board, CCritterList^ pCritterList, int iRow, int iCol, Tribe eTribe );

	// Movement Functions
	virtual void	Move() override;
	void			GoHome();
	bool			WillBeHome( int iDelRow, int iDelCol );

	// String Functions
	virtual String^	 ToString() override;
};
