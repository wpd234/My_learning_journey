#pragma once
#include "FileManager.h"
#include "User.h"
#include <vector>
using namespace std;

#ifndef USERMANAGER_H
#define USERMANAGER_H

class UserManager {
private:
    vector<User> userList;  // 直接存储 User，不要 UserInfo
    string userFile = "users.txt";
    void loadUsers();
    void saveUsers();
public:
    UserManager();
    bool registerUser(string uname, string pwd, char sex, float weight, float height);
    User* login(string uname, string pwd);
    void changePassword(string uname, string newPwd);
    void removeUser(string uname);
    bool userExists(string uname);
};

#endif