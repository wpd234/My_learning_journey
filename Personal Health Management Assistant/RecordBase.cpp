#include "RecordBase.h"
#include "User.h"  // 在 cpp 中包含 User.h

RecordBase::RecordBase(User& u, Time d) : user(u), Date(d), type("Unknown") {}

Time RecordBase::getDate() const {
    return Date;
}