// Header file for Gamesquare class

#pragma once

using namespace System;

// Declare Types and Tribes
enum		CritterType{ MAMMA, HARVESTER, KILLER, EVANGELIST, CRUSHER };
const int	ciNumTypes = 5;

enum		Tribe{ BLUE, RED };
const int	ciNumTribes = 2;

ref class CGameSquare
{

// Data Members
private:
	bool	mbWall;
	bool	mbCritter;
	int		miFood;
	array< int, 1>^ meTribeCount;

// Methods
public:
	// Constructors
	CGameSquare(void);

	// Wall Functions
	bool	HasWall();
	void	SetWall( bool bWall );

	// Food Functions
	void	AdjustFood( int iFood );
	int		GetFood();
	void	SetFood( int iFood );

	// Tribe Functions
	bool	HasEnemyTribe( Tribe eTribe );
	bool	HasTribe( Tribe eTribe );
	void	UpdateCount( Tribe eTribe, int iChange );	

	// String Functions
	virtual	String^	ToString() override;




	//bool	HasCritter();
	//void	SetCritter( bool bCritter );
};
