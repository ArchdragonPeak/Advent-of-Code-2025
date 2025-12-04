#include <fstream>
#include <iostream>
#include <string>
#include <vector>


int main() {
  std::ifstream file("input");
  std::string ids;
  getline(file, ids);
  std::vector<std::string> idList;
  std::vector<std::string> invalidList;
  // std::cout << ids << "\n";

  // append every id range to idList
  int pointer = 0;
  int len = 0;

  for (int i = 0; i < ids.length(); i++)
  {
    char c = ids[i];
    if (c == ',') {
      idList.push_back(ids.substr(pointer, len));
      pointer = i + 1;
      len = -1;
    }
    len++;
  }

  idList.push_back(ids.substr(pointer, len));

  // per idList-Item
  for (std::string item : idList)
  {
    size_t minusPos = item.find('-');
    std::string firstStr = item.substr(0, minusPos);
    std::string secondStr = item.substr(minusPos + 1, item.length() - firstStr.length() + 1);
    // std::cout << firstStr << ":" << secondStr << "\n";

    long long firstInt = std::stoll(firstStr.c_str());
    long long secondInt = std::stoll(secondStr.c_str());
    for (size_t i = firstInt; i <= secondInt; i++)
    {
      std::string lol = std::to_string(i);
      if (lol.length() % 2 == 0)
      {
        // begin to half the length-1 and half the length to half the length
        std::string firstID = lol.substr(0, (lol.length() / 2));
        std::string secondID = lol.substr(lol.length() / 2, lol.length() / 2);
        std::string val = "valid";

        if (firstID == secondID)
        {
          val = "invalid";
          invalidList.push_back(lol);
        }
        // std::cout << lol << " " << firstID << " " << secondID << " -> " <<
        // val << "\n";
      }
    }
  }

  long long num = 0;
  for (std::string str : invalidList)
  {
    num += std::atoll(str.c_str());
  }
  std::cout << "num: " << num;

  /* 1227775554
  for(std::string str : idList)
  {
      std::cout << str << "\n";
  }
  */
  return 0;
}
