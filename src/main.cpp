#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

#include "board.h"
//I create this class to store the point of path;
class Point {
public:
  Point(int x0, int y0) : x(x0), y(y0) {}
  int x,y;
};
//in this function,I just find the min number int the map and statr to find all the path from this point
Point sortmin(Board &board,std::vector<std::vector<bool> > &block_grid)
{
  int x=0;
  int y=0;
  char min='z';
//traverse all the map to find the min number
for(int i=0;i<board.height();i++)
{
for(int j=0;j<board.width();j++)
{
if(board.get(i,j)!=' '&&block_grid[j][i]==true&&board.get(i,j)<min)
{
 min=board.get(i,j);
  x=j;
  y=i;
}
}
}
//if the min not change,it means i find all the solution and its time to output
if(min=='z')
return Point(board.width(),board.height());
return Point(x,y);
}
//use this finction to change char to int so that I can calculate the step;
int change(Point &a,Board &board)
{
if(board.get(a.y,a.x)>='A'){
return (int)(board.get(a.y,a.x)-'A'+10);
}
else{
return (int)(board.get(a.y,a.x)-'0');
}
}
//in this function,I just traverse all the direction to find all the point which
//number can match the first point
int find_all(int count,std::vector<std::vector<bool> > &block_grid,Board &board,Point a,int x,int y,int step,std::vector<Point> &path,std::vector<std::vector<Point> > &allpath)
{
  //when i traverse the map,it can not come back to the point
  for(int i=0;i<path.size();i++)
  {
  if(x==path[i].x&&y==path[i].y)
  return 0;
  }
  //if the point out the boundry or this point already block,return back
  if(x<0||y<0||step<1||x>=board.width()||y>=board.height()||block_grid[x][y]==false)
  {
    return 0;
  }
  //if the point has value but not we want to,return back
  if(step!=1&&board.get(y,x)!=' '&&(a.y!=y||a.x!=x))
  return 0;
    count=0;
    path.push_back(Point(x,y));
//if we find the match point,push back the path to a vector<vector> so that we can
//use later
if(board.get(y,x)==board.get(a.y,a.x)&&step==1)
{
  if(a.y==y&&a.x==x&&change(a,board)!=1)
  {
    path.pop_back();
  return 0;
  }

  allpath.push_back(path);
  path.pop_back();
  return 1;
}
//traverse all four directions and use recursion
if(find_all(count,block_grid,board,a,x+1,y,step-1,path,allpath)==1)
{
  count=1;
}
if(find_all(count,block_grid,board,a,x,y-1,step-1,path,allpath)==1)
{
  count=1;
}
if(find_all(count,block_grid,board,a,x,y+1,step-1,path,allpath)==1)
{
  count=1;
}
if(find_all(count,block_grid,board,a,x-1,y,step-1,path,allpath)==1)
{
  count=1;
}
  path.pop_back();
return count;
}
//this funtion is to find all solution about the map
int solution(int success,std::vector<std::vector<std::vector<Point> > > &all,std::vector<std::vector<Point> > &answear,Point &a,std::vector<std::vector<bool> > &block_grid,int step,std::vector<Point> &path,std::vector<std::vector<Point> > allpath,Board &board)
{
  int count=0;
  success=0;
  allpath.clear();
  a=sortmin(board,block_grid);//to obtain the min number to start;
  //when we find one solution,push back to a trible vector to store the path
  if(a.x==board.width()&&a.y==board.height())
  {
    all.push_back(answear);
  return 1;
  }
  //step is the value of the point
  step=change(a,board);
  //use another recursion to find all path that can find point match a;
  if(find_all(count,block_grid,board,a,a.x,a.y,step,path,allpath)==0)
  {
    return 0;
  }
   else
   {
     //when we find allpath from a,we will store it in allpath vector and
     //use recursion to find another's allpath,we use for loop so that we
     //will never miss one path;
     for(int i=0;i<allpath.size();i++)
   {
       for(int j=0;j<allpath[i].size();j++)
       block_grid[allpath[i][j].x][allpath[i][j].y]=false;//block_grid is block the point which already walk
       answear.push_back(allpath[i]);//push back the path
     if(solution(success,all,answear,a,block_grid,step,path,allpath,board)==0)
     {
       //if we can not find solution from this path,we need to restore the path
      for(int k=0;k<allpath[i].size();k++)
      block_grid[allpath[i][k].x][allpath[i][k].y]=true;
      answear.pop_back();//if the path can not work,pop back
     }
     //if we find one solution,we will not return because we need to traverse all
     //the path to find all the solution;
     else{
     success=1;
     for(int k=0;k<allpath[i].size();k++)
     block_grid[allpath[i][k].x][allpath[i][k].y]=true;
     answear.pop_back();
   }
   }
   return success;
 }
}
//this function is similiar with the solution function,but it will return once you
//find one solution
int one(int success,std::vector<std::vector<Point> > &answear,Point &a,std::vector<std::vector<bool> > &block_grid,int step,std::vector<Point> &path,std::vector<std::vector<Point> > allpath,Board &board)
{
  int count=0;
  allpath.clear();
  a=sortmin(board,block_grid);
  //once we find the solution,return back and do not store it
  if(a.x==board.width()&&a.y==board.height())
  {
  return 1;
  }
  step=change(a,board);
  if(find_all(count,block_grid,board,a,a.x,a.y,step,path,allpath)==0)
  {
    return 0;
  }
   else
   {
     for(int i=0;i<allpath.size();i++)
     {
       for(int j=0;j<allpath[i].size();j++)
       block_grid[allpath[i][j].x][allpath[i][j].y]=false;
       answear.push_back(allpath[i]);
     if(one(success,answear,a,block_grid,step,path,allpath,board)==0)
     {
      for(int k=0;k<allpath[i].size();k++)
      block_grid[allpath[i][k].x][allpath[i][k].y]=true;
      answear.pop_back();
     }
     //unlike the solution function,once we find a solution,we just return rather
     //than to search other difrection to find all solutions
     else
     {
     return 1;
     }
     }
     return 0;
    }
}

