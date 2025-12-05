#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>

using std::vector;
using std::string;
using std::cout;

int main()
{
  std::ifstream file("input");
  vector<string> linesRanges;
  vector<string> linesIDs;
  string line;
  std::set<long long> availableIDs;

  while(getline(file, line))
  {
    if(line.find('-') != string::npos)
    {
      linesRanges.push_back(line);
    }
    else if(!line.empty())
    {
      linesIDs.push_back(line);
    }
  }

  file.close();

  for(string line : linesIDs)
  {
    long long id = stoll(line);
    for(string range:linesRanges)
    {
      long long start = stoll(range.substr(0, range.find('-')));
      long long end = stoll(range.substr(range.find('-')+1, range.size()));
      if(id >= start && id <= end)
      {
        availableIDs.insert(id);
        cout << "ist drin: " << id << "\n";
      }
    }
  }
  cout << availableIDs.size() << "\n";
}
