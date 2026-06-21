#pragma once
#include "RecordBase.h"
#include <string>
using namespace std;

class Diet : public RecordBase {
private:
    int calorie;
    double carbs;
    double protein;
    double fat;
    int quantity;
public:
    Diet(Time t, User& u, int cal, double carbs, double protein, double fat);
    void show() const override;
    string getSaveString() const override;
    void calculateQuantity();
    int getScore() const override { return quantity; }
    int getQuantity() const { return quantity; }
	int getCalorie() const { return calorie; }
};