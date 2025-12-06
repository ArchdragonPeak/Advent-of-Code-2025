#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdint>

using std::cout;
using std::string;
using std::vector;


struct Tuple
{
  size_t x;
  size_t y;
};

size_t findNextSmallestX(const size_t y, const vector<Tuple>& lines)
{
  // biggest rang found, now move xN
  size_t nextSmallestxNID = SIZE_MAX;
  size_t xN = -1;
  for(size_t i = 0; i < lines.size(); i++)
  {
    if(lines[i].x > lines[y].y && lines[i].x < nextSmallestxNID)
    {
      nextSmallestxNID = lines[i].x;
      xN = i;
    }
  }
  return xN;
}

// checks if there is a range with y+1 in it.
// x and y represent a virtual range that has been proven to be continuous
// bingus returns the biggest y thats continuous
size_t bingus(const size_t x, size_t y, const vector<Tuple>& lines)
{
  cout << "bingus called with " << x << "/" << y << " -> " << lines[x].x << "/" << lines[y].y << "\n";
  size_t idAfterRange = lines[y].y + 1;
  cout << "idAfterRange: " << idAfterRange << "\n";

  for(size_t i = 0; i < lines.size(); i++)
  {
    const size_t xIDi = lines[i].x;
    const size_t yIDi = lines[i].y;

    // condition: idAfterRange in range i
    if(idAfterRange >= xIDi && idAfterRange <= yIDi)
    {
      cout << "found range with idAfterRange in it\n";
      const size_t newY = i; // save index of range
      y = bingus(x, newY,lines);
    }
  }
  cout << "bingus returning " << y << "\n";
  return y;
}


int main()
{
  std::ifstream file("input");
  string line;
  vector<Tuple> lines;
  long long idCounter = 0;

  // fill vector with valid tuples
  while(getline(file,line))
  {
    const unsigned long minusPos = line.find('-');
    if(minusPos != string::npos)
    {
      const Tuple t = {
        stoul(line.substr(0,minusPos)),
        stoul(line.substr(minusPos+1, line.size()))};
      lines.push_back(t);
      //cout << t.x << "-" << t.y << "\n";
    }
  }

  size_t xN = 0;
  size_t yN = 0;

  // find smallest xn and biggest yn
  size_t s = SIZE_MAX;
  size_t b = 0;
  for(size_t i = 0; i < lines.size(); i++)
  {
    if(lines[i].x < s)
    {
      xN = i;
      s = lines[i].x;
    }
    if(lines[i].y > b)
    {
      yN = i;
      b = lines[i].y;
    }
  }
  cout << "smallest xN at: " << xN << ", " << "biggest: " << yN << "\n\n";

  //size_t idAfterRange = lines[xN].y+1;

  // now we have starting range with smallest x
  // we now calculate the biggest y we can get
  // that creates a continuous range from smallest x to said y
  // save it, and find the next smallest xN that is bigger than old yN
  while(true)
  {
    size_t y = bingus(xN, xN, lines);
    cout << "y: " << y << "\n";
    idCounter+= (lines[y].y - lines[xN].x) + 1;

    size_t nextSmallestxN = findNextSmallestX(y, lines);

    cout << "nextSmallestxN: " << nextSmallestxN << "\n";

    xN = nextSmallestxN;

    cout << "idCounter: " << idCounter << "\n\n";
    if(lines[y].y == b)
    {
      break;
    }
  }

  return 0;
}
