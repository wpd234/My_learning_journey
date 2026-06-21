#include "HealthAnalyzer.h"
#include "User.h"
#include "Diet.h"
#include "Sleep.h"
#include "Sport.h"
#include "VitalSigns.h"
#include "LifeStyle.h"
#include <iostream>
#include <map>
#include <iomanip>
#include <algorithm>
using namespace std;

HealthAnalyzer::HealthAnalyzer(User* u) : user(u) {}

double HealthAnalyzer::getAvgScore(const vector<RecordBase*>& records, const string& type) const {
    double totalScore = 0;
    int count = 0;

    for (auto record : records) {
        if (record->getType() == type) {
            totalScore += record->getScore();
            count++;
        }
    }

    if (count == 0) {
        return 0;
    }
    return totalScore / count;
}

double HealthAnalyzer::calculateDayScore(const vector<RecordBase*>& dayRecords) const {
    double dietScore = getAvgScore(dayRecords, "Diet");
    double sleepScore = getAvgScore(dayRecords, "Sleep");
    double sportScore = getAvgScore(dayRecords, "Sport");
    double vitalScore = getAvgScore(dayRecords, "VitalSigns");
    double lifestyleScore = getAvgScore(dayRecords, "LIFESTYLE");

    double totalScore = dietScore * WEIGHT_DIET +
        sleepScore * WEIGHT_SLEEP +
        sportScore * WEIGHT_SPORT +
        vitalScore * WEIGHT_VITAL +
        lifestyleScore * WEIGHT_LIFESTYLE;

    return totalScore;
}

void HealthAnalyzer::calculateMonthAverages(const vector<RecordBase*>& monthRecords,
    double& dietAvg, double& sleepAvg,
    double& sportAvg, double& vitalAvg,
    double& lifestyleAvg, int& daysCount) const {
    // 按天分组
    map<Time, vector<RecordBase*>> dayGroups;
    for (auto record : monthRecords) {
        Time date = record->getDate();
        dayGroups[date].push_back(record);
    }

    daysCount = dayGroups.size();

    if (daysCount == 0) {
        dietAvg = sleepAvg = sportAvg = vitalAvg = lifestyleAvg = 0;
        return;
    }

    double totalDiet = 0, totalSleep = 0, totalSport = 0, totalVital = 0, totalLifestyle = 0;
    int dietDays = 0, sleepDays = 0, sportDays = 0, vitalDays = 0, lifestyleDays = 0;

    for (auto& pair : dayGroups) {
        double dietScore = getAvgScore(pair.second, "Diet");
        double sleepScore = getAvgScore(pair.second, "Sleep");
        double sportScore = getAvgScore(pair.second, "Sport");
        double vitalScore = getAvgScore(pair.second, "VitalSigns");
        double lifestyleScore = getAvgScore(pair.second, "LIFESTYLE");

        if (dietScore > 0) { totalDiet += dietScore; dietDays++; }
        if (sleepScore > 0) { totalSleep += sleepScore; sleepDays++; }
        if (sportScore > 0) { totalSport += sportScore; sportDays++; }
        if (vitalScore > 0) { totalVital += vitalScore; vitalDays++; }
        if (lifestyleScore > 0) { totalLifestyle += lifestyleScore; lifestyleDays++; }
    }

    dietAvg = (dietDays > 0) ? totalDiet / dietDays : 0;
    sleepAvg = (sleepDays > 0) ? totalSleep / sleepDays : 0;
    sportAvg = (sportDays > 0) ? totalSport / sportDays : 0;
    vitalAvg = (vitalDays > 0) ? totalVital / vitalDays : 0;
    lifestyleAvg = (lifestyleDays > 0) ? totalLifestyle / lifestyleDays : 0;
}

