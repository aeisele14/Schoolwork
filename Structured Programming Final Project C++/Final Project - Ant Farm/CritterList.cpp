// Alex Eisele
// Code for Critter List

#include "StdAfx.h"
#include "CritterList.h"

#pragma region Constructors
CCritterList::CCritterList(void)
{
	mpCritter = nullptr;
	mpPrev = nullptr;
	mpNext = nullptr;
	mpFirst = this;
}
CCritterList::CCritterList(CCritter^ pCritter)
{
	mpCritter = pCritter;
	mpPrev = nullptr;
	mpNext = nullptr;
	mpFirst = this;
}

#pragma endregion 

#pragma region List Editing Functions

// Append an item to the end of the list - uses recursion
void CCritterList::Append(CCritter ^pCritter)
{
	CCritterList^	pList;
	
	if ( mpNext == nullptr )
	{
		pList = gcnew CCritterList( pCritter );
		mpNext = pList;
		pList->mpPrev = this;
		pList->mpFirst = this->mpFirst;
	}
	else
		mpNext->Append( pCritter );
}

// Set the First critter in the list
void	CCritterList::SetFirst(CCritterList ^pList)
{
	mpFirst= pList;
	if(mpNext != nullptr)
		mpNext->SetFirst(pList);
}

// Insert - insert the given value into the given slot, return the address of the first element in the list.
CCritterList^ CCritterList::Insert(CCritter^ pCritter, int iSlot)
{
	CCritterList^	pList;
	if(iSlot < 0)
		return mpFirst;

	else if (iSlot == 0)
	{
		pList = gcnew CCritterList( pCritter );
		// check to see if we are replacing the first item
		if( mpPrev == nullptr )
		{
			mpPrev = pList;
			pList->mpNext = this;
			SetFirst( pList );
		}
		else
		{
		
		mpPrev->mpNext = pList;
		pList->mpPrev = mpPrev;
		mpPrev = pList;
		pList->mpNext = this;
		}
	}
	else if (mpNext != nullptr)
		mpNext->Insert(pCritter, iSlot - 1); 

	return mpFirst;
}

// Delete - delete the given value from the given slot, return the new address of the next element in the list.
CCritterList^ CCritterList::Delete(int iSlot)
{
	CCritterList^ pNewFirst;
	// handles negatives
	if(iSlot < 0)
		return mpFirst;
	// handles 1st element deletion
	if((mpFirst == this) && (iSlot == 0))
	{
		// checks to see if only list item
		if(mpNext == nullptr)
			return nullptr;
		else
		{
			mpNext->mpPrev = nullptr;
			mpNext->SetFirst(mpNext);
			pNewFirst = mpNext;
			mpNext = nullptr;
			return pNewFirst;
		}
	}
	else if (iSlot == 0)
	{
		mpPrev->mpNext = mpNext;
		if(mpNext != nullptr)
			mpNext->mpPrev = mpPrev;
		mpPrev = nullptr;
		mpNext = nullptr;
	}
	else if (mpNext != nullptr)
		mpNext->Delete(iSlot - 1);
	
	return mpFirst;
}

#pragma endregion

#pragma region List Accessing Functions

// Length - return the list length
int		CCritterList::Length()
{
	int		iCount;
	
	iCount = 1;
	
	if( mpNext != nullptr )
		iCount += mpNext->Length();
		
	return iCount;
}

// Find a dead critter in the list
int		CCritterList::FindDeadCritter( int& iRow, int& iCol )
{	
	CCritter^ pCritter;
	int i;

	for ( i = 0; i <= Length(); i++)
	{
		pCritter = GetCritter( i );

		// if dead return that critters spot in the list and find dead critters location on the board
		if ( pCritter->CheckFood() <= 0 )
		{
			iRow = pCritter->GetRow();
			iCol = pCritter->GetCol();
			return i; 
		}
	}
	
	return -1; 
}

// Access to the first critter in the list
CCritterList^	CCritterList::GetFirst()
{
	return mpFirst;
}

