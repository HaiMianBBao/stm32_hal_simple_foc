#include <SimpleFOC.h>
#include "Commander.h"
#include "SerialUart.h"
#include "gpio.h"
#include "main.h"

// magnetic sensor instance - SPI
// MagneticSensorSPI sensor = MagneticSensorSPI(AS5147_SPI, 10);
// magnetic sensor instance - MagneticSensorI2C
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
// magnetic sensor instance - analog output
// MagneticSensorAnalog sensor = MagneticSensorAnalog(A1, 14, 1020);

// BLDC motor & driver instance
// BLDCMotor motor = BLDCMotor(pole pair number);
BLDCMotor motor = BLDCMotor(11);
// BLDCDriver3PWM driver = BLDCDriver3PWM(pwmA, pwmB, pwmC, Enable(optional));
BLDCDriver3PWM driver = BLDCDriver3PWM(A0, A1, A2, A3);

float target_position = 0;
float target_velocity = 0;
Commander command = Commander(Serial);

void doTarget(char *cmd)
{
    Serial.printf("doTarget ");
    command.scalar(&target_velocity, cmd);
}

void doLimit(char *cmd)
{
    Serial.printf("doLimit ");
    command.scalar(&motor.voltage_limit, cmd);
}

void doVelocity(char *cmd)
{
    Serial.printf("doVelocity ");
    command.scalar(&motor.velocity_limit, cmd);
}

void uart_rev_cb(void)
{
    /*!< Do nothing */
}

void setup(void)
{
    Serial.begin(115200);

    // initialise magnetic sensor hardware
    sensor.init();
    // link the motor to the sensor
    motor.linkSensor(&sensor);

    // driver config
    // power supply voltage [V]
    driver.voltage_power_supply = 12;
    // limit the maximal dc voltage the driver can set
    // as a protection measure for the low-resistance motors
    // this value is fixed on startup
    driver.voltage_limit = 6;
    driver.init();
    // link the motor and the driver
    motor.linkDriver(&driver);

    // set motion control loop to be used
    motor.controller = MotionControlType::velocity;

    // contoller configuration
    // default parameters in defaults.h

    // velocity PI controller parameters
    motor.PID_velocity.P = 0.2f;
    motor.PID_velocity.I = 20;
    motor.PID_velocity.D = 0;
    // default voltage_power_supply
    motor.voltage_limit = 6;
    // jerk control using voltage voltage ramp
    // default value is 300 volts per sec  ~ 0.3V per millisecond
    motor.PID_velocity.output_ramp = 1000;

    // velocity low pass filtering
    // default 5ms - try different values to see what is the best.
    // the lower the less filtered
    motor.LPF_velocity.Tf = 0.01f;

    motor.useMonitoring(Serial);
    // init motor hardware
    motor.init();

    // align sensor and start FOC
    motor.initFOC();

    command.add('T', doTarget, "target angle");
    command.add('L', doLimit, "voltage limit");
    command.add('V', doVelocity, "movement velocity");
    // Serial.attachInterrupt(uart_rev_cb);

    Serial.println(F("Motor ready."));
    Serial.println(F("Set the target velocity using serial terminal:"));
    _delay(1000);
}

void loop(void)
{
    while (1) {
        // main FOC algorithm function
        // the faster you run this function the better
        // Arduino UNO loop  ~1kHz
        // Bluepill loop ~10kHz
        motor.loopFOC();

        // Motion control function
        // velocity, position or voltage (defined in motor.controller)
        // this function can be run at much lower frequency than loopFOC() function
        // You can also use motor.move() and set the motor.target in the code
        motor.move(target_velocity);

        // function intended to be used with serial plotter to monitor motor variables
        // significantly slowing the execution down!!!!
        motor.monitor();

        // user communication
        command.run();
    }
}