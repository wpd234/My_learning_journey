#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>
#include "Time.h"
#include "User.h"
#include "UserManager.h"
#include "HealthAnalyzer.h"
#include "GoalManager.h"
#include "FileManager.h"
#include "Diet.h"
#include "Sleep.h"
#include "Sport.h"
#include "VitalSigns.h"
#include "LifeStyle.h"

using namespace std;

// 获取当前系统日期
Time getCurrentDate() {
    time_t now = time(nullptr);
    tm localtm;
#ifdef _WIN32
    localtime_s(&localtm, &now);
#else
    localtime_r(&now, &localtm);
#endif
    return Time(localtm.tm_year + 1900, localtm.tm_mon + 1, localtm.tm_mday);
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void waitForEnter() {
    cout << "\n按回车键继续...";
    clearInput();
    cin.get();
}

void showMainMenu() {
    cout << "\n========== 个人健康管理系统 ==========" << endl;
    cout << "1. 用户注册" << endl;
    cout << "2. 用户登录" << endl;
    cout << "3. 退出系统" << endl;
    cout << "=======================================" << endl;
    cout << "请选择: ";
}

void showUserMenu() {
    cout << "\n========== 健康管理菜单 ==========" << endl;
    cout << "1. 添加健康记录" << endl;
    cout << "2. 查看今日报告" << endl;
    cout << "3. 查看指定日期报告" << endl;
    cout << "4. 查看本周报告" << endl;
    cout << "5. 查看本月报告" << endl;
    cout << "6. 查看健康建议" << endl;
    cout << "7. 查看目标进度" << endl;
    cout << "8. 设置健康目标" << endl;
    cout << "9. 查看所有记录" << endl;
    cout << "10. 修改密码" << endl;
    cout << "11. 注销账号" << endl;
    cout << "0. 退出登录" << endl;
    cout << "=================================" << endl;
    cout << "请选择: ";
}

void addRecordMenu(User* currentUser) {
    int choice;
    cout << "\n===== 添加健康记录 =====" << endl;
    cout << "1. 饮食记录" << endl;
    cout << "2. 睡眠记录" << endl;
    cout << "3. 运动记录" << endl;
    cout << "4. 生命体征记录" << endl;
    cout << "5. 生活习惯记录" << endl;
    cout << "0. 返回" << endl;
    cout << "请选择: ";
    cin >> choice;

    int year, month, day;
    cout << "请输入日期(年 月 日): ";
    cin >> year >> month >> day;
    Time date(year, month, day);

    switch (choice) {
    case 1: {
        int calorie;
        double carbs, protein, fat;
        cout << "请输入热量(千卡): ";
        cin >> calorie;
        cout << "请输入碳水化合物(克): ";
        cin >> carbs;
        cout << "请输入蛋白质(克): ";
        cin >> protein;
        cout << "请输入脂肪(克): ";
        cin >> fat;

        Diet* diet = new Diet(date, *currentUser, calorie, carbs, protein, fat);
        diet->calculateQuantity();
        currentUser->addRecord(diet);
        cout << "饮食记录添加成功！评分: " << diet->getScore() << "/10" << endl;
        break;
    }
    case 2: {
        int hour, quality, sol, wakeTimes;
        cout << "请输入睡眠时长(小时): ";
        cin >> hour;
        cout << "请输入睡眠质量(1-10): ";
        cin >> quality;
        cout << "请输入睡眠潜伏期(分钟): ";
        cin >> sol;
        cout << "请输入夜醒次数: ";
        cin >> wakeTimes;

        Sleep* sleep = new Sleep(date, *currentUser, hour, quality, sol, wakeTimes);
        currentUser->addRecord(sleep);
        cout << "睡眠记录添加成功！评分: " << sleep->getScore() << "/10" << endl;
        break;
    }
    case 3: {
        int minutes, calorie;
        cout << "请输入运动时长(分钟): ";
        cin >> minutes;
        cout << "请输入消耗热量(千卡): ";
        cin >> calorie;

        Sport* sport = new Sport(date, *currentUser, minutes, calorie);
        sport->calculateQuality();
        currentUser->addRecord(sport);
        cout << "运动记录添加成功！评分: " << sport->getScore() << "/10" << endl;
        break;
    }
    case 4: {
        double temp, glucose, lipid, oxygen;
        int sys, dia, hr;
        cout << "请输入体温(°C): ";
        cin >> temp;
        cout << "请输入收缩压(mmHg): ";
        cin >> sys;
        cout << "请输入舒张压(mmHg): ";
        cin >> dia;
        cout << "请输入血糖(mmol/L): ";
        cin >> glucose;
        cout << "请输入心率(次/分): ";
        cin >> hr;
        cout << "请输入血脂(mmol/L): ";
        cin >> lipid;
        cout << "请输入血氧(%): ";
        cin >> oxygen;

        VitalSigns* vs = new VitalSigns(date, *currentUser, temp, sys, dia, glucose, hr, lipid, oxygen);
        currentUser->addRecord(vs);
        cout << "生命体征记录添加成功！评分: " << vs->getScore() << "/10" << endl;
        break;
    }
    case 5: {
        int steps, sitTime, eyeTime, stress, mood;
        double water;
        cout << "请输入步数: ";
        cin >> steps;
        cout << "请输入饮水量(升): ";
        cin >> water;
        cout << "请输入久坐时间(小时): ";
        cin >> sitTime;
        cout << "请输入用眼时间(小时): ";
        cin >> eyeTime;
        cout << "请输入压力指数(1-10): ";
        cin >> stress;
        cout << "请输入心情指数(1-10): ";
        cin >> mood;

        LifeStyle* ls = new LifeStyle(date, *currentUser, steps, water, sitTime, eyeTime, stress, mood);
        ls->calculateQuality();
        currentUser->addRecord(ls);
        cout << "生活习惯记录添加成功！评分: " << ls->getScore() << "/10" << endl;
        break;
    }
    default:
        return;
    }

    FileManager fm(currentUser->getUsername());
    fm.save(*currentUser);
    cout << "数据已自动保存。" << endl;
}

void viewDayReport(User* currentUser) {
    int year, month, day;
    cout << "请输入日期(年 月 日): ";
    cin >> year >> month >> day;
    Time date(year, month, day);
    HealthAnalyzer analyzer(currentUser);
    analyzer.showDayReport(date);
}

void viewAllRecords(User* currentUser) {
    vector<RecordBase*>& records = currentUser->getRecords();
    if (records.empty()) {
        cout << "暂无任何记录！" << endl;
        return;
    }
    cout << "\n========== 所有健康记录 ==========" << endl;
    for (auto record : records) {
        cout << "日期: " << record->getDate().toString() << " | ";
        if (record->getType() == "DIET") cout << "[饮食] ";
        else if (record->getType() == "SLEEP") cout << "[睡眠] ";
        else if (record->getType() == "SPORT") cout << "[运动] ";
        else if (record->getType() == "VITAL_SIGNS") cout << "[生命体征] ";
        else if (record->getType() == "LIFESTYLE") cout << "[生活习惯] ";
        cout << "评分: " << record->getScore() << "/10" << endl;
    }
    cout << "共 " << records.size() << " 条记录" << endl;
}

void showWeekReport(User* currentUser) {
    int year, month, day;
    cout << "请输入参考日期(年 月 日，将显示该日所在周的报告): ";
    cin >> year >> month >> day;
    Time date(year, month, day);
    HealthAnalyzer analyzer(currentUser);
    analyzer.showWeekReport(date);
}

void showMonthReport(User* currentUser) {
    int year, month;
    cout << "请输入年份和月份(年 月): ";
    cin >> year >> month;
    Time date(year, month, 1);
    HealthAnalyzer analyzer(currentUser);
    analyzer.showMonthReport(date);
}

void changePassword(User* currentUser, UserManager& um) {
    string oldPwd, newPwd;
    cout << "请输入原密码: ";
    cin >> oldPwd;
    cout << "请输入新密码: ";
    cin >> newPwd;
    if (currentUser->getPassword() == oldPwd) {
        currentUser->setPassword(newPwd);
        um.changePassword(currentUser->getUsername(), newPwd);
        cout << "密码修改成功！" << endl;
    }
    else {
        cout << "原密码错误！" << endl;
    }
}

void deleteAccount(User*& currentUser, UserManager& um) {
    string pwd;
    cout << "请输入密码确认注销: ";
    cin >> pwd;
    if (currentUser->getPassword() == pwd) {
        um.removeUser(currentUser->getUsername());
        delete currentUser;
        currentUser = nullptr;
        cout << "账号已注销！" << endl;
    }
    else {
        cout << "密码错误！" << endl;
    }
}

int main() {
    UserManager userManager;
    User* currentUser = nullptr;
    GoalManager* goalManager = nullptr;
    int choice;

    cout << "=====================================" << endl;
    cout << "   欢迎使用个人健康管理系统" << endl;
    cout << "=====================================" << endl;

    while (true) {
        if (currentUser == nullptr) {
            showMainMenu();
            cin >> choice;

            switch (choice) {
            case 1: {
                string username, password;
                char sex;
                float weight, height;
                cout << "===== 用户注册 =====" << endl;
                cout << "用户名: ";
                cin >> username;
                cout << "密码: ";
                cin >> password;
                cout << "性别(m/f): ";
                cin >> sex;
                cout << "体重(kg): ";
                cin >> weight;
                cout << "身高(cm): ";
                cin >> height;
                if (userManager.registerUser(username, password, sex, weight, height)) {
                    cout << "注册成功！请登录。" << endl;
                }
                break;
            }
            case 2: {
                string username, password;
                cout << "===== 用户登录 =====" << endl;
                cout << "用户名: ";
                cin >> username;
                cout << "密码: ";
                cin >> password;
                currentUser = userManager.login(username, password);
                if (currentUser != nullptr) {
                    cout << "登录成功！欢迎 " << currentUser->getUsername() << endl;
                    goalManager = new GoalManager(currentUser);
                }
                break;
            }
            case 3:
                cout << "感谢使用！再见！" << endl;
                return 0;
            default:
                cout << "无效选择！" << endl;
                break;
            }
        }
        else {
            showUserMenu();
            cin >> choice;

            switch (choice) {
            case 1:
                addRecordMenu(currentUser);
                break;
            case 2: {
                Time today = getCurrentDate();
                HealthAnalyzer analyzer(currentUser);
                analyzer.showDayReport(today);
                break;
            }
            case 3:
                viewDayReport(currentUser);
                break;
            case 4:
                showWeekReport(currentUser);
                break;
            case 5:
                showMonthReport(currentUser);
                break;
            case 6: {
                HealthAnalyzer analyzer(currentUser);
                analyzer.showAdvice();
                break;
            }
            case 7:
                if (goalManager != nullptr) {
                    Time today = getCurrentDate();
                    goalManager->showProgress(today);
                }
                break;
            case 8:
                if (goalManager != nullptr) {
                    int cal, min;
                    cout << "请输入每日热量目标(千卡): ";
                    cin >> cal;
                    cout << "请输入每日运动目标(分钟): ";
                    cin >> min;
                    goalManager->setGoals(cal, min);
                }
                break;
            case 9:
                viewAllRecords(currentUser);
                break;
            case 10:
                changePassword(currentUser, userManager);
                {
                    FileManager fm(currentUser->getUsername());
                    fm.save(*currentUser);
                }
                break;
            case 11:
                deleteAccount(currentUser, userManager);
                if (currentUser == nullptr) {
                    delete goalManager;
                    goalManager = nullptr;
                }
                break;
            case 0:
                if (currentUser != nullptr) {
                    FileManager fm(currentUser->getUsername());
                    fm.save(*currentUser);
                    cout << "数据已保存。" << endl;
                }
                delete goalManager;
                goalManager = nullptr;
                currentUser = nullptr;
                cout << "已退出登录！" << endl;
                break;
            default:
                cout << "无效选择！" << endl;
                break;
            }

            if (choice != 0 && choice != 11 && currentUser != nullptr) {
                waitForEnter();
            }
        }
    }
    return 0;
}