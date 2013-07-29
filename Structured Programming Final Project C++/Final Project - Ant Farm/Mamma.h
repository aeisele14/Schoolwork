// Header File for Mamma SubClass

#pragma once
#include "Critter.h"
#include "CritterList.h"
#include "Harvester.h"
#include "Killer.h"
#include "Evangelist.h"
#include "Crusher.h"

ref class CMamma :
public CCritter
{	
// data members

	CCritterList^		mpCritterList;

// Methods
public:
	// Constructors
	CMamma(void);
	CMamma( CGameBoard^ Board, int iRow, int iCol, CCritterList^ pCritterList, Tribe eTribe );
	
	// Action Functions
	void		Reproduce();
		// override Move and ToString
		virtual void	Move() override;

	// List Functions
	void		SetCritterList( CCritterList^ pCritterList );

};
