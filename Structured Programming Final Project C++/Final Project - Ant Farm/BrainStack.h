// header file for Brainstack Class

#pragma once

using namespace System;

ref class CBrainStack
{

// data members
private:
	int				miDelRow;
	int				miDelCol;
	CBrainStack^	mpNext;

// methods
public:
	// Construction
	CBrainStack(void);
	CBrainStack( int iDelRow, int iDelCol );

	// Accessing
	
	// Stack Functions
	CBrainStack^	Push( int iDelRow, int iDelCol );
	CBrainStack^	Pop();

	// Location Functions
	int				GetDelRow();
	int				GetDelCol();

	// String Functions
	virtual String^	ToString() override;
};
