// JScript source code for Connect four project



//The gameboard array - this holds the game status
var gaBoard = [['o', 'o', 'o', 'o', 'o', 'o', 'o'], ['o', 'o', 'o', 'o', 'o', 'o', 'o'],
               ['o', 'o', 'o', 'o', 'o', 'o', 'o'], ['o', 'o', 'o', 'o', 'o', 'o', 'o'],
               ['o', 'o', 'o', 'o', 'o', 'o', 'o'], ['o', 'o', 'o', 'o', 'o', 'o', 'o']];

var gcPlayer = "Red"; //current player color
var gbGameOver = true;

//Gameboard
function vLoad() 
{
    var strTable, i, j, strID, strOver, strOut, strTitle, strHover, strPush, strArrow, strNewGame;

    strTable = "<table cellpadding='0' cellspacing='0'>";

    //Row for Title
    for (i = 0; i < 1; i++) 
    {
        strTable += "<tr>";

        strTable += "<th style='color:blue; font-size:xx-large' colspan='7'>Connect Four Game</th>";

        strTable += "</tr>";
    }

    //Row for New game and Computer Moves Buttons
    strTable += "<tr>";

    strTable += strTH(strButton("New Game", "vNewGame()"), 3);

    strTable += strTH(strButton("Computer Move", "vComputerMove()"), 2);

    strTable += strTH(strComboBox("cboComputerLevel", "Easy", "Medium", "Difficult"), 3);

    strTable += "</tr>";
        
    //Row for Buttons
    
    strTable += "<tr>";

    for (j = 0; j < 7; j++) 
    {
        strID = "img" + j;
        strHover = "vArrowHover(\"" + strID + "\")";
        strPush = "vArrowDown(\"" + strID + "\", " + j + ")";
        strArrow = "vArrow(\"" + strID + "\")";

        strTable += strTD(strImage("Images/Connect 4 Project Images/Arrow.jpg", strID, strPush, strHover, strArrow, strArrow), 1);
    } 

    strTable += "</tr>";

    //put a row in the Gameboard
    for (i = 5; i >= 0; i--) 
    {
        strTable += "<tr>";

        //put in the column in the Gameboard
        for (j = 0; j < 7; j++) 
        {

            strID = "img" + i + j;
            strOver = "vMakeRed(\"" + strID + "\")";
            strOut = "vMakeBlack(\"" + strID + "\")";

            strTable += strTD(strImage("Images/Connect 4 Project Images/Open.jpg", strID, "", "", ""));
        }

        strTable += "</tr>";
    }

    //Row for Text Area
    for (i = 0; i < 1; i++) 
    {
        strTable += "<tr>";
        strTable += strTD(strTextArea(4, 58), 7);

        strTable += "</tr>";
    }

    strTable += "</table>";

    frm1.innerHTML = strTable;
}

//********************************************************************
//Functions for Game Reset and Computer Move

function vNewGame() 
{
	for (i = 0; i < 6; i++)
	{
		for(j = 0; j < 7; j++)
		{
			gaBoard[i][j] = 'o';
			strID = "img" + i + j;
			vMakeOpen(strID);
			frm1.taMessage.value = "";
			gbGameOver = true;
		}
    }
    gcPlayer = "Red";
    giCounter = 0;
}