// 显示单日报告
void HealthAnalyzer::showDayReport(Time t) {
    vector<RecordBase*> records = user->getByDay(t);

    cout << "\n========== " << t.toString() << " 健康报告 ==========" << endl;

    if (records.empty()) {
        cout << "该日期暂无数据记录。" << endl;
        return;
    }

    // 分类显示各记录
    cout << "\n--- 饮食记录 ---" << endl;
    bool hasDiet = false;
    for (auto r : records) {
        if (r->getType() == "Diet") {
            r->show();
            hasDiet = true;
        }
    }
    if (!hasDiet) cout << "今日无饮食记录。" << endl;

    cout << "\n--- 睡眠记录 ---" << endl;
    bool hasSleep = false;
    for (auto r : records) {
        if (r->getType() == "Sleep") {
            r->show();
            hasSleep = true;
        }
    }
    if (!hasSleep) cout << "今日无睡眠记录。" << endl;

    cout << "\n--- 运动记录 ---" << endl;
    bool hasSport = false;
    for (auto r : records) {
        if (r->getType() == "Sport") {
            r->show();
            hasSport = true;
        }
    }
    if (!hasSport) cout << "今日无运动记录。" << endl;

    cout << "\n--- 生命体征 ---" << endl;
    bool hasVital = false;
    for (auto r : records) {
        if (r->getType() == "VitalSigns") {
            r->show();
            hasVital = true;
        }
    }
    if (!hasVital) cout << "今日无生命体征记录。" << endl;

    cout << "\n--- 生活习惯 ---" << endl;
    bool hasLifestyle = false;
    for (auto r : records) {
        if (r->getType() == "LIFESTYLE") {
            r->show();
            hasLifestyle = true;
        }
    }
    if (!hasLifestyle) cout << "今日无生活习惯记录。" << endl;

    cout << "\n========== 各维度评分 ==========" << endl;
    cout << "饮食评分: " << fixed << setprecision(1) << getAvgScore(records, "Diet") << "/10" << endl;
    cout << "睡眠评分: " << getAvgScore(records, "Sleep") << "/10" << endl;
    cout << "运动评分: " << getAvgScore(records, "Sport") << "/10" << endl;
    cout << "生命体征评分: " << getAvgScore(records, "VitalSigns") << "/10" << endl;
    cout << "生活习惯评分: " << getAvgScore(records, "LIFESTYLE") << "/10" << endl;

    // 显示综合评分
    double dayScore = calculateDayScore(records);
    cout << "\n========== 综合评分 ==========" << endl;
    cout << "今日健康总分: " << dayScore << "/10" << endl;

    // 评分等级
    if (dayScore >= 8.5) cout << "评价: 优秀！继续保持！" << endl;
    else if (dayScore >= 7.0) cout << "评价: 良好，还有提升空间。" << endl;
    else if (dayScore >= 5.0) cout << "评价: 一般，需要注意改善。" << endl;
    else if (dayScore > 0) cout << "评价: 较差，请关注健康状况！" << endl;
    else cout << "评价: 数据不足，无法有效评价。" << endl;

    cout << "\n--- 异常提醒 ---" << endl;
    bool hasWarning = false;
    for (auto r : records) {
        if (r->getType() == "VitalSigns") {
			((VitalSigns*)r)->showWarning();//父类强制转换为子类，调用子类特有的函数
            hasWarning = true;
        }
        if (r->getType() == "LIFESTYLE") {
            ((LifeStyle*)r)->showWarning();
            hasWarning = true;
        }
    }
    if (!hasWarning) {
        cout << "无异常指标。" << endl;
    }
}

// 显示本周报告
void HealthAnalyzer::showWeekReport(Time t) {
    cout << "\n========== 本周健康报告 ==========" << endl;
    cout << "报告周期: " << t.addDays(-6).toString() << " 至 " << t.toString() << endl;

    // 获取最近7天的数据
    vector<double> dailyScores;
    vector<Time> dates;

    for (int i = 6; i >= 0; i--) {
        Time date = t.addDays(-i);
        dates.push_back(date);
        vector<RecordBase*> dayRecords = user->getByDay(date);
        double score = calculateDayScore(dayRecords);
        dailyScores.push_back(score);
    }

    // 显示每日评分曲线
    cout << "\n--- 每日健康评分 ---" << endl;
    double weekAvg = 0;
    int validDays = 0;

    for (int i = 0; i < 7; i++) {
        cout << dates[i].toString() << ": ";
        double score = dailyScores[i];

        if (score > 0) {
            validDays++;
            weekAvg += score;
        }

        // 进度条
        int barLen = (int)(score / 10 * 20);
        cout << score << "/10 [";
        for (int j = 0; j < 20; j++) {
            if (j < barLen) cout << "=";
            else cout << " ";
        }
        cout << "]" << endl;
    }

    weekAvg = (validDays > 0) ? weekAvg / validDays : 0;
    cout << "\n本周平均健康分: " << fixed << setprecision(1) << weekAvg << "/10" << endl;

    // 趋势分析
    double firstValid = -1, lastValid = -1;
    for (int i = 0; i < 7; i++) {
        if (dailyScores[i] > 0 && firstValid < 0) firstValid = dailyScores[i];
        if (dailyScores[i] > 0) lastValid = dailyScores[i];
    }

    if (firstValid > 0 && lastValid > 0) {
        if (lastValid > firstValid + 1) {
            cout << "趋势: 健康状况在改善，继续努力！" << endl;
        }
        else if (lastValid < firstValid - 1) {
            cout << "趋势: 健康状况下滑，请注意调整！" << endl;
        }
        else {
            cout << "趋势: 健康状况保持稳定。" << endl;
        }
    }
}

