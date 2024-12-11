#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <algorithm>
#include <filesystem>
#include <string>

class Navigation {
    std::string current_directory;

   public:
    Navigation();
    void pwd();
};

#endif
