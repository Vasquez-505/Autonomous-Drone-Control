/*
 * flightControlSystem_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "flightControlSystem".
 *
 * Model version              : 11.23
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Fri Jun  5 16:39:54 2026
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM 9
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef flightControlSystem_private_h_
#define flightControlSystem_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#include "flightControlSystem.h"
#include "flightControlSystem_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

/* Imported (extern) pointer block signals */
extern uint8_T *imRGB;                 /* '<Root>/Image Data' */
extern void flightControlSystem_MeasurementUpdate_Init
  (B_MeasurementUpdate_flightControlSystem_T *localB,
   P_MeasurementUpdate_flightControlSystem_T *localP);
extern void flightControlSystem_MeasurementUpdate_Start
  (DW_MeasurementUpdate_flightControlSystem_T *localDW);
extern void flightControlSystem_MeasurementUpdate_Disable
  (B_MeasurementUpdate_flightControlSystem_T *localB,
   DW_MeasurementUpdate_flightControlSystem_T *localDW,
   P_MeasurementUpdate_flightControlSystem_T *localP);
extern void flightControlSystem_MeasurementUpdate(boolean_T rtu_Enable, const
  real32_T rtu_Lk[4], const real32_T rtu_yk[2], const real32_T rtu_Ck[4], const
  real32_T rtu_xhatkk1[2], const real32_T rtu_Dk[2], real32_T rtu_uk,
  B_MeasurementUpdate_flightControlSystem_T *localB,
  DW_MeasurementUpdate_flightControlSystem_T *localDW,
  P_MeasurementUpdate_flightControlSystem_T *localP);
extern void flightControlSystem_EnabledSubsystem_Init
  (B_EnabledSubsystem_flightControlSystem_T *localB,
   P_EnabledSubsystem_flightControlSystem_T *localP);
extern void flightControlSystem_EnabledSubsystem_Start
  (DW_EnabledSubsystem_flightControlSystem_T *localDW);
extern void flightControlSystem_EnabledSubsystem_Disable
  (B_EnabledSubsystem_flightControlSystem_T *localB,
   DW_EnabledSubsystem_flightControlSystem_T *localDW,
   P_EnabledSubsystem_flightControlSystem_T *localP);
extern void flightControlSystem_EnabledSubsystem(boolean_T rtu_Enable, const
  real32_T rtu_Mk[4], const real32_T rtu_Ck[4], const real32_T rtu_yk[2], const
  real32_T rtu_xhatkk1[2], B_EnabledSubsystem_flightControlSystem_T *localB,
  DW_EnabledSubsystem_flightControlSystem_T *localDW,
  P_EnabledSubsystem_flightControlSystem_T *localP);
extern void flightControlSystem_MeasurementUpdate_f_Init
  (B_MeasurementUpdate_flightControlSystem_n_T *localB,
   P_MeasurementUpdate_flightControlSystem_o_T *localP);
extern void flightControlSystem_MeasurementUpdate_c_Start
  (DW_MeasurementUpdate_flightControlSystem_o_T *localDW);
extern void flightControlSystem_MeasurementUpdate_c_Disable
  (B_MeasurementUpdate_flightControlSystem_n_T *localB,
   DW_MeasurementUpdate_flightControlSystem_o_T *localDW,
   P_MeasurementUpdate_flightControlSystem_o_T *localP);
extern void flightControlSystem_MeasurementUpdate_j(boolean_T rtu_Enable, const
  real32_T rtu_Lk[16], const real32_T rtu_yk[4], const real32_T rtu_Ck[16],
  const real32_T rtu_xhatkk1[4], const real32_T rtu_Dk[4], real32_T rtu_uk,
  B_MeasurementUpdate_flightControlSystem_n_T *localB,
  DW_MeasurementUpdate_flightControlSystem_o_T *localDW,
  P_MeasurementUpdate_flightControlSystem_o_T *localP);
extern void flightControlSystem_EnabledSubsystem_d_Init
  (B_EnabledSubsystem_flightControlSystem_g_T *localB,
   P_EnabledSubsystem_flightControlSystem_i_T *localP);
extern void flightControlSystem_EnabledSubsystem_h_Start
  (DW_EnabledSubsystem_flightControlSystem_b_T *localDW);
