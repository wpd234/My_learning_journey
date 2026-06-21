#pragma once
#include "RecordBase.h"

class VitalSigns : public RecordBase {
private:
    double temperature;
    int sysBP;
    int diaBP;
    int heartRate;
    double glucose;
    double bloodLipid;
    double bloodOxygen;

    bool isTempAbnormal() const;
    bool isBPAbnormal() const;
    bool isGlucoseAbnormal() const;
    bool isHeartRateAbnormal() const;
    bool isBloodLipidAbnormal() const;
    bool isBloodOxygenAbnormal() const;

    int calculateScore() const;  // 私有方法，计算生命体征评分

public:
    VitalSigns(Time t, User& u, double temp, int sys, int dia, double glu, int hr, double lipid, double oxygen);

    bool isAbnormal() const;
    void showWarning() const;
    void show() const override;
    string getSaveString() const override;
    int getScore() const override { return calculateScore(); }

    // getter方法
    double getTemperature() const { return temperature; }
    int getSysBP() const { return sysBP; }
    int getDiaBP() const { return diaBP; }
    double getGlucose() const { return glucose; }
    int getHeartRate() const { return heartRate; }
    double getBloodOxygen() const { return bloodOxygen; }
};