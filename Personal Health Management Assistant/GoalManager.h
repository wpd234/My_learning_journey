#pragma once
#include "User.h"
#include "Time.h"

class GoalManager {
private:
    User* user;
    int targetCalorie;
    int targetSportMin;
public:
    GoalManager(User* u);
    void setGoals(int cal, int min);
    void showProgress(Time t);
    int getTargetCalorie() const { return targetCalorie; }
    int getTargetSportMin() const { return targetSportMin; }
};