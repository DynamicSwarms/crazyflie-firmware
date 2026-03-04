#include <stdint.h>
#include <stdbool.h>
#include "log.h"
#include "param.h"
#include "pm.h"

static bool isInit = false;
static float batteryVoltage = 4.2f;
static uint16_t batteryVoltageMV = 4200;
static float chargeCurrent = 0.0f;
static float batteryVoltageMin = 4.2f;
static float batteryVoltageMax = 4.2f;
static int8_t pmState = 0;
static uint8_t batteryLevel = 100;

// Limits (not used in SITL but provided for param system)
static float batteryCriticalLowVoltage = 3.0f;
static float batteryLowVoltage = 3.2f;

void pmInit(void)
{
  isInit = true;
}

bool pmTest(void)
{
  return isInit;
}

float pmGetBatteryVoltage(void)
{
  return batteryVoltage;
}

float pmGetBatteryVoltageMin(void)
{
  return batteryVoltageMin;
}

float pmGetBatteryVoltageMax(void)
{
  return batteryVoltageMax;
}

bool pmIsBatteryLow(void)
{
  return false;
}

bool pmIsChargerConnected(void)
{
  return false;
}

bool pmIsCharging(void)
{
  return false;
}

bool pmIsDischarging(void)
{
  return false;
}

void pmSetChargeState(PMChargeStates chgState)
{
  // No-op for SITL
}

void pmSyslinkUpdate(SyslinkPacket *slp)
{
  // No-op for SITL
}

void pmEnableExtBatteryVoltMeasuring(const deckPin_t pin, float multiplier)
{
  // No-op for SITL
}

float pmMeasureExtBatteryVoltage(void)
{
  return 0.0f;
}

void pmEnableExtBatteryCurrMeasuring(const deckPin_t pin, float ampPerVolt)
{
  // No-op for SITL
}

float pmMeasureExtBatteryCurrent(void)
{
  return 0.0f;
}

void pmIgnoreChargedState(bool ignore)
{
  // No-op for SITL
}

bool pmRegisterGracefulShutdownCallback(graceful_shutdown_callback_t cb)
{
  return true;
}

void pmTask(void *param)
{
  // No-op for SITL - task not created
}

LOG_GROUP_START(pm)
LOG_ADD_CORE(LOG_FLOAT, vbat, &batteryVoltage)
LOG_ADD(LOG_UINT16, vbatMV, &batteryVoltageMV)
LOG_ADD(LOG_FLOAT, chargeCurrent, &chargeCurrent)
LOG_ADD_CORE(LOG_INT8, state, &pmState)
LOG_ADD_CORE(LOG_UINT8, batteryLevel, &batteryLevel)
LOG_GROUP_STOP(pm)

PARAM_GROUP_START(pm)
PARAM_ADD_CORE(PARAM_FLOAT | PARAM_PERSISTENT, lowVoltage, &batteryLowVoltage)
PARAM_ADD_CORE(PARAM_FLOAT | PARAM_PERSISTENT, criticalLowVoltage, &batteryCriticalLowVoltage)
PARAM_GROUP_STOP(pm)
