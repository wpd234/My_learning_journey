#include "Sleep.h"
#include "User.h"           // 添加
#include "DataValidator.h"
#include <iostream>
using namespace std;

Sleep::Sleep(Time t, User& u,int h, int q, int s, int w) : RecordBase(u, t) {
	string errorMsg;
	if (DataValidator::validateSleepDuration(h, errorMsg))
		sleepHour = h;
	if (DataValidator::validateQuality(q, errorMsg))
		quality = q;
	sol = s;
	wakeUpTimes = w;
	type = "Sleep";
}

void Sleep::show() const {
	cout << "睡眠时长: " << sleepHour << "小时 ";
	cout << "睡眠质量: " << quality << "/10 ";
	cout << "睡眠潜伏期: " << sol << "分钟 ";
	cout << "夜醒次数: " << wakeUpTimes << endl;
}

string Sleep::getSaveString() const {
	return "SLEEP:" + Date.toString() + "," + to_string(sleepHour) + "," +
		to_string(quality) + "," + to_string(sol) + "," + to_string(wakeUpTimes);
}

int Sleep::getScore() const {
    // 综合睡眠质量评分
    double score = quality;  // 基础分来自用户自评

    // 时长调整（推荐7-9小时）
    if (sleepHour >= 7 && sleepHour <= 9) {
        score += 1.0;  // 时长合理，加1分
    }
    else if (sleepHour < 5 || sleepHour > 10) {
        score -= 1.0;  // 时长严重不合理，扣1分
    }
    else if (sleepHour < 6 || sleepHour > 10) {
        score -= 0.5;  // 时长稍不合理，扣0.5分
    }

    // 夜醒次数调整
    if (wakeUpTimes == 0) {
        score += 0.5;  // 无夜醒，加0.5分
    }
    else if (wakeUpTimes >= 3) {
        score -= 1.0;  // 夜醒频繁，扣1分
    }
    else if (wakeUpTimes >= 2) {
        score -= 0.5;  // 夜醒较多，扣0.5分
    }

    // 入睡潜伏期调整（理想15-30分钟）
    if (sol >= 15 && sol <= 30) {
        score += 0.5;  // 入睡正常，加0.5分
    }
    else if (sol > 60) {
        score -= 1.0;  // 入睡困难，扣1分
    }
    else if (sol > 45) {
        score -= 0.5;  // 入睡较慢，扣0.5分
    }

    if (score < 1) score = 1;
    if (score > 10) score = 10;
    return (int)round(score);
}