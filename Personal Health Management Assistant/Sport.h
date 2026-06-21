#pragma once
#include "RecordBase.h"
#include <string>
using namespace std;

class Sport : public RecordBase {
private:
    int minutes;      // 运动时长(分钟)
    int calorie;      // 消耗热量(千卡)
    int quality;      // 运动质量评分(1-10)
public:
    Sport(Time t, User& u, int min, int c);
    void show() const override;
    string getSaveString() const override;
    void calculateQuality();
    int getScore() const override { return quality; }
    int getQuality() const { return quality; }
    int getMinutes() const { return minutes; }
    int getCalorie() const { return calorie; }
};