// 显示本月报告
void HealthAnalyzer::showMonthReport(Time t) {
    cout << "\n========== 本月健康报告 ==========" << endl;
    cout << "报告周期: " << t.getYear() << "年" << t.getMonth() << "月" << endl;

    vector<RecordBase*> monthRecords = user->getByMonth(t);

    if (monthRecords.empty()) {
        cout << "本月暂无数据记录。" << endl;
        return;
    }

    // 计算月度各维度平均分
    double dietAvg, sleepAvg, sportAvg, vitalAvg, lifestyleAvg;
    int daysCount;
    calculateMonthAverages(monthRecords, dietAvg, sleepAvg, sportAvg, vitalAvg, lifestyleAvg, daysCount);

    // 显示各维度平均分
    cout << "\n--- 各维度平均评分 ---" << endl;
    cout << "饮食健康: " << fixed << setprecision(1) << dietAvg << "/10 (有记录天数:" << daysCount << ")" << endl;
    cout << "睡眠质量: " << sleepAvg << "/10" << endl;
    cout << "运动情况: " << sportAvg << "/10" << endl;
    cout << "生命体征: " << vitalAvg << "/10" << endl;
    cout << "生活习惯: " << lifestyleAvg << "/10" << endl;

    // 计算月总评分（各维度加权平均）
    double monthScore = dietAvg * WEIGHT_DIET +
        sleepAvg * WEIGHT_SLEEP +
        sportAvg * WEIGHT_SPORT +
        vitalAvg * WEIGHT_VITAL +
        lifestyleAvg * WEIGHT_LIFESTYLE;

    cout << "\n本月综合健康评分: " << monthScore << "/10" << endl;

    // 评分等级
    if (monthScore >= 8.0) cout << "评价: 健康状况优秀！" << endl;
    else if (monthScore >= 6.0) cout << "评价: 健康状况良好。" << endl;
    else if (monthScore >= 4.0) cout << "评价: 健康状况一般，建议改善。" << endl;
    else if (monthScore > 0) cout << "评价: 健康状况较差，请及时调整生活方式！" << endl;
    else cout << "评价: 数据不足，无法有效评价。" << endl;
}

