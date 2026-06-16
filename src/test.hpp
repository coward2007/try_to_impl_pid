#include "pid.hpp"
#include <cmath>
#include <vector>
#include "../pid_testing_and_visualization/pid_test_utils.hpp"

inline void testPID(pid_config cfg) {

    PID pid(cfg);

    // --- 目标位置 (rad) ---
    float setpoint = 50.0f;
    float measurement = 0.0f;  // 角度位置 (rad)
    float velocity = 0.0f;      // 角速度 (rad/s)
    float dt = 0.001f;          // 1ms 仿真步长
    int steps = 100;           // 1s 总时长

    // ====== FAULHABER 1516T012SR 真实参数 ======
    // 来源: https://www.faulhaber.com/en/products/series/1516...sr/
    // 15mm 有刷直流微电机, 稀有金属换向, 12V 额定
    constexpr float R   = 60.5f;       // 端电阻 (Ω)
    constexpr float L   = 406e-6f;     // 电枢电感 (H)
    constexpr float Kt  = 0.00833f;    // 转矩常数 (N·m/A)  [datasheet: 8.33 mNm/A]
    constexpr float Ke  = 0.00833f;    // 反电动势常数 (V·s/rad), SI 下 = Kt
    constexpr float J   = 0.4e-7f;     // 转子惯量 (kg·m²)  [datasheet: 0.4 g·cm²]
    constexpr float V_bus = 12.0f;     // 母线电压 (V)      [datasheet: UN = 12V]
    constexpr float I_max = 0.25f;     // 最大电枢电流 (A)  [datasheet: Istall ≈ 0.2A]
    // 粘性摩擦系数 B 由空载数据反推:
    //   I0 = 14.5mA → T_no_load = Kt*I0 = 0.12mNm
    //   B = T_no_load / ω0 = 0.12e-3 / 1340 = 9.0e-8 N·m·s/rad
    constexpr float B   = 9.0e-8f;     // 粘性摩擦 (N·m·s/rad)
    // 库仑(静)摩擦力矩 ≈ 空载转矩 (data sheet 未直接给出, 按 I0 估算)
    constexpr float Fc  = 1.2e-4f;     // 库仑摩擦 (N·m)
    constexpr float electrical_tau = L / R;  // ≈ 6.7µs, 远小于机械时间常数

    // 收集仿真数据（从初始值开始）
    std::vector<float> step_vec;
    std::vector<float> setpoint_vec;
    std::vector<float> measurement_vec;
    std::vector<float> output_vec;

    step_vec.push_back(0.0f);
    setpoint_vec.push_back(setpoint);
    measurement_vec.push_back(measurement);
    output_vec.push_back(0.0f);

    for (int i = 0; i < steps; ++i) {
        float output = pid.update(setpoint, measurement, dt);

        // ============ FAULHABER 1516T012SR 物理模型 ============
        //   1. 电压限幅 (母线电压)
        float voltage = std::clamp(output, -V_bus, V_bus);
        //   2. 电枢回路: V = R·i + L·di/dt + Ke·ω
        //      忽略电气动态 (τ_elec ≈ 6.7µs << τ_mech ≈ 35ms)
        float back_emf = Ke * velocity;
        float current = std::clamp((voltage - back_emf) / R, -I_max, I_max);
        //   3. 电磁转矩
        float torque_em = Kt * current;
        //   4. 库仑摩擦 (与速度反向)
        float torque_coulomb = velocity != 0.0f
            ? std::copysign(Fc, velocity) : 0.0f;
        //   5. 运动方程: J·dω/dt = T_em - B·ω - T_coulomb
        float net_torque = torque_em - B * velocity - torque_coulomb;
        velocity += net_torque / J * dt;
        //   6. 位置积分
        measurement += velocity * dt;

        step_vec.push_back(static_cast<float>(i + 1));
        setpoint_vec.push_back(setpoint);
        measurement_vec.push_back(measurement);
        output_vec.push_back(output);

        // 提前收敛判断
        if (std::fabs(setpoint - measurement) < 0.001f && std::fabs(velocity) < 0.01f) {
            break;
        }
    }

    float final_error = std::fabs(setpoint - measurement);

    // 生成图表 HTML
    generatePlotHTML(step_vec, setpoint_vec, measurement_vec, output_vec,
                     cfg.Kp, cfg.Ki, cfg.Kd, final_error);

    // setConfig 测试
    pid_config cfg2;
    cfg2.Kp = 5.0f;
    cfg2.Ki = 0.0f;
    cfg2.Kd = 0.0f;

    pid.setConfig(cfg2);
    float test_out = pid.update(setpoint, measurement, dt);
}