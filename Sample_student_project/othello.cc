// Brock Ferrell
// CS2401
// November 23, 2015
// Project7

//@file othello.cc
//@brief This is the implementation to play Othello
//@author Jonahtna Feige (documentation only)
//@author Brock Ferrell (all code)
#include "othello.h" // Provides definition of othello class

namespace main_savitch_14
{
// PUBLIC MEMBER FUNCTIONS
void Othello::display_status()const
/*
  @brief This function displays the current status of the board
    This function uses basic output characters to display a game
    board with varying colors and a Character/Number grid system.
  @return void
*/
{
  cout << BLUE << "   _______ _______ _______ _______ _______ _______ _______ _______\n";
  cout << BLUE << "   |  A  | |  B  | |  C  | |  D  | |  E  | |  F  | |  G  | |  H  |" << endl;

  for (int y = 0; y < 8; y++)
  {
    cout << BLUE << "  " << y + 1 << BLUE << '|' << RESET;
    for (int x = 0; x < 8; x++)
    {
      if (!gameBoard[x][y].is_black() && !gameBoard[x][y].is_white())
      {
        cout << B_RED << "     " << RESET;
      }
      else if (gameBoard[x][y].is_black())
      {
        cout << B_BLACK << WHITE << BOLD << "  B  " << RESET;
      }
      else if (gameBoard[x][y].is_white())
      {
        cout << B_WHITE << BLACK << BOLD << "  W  " << RESET;
      }

      if (x == 7)
      {
        cout << BLUE << "|     " << RESET;
      }
      else if (y < 8 && x <= 6)
      {
        cout << BLUE << "| |" << RESET;
      }
    }
    if (y < 8)
    {
      cout << BLUE << endl << "   |_____| |_____| |_____| |_____| |_____| |_____| |_____| |_____|\n";
    }
  }
  cout << "\nEnter a move in the format(letter,number) (Ex: A3)" << endl;
}

void Othello::make_move(const string& move) 
/*
  @brief This function sets up the selected move
    This function uses .set_white and .set_black 
    to set the next state of the board
  @return void
*/
{
  int c, r;                         //The vertical and horizontal move
  c = int(toupper(move[0]) - 'A');
  r = int(move[1] - '1');

  if (next_mover() == HUMAN) {
    if (move == "s" || move == "S") {
      make_skips();
    }

    else if (gameBoard[c + 1][r].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c++;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c - 1][r].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c--;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c][r + 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        r++;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c][r - 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        r--;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c + 1][r - 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c++;
        r--;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c - 1][r - 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c--;
        r--;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c - 1][r + 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c--;
        r++;
      } while (gameBoard[c][r].is_white());
    }

    else if (gameBoard[c + 1][r + 1].is_white()) {
      do {
        gameBoard[c][r].set_black();
        c++;
        r++;
      } while (gameBoard[c][r].is_white());
    }
  }

  if (next_mover() == COMPUTER) {
    if (move == "s" || move == "S") {
      make_skips();
    }

    else if (gameBoard[c + 1][r].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c++;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c - 1][r].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c--;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c][r + 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        r++;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c][r - 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        r--;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c + 1][r - 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c++;
        r--;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c - 1][r - 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c--;
        r--;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c - 1][r + 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c--;
        r++;
      } while (gameBoard[c][r].is_black());
    }

    else if (gameBoard[c + 1][r + 1].is_black()) {
      do {
        gameBoard[c][r].set_white();
        c++;
        r++;
      } while (gameBoard[c][r].is_black());
    }
    skips = 0;
  }
  move_number++;
}


void Othello::restart() {
/*
  @brief This function sets the board back to its begining 
         state before the board had any moves on it.
  @return void
*/
  gameBoard[3][3].set_white();
  gameBoard[3][4].set_black();
  gameBoard[4][3].set_black();
  gameBoard[4][4].set_white();

  white = 2;
  black = 2;
  skips = 0;
  openSpots = 60;
}

