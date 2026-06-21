#include "LifeStyle.h"
#include <iostream>
using namespace std;

LifeStyle::LifeStyle(Time t, User& u,int steps_, double water_, int sitTime_, int eyeTime_, int stress_, int mood_) : RecordBase(u, t), 
steps(steps_), water(water_), sitTime(sitTime_), eyeTime(eyeTime_), stress(stress_), mood(mood_) {
	type = "LIFESTYLE";
}

bool LifeStyle::stepsabnormal() const {
	return steps < 3000;
}

bool LifeStyle::waterabnormal() const {
	return water < 1.5;
}

bool LifeStyle::sitTimeabnormal() const {
	return sitTime > 8;
}

bool LifeStyle::eyeTimeabnormal() const {
	return eyeTime > 8;
}

bool LifeStyle::stressabnormal() const {
	return stress > 7;
}

bool LifeStyle::moodabnormal() const {
	return mood < 3;
}

bool LifeStyle::isAbnormal() const {
	return stepsabnormal() || waterabnormal() || sitTimeabnormal() || eyeTimeabnormal() || stressabnormal() || moodabnormal();
}

void LifeStyle::show() const {
	cout << "步数: " << steps << "步 ";
	cout << "饮水量: " << water << "升 ";
	cout << "久坐时间: " << sitTime << "小时 ";
	cout << "用眼时间: " << eyeTime << "小时 ";
	cout << "压力水平: " << stress << "/10 ";
	cout << "心情指数: " << mood << "/10" << endl;
}

void LifeStyle::showWarning() const {
	if (stepsabnormal()) {
		cout << "步数过少: " << steps << "步" << endl;
	}
	if (waterabnormal()) {
		cout << "饮水量不足: " << water << "升" << endl;
	}
	if (sitTimeabnormal()) {
		cout << "久坐时间过长: " << sitTime << "小时" << endl;
	}
	if (eyeTimeabnormal()) {
		cout << "用眼时间过长: " << eyeTime << "小时" << endl;
	}
	if (stressabnormal()) {
		cout << "压力水平过高: " << stress << "/10" << endl;
	}
	if (moodabnormal()) {
		cout << "心情指数过低: " << mood << "/10" << endl;
	}
}

string LifeStyle::getSaveString() const {
	return "LIFESTYLE:" + Date.toString() + "," + to_string(steps) + "," +
		to_string(water) + "," + to_string(sitTime) + "," +
		to_string(eyeTime) + "," + to_string(stress) + "," + to_string(mood);
}

void LifeStyle::calculateQuality() {
    int score = 5; 

    if (steps >= 10000) score += 3;
    else if (steps >= 8000) score += 2;
    else if (steps >= 6000) score += 1;
    else if (steps < 3000) score -= 2;
    else if (steps < 5000) score -= 1;

    if (water >= 2.0) score += 2;
    else if (water >= 1.5) score += 1;
    else if (water < 1.0) score -= 1;

    if (sitTime <= 4) score += 2;
    else if (sitTime <= 6) score += 1;
    else if (sitTime > 10) score -= 1;

    if (eyeTime <= 4) score += 2;
    else if (eyeTime <= 6) score += 1;
    else if (eyeTime > 10) score -= 1;

    if (stress <= 3) score += 1;
    else if (stress >= 8) score -= 1;

    if (mood >= 8) score += 1;
    else if (mood <= 3) score -= 1;

    if (score < 1) score = 1;
    if (score > 10) score = 10;

    quality = score;
}