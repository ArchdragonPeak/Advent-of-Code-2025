#include <fstream>
#include <vector>
#include <string>
#include <iostream>


int main()
{
    std::ifstream file("input");
    std::string ids;
    getline(file, ids);
    std::vector<std::string> idList;
    std::vector<std::string> invalidList;
    //std::cout << ids << "\n";

    // append every id range to idList
    int pointer = 0;
    int len = 0;
    for(int i = 0; i<ids.length();i++)
    {
        char c = ids[i];
        if(c == ',')
        {
            idList.push_back(ids.substr(pointer,len));
            pointer = i+1;
            len = -1;
        }
        len++;
    }
    idList.push_back(ids.substr(pointer,len));

    // per idList-Item
    for(std::string item : idList)
    {
        size_t minusPos = item.find('-');
        std::string firstStr = item.substr(0, minusPos);
        std::string secondStr = item.substr(minusPos+1, item.length()-firstStr.length()+1);
        //std::cout << firstStr << ":" << secondStr << "\n";

        long long firstInt = std::stoll(firstStr.c_str());
        long long secondInt = std::stoll(secondStr.c_str());
        for(size_t i = firstInt;i <= secondInt;i++)
        {
            std::string id = std::to_string(i);
            //std::cout << "id: " << id << "\n";
            for(int j = 1;j<=id.length();j++)
            {
                std::string digits = id.substr(0,j);
                bool isSame = false;
                for(int k = digits.length();k <= id.length()-digits.length();k=k+digits.length())
                {
                    isSame = true;
                    //std::cout << "k: " << k << " " << "digits: " << digits << "!=" << id.substr(k,j) << "\n";
                    if(digits != id.substr(k, j) || id.length() % j != 0)
                    {
                        isSame = false;
                        break;
                    }
                }
                if(isSame)
                {
                    invalidList.push_back(id);
                    std::cout << "ID gefunden: " << id << "\n";
                    break;
                }
            }
        }
    }
    long long num = 0;
    for(std::string str : invalidList)
    {
        num+= std::atoll(str.c_str());
    }
    std::cout << "num: " << num << "\n";
    file.close();
    return 0;
}
