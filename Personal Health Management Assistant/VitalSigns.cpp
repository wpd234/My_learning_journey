#include "VitalSigns.h"
#include "User.h"           // 添加
#include <iostream>
#include <cmath>
using namespace std;
VitalSigns::VitalSigns(Time t, User& u, double temp, int sys, int dia, double glu, int hr, double lipid, double oxygen) : RecordBase(u, t) {
	temperature = temp;
	sysBP = sys;
	diaBP = dia;
	glucose = glu;
	heartRate = hr;
	bloodLipid = lipid;
	bloodOxygen = oxygen;
	type = "VitalSigns";
}

bool VitalSigns::isTempAbnormal() const {
	return temperature < 36.0 || temperature > 37.5;
}

bool VitalSigns::isBPAbnormal() const {
	return sysBP < 90 || sysBP > 140 || diaBP < 60 || diaBP > 90;
}

bool VitalSigns::isGlucoseAbnormal() const {
	return glucose < 3.9 || glucose > 6.1;
}

bool VitalSigns::isAbnormal() const {
	return isTempAbnormal() || isBPAbnormal() || isGlucoseAbnormal() || isHeartRateAbnormal() || isBloodLipidAbnormal() || isBloodOxygenAbnormal();
}

bool VitalSigns::isHeartRateAbnormal() const {
	return heartRate < 40 || heartRate > 220;
}

bool VitalSigns::isBloodLipidAbnormal() const {
	return bloodLipid < 0 || bloodLipid > 5.2;
}
bool VitalSigns::isBloodOxygenAbnormal() const {
	return bloodOxygen < 95 || bloodOxygen > 100;
}

void VitalSigns::showWarning() const {
	if (isTempAbnormal()) {
		cout << "体温异常: " << temperature << "°C" << endl;
	}
	if (isBPAbnormal()) {
		cout << "血压异常: " << sysBP << "/" << diaBP << " mmHg" << endl;
	}
	if (isGlucoseAbnormal()) {
		cout << "血糖异常: " << glucose << " mmol/L" << endl;
	}
	if (isHeartRateAbnormal()) {
		cout << "心率异常: " << heartRate << " 次/分" << endl;
	}
	if (isBloodLipidAbnormal()) {
		cout << "血脂异常: " << bloodLipid << " mmol/L" << endl;
	}
	if (isBloodOxygenAbnormal()) {
		cout << "血氧异常: " << bloodOxygen << " %" << endl;
	}
}

void VitalSigns::show() const {
	cout << "体温: " << temperature << "°C ";
	cout << "血压: " << sysBP << "/" << diaBP << " mmHg ";
	cout << "血糖: " << glucose << " mmol/L ";
	cout << "心率: " << heartRate << " 次/分 ";
	cout << "血脂: " << bloodLipid << " mmol/L ";
	cout << "血氧: " << bloodOxygen << " %" << endl;
}

string VitalSigns::getSaveString() const {
	return "VITAL_SIGNS:" + Date.toString() + "," + to_string(temperature) + "," +
		to_string(sysBP) + "," + to_string(diaBP) + "," +
		to_string(glucose) + "," + to_string(heartRate) + "," +
		to_string(bloodLipid) + "," + to_string(bloodOxygen);
}

int VitalSigns::calculateScore() const {
    double score = 10.0;

    // 体温评分（36.0-37.2为正常）
    if (temperature < 35.5) score -= 3.0;
    else if (temperature < 36.0) score -= 1.5;
    else if (temperature > 37.5) score -= 1.5;
    else if (temperature > 37.2) score -= 0.5;

    // 血压评分
    // 理想血压：<120/80
    // 正常高值：120-139/80-89
    if (sysBP >= 140) score -= 2.0;
    else if (sysBP >= 130) score -= 1.0;
    else if (sysBP >= 120) score -= 0.5;

    if (diaBP >= 90) score -= 2.0;
    else if (diaBP >= 85) score -= 1.0;
    else if (diaBP >= 80) score -= 0.5;

    // 血糖评分（空腹：3.9-6.1为正常）
    if (glucose < 3.0) score -= 3.0;
    else if (glucose < 3.5) score -= 2.0;
    else if (glucose < 3.9) score -= 1.0;
    else if (glucose > 7.0) score -= 2.0;
    else if (glucose > 6.1) score -= 1.0;

    // 心率评分（静息：60-100为正常，运动员可更低）
    if (heartRate < 50) score -= 0.5;
    else if (heartRate < 60) score -= 0.0;  // 稍慢但可能正常
    else if (heartRate > 100) score -= 1.0;
    else if (heartRate > 90) score -= 0.5;

    // 血氧评分（95-100为正常）
    if (bloodOxygen < 90) score -= 3.0;
    else if (bloodOxygen < 92) score -= 2.0;
    else if (bloodOxygen < 94) score -= 1.0;
    else if (bloodOxygen < 95) score -= 0.5;

    // 血脂评分（总胆固醇理想值<5.2）
    if (bloodLipid > 6.2) score -= 2.0;
    else if (bloodLipid > 5.2) score -= 1.0;

    if (score < 1) score = 1;
    if (score > 10) score = 10;
    return (int)round(score);
}