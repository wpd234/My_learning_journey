#pragma once
#include "RecordBase.h"

class Sleep : public RecordBase {
private:
    string name;
    int sleepHour;
    int quality;
	int sol;//睡眠潜伏期(单位分钟)
	int wakeUpTimes;//夜醒次数
public:
    Sleep(Time t, User& u,int h, int q, int s, int w);
    void show() const override;
    string getSaveString() const override;
    int getScore() const override; // 睡眠质量就是评分
    int getQuality() const { return quality; }
    int getSleepHour() const { return sleepHour; }
    int getWakeUpTimes() const { return wakeUpTimes; }
    int getSOL() const { return sol; }
};