bool Othello::is_legal(const string& move)const {
  /*
  @ This fuction cheks the legality of a move
    it takes a string, and checks every possible 
    space to check for a match.
  @return bool
*/
  int c, r;                         //The vertical and horizontal move
  c = int(toupper(move[0]) - 'A');
  r = int(move[1] - '1');

//@param message BLACK'S TURN
  if (next_mover() == HUMAN) {
    if (gameBoard[c][r].is_blank()) {
      if (gameBoard[c][r - 1].is_white()) {
        do {
          r--;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());

      }

      if (gameBoard[c][r + 1].is_white()) {
        do {
          r++;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());

      }

      if (gameBoard[c + 1][r].is_white()) {
        do {
          c++;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());

      }

      if (gameBoard[c - 1][r].is_white()) {
        do {
          c--;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }

      if (gameBoard[c + 1][r - 1].is_white()) {
        do {
          c++;
          r--;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }

      if (gameBoard[c - 1][r - 1].is_white()) {
        do {
          c--;
          r--;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }

      if (gameBoard[c - 1][r + 1].is_white()) {
        do {
          c--;
          r++;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }

      if (gameBoard[c + 1][r + 1].is_white()) {
        do {
          c++;
          r++;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }
    } else {
      return false;
    }
  }

//@param message, WHITE'S TURN
  if (next_mover() == COMPUTER) {
    if (gameBoard[c][r].is_blank()) {
      if (gameBoard[c][r - 1].is_white()) {
        do {
          r--;
          if (gameBoard[c][r].is_black()) {
            return true;
          }
        } while (gameBoard[c][r].is_white());
      }

      if (gameBoard[c][r + 1].is_black()) {
        do {
          r++;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }

      if (gameBoard[c + 1][r].is_black()) {
        do {
          c++;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }

      if (gameBoard[c - 1][r].is_black()) {
        do {
          c--;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }

      if (gameBoard[c + 1][r - 1].is_black()) {
        do {
          c++;
          r--;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());

      }

      if (gameBoard[c - 1][r - 1].is_black()) {
        do {
          c--;
          r--;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }

      if (gameBoard[c - 1][r + 1].is_black()) {
        do {
          c--;
          r++;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }

      if (gameBoard[c + 1][r + 1].is_black()) {
        do {
          c++;
          r++;
          if (gameBoard[c][r].is_white()) {
            return true;
          }
        } while (gameBoard[c][r].is_black());
      }
    } else {
      return false;
    }
  }
}

void Othello::countingPieces() {
/*
  @ This fuction counts each peice on the 
    board then outsputs the results
  @return void
*/

  int black = 0;    //counts about of black peice
  int white = 0;    //counts about of white peice

  for (int b = 0; b < 8; b++) {
    for (int a = 0; a < 8; a++) {
      if (gameBoard[a][b].is_white()) {
        white++;
      } else if (gameBoard[a][b].is_black()) {
        black++;
      }
    }
  }
  cout << "Total move: " << moves_completed() << endl;
  openSpots = 64 - (black + white);
  cout << "Black: "  << black << " ---" << " White: " << white;
  cout << endl;
}

bool Othello::is_game_over()const {
    /*
  @ This function looks at the four end conditions
    after every move, and checks for nd conditons.
  @return bool
*/

  if (skips == 2 || openSpots == 0 || black == 0 || white == 0) {
    cout << "The game is over.\n";
    return true;    // if game is over
  }
  else {
    return false;   //if game is not over
  }
}

void Othello::whosTurn() {
/*
  @ This fuction uses the next_mover counter
    to find who is the next person to go.
  @return void
*/

  if (next_mover() == COMPUTER) {
    cout << "\nWhite's Turn!" << endl;
  }

  if (next_mover() == HUMAN) {
    cout << "\nBlack's Turn!" << endl;
  }
}

void Othello::make_skips() {
/*
  @ This fuction increases the skip counter.
  @return void
*/

  skips++;
}

game::who Othello::winning()const {
/*
  @ This fuction counts each peice on the 
    board then outputs who is currently winning
  @return game::who
*/

  if (black > white) {
    return last_mover();
  } else if (white > black) {
    return next_mover();
  } else {
    return NEUTRAL;
  }

}

int Othello::evaluate()const {
 /*
  @ This fuction looks at every possible move for
    a computer and eturns the best possible move
    thought an integer value.
  @return int
*/

  int tmp_white = w;    // used to check score of white
  int tmp_black = b;    // used to check score of black

  if (gameBoard[0][0].is_white() || gameBoard[7][7].is_white() || gameBoard[0][7].is_white() || gameBoard[7][0].is_white()) {
    tmp_white += 5;
  }
  if (gameBoard[0][0].is_black() || gameBoard[7][7].is_black() || gameBoard[0][7].is_black() || gameBoard[7][0].is_black()) {
    tmp_black += 5;
  }

  if (b > w) {
    return b;
  } else if (w > b) {
    return w;
  }
}

void Othello::compute_moves(std::queue<std::string>& moves)const {
 /*
  @ This fuction generates every possible move 
  on a board and checks to find which are legal to use.
  @return void
*/

  string r;       //The vertical move
  string c;       //The horizontal move
  string move;    //Total move

  for (int i = 0; i < 8; i++) {
    c = i + 'A';
    for (int j = 0; j < 8; j++) {
      r = j + '1';
      move = c + r;
      if (is_legal(move)) {
        moves.push(move);
      }
      else {

      }
    }
  }
}

}
