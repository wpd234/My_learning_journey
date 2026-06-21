#include "FileManager.h"
#include "Diet.h"
#include "Sleep.h"
#include "Sport.h"
#include "VitalSigns.h"
#include "LifeStyle.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

FileManager::FileManager(string user) : filename(user + ".txt") {}

bool FileManager::load(User& user) {
    ifstream infile(filename);
    if (!infile) {
        cout << "文件不存在：" << filename << "，将创建新文件。" << endl;
        return true;
    }

    cout << "正在加载文件：" << filename << endl;

    string line;
    int lineCount = 0;
    int successCount = 0;

    while (getline(infile, line)) {
        lineCount++;
        if (line.empty()) continue;

        size_t colonPos = line.find(':');
        if (colonPos == string::npos) {
            cout << "格式错误（缺少冒号）: " << line << endl;
            continue;
        }

        string type = line.substr(0, colonPos);
        string data = line.substr(colonPos + 1);

        size_t commaPos = data.find(',');
        if (commaPos == string::npos) {
            cout << "格式错误（缺少逗号）: " << line << endl;
            continue;
        }

        string dateStr = data.substr(0, commaPos);
        Time date(dateStr);
        string restData = data.substr(commaPos + 1);

        if (type == "DIET") {
            int calorie, quantity;
            double carbs, protein, fat;
            stringstream ds(restData);
            ds >> calorie; ds.ignore();
            ds >> carbs; ds.ignore();
            ds >> protein; ds.ignore();
            ds >> fat; ds.ignore();
            ds >> quantity;

            Diet* diet = new Diet(date, user, calorie, carbs, protein, fat);
            diet->calculateQuantity();  // 重要：计算评分
            user.addRecord(diet);
            successCount++;
        }
        else if (type == "SPORT") {
            int minutes, calorie, quality;
            stringstream ds(restData);
            ds >> minutes; ds.ignore();
            ds >> calorie; ds.ignore();
            ds >> quality;

            Sport* sport = new Sport(date, user, minutes, calorie);
            sport->calculateQuality();  // 重要：计算评分
            user.addRecord(sport);
            successCount++;
        }
        else if (type == "SLEEP") {
            int hour, quality, sol, wakeTimes;
            stringstream ds(restData);
            ds >> hour; ds.ignore();
            ds >> quality; ds.ignore();
            ds >> sol; ds.ignore();
            ds >> wakeTimes;

            Sleep* sleep = new Sleep(date, user, hour, quality, sol, wakeTimes);
            user.addRecord(sleep);
            successCount++;
        }
        else if (type == "VITAL_SIGNS") {
            double temp, glucose, lipid, oxygen;
            int sys, dia, hr;
            stringstream ds(restData);
            ds >> temp; ds.ignore();
            ds >> sys; ds.ignore();
            ds >> dia; ds.ignore();
            ds >> glucose; ds.ignore();
            ds >> hr; ds.ignore();
            ds >> lipid; ds.ignore();
            ds >> oxygen;

            VitalSigns* vs = new VitalSigns(date, user, temp, sys, dia, glucose, hr, lipid, oxygen);
            user.addRecord(vs);
            successCount++;
        }
        else if (type == "LIFESTYLE") {
            int steps, sitTime, eyeTime, stress, mood;
            double water;
            stringstream ds(restData);
            ds >> steps; ds.ignore();
            ds >> water; ds.ignore();
            ds >> sitTime; ds.ignore();
            ds >> eyeTime; ds.ignore();
            ds >> stress; ds.ignore();
            ds >> mood;

            LifeStyle* ls = new LifeStyle(date, user, steps, water, sitTime, eyeTime, stress, mood);
            ls->calculateQuality();
            user.addRecord(ls);
            successCount++;
        }
        else {
            cout << "未知类型: " << type << endl;
        }
    }

    infile.close();
    cout << "加载完成：共读取 " << lineCount << " 行，成功加载 " << successCount << " 条记录。" << endl;

    return true;
}

bool FileManager::save(User& user) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "无法保存文件: " << filename << endl;
        return false;
    }

    int saveCount = 0;
    for (auto record : user.getRecords()) {
        outfile << record->getSaveString() << endl;
        saveCount++;
    }

    outfile.close();
    cout << "保存完成：共保存 " << saveCount << " 条记录到 " << filename << endl;
    return true;
}