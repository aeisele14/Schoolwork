#pragma once

#include "GameBoard.h"
#include "CritterList.h"
#include "Critter.h"
#include "CritterList.h"
#include "BrainStack.h"
#include "Mamma.h"
#include "Harvester.h"

namespace FinalProjectAntFarm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	// board dimensions constants:
	const int	ciWidth = 16;
	//const int	ciNumRows = 15; - defined in CGameBoard
	//const int	ciNumCols = 20;

	public ref class Form1 : public System::Windows::Forms::Form
	{
		// my data members
	private:
		bool			mbStarted;
		bool			mbRunning;
		bool			mbDrawGrass;
		bool			mbDrawWall;
		bool			mbDrawFood;

		bool			mbDrawCritter;

		Image^			mimgGrass;
		Image^			mimgWall;
		Image^			mimgFood;

		Image^			mimgBlueHarvester;
		Image^			mimgRedHarvester;
		Image^			mimgBlueMamma;
		Image^			mimgRedMamma;
		Image^			mimgBlueKiller;
		Image^			mimgRedKiller;
		Image^			mimgBlueEvangelist;
		Image^			mimgRedEvangelist;
		Image^			mimgBlueCrusher;
		Image^			mimgRedCrusher;

		CGameBoard^		mBoard;
		CMamma^			mMammaCritter;
		CCritter^		mCritter;
		CCritterList^	mCritterList;
		//TODO - temporary data members for a bouncing BlueHarvester
		int			miRow;
		int			miCol;
		int			miDelRow;
		int			miDelCol;
	private: System::Windows::Forms::Label^  lblStats;








			 int			miFood;






			

	public:
		Form1(void)
		{
			InitializeComponent();
			// NOT SURE WHAT WE BUILD HERE, BUT IT WAS FOR THE GAME AREA
			pnlBoard->Width = ciNumCols * ciWidth + 4;
			pnlBoard->Height = ciNumRows * ciWidth + 4;

			mBoard = gcnew CGameBoard();
			mMammaCritter = gcnew CMamma( mBoard, 0, 0, nullptr , BLUE );
			mCritterList = gcnew CCritterList( mMammaCritter );
			mMammaCritter->SetCritterList( mCritterList );
			mMammaCritter = gcnew CMamma( mBoard, 14, 19, mCritterList, RED );
			mCritterList->Append( mMammaCritter );

			mbStarted = false;
			mbRunning = false;
			mbDrawGrass = false;
			mbDrawWall = false;
			mbDrawFood = false;

			mbDrawCritter = false;

			mimgGrass = Image::FromFile( "Grass.bmp" );
			mimgWall = Image::FromFile( "Wall.bmp" );
			mimgFood = Image::FromFile( "food.bmp" );
			mimgBlueHarvester = Image::FromFile( "Harvester (Blue).bmp" );
			mimgRedHarvester = Image::FromFile( "Harvester (Red).bmp" );
			mimgBlueMamma = Image::FromFile( "Mamma (Blue).bmp" );
			mimgRedMamma = Image::FromFile( "Mamma (Red).bmp" );
			mimgBlueKiller = Image::FromFile( "Killer (Blue).bmp" );
			mimgRedKiller = Image::FromFile( "Killer (Red).bmp" );
			mimgBlueEvangelist = Image::FromFile( "Evangelist (Blue).bmp" );
			mimgRedEvangelist = Image::FromFile( "Evangelist (Red).bmp" );
			mimgBlueCrusher = Image::FromFile( "Crusher (Blue).bmp" );
			mimgRedCrusher = Image::FromFile( "Crusher (Red).bmp" );

			miRow = 2;
			miCol = 0;
			miDelRow = 1;
			miDelCol = 1;
			miFood = 5;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	// Windows generated data members
	private: System::Windows::Forms::Panel^  pnlBoard;
	private: System::Windows::Forms::ComboBox^  cboTool;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Button^  btnRun;
	private: System::Windows::Forms::Timer^  timer1;
	protected: 


	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pnlBoard = (gcnew System::Windows::Forms::Panel());
			this->cboTool = (gcnew System::Windows::Forms::ComboBox());
			this->btnRun = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->lblStats = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// pnlBoard
			// 
			this->pnlBoard->Location = System::Drawing::Point(12, 39);
			this->pnlBoard->Name = L"pnlBoard";
			this->pnlBoard->Size = System::Drawing::Size(244, 164);
			this->pnlBoard->TabIndex = 0;
			this->pnlBoard->Visible = false;
			// 
			// cboTool
			// 
			this->cboTool->FormattingEnabled = true;
			this->cboTool->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Food", L"Wall", L"Grass"});
			this->cboTool->Location = System::Drawing::Point(12, 12);
			this->cboTool->Name = L"cboTool";
			this->cboTool->Size = System::Drawing::Size(121, 21);
			this->cboTool->TabIndex = 1;
			// 
			// btnRun
			// 
			this->btnRun->Location = System::Drawing::Point(181, 10);
			this->btnRun->Name = L"btnRun";
			this->btnRun->Size = System::Drawing::Size(75, 23);
			this->btnRun->TabIndex = 2;
			this->btnRun->Text = L"Run";
			this->btnRun->UseVisualStyleBackColor = true;
			this->btnRun->Click += gcnew System::EventHandler(this, &Form1::btnRun_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 250;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// lblStats
			// 
			this->lblStats->AutoSize = true;
			this->lblStats->Location = System::Drawing::Point(48, 324);
			this->lblStats->Name = L"lblStats";
			this->lblStats->Size = System::Drawing::Size(0, 13);
			this->lblStats->TabIndex = 3;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(424, 442);
			this->Controls->Add(this->lblStats);
			this->Controls->Add(this->btnRun);
			this->Controls->Add(this->cboTool);
			this->Controls->Add(this->pnlBoard);
			this->Name = L"Form1";
			this->Text = L"Ant Farm";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

# pragma region Form Loader

// Handles form load
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
{
	cboTool->SelectedIndex = 0;
}

#pragma endregion 

#pragma region Drawing Handler 
// draws the border around the game play area, by overriding the OnPaint
protected:
virtual void OnPaint( PaintEventArgs^ e ) override
{
	Pen^		pBlackPen = gcnew Pen(Color::Black, 2);
	Rectangle	rect;
	
	if( !mbStarted )
	{
		rect.Y = pnlBoard->Location.Y;
		rect.X = pnlBoard->Location.X;
		rect.Width = pnlBoard->Width - 2;
		rect.Height = pnlBoard->Height -2;
		e->Graphics->DrawRectangle( pBlackPen, rect );

		mbStarted = true;

		// TODO - for now, we draw the whole board on startup
		// this builds the entire screen with the grass image
		Bitmap^		bmp = gcnew Bitmap(pnlBoard->Width - 4, pnlBoard->Height - 4, e->Graphics);
		IntPtr		ip = bmp->GetHbitmap();
		Image^		img = Image::FromHbitmap( ip );
		Graphics^	gr = Graphics::FromImage( img );

		int	iRow, iCol;

		for ( iRow = 0; iRow < ciNumRows; iRow++ )
			for ( iCol = 0; iCol < ciNumCols; iCol++ )
				gr->DrawImage( mimgGrass, iCol * ciWidth, iRow * ciWidth );
		
		e->Graphics->DrawImage( img, rect.X + 1, rect.Y + 1 );
	}
	
	// This is where you will change the images to draw the different types and tribes

	if ( mbDrawGrass )
		e->Graphics->DrawImage( mimgGrass, e->ClipRectangle );	
	else if ( mbDrawWall )
		e->Graphics->DrawImage( mimgWall, e->ClipRectangle );
	else if ( mbDrawFood )
		e->Graphics->DrawImage( mimgFood, e->ClipRectangle );

	else if (mbDrawCritter)
	{
		CritterType eType;
		Tribe		eTribe;

		eType = mCritter->GetType();
		eTribe = mCritter->GetTribe();

		if (eTribe == BLUE)
		{
			if (eType == MAMMA)
				e->Graphics->DrawImage( mimgBlueMamma, e->ClipRectangle );
			else if ( eType == HARVESTER )
				e->Graphics->DrawImage( mimgBlueHarvester, e->ClipRectangle );
			else if ( eType == KILLER )
				e->Graphics->DrawImage( mimgBlueKiller, e->ClipRectangle );
			else if ( eType == EVANGELIST )
				e->Graphics->DrawImage( mimgBlueEvangelist, e->ClipRectangle );
			else if ( eType == CRUSHER )
				e->Graphics->DrawImage( mimgBlueCrusher, e->ClipRectangle );
		}
		else if (eTribe == RED)
		{
			if (eType == MAMMA)					
				e->Graphics->DrawImage( mimgRedMamma, e->ClipRectangle );					
			else if ( eType == HARVESTER )
				e->Graphics->DrawImage( mimgRedHarvester, e->ClipRectangle );
			else if ( eType == KILLER )
				e->Graphics->DrawImage( mimgRedKiller, e->ClipRectangle );
			else if ( eType == EVANGELIST )
				e->Graphics->DrawImage( mimgRedEvangelist, e->ClipRectangle );
			else if ( eType == CRUSHER )
				e->Graphics->DrawImage( mimgRedCrusher, e->ClipRectangle );
		}
	}
}

#pragma endregion

#pragma region Mouse Click and Combo Box Selection

// override the mouse click event, so we can draw in our panel **GOING TO CHANGE THIS LATER**
virtual void OnMouseClick( MouseEventArgs^ e ) override
{
	int iRow, iCol;

	if( IsInPanel( e->X, e->Y ) )
	{
		PointToRowCol( e->X, e->Y, iRow, iCol);

		if ( cboTool->SelectedText == "Grass" )
		{
			mbDrawGrass = true;
			mBoard->SetWall( iRow, iCol, false );
		}
		else if ( cboTool->SelectedText == "Wall" )
		{
			mbDrawWall = true;
			mBoard->SetWall( iRow, iCol, true );
		}
		else if ( cboTool->SelectedText == "Food" )
		{
			mbDrawFood = true;
			mBoard->AdjustFood( iRow, iCol, 5 );
			//lblFoodValue->Text = "Food in Square = " + mBoard->GetFood( iRow, iCol );
		}

		Invalidate( RowColToRect( iRow, iCol ) );
		Update();
		mbDrawGrass = false;
		mbDrawWall = false;
		mbDrawFood = false;
	}
	
}

#pragma endregion

#pragma region Run Button Handler

// Handle the Run button click
private: System::Void btnRun_Click(System::Object^  sender, System::EventArgs^  e) 
{
	if ( mbRunning )
	{
		mbRunning = false;
		btnRun->Text = "Run";
		timer1->Enabled = false;
	}
	else
	{
		mbRunning = true;
		btnRun->Text = "Stop";
		timer1->Enabled = true;
	}
}

#pragma endregion

#pragma region Timer Tick Handler

// Handle a time tick
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
{
	Rectangle	rect;
	int			iRow, iCol;
	int			iDeadIndex;
	bool		bContinue;

	bContinue = true;

	// Loop through the critter list
	while ( bContinue )
	{
		mCritter = mCritterList->GetCritter(0);

	// Handle critter movement

		// Get new location of Critter
		mCritter->GetRowCol( iRow, iCol );
		miRow = iRow;
		miCol = iCol;

		// Draw grass over the square that the BlueHarvester is in	ivalidate the correct rectangle
		if ( mBoard->GetFood( miRow, miCol ) <= 0 )
			mbDrawGrass = true;
		else 
			mbDrawFood = true;

		rect = RowColToRect( iRow, iCol );
		Invalidate( rect );
		Update();
		mbDrawGrass = false;
		mbDrawFood = false;

		//Move the creature
		mCritter->Move();

		// Get new location of Critter
		mCritter->GetRowCol( iRow, iCol );
		miRow = iRow;
		miCol = iCol;
		
		// Draw Creature in new location
		mbDrawCritter = true;	

		rect = RowColToRect( iRow, iCol );
		Invalidate( rect );
		Update();

		mbDrawCritter = false;

		// Check to see if we're done
		if (mCritterList->GetNext() != nullptr )
			mCritterList = mCritterList->GetNext();
		else
			bContinue = false;
	}
	
	mCritterList = mCritterList->GetFirst();

	do
	{
		iDeadIndex = mCritterList->FindDeadCritter( iRow, iCol );

		if ( iDeadIndex != -1 )
		{
			mCritter = mCritterList->GetCritter( iDeadIndex );
			mBoard->UpdateCount( iRow, iCol, mCritter->GetTribe(), -1);
			if ( !mBoard->HasTribe( iRow, iCol, mCritter->GetTribe() ) )
			{
				mbDrawGrass = true;
				rect = RowColToRect( iRow, iCol );
				Invalidate( rect );
				Update();
				mbDrawGrass = false;
			}
			mCritterList = mCritterList->Delete( iDeadIndex );
		}
	}while ( iDeadIndex != -1 );

	mCritterList = mCritterList->GetFirst();

	lblStats->Text = mCritterList->PrintStats();
}

# pragma endregion

# pragma region Utilities
// checks to see if mouse click is in the game board region
bool	IsInPanel( int iX, int iY )
{
	return ( ( iX > pnlBoard->Left ) && ( iX < pnlBoard->Right - 4 )
			&& ( iY > pnlBoard->Top ) && ( iY < pnlBoard->Bottom - 4 ) );
}

// take an (x,y) coordinate, & return the row & column it's in
// use & for pass by reference
void	PointToRowCol(int iX, int iY, int& iRow, int& iCol )
{
	// Snaps the landscape to grid
	iCol = ( iX - pnlBoard->Left ) / ciWidth;
	iRow = ( iY - pnlBoard->Top ) / ciWidth;
}

//	take a row & column, and return the game board rectangle
Rectangle	RowColToRect( int iRow, int iCol )
{
	Rectangle rect;
	
	rect.X = pnlBoard->Left + iCol * ciWidth + 1;
	rect.Y = pnlBoard->Top + iRow * ciWidth + 1;
	rect.Height = ciWidth;
	rect.Width = ciWidth;

	return rect;
}

# pragma endregion

};
}



#pragma region Notes

/*	// Make the BlueHarvester turn around if it is at an edge
	if ( miCol >= ciNumCols - 1 )
		miDelCol = -1;
	if ( miCol <= 0 )
		miDelCol = 1;
	if ( miRow >= ciNumRows - 1 )
		miDelRow = -1;
	if ( miRow <= 0 )
		miDelRow = 1;
	*/

	
	/*
	// Check to see if the BlueHarvester will hit a wall. If so, reverse course.	
	if ( mBoard->HasWall( miRow + miDelRow , miCol + miDelCol ) == true  )
	{
		int		iTempDelRow;
		
		if ( !mBoard->HasWall( miRow, miCol + miDelCol ) || mBoard->HasWall( miRow + miDelRow, miCol ) )
				iTempDelRow *= -miDelRow;
		if ( !mBoard->HasWall( miRow + miDelRow, miCol ) || mBoard->HasWall( miRow, miCol + miDelCol ) )
				miDelCol *= -1;

		miDelRow = iTempDelRow;
	}
		
	// Move the BlueHarvester, and invalidate its new rectangle
		miCol += miDelCol;
		miRow += miDelRow;
	mbDrawBlueHarvester = true;
		rect = RowColToRect( miRow, miCol );
		Invalidate( rect );
		Update();
	mbDrawBlueHarvester = false;
*/

#pragma endregion


//TODO:

// Fix so enemy tribes don't enter MAMMA
// Fix Harvester so won't cross into enemy tribes square
