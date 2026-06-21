#include "UserManager.h"
#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

UserManager::UserManager() {
    loadUsers();
}

void UserManager::loadUsers() {
    ifstream infile(userFile);
    if (!infile) return;

    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string userID, username, password, sexStr;
        float weight, height;

        getline(ss, userID, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, sexStr, ',');
        ss >> weight;
        ss.ignore();
        ss >> height;

        char sex = sexStr[0];
        User user(userID, username, sex, password, weight, height);
        userList.push_back(user);
    }
    infile.close();
}

void UserManager::saveUsers() {
    ofstream outfile(userFile);
    if (!outfile) return;

    for (const auto& user : userList) {
        outfile << user.getUserID() << ","
            << user.getUsername() << ","
            << user.getPassword() << ","
            << user.getSex() << ","
            << user.getWeight() << ","
            << user.getHeight() << endl;
    }
    outfile.close();
}

bool UserManager::registerUser(string uname, string pwd, char sex, float weight, float height) {
    for (const auto& user : userList) {
        if (user.getUsername() == uname) {
            cout << "用户名已存在！" << endl;
            return false;
        }
    }

    string userID = "U" + to_string(userList.size() + 1000);
    User newUser(userID, uname, sex, pwd, weight, height);
    userList.push_back(newUser);
    saveUsers();

    FileManager fm(uname);
    fm.save(newUser);

    cout << "注册成功！" << endl;
    return true;
}

User* UserManager::login(string username, string password) {
    for (auto& user : userList) {
        if (user.getUsername() == username && user.getPassword() == password) {
            cout << "登录成功！欢迎 " << username << endl;
            FileManager fm(username);
            fm.load(user);  // 这会修改 user 对象中的 records
            return &user;
        }
    }
    cout << "用户名或密码错误！" << endl;
    return nullptr;
}

void UserManager::changePassword(string uname, string newPwd) {
    for (auto& user : userList) {
        if (user.getUsername() == uname) {
            user.setPassword(newPwd);
            saveUsers();
            cout << "密码修改成功！" << endl;
            return;
        }
    }
    cout << "用户不存在！" << endl;
}

void UserManager::removeUser(string uname) {
    auto it = remove_if(userList.begin(), userList.end(),
        [&uname](const User& u) { return u.getUsername() == uname; });

    if (it != userList.end()) {
        userList.erase(it, userList.end());
        saveUsers();
        string filename = uname + ".txt";
        remove(filename.c_str());
        cout << "用户已删除" << endl;
    }
    else {
        cout << "用户不存在" << endl;
    }
}

bool UserManager::userExists(string uname) {
    for (const auto& user : userList) {
        if (user.getUsername() == uname) return true;
    }
    return false;
}