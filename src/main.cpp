#include "pid.hpp"
#include "test.hpp"
#include "../pid_testing_and_visualization/pid_test_utils.hpp"

pid_config cfg{
    // PID 参数 (可调)
    2.0f,   // 比例系数 Kp
    0.0f,   // 积分系数 Ki
    4.2f    // 微分系数 Kd
};

int main() {
    testPID(cfg);
    return 0;
}