extern void flightControlSystem_EnabledSubsystem_n_Disable
  (B_EnabledSubsystem_flightControlSystem_g_T *localB,
   DW_EnabledSubsystem_flightControlSystem_b_T *localDW,
   P_EnabledSubsystem_flightControlSystem_i_T *localP);
extern void flightControlSystem_EnabledSubsystem_e(boolean_T rtu_Enable, const
  real32_T rtu_Mk[16], const real32_T rtu_Ck[16], const real32_T rtu_yk[4],
  const real32_T rtu_xhatkk1[4], B_EnabledSubsystem_flightControlSystem_g_T
  *localB, DW_EnabledSubsystem_flightControlSystem_b_T *localDW,
  P_EnabledSubsystem_flightControlSystem_i_T *localP);
extern void flightControlSystem_Geofencingerror(uint8_T *rty_Out1,
  P_Geofencingerror_flightControlSystem_T *localP);
extern void flightControlSystem_MeasurementUpdate_e_Init
  (B_MeasurementUpdate_flightControlSystem_k_T *localB,
   P_MeasurementUpdate_flightControlSystem_i_T *localP);
extern void flightControlSystem_MeasurementUpdate_h_Start
  (DW_MeasurementUpdate_flightControlSystem_c_T *localDW);
extern void flightControlSystem_MeasurementUpdate_k_Disable
  (B_MeasurementUpdate_flightControlSystem_k_T *localB,
   DW_MeasurementUpdate_flightControlSystem_c_T *localDW,
   P_MeasurementUpdate_flightControlSystem_i_T *localP);
extern void flightControlSystem_MeasurementUpdate_o(boolean_T rtu_Enable, const
  real32_T rtu_Lk[2], real32_T rtu_yk, const real32_T rtu_Ck[2], const real32_T
  rtu_xhatkk1[2], real32_T rtu_Dk, real32_T rtu_uk,
  B_MeasurementUpdate_flightControlSystem_k_T *localB,
  DW_MeasurementUpdate_flightControlSystem_c_T *localDW,
  P_MeasurementUpdate_flightControlSystem_i_T *localP);
extern void flightControlSystem_EnabledSubsystem_c_Init
  (B_EnabledSubsystem_flightControlSystem_c_T *localB,
   P_EnabledSubsystem_flightControlSystem_g_T *localP);
extern void flightControlSystem_EnabledSubsystem_o_Start
  (DW_EnabledSubsystem_flightControlSystem_o_T *localDW);
extern void flightControlSystem_EnabledSubsystem_g_Disable
  (B_EnabledSubsystem_flightControlSystem_c_T *localB,
   DW_EnabledSubsystem_flightControlSystem_o_T *localDW,
   P_EnabledSubsystem_flightControlSystem_g_T *localP);
extern void flightControlSystem_EnabledSubsystem_k(boolean_T rtu_Enable, const
  real32_T rtu_Mk[2], const real32_T rtu_Ck[2], real32_T rtu_yk, const real32_T
  rtu_xhatkk1[2], B_EnabledSubsystem_flightControlSystem_c_T *localB,
  DW_EnabledSubsystem_flightControlSystem_o_T *localDW,
  P_EnabledSubsystem_flightControlSystem_g_T *localP);
extern void flightControlSystem_FlightControlSystem_SetupRTR
  (RT_MODEL_flightControlSystem_T * const flightControlSystem_M,
   DW_FlightControlSystem_flightControlSystem_T *localDW);
extern void flightControlSystem_FlightControlSystem_Init
  (B_FlightControlSystem_flightControlSystem_T *localB,
   DW_FlightControlSystem_flightControlSystem_T *localDW,
   P_FlightControlSystem_flightControlSystem_T *localP,
   ZCE_FlightControlSystem_flightControlSystem_T *localZCE);
extern void flightControlSystem_FlightControlSystem_Start
  (DW_FlightControlSystem_flightControlSystem_T *localDW);
extern void flightControlSystem_FlightControlSystem
  (RT_MODEL_flightControlSystem_T * const flightControlSystem_M, const
   CommandBus *rtu_ReferenceValueServerCmds, const SensorsBus *rtu_Sensors,
   B_FlightControlSystem_flightControlSystem_T *localB,
   DW_FlightControlSystem_flightControlSystem_T *localDW,
   P_FlightControlSystem_flightControlSystem_T *localP,
   ZCE_FlightControlSystem_flightControlSystem_T *localZCE);

#endif                                 /* flightControlSystem_private_h_ */