// Access to the next Critter in the list
CCritterList^	CCritterList::GetNext()
{
	return mpNext;	
}

// GetCritter - returns the critter
CCritter^	CCritterList::GetCritter(int iSlot)
{
	if( (iSlot <= 0) || (mpNext == nullptr) )
		return mpCritter;
	else
		return mpNext->GetCritter( iSlot - 1 );
}

bool		CCritterList::HasMamma( int iRow, int iCol )
{
	if ( ( iRow == GetCritter( 0 )->GetRow() ) && ( iCol == GetCritter( 0 )->GetCol() ) )
		return true;
	else if ( ( iRow == GetCritter( 1 )->GetRow() ) && ( iCol == GetCritter( 1 )->GetCol() ) )
		return true;
	else
		return false;
}

#pragma endregion

#pragma region String Functions

String^		CCritterList::PrintStats()
{
	int		i, iBlueCount, iRedCount, iHarvesterB, iHarvesterR, iKillerB, iKillerR, iCrusherB, iCrusherR, iEvangelistB, iEvangelistR; 

	CCritter^	pCritter;
	String^		strPrint;

	iBlueCount = 0;
	iRedCount = 0;
	iHarvesterB = 0;
	iHarvesterR = 0;
	iKillerB = 0;
	iKillerR = 0;
	iCrusherB = 0;
	iCrusherR = 0;
	iEvangelistB = 0;
	iEvangelistR = 0; 

	for(i = 0; i < Length(); i++)
	{
		pCritter = GetCritter(i);

		if(pCritter->GetTribe() == BLUE)
		{
			iBlueCount++;
			if(pCritter->GetType() == HARVESTER)
				iHarvesterB++;
			else if(pCritter->GetType() == KILLER)
				iKillerB++;
			else if(pCritter->GetType() == CRUSHER)
				iCrusherB++;
		}
		else
		{
			iRedCount++;
			if(pCritter->GetType() == HARVESTER)
				iHarvesterR++;
			else if(pCritter->GetType() == KILLER)
				iKillerR++;
			else if(pCritter->GetType() == CRUSHER)
				iCrusherR++;
		}

	}
	strPrint =		"Blue Tribe: " + iBlueCount + "                 Red Tribe: " + iRedCount + "\r\n" + "\r\n"
					"Harvesters: " + iHarvesterB + "                Harvesters: " + iHarvesterR + "\r\n" + "\r\n"
					"Killers: " + iKillerB +		  "                        Killers: " + iKillerR + "\r\n" + "\r\n"
					"Crushers: " + iCrusherB +	  "                   Crushers: " + iCrusherR;

	return strPrint;
}

// ToString - return a string which shows all the list items
String^		CCritterList::ToString(int iSlot)
{
	return GetCritter( iSlot )->ToString();
}

#pragma endregion


#pragma region Notes

// Alternate FindDeadCritter Function
/*int	iSlot;

	iSlot = 1;

	if(mpCritter->CheckFood() < 1)
	{
		mpCritter->GetRowCol(iRow, iCol);
		return 0;
	}
	else
	{
		if(mpNext != nullptr)
			iSlot += mpNext->FindDeadCritter(iRow, iCol);
		else
			return mpFirst->Length() * -1;
	}
	return iSlot;*/



//CCritter^	CCritterList::Victim(int iEnemyRow, int iEnemyCol)
//{
//	int iRow, iCol;
//
//	mpCritter->GetRowCol(iRow, iCol);
//
//	if((iRow == iEnemyRow) && (iCol == iEnemyCol) && (mpCritter->GetType() != MAMMA) )
//		return mpCritter;
//
//	else
//	{
//		if(mpNext != nullptr)
//			mpNext->Victim(iEnemyRow, iEnemyCol);
//		else
//			return nullptr;
//	}
//
//	return mpNext->Victim(iEnemyRow, iEnemyCol);
//}

#pragma endregion
