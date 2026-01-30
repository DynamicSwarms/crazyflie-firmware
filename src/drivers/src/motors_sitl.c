/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2011-2024 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * motors_sitl.c - SITL (Software-In-The-Loop) motor driver
 *
 * This is a minimal motor implementation for SITL that tracks motor PWM values
 * and sends them to the Gazebo simulator via CRTP packets.
 */

#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "motors.h"
#include "config.h"
#include "crtp.h"
#include "cfassert.h"

static bool isInit = false;
static uint16_t motor_ratios[NBR_OF_MOTORS] = {0, 0, 0, 0};

// CRTP packet for sending motor commands to simulator
static uint32_t lastSentTime = 0;
static CRTPPacket sitlMotorPacket;

// Test sound tones (same as motors.c but unused in SITL)
const uint16_t testsound[NBR_OF_MOTORS] = {440, 880, 698, 587}; // A4, A5, F5, D5

void motorsInit(const MotorPerifDef** motorMapSelect) {
  (void)motorMapSelect;

  // Initialize motor ratios
  for (int i = 0; i < NBR_OF_MOTORS; i++) {
    motor_ratios[i] = 0;
  }

  // Initialize CRTP packet for sending to simulator
  lastSentTime = xTaskGetTickCount();
  sitlMotorPacket.size = 4 * sizeof(uint16_t);
  sitlMotorPacket.header = CRTP_HEADER(CRTP_PORT_SETPOINT_SIM, 0);

  isInit = true;
}

void motorsDeInit(const MotorPerifDef** motorMapSelect) {
  (void)motorMapSelect;
  isInit = false;
}

void motorsSetRatio(uint32_t id, uint16_t ratio) {
  ASSERT(id < NBR_OF_MOTORS);

  if (isInit) {
    motor_ratios[id] = ratio;
  }
}

void sendMotorPacketsSITL(void) {
  if (isInit) {
    if (xTaskGetTickCount() - lastSentTime >= M2T(1)) {
      memcpy(sitlMotorPacket.data, (uint8_t*)motor_ratios, sitlMotorPacket.size);
      crtpSendPacket(&sitlMotorPacket);
      lastSentTime = xTaskGetTickCount();
    }
  }
}

uint16_t motorsGetRatio(uint32_t id) {
  ASSERT(id < NBR_OF_MOTORS);

  return motor_ratios[id];
}

// Stub implementations for other motor API functions
bool motorsTest(void) {
  return true;
}

void motorsStop(void) {
  for (int i = 0; i < NBR_OF_MOTORS; i++) {
    motor_ratios[i] = 0;
  }
}

void motorsEnablePWM(void) {
  // No-op for SITL
}

void motorsDisablePWM(void) {
  // No-op for SITL
}

void motorsBeep(int id, bool enable, uint16_t frequency, uint16_t ratio) {
  (void)id;
  (void)enable;
  (void)frequency;
  (void)ratio;
  // No-op for SITL
}

const MotorHealthTestDef* motorsGetHealthTestSettings(uint32_t id) {
  (void)id;
  return NULL;
}

float motorsCompensateBatteryVoltage(uint32_t id, float iThrust, float supplyVoltage) {
  (void)id;
  (void)supplyVoltage;
  return iThrust;
}

void motorsBurstDshot(void) {
  // No-op for SITL
}

// Additional stub functions that may be needed
void motorsEnablePassthough(uint32_t id) {
  (void)id;
  // No-op for SITL
}

void motorsESCSetInput(uint32_t id) {
  (void)id;
  // No-op for SITL
}

void motorsESCSetOutput(uint32_t id) {
  (void)id;
  // No-op for SITL
}

void motorsESCSetHi(uint32_t id) {
  (void)id;
  // No-op for SITL
}

void motorsESCSetLo(uint32_t id) {
  (void)id;
  // No-op for SITL
}

int motorsESCIsHi(uint32_t id) {
  (void)id;
  return 0;
}

int motorsESCIsLo(uint32_t id) {
  (void)id;
  return 0;
}

void motorsTestTask(void* params) {
  (void)params;
  // No-op for SITL
}
