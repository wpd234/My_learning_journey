#pragma once
class User;
class Time;
#include "RecordBase.h"

class LifeStyle : public RecordBase
{
private:
    int steps;           // 每日步数
    double water;        // 饮水量(ml)
    int sitTime;         // 久坐时长(小时)
    int eyeTime;         // 用眼时长(小时)
    int stress;          // 压力指数 1-10
    int mood;            // 情绪指数 1-10
    int quality;         // 生活习惯评分
public:
    LifeStyle(Time t, User& u, int steps_, double water_, int sitTime_, int eyeTime_, int stress_, int mood_);
    void calculateQuality();
    void show() const override;
    string getSaveString() const override;
    int getQuality() const { return quality; }
    bool stepsabnormal() const;
	bool waterabnormal() const;
	bool sitTimeabnormal() const;
	bool eyeTimeabnormal() const;
	bool stressabnormal() const;
	bool moodabnormal() const;
	bool isAbnormal() const;
	void showWarning() const;
    int getScore() const override { return quality; }

    int getSteps() const { return steps; }
    double getWater() const { return water; }
    int getSitTime() const { return sitTime; }
    int getEyeTime() const { return eyeTime; }
    int getStress() const { return stress; }
    int getMood() const { return mood; }
};