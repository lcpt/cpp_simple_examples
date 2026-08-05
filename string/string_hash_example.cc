// Source - https://stackoverflow.com/a/8029155
// Posted by Seth Carnegie, modified by community. See post 'Timeline' for change history
// Retrieved 2026-08-05, License - CC BY-SA 3.0

#include <string>
#include <unordered_map>
#include <iostream>

std::hash<std::string> hasher;

const std::string s= "heyho";

int main()
  {
    size_t hash = hasher(s);

    std::cout << hash << std::endl;
  }
