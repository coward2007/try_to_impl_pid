#include "pid.hpp"

float PID::update(float setpoint, float measurement, float dt) {
    float error = setpoint - measurement;
    integral_ += error * dt;
    float devivative = (error- prev_error_) / dt;
    float output = config_.Kp  * error + config_.Ki * integral_ + config_.Kd * devivative;
    prev_error_ =error;
    return output; 


}