function vComputerMove() 
{
    var strID, iCol, iRow, iWinCol, iLoseCol, iForceCol, iBlockForceCol, cAdversary;

    //Initialize winning column with illegal column
    iWinCol = -1;

    //Initialize losing column with illegal column
    iLoseCol = -1;

    //Initialize force win column with illegal column
    iForceCol = -1;

    //Initialize force win column with illegal column
    iBlockForceCol = -1;

    //Determine Adversary
    if (gcPlayer == "Red")                  
        cAdversary = "Black";
    else
        cAdversary = "Red";


    iWinCol = iComputerTakesWin();
    iLoseCol = iComputerBlocksWin(cAdversary);
    iForceCol = iComputerForceWin(cAdversary);
    iBlockForceCol = iComputerBlockForceWin(cAdversary);

    if (frm1.cboComputerLevel.value == 'Easy')
    {
        //Computer Moves Randomly
        vComputerMoveRandom();
        //frm1.taMessage.value = "Random";    
    }

    if (frm1.cboComputerLevel.value == 'Medium')
    {
        //Computer takes a win if it is there
        if (iWinCol != -1)
        {
            strID = "img" + iWinCol;
            vArrowDown(strID, iWinCol);
            //frm1.taMessage.value = "Take Win";
        }

        //Computer Blocks adversary
        else if (iLoseCol != -1)
        {
            strID = "img" + iLoseCol;
            vArrowDown(strID, iLoseCol);
            //frm1.taMessage.value = "Block";
        }

        else
        {
            vComputerMoveRandom();
            //frm1.taMessage.value = "Random";
        }
    }

    if (frm1.cboComputerLevel.value == 'Difficult')
    {
        //Computer takes a win if it is there
        if (iWinCol != -1)
        {
            strID = "img" + iWinCol;
            vArrowDown(strID, iWinCol);
            //frm1.taMessage.value = "Take Win";
        }

        //Computer Blocks adversary
        else if (iLoseCol != -1)
        {
            strID = "img" + iLoseCol;
            vArrowDown(strID, iLoseCol);
            //frm1.taMessage.value = "Block";
        }

        //Computer Forces a 2 Move Win
        else if (iForceCol != -1)
        {
            strID = "img" + iForceCol;
            vArrowDown(strID, iForceCol);
            //frm1.taMessage.value = "2 force win";
        }

        //Computer Blocks a 2 Move Forced Win
        else if (iBlockForceCol != -1)
        {
            strID = "img" + iBlockForceCol;
            vArrowDown(strID, iBlockForceCol);
            //frm1.taMessage.value = "Block 2 force win";    
        }
        
        //Computer Moves Randomly
        else
        {
            vComputerMoveRandom();
            //frm1.taMessage.value = "Random";
        }
    }
}

function iComputerTakesWin()
{
    var iRow, iWinCol;

    //Initialize winning column with illegal column
    iWinCol = -1;

    //Computer checks for win
    for (i = 0; i < 7; i++)                 //check columns
    {
        iRow = iFindSlotOpen(i);            //find open slot in board check
        if (iRow < 6)
        {
            gaBoard[iRow][i] = gcPlayer;    //put in piece
            bWinner(gcPlayer, iRow, i);     //check for win
            if (bWinner(gcPlayer, iRow, i) == true)
                iWinCol = i;                //mark winning column
            gaBoard[iRow][i] = 'o';         //remove piece
        }
    }

    return iWinCol;
}

function iComputerBlocksWin(cAdversary)
{
    var iRow, iLoseCol;
    
    //Initialize losing column with illegal column
    iLoseCol = -1;

    //Computer checks if adversary has win
    for (j = 0; j < 7; j++)
    {
        iRow = iFindSlotOpen(j);            //find open slot in board check
        if (iRow < 6)
        {
            gaBoard[iRow][j] = cAdversary;  //put in piece
            bWinner(cAdversary, iRow, j);   //check for win
            if (bWinner(cAdversary, iRow, j) == true)
                iLoseCol = j;               //mark winning column
            gaBoard[iRow][j] = 'o';         //remove piece
        }
    }

    return iLoseCol;
}

function iComputerForceWin(cAdversary)
{
    var iRowA, iRowB, iRowC, iForceCol;

    iForceCol = -1;
    
    for (k = 0; k < 7; k++)
    {
        iRowA = iFindSlotOpen(k);
        if (iRowA < 6)
        {
            gaBoard[iRowA][k] = gcPlayer;
            for (m = 0; m < 7; m++)
            {
                iRowB = iFindSlotOpen(m);
                if (iRowB < 6)
                {
                    gaBoard[iRowB][m] = cAdversary;
                    for (n = 0; n < 7; n++)
                    {
                        iRowC = iFindSlotOpen(n);
                        if (iRowC < 6)
                        {
                            gaBoard[iRowC][n] = gcPlayer;
                            bWinner(gcPlayer, iRowC, n);
                            if (bWinner(gcPlayer, iRowC, n) == true)
                                iForceCol = n;
                            gaBoard[iRowC][n] = 'o';                     
                        }                    
                    }
                    gaBoard[iRowB][m] = 'o';
                }
                    
            }
            gaBoard[iRowA][k] = 'o'; 
        }
    }

    return iForceCol;
}

