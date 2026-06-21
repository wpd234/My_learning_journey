#include "User.h"
#include "RecordBase.h"

User::User(string id, string name, char s, string pass, float w, float h)
    : userID(id), username(name), sex(s), password(pass), weight(w), height(h) {
    bmi = weight / (height * height);
}

User::~User() {
    for (auto record : records) {
        delete record;
    }
}

void User::addRecord(RecordBase* r) {
    records.push_back(r);
}

vector<RecordBase*>& User::getRecords() {
    return records;
}

void User::clearAll() {
    for (auto record : records) {
        delete record;
    }
    records.clear();
}

vector<RecordBase*> User::getByDay(Time t) {
    vector<RecordBase*> result;
    for (auto record : records) {
        if (record->getDate().isSameDay(t)) {
            result.push_back(record);
        }
    }
    return result;
}

vector<RecordBase*> User::getByMonth(Time t) {
    vector<RecordBase*> result;
    for (auto record : records) {
        if (record->getDate().getYear() == t.getYear() &&
            record->getDate().getMonth() == t.getMonth()) {
            result.push_back(record);
        }
    }
    return result;
}

// 注意：不要在这里重复实现 getUsername、getUserID 等内联函数