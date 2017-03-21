#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <string>

class Board {
public:
  // CONSTRUCTOR
  Board(int w, int h);
  // ACCESSORS
  int width() const { return width_; }
  int height() const { return height_; }
  char get(int y, int x) const;
  // MODIFIER
  void set(int x, int y, int v);
  void set(int x,int y,char v);
  void clear();
private:
  // REPRESENTATION
  int height_;
  int width_;
  std::vector<std::vector<char> > board;
};

// PRINT FUNCTION
std::ostream& operator<<(std::ostream& ostr, const Board &b);

#endif
