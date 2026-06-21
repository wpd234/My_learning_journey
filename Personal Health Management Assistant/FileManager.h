#pragma once
#include "User.h"
#include <string>

class FileManager {
private:
    string filename;
public:
    FileManager(string user);
    bool load(User& user);
    bool save(User& user);
};