// 健康建议
void HealthAnalyzer::showAdvice() {
    Time getCurrentDate();
    Time now = getCurrentDate();
    vector<RecordBase*> monthRecords = user->getByMonth(now);

    cout << "\n========== 个性化健康建议 ==========" << endl;

    if (monthRecords.empty()) {
        cout << "暂无足够数据生成建议。请先添加健康记录。" << endl;
        return;
    }

    // 计算月度各维度平均分
    double dietAvg, sleepAvg, sportAvg, vitalAvg, lifestyleAvg;
    int daysCount;
    calculateMonthAverages(monthRecords, dietAvg, sleepAvg, sportAvg, vitalAvg, lifestyleAvg, daysCount);

    // 统计分析生活习惯细节
    int totalSteps = 0, stepsCount = 0;
    int highStressCount = 0, stressCount = 0;
    int lowMoodCount = 0, moodCount = 0;
    double totalWater = 0, waterCount = 0;
    int longSitCount = 0, sitCount = 0;

    for (auto r : monthRecords) {
        if (r->getType() == "LIFESTYLE") {
            LifeStyle* ls = (LifeStyle*)r;
            totalSteps += ls->getSteps();
            stepsCount++;
            totalWater += ls->getWater();
            waterCount++;
            if (ls->getSitTime() > 8) longSitCount++;
            sitCount++;
            if (ls->getStress() > 7) highStressCount++;
            stressCount++;
            if (ls->getMood() < 4) lowMoodCount++;
            moodCount++;
        }
    }

    double avgSteps = (stepsCount > 0) ? totalSteps / stepsCount : 0;
    double avgWater = (waterCount > 0) ? totalWater / waterCount : 0;

    // 生成建议
    bool hasAdvice = false;

    if (dietAvg < 6.0 && dietAvg > 0) {
        cout << "【饮食建议】" << endl;
        cout << "• 您的饮食评分偏低(" << dietAvg << "/10)，建议增加蔬菜水果摄入。" << endl;
        cout << "• 控制高热量、高脂肪食物的摄入。" << endl;
        cout << "• 保持三餐规律，避免暴饮暴食。" << endl << endl;
        hasAdvice = true;
    }
    else if (dietAvg >= 8.0) {
        cout << "【饮食建议】" << endl;
        cout << "• 您的饮食习惯很好！继续保持均衡营养。" << endl << endl;
        hasAdvice = true;
    }

    if (sleepAvg < 6.0 && sleepAvg > 0) {
        cout << "【睡眠建议】" << endl;
        cout << "• 您的睡眠质量不佳(" << sleepAvg << "/10)，建议保持规律作息。" << endl;
        cout << "• 睡前避免使用电子设备。" << endl;
        cout << "• 保持卧室安静、黑暗、凉爽。" << endl << endl;
        hasAdvice = true;
    }

    if (sportAvg < 6.0 && sportAvg > 0) {
        cout << "【运动建议】" << endl;
        cout << "• 您运动不足(" << sportAvg << "/10)，建议每周进行3-5次有氧运动。" << endl;
        cout << "• 每天坚持30分钟以上的中等强度运动。" << endl << endl;
        hasAdvice = true;
    }
    else if (sportAvg >= 8.0) {
        cout << "【运动建议】" << endl;
        cout << "• 您的运动习惯很好！继续保持。" << endl << endl;
        hasAdvice = true;
    }

    if (avgSteps > 0 && avgSteps < 5000) {
        cout << "【步数建议】" << endl;
        cout << "• 您日均步数偏少(" << avgSteps << "步)，建议每天步行8000-10000步。" << endl;
        cout << "• 可利用碎片时间多走动。" << endl << endl;
        hasAdvice = true;
    }

    if (avgWater > 0 && avgWater < 1.5) {
        cout << "【饮水建议】" << endl;
        cout << "• 您饮水量不足(" << avgWater << "升)，建议每天饮水1.5-2升。" << endl << endl;
        hasAdvice = true;
    }

    if (sitCount > 0 && (double)longSitCount / sitCount > 0.5) {
        cout << "【久坐建议】" << endl;
        cout << "• 您久坐时间较长，建议每小时站起来活动5分钟。" << endl << endl;
        hasAdvice = true;
    }

    if (stressCount > 0 && (double)highStressCount / stressCount > 0.3) {
        cout << "【心理健康建议】" << endl;
        cout << "• 您近期压力较大，建议适当放松。" << endl;
        cout << "• 尝试冥想、深呼吸等减压方式。" << endl;
        cout << "• 保持社交活动，与亲友交流。" << endl << endl;
        hasAdvice = true;
    }

    if (moodCount > 0 && (double)lowMoodCount / moodCount > 0.3) {
        cout << "【情绪建议】" << endl;
        cout << "• 您近期心情指数偏低，建议多做一些让自己开心的事。" << endl;
        cout << "• 适当运动有助于改善情绪。" << endl << endl;
        hasAdvice = true;
    }

    if (!hasAdvice) {
        if (dietAvg >= 7.0 && sleepAvg >= 7.0 && sportAvg >= 7.0 && avgSteps >= 8000) {
            cout << "【总体评价】" << endl;
            cout << "• 您的整体健康状况良好，请继续保持健康的生活方式！" << endl;
        }
        else {
            cout << "【总体评价】" << endl;
            cout << "• 您的各项指标表现不错，继续保持良好的生活习惯！" << endl;
        }
    }
}

// 检查异常提醒
void HealthAnalyzer::checkAlert(Time t) {
    vector<RecordBase*> records = user->getByDay(t);

    bool hasAlert = false;
    for (auto r : records) {
        if (r->getType() == "VitalSigns") {
            VitalSigns* vs = (VitalSigns*)r;
            if (vs->isAbnormal()) {
                if (!hasAlert) {
                    cout << "\n【生命体征异常提醒】" << endl;
                    hasAlert = true;
                }
                vs->showWarning();
            }
        }
        if (r->getType() == "LIFESTYLE") {
            LifeStyle* ls = (LifeStyle*)r;
            if (ls->isAbnormal()) {
                if (!hasAlert) {
                    cout << "\n【生活习惯异常提醒】" << endl;
                    hasAlert = true;
                }
                ls->showWarning();
            }
        }
    }

    if (hasAlert) {
        cout << "请关注您的健康状况！" << endl;
    }
}