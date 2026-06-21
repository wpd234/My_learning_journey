#pragma once
#include "Time.h"
#include <string>
using namespace std;

// 前向声明，避免循环依赖
class User;

class RecordBase {
protected:
    User& user;
    Time Date;
    string type;
public:
    RecordBase(User& u, Time d);
    virtual void show() const = 0;
    virtual string getSaveString() const = 0;
    virtual int getScore() const = 0;
    Time getDate() const;
    string getType() const { return type; }
    virtual ~RecordBase() = default;
};