function iComputerBlockForceWin(cAdversary)
{
    var iRowA, iRowB, iRowC, iBlockForceCol;

    iBlockForceCol = -1;

    for (k = 0; k < 7; k++)
    {
        iRowA = iFindSlotOpen(k);
        if (iRowA < 6)
        {
            gaBoard[iRowA][k] = cAdversary;
            for (m = 0; m < 7; m++)
            {
                iRowB = iFindSlotOpen(m);
                if (iRowB < 6)
                {
                    gaBoard[iRowB][m] = gcPlayer;
                    for (n = 0; n < 7; n++)
                    {
                        iRowC = iFindSlotOpen(n);
                        if (iRowC < 6)
                        {
                            gaBoard[iRowC][n] = cAdversary;
                            bWinner(cAdversary, iRowC, n);
                            if (bWinner(cAdversary, iRowC, n) == true)
                                iBlockForceCol = n;
                            gaBoard[iRowC][n] = 'o';
                        }
                    }
                    gaBoard[iRowB][m] = 'o';
                }

            }
            gaBoard[iRowA][k] = 'o';
        }
    }

    return iBlockForceCol;

}

function vComputerMoveRandom() 
{
    var strID, iCol;

    iCol = Math.floor(Math.random() * 7);

    strID = "img" + iCol;

    vArrowDown(strID, iCol);
}


//*********************************************************************
//Functions for modifying controls
function vMakeRed(strID) 
{
    document.getElementById(strID).src = "Images/Connect 4 Project Images/Red.jpg";
}

function vMakeBlack(strID) 
{
    document.getElementById(strID).src = "Images/Connect 4 Project Images/Black.jpg";
}

function vMakeOpen(strID)
{
	document.getElementById(strID).src = "Images/Connect 4 Project Images/Open.jpg";
}

function vArrow(strID)
{
    document.getElementById(strID).src = "Images/Connect 4 Project Images/Arrow.jpg";
}

function vArrowHover(strID)
{
    document.getElementById(strID).src = "Images/Connect 4 Project Images/Hover.jpg";
}

function vShowDown(strID)
{
    document.getElementById(strID).src = "Images/Connect 4 Project Images/Push.jpg";
}

function vArrowDown(strID, iCol) 
{
    var i, strID2, iRow;

    vShowDown(strID);

    if (gbGameOver == false)
    {
        frm1.taMessage.value += "Game is Over, no more moves. \n";
        return;
    }

    //see if we can drop a piece into the selected column
    if (gaBoard[5][iCol] == "o")
    {
        //frm1.taMessage.value += gcPlayer + " moves into column " + iCol + ".\n";

        iRow = iFindSlotOpen(iCol);
        gaBoard[iRow][iCol] = gcPlayer;
        strID2 = "img" + iRow + iCol;

        //switch players
        if (gcPlayer == "Red")
        {
            vMakeRed(strID2);
            
            if (bWinner(gcPlayer, iRow, iCol) == true)
            {
                frm1.taMessage.value += "Congratulations! " + gcPlayer + " has won. \n";
                gbGameOver = false;
            }
            gcPlayer = "Black";
        }
        else
        {
            vMakeBlack(strID2);

            if (bWinner(gcPlayer, iRow, iCol) == true)
            {
                frm1.taMessage.value += "Congratulations! " + gcPlayer + " has won. \n";
                gbGameOver = false;
            }

            gcPlayer = "Red";
        }
    }

    else
    {
        frm1.taMessage.value = "Sorry, column " + iCol + " is full - try again. \n";
    }

    if ((gaBoard[5][0] != "o") && (gaBoard[5][1] != "o") && (gaBoard[5][2] != "o") && (gaBoard[5][3] != "o") && (gaBoard[5][4] != "o") && (gaBoard[5][5] != "o") && (gaBoard[5][6] != "o"))
    {
        frm1.taMessage.value = "The board is full. Please start a new game. \n";
        gbGameOver = false;
    }

    vShowDown(strID);
}

//determines what slot in a column is open
function iFindSlotOpen(iCol) 
{
    var iRow;
    iRow = 0;

    while ((iRow < 6) && (gaBoard[iRow][iCol] != "o")) 
    {
        iRow++;
    }
    return iRow;
}

