// Alex Eisele
// Critter brain stack code

#include "StdAfx.h"
#include "BrainStack.h"

#pragma region Constructors

// Constructors
CBrainStack::CBrainStack(void)
{
	miDelRow = 0;
	miDelCol = 0;
	mpNext = nullptr;
}

CBrainStack::CBrainStack( int iDelRow, int iDelCol )
{
	miDelRow = iDelRow;
	miDelCol = iDelCol;
	mpNext = nullptr;
}	

#pragma endregion

#pragma region Stack Functions

CBrainStack^	CBrainStack::Push( int iDelRow, int iDelCol )
{
	CBrainStack^	pNewTop = gcnew CBrainStack( iDelRow, iDelCol );
	
	pNewTop->mpNext = this;
	return pNewTop;
}

CBrainStack^	CBrainStack::Pop()
{
	CBrainStack^	pNewTop;

	pNewTop = mpNext;
	mpNext = nullptr;

	return pNewTop;
}

#pragma endregion

#pragma region Location Functions

int		CBrainStack::GetDelRow()
{
	return miDelRow;
}

int		CBrainStack::GetDelCol()
{
	return miDelCol;
}

#pragma endregion

#pragma region String Functions

String^	CBrainStack::ToString()
{
	return "DeltaRow: " + miDelRow + "DeltaCol: " + miDelCol;
}

#pragma endregion