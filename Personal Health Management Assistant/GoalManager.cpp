#include "GoalManager.h"
#include "Diet.h"
#include "Sport.h"
#include <iostream>
#include <iomanip>
using namespace std;

GoalManager::GoalManager(User* u) : user(u), targetCalorie(2000), targetSportMin(30) {}

void GoalManager::setGoals(int cal, int min) {
    if (cal > 0 && cal <= 5000) {
        targetCalorie = cal;
    }
    else {
        cout << "热量目标无效（应为1-5000），使用当前值: " << targetCalorie << endl;
    }

    if (min > 0 && min <= 300) {
        targetSportMin = min;
    }
    else {
        cout << "运动目标无效（应为1-300），使用当前值: " << targetSportMin << endl;
    }

    cout << "目标设置成功！" << endl;
    cout << "每日热量目标: " << targetCalorie << " 千卡" << endl;
    cout << "每日运动目标: " << targetSportMin << " 分钟" << endl;
}

void GoalManager::showProgress(Time t) {
    if (user == nullptr) {
        cout << "错误：用户未设置！" << endl;
        return;
    }

    cout << "\n========== " << t.toString() << " 目标进度 ==========" << endl;
    cout << "当前目标: 热量 " << targetCalorie << " 千卡, 运动 " << targetSportMin << " 分钟" << endl;

    // 获取当天的记录
    vector<RecordBase*> dayRecords = user->getByDay(t);

    int totalCalorie = 0;
    int totalSportMinutes = 0;

    // 统计当天数据
    for (auto record : dayRecords) {
        if (record->getType() == "Diet") {
            Diet* diet = dynamic_cast<Diet*>(record);
            if (diet) {
                totalCalorie += diet->getCalorie();
            }
        }
        else if (record->getType() == "Sport") {
            Sport* sport = dynamic_cast<Sport*>(record);
            if (sport) {
                totalSportMinutes += sport->getMinutes();
            }
        }
    }

    // 热量目标进度
    if (targetCalorie > 0) {
        double caloriePercent = (double)totalCalorie / targetCalorie * 100;
        if (caloriePercent > 100) caloriePercent = 100;
        cout << "热量摄入: " << totalCalorie << "/" << targetCalorie << " 千卡 ";
        cout << "[" << fixed << setprecision(0) << caloriePercent << "%]" << endl;

        // 进度条
        int barLen = (int)(caloriePercent / 100 * 20);
        cout << "[";
        for (int j = 0; j < 20; j++) {
            if (j < barLen) cout << "=";
            else cout << " ";
        }
        cout << "]" << endl;

        if (totalCalorie > targetCalorie) {
            cout << "警告: 热量摄入超标！" << endl;
        }
        else if (totalCalorie < targetCalorie * 0.7) {
            cout << "提示: 热量摄入不足。" << endl;
        }
        else {
            cout << "评价: 热量摄入合理。" << endl;
        }
    }

    cout << endl;

    // 运动目标进度
    if (targetSportMin > 0) {
        double sportPercent = (double)totalSportMinutes / targetSportMin * 100;
        if (sportPercent > 100) sportPercent = 100;
        cout << "运动时长: " << totalSportMinutes << "/" << targetSportMin << " 分钟 ";
        cout << "[" << fixed << setprecision(0) << sportPercent << "%]" << endl;

        // 进度条
        int barLen = (int)(sportPercent / 100 * 20);
        cout << "[";
        for (int j = 0; j < 20; j++) {
            if (j < barLen) cout << "=";
            else cout << " ";
        }
        cout << "]" << endl;

        if (totalSportMinutes < targetSportMin) {
            cout << "提示: 运动时长不足，建议增加运动。" << endl;
        }
        else {
            cout << "评价: 运动目标达成！" << endl;
        }
    }

    // 综合评估
    cout << "\n--- 综合评估 ---" << endl;
    bool calorieOk = (totalCalorie <= targetCalorie && totalCalorie >= targetCalorie * 0.7);
    bool sportOk = (totalSportMinutes >= targetSportMin);

    if (calorieOk && sportOk) {
        cout << "优秀！今日达成所有健康目标！" << endl;
    }
    else if (calorieOk || sportOk) {
        cout << "良好！部分目标已达成，继续努力！" << endl;
    }
    else {
        cout << "需要加油！建议制定更合理的计划。" << endl;
    }
}