//determines what player wins
function bWinner(cPlayer, iRow, iCol) 
{
    var bPossible, iStart, iEnd, iStartCol, iStartRow, iStartA, iStartB, iEndA, iEndB;

    bPossible = false;

    //Horizontal 4-in-a row Checker
    iStart = iCol - 3;
    if (iStart < 0)
        iStart = 0;
    iEnd = iCol;
    if (iEnd > 3)
        iEnd = 3;
    
    for (iStartCol = iStart; iStartCol <= iEnd; iStartCol++) 
    {
        if ((gaBoard[iRow][iStartCol] == cPlayer) && (gaBoard[iRow][iStartCol + 1] == cPlayer)
                           && (gaBoard[iRow][iStartCol + 2] == cPlayer) && (gaBoard[iRow][iStartCol + 3] == cPlayer))
            bPossible = true;			
    }

    //Vertical 4-in-a row Checker
    iStart = iRow - 3;
    if (iStart < 0)
        iStart = 0;
    iEnd = iRow;
    if (iEnd > 2)
        iEnd = 2;

    for (iStartRow = iStart; iStartRow <= iEnd; iStartRow++) 
    {
        if ((gaBoard[iStartRow][iCol] == cPlayer) && (gaBoard[iStartRow + 1][iCol] == cPlayer)
                           && (gaBoard[iStartRow + 2][iCol] == cPlayer) && (gaBoard[iStartRow + 3][iCol] == cPlayer)) 
            bPossible = true;			
    }

//Diagonal 4-in-a row Checkers
    
    //Up and to the Right Diagonals
    iStartA = iRow - 3;
    if (iStartA < 0)
        iStartA = 0;
    iEndA = iRow;
    if (iEndA > 2)
        iEndA = 2;

    iStartB = iCol - 3;
    if (iStartB < 0)
        iStartB = 0;
    iEndB = iCol;
    if (iEndB > 3)
        iEndB = 3;

    for (iStartRow = iStartA; iStartRow <= iEndA; iStartRow++) 
    {
        for (iStartCol = iStartB; iStartCol <= iEndB; iStartCol++) 
        {
            if ((gaBoard[iStartRow][iStartCol] == cPlayer) && (gaBoard[iStartRow + 1][iStartCol + 1] == cPlayer)
                           && (gaBoard[iStartRow + 2][iStartCol + 2] == cPlayer) && (gaBoard[iStartRow + 3][iStartCol + 3] == cPlayer))
                bPossible = true;				
        }
    }

    //Up and to the Left Diagonals
    iStartA = iRow - 3;
    if (iStartA < 0)
        iStartA = 0;
    iEndA = iRow;
    if (iEndA > 2)
        iEndA = 2;

    iStartB = iCol + 3;
    if (iStartB > 6)
        iStartB = 6;
    iEndB = iCol;
    if (iEndB < 3)
        iEndB = 3;

    for (iStartRow = iStartA; iStartRow <= iEndA; iStartRow++) 
    {
        for (iStartCol = iStartB; iStartCol >= iEndB; iStartCol--) 
        {
            if ((gaBoard[iStartRow][iStartCol] == cPlayer) && (gaBoard[iStartRow + 1][iStartCol - 1] == cPlayer)
                           && (gaBoard[iStartRow + 2][iStartCol - 2] == cPlayer) && (gaBoard[iStartRow + 3][iStartCol - 3] == cPlayer))
                bPossible = true;		
        }
    }

    return bPossible;
}

//*********************************************************************
//Functions for creating form controls

//Button Maker
function strButton(strValue, strOnclick) 
{
    return "<input type='button' value='" + strValue + "' onclick='" + strOnclick + "' />"

}

//Image Maker
function strImage(strSrc, strID, strOnclick, strMouseOver, strMouseOut, strMouseUp) 
{
    var strReturn;

    strReturn = "<img src = '" + strSrc + "' id = '" + strID + "' " + "' onclick='" + strOnclick + "' ";
    strReturn += "onmouseover='" + strMouseOver + "' onmouseout = '" + strMouseOut + "' onmouseup='" + strMouseUp + "' />";

    return strReturn;

}

//TD Maker
function strTD(strContent, iColspan) 
{
    var strReturn;

    strReturn = "<td colspan = '" + iColspan + "'> " + strContent + " </td>";

    return strReturn;

}

//TH Maker
function strTH(strContent, iColspan) 
{
    var strReturn;

    strReturn = "<th colspan = '" + iColspan + "'> " + strContent + " </th>";

    return strReturn;

}

//Text Area Maker
function strTextArea(iRows, iCols) 
{
    var strReturn;

    strReturn = "<textarea id= 'taMessage' ";
    strReturn += "' rows = '" + iRows + "' cols='" + iCols + "'style='text-align:left' >";
    strReturn += "</textarea>";

    return strReturn;
}

//Combo Box Maker
function strComboBox(strID, strValue1, strValue2, strValue3)
{
    var strReturn;

    strReturn = "Level&nbsp&nbsp&nbsp<select id='" + strID + "'>";
    strReturn += "<option value='Easy'>" + strValue1 + "</option>";
    strReturn += "<option value='Medium'>" + strValue2 + "</option>";
    strReturn += "<option value='Difficult'>" + strValue3 + "</option>";
    strReturn += "</select>";

    return strReturn;
}