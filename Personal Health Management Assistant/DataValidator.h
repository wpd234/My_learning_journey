#pragma once
#ifndef DATAVALIDATOR_H	
#define DATAVALIDATOR_H
#include<string>
#include<iostream>
using namespace std;

class DataValidator {
public:
    static bool validateCalories(double calories, string& errorMsg) {
        if (calories <= 0) {
            errorMsg = "热量必须大于0";
            return false;
        }
        if (calories > 5000) {
            errorMsg = "热量超过5000千卡，超出正常范围";
            return false;
        }
        return true;
    }

    static bool validateWeight(double weight, string& errorMsg) {
        if (weight < 20 || weight > 300) {
            errorMsg = "体重应在20-300kg之间";
            return false;
        }
        return true;
    }

    static bool validateHeight(double height, string& errorMsg) {
        if (height < 50 || height > 250) {
            errorMsg = "身高应在50-250cm之间";
            return false;
        }
        return true;
    }

    static bool validateAge(int age, string& errorMsg) {
        if (age < 0 || age > 150) {
            errorMsg = "年龄应在0-150岁之间";
            return false;
        }
        return true;
    }

    static bool validateBloodPressure(int systolic, int diastolic, string& errorMsg) {
        if (systolic < 50 || systolic > 250) {
            errorMsg = "收缩压应在50-250mmHg之间";
            return false;
        }
        if (diastolic < 30 || diastolic > 150) {
            errorMsg = "舒张压应在30-150mmHg之间";
            return false;
        }
        if (systolic <= diastolic) {
            errorMsg = "收缩压必须大于舒张压";
            return false;
        }
        return true;
    }

    static bool validateHeartRate(int heartRate, int age, string& errorMsg) {
        if (heartRate < 40 || heartRate > 220) {
            errorMsg = "心率应在40-220次/分之间";
            return false;
        }

        int maxRate = 220 - age;
        if (heartRate > maxRate * 1.2) {
            errorMsg = "心率超过最大心率的120%，数据可能错误";
            return false;
        }
        return true;
    }

    static bool validateSleepDuration(double hours, string& errorMsg) {
        if (hours < 0 || hours > 24) {
            errorMsg = "睡眠时长应在0-24小时之间";
            return false;
        }
        return true;
    }

    static bool validateDuration(int minutes, string& errorMsg) {
        if (minutes <= 0 || minutes > 1440) {
            errorMsg = "运动时长应在1-1440分钟之间";
            return false;
        }
        return true;
    }
    static bool validateQuality(int quality, string& errorMsg) {
        if (quality < 1 || quality > 10) {
            errorMsg = "睡眠质量应在1-10之间";
            return false;
        }
        return true;
	}

    static bool validateCarbs(double carbs, string& errorMsg) {
        if (carbs < 0 || carbs > 1000) {
            errorMsg = "碳水化合物摄入量应在0-1000克之间";
            return false;
        }
        return true;
    }
    static bool validateProtein(double protein, string& errorMsg) {
        if (protein < 0 || protein > 500) {
            errorMsg = "蛋白质摄入量应在0-500克之间";
            return false;
        }
        return true;
    }
    static bool validateFat(double fat, string& errorMsg) {
        if (fat < 0 || fat > 300) {
            errorMsg = "脂肪摄入量应在0-300克之间";
            return false;
        }
        return true;
	}
    static bool validateMinutes(int minutes, string& errorMsg) {
        if (minutes <= 0 || minutes > 1440) {
            errorMsg = "运动时长应在1-1440分钟之间";
            return false;
        }
        return true;
	}
};

#endif