// Header File for Critter List Class

#pragma once
using namespace System;
#include "Critter.h"

ref class CCritterList
{

// data members
private:
	CCritter^		mpCritter;
	CCritterList^	mpPrev;
	CCritterList^	mpNext;
	CCritterList^	mpFirst;
	
//Methods
public:
	// constructors
	CCritterList(void);
	CCritterList( CCritter^ pCritter );
	
	// accessing

	// List Editing Functions
	void			Append(CCritter^ pCritter);
	void			SetFirst(CCritterList^ pList);
	CCritterList^	Insert(CCritter^ pCritter, int iSlot);
	CCritterList^	Delete(int iSlot);

	// List Accessing Functions
	int				Length();
	int				FindDeadCritter( int& iRow, int& iCol );
	CCritterList^	GetFirst();
	CCritterList^	GetNext();	
	CCritter^		GetCritter(int iSlot);
	bool			HasMamma( int iRow, int iCol );


	// String Functions
	String^			PrintStats();
	String^			ToString(int iSlot);

	
	//CCritter^		Victim(int iEnemyRow, int iEnemyCol);
};