int main(int argc, char* argv[]) {

  // parse the arguments
  if (argc < 2) {
    std::cerr << "USAGE:  " << argv[0] << " <puzzlefile>" << std::endl;
    std::cerr << "        " << argv[0] << " <puzzlefile> find_all_solutions" << std::endl;
    exit(0);
  }
  bool all_solutions = false;
  if (argc > 2) {
    assert (argc == 3);
    assert (std::string(argv[2]) == std::string("find_all_solutions"));
    all_solutions = true;
  }

  // open the file
  std::ifstream istr(argv[1]);
  if (!istr.good()) {
    std::cerr << "ERROR!  cannot open " << argv[1] << std::endl;
    exit(0);
  }

  // read the file
  std::string token;
  istr >> token;
  assert (token == "width");
  int width,height;
  istr >> width;
  istr >> token;
  assert (token == "height");
  istr >> height;
  assert (width > 0);
  assert (height > 0);
  int x,y,v;

  // create the board
  Board board(width,height);
  while (istr >> x >> y >> v) {
    assert (x >= 0 && x < width);
    assert (y >= 0 && y < height);
    board.set(x,y,v);
  }
  std::vector<std::vector<bool> > block_grid;
  std::vector<bool> block;
for(int j=0;j<width;j++)
{
  for(int i=0;i<height;i++)
  {
  block.push_back(true);
  }
  block_grid.push_back(block);
}
  // print the original puzzle board
  std::cout << board;

  // Now...  solve it!
  std::vector<std::vector<std::vector<Point> > > all;
  std::vector<std::vector<Point> > allpath;
  std::vector<std::vector<Point> > answear;
  std::vector<Point> path;
  int step=0;
  Point a(0,0);
  int success=1;
  //this is output function,we just output the path which store in the double vector
  if(all_solutions==false)
  {
    if(one(success,answear,a,block_grid,step,path,allpath,board)==1)
    {
      std::cout<<"Solution:"<<std::endl;
        for(int j=0;j<answear.size();j++)
        {
        for(int k=0;k<answear[j].size();k++)
        {
        std::cout<<'('<<answear[j][k].x<<','<<answear[j][k].y<<')';
          board.set(answear[j][k].x,answear[j][k].y,'X');
        }
        std::cout<<std::endl;
        }

        std::cout<<board<<std::endl;

    }
    else
    {
      std::cout<<"No solutions"<<std::endl;
    }
  }
  else
  {
    if(solution(success,all,answear,a,block_grid,step,path,allpath,board)==1)
    {
    for(int i=0;i<all.size();i++)
    {
    std::cout<<"Solution:"<<std::endl;
    for(int j=0;j<all[i].size();j++)
    {
    for(int k=0;k<all[i][j].size();k++)
    {
    std::cout<<'('<<all[i][j][k].x<<','<<all[i][j][k].y<<')';
    board.set(all[i][j][k].x,all[i][j][k].y,'X');
    }
    std::cout<<std::endl;
    }
    std::cout<<board<<std::endl;
    board.clear();
    }
    std::cout<<"Found"<<' '<<all.size()<<' '<<"solution(s)"<<std::endl;
    }
    else
    {
    std::cout<<"No solutions"<<std::endl;
    }
  }
}
