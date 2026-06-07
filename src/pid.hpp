#pragma once

#include <algorithm>
#include <cmath>

struct pid_config {
    float Kp;            // 比例系数
    float Ki;            // 积分系数
    float Kd;            // 微分系数
};

class PID {
public:
    PID(const pid_config& config)
        : config_(config), prev_error_(0.0f), integral_(0.0f) {}

    void setConfig(const pid_config& config) {
        config_ = config;
    }

    float update(float setpoint, float measurement, float dt = 0.01f);

private:
    pid_config config_;
    float prev_error_;
    float integral_;
};
