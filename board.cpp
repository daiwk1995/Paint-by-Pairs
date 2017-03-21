#include <cassert>
#include <iostream>

#include "board.h"


// CONSTRUCTOR
Board::Board(int w, int h) {
  height_ = h;
  width_ = w;
  board = std::vector<std::vector<char> >(h,std::vector<char>(w,' '));
}

// ACCESSOR
char Board::get(int y, int x) const {
  assert (y >= 0 && board.size());
  assert (x >= 0 && board[y].size());
  return board[y][x];
}

// helper function for set
char IntToChar(int v) {
  assert (v >= 1 && v <= 30);
  if (v <= 9) {
    return char('0' + v);
  } else {
    // A = 10
    // B = 11
    // C = 12
    // etc
    return char('A' + (v-10));
  }
}

// MODIFIER
void Board::set(int x, int y, int v) {
  assert (x < width_);
  assert (y < height_);
  assert(board[y][x] == ' ');
  board[y][x] = IntToChar(v);
}
void Board::set(int x,int y, char v)
{
  assert (x < width_);
  assert (y < height_);
  board[y][x]=v;
}
void Board::clear()
{
  for(int i=0;i<height_;i++)
  {
    for(int j=0;j<width_;j++)
    board[i][j]=' ';
  }
}
// PRINT FUNCTION
std::ostream& operator<<(std::ostream& ostr, const Board &b) {
  // top frame
  ostr << "+" << std::string(b.width(),'-') << "+" << std::endl;
  for (int y = b.height()-1; y >= 0; y--) {
    ostr << "|";
    // each row
    for (int x = 0; x < b.width(); x++) {
      ostr << b.get(y,x);
    }
    ostr << "|" << std::endl;
  }
  // bottom frame
  ostr << "+" << std::string(b.width(),'-') << "+" << std::endl;
  return ostr;
}
