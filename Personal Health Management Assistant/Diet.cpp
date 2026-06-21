#include "Diet.h"
#include "User.h"
#include "DataValidator.h"
#include <iostream>
#include <cmath>
using namespace std;

Diet::Diet(Time t, User& u, int cal, double carbs, double protein, double fat) : RecordBase(u, t) {
    string errorMsg;
    if (DataValidator::validateCalories(cal, errorMsg))
        calorie = cal;
    if (DataValidator::validateCarbs(carbs, errorMsg))
        this->carbs = carbs;
    if (DataValidator::validateProtein(protein, errorMsg))
        this->protein = protein;
    if (DataValidator::validateFat(fat, errorMsg))
        this->fat = fat;
    type = "Diet";
    quantity = 0;  
}

void Diet::show() const {
    cout << "热量: " << calorie << "千卡 ";
    cout << "碳水化合物: " << carbs << "克 ";
    cout << "蛋白质: " << protein << "克 ";
    cout << "脂肪: " << fat << "克 ";
    cout << "饮食质量: " << quantity << "/10 " << endl;
}

string Diet::getSaveString() const {
    return "DIET:" + Date.toString() + "," + to_string(calorie) + "," +
        to_string(carbs) + "," + to_string(protein) + "," +
        to_string(fat) + "," + to_string(quantity);
}

void Diet::calculateQuantity() {
    // 根据《中国居民膳食指南》成年人每日能量需要量
    int target = 0;
    if (user.getSex() == 'f') {
        if (user.getWeight() < 50) target = 1600;
        else if (user.getWeight() <= 60) target = 1800;
        else if (user.getWeight() <= 70) target = 2000;
        else target = 2200;
    }
    else {
        if (user.getWeight() < 60) target = 2000;
        else if (user.getWeight() <= 70) target = 2200;
        else if (user.getWeight() <= 80) target = 2400;
        else target = 2600;
    }

    // 热量评分
    double calScore = 0.0;
    int deviation = abs(calorie - target);
    if (deviation <= 100) calScore = 10.0;
    else if (deviation <= 200) calScore = 9.0;
    else if (deviation <= 300) calScore = 8.0;
    else if (deviation <= 400) calScore = 7.0;
    else if (deviation <= 500) calScore = 6.0;
    else if (deviation <= 700) calScore = 5.0;
    else if (deviation <= 900) calScore = 4.0;
    else calScore = max(1.0, 10.0 - deviation / 200.0);

    // 营养均衡评分
    double total = carbs * 4 + protein * 4 + fat * 9;
    if (total <= 0) {
        quantity = (int)round(calScore);
        if (quantity < 1) quantity = 1;
        if (quantity > 10) quantity = 10;
        return;
    }

    double cRatio = carbs * 4 / total * 100;
    double pRatio = protein * 4 / total * 100;
    double fRatio = fat * 9 / total * 100;

    double nutScore = 0.0;
    if (cRatio >= 50 && cRatio <= 65) nutScore += 3.0;
    else if (cRatio >= 45 && cRatio <= 70) nutScore += 2.0;
    else if (cRatio >= 40 && cRatio <= 75) nutScore += 1.0;

    if (pRatio >= 10 && pRatio <= 20) nutScore += 3.0;
    else if (pRatio >= 8 && pRatio <= 25) nutScore += 2.0;
    else if (pRatio >= 6 && pRatio <= 30) nutScore += 1.0;

    if (fRatio >= 20 && fRatio <= 30) nutScore += 3.0;
    else if (fRatio >= 15 && fRatio <= 35) nutScore += 2.0;
    else if (fRatio >= 10 && fRatio <= 40) nutScore += 1.0;

    double totalScore = calScore * 0.6 + nutScore;

    quantity = (int)round(totalScore);
    if (quantity < 1) quantity = 1;
    if (quantity > 10) quantity = 10;
}