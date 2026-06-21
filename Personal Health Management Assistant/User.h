#pragma once
#include <vector>
#include <string>
#include "Time.h"

using namespace std;

// 前向声明
class RecordBase;

class User {
private:
    string userID;
    string username;
    string password;
    char sex;
    vector<RecordBase*> records;
    float weight;
    float height;
    float bmi;

public:
    User(string id, string name, char s, string pass, float w, float h);
    ~User();

    void addRecord(RecordBase* r);
    void clearAll();
    vector<RecordBase*>& getRecords();

    // 声明为 inline 或者只在头文件中声明
    string getUsername() const { return username; }
    string getUserID() const { return userID; }
    string getPassword() const { return password; }
    float getWeight() const { return weight; }
    float getHeight() const { return height; }
    float getBMI() const { return bmi; }
    char getSex() const { return sex; }

    void setPassword(const string& pass) { password = pass; }

    vector<RecordBase*> getByDay(Time t);
    vector<RecordBase*> getByMonth(Time t);
};