#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>

using std::string;
using std::vector;
using std::cout;
using std::shared_ptr;
using std::make_shared;

struct Tuple
{
  size_t x;
  size_t y;
};

struct Node
{
  Tuple pos;
  shared_ptr<Node> left;
  shared_ptr<Node> right;
  size_t value = 0;
};

size_t counter = 0;

void traverse(shared_ptr<Node>& parent)
{
  cout << "Traversing: " << parent->pos.x << ", " << parent->pos.y << "\n";
  
  //if(parent->value != 0) return;
  counter++;
  // go left
  if(parent->left != nullptr)
  {
    if(parent->left->value == 0)
    {
      traverse(parent->left);
      parent->value += parent->left->value;
    }
    else
    {
      parent->value += parent->left->value;
    }
  }
  else
  {
    cout << "no left child" << "\n";
    parent->value++;
  }
  
  // go right
  if(parent->right != nullptr)
  {
    if(parent->right->value == 0)
    {
    traverse(parent->right);
    parent->value += parent->right->value;
    }
    else
    {
      parent->value += parent->right->value;
    }
  }
  else
  {
    cout << "no right child" << "\n";
    parent->value++;
  }
  cout << "My value is: " << parent->value << "\n";
}

void getChildren(vector<string> lines, vector<shared_ptr<Node>>& treeList, shared_ptr<Node>& node)
{
  const size_t y = node->pos.y;
  //cout << node-> pos.x <<", " << y << "\n";
  
  // alogrithm to get the two children of a node
  for(size_t i = node->pos.x; i < lines.size();i++)
  {
    //cout << "i: " << i << " y: " << y << "\n";
    if(y>0 && node->left == nullptr)
    {
      if(lines[i][y-1] == '^')
      {
        // left node
        for(shared_ptr<Node>& child:treeList)
        {
          if(child->pos.x == i && child->pos.y == node->pos.y-1)
          {
            cout << "Child Node (" << child->pos.x << ", " << child->pos.y
            << ") found for (" << node->pos.x << ", " << node->pos.y << ")" << "\n";
            node->left = child;
            break;
          }
        }
      }
    }
    
    if(y<lines[i].size()-1 && node->right == nullptr)
    {
      if(lines[i][y+1] == '^')
      {
        // right node
        for(shared_ptr<Node>& child:treeList)
        {
          if(child->pos.x == i && child->pos.y == node->pos.y+1)
          {
            cout << "Child Node (" << child->pos.x << ", " << child->pos.y
            << ") found for (" << node->pos.x << ", " << node->pos.y << ")" << "\n";
            node->right = child;
            break;
          }
        }
      }
    }
  }
}

// x: height, y: width
void construct(vector<string> lines, vector<shared_ptr<Node>>& treeList)
{
  for(size_t i = 0; i < lines.size(); i++)
  {
    cout << lines[i] << " line: " << i << "\n";
    for(size_t j = 0; j < lines[i].size(); j++)
    {
      if(lines[i][j] == '^')
      {
        shared_ptr<Node> node = make_shared<Node>();
        node->pos = {i ,j};
        //if(i == lines.size()-2) node->value = 2;
        cout << "Node: (" << node->pos.x << ", " << node->pos.y << ") value: " << node->value << "\n";
        treeList.push_back(std::move(node));
      }
    }
  }
}


int main()
{
  std::fstream file("input");
  string line;
  vector<string> lines;
  vector<shared_ptr<Node>> treeList;
  while(getline(file, line))
  {
    lines.push_back(line);
  }
  
  // first beam
  size_t first = lines[0].find('S');
  lines[1][first] = '|';
  
  // erasing multiple exists, but still
  lines.erase(lines.begin());
  lines.erase(lines.begin());
  
  shared_ptr<Node> root = make_shared<Node>();
  root->pos = {0, lines[0].find('^')};
  construct(lines, treeList);
  
  // construct tree
  for(shared_ptr<Node>& node : treeList)
  {
    getChildren(lines, treeList, node);
  }
  cout << treeList.size() << "\n";
  // traverse tree
  traverse(treeList[0]);
  
  
  cout << "Root Node Value: " << treeList[0]->value << "\n";
  
  
  cout << "---" << "\n";
  cout << counter << "\n";
}