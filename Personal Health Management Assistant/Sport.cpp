#include "Sport.h"
#include "User.h"
#include "DataValidator.h"
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

Sport::Sport(Time t, User& u, int min, int c) : RecordBase(u, t) {
    string errorMsg;
    if (DataValidator::validateMinutes(min, errorMsg))
        minutes = min;
    if (DataValidator::validateCalories(c, errorMsg))
        calorie = c;
    type = "Sport";
    quality = 0;
}

void Sport::show() const {
    cout << "运动时长: " << minutes << "分钟 ";
    cout << "消耗热量: " << calorie << "千卡 ";
    cout << "运动质量: " << quality << "/10 " << endl;
}

string Sport::getSaveString() const {
    return "SPORT:" + Date.toString() + "," + to_string(minutes) + "," +
        to_string(calorie) + "," + to_string(quality);
}

void Sport::calculateQuality() {
    // 时长评分
    double timeScore = 0.0;
    if (minutes >= 60) timeScore = 10.0;
    else if (minutes >= 45) timeScore = 8.0;
    else if (minutes >= 30) timeScore = 6.0;
    else if (minutes >= 20) timeScore = 4.0;
    else if (minutes >= 10) timeScore = 2.0;
    else if (minutes > 0) timeScore = 1.0;
    else timeScore = 0.0;

    // 强度评分（每分钟消耗热量）
    double calPerMinute = (minutes > 0) ? (double)calorie / minutes : 0;
    double intensityScore = 0.0;
    if (calPerMinute >= 10) intensityScore = 10.0;
    else if (calPerMinute >= 8) intensityScore = 8.0;
    else if (calPerMinute >= 6) intensityScore = 6.0;
    else if (calPerMinute >= 4) intensityScore = 4.0;
    else if (calPerMinute > 0) intensityScore = 2.0;
    else intensityScore = 0.0;

    // 综合评分：时长权重50%，强度权重50%
    double totalScore = timeScore * 0.5 + intensityScore * 0.5;

    quality = (int)round(totalScore);
    if (quality < 1) quality = 1;
    if (quality > 10) quality = 10;
}