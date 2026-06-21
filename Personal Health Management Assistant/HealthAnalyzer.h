#pragma once
#include "User.h"
#include "Time.h"

class HealthAnalyzer {
private:
    User* user;

    // 各维度权重
    const double WEIGHT_DIET = 0.25;      // 饮食权重
    const double WEIGHT_SLEEP = 0.20;     // 睡眠权重
    const double WEIGHT_SPORT = 0.20;     // 运动权重
    const double WEIGHT_VITAL = 0.20;     // 生命体征权重
    const double WEIGHT_LIFESTYLE = 0.15; // 生活习惯权重

    // 计算某天某类记录的平均分
    double getAvgScore(const vector<RecordBase*>& records, const string& type) const;

    // 计算单日综合评分
    double calculateDayScore(const vector<RecordBase*>& dayRecords) const;

    // 计算月度各维度平均分
    void calculateMonthAverages(const vector<RecordBase*>& monthRecords,
        double& dietAvg, double& sleepAvg,
        double& sportAvg, double& vitalAvg,
        double& lifestyleAvg, int& daysCount) const;

public:
    HealthAnalyzer(User* u);

    void showDayReport(Time t);
    void showWeekReport(Time t);
    void showMonthReport(Time t);
    void showAdvice();
    void checkAlert(Time t);
};