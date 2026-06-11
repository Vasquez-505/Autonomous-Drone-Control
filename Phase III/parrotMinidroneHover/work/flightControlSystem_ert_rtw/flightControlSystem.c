/*
 * flightControlSystem.c
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

#include "flightControlSystem.h"
#include "rtwtypes.h"
#include "flightControlSystem_types.h"
#include "flightControlSystem_private.h"
#include <math.h>
#include "rt_nonfinite.h"
#include <string.h>
#include "zero_crossing_types.h"

/* Exported block signals */
CommandBus cmd_inport;                 /* '<Root>/AC cmd' */
SensorsBus sensor_inport;              /* '<Root>/Sensors' */
real32_T motors_outport[4];            /* '<Root>/Flight Control System' */
uint8_T flag_outport;                  /* '<Root>/Flight Control System' */

/* Block signals (default storage) */
B_flightControlSystem_T flightControlSystem_B;

/* Block states (default storage) */
DW_flightControlSystem_T flightControlSystem_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_flightControlSystem_T flightControlSystem_PrevZCX;

/* External outputs (root outports fed by signals with default storage) */
ExtY_flightControlSystem_T flightControlSystem_Y;

/* Real-time model */
static RT_MODEL_flightControlSystem_T flightControlSystem_M_;
RT_MODEL_flightControlSystem_T *const flightControlSystem_M =
  &flightControlSystem_M_;

/* Forward declaration for local functions */
static real32_T flightControlSystem_rt_powf_snf(real32_T u0, real32_T u1,
  B_FlightControlSystem_flightControlSystem_T *localB);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void flightControlSystem_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(flightControlSystem_M, 1));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (flightControlSystem_M->Timing.TaskCounters.TID[1])++;
  if ((flightControlSystem_M->Timing.TaskCounters.TID[1]) > 39) {/* Sample time: [0.2s, 0.0s] */
    flightControlSystem_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/*
 * System initialize for enable system:
 *    '<S44>/MeasurementUpdate'
 *    '<S206>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_Init
  (B_MeasurementUpdate_flightControlSystem_T *localB,
   P_MeasurementUpdate_flightControlSystem_T *localP)
{
  /* SystemInitialize for Product: '<S75>/Product3' incorporates:
   *  Outport: '<S75>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3[0] = localP->Lykyhatkk1_Y0;
  localB->Product3[1] = localP->Lykyhatkk1_Y0;
}

/*
 * Disable for enable system:
 *    '<S44>/MeasurementUpdate'
 *    '<S206>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_Disable
  (B_MeasurementUpdate_flightControlSystem_T *localB,
   DW_MeasurementUpdate_flightControlSystem_T *localDW,
   P_MeasurementUpdate_flightControlSystem_T *localP)
{
  /* Disable for Product: '<S75>/Product3' incorporates:
   *  Outport: '<S75>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3[0] = localP->Lykyhatkk1_Y0;
  localB->Product3[1] = localP->Lykyhatkk1_Y0;
  localDW->MeasurementUpdate_MODE = false;
}

/*
 * Start for enable system:
 *    '<S44>/MeasurementUpdate'
 *    '<S206>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_Start
  (DW_MeasurementUpdate_flightControlSystem_T *localDW)
{
  localDW->MeasurementUpdate_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S44>/MeasurementUpdate'
 *    '<S206>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate(boolean_T rtu_Enable, const real32_T
  rtu_Lk[4], const real32_T rtu_yk[2], const real32_T rtu_Ck[4], const real32_T
  rtu_xhatkk1[2], const real32_T rtu_Dk[2], real32_T rtu_uk,
  B_MeasurementUpdate_flightControlSystem_T *localB,
  DW_MeasurementUpdate_flightControlSystem_T *localDW,
  P_MeasurementUpdate_flightControlSystem_T *localP)
{
  real32_T rtu_yk_idx_0;
  real32_T rtu_yk_idx_1;

  /* Outputs for Enabled SubSystem: '<S44>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S75>/Enable'
   */
  if (rtu_Enable) {
    localDW->MeasurementUpdate_MODE = true;

    /* Sum: '<S75>/Sum' incorporates:
     *  Product: '<S75>/C[k]*xhat[k|k-1]'
     *  Product: '<S75>/D[k]*u[k]'
     *  Sum: '<S75>/Add1'
     */
    rtu_yk_idx_0 = rtu_yk[0] - ((rtu_Ck[0] * rtu_xhatkk1[0] + rtu_xhatkk1[1] *
      rtu_Ck[2]) + rtu_Dk[0] * rtu_uk);
    rtu_yk_idx_1 = rtu_yk[1] - ((rtu_xhatkk1[0] * rtu_Ck[1] + rtu_xhatkk1[1] *
      rtu_Ck[3]) + rtu_Dk[1] * rtu_uk);

    /* Product: '<S75>/Product3' */
    localB->Product3[0] = rtu_Lk[0] * rtu_yk_idx_0;
    localB->Product3[1] = rtu_Lk[1] * rtu_yk_idx_0;
    localB->Product3[0] += rtu_Lk[2] * rtu_yk_idx_1;
    localB->Product3[1] += rtu_Lk[3] * rtu_yk_idx_1;
  } else if (localDW->MeasurementUpdate_MODE) {
    flightControlSystem_MeasurementUpdate_Disable(localB, localDW, localP);
  }

  /* End of Outputs for SubSystem: '<S44>/MeasurementUpdate' */
}

/*
 * System initialize for enable system:
 *    '<S51>/Enabled Subsystem'
 *    '<S213>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_Init
  (B_EnabledSubsystem_flightControlSystem_T *localB,
   P_EnabledSubsystem_flightControlSystem_T *localP)
{
  /* SystemInitialize for Product: '<S77>/Product2' incorporates:
   *  Outport: '<S77>/deltax'
   */
  localB->Product2[0] = localP->deltax_Y0;
  localB->Product2[1] = localP->deltax_Y0;
}

/*
 * Disable for enable system:
 *    '<S51>/Enabled Subsystem'
 *    '<S213>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_Disable
  (B_EnabledSubsystem_flightControlSystem_T *localB,
   DW_EnabledSubsystem_flightControlSystem_T *localDW,
   P_EnabledSubsystem_flightControlSystem_T *localP)
{
  /* Disable for Product: '<S77>/Product2' incorporates:
   *  Outport: '<S77>/deltax'
   */
  localB->Product2[0] = localP->deltax_Y0;
  localB->Product2[1] = localP->deltax_Y0;
  localDW->EnabledSubsystem_MODE = false;
}

/*
 * Start for enable system:
 *    '<S51>/Enabled Subsystem'
 *    '<S213>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_Start
  (DW_EnabledSubsystem_flightControlSystem_T *localDW)
{
  localDW->EnabledSubsystem_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S51>/Enabled Subsystem'
 *    '<S213>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem(boolean_T rtu_Enable, const real32_T
  rtu_Mk[4], const real32_T rtu_Ck[4], const real32_T rtu_yk[2], const real32_T
  rtu_xhatkk1[2], B_EnabledSubsystem_flightControlSystem_T *localB,
  DW_EnabledSubsystem_flightControlSystem_T *localDW,
  P_EnabledSubsystem_flightControlSystem_T *localP)
{
  real32_T rtu_yk_idx_0;
  real32_T rtu_yk_idx_1;

  /* Outputs for Enabled SubSystem: '<S51>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S77>/Enable'
   */
  if (rtu_Enable) {
    localDW->EnabledSubsystem_MODE = true;

    /* Sum: '<S77>/Add1' incorporates:
     *  Product: '<S77>/Product'
     */
    rtu_yk_idx_0 = rtu_yk[0] - (rtu_Ck[0] * rtu_xhatkk1[0] + rtu_xhatkk1[1] *
      rtu_Ck[2]);
    rtu_yk_idx_1 = rtu_yk[1] - (rtu_xhatkk1[0] * rtu_Ck[1] + rtu_xhatkk1[1] *
      rtu_Ck[3]);

    /* Product: '<S77>/Product2' */
    localB->Product2[0] = rtu_Mk[0] * rtu_yk_idx_0;
    localB->Product2[1] = rtu_Mk[1] * rtu_yk_idx_0;
    localB->Product2[0] += rtu_Mk[2] * rtu_yk_idx_1;
    localB->Product2[1] += rtu_Mk[3] * rtu_yk_idx_1;
  } else if (localDW->EnabledSubsystem_MODE) {
    flightControlSystem_EnabledSubsystem_Disable(localB, localDW, localP);
  }

  /* End of Outputs for SubSystem: '<S51>/Enabled Subsystem' */
}

/*
 * System initialize for enable system:
 *    '<S98>/MeasurementUpdate'
 *    '<S152>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_f_Init
  (B_MeasurementUpdate_flightControlSystem_n_T *localB,
   P_MeasurementUpdate_flightControlSystem_o_T *localP)
{
  /* SystemInitialize for Product: '<S129>/Product3' incorporates:
   *  Outport: '<S129>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3[0] = localP->Lykyhatkk1_Y0;
  localB->Product3[1] = localP->Lykyhatkk1_Y0;
  localB->Product3[2] = localP->Lykyhatkk1_Y0;
  localB->Product3[3] = localP->Lykyhatkk1_Y0;
}

/*
 * Disable for enable system:
 *    '<S98>/MeasurementUpdate'
 *    '<S152>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_c_Disable
  (B_MeasurementUpdate_flightControlSystem_n_T *localB,
   DW_MeasurementUpdate_flightControlSystem_o_T *localDW,
   P_MeasurementUpdate_flightControlSystem_o_T *localP)
{
  /* Disable for Product: '<S129>/Product3' incorporates:
   *  Outport: '<S129>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3[0] = localP->Lykyhatkk1_Y0;
  localB->Product3[1] = localP->Lykyhatkk1_Y0;
  localB->Product3[2] = localP->Lykyhatkk1_Y0;
  localB->Product3[3] = localP->Lykyhatkk1_Y0;
  localDW->MeasurementUpdate_MODE = false;
}

/*
 * Start for enable system:
 *    '<S98>/MeasurementUpdate'
 *    '<S152>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_c_Start
  (DW_MeasurementUpdate_flightControlSystem_o_T *localDW)
{
  localDW->MeasurementUpdate_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S98>/MeasurementUpdate'
 *    '<S152>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_j(boolean_T rtu_Enable, const
  real32_T rtu_Lk[16], const real32_T rtu_yk[4], const real32_T rtu_Ck[16],
  const real32_T rtu_xhatkk1[4], const real32_T rtu_Dk[4], real32_T rtu_uk,
  B_MeasurementUpdate_flightControlSystem_n_T *localB,
  DW_MeasurementUpdate_flightControlSystem_o_T *localDW,
  P_MeasurementUpdate_flightControlSystem_o_T *localP)
{
  int32_T i;
  int32_T rtu_Ck_idx_0_tmp;
  real32_T rtu_yk_0[4];
  real32_T rtu_Ck_idx_0;
  real32_T rtu_Ck_idx_1;
  real32_T rtu_Ck_idx_2;
  real32_T rtu_Ck_idx_3;
  real32_T tmp;

  /* Outputs for Enabled SubSystem: '<S98>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S129>/Enable'
   */
  if (rtu_Enable) {
    localDW->MeasurementUpdate_MODE = true;

    /* Product: '<S129>/C[k]*xhat[k|k-1]' */
    rtu_Ck_idx_0 = 0.0F;
    rtu_Ck_idx_1 = 0.0F;
    rtu_Ck_idx_2 = 0.0F;
    rtu_Ck_idx_3 = 0.0F;
    for (i = 0; i < 4; i++) {
      tmp = rtu_xhatkk1[i];
      rtu_Ck_idx_0_tmp = i << 2;
      rtu_Ck_idx_0 += rtu_Ck[rtu_Ck_idx_0_tmp] * tmp;
      rtu_Ck_idx_1 += rtu_Ck[rtu_Ck_idx_0_tmp + 1] * tmp;
      rtu_Ck_idx_2 += rtu_Ck[rtu_Ck_idx_0_tmp + 2] * tmp;
      rtu_Ck_idx_3 += rtu_Ck[rtu_Ck_idx_0_tmp + 3] * tmp;
    }

    /* End of Product: '<S129>/C[k]*xhat[k|k-1]' */

    /* Sum: '<S129>/Sum' incorporates:
     *  Product: '<S129>/D[k]*u[k]'
     *  Sum: '<S129>/Add1'
     */
    rtu_yk_0[0] = rtu_yk[0] - (rtu_Dk[0] * rtu_uk + rtu_Ck_idx_0);
    rtu_yk_0[1] = rtu_yk[1] - (rtu_Dk[1] * rtu_uk + rtu_Ck_idx_1);
    rtu_yk_0[2] = rtu_yk[2] - (rtu_Dk[2] * rtu_uk + rtu_Ck_idx_2);
    rtu_yk_0[3] = rtu_yk[3] - (rtu_Dk[3] * rtu_uk + rtu_Ck_idx_3);

    /* Product: '<S129>/Product3' */
    rtu_Ck_idx_0 = 0.0F;
    rtu_Ck_idx_1 = 0.0F;
    rtu_Ck_idx_2 = 0.0F;
    rtu_Ck_idx_3 = 0.0F;
    for (i = 0; i < 4; i++) {
      tmp = rtu_yk_0[i];
      rtu_Ck_idx_0_tmp = i << 2;
      rtu_Ck_idx_0 += rtu_Lk[rtu_Ck_idx_0_tmp] * tmp;
      rtu_Ck_idx_1 += rtu_Lk[rtu_Ck_idx_0_tmp + 1] * tmp;
      rtu_Ck_idx_2 += rtu_Lk[rtu_Ck_idx_0_tmp + 2] * tmp;
      rtu_Ck_idx_3 += rtu_Lk[rtu_Ck_idx_0_tmp + 3] * tmp;
    }

    localB->Product3[3] = rtu_Ck_idx_3;
    localB->Product3[2] = rtu_Ck_idx_2;
    localB->Product3[1] = rtu_Ck_idx_1;
    localB->Product3[0] = rtu_Ck_idx_0;

    /* End of Product: '<S129>/Product3' */
  } else if (localDW->MeasurementUpdate_MODE) {
    flightControlSystem_MeasurementUpdate_c_Disable(localB, localDW, localP);
  }

  /* End of Outputs for SubSystem: '<S98>/MeasurementUpdate' */
}

/*
 * System initialize for enable system:
 *    '<S105>/Enabled Subsystem'
 *    '<S159>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_d_Init
  (B_EnabledSubsystem_flightControlSystem_g_T *localB,
   P_EnabledSubsystem_flightControlSystem_i_T *localP)
{
  /* SystemInitialize for Product: '<S131>/Product2' incorporates:
   *  Outport: '<S131>/deltax'
   */
  localB->Product2[0] = localP->deltax_Y0;
  localB->Product2[1] = localP->deltax_Y0;
  localB->Product2[2] = localP->deltax_Y0;
  localB->Product2[3] = localP->deltax_Y0;
}

/*
 * Disable for enable system:
 *    '<S105>/Enabled Subsystem'
 *    '<S159>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_n_Disable
  (B_EnabledSubsystem_flightControlSystem_g_T *localB,
   DW_EnabledSubsystem_flightControlSystem_b_T *localDW,
   P_EnabledSubsystem_flightControlSystem_i_T *localP)
{
  /* Disable for Product: '<S131>/Product2' incorporates:
   *  Outport: '<S131>/deltax'
   */
  localB->Product2[0] = localP->deltax_Y0;
  localB->Product2[1] = localP->deltax_Y0;
  localB->Product2[2] = localP->deltax_Y0;
  localB->Product2[3] = localP->deltax_Y0;
  localDW->EnabledSubsystem_MODE = false;
}

/*
 * Start for enable system:
 *    '<S105>/Enabled Subsystem'
 *    '<S159>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_h_Start
  (DW_EnabledSubsystem_flightControlSystem_b_T *localDW)
{
  localDW->EnabledSubsystem_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S105>/Enabled Subsystem'
 *    '<S159>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_e(boolean_T rtu_Enable, const real32_T
  rtu_Mk[16], const real32_T rtu_Ck[16], const real32_T rtu_yk[4], const
  real32_T rtu_xhatkk1[4], B_EnabledSubsystem_flightControlSystem_g_T *localB,
  DW_EnabledSubsystem_flightControlSystem_b_T *localDW,
  P_EnabledSubsystem_flightControlSystem_i_T *localP)
{
  int32_T Product2_tmp;
  int32_T i;
  real32_T rtu_yk_0[4];
  real32_T Product2;
  real32_T Product2_0;
  real32_T Product2_1;
  real32_T Product2_2;
  real32_T rtu_xhatkk1_0;
  real32_T rtu_xhatkk1_1;
  real32_T rtu_xhatkk1_2;
  real32_T rtu_xhatkk1_3;
  real32_T tmp;

  /* Outputs for Enabled SubSystem: '<S105>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S131>/Enable'
   */
  if (rtu_Enable) {
    localDW->EnabledSubsystem_MODE = true;

    /* Product: '<S131>/Product' */
    rtu_xhatkk1_0 = rtu_xhatkk1[1];
    rtu_xhatkk1_1 = rtu_xhatkk1[0];
    rtu_xhatkk1_2 = rtu_xhatkk1[2];
    rtu_xhatkk1_3 = rtu_xhatkk1[3];

    /* Product: '<S131>/Product2' */
    Product2 = 0.0F;
    Product2_0 = 0.0F;
    Product2_1 = 0.0F;
    Product2_2 = 0.0F;
    for (i = 0; i < 4; i++) {
      /* Sum: '<S131>/Add1' incorporates:
       *  Product: '<S131>/Product'
       */
      rtu_yk_0[i] = rtu_yk[i] - (((rtu_Ck[i + 4] * rtu_xhatkk1_0 + rtu_Ck[i] *
        rtu_xhatkk1_1) + rtu_Ck[i + 8] * rtu_xhatkk1_2) + rtu_Ck[i + 12] *
        rtu_xhatkk1_3);

      /* Product: '<S131>/Product2' */
      tmp = rtu_yk_0[i];
      Product2_tmp = i << 2;
      Product2 += rtu_Mk[Product2_tmp] * tmp;
      Product2_0 += rtu_Mk[Product2_tmp + 1] * tmp;
      Product2_1 += rtu_Mk[Product2_tmp + 2] * tmp;
      Product2_2 += rtu_Mk[Product2_tmp + 3] * tmp;
    }

    /* Product: '<S131>/Product2' */
    localB->Product2[3] = Product2_2;
    localB->Product2[2] = Product2_1;
    localB->Product2[1] = Product2_0;
    localB->Product2[0] = Product2;
  } else if (localDW->EnabledSubsystem_MODE) {
    flightControlSystem_EnabledSubsystem_n_Disable(localB, localDW, localP);
  }

  /* End of Outputs for SubSystem: '<S105>/Enabled Subsystem' */
}

/*
 * Output and update for action system:
 *    '<S4>/Geofencing error'
 *    '<S4>/estimator//Optical flow error'
 *    '<S4>/No optical flow '
 *    '<S4>/Ultrasound improper'
 */
void flightControlSystem_Geofencingerror(uint8_T *rty_Out1,
  P_Geofencingerror_flightControlSystem_T *localP)
{
  /* SignalConversion generated from: '<S252>/Out1' incorporates:
   *  Constant: '<S252>/Constant'
   */
  *rty_Out1 = localP->Constant_Value;
}

/*
 * System initialize for enable system:
 *    '<S361>/MeasurementUpdate'
 *    '<S415>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_e_Init
  (B_MeasurementUpdate_flightControlSystem_k_T *localB,
   P_MeasurementUpdate_flightControlSystem_i_T *localP)
{
  /* SystemInitialize for Product: '<S392>/Product3' incorporates:
   *  Outport: '<S392>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3[0] = localP->Lykyhatkk1_Y0;
  localB->Product3[1] = localP->Lykyhatkk1_Y0;
}

/*
 * Disable for enable system:
 *    '<S361>/MeasurementUpdate'
 *    '<S415>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_k_Disable
  (B_MeasurementUpdate_flightControlSystem_k_T *localB,
   DW_MeasurementUpdate_flightControlSystem_c_T *localDW,
   P_MeasurementUpdate_flightControlSystem_i_T *localP)
{
  /* Disable for Product: '<S392>/Product3' incorporates:
   *  Outport: '<S392>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3[0] = localP->Lykyhatkk1_Y0;
  localB->Product3[1] = localP->Lykyhatkk1_Y0;
  localDW->MeasurementUpdate_MODE = false;
}

/*
 * Start for enable system:
 *    '<S361>/MeasurementUpdate'
 *    '<S415>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_h_Start
  (DW_MeasurementUpdate_flightControlSystem_c_T *localDW)
{
  localDW->MeasurementUpdate_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S361>/MeasurementUpdate'
 *    '<S415>/MeasurementUpdate'
 */
void flightControlSystem_MeasurementUpdate_o(boolean_T rtu_Enable, const
  real32_T rtu_Lk[2], real32_T rtu_yk, const real32_T rtu_Ck[2], const real32_T
  rtu_xhatkk1[2], real32_T rtu_Dk, real32_T rtu_uk,
  B_MeasurementUpdate_flightControlSystem_k_T *localB,
  DW_MeasurementUpdate_flightControlSystem_c_T *localDW,
  P_MeasurementUpdate_flightControlSystem_i_T *localP)
{
  real32_T rtb_Sum_jt;

  /* Outputs for Enabled SubSystem: '<S361>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S392>/Enable'
   */
  if (rtu_Enable) {
    localDW->MeasurementUpdate_MODE = true;

    /* Sum: '<S392>/Sum' incorporates:
     *  Product: '<S392>/C[k]*xhat[k|k-1]'
     *  Product: '<S392>/D[k]*u[k]'
     *  Sum: '<S392>/Add1'
     */
    rtb_Sum_jt = rtu_yk - ((rtu_Ck[0] * rtu_xhatkk1[0] + rtu_Ck[1] *
      rtu_xhatkk1[1]) + rtu_Dk * rtu_uk);

    /* Product: '<S392>/Product3' */
    localB->Product3[0] = rtu_Lk[0] * rtb_Sum_jt;
    localB->Product3[1] = rtu_Lk[1] * rtb_Sum_jt;
  } else if (localDW->MeasurementUpdate_MODE) {
    flightControlSystem_MeasurementUpdate_k_Disable(localB, localDW, localP);
  }

  /* End of Outputs for SubSystem: '<S361>/MeasurementUpdate' */
}

/*
 * System initialize for enable system:
 *    '<S368>/Enabled Subsystem'
 *    '<S422>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_c_Init
  (B_EnabledSubsystem_flightControlSystem_c_T *localB,
   P_EnabledSubsystem_flightControlSystem_g_T *localP)
{
  /* SystemInitialize for Product: '<S394>/Product2' incorporates:
   *  Outport: '<S394>/deltax'
   */
  localB->Product2[0] = localP->deltax_Y0;
  localB->Product2[1] = localP->deltax_Y0;
}

/*
 * Disable for enable system:
 *    '<S368>/Enabled Subsystem'
 *    '<S422>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_g_Disable
  (B_EnabledSubsystem_flightControlSystem_c_T *localB,
   DW_EnabledSubsystem_flightControlSystem_o_T *localDW,
   P_EnabledSubsystem_flightControlSystem_g_T *localP)
{
  /* Disable for Product: '<S394>/Product2' incorporates:
   *  Outport: '<S394>/deltax'
   */
  localB->Product2[0] = localP->deltax_Y0;
  localB->Product2[1] = localP->deltax_Y0;
  localDW->EnabledSubsystem_MODE = false;
}

/*
 * Start for enable system:
 *    '<S368>/Enabled Subsystem'
 *    '<S422>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_o_Start
  (DW_EnabledSubsystem_flightControlSystem_o_T *localDW)
{
  localDW->EnabledSubsystem_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S368>/Enabled Subsystem'
 *    '<S422>/Enabled Subsystem'
 */
void flightControlSystem_EnabledSubsystem_k(boolean_T rtu_Enable, const real32_T
  rtu_Mk[2], const real32_T rtu_Ck[2], real32_T rtu_yk, const real32_T
  rtu_xhatkk1[2], B_EnabledSubsystem_flightControlSystem_c_T *localB,
  DW_EnabledSubsystem_flightControlSystem_o_T *localDW,
  P_EnabledSubsystem_flightControlSystem_g_T *localP)
{
  real32_T rtb_Add1_d;

  /* Outputs for Enabled SubSystem: '<S368>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S394>/Enable'
   */
  if (rtu_Enable) {
    localDW->EnabledSubsystem_MODE = true;

    /* Sum: '<S394>/Add1' incorporates:
     *  Product: '<S394>/Product'
     */
    rtb_Add1_d = rtu_yk - (rtu_Ck[0] * rtu_xhatkk1[0] + rtu_Ck[1] * rtu_xhatkk1
      [1]);

    /* Product: '<S394>/Product2' */
    localB->Product2[0] = rtu_Mk[0] * rtb_Add1_d;
    localB->Product2[1] = rtu_Mk[1] * rtb_Add1_d;
  } else if (localDW->EnabledSubsystem_MODE) {
    flightControlSystem_EnabledSubsystem_g_Disable(localB, localDW, localP);
  }

  /* End of Outputs for SubSystem: '<S368>/Enabled Subsystem' */
}

static real32_T flightControlSystem_rt_powf_snf(real32_T u0, real32_T u1,
  B_FlightControlSystem_flightControlSystem_T *localB)
{
  real32_T y;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else {
    localB->f = (real32_T)fabs(u0);
    localB->f1 = (real32_T)fabs(u1);
    if (rtIsInfF(u1)) {
      if (localB->f == 1.0F) {
        y = 1.0F;
      } else if (localB->f > 1.0F) {
        if (u1 > 0.0F) {
          y = (rtInfF);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = (rtInfF);
      }
    } else if (localB->f1 == 0.0F) {
      y = 1.0F;
    } else if (localB->f1 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = (real32_T)sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > (real32_T)floor(u1))) {
      y = (rtNaNF);
    } else {
      y = (real32_T)pow(u0, u1);
    }
  }

  return y;
}

/* SetupRuntimeResources for atomic system: '<Root>/Flight Control System' */
void flightControlSystem_FlightControlSystem_SetupRTR
  (RT_MODEL_flightControlSystem_T * const flightControlSystem_M,
   DW_FlightControlSystem_flightControlSystem_T *localDW)
{
  /* SetupRuntimeResources for ToWorkspace: '<S6>/To Workspace1' */
  {
    static int_T rt_ToWksWidths[] = { 28 };

    static int_T rt_ToWksNumDimensions[] = { 1 };

    static int_T rt_ToWksDimensions[] = { 28 };

    static boolean_T rt_ToWksIsVarDims[] = { 0 };

    static void *rt_ToWksCurrSigDims[] = { (NULL) };

    static int_T rt_ToWksCurrSigDimsSize[] = { 4 };

    static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_SINGLE };

    static int_T rt_ToWksComplexSignals[] = { 0 };

    static int_T rt_ToWksFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ToWksLoggingPreprocessingFcnPtrs[] = {
      (NULL)
    };

    static const char_T *rt_ToWksLabels[] = { "" };

    static RTWLogSignalInfo rt_ToWksSignalInfo = {
      1,
      rt_ToWksWidths,
      rt_ToWksNumDimensions,
      rt_ToWksDimensions,
      rt_ToWksIsVarDims,
      rt_ToWksCurrSigDims,
      rt_ToWksCurrSigDimsSize,
      rt_ToWksDataTypeIds,
      rt_ToWksComplexSignals,
      rt_ToWksFrameData,
      rt_ToWksLoggingPreprocessingFcnPtrs,

      { rt_ToWksLabels },
      (NULL),
      (NULL),
      (NULL),

      { (NULL) },

      { (NULL) },
      (NULL),
      (NULL)
    };

    static const char_T rt_ToWksBlockName[] =
      "flightControlSystem/Flight Control System/RawSensors/To Workspace1";
    localDW->ToWorkspace1_PWORK.LoggedData = rt_CreateStructLogVar(
      flightControlSystem_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(flightControlSystem_M),
      flightControlSystem_M->Timing.stepSize0,
      (&rtmGetErrorStatus(flightControlSystem_M)),
      "SensorRawData",
      1,
      0,
      1,
      0.005,
      &rt_ToWksSignalInfo,
      rt_ToWksBlockName);
    if (localDW->ToWorkspace1_PWORK.LoggedData == (NULL))
      return;
  }

  /* SetupRuntimeResources for ToWorkspace: '<S1>/To Workspace' */
  {
    static int_T rt_ToWksWidths[] = { 12 };

    static int_T rt_ToWksNumDimensions[] = { 1 };

    static int_T rt_ToWksDimensions[] = { 12 };

    static boolean_T rt_ToWksIsVarDims[] = { 0 };

    static void *rt_ToWksCurrSigDims[] = { (NULL) };

    static int_T rt_ToWksCurrSigDimsSize[] = { 4 };

    static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_SINGLE };

    static int_T rt_ToWksComplexSignals[] = { 0 };

    static int_T rt_ToWksFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ToWksLoggingPreprocessingFcnPtrs[] = {
      (NULL)
    };

    static const char_T *rt_ToWksLabels[] = { "" };

    static RTWLogSignalInfo rt_ToWksSignalInfo = {
      1,
      rt_ToWksWidths,
      rt_ToWksNumDimensions,
      rt_ToWksDimensions,
      rt_ToWksIsVarDims,
      rt_ToWksCurrSigDims,
      rt_ToWksCurrSigDimsSize,
      rt_ToWksDataTypeIds,
      rt_ToWksComplexSignals,
      rt_ToWksFrameData,
      rt_ToWksLoggingPreprocessingFcnPtrs,

      { rt_ToWksLabels },
      (NULL),
      (NULL),
      (NULL),

      { (NULL) },

      { (NULL) },
      (NULL),
      (NULL)
    };

    static const char_T rt_ToWksBlockName[] =
      "flightControlSystem/Flight Control System/To Workspace";
    localDW->ToWorkspace_PWORK.LoggedData = rt_CreateStructLogVar(
      flightControlSystem_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(flightControlSystem_M),
      flightControlSystem_M->Timing.stepSize0,
      (&rtmGetErrorStatus(flightControlSystem_M)),
      "measuredStates",
      1,
      0,
      1,
      0.005,
      &rt_ToWksSignalInfo,
      rt_ToWksBlockName);
    if (localDW->ToWorkspace_PWORK.LoggedData == (NULL))
      return;
  }

  /* SetupRuntimeResources for ToWorkspace: '<S5>/To Workspace' */
  {
    static int_T rt_ToWksWidths[] = { 6 };

    static int_T rt_ToWksNumDimensions[] = { 1 };

    static int_T rt_ToWksDimensions[] = { 6 };

    static boolean_T rt_ToWksIsVarDims[] = { 0 };

    static void *rt_ToWksCurrSigDims[] = { (NULL) };

    static int_T rt_ToWksCurrSigDimsSize[] = { 4 };

    static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_SINGLE };

    static int_T rt_ToWksComplexSignals[] = { 0 };

    static int_T rt_ToWksFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ToWksLoggingPreprocessingFcnPtrs[] = {
      (NULL)
    };

    static const char_T *rt_ToWksLabels[] = { "" };

    static RTWLogSignalInfo rt_ToWksSignalInfo = {
      1,
      rt_ToWksWidths,
      rt_ToWksNumDimensions,
      rt_ToWksDimensions,
      rt_ToWksIsVarDims,
      rt_ToWksCurrSigDims,
      rt_ToWksCurrSigDimsSize,
      rt_ToWksDataTypeIds,
      rt_ToWksComplexSignals,
      rt_ToWksFrameData,
      rt_ToWksLoggingPreprocessingFcnPtrs,

      { rt_ToWksLabels },
      (NULL),
      (NULL),
      (NULL),

      { (NULL) },

      { (NULL) },
      (NULL),
      (NULL)
    };

    static const char_T rt_ToWksBlockName[] =
      "flightControlSystem/Flight Control System/Path Planning/To Workspace";
    localDW->ToWorkspace_PWORK_c.LoggedData = rt_CreateStructLogVar(
      flightControlSystem_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(flightControlSystem_M),
      flightControlSystem_M->Timing.stepSize0,
      (&rtmGetErrorStatus(flightControlSystem_M)),
      "posOriRef",
      1,
      0,
      1,
      0.005,
      &rt_ToWksSignalInfo,
      rt_ToWksBlockName);
    if (localDW->ToWorkspace_PWORK_c.LoggedData == (NULL))
      return;
  }

  /* SetupRuntimeResources for ToWorkspace: '<S16>/To Workspace' */
  {
    static int_T rt_ToWksWidths[] = { 4 };

    static int_T rt_ToWksNumDimensions[] = { 1 };

    static int_T rt_ToWksDimensions[] = { 4 };

    static boolean_T rt_ToWksIsVarDims[] = { 0 };

    static void *rt_ToWksCurrSigDims[] = { (NULL) };

    static int_T rt_ToWksCurrSigDimsSize[] = { 4 };

    static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_SINGLE };

    static int_T rt_ToWksComplexSignals[] = { 0 };

    static int_T rt_ToWksFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ToWksLoggingPreprocessingFcnPtrs[] = {
      (NULL)
    };

    static const char_T *rt_ToWksLabels[] = { "" };

    static RTWLogSignalInfo rt_ToWksSignalInfo = {
      1,
      rt_ToWksWidths,
      rt_ToWksNumDimensions,
      rt_ToWksDimensions,
      rt_ToWksIsVarDims,
      rt_ToWksCurrSigDims,
      rt_ToWksCurrSigDimsSize,
      rt_ToWksDataTypeIds,
      rt_ToWksComplexSignals,
      rt_ToWksFrameData,
      rt_ToWksLoggingPreprocessingFcnPtrs,

      { rt_ToWksLabels },
      (NULL),
      (NULL),
      (NULL),

      { (NULL) },

      { (NULL) },
      (NULL),
      (NULL)
    };

    static const char_T rt_ToWksBlockName[] =
      "flightControlSystem/Flight Control System/Controller/thrustsToMotorCommands/To Workspace";
    localDW->ToWorkspace_PWORK_d.LoggedData = rt_CreateStructLogVar(
      flightControlSystem_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(flightControlSystem_M),
      flightControlSystem_M->Timing.stepSize0,
      (&rtmGetErrorStatus(flightControlSystem_M)),
      "motorCommandsOut",
      1,
      0,
      1,
      0.005,
      &rt_ToWksSignalInfo,
      rt_ToWksBlockName);
    if (localDW->ToWorkspace_PWORK_d.LoggedData == (NULL))
      return;
  }

  /* SetupRuntimeResources for ToWorkspace: '<S9>/To Workspace' */
  {
    static int_T rt_ToWksWidths[] = { 4 };

    static int_T rt_ToWksNumDimensions[] = { 1 };

    static int_T rt_ToWksDimensions[] = { 4 };

    static boolean_T rt_ToWksIsVarDims[] = { 0 };

    static void *rt_ToWksCurrSigDims[] = { (NULL) };

    static int_T rt_ToWksCurrSigDimsSize[] = { 4 };

    static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_SINGLE };

    static int_T rt_ToWksComplexSignals[] = { 0 };

    static int_T rt_ToWksFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ToWksLoggingPreprocessingFcnPtrs[] = {
      (NULL)
    };

    static const char_T *rt_ToWksLabels[] = { "" };

    static RTWLogSignalInfo rt_ToWksSignalInfo = {
      1,
      rt_ToWksWidths,
      rt_ToWksNumDimensions,
      rt_ToWksDimensions,
      rt_ToWksIsVarDims,
      rt_ToWksCurrSigDims,
      rt_ToWksCurrSigDimsSize,
      rt_ToWksDataTypeIds,
      rt_ToWksComplexSignals,
      rt_ToWksFrameData,
      rt_ToWksLoggingPreprocessingFcnPtrs,

      { rt_ToWksLabels },
      (NULL),
      (NULL),
      (NULL),

      { (NULL) },

      { (NULL) },
      (NULL),
      (NULL)
    };

    static const char_T rt_ToWksBlockName[] =
      "flightControlSystem/Flight Control System/Controller/ControlMixer/To Workspace";
    localDW->ToWorkspace_PWORK_g.LoggedData = rt_CreateStructLogVar(
      flightControlSystem_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(flightControlSystem_M),
      flightControlSystem_M->Timing.stepSize0,
      (&rtmGetErrorStatus(flightControlSystem_M)),
      "controlActionFM",
      1,
      0,
      1,
      0.005,
      &rt_ToWksSignalInfo,
      rt_ToWksBlockName);
    if (localDW->ToWorkspace_PWORK_g.LoggedData == (NULL))
      return;
  }

  /* SetupRuntimeResources for ToWorkspace: '<S272>/To Workspace' */
  {
    static int_T rt_ToWksWidths[] = { 3 };

    static int_T rt_ToWksNumDimensions[] = { 1 };

    static int_T rt_ToWksDimensions[] = { 3 };

    static boolean_T rt_ToWksIsVarDims[] = { 0 };

    static void *rt_ToWksCurrSigDims[] = { (NULL) };

    static int_T rt_ToWksCurrSigDimsSize[] = { 4 };

    static BuiltInDTypeId rt_ToWksDataTypeIds[] = { SS_SINGLE };

    static int_T rt_ToWksComplexSignals[] = { 0 };

    static int_T rt_ToWksFrameData[] = { 0 };

    static RTWPreprocessingFcnPtr rt_ToWksLoggingPreprocessingFcnPtrs[] = {
      (NULL)
    };

    static const char_T *rt_ToWksLabels[] = { "" };

    static RTWLogSignalInfo rt_ToWksSignalInfo = {
      1,
      rt_ToWksWidths,
      rt_ToWksNumDimensions,
      rt_ToWksDimensions,
      rt_ToWksIsVarDims,
      rt_ToWksCurrSigDims,
      rt_ToWksCurrSigDimsSize,
      rt_ToWksDataTypeIds,
      rt_ToWksComplexSignals,
      rt_ToWksFrameData,
      rt_ToWksLoggingPreprocessingFcnPtrs,

      { rt_ToWksLabels },
      (NULL),
      (NULL),
      (NULL),

      { (NULL) },

      { (NULL) },
      (NULL),
      (NULL)
    };

    static const char_T rt_ToWksBlockName[] =
      "flightControlSystem/Flight Control System/State Estimator/Attitude Estimator/To Workspace";
    localDW->ToWorkspace_PWORK_l.LoggedData = rt_CreateStructLogVar(
      flightControlSystem_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(flightControlSystem_M),
      flightControlSystem_M->Timing.stepSize0,
      (&rtmGetErrorStatus(flightControlSystem_M)),
      "estimatedGyroBias",
      1,
      0,
      1,
      0.005,
      &rt_ToWksSignalInfo,
      rt_ToWksBlockName);
    if (localDW->ToWorkspace_PWORK_l.LoggedData == (NULL))
      return;
  }

  /* SetupRuntimeResources for Scope: '<S3>/yaw' */
  {
    RTWLogSignalInfo rt_ScopeSignalInfo;
    static int_T rt_ScopeSignalWidths[] = { 2 };

    static int_T rt_ScopeSignalNumDimensions[] = { 1 };

    static int_T rt_ScopeSignalDimensions[] = { 2 };

    static void *rt_ScopeCurrSigDims[] = { (NULL) };

    static int_T rt_ScopeCurrSigDimsSize[] = { 4 };

    static const char_T *rt_ScopeSignalLabels[] = { "" };

    static char_T rt_ScopeSignalTitles[] = "";
    static int_T rt_ScopeSignalTitleLengths[] = { 0 };

    static boolean_T rt_ScopeSignalIsVarDims[] = { 0 };

    static int_T rt_ScopeSignalPlotStyles[] = { 1, 1 };

    BuiltInDTypeId dTypes[1] = { SS_SINGLE };

    static char_T rt_ScopeBlockName[] =
      "flightControlSystem/Flight Control System/Controller/yaw";
    static RTWPreprocessingFcnPtr rt_ScopeSignalLoggingPreprocessingFcnPtrs[] =
      {
      (NULL)
    };

    rt_ScopeSignalInfo.numSignals = 1;
    rt_ScopeSignalInfo.numCols = rt_ScopeSignalWidths;
    rt_ScopeSignalInfo.numDims = rt_ScopeSignalNumDimensions;
    rt_ScopeSignalInfo.dims = rt_ScopeSignalDimensions;
    rt_ScopeSignalInfo.isVarDims = rt_ScopeSignalIsVarDims;
    rt_ScopeSignalInfo.currSigDims = rt_ScopeCurrSigDims;
    rt_ScopeSignalInfo.currSigDimsSize = rt_ScopeCurrSigDimsSize;
    rt_ScopeSignalInfo.dataTypes = dTypes;
    rt_ScopeSignalInfo.complexSignals = (NULL);
    rt_ScopeSignalInfo.frameData = (NULL);
    rt_ScopeSignalInfo.preprocessingPtrs =
      rt_ScopeSignalLoggingPreprocessingFcnPtrs;
    rt_ScopeSignalInfo.labels.cptr = rt_ScopeSignalLabels;
    rt_ScopeSignalInfo.titles = rt_ScopeSignalTitles;
    rt_ScopeSignalInfo.titleLengths = rt_ScopeSignalTitleLengths;
    rt_ScopeSignalInfo.plotStyles = rt_ScopeSignalPlotStyles;
    rt_ScopeSignalInfo.blockNames.cptr = (NULL);
    rt_ScopeSignalInfo.stateNames.cptr = (NULL);
    rt_ScopeSignalInfo.crossMdlRef = (NULL);
    rt_ScopeSignalInfo.dataTypeConvert = (NULL);
    localDW->yaw_PWORK.LoggedData = rt_CreateStructLogVar(
      flightControlSystem_M->rtwLogInfo,
      0.0,
      rtmGetTFinal(flightControlSystem_M),
      flightControlSystem_M->Timing.stepSize0,
      (&rtmGetErrorStatus(flightControlSystem_M)),
      "ScopeData3",
      1,
      0,
      1,
      0.005,
      &rt_ScopeSignalInfo,
      rt_ScopeBlockName);
    if (localDW->yaw_PWORK.LoggedData == (NULL))
      return;
  }
}

/* System initialize for atomic system: '<Root>/Flight Control System' */
void flightControlSystem_FlightControlSystem_Init
  (B_FlightControlSystem_flightControlSystem_T *localB,
   DW_FlightControlSystem_flightControlSystem_T *localDW,
   P_FlightControlSystem_flightControlSystem_T *localP,
   ZCE_FlightControlSystem_flightControlSystem_T *localZCE)
{
  int32_T i;

  /* InitializeConditions for DiscreteIntegrator: '<S457>/SimplyIntegrateVelocity' */
  localDW->SimplyIntegrateVelocity_DSTATE[0] =
    localP->SimplyIntegrateVelocity_IC;
  localDW->SimplyIntegrateVelocity_DSTATE[1] =
    localP->SimplyIntegrateVelocity_IC;
  localDW->SimplyIntegrateVelocity_PrevResetState = 2;

  /* InitializeConditions for Reshape: '<S275>/Reshapexhat' incorporates:
   *  Delay: '<S271>/Delay2'
   */
  localDW->Delay2_DSTATE = localP->Delay2_InitialCondition;

  /* InitializeConditions for Delay: '<S275>/MemoryX' */
  localDW->icLoad = true;

  /* InitializeConditions for DiscreteFilter: '<S276>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[0] =
    localP->pressureFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S276>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[0] = localP->sonarFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S276>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[1] =
    localP->pressureFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S276>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[1] = localP->sonarFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S276>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[2] =
    localP->pressureFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteFilter: '<S276>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[2] = localP->sonarFilter_IIR_InitialStates;

  /* InitializeConditions for DiscreteIntegrator: '<S339>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_p = localP->DiscreteTimeIntegrator_IC_b;

  /* InitializeConditions for Delay: '<S341>/MemoryX' */
  localDW->icLoad_a = true;

  /* InitializeConditions for DiscreteFir: '<S273>/FIR_IMUaccel' */
  localDW->FIR_IMUaccel_circBuf = 0;
  for (i = 0; i < 15; i++) {
    localDW->FIR_IMUaccel_states[i] = localP->FIR_IMUaccel_InitialStates;
  }

  /* End of InitializeConditions for DiscreteFir: '<S273>/FIR_IMUaccel' */

  /* InitializeConditions for Delay: '<S395>/MemoryX' */
  localDW->icLoad_n = true;

  /* InitializeConditions for DiscreteFilter: '<S273>/IIR_IMUgyro_r' */
  for (i = 0; i < 5; i++) {
    localDW->IIR_IMUgyro_r_states[i] = localP->IIR_IMUgyro_r_InitialStates;
  }

  /* End of InitializeConditions for DiscreteFilter: '<S273>/IIR_IMUgyro_r' */

  /* InitializeConditions for Sum: '<S454>/FixPt Sum1' incorporates:
   *  UnitDelay: '<S452>/Output'
   */
  localDW->Output_DSTATE = localP->Output_InitialCondition;

  /* InitializeConditions for Delay: '<S461>/MemoryX' */
  localDW->icLoad_k = true;

  /* InitializeConditions for Sum: '<S535>/FixPt Sum1' incorporates:
   *  UnitDelay: '<S534>/Output'
   */
  localDW->Output_DSTATE_i = localP->Output_InitialCondition_h;

  /* InitializeConditions for DiscreteFilter: '<S460>/IIRgyroz' */
  for (i = 0; i < 10; i++) {
    localDW->IIRgyroz_states[i] = localP->IIRgyroz_InitialStates;
  }

  /* End of InitializeConditions for DiscreteFilter: '<S460>/IIRgyroz' */

  /* InitializeConditions for DiscreteIntegrator: '<S265>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = localP->DiscreteTimeIntegrator_IC;

  /* InitializeConditions for Delay: '<S21>/MemoryX' */
  localDW->icLoad_b = true;

  /* InitializeConditions for DiscreteIntegrator: '<S15>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_DSTATE = localP->DiscreteTimeIntegrator2_IC;

  /* InitializeConditions for Delay: '<S20>/MemoryX' */
  localDW->icLoad_i = true;

  /* InitializeConditions for DiscreteIntegrator: '<S14>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_DSTATE_h =
    localP->DiscreteTimeIntegrator2_IC_l;

  /* InitializeConditions for Sum: '<S242>/FixPt Sum1' incorporates:
   *  UnitDelay: '<S241>/Output'
   */
  localDW->Output_DSTATE_n = localP->Output_InitialCondition_i;

  /* InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_m = localP->DiscreteTimeIntegrator_IC_j;
  localDW->DiscreteTimeIntegrator_PrevResetState = 2;

  /* InitializeConditions for Delay: '<S19>/MemoryX' */
  localDW->icLoad_o = true;

  /* InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_DSTATE_p =
    localP->DiscreteTimeIntegrator2_IC_i;

  /* InitializeConditions for Delay: '<S22>/MemoryX' */
  localDW->icLoad_h = true;

  /* InitializeConditions for DiscreteIntegrator: '<S18>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_DSTATE_d =
    localP->DiscreteTimeIntegrator2_IC_lx;

  /* InitializeConditions for UnitDelay: '<S468>/UD' incorporates:
   *  Sum: '<S468>/Diff'
   */
  localDW->UD_DSTATE[0] = localP->DiscreteDerivative_ICPrevScaledInput;

  /* InitializeConditions for Delay: '<S456>/Delay' */
  localDW->Delay_DSTATE[0] = localP->Delay_InitialCondition;

  /* InitializeConditions for Delay: '<S7>/Delay1' */
  localDW->Delay1_DSTATE[0] = localP->Delay1_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_c[0] =
    localP->DiscreteTimeIntegrator_IC_g;

  /* InitializeConditions for Delay: '<S8>/Delay' */
  localDW->Delay_DSTATE_f[0] = localP->Delay_InitialCondition_n;

  /* InitializeConditions for UnitDelay: '<S468>/UD' incorporates:
   *  Sum: '<S468>/Diff'
   */
  localDW->UD_DSTATE[1] = localP->DiscreteDerivative_ICPrevScaledInput;

  /* InitializeConditions for Delay: '<S456>/Delay' */
  localDW->Delay_DSTATE[1] = localP->Delay_InitialCondition;

  /* InitializeConditions for Delay: '<S7>/Delay1' */
  localDW->Delay1_DSTATE[1] = localP->Delay1_InitialCondition;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_c[1] =
    localP->DiscreteTimeIntegrator_IC_g;

  /* InitializeConditions for Delay: '<S8>/Delay' */
  localDW->Delay_DSTATE_f[1] = localP->Delay_InitialCondition_n;

  /* InitializeConditions for Sum: '<S258>/FixPt Sum1' incorporates:
   *  UnitDelay: '<S251>/Output'
   */
  localDW->Output_DSTATE_ir = localP->Output_InitialCondition_m;

  /* InitializeConditions for Sum: '<S255>/Add' incorporates:
   *  Delay: '<S255>/Delay One Step'
   */
  localDW->DelayOneStep_DSTATE = localP->DelayOneStep_InitialCondition;

  /* SystemInitialize for Enabled SubSystem: '<S44>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_Init(&localB->MeasurementUpdate,
    &localP->MeasurementUpdate);

  /* End of SystemInitialize for SubSystem: '<S44>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S51>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_Init(&localB->EnabledSubsystem,
    &localP->EnabledSubsystem);

  /* End of SystemInitialize for SubSystem: '<S51>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S98>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_f_Init(&localB->MeasurementUpdate_j,
    &localP->MeasurementUpdate_j);

  /* End of SystemInitialize for SubSystem: '<S98>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S105>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_d_Init(&localB->EnabledSubsystem_e,
    &localP->EnabledSubsystem_e);

  /* End of SystemInitialize for SubSystem: '<S105>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S152>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_f_Init(&localB->MeasurementUpdate_jc,
    &localP->MeasurementUpdate_jc);

  /* End of SystemInitialize for SubSystem: '<S152>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S159>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_d_Init(&localB->EnabledSubsystem_d,
    &localP->EnabledSubsystem_d);

  /* End of SystemInitialize for SubSystem: '<S159>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S206>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_Init(&localB->MeasurementUpdate_c,
    &localP->MeasurementUpdate_c);

  /* End of SystemInitialize for SubSystem: '<S206>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S213>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_Init(&localB->EnabledSubsystem_n,
    &localP->EnabledSubsystem_n);

  /* End of SystemInitialize for SubSystem: '<S213>/Enabled Subsystem' */

  /* SystemInitialize for Merge: '<S4>/Merge' */
  localB->Merge = localP->Merge_InitialOutput;

  /* SystemInitialize for Triggered SubSystem: '<S264>/Triggered Subsystem' */
  /* SystemInitialize for SignalConversion generated from: '<S268>/X' incorporates:
   *  Outport: '<S268>/X'
   */
  localB->BufferToMakeInportVirtual_InsertedFor_X_at_inport_0 = localP->X_Y0;

  /* SystemInitialize for SignalConversion generated from: '<S268>/Y' incorporates:
   *  Outport: '<S268>/Y'
   */
  localB->BufferToMakeInportVirtual_InsertedFor_Y_at_inport_0 = localP->Y_Y0;
  localZCE->TriggeredSubsystem_Trig_ZCE_p = ZERO_ZCSIG;

  /* End of SystemInitialize for SubSystem: '<S264>/Triggered Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S297>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S327>/Product3' incorporates:
   *  Outport: '<S327>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3[0] = localP->Lykyhatkk1_Y0;

  /* End of SystemInitialize for SubSystem: '<S297>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S303>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S329>/Product2' incorporates:
   *  Outport: '<S329>/deltax'
   */
  localB->Product2[0] = localP->deltax_Y0;

  /* End of SystemInitialize for SubSystem: '<S303>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S297>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S327>/Product3' incorporates:
   *  Outport: '<S327>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3[1] = localP->Lykyhatkk1_Y0;

  /* End of SystemInitialize for SubSystem: '<S297>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S303>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S329>/Product2' incorporates:
   *  Outport: '<S329>/deltax'
   */
  localB->Product2[1] = localP->deltax_Y0;

  /* End of SystemInitialize for SubSystem: '<S303>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S361>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_e_Init(&localB->MeasurementUpdate_o,
    &localP->MeasurementUpdate_o);

  /* End of SystemInitialize for SubSystem: '<S361>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S368>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_c_Init(&localB->EnabledSubsystem_k,
    &localP->EnabledSubsystem_k);

  /* End of SystemInitialize for SubSystem: '<S368>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S415>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_e_Init(&localB->MeasurementUpdate_n,
    &localP->MeasurementUpdate_n);

  /* End of SystemInitialize for SubSystem: '<S415>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S422>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_c_Init(&localB->EnabledSubsystem_j,
    &localP->EnabledSubsystem_j);

  /* End of SystemInitialize for SubSystem: '<S422>/Enabled Subsystem' */

  /* SystemInitialize for Triggered SubSystem: '<S449>/Triggered Subsystem' */
  /* SystemInitialize for SignalConversion generated from: '<S453>/In1' incorporates:
   *  Outport: '<S453>/Out1'
   */
  localB->In1 = localP->Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S449>/Triggered Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S499>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S530>/Product3' incorporates:
   *  Outport: '<S530>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3_o[0] = localP->Lykyhatkk1_Y0_e;

  /* End of SystemInitialize for SubSystem: '<S499>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S506>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S532>/Product2' incorporates:
   *  Outport: '<S532>/deltax'
   */
  localB->Product2_f[0] = localP->deltax_Y0_o;

  /* End of SystemInitialize for SubSystem: '<S506>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S499>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S530>/Product3' incorporates:
   *  Outport: '<S530>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3_o[1] = localP->Lykyhatkk1_Y0_e;

  /* End of SystemInitialize for SubSystem: '<S499>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S506>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S532>/Product2' incorporates:
   *  Outport: '<S532>/deltax'
   */
  localB->Product2_f[1] = localP->deltax_Y0_o;

  /* End of SystemInitialize for SubSystem: '<S506>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S499>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S530>/Product3' incorporates:
   *  Outport: '<S530>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3_o[2] = localP->Lykyhatkk1_Y0_e;

  /* End of SystemInitialize for SubSystem: '<S499>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S506>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S532>/Product2' incorporates:
   *  Outport: '<S532>/deltax'
   */
  localB->Product2_f[2] = localP->deltax_Y0_o;

  /* End of SystemInitialize for SubSystem: '<S506>/Enabled Subsystem' */

  /* SystemInitialize for Enabled SubSystem: '<S499>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S530>/Product3' incorporates:
   *  Outport: '<S530>/L*(y[k]-yhat[k|k-1])'
   */
  localB->Product3_o[3] = localP->Lykyhatkk1_Y0_e;

  /* End of SystemInitialize for SubSystem: '<S499>/MeasurementUpdate' */

  /* SystemInitialize for Enabled SubSystem: '<S506>/Enabled Subsystem' */
  /* SystemInitialize for Product: '<S532>/Product2' incorporates:
   *  Outport: '<S532>/deltax'
   */
  localB->Product2_f[3] = localP->deltax_Y0_o;

  /* End of SystemInitialize for SubSystem: '<S506>/Enabled Subsystem' */
}

/* Start for atomic system: '<Root>/Flight Control System' */
void flightControlSystem_FlightControlSystem_Start
  (DW_FlightControlSystem_flightControlSystem_T *localDW)
{
  /* Start for Enabled SubSystem: '<S303>/Enabled Subsystem' */
  localDW->EnabledSubsystem_MODE_g = false;

  /* End of Start for SubSystem: '<S303>/Enabled Subsystem' */

  /* Start for Enabled SubSystem: '<S368>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_o_Start(&localDW->EnabledSubsystem_k);

  /* End of Start for SubSystem: '<S368>/Enabled Subsystem' */

  /* Start for Enabled SubSystem: '<S422>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_o_Start(&localDW->EnabledSubsystem_j);

  /* End of Start for SubSystem: '<S422>/Enabled Subsystem' */

  /* Start for Enabled SubSystem: '<S506>/Enabled Subsystem' */
  localDW->EnabledSubsystem_MODE = false;

  /* End of Start for SubSystem: '<S506>/Enabled Subsystem' */

  /* Start for Enabled SubSystem: '<S499>/MeasurementUpdate' */
  localDW->MeasurementUpdate_MODE = false;

  /* End of Start for SubSystem: '<S499>/MeasurementUpdate' */

  /* Start for Enabled SubSystem: '<S159>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_h_Start(&localDW->EnabledSubsystem_d);

  /* End of Start for SubSystem: '<S159>/Enabled Subsystem' */

  /* Start for Enabled SubSystem: '<S105>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_h_Start(&localDW->EnabledSubsystem_e);

  /* End of Start for SubSystem: '<S105>/Enabled Subsystem' */

  /* Start for Enabled SubSystem: '<S51>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_Start(&localDW->EnabledSubsystem);

  /* End of Start for SubSystem: '<S51>/Enabled Subsystem' */

  /* Start for Enabled SubSystem: '<S213>/Enabled Subsystem' */
  flightControlSystem_EnabledSubsystem_Start(&localDW->EnabledSubsystem_n);

  /* End of Start for SubSystem: '<S213>/Enabled Subsystem' */

  /* Start for Enabled SubSystem: '<S152>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_c_Start(&localDW->MeasurementUpdate_jc);

  /* End of Start for SubSystem: '<S152>/MeasurementUpdate' */

  /* Start for Enabled SubSystem: '<S98>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_c_Start(&localDW->MeasurementUpdate_j);

  /* End of Start for SubSystem: '<S98>/MeasurementUpdate' */

  /* Start for Enabled SubSystem: '<S415>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_h_Start(&localDW->MeasurementUpdate_n);

  /* End of Start for SubSystem: '<S415>/MeasurementUpdate' */

  /* Start for Enabled SubSystem: '<S361>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_h_Start(&localDW->MeasurementUpdate_o);

  /* End of Start for SubSystem: '<S361>/MeasurementUpdate' */

  /* Start for Enabled SubSystem: '<S297>/MeasurementUpdate' */
  localDW->MeasurementUpdate_MODE_p = false;

  /* End of Start for SubSystem: '<S297>/MeasurementUpdate' */

  /* Start for Enabled SubSystem: '<S206>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_Start(&localDW->MeasurementUpdate_c);

  /* End of Start for SubSystem: '<S206>/MeasurementUpdate' */

  /* Start for Enabled SubSystem: '<S44>/MeasurementUpdate' */
  flightControlSystem_MeasurementUpdate_Start(&localDW->MeasurementUpdate);

  /* End of Start for SubSystem: '<S44>/MeasurementUpdate' */
}

/* Output and update for atomic system: '<Root>/Flight Control System' */
void flightControlSystem_FlightControlSystem(RT_MODEL_flightControlSystem_T *
  const flightControlSystem_M, const CommandBus *rtu_ReferenceValueServerCmds,
  const SensorsBus *rtu_Sensors, B_FlightControlSystem_flightControlSystem_T
  *localB, DW_FlightControlSystem_flightControlSystem_T *localDW,
  P_FlightControlSystem_flightControlSystem_T *localP,
  ZCE_FlightControlSystem_flightControlSystem_T *localZCE)
{
  boolean_T rtb_Compare_cm;
  boolean_T rtb_Compare_li;
  boolean_T rtb_Compare_nu;
  boolean_T rtb_Compare_or;

  /* SignalConversion generated from: '<S270>/Bus Selector7' */
  localB->vbat_V = rtu_Sensors->HALSensors.HAL_vbat_SI.vbat_V;

  /* SignalConversion generated from: '<S270>/Bus Selector1' */
  localB->FIR_IMUaccel[0] = rtu_Sensors->VisionSensors.opticalFlow_data[0];
  localB->FIR_IMUaccel[1] = rtu_Sensors->VisionSensors.opticalFlow_data[1];
  localB->FIR_IMUaccel[2] = rtu_Sensors->VisionSensors.opticalFlow_data[2];

  /* SignalConversion generated from: '<S270>/Bus Selector1' */
  localB->posVIS_data[0] = rtu_Sensors->VisionSensors.posVIS_data[0];
  localB->posVIS_data[1] = rtu_Sensors->VisionSensors.posVIS_data[1];
  localB->posVIS_data[2] = rtu_Sensors->VisionSensors.posVIS_data[2];
  localB->posVIS_data[3] = rtu_Sensors->VisionSensors.posVIS_data[3];

  /* SignalConversion generated from: '<S6>/To Workspace1' incorporates:
   *  SignalConversion generated from: '<S270>/Bus Selector1'
   *  SignalConversion generated from: '<S270>/Bus Selector3'
   *  SignalConversion generated from: '<S270>/Bus Selector4'
   *  SignalConversion generated from: '<S270>/Bus Selector5'
   *  SignalConversion generated from: '<S270>/Bus Selector6'
   * */
  localB->TmpSignalConversionAtToWorkspace1Inport1[7] =
    rtu_Sensors->VisionSensors.usePosVIS_flag;
  localB->TmpSignalConversionAtToWorkspace1Inport1[8] =
    rtu_Sensors->HALSensors.HAL_acc_SI.x;
  localB->TmpSignalConversionAtToWorkspace1Inport1[9] =
    rtu_Sensors->HALSensors.HAL_acc_SI.y;
  localB->TmpSignalConversionAtToWorkspace1Inport1[10] =
    rtu_Sensors->HALSensors.HAL_acc_SI.z;
  localB->TmpSignalConversionAtToWorkspace1Inport1[11] =
    rtu_Sensors->HALSensors.HAL_gyro_SI.x;
  localB->TmpSignalConversionAtToWorkspace1Inport1[12] =
    rtu_Sensors->HALSensors.HAL_gyro_SI.y;
  localB->TmpSignalConversionAtToWorkspace1Inport1[13] =
    rtu_Sensors->HALSensors.HAL_gyro_SI.z;
  localB->TmpSignalConversionAtToWorkspace1Inport1[14] =
    rtu_Sensors->HALSensors.HAL_pressure_SI.pressure;
  localB->TmpSignalConversionAtToWorkspace1Inport1[15] =
    rtu_Sensors->HALSensors.HAL_ultrasound_SI.altitude;

  /* DataTypeConversion: '<S6>/Data Type Conversion2' */
  localB->ManualSwitch1 = (real32_T)
    rtu_Sensors->HALSensors.HAL_vbat_SI.vbat_percentage;

  /* SignalConversion generated from: '<S270>/Bus Selector8' */
  localB->Abs5 = rtu_Sensors->HALSensors.HAL_gyro_SI.temperature;

  /* SignalConversion generated from: '<S270>/Bus Selector9' */
  localB->DiscreteTimeIntegrator_l =
    rtu_Sensors->HALSensors.HAL_acc_SI.temperature;

  /* SignalConversion generated from: '<S6>/To Workspace1' */
  localB->TmpSignalConversionAtToWorkspace1Inport1[0] = localB->FIR_IMUaccel[0];
  localB->TmpSignalConversionAtToWorkspace1Inport1[1] = localB->FIR_IMUaccel[1];
  localB->TmpSignalConversionAtToWorkspace1Inport1[2] = localB->FIR_IMUaccel[2];
  localB->TmpSignalConversionAtToWorkspace1Inport1[3] = localB->posVIS_data[0];
  localB->TmpSignalConversionAtToWorkspace1Inport1[4] = localB->posVIS_data[1];
  localB->TmpSignalConversionAtToWorkspace1Inport1[5] = localB->posVIS_data[2];
  localB->TmpSignalConversionAtToWorkspace1Inport1[6] = localB->posVIS_data[3];
  localB->TmpSignalConversionAtToWorkspace1Inport1[16] = localB->vbat_V;
  for (localB->i = 0; localB->i < 8; localB->i++) {
    /* SignalConversion generated from: '<S6>/Bus Selector2' */
    localB->rtb_SensorCalibration_c = rtu_Sensors->SensorCalibration[localB->i];

    /* SignalConversion generated from: '<S6>/To Workspace1' */
    localB->TmpSignalConversionAtToWorkspace1Inport1[localB->i + 17] =
      localB->rtb_SensorCalibration_c;
  }

  /* SignalConversion generated from: '<S6>/To Workspace1' */
  localB->TmpSignalConversionAtToWorkspace1Inport1[25] = localB->ManualSwitch1;
  localB->TmpSignalConversionAtToWorkspace1Inport1[26] = localB->Abs5;
  localB->TmpSignalConversionAtToWorkspace1Inport1[27] =
    localB->DiscreteTimeIntegrator_l;

  /* ToWorkspace: '<S6>/To Workspace1' */
  {
    double locTime = flightControlSystem_M->Timing.taskTime0
      ;
    rt_UpdateStructLogVar((StructLogVar *)localDW->ToWorkspace1_PWORK.LoggedData,
                          &locTime,
                          &localB->TmpSignalConversionAtToWorkspace1Inport1[0]);
  }

  for (localB->i = 0; localB->i < 16; localB->i++) {
    /* DataTypeConversion: '<S176>/Conversion' incorporates:
     *  Constant: '<S132>/KalmanGainM'
     */
    localB->Conversion_bf[localB->i] = (real32_T)localP->
      KalmanGainM_Value[localB->i];

    /* DataTypeConversion: '<S122>/Conversion' incorporates:
     *  Constant: '<S78>/KalmanGainM'
     */
    localB->Conversion_c[localB->i] = (real32_T)localP->
      KalmanGainM_Value_n[localB->i];

    /* DataTypeConversion: '<S121>/Conversion' incorporates:
     *  Constant: '<S78>/KalmanGainL'
     */
    localB->Conversion_i[localB->i] = (real32_T)localP->KalmanGainL_Value
      [localB->i];

    /* DataTypeConversion: '<S175>/Conversion' incorporates:
     *  Constant: '<S132>/KalmanGainL'
     */
    localB->Conversion_c0[localB->i] = (real32_T)localP->
      KalmanGainL_Value_n[localB->i];
  }

  /* DiscreteIntegrator: '<S457>/SimplyIntegrateVelocity' incorporates:
   *  Constant: '<S1>/controlModePosVsOrient'
   */
  if (localP->controlModePosVsOrient_Value &&
      (localDW->SimplyIntegrateVelocity_PrevResetState <= 0)) {
    localDW->SimplyIntegrateVelocity_DSTATE[0] =
      localP->SimplyIntegrateVelocity_IC;
    localDW->SimplyIntegrateVelocity_DSTATE[1] =
      localP->SimplyIntegrateVelocity_IC;
  }

  /* DiscreteIntegrator: '<S457>/SimplyIntegrateVelocity' */
  localB->SimplyIntegrateVelocity[0] = localDW->SimplyIntegrateVelocity_DSTATE[0];
  localB->SimplyIntegrateVelocity[1] = localDW->SimplyIntegrateVelocity_DSTATE[1];

  /* RelationalOperator: '<S278>/Compare' incorporates:
   *  Constant: '<S278>/Constant'
   *  Delay: '<S271>/Delay2'
   */
  localB->Compare = (localDW->Delay2_DSTATE > localP->outlierBelowFloor_const);

  /* Delay: '<S275>/MemoryX' incorporates:
   *  Constant: '<S275>/X0'
   *  DataTypeConversion: '<S275>/DataTypeConversionReset'
   *  Reshape: '<S275>/ReshapeX0'
   */
  localDW->icLoad = (localB->Compare || localDW->icLoad);
  if (localDW->icLoad) {
    localDW->MemoryX_DSTATE[0] = localP->X0_Value[0];
    localDW->MemoryX_DSTATE[1] = localP->X0_Value[1];
  }

  /* Gain: '<S271>/invertzaxisGain' */
  localB->invertzaxisGain = (real_T)localP->invertzaxisGain_Gain *
    rtu_Sensors->HALSensors.HAL_ultrasound_SI.altitude;

  /* DataTypeConversion: '<S273>/Data Type Conversion' */
  for (localB->i = 0; localB->i < 8; localB->i++) {
    localB->SensorCalibration[localB->i] = rtu_Sensors->SensorCalibration
      [localB->i];
  }

  /* End of DataTypeConversion: '<S273>/Data Type Conversion' */

  /* Sum: '<S273>/Sum2' */
  localB->DiscreteTimeIntegrator_l =
    rtu_Sensors->HALSensors.HAL_pressure_SI.pressure - localB->
    SensorCalibration[6];

  /* DiscreteFilter: '<S276>/pressureFilter_IIR' incorporates:
   *  Gain: '<S271>/prsToAltGain'
   */
  localB->vbat_V = (((localP->prsToAltGain_Gain *
                      localB->DiscreteTimeIntegrator_l -
                      localDW->pressureFilter_IIR_states[0] *
                      localP->pressureFilter_IIR_DenCoef[1]) -
                     localDW->pressureFilter_IIR_states[1] *
                     localP->pressureFilter_IIR_DenCoef[2]) -
                    localDW->pressureFilter_IIR_states[2] *
                    localP->pressureFilter_IIR_DenCoef[3]) /
    localP->pressureFilter_IIR_DenCoef[0];
  localB->ManualSwitch1 = ((localP->pressureFilter_IIR_NumCoef[0] *
    localB->vbat_V + localDW->pressureFilter_IIR_states[0] *
    localP->pressureFilter_IIR_NumCoef[1]) + localDW->pressureFilter_IIR_states
    [1] * localP->pressureFilter_IIR_NumCoef[2]) +
    localDW->pressureFilter_IIR_states[2] * localP->pressureFilter_IIR_NumCoef[3];

  /* DiscreteFilter: '<S276>/sonarFilter_IIR' */
  localB->sonarFilter_IIR_tmp = (((localB->invertzaxisGain -
    localDW->sonarFilter_IIR_states[0] * localP->sonarFilter_IIR_DenCoef[1]) -
    localDW->sonarFilter_IIR_states[1] * localP->sonarFilter_IIR_DenCoef[2]) -
    localDW->sonarFilter_IIR_states[2] * localP->sonarFilter_IIR_DenCoef[3]) /
    localP->sonarFilter_IIR_DenCoef[0];

  /* Saturate: '<S276>/SaturationSonar' */
  if (localB->invertzaxisGain > -flightControlSystem_P.Sensors.altSensorMin) {
    localB->Step4 = -flightControlSystem_P.Sensors.altSensorMin;
  } else if (localB->invertzaxisGain < localP->SaturationSonar_LowerSat) {
    localB->Step4 = localP->SaturationSonar_LowerSat;
  } else {
    localB->Step4 = localB->invertzaxisGain;
  }

  /* Logic: '<S276>/nicemeasurementor newupdateneeded' incorporates:
   *  Abs: '<S276>/Absestdiff'
   *  Abs: '<S276>/Absestdiff1'
   *  Abs: '<S276>/Absestdiff2'
   *  Constant: '<S330>/Constant'
   *  Constant: '<S331>/Constant'
   *  Constant: '<S332>/Constant'
   *  Constant: '<S333>/Constant'
   *  Delay: '<S271>/Delay2'
   *  DiscreteFilter: '<S276>/pressureFilter_IIR'
   *  DiscreteFilter: '<S276>/sonarFilter_IIR'
   *  Logic: '<S276>/NOT'
   *  Logic: '<S276>/findingoutliers'
   *  Logic: '<S276>/newupdateneeded'
   *  RelationalOperator: '<S330>/Compare'
   *  RelationalOperator: '<S331>/Compare'
   *  RelationalOperator: '<S332>/Compare'
   *  RelationalOperator: '<S333>/Compare'
   *  Saturate: '<S276>/SaturationSonar'
   *  Sum: '<S276>/Add'
   *  Sum: '<S276>/Add1'
   *  Sum: '<S276>/Add2'
   */
  localB->nicemeasurementornewupdateneeded = ((fabs(localDW->Delay2_DSTATE -
    localB->Step4) <= localP->outlierJump_const) && (localB->invertzaxisGain <
    -flightControlSystem_P.Sensors.altSensorMin) && ((!(fabs
    (localB->ManualSwitch1 - localDW->Delay2_DSTATE) >=
    localP->currentEstimateVeryOffFromPressure_const)) || (!(fabs
    ((((localP->sonarFilter_IIR_NumCoef[0] * localB->sonarFilter_IIR_tmp +
        localDW->sonarFilter_IIR_states[0] * localP->sonarFilter_IIR_NumCoef[1])
       + localDW->sonarFilter_IIR_states[1] * localP->sonarFilter_IIR_NumCoef[2])
      + localDW->sonarFilter_IIR_states[2] * localP->sonarFilter_IIR_NumCoef[3])
     - localDW->Delay2_DSTATE) >= localP->currentStateVeryOffsonarflt_const))));

  /* Outputs for Enabled SubSystem: '<S303>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S329>/Enable'
   */
  /* DataTypeConversion: '<S275>/DataTypeConversionEnable' */
  if (localB->nicemeasurementornewupdateneeded) {
    localDW->EnabledSubsystem_MODE_g = true;

    /* Sum: '<S329>/Add1' incorporates:
     *  Constant: '<S275>/C'
     *  Delay: '<S275>/MemoryX'
     *  Product: '<S329>/Product'
     *  Reshape: '<S275>/Reshapey'
     */
    localB->Step4 = localB->invertzaxisGain - (localP->C_Value[0] *
      localDW->MemoryX_DSTATE[0] + localP->C_Value[1] * localDW->MemoryX_DSTATE
      [1]);

    /* Product: '<S329>/Product2' incorporates:
     *  Constant: '<S279>/KalmanGainM'
     *  DataTypeConversion: '<S320>/Conversion'
     */
    localB->Product2[0] = localP->KalmanGainM_Value_f[0] * localB->Step4;
    localB->Product2[1] = localP->KalmanGainM_Value_f[1] * localB->Step4;
  } else if (localDW->EnabledSubsystem_MODE_g) {
    /* Disable for Product: '<S329>/Product2' incorporates:
     *  Outport: '<S329>/deltax'
     */
    localB->Product2[0] = localP->deltax_Y0;
    localB->Product2[1] = localP->deltax_Y0;
    localDW->EnabledSubsystem_MODE_g = false;
  }

  /* End of Outputs for SubSystem: '<S303>/Enabled Subsystem' */

  /* Reshape: '<S275>/Reshapexhat' incorporates:
   *  Delay: '<S275>/MemoryX'
   *  Sum: '<S303>/Add'
   */
  localDW->Delay2_DSTATE = localB->Product2[0] + localDW->MemoryX_DSTATE[0];

  /* DataTypeConversion: '<S271>/Data Type Conversion' incorporates:
   *  Reshape: '<S275>/Reshapexhat'
   */
  localB->DataTypeConversion = (real32_T)localDW->Delay2_DSTATE;

  /* Delay: '<S341>/MemoryX' incorporates:
   *  Constant: '<S341>/X0'
   *  Reshape: '<S341>/ReshapeX0'
   */
  if (localDW->icLoad_a) {
    localDW->MemoryX_DSTATE_l[0] = localP->X0_Value_f[0];
    localDW->MemoryX_DSTATE_l[1] = localP->X0_Value_f[1];
  }

  /* Bias: '<S273>/Assuming that the  preflight calibration was done at level orientation' */
  for (localB->i = 0; localB->i < 6; localB->i++) {
    localB->Sum1_c[localB->i] = localB->SensorCalibration[localB->i] +
      localP->
      Assumingthatthepreflightcalibrationwasdoneatlevelorientation_Bi[localB->i];
  }

  /* End of Bias: '<S273>/Assuming that the  preflight calibration was done at level orientation' */

  /* Sum: '<S273>/Sum1' */
  localB->inverseIMU_gain[0] = rtu_Sensors->HALSensors.HAL_acc_SI.x -
    localB->Sum1_c[0];
  localB->inverseIMU_gain[1] = rtu_Sensors->HALSensors.HAL_acc_SI.y -
    localB->Sum1_c[1];
  localB->inverseIMU_gain[2] = rtu_Sensors->HALSensors.HAL_acc_SI.z -
    localB->Sum1_c[2];
  localB->inverseIMU_gain[3] = rtu_Sensors->HALSensors.HAL_gyro_SI.x -
    localB->Sum1_c[3];
  localB->inverseIMU_gain[4] = rtu_Sensors->HALSensors.HAL_gyro_SI.y -
    localB->Sum1_c[4];
  localB->inverseIMU_gain[5] = rtu_Sensors->HALSensors.HAL_gyro_SI.z -
    localB->Sum1_c[5];
  for (localB->i = 0; localB->i < 6; localB->i++) {
    /* Gain: '<S273>/inverseIMU_gain' incorporates:
     *  Sum: '<S273>/Sum1'
     */
    localB->inverseIMU_gain[localB->i] *= localP->inverseIMU_gain_Gain[localB->i];
  }

  /* DiscreteFir: '<S273>/FIR_IMUaccel' */
  localB->rtb_SensorCalibration_c = localB->inverseIMU_gain[0] *
    localP->FIR_IMUaccel_Coefficients[0];
  localB->i = 1;
  localB->j = localDW->FIR_IMUaccel_circBuf;
  while (localB->j < 5) {
    localB->rtb_SensorCalibration_c += localDW->FIR_IMUaccel_states[localB->j] *
      localP->FIR_IMUaccel_Coefficients[localB->i];
    localB->i++;
    localB->j++;
  }

  localB->j = 0;
  while (localB->j < localDW->FIR_IMUaccel_circBuf) {
    localB->rtb_SensorCalibration_c += localDW->FIR_IMUaccel_states[localB->j] *
      localP->FIR_IMUaccel_Coefficients[localB->i];
    localB->i++;
    localB->j++;
  }

  localB->FIR_IMUaccel[0] = localB->rtb_SensorCalibration_c;

  /* Math: '<S340>/Math Function' incorporates:
   *  Constant: '<S340>/Constant'
   *  DiscreteFir: '<S273>/FIR_IMUaccel'
   */
  if ((localB->rtb_SensorCalibration_c < 0.0F) && (localP->Constant_Value_k >
       (real32_T)floor(localP->Constant_Value_k))) {
    localB->TmpSignalConversionAtToWorkspaceInport1_of[0] =
      -flightControlSystem_rt_powf_snf(-localB->rtb_SensorCalibration_c,
      localP->Constant_Value_k, localB);
  } else {
    localB->TmpSignalConversionAtToWorkspaceInport1_of[0] =
      flightControlSystem_rt_powf_snf(localB->rtb_SensorCalibration_c,
      localP->Constant_Value_k, localB);
  }

  /* DiscreteFir: '<S273>/FIR_IMUaccel' */
  localB->rtb_SensorCalibration_c = localP->FIR_IMUaccel_Coefficients[0] *
    localB->inverseIMU_gain[1];
  localB->i = 1;
  localB->j = localDW->FIR_IMUaccel_circBuf;
  while (localB->j < 5) {
    localB->rtb_SensorCalibration_c += localDW->FIR_IMUaccel_states[localB->j +
      5] * localP->FIR_IMUaccel_Coefficients[localB->i];
    localB->i++;
    localB->j++;
  }

  localB->j = 0;
  while (localB->j < localDW->FIR_IMUaccel_circBuf) {
    localB->rtb_SensorCalibration_c += localDW->FIR_IMUaccel_states[localB->j +
      5] * localP->FIR_IMUaccel_Coefficients[localB->i];
    localB->i++;
    localB->j++;
  }

  localB->FIR_IMUaccel[1] = localB->rtb_SensorCalibration_c;

  /* Math: '<S340>/Math Function' incorporates:
   *  Constant: '<S340>/Constant'
   *  DiscreteFir: '<S273>/FIR_IMUaccel'
   */
  if ((localB->rtb_SensorCalibration_c < 0.0F) && (localP->Constant_Value_k >
       (real32_T)floor(localP->Constant_Value_k))) {
    localB->TmpSignalConversionAtToWorkspaceInport1_of[1] =
      -flightControlSystem_rt_powf_snf(-localB->rtb_SensorCalibration_c,
      localP->Constant_Value_k, localB);
  } else {
    localB->TmpSignalConversionAtToWorkspaceInport1_of[1] =
      flightControlSystem_rt_powf_snf(localB->rtb_SensorCalibration_c,
      localP->Constant_Value_k, localB);
  }

  /* DiscreteFir: '<S273>/FIR_IMUaccel' */
  localB->rtb_SensorCalibration_c = localP->FIR_IMUaccel_Coefficients[0] *
    localB->inverseIMU_gain[2];
  localB->i = 1;
  localB->j = localDW->FIR_IMUaccel_circBuf;
  while (localB->j < 5) {
    localB->rtb_SensorCalibration_c += localDW->FIR_IMUaccel_states[localB->j +
      10] * localP->FIR_IMUaccel_Coefficients[localB->i];
    localB->i++;
    localB->j++;
  }

  localB->j = 0;
  while (localB->j < localDW->FIR_IMUaccel_circBuf) {
    localB->rtb_SensorCalibration_c += localDW->FIR_IMUaccel_states[localB->j +
      10] * localP->FIR_IMUaccel_Coefficients[localB->i];
    localB->i++;
    localB->j++;
  }

  localB->FIR_IMUaccel[2] = localB->rtb_SensorCalibration_c;

  /* Math: '<S340>/Math Function' incorporates:
   *  Constant: '<S340>/Constant'
   *  DiscreteFir: '<S273>/FIR_IMUaccel'
   */
  if ((localB->rtb_SensorCalibration_c < 0.0F) && (localP->Constant_Value_k >
       (real32_T)floor(localP->Constant_Value_k))) {
    localB->TmpSignalConversionAtToWorkspaceInport1_of[2] =
      -flightControlSystem_rt_powf_snf(-localB->rtb_SensorCalibration_c,
      localP->Constant_Value_k, localB);
  } else {
    localB->TmpSignalConversionAtToWorkspaceInport1_of[2] =
      flightControlSystem_rt_powf_snf(localB->rtb_SensorCalibration_c,
      localP->Constant_Value_k, localB);
  }

  /* Gain: '<S337>/Gain2' */
  localB->Abs5 = localP->Gain2_Gain * localB->FIR_IMUaccel[0];

  /* Trigonometry: '<S337>/Trigonometric Function1' */
  if (localB->Abs5 > 1.0F) {
    localB->Abs5 = 1.0F;
  } else if (localB->Abs5 < -1.0F) {
    localB->Abs5 = -1.0F;
  }

  /* Trigonometry: '<S337>/Trigonometric Function1' */
  localB->TrigonometricFunction1 = (real32_T)asin(localB->Abs5);

  /* Sqrt: '<S340>/Sqrt' incorporates:
   *  Sum: '<S340>/Sum of Elements'
   */
  localB->Abs5 = (real32_T)sqrt
    ((localB->TmpSignalConversionAtToWorkspaceInport1_of[0] +
      localB->TmpSignalConversionAtToWorkspaceInport1_of[1]) +
     localB->TmpSignalConversionAtToWorkspaceInport1_of[2]);

  /* Logic: '<S272>/Logical Operator' incorporates:
   *  Constant: '<S335>/Constant'
   *  Constant: '<S336>/Constant'
   *  RelationalOperator: '<S335>/Compare'
   *  RelationalOperator: '<S336>/Compare'
   */
  localB->LogicalOperator = (int16_T)((localB->Abs5 >
    localP->CompareToConstant_const) && (localB->Abs5 <
    localP->CompareToConstant1_const));

  /* DataTypeConversion: '<S385>/Conversion' incorporates:
   *  Constant: '<S342>/KalmanGainM'
   */
  localB->Conversion_n[0] = (real32_T)localP->KalmanGainM_Value_p[0];
  localB->Conversion_n[1] = (real32_T)localP->KalmanGainM_Value_p[1];

  /* Outputs for Enabled SubSystem: '<S368>/Enabled Subsystem' */
  /* DataTypeConversion: '<S341>/DataTypeConversionEnable' incorporates:
   *  Constant: '<S341>/C'
   *  Delay: '<S341>/MemoryX'
   *  Reshape: '<S341>/Reshapey'
   */
  flightControlSystem_EnabledSubsystem_k((localB->LogicalOperator != 0),
    localB->Conversion_n, localP->C_Value_j, localB->TrigonometricFunction1,
    localDW->MemoryX_DSTATE_l, &localB->EnabledSubsystem_k,
    &localDW->EnabledSubsystem_k, &localP->EnabledSubsystem_k);

  /* End of Outputs for SubSystem: '<S368>/Enabled Subsystem' */

  /* Delay: '<S395>/MemoryX' incorporates:
   *  Constant: '<S395>/X0'
   *  Reshape: '<S395>/ReshapeX0'
   */
  if (localDW->icLoad_n) {
    localDW->MemoryX_DSTATE_p[0] = localP->X0_Value_fi[0];
    localDW->MemoryX_DSTATE_p[1] = localP->X0_Value_fi[1];
  }

  /* Trigonometry: '<S338>/Trigonometric Function' incorporates:
   *  DiscreteFir: '<S273>/FIR_IMUaccel'
   *  Product: '<S338>/Divide'
   */
  localB->TrigonometricFunction = (real32_T)atan(localB->FIR_IMUaccel[1] /
    localB->rtb_SensorCalibration_c);

  /* DataTypeConversion: '<S439>/Conversion' incorporates:
   *  Constant: '<S396>/KalmanGainM'
   */
  localB->Conversion_f[0] = (real32_T)localP->KalmanGainM_Value_e[0];
  localB->Conversion_f[1] = (real32_T)localP->KalmanGainM_Value_e[1];

  /* Outputs for Enabled SubSystem: '<S422>/Enabled Subsystem' */
  /* DataTypeConversion: '<S395>/DataTypeConversionEnable' incorporates:
   *  Constant: '<S395>/C'
   *  Delay: '<S395>/MemoryX'
   *  Reshape: '<S395>/Reshapey'
   */
  flightControlSystem_EnabledSubsystem_k((localB->LogicalOperator != 0),
    localB->Conversion_f, localP->C_Value_a, localB->TrigonometricFunction,
    localDW->MemoryX_DSTATE_p, &localB->EnabledSubsystem_j,
    &localDW->EnabledSubsystem_j, &localP->EnabledSubsystem_j);

  /* End of Outputs for SubSystem: '<S422>/Enabled Subsystem' */

  /* DataTypeConversion: '<S272>/Data Type Conversion3' incorporates:
   *  Delay: '<S341>/MemoryX'
   *  Delay: '<S395>/MemoryX'
   *  DiscreteIntegrator: '<S339>/Discrete-Time Integrator'
   *  Sum: '<S368>/Add'
   *  Sum: '<S422>/Add'
   */
  localB->DataTypeConversion3[0] = localDW->DiscreteTimeIntegrator_DSTATE_p;
  localB->DataTypeConversion3[1] = localB->EnabledSubsystem_k.Product2[0] +
    localDW->MemoryX_DSTATE_l[0];
  localB->DataTypeConversion3[2] = localB->EnabledSubsystem_j.Product2[0] +
    localDW->MemoryX_DSTATE_p[0];

  /* DiscreteFilter: '<S273>/IIR_IMUgyro_r' */
  localB->Abs5 = localB->inverseIMU_gain[5];
  for (localB->j = 0; localB->j < 5; localB->j++) {
    localB->Abs5 -= localP->IIR_IMUgyro_r_DenCoef[localB->j + 1] *
      localDW->IIR_IMUgyro_r_states[localB->j];
  }

  localB->DiscreteTimeIntegrator_l = localB->Abs5 /
    localP->IIR_IMUgyro_r_DenCoef[0];
  localB->Abs5 = localP->IIR_IMUgyro_r_NumCoef[0] *
    localB->DiscreteTimeIntegrator_l;
  for (localB->j = 0; localB->j < 5; localB->j++) {
    localB->Abs5 += localP->IIR_IMUgyro_r_NumCoef[localB->j + 1] *
      localDW->IIR_IMUgyro_r_states[localB->j];
  }

  /* RelationalOperator: '<S451>/Compare' incorporates:
   *  Constant: '<S451>/Constant'
   *  UnitDelay: '<S452>/Output'
   */
  localB->Compare_e3 = (localDW->Output_DSTATE ==
                        localP->CompareToConstant_const_p);

  /* Outputs for Triggered SubSystem: '<S449>/Triggered Subsystem' incorporates:
   *  TriggerPort: '<S453>/Trigger'
   */
  if (((localZCE->TriggeredSubsystem_Trig_ZCE == POS_ZCSIG) != (int32_T)
       localB->Compare_e3) && (localZCE->TriggeredSubsystem_Trig_ZCE !=
       UNINITIALIZED_ZCSIG)) {
    /* SignalConversion generated from: '<S453>/In1' */
    localB->In1 = rtu_Sensors->HALSensors.HAL_gyro_SI.temperature;
  }

  localZCE->TriggeredSubsystem_Trig_ZCE = localB->Compare_e3;

  /* End of Outputs for SubSystem: '<S449>/Triggered Subsystem' */

  /* ManualSwitch: '<S449>/Disable temperature compensation' incorporates:
   *  Constant: '<S449>/Constant'
   *  Gain: '<S449>/Gain'
   */
  if (localP->Disabletemperaturecompensation_CurrentSetting == 1) {
    /* Sum: '<S449>/Subtract' */
    localB->Subtract_c = rtu_Sensors->HALSensors.HAL_gyro_SI.temperature -
      localB->In1;
    localB->Step4 = localP->Gain_Gain_b * localB->Subtract_c;
  } else {
    localB->Step4 = localP->Constant_Value;
  }

  /* End of ManualSwitch: '<S449>/Disable temperature compensation' */

  /* Sum: '<S449>/Subtract1' incorporates:
   *  DataTypeConversion: '<S449>/Data Type Conversion1'
   *  DiscreteFilter: '<S273>/IIR_IMUgyro_r'
   */
  localB->Subtract_c = localB->Abs5 - (real32_T)localB->Step4;

  /* SignalConversion generated from: '<S272>/To Workspace' incorporates:
   *  Constant: '<S339>/Constant'
   *  Delay: '<S341>/MemoryX'
   *  Delay: '<S395>/MemoryX'
   *  Sum: '<S368>/Add'
   *  Sum: '<S422>/Add'
   */
  localB->TmpSignalConversionAtToWorkspaceInport1_of[0] =
    localB->EnabledSubsystem_j.Product2[1] + localDW->MemoryX_DSTATE_p[1];
  localB->TmpSignalConversionAtToWorkspaceInport1_of[1] =
    localB->EnabledSubsystem_k.Product2[1] + localDW->MemoryX_DSTATE_l[1];
  localB->TmpSignalConversionAtToWorkspaceInport1_of[2] =
    localP->Constant_Value_f;

  /* Sum: '<S272>/Subtract' */
  localB->Subtract[0] = localB->inverseIMU_gain[3] -
    localB->TmpSignalConversionAtToWorkspaceInport1_of[0];
  localB->Subtract[1] = localB->inverseIMU_gain[4] -
    localB->TmpSignalConversionAtToWorkspaceInport1_of[1];
  localB->Subtract[2] = localB->Subtract_c -
    localB->TmpSignalConversionAtToWorkspaceInport1_of[2];

  /* Delay: '<S461>/MemoryX' incorporates:
   *  Constant: '<S461>/X0'
   *  Reshape: '<S461>/ReshapeX0'
   */
  if (localDW->icLoad_k) {
    localDW->MemoryX_DSTATE_a[0] = localP->X0_Value_e[0];
    localDW->MemoryX_DSTATE_a[1] = localP->X0_Value_e[1];
    localDW->MemoryX_DSTATE_a[2] = localP->X0_Value_e[2];
    localDW->MemoryX_DSTATE_a[3] = localP->X0_Value_e[3];
  }

  /* Switch: '<S462>/Switch' incorporates:
   *  Constant: '<S533>/Constant'
   *  Gain: '<S462>/opticalFlowErrorCorrect'
   *  RelationalOperator: '<S533>/Compare'
   *  UnitDelay: '<S534>/Output'
   */
  if (localDW->Output_DSTATE_i < localP->CompareToConstant_const_mg) {
    localB->u_b[0] = rtu_Sensors->VisionSensors.opticalFlow_data[0];
    localB->u_b[1] = rtu_Sensors->VisionSensors.opticalFlow_data[1];
    localB->u_b[2] = rtu_Sensors->VisionSensors.opticalFlow_data[2];
  } else {
    /* Gain: '<S462>/Gain' */
    localB->Abs5 = localP->Gain_Gain_h * localB->DataTypeConversion;

    /* Product: '<S462>/ ' */
    localB->rtb_sincos_o1_idx_0 = rtu_Sensors->VisionSensors.opticalFlow_data[0]
      * localB->Abs5;
    localB->u_b[0] = localP->opticalFlowErrorCorrect_Gain *
      localB->rtb_sincos_o1_idx_0;

    /* Product: '<S462>/ ' incorporates:
     *  Gain: '<S462>/opticalFlowErrorCorrect'
     */
    localB->rtb_sincos_o1_idx_0 = rtu_Sensors->VisionSensors.opticalFlow_data[1]
      * localB->Abs5;
    localB->u_b[1] = localP->opticalFlowErrorCorrect_Gain *
      localB->rtb_sincos_o1_idx_0;

    /* Product: '<S462>/ ' incorporates:
     *  Gain: '<S462>/opticalFlowErrorCorrect'
     */
    localB->rtb_sincos_o1_idx_0 = rtu_Sensors->VisionSensors.opticalFlow_data[2]
      * localB->Abs5;
    localB->u_b[2] = localP->opticalFlowErrorCorrect_Gain *
      localB->rtb_sincos_o1_idx_0;
  }

  /* End of Switch: '<S462>/Switch' */

  /* Abs: '<S459>/Abs' */
  localB->Abs5 = (real32_T)fabs(localB->DataTypeConversion);

  /* Gain: '<S456>/Gain' incorporates:
   *  Gain: '<S459>/Gain1'
   *  Product: '<S459>/prod'
   */
  localB->Conversion_f[0] = localB->Abs5 * localB->Subtract[1] *
    localP->Gain1_Gain * localP->Gain_Gain_i3;
  localB->Conversion_f[1] = localB->Abs5 * localB->Subtract[0] *
    localP->Gain_Gain_i3;
  for (localB->i = 0; localB->i < 2; localB->i++) {
    /* Sum: '<S456>/angular velocity compensation' */
    localB->rtb_sincos_o1_idx_0 = localB->u_b[localB->i];

    /* Sum: '<S456>/angular velocity compensation' */
    localB->angularvelocitycompensation[localB->i] = localB->rtb_sincos_o1_idx_0
      + localB->Conversion_f[localB->i];

    /* DiscreteFilter: '<S460>/IIRgyroz' */
    localB->memOffset = localB->i * 5;
    localB->Abs5 = localB->inverseIMU_gain[localB->i + 3];
    for (localB->j = 0; localB->j < 5; localB->j++) {
      localB->Abs5 -= localP->IIRgyroz_DenCoef[localB->j + 1] *
        localDW->IIRgyroz_states[localB->memOffset + localB->j];
    }

    localB->Abs5 /= localP->IIRgyroz_DenCoef[0];
    localDW->IIRgyroz_tmp[localB->i] = localB->Abs5;
    localB->Abs5 *= localP->IIRgyroz_NumCoef[0];
    for (localB->j = 0; localB->j < 5; localB->j++) {
      localB->Abs5 += localP->IIRgyroz_NumCoef[localB->j + 1] *
        localDW->IIRgyroz_states[localB->memOffset + localB->j];
    }

    /* SampleTimeMath: '<S468>/TSamp' incorporates:
     *  DiscreteFilter: '<S460>/IIRgyroz'
     *
     * About '<S468>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     *   */
    localB->Abs5 *= localP->TSamp_WtEt;
    localB->Conversion_n[localB->i] = localB->Abs5;

    /* Sum: '<S468>/Diff' incorporates:
     *  UnitDelay: '<S468>/UD'
     */
    localDW->UD_DSTATE[localB->i] = localB->Abs5 - localDW->UD_DSTATE[localB->i];

    /* Sum: '<S460>/Add' incorporates:
     *  Delay: '<S456>/Delay'
     */
    localB->Conversion_f[localB->i] = localB->rtb_sincos_o1_idx_0 -
      localDW->Delay_DSTATE[localB->i];
  }

  /* Logic: '<S460>/Logical Operator3' incorporates:
   *  Abs: '<S460>/Abs'
   *  Abs: '<S460>/Abs1'
   *  Abs: '<S460>/Abs2'
   *  Abs: '<S460>/Abs3'
   *  Abs: '<S460>/Abs4'
   *  Abs: '<S460>/Abs5'
   *  Abs: '<S460>/Abs6'
   *  Abs: '<S460>/Abs7'
   *  Abs: '<S460>/Abs8'
   *  Abs: '<S460>/Abs9'
   *  Constant: '<S469>/Constant'
   *  Constant: '<S470>/Constant'
   *  Constant: '<S471>/Constant'
   *  Constant: '<S472>/Constant'
   *  Constant: '<S473>/Constant'
   *  Constant: '<S474>/Constant'
   *  Constant: '<S475>/Constant'
   *  Constant: '<S476>/Constant'
   *  Constant: '<S477>/Constant'
   *  Constant: '<S478>/Constant'
   *  Constant: '<S479>/Constant'
   *  Logic: '<S460>/Logical Operator'
   *  Logic: '<S460>/Logical Operator1'
   *  Logic: '<S460>/Logical Operator2'
   *  RelationalOperator: '<S469>/Compare'
   *  RelationalOperator: '<S470>/Compare'
   *  RelationalOperator: '<S471>/Compare'
   *  RelationalOperator: '<S472>/Compare'
   *  RelationalOperator: '<S473>/Compare'
   *  RelationalOperator: '<S474>/Compare'
   *  RelationalOperator: '<S475>/Compare'
   *  RelationalOperator: '<S476>/Compare'
   *  RelationalOperator: '<S477>/Compare'
   *  RelationalOperator: '<S478>/Compare'
   *  RelationalOperator: '<S479>/Compare'
   */
  localB->LogicalOperator3 = (((((real32_T)fabs(localB->DataTypeConversion3[1]) <=
    localP->maxp_const) && ((real32_T)fabs(localB->DataTypeConversion3[2]) <=
    localP->maxq_const) && ((real32_T)fabs(localB->inverseIMU_gain[3]) <=
    localP->maxw1_const) && ((real32_T)fabs(localB->inverseIMU_gain[4]) <=
    localP->maxw2_const) && ((real32_T)fabs(localDW->UD_DSTATE[0]) <=
    localP->maxdw1_const) && ((real32_T)fabs(localDW->UD_DSTATE[1]) <=
    localP->maxdw2_const)) || (((real32_T)fabs(localB->inverseIMU_gain[3]) <=
    localP->maxp2_const) && ((real32_T)fabs(localB->inverseIMU_gain[4]) <=
    localP->maxq2_const))) && ((real32_T)fabs(localB->Conversion_f[0]) <=
    localP->maxw3_const) && ((real32_T)fabs(localB->Conversion_f[1]) <=
    localP->maxw4_const) && (localB->DataTypeConversion <=
    localP->minHeightforOF_const));

  /* Outputs for Enabled SubSystem: '<S506>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S532>/Enable'
   */
  /* DataTypeConversion: '<S461>/DataTypeConversionEnable' */
  if (localB->LogicalOperator3) {
    localDW->EnabledSubsystem_MODE = true;

    /* Delay: '<S461>/MemoryX' incorporates:
     *  Constant: '<S461>/C'
     *  Product: '<S532>/Product'
     */
    localB->rtb_pitchrollerror_l_idx_0 = localDW->MemoryX_DSTATE_a[1];
    localB->rtb_sincos_o1_idx_1 = localDW->MemoryX_DSTATE_a[0];
    localB->rtb_sincos_o1_idx_2 = localDW->MemoryX_DSTATE_a[2];
    localB->Bias_k = localDW->MemoryX_DSTATE_a[3];

    /* Product: '<S532>/Product2' */
    localB->rtb_sincos_o1_idx_0 = 0.0F;
    localB->Bias1_c = 0.0F;
    localB->Product2_f_b = 0.0F;
    localB->Product2_f_p = 0.0F;
    for (localB->i = 0; localB->i < 2; localB->i++) {
      /* Sum: '<S532>/Add1' incorporates:
       *  Constant: '<S461>/C'
       *  Delay: '<S461>/MemoryX'
       *  Product: '<S532>/Product'
       *  Reshape: '<S461>/Reshapey'
       */
      localB->Abs5 = localB->angularvelocitycompensation[localB->i] -
        (((localP->C_Value_p[localB->i + 2] * localB->rtb_pitchrollerror_l_idx_0
           + localP->C_Value_p[localB->i] * localB->rtb_sincos_o1_idx_1) +
          localP->C_Value_p[localB->i + 4] * localB->rtb_sincos_o1_idx_2) +
         localP->C_Value_p[localB->i + 6] * localB->Bias_k);

      /* Product: '<S532>/Product2' incorporates:
       *  Constant: '<S480>/KalmanGainM'
       *  DataTypeConversion: '<S523>/Conversion'
       */
      localB->j = localB->i << 2;
      localB->rtb_sincos_o1_idx_0 += (real32_T)localP->
        KalmanGainM_Value_d[localB->j] * localB->Abs5;
      localB->Bias1_c += (real32_T)localP->KalmanGainM_Value_d[localB->j + 1] *
        localB->Abs5;
      localB->Product2_f_b += (real32_T)localP->KalmanGainM_Value_d[localB->j +
        2] * localB->Abs5;
      localB->Product2_f_p += (real32_T)localP->KalmanGainM_Value_d[localB->j +
        3] * localB->Abs5;
    }

    /* Product: '<S532>/Product2' */
    localB->Product2_f[3] = localB->Product2_f_p;
    localB->Product2_f[2] = localB->Product2_f_b;
    localB->Product2_f[1] = localB->Bias1_c;
    localB->Product2_f[0] = localB->rtb_sincos_o1_idx_0;
  } else if (localDW->EnabledSubsystem_MODE) {
    /* Disable for Product: '<S532>/Product2' incorporates:
     *  Outport: '<S532>/deltax'
     */
    localB->Product2_f[0] = localP->deltax_Y0_o;
    localB->Product2_f[1] = localP->deltax_Y0_o;
    localB->Product2_f[2] = localP->deltax_Y0_o;
    localB->Product2_f[3] = localP->deltax_Y0_o;
    localDW->EnabledSubsystem_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S506>/Enabled Subsystem' */

  /* Reshape: '<S461>/Reshapexhat' incorporates:
   *  Delay: '<S461>/MemoryX'
   *  Sum: '<S506>/Add'
   */
  localB->Reshapexhat[0] = localB->Product2_f[0] + localDW->MemoryX_DSTATE_a[0];
  localB->Reshapexhat[1] = localB->Product2_f[1] + localDW->MemoryX_DSTATE_a[1];
  localB->Reshapexhat[2] = localB->Product2_f[2] + localDW->MemoryX_DSTATE_a[2];
  localB->Reshapexhat[3] = localB->Product2_f[3] + localDW->MemoryX_DSTATE_a[3];

  /* Trigonometry: '<S277>/sincos' */
  localB->rtb_sincos_o1_idx_0 = (real32_T)sin(localB->DataTypeConversion3[0]);
  localB->sincos_o1_g[0] = (real32_T)cos(localB->DataTypeConversion3[0]);
  localB->rtb_sincos_o1_idx_1 = (real32_T)sin(localB->DataTypeConversion3[1]);
  localB->sincos_o1_g[1] = (real32_T)cos(localB->DataTypeConversion3[1]);
  localB->rtb_sincos_o1_idx_2 = (real32_T)sin(localB->DataTypeConversion3[2]);
  localB->sincos_o1_g[2] = (real32_T)cos(localB->DataTypeConversion3[2]);

  /* Fcn: '<S277>/Fcn11' */
  localB->VectorConcatenate[0] = localB->sincos_o1_g[0] * localB->sincos_o1_g[1];

  /* Fcn: '<S277>/Fcn21' incorporates:
   *  Fcn: '<S277>/Fcn22'
   */
  localB->Abs5 = localB->rtb_sincos_o1_idx_1 * localB->rtb_sincos_o1_idx_2;
  localB->VectorConcatenate[1] = localB->Abs5 * localB->sincos_o1_g[0] -
    localB->rtb_sincos_o1_idx_0 * localB->sincos_o1_g[2];

  /* Fcn: '<S277>/Fcn31' incorporates:
   *  Fcn: '<S277>/Fcn32'
   */
  localB->rtb_pitchrollerror_l_idx_0 = localB->rtb_sincos_o1_idx_1 *
    localB->sincos_o1_g[2];
  localB->VectorConcatenate[2] = localB->rtb_pitchrollerror_l_idx_0 *
    localB->sincos_o1_g[0] + localB->rtb_sincos_o1_idx_0 *
    localB->rtb_sincos_o1_idx_2;

  /* Fcn: '<S277>/Fcn12' */
  localB->VectorConcatenate[3] = localB->rtb_sincos_o1_idx_0 *
    localB->sincos_o1_g[1];

  /* Fcn: '<S277>/Fcn22' */
  localB->VectorConcatenate[4] = localB->Abs5 * localB->rtb_sincos_o1_idx_0 +
    localB->sincos_o1_g[0] * localB->sincos_o1_g[2];

  /* Fcn: '<S277>/Fcn32' */
  localB->VectorConcatenate[5] = localB->rtb_pitchrollerror_l_idx_0 *
    localB->rtb_sincos_o1_idx_0 - localB->sincos_o1_g[0] *
    localB->rtb_sincos_o1_idx_2;

  /* Fcn: '<S277>/Fcn13' */
  localB->VectorConcatenate[6] = -localB->rtb_sincos_o1_idx_1;

  /* Fcn: '<S277>/Fcn23' */
  localB->VectorConcatenate[7] = localB->sincos_o1_g[1] *
    localB->rtb_sincos_o1_idx_2;

  /* Fcn: '<S277>/Fcn33' */
  localB->VectorConcatenate[8] = localB->sincos_o1_g[1] * localB->sincos_o1_g[2];

  /* SignalConversion generated from: '<S271>/Product1' incorporates:
   *  Delay: '<S275>/MemoryX'
   *  Delay: '<S7>/Delay1'
   *  Sum: '<S303>/Add'
   */
  localB->rtb_FIR_IMUaccel_m[0] = localDW->Delay1_DSTATE[0];
  localB->rtb_FIR_IMUaccel_m[1] = localDW->Delay1_DSTATE[1];
  localB->rtb_FIR_IMUaccel_m[2] = localB->Product2[1] + localDW->MemoryX_DSTATE
    [1];

  /* Product: '<S271>/Product1' incorporates:
   *  Reshape: '<S334>/Reshape (9) to [3x3] column-major'
   */
  localB->Saturation = 0.0;
  for (localB->i = 0; localB->i < 3; localB->i++) {
    localB->Saturation += localB->VectorConcatenate[3 * localB->i + 2] *
      localB->rtb_FIR_IMUaccel_m[localB->i];
  }

  /* End of Product: '<S271>/Product1' */

  /* DataTypeConversion: '<S271>/Data Type Conversion2' */
  localB->DataTypeConversion2 = (real32_T)localB->Saturation;

  /* SignalConversion generated from: '<S1>/To Workspace' */
  localB->TmpSignalConversionAtToWorkspaceInport1[0] =
    localB->SimplyIntegrateVelocity[0];
  localB->TmpSignalConversionAtToWorkspaceInport1[1] =
    localB->SimplyIntegrateVelocity[1];
  localB->TmpSignalConversionAtToWorkspaceInport1[2] =
    localB->DataTypeConversion;
  localB->TmpSignalConversionAtToWorkspaceInport1[3] =
    localB->DataTypeConversion3[0];
  localB->TmpSignalConversionAtToWorkspaceInport1[4] =
    localB->DataTypeConversion3[1];
  localB->TmpSignalConversionAtToWorkspaceInport1[5] =
    localB->DataTypeConversion3[2];
  localB->TmpSignalConversionAtToWorkspaceInport1[6] = localB->Reshapexhat[0];
  localB->TmpSignalConversionAtToWorkspaceInport1[7] = localB->Reshapexhat[1];
  localB->TmpSignalConversionAtToWorkspaceInport1[8] =
    localB->DataTypeConversion2;
  localB->TmpSignalConversionAtToWorkspaceInport1[9] = localB->Subtract[0];
  localB->TmpSignalConversionAtToWorkspaceInport1[10] = localB->Subtract[1];
  localB->TmpSignalConversionAtToWorkspaceInport1[11] = localB->Subtract[2];

  /* ToWorkspace: '<S1>/To Workspace' */
  {
    double locTime = flightControlSystem_M->Timing.taskTime0
      ;
    rt_UpdateStructLogVar((StructLogVar *)localDW->ToWorkspace_PWORK.LoggedData,
                          &locTime,
                          &localB->TmpSignalConversionAtToWorkspaceInport1[0]);
  }

  for (localB->i = 0; localB->i < 3; localB->i++) {
    /* Math: '<S271>/Math Function' incorporates:
     *  Reshape: '<S334>/Reshape (9) to [3x3] column-major'
     */
    localB->MathFunction[3 * localB->i] = localB->VectorConcatenate[localB->i];
    localB->MathFunction[3 * localB->i + 1] = localB->VectorConcatenate
      [localB->i + 3];
    localB->MathFunction[3 * localB->i + 2] = localB->VectorConcatenate
      [localB->i + 6];

    /* Trigonometry: '<S464>/sincos' */
    localB->sincos_o1_g[localB->i] = (real32_T)sin(localB->
      DataTypeConversion3[localB->i]);
    localB->Product_g[localB->i] = (real32_T)cos(localB->
      DataTypeConversion3[localB->i]);
  }

  /* Fcn: '<S464>/Fcn11' */
  localB->VectorConcatenate[0] = localB->Product_g[0] * localB->Product_g[1];

  /* Fcn: '<S464>/Fcn21' incorporates:
   *  Fcn: '<S464>/Fcn22'
   */
  localB->Abs5 = localB->sincos_o1_g[1] * localB->sincos_o1_g[2];
  localB->VectorConcatenate[1] = localB->Abs5 * localB->Product_g[0] -
    localB->sincos_o1_g[0] * localB->Product_g[2];

  /* Fcn: '<S464>/Fcn31' incorporates:
   *  Fcn: '<S464>/Fcn32'
   */
  localB->rtb_pitchrollerror_l_idx_0 = localB->sincos_o1_g[1] *
    localB->Product_g[2];
  localB->VectorConcatenate[2] = localB->rtb_pitchrollerror_l_idx_0 *
    localB->Product_g[0] + localB->sincos_o1_g[0] * localB->sincos_o1_g[2];

  /* Fcn: '<S464>/Fcn12' */
  localB->VectorConcatenate[3] = localB->sincos_o1_g[0] * localB->Product_g[1];

  /* Fcn: '<S464>/Fcn22' */
  localB->VectorConcatenate[4] = localB->Abs5 * localB->sincos_o1_g[0] +
    localB->Product_g[0] * localB->Product_g[2];

  /* Fcn: '<S464>/Fcn32' */
  localB->VectorConcatenate[5] = localB->rtb_pitchrollerror_l_idx_0 *
    localB->sincos_o1_g[0] - localB->Product_g[0] * localB->sincos_o1_g[2];

  /* Fcn: '<S464>/Fcn13' */
  localB->VectorConcatenate[6] = -localB->sincos_o1_g[1];

  /* Fcn: '<S464>/Fcn23' */
  localB->VectorConcatenate[7] = localB->Product_g[1] * localB->sincos_o1_g[2];

  /* Fcn: '<S464>/Fcn33' */
  localB->VectorConcatenate[8] = localB->Product_g[1] * localB->Product_g[2];

  /* Reshape: '<S467>/Reshape (9) to [3x3] column-major' */
  for (localB->i = 0; localB->i < 9; localB->i++) {
    localB->Reshape9to3x3columnmajor[localB->i] = localB->
      VectorConcatenate[localB->i];
  }

  /* End of Reshape: '<S467>/Reshape (9) to [3x3] column-major' */

  /* Trigonometry: '<S537>/sincos' */
  localB->Product_g[0] = (real32_T)sin(localB->DataTypeConversion3[0]);
  localB->rtb_sincos_o1_idx_0 = (real32_T)cos(localB->DataTypeConversion3[0]);
  localB->Product_g[1] = (real32_T)sin(localB->DataTypeConversion3[1]);
  localB->rtb_sincos_o1_idx_1 = (real32_T)cos(localB->DataTypeConversion3[1]);
  localB->Product_g[2] = (real32_T)sin(localB->DataTypeConversion3[2]);
  localB->rtb_sincos_o1_idx_2 = (real32_T)cos(localB->DataTypeConversion3[2]);

  /* Fcn: '<S537>/Fcn11' */
  localB->VectorConcatenate[0] = localB->rtb_sincos_o1_idx_0 *
    localB->rtb_sincos_o1_idx_1;

  /* Fcn: '<S537>/Fcn21' incorporates:
   *  Fcn: '<S537>/Fcn22'
   */
  localB->Abs5 = localB->Product_g[1] * localB->Product_g[2];
  localB->VectorConcatenate[1] = localB->Abs5 * localB->rtb_sincos_o1_idx_0 -
    localB->Product_g[0] * localB->rtb_sincos_o1_idx_2;

  /* Fcn: '<S537>/Fcn31' incorporates:
   *  Fcn: '<S537>/Fcn32'
   */
  localB->rtb_pitchrollerror_l_idx_0 = localB->Product_g[1] *
    localB->rtb_sincos_o1_idx_2;
  localB->VectorConcatenate[2] = localB->rtb_pitchrollerror_l_idx_0 *
    localB->rtb_sincos_o1_idx_0 + localB->Product_g[0] * localB->Product_g[2];

  /* Fcn: '<S537>/Fcn12' */
  localB->VectorConcatenate[3] = localB->Product_g[0] *
    localB->rtb_sincos_o1_idx_1;

  /* Fcn: '<S537>/Fcn22' */
  localB->VectorConcatenate[4] = localB->Abs5 * localB->Product_g[0] +
    localB->rtb_sincos_o1_idx_0 * localB->rtb_sincos_o1_idx_2;

  /* Fcn: '<S537>/Fcn32' */
  localB->VectorConcatenate[5] = localB->rtb_pitchrollerror_l_idx_0 *
    localB->Product_g[0] - localB->rtb_sincos_o1_idx_0 * localB->Product_g[2];

  /* Fcn: '<S537>/Fcn13' */
  localB->VectorConcatenate[6] = -localB->Product_g[1];

  /* Fcn: '<S537>/Fcn23' */
  localB->VectorConcatenate[7] = localB->rtb_sincos_o1_idx_1 * localB->
    Product_g[2];

  /* Fcn: '<S537>/Fcn33' */
  localB->VectorConcatenate[8] = localB->rtb_sincos_o1_idx_1 *
    localB->rtb_sincos_o1_idx_2;

  /* BusAssignment: '<S1>/Control Mode Update' */
  localB->Compare_e3 = rtu_ReferenceValueServerCmds->land_drone;
  localB->Saturation = rtu_ReferenceValueServerCmds->time_remaining;

  /* Logic: '<S263>/OR' incorporates:
   *  BusAssignment: '<S1>/Control Mode Update'
   *  Constant: '<S267>/Constant'
   *  Constant: '<S5>/Constant'
   *  RelationalOperator: '<S267>/Compare'
   */
  localB->OR = ((localB->Saturation <= localP->ComparewithStoptime_const) ||
                localP->Constant_Value_o || localB->Compare_e3);

  /* Outputs for Triggered SubSystem: '<S264>/Triggered Subsystem' incorporates:
   *  TriggerPort: '<S268>/Trigger'
   */
  if (localB->OR && (localZCE->TriggeredSubsystem_Trig_ZCE_p != POS_ZCSIG)) {
    /* SignalConversion generated from: '<S268>/X' */
    localB->BufferToMakeInportVirtual_InsertedFor_X_at_inport_0 =
      localB->SimplyIntegrateVelocity[0];

    /* SignalConversion generated from: '<S268>/Y' */
    localB->BufferToMakeInportVirtual_InsertedFor_Y_at_inport_0 =
      localB->SimplyIntegrateVelocity[1];
  }

  localZCE->TriggeredSubsystem_Trig_ZCE_p = localB->OR;

  /* End of Outputs for SubSystem: '<S264>/Triggered Subsystem' */

  /* Step: '<S265>/Step1' incorporates:
   *  Step: '<S266>/Step8'
   *  Step: '<S266>/Step9'
   */
  localB->DiscreteTimeIntegrator_tmp = flightControlSystem_M->Timing.taskTime0;
  if (localB->DiscreteTimeIntegrator_tmp < localP->Step1_Time) {
    localB->Step4 = localP->Step1_Y0;
  } else {
    localB->Step4 = localP->Step1_YFinal;
  }

  /* DiscreteIntegrator: '<S265>/Discrete-Time Integrator' incorporates:
   *  Step: '<S265>/Step1'
   */
  localDW->DiscreteTimeIntegrator_DSTATE +=
    localP->DiscreteTimeIntegrator_gainval * localB->Step4;

  /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
   *  Constant: '<S264>/Landing Look-ahead distance'
   *  Constant: '<S265>/zValue2'
   *  Logic: '<S5>/NOT'
   *  Saturate: '<S265>/Saturation'
   *  Sum: '<S264>/Add'
   */
  if (localB->OR) {
    localB->Saturation =
      localB->BufferToMakeInportVirtual_InsertedFor_X_at_inport_0;
    localB->rtb_Product1_idx_1 =
      localB->BufferToMakeInportVirtual_InsertedFor_Y_at_inport_0;
    localB->rtb_Product1_idx_2 = localB->DataTypeConversion +
      localP->LandingLookaheaddistance_Value;
  } else {
    if (localDW->DiscreteTimeIntegrator_DSTATE > localP->Saturation_UpperSat) {
      /* Saturate: '<S265>/Saturation' */
      localB->Saturation = localP->Saturation_UpperSat;
    } else if (localDW->DiscreteTimeIntegrator_DSTATE <
               localP->Saturation_LowerSat) {
      /* Saturate: '<S265>/Saturation' */
      localB->Saturation = localP->Saturation_LowerSat;
    } else {
      /* Saturate: '<S265>/Saturation' */
      localB->Saturation = localDW->DiscreteTimeIntegrator_DSTATE;
    }

    localB->rtb_Product1_idx_1 = localB->Saturation;
    localB->rtb_Product1_idx_2 = localP->zValue2_Value;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch' */

  /* Step: '<S266>/Step8' */
  if (localB->DiscreteTimeIntegrator_tmp < localP->Step8_Time) {
    localB->Step4 = localP->Step8_Y0;
  } else {
    localB->Step4 = localP->Step8_YFinal;
  }

  /* Step: '<S266>/Step9' */
  if (localB->DiscreteTimeIntegrator_tmp < localP->Step9_Time) {
    localB->DiscreteTimeIntegrator_tmp = localP->Step9_Y0;
  } else {
    localB->DiscreteTimeIntegrator_tmp = localP->Step9_YFinal;
  }

  /* DataTypeConversion: '<S5>/Data Type Conversion2' incorporates:
   *  Gain: '<S266>/Gain'
   *  Step: '<S266>/Step8'
   *  Step: '<S266>/Step9'
   *  Sum: '<S266>/Add4'
   */
  localB->rtb_sincos_o1_idx_0 = (real32_T)((localB->Step4 +
    localB->DiscreteTimeIntegrator_tmp) * localP->Gain_Gain);

  /* SignalConversion generated from: '<S5>/To Workspace' incorporates:
   *  Constant: '<S266>/xValue4'
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  DataTypeConversion: '<S5>/Data Type Conversion2'
   */
  localB->Sum1_c[0] = (real32_T)localB->Saturation;
  localB->Sum1_c[3] = localB->rtb_sincos_o1_idx_0;
  localB->Sum1_c[1] = (real32_T)localB->rtb_Product1_idx_1;
  localB->Sum1_c[4] = (real32_T)localP->xValue4_Value;
  localB->Sum1_c[2] = (real32_T)localB->rtb_Product1_idx_2;
  localB->Sum1_c[5] = (real32_T)localP->xValue4_Value;

  /* ToWorkspace: '<S5>/To Workspace' */
  {
    double locTime = flightControlSystem_M->Timing.taskTime0
      ;
    rt_UpdateStructLogVar((StructLogVar *)
                          localDW->ToWorkspace_PWORK_c.LoggedData, &locTime,
                          &localB->Sum1_c[0]);
  }

  /* RelationalOperator: '<S463>/Compare' incorporates:
   *  Constant: '<S463>/Constant'
   */
  localB->Compare_e3 = (localB->DataTypeConversion <=
                        localP->DeactivateAccelerationIfOFisnotusedduetolowaltitude_const);

  /* Logic: '<S458>/Logical Operator' incorporates:
   *  Constant: '<S465>/Constant'
   *  Constant: '<S466>/Constant'
   *  RelationalOperator: '<S465>/Compare'
   *  RelationalOperator: '<S466>/Compare'
   */
  rtb_Compare_or = ((localB->u_b[0] !=
                     localP->donotuseaccifopticalflowneveravailableNoteOF60HzbutZOHto200_con)
                    || (localB->u_b[1] !=
                        localP->donotuseaccifopticalflowneveravailableNoteOF60HzbutZOHto2001_co));

  /* Product: '<S458>/Product1' incorporates:
   *  Constant: '<S458>/gravity'
   */
  localB->Step4 = localP->gravity_Value[1];
  localB->DiscreteTimeIntegrator_tmp = localP->gravity_Value[0];
  localB->gravity_Value = localP->gravity_Value[2];

  /* Sum: '<S458>/Add' incorporates:
   *  Constant: '<S458>/gravity'
   *  Product: '<S458>/Product1'
   *  Reshape: '<S467>/Reshape (9) to [3x3] column-major'
   */
  for (localB->i = 0; localB->i < 3; localB->i++) {
    localB->rtb_FIR_IMUaccel_m[localB->i] = localB->FIR_IMUaccel[localB->i] -
      ((localB->Reshape9to3x3columnmajor[localB->i + 3] * localB->Step4 +
        localB->Reshape9to3x3columnmajor[localB->i] *
        localB->DiscreteTimeIntegrator_tmp) + localB->
       Reshape9to3x3columnmajor[localB->i + 6] * localB->gravity_Value);
  }

  /* End of Sum: '<S458>/Add' */

  /* Product: '<S458>/Product' incorporates:
   *  Gain: '<S458>/gainaccinput1'
   */
  localB->Product[0] = (real32_T)(localP->gainaccinput1_Gain *
    localB->rtb_FIR_IMUaccel_m[0]) * (real32_T)rtb_Compare_or * (real32_T)
    localB->Compare_e3;
  localB->Product[1] = (real32_T)(localP->gainaccinput1_Gain *
    localB->rtb_FIR_IMUaccel_m[1]) * (real32_T)rtb_Compare_or * (real32_T)
    localB->Compare_e3;

  /* Outputs for Enabled SubSystem: '<S499>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S530>/Enable'
   */
  /* DataTypeConversion: '<S461>/DataTypeConversionEnable' */
  if (localB->LogicalOperator3) {
    localDW->MeasurementUpdate_MODE = true;

    /* Product: '<S530>/C[k]*xhat[k|k-1]' incorporates:
     *  Constant: '<S461>/C'
     *  Delay: '<S461>/MemoryX'
     */
    localB->Bias_k = 0.0F;
    localB->Bias1_c = 0.0F;
    for (localB->i = 0; localB->i < 4; localB->i++) {
      localB->Abs5 = localDW->MemoryX_DSTATE_a[localB->i];
      localB->j = localB->i << 1;
      localB->Bias_k += localP->C_Value_p[localB->j] * localB->Abs5;
      localB->Bias1_c += localP->C_Value_p[localB->j + 1] * localB->Abs5;
    }

    /* End of Product: '<S530>/C[k]*xhat[k|k-1]' */

    /* Sum: '<S530>/Sum' incorporates:
     *  Constant: '<S461>/D'
     *  Product: '<S530>/D[k]*u[k]'
     *  Reshape: '<S461>/Reshapeu'
     *  Reshape: '<S461>/Reshapey'
     *  Sum: '<S530>/Add1'
     */
    localB->fv[0] = localB->angularvelocitycompensation[0] - ((localP->
      D_Value_k[0] * localB->Product[0] + localB->Product[1] * localP->
      D_Value_k[2]) + localB->Bias_k);
    localB->fv[1] = localB->angularvelocitycompensation[1] - ((localB->Product[0]
      * localP->D_Value_k[1] + localB->Product[1] * localP->D_Value_k[3]) +
      localB->Bias1_c);

    /* Product: '<S530>/Product3' incorporates:
     *  Constant: '<S480>/KalmanGainL'
     *  DataTypeConversion: '<S522>/Conversion'
     */
    localB->rtb_pitchrollerror_l_idx_0 = 0.0F;
    localB->rtb_sincos_o1_idx_1 = 0.0F;
    localB->rtb_sincos_o1_idx_2 = 0.0F;
    localB->Bias_k = 0.0F;
    for (localB->i = 0; localB->i < 2; localB->i++) {
      localB->Abs5 = localB->fv[localB->i];

      /* DataTypeConversion: '<S522>/Conversion' incorporates:
       *  Constant: '<S480>/KalmanGainL'
       */
      localB->j = localB->i << 2;
      localB->rtb_pitchrollerror_l_idx_0 += (real32_T)
        localP->KalmanGainL_Value_j[localB->j] * localB->Abs5;
      localB->rtb_sincos_o1_idx_1 += (real32_T)localP->
        KalmanGainL_Value_j[localB->j + 1] * localB->Abs5;
      localB->rtb_sincos_o1_idx_2 += (real32_T)localP->
        KalmanGainL_Value_j[localB->j + 2] * localB->Abs5;
      localB->Bias_k += (real32_T)localP->KalmanGainL_Value_j[localB->j + 3] *
        localB->Abs5;
    }

    localB->Product3_o[3] = localB->Bias_k;
    localB->Product3_o[2] = localB->rtb_sincos_o1_idx_2;
    localB->Product3_o[1] = localB->rtb_sincos_o1_idx_1;
    localB->Product3_o[0] = localB->rtb_pitchrollerror_l_idx_0;

    /* End of Product: '<S530>/Product3' */
  } else if (localDW->MeasurementUpdate_MODE) {
    /* Disable for Product: '<S530>/Product3' incorporates:
     *  Outport: '<S530>/L*(y[k]-yhat[k|k-1])'
     */
    localB->Product3_o[0] = localP->Lykyhatkk1_Y0_e;
    localB->Product3_o[1] = localP->Lykyhatkk1_Y0_e;
    localB->Product3_o[2] = localP->Lykyhatkk1_Y0_e;
    localB->Product3_o[3] = localP->Lykyhatkk1_Y0_e;
    localDW->MeasurementUpdate_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S499>/MeasurementUpdate' */

  /* Product: '<S499>/B[k]*u[k]' incorporates:
   *  Constant: '<S461>/B'
   *  Reshape: '<S461>/Reshapeu'
   *  Saturate: '<S16>/Saturation5'
   */
  localB->MotorDirections[0] = 0.0F;
  localB->MotorDirections[1] = 0.0F;
  localB->MotorDirections[2] = 0.0F;
  localB->MotorDirections[3] = 0.0F;
  localB->Bias_k = localB->MotorDirections[0];
  localB->Bias1_c = localB->MotorDirections[1];
  localB->Product2_f_b = localB->MotorDirections[2];
  localB->Product2_f_p = localB->MotorDirections[3];
  for (localB->i = 0; localB->i < 2; localB->i++) {
    localB->Abs5 = localB->Product[localB->i];
    localB->j = localB->i << 2;
    localB->Bias_k += localP->B_Value_a[localB->j] * localB->Abs5;
    localB->Bias1_c += localP->B_Value_a[localB->j + 1] * localB->Abs5;
    localB->Product2_f_b += localP->B_Value_a[localB->j + 2] * localB->Abs5;
    localB->Product2_f_p += localP->B_Value_a[localB->j + 3] * localB->Abs5;
  }

  /* Saturate: '<S16>/Saturation5' incorporates:
   *  Product: '<S499>/B[k]*u[k]'
   */
  localB->MotorDirections[3] = localB->Product2_f_p;
  localB->MotorDirections[2] = localB->Product2_f_b;
  localB->MotorDirections[1] = localB->Bias1_c;
  localB->MotorDirections[0] = localB->Bias_k;

  /* Delay: '<S461>/MemoryX' incorporates:
   *  Constant: '<S461>/A'
   *  Product: '<S499>/A[k]*xhat[k|k-1]'
   */
  localB->rtb_pitchrollerror_l_idx_0 = localDW->MemoryX_DSTATE_a[1];
  localB->rtb_sincos_o1_idx_1 = localDW->MemoryX_DSTATE_a[0];
  localB->rtb_sincos_o1_idx_2 = localDW->MemoryX_DSTATE_a[2];
  localB->Bias_k = localDW->MemoryX_DSTATE_a[3];

  /* Sum: '<S499>/Add' incorporates:
   *  Constant: '<S461>/A'
   *  Delay: '<S461>/MemoryX'
   *  Product: '<S499>/A[k]*xhat[k|k-1]'
   */
  for (localB->i = 0; localB->i < 4; localB->i++) {
    localB->posVIS_data[localB->i] = ((((localP->A_Value_c[localB->i + 4] *
      localB->rtb_pitchrollerror_l_idx_0 + localP->A_Value_c[localB->i] *
      localB->rtb_sincos_o1_idx_1) + localP->A_Value_c[localB->i + 8] *
      localB->rtb_sincos_o1_idx_2) + localP->A_Value_c[localB->i + 12] *
      localB->Bias_k) + localB->MotorDirections[localB->i]) + localB->
      Product3_o[localB->i];
  }

  /* End of Sum: '<S499>/Add' */

  /* Reshape: '<S21>/Reshapey' */
  localB->Reshapey_h[0] = localB->SimplyIntegrateVelocity[0];
  localB->Reshapey_h[1] = localB->DataTypeConversion3[1];
  localB->Reshapey_h[2] = localB->Reshapexhat[0];
  localB->Reshapey_h[3] = localB->Subtract[1];

  /* Delay: '<S21>/MemoryX' incorporates:
   *  Constant: '<S21>/X0'
   *  Reshape: '<S21>/ReshapeX0'
   */
  if (localDW->icLoad_b) {
    localDW->MemoryX_DSTATE_b[0] = localP->X0_Value_p[0];
    localDW->MemoryX_DSTATE_b[1] = localP->X0_Value_p[1];
    localDW->MemoryX_DSTATE_b[2] = localP->X0_Value_p[2];
    localDW->MemoryX_DSTATE_b[3] = localP->X0_Value_p[3];
  }

  /* Outputs for Enabled SubSystem: '<S159>/Enabled Subsystem' */
  /* Constant: '<S21>/Enable' incorporates:
   *  Constant: '<S21>/C'
   *  Delay: '<S21>/MemoryX'
   */
  flightControlSystem_EnabledSubsystem_e(localP->Enable_Value,
    localB->Conversion_bf, localP->C_Value_i, localB->Reshapey_h,
    localDW->MemoryX_DSTATE_b, &localB->EnabledSubsystem_d,
    &localDW->EnabledSubsystem_d, &localP->EnabledSubsystem_d);

  /* End of Outputs for SubSystem: '<S159>/Enabled Subsystem' */

  /* Reshape: '<S21>/Reshapexhat' incorporates:
   *  Delay: '<S21>/MemoryX'
   *  Sum: '<S159>/Add'
   */
  localB->Reshapexhat_p[0] = localB->EnabledSubsystem_d.Product2[0] +
    localDW->MemoryX_DSTATE_b[0];
  localB->Reshapexhat_p[1] = localB->EnabledSubsystem_d.Product2[1] +
    localDW->MemoryX_DSTATE_b[1];
  localB->Reshapexhat_p[2] = localB->EnabledSubsystem_d.Product2[2] +
    localDW->MemoryX_DSTATE_b[2];
  localB->Reshapexhat_p[3] = localB->EnabledSubsystem_d.Product2[3] +
    localDW->MemoryX_DSTATE_b[3];

  /* DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */
  localB->Conversion_f[0] = localDW->DiscreteTimeIntegrator_DSTATE_c[0];
  localB->Conversion_f[1] = localDW->DiscreteTimeIntegrator_DSTATE_c[1];

  /* Switch: '<S3>/Switch_refAtt' incorporates:
   *  Constant: '<S1>/controlModePosVsOrient'
   *  Constant: '<S266>/xValue4'
   *  DataTypeConversion: '<S5>/Data Type Conversion2'
   *  Gain: '<S11>/D_xy'
   *  Gain: '<S11>/P_xy'
   *  Saturate: '<S11>/Saturation'
   *  Sum: '<S11>/Sum18'
   */
  if (localP->controlModePosVsOrient_Value) {
    /* Trigonometry: '<S11>/Trigonometric Function' */
    localB->rtb_pitchrollerror_l_idx_0 = (real32_T)sin
      (localB->DataTypeConversion3[0]);
    localB->rtb_sincos_o1_idx_1 = (real32_T)cos(localB->DataTypeConversion3[0]);

    /* Sum: '<S11>/Sum17' incorporates:
     *  DataTypeConversion: '<S5>/Data Type Conversion'
     */
    localB->rtb_sincos_o1_idx_2 = (real32_T)localB->Saturation -
      localB->SimplyIntegrateVelocity[0];
    localB->Bias_k = (real32_T)localB->rtb_Product1_idx_1 -
      localB->SimplyIntegrateVelocity[1];

    /* Product: '<S11>/Product' incorporates:
     *  Gain: '<S11>/Gain'
     *  SignalConversion generated from: '<S11>/Vector Concatenate1'
     *  SignalConversion generated from: '<S11>/Vector Concatenate'
     * */
    localB->Abs5 = localB->rtb_sincos_o1_idx_1 * localB->rtb_sincos_o1_idx_2 +
      localB->rtb_pitchrollerror_l_idx_0 * localB->Bias_k;
    localB->rtb_sincos_o1_idx_1 = localP->Gain_Gain_i *
      localB->rtb_pitchrollerror_l_idx_0 * localB->rtb_sincos_o1_idx_2 +
      localB->rtb_sincos_o1_idx_1 * localB->Bias_k;

    /* Saturate: '<S11>/Saturation' */
    if (localB->Abs5 > localP->Saturation_UpperSat_l) {
      localB->Abs5 = localP->Saturation_UpperSat_l;
    } else if (localB->Abs5 < localP->Saturation_LowerSat_h) {
      localB->Abs5 = localP->Saturation_LowerSat_h;
    }

    localB->rtb_pitchrollerror_l_idx_0 = localP->P_xy_Gain[0] * localB->Abs5 +
      localP->D_xy_Gain[0] * localB->Reshapexhat[0];

    /* Saturate: '<S11>/Saturation' incorporates:
     *  Gain: '<S11>/D_xy'
     *  Gain: '<S11>/P_xy'
     *  Sum: '<S11>/Sum18'
     */
    if (localB->rtb_sincos_o1_idx_1 > localP->Saturation_UpperSat_l) {
      localB->rtb_sincos_o1_idx_1 = localP->Saturation_UpperSat_l;
    } else if (localB->rtb_sincos_o1_idx_1 < localP->Saturation_LowerSat_h) {
      localB->rtb_sincos_o1_idx_1 = localP->Saturation_LowerSat_h;
    }

    localB->rtb_sincos_o1_idx_1 = localP->P_xy_Gain[1] *
      localB->rtb_sincos_o1_idx_1 + localP->D_xy_Gain[1] * localB->Reshapexhat[1];
  } else {
    localB->rtb_pitchrollerror_l_idx_0 = (real32_T)localP->xValue4_Value;
    localB->rtb_sincos_o1_idx_1 = (real32_T)localP->xValue4_Value;
  }

  /* End of Switch: '<S3>/Switch_refAtt' */

  /* Sum: '<S8>/Sum19' */
  localB->rtb_pitchrollerror_l_idx_0 -= localB->DataTypeConversion3[1];
  localB->rtb_sincos_o1_idx_1 -= localB->DataTypeConversion3[2];

  /* ManualSwitch: '<S3>/Manual Switch2' incorporates:
   *  DiscreteIntegrator: '<S15>/Discrete-Time Integrator2'
   *  DiscreteIntegrator: '<S8>/Discrete-Time Integrator'
   *  Gain: '<S15>/Gain4'
   *  Gain: '<S15>/Gain7'
   *  Gain: '<S8>/D_pr1'
   *  Gain: '<S8>/I_pr'
   *  Gain: '<S8>/P_pr2'
   *  Sum: '<S15>/Subtract3'
   *  Sum: '<S8>/Sum16'
   */
  if (localP->ManualSwitch2_CurrentSetting == 1) {
    localB->Abs5 = (localP->P_pr2_Gain[0] * localB->rtb_pitchrollerror_l_idx_0 +
                    localP->I_pr_Gain * localDW->
                    DiscreteTimeIntegrator_DSTATE_c[0]) - localP->D_pr1_Gain[0] *
      localB->Subtract[1];
  } else {
    localB->Abs5 = (0.0F - (((flightControlSystem_P.Kd3[0] *
      localB->Reshapexhat_p[0] + flightControlSystem_P.Kd3[1] *
      localB->Reshapexhat_p[1]) + flightControlSystem_P.Kd3[2] *
      localB->Reshapexhat_p[2]) + flightControlSystem_P.Kd3[3] *
      localB->Reshapexhat_p[3])) - flightControlSystem_P.Kid3 *
      localDW->DiscreteTimeIntegrator2_DSTATE;
  }

  /* End of ManualSwitch: '<S3>/Manual Switch2' */

  /* Bias: '<S3>/Bias' */
  localB->Bias_k = localB->Abs5 + localP->Bias_Bias_e;

  /* Delay: '<S20>/MemoryX' incorporates:
   *  Constant: '<S20>/X0'
   *  Reshape: '<S20>/ReshapeX0'
   */
  if (localDW->icLoad_i) {
    localDW->MemoryX_DSTATE_pv[0] = localP->X0_Value_pq[0];
    localDW->MemoryX_DSTATE_pv[1] = localP->X0_Value_pq[1];
    localDW->MemoryX_DSTATE_pv[2] = localP->X0_Value_pq[2];
    localDW->MemoryX_DSTATE_pv[3] = localP->X0_Value_pq[3];
  }

  /* Reshape: '<S20>/Reshapey' */
  localB->MatrixConcatenate[0] = localB->SimplyIntegrateVelocity[1];
  localB->MatrixConcatenate[1] = localB->DataTypeConversion3[2];
  localB->MatrixConcatenate[2] = localB->Reshapexhat[1];
  localB->MatrixConcatenate[3] = localB->Subtract[0];

  /* Outputs for Enabled SubSystem: '<S105>/Enabled Subsystem' */
  /* Constant: '<S20>/Enable' incorporates:
   *  Constant: '<S20>/C'
   *  Delay: '<S20>/MemoryX'
   */
  flightControlSystem_EnabledSubsystem_e(localP->Enable_Value_k,
    localB->Conversion_c, localP->C_Value_k, localB->MatrixConcatenate,
    localDW->MemoryX_DSTATE_pv, &localB->EnabledSubsystem_e,
    &localDW->EnabledSubsystem_e, &localP->EnabledSubsystem_e);

  /* End of Outputs for SubSystem: '<S105>/Enabled Subsystem' */

  /* Reshape: '<S20>/Reshapexhat' incorporates:
   *  Delay: '<S20>/MemoryX'
   *  Sum: '<S105>/Add'
   */
  localB->Reshapexhat_m[0] = localB->EnabledSubsystem_e.Product2[0] +
    localDW->MemoryX_DSTATE_pv[0];
  localB->Reshapexhat_m[1] = localB->EnabledSubsystem_e.Product2[1] +
    localDW->MemoryX_DSTATE_pv[1];
  localB->Reshapexhat_m[2] = localB->EnabledSubsystem_e.Product2[2] +
    localDW->MemoryX_DSTATE_pv[2];
  localB->Reshapexhat_m[3] = localB->EnabledSubsystem_e.Product2[3] +
    localDW->MemoryX_DSTATE_pv[3];

  /* ManualSwitch: '<S3>/Manual Switch3' incorporates:
   *  DiscreteIntegrator: '<S14>/Discrete-Time Integrator2'
   *  DiscreteIntegrator: '<S8>/Discrete-Time Integrator'
   *  Gain: '<S14>/Gain4'
   *  Gain: '<S14>/Gain7'
   *  Gain: '<S8>/D_pr1'
   *  Gain: '<S8>/I_pr'
   *  Gain: '<S8>/P_pr2'
   *  Sum: '<S14>/Subtract3'
   *  Sum: '<S8>/Sum16'
   */
  if (localP->ManualSwitch3_CurrentSetting == 1) {
    localB->Abs5 = (localP->P_pr2_Gain[1] * localB->rtb_sincos_o1_idx_1 +
                    localP->I_pr_Gain * localDW->
                    DiscreteTimeIntegrator_DSTATE_c[1]) - localB->Subtract[0] *
      localP->D_pr1_Gain[1];
  } else {
    localB->Abs5 = (0.0F - (((flightControlSystem_P.Kd2[0] *
      localB->Reshapexhat_m[0] + flightControlSystem_P.Kd2[1] *
      localB->Reshapexhat_m[1]) + flightControlSystem_P.Kd2[2] *
      localB->Reshapexhat_m[2]) + flightControlSystem_P.Kd2[3] *
      localB->Reshapexhat_m[3])) - flightControlSystem_P.Kid2 *
      localDW->DiscreteTimeIntegrator2_DSTATE_h;
  }

  /* End of ManualSwitch: '<S3>/Manual Switch3' */

  /* Bias: '<S3>/Bias1' */
  localB->Bias1_c = localB->Abs5 + localP->Bias1_Bias;

  /* RelationalOperator: '<S240>/Compare' incorporates:
   *  Constant: '<S240>/Constant'
   *  UnitDelay: '<S241>/Output'
   */
  localB->Compare_e3 = (localDW->Output_DSTATE_n <
                        localP->CompareToConstant_const_pa);

  /* DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
  if ((!localB->Compare_e3) && (localDW->DiscreteTimeIntegrator_PrevResetState ==
       1)) {
    localDW->DiscreteTimeIntegrator_DSTATE_m =
      localP->DiscreteTimeIntegrator_IC_j;
  }

  /* Sum: '<S13>/Sum2' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   */
  localB->rtb_sincos_o1_idx_2 = (real32_T)localB->rtb_Product1_idx_2 -
    localB->DataTypeConversion;

  /* Delay: '<S19>/MemoryX' incorporates:
   *  Constant: '<S19>/X0'
   *  Reshape: '<S19>/ReshapeX0'
   */
  if (localDW->icLoad_o) {
    localDW->MemoryX_DSTATE_e[0] = localP->X0_Value_l[0];
    localDW->MemoryX_DSTATE_e[1] = localP->X0_Value_l[1];
  }

  /* DataTypeConversion: '<S68>/Conversion' incorporates:
   *  Constant: '<S24>/KalmanGainM'
   */
  localB->Reshapexhat_p[0] = (real32_T)localP->KalmanGainM_Value_pm[0];
  localB->Reshapexhat_p[1] = (real32_T)localP->KalmanGainM_Value_pm[1];
  localB->Reshapexhat_p[2] = (real32_T)localP->KalmanGainM_Value_pm[2];
  localB->Reshapexhat_p[3] = (real32_T)localP->KalmanGainM_Value_pm[3];

  /* Reshape: '<S19>/Reshapey' */
  localB->P_pr[0] = localB->DataTypeConversion;
  localB->P_pr[1] = localB->DataTypeConversion2;

  /* Outputs for Enabled SubSystem: '<S51>/Enabled Subsystem' */
  /* Constant: '<S19>/Enable' incorporates:
   *  Constant: '<S19>/C'
   *  Delay: '<S19>/MemoryX'
   */
  flightControlSystem_EnabledSubsystem(localP->Enable_Value_g,
    localB->Reshapexhat_p, localP->C_Value_kb, localB->P_pr,
    localDW->MemoryX_DSTATE_e, &localB->EnabledSubsystem,
    &localDW->EnabledSubsystem, &localP->EnabledSubsystem);

  /* End of Outputs for SubSystem: '<S51>/Enabled Subsystem' */

  /* Reshape: '<S19>/Reshapexhat' incorporates:
   *  Delay: '<S19>/MemoryX'
   *  Sum: '<S51>/Add'
   */
  localB->Reshapexhat_f[0] = localB->EnabledSubsystem.Product2[0] +
    localDW->MemoryX_DSTATE_e[0];
  localB->Reshapexhat_f[1] = localB->EnabledSubsystem.Product2[1] +
    localDW->MemoryX_DSTATE_e[1];

  /* ManualSwitch: '<S3>/Manual Switch' incorporates:
   *  Bias: '<S17>/Bias'
   *  DiscreteIntegrator: '<S17>/Discrete-Time Integrator2'
   *  Gain: '<S17>/Gain4'
   *  Gain: '<S17>/Gain7'
   *  Sum: '<S17>/Subtract3'
   */
  if (localP->ManualSwitch_CurrentSetting == 1) {
    /* Switch: '<S13>/TakeoffOrControl_Switch1' incorporates:
     *  Constant: '<S13>/w1'
     *  DiscreteIntegrator: '<S13>/Discrete-Time Integrator'
     *  Gain: '<S13>/D_z1'
     *  Gain: '<S13>/P_z1'
     *  Gain: '<S13>/takeoff_gain1'
     *  Sum: '<S13>/Sum1'
     */
    if (localB->Compare_e3) {
      localB->Abs5 = localP->takeoff_gain1_Gain * localP->w1_Value;
    } else {
      localB->Abs5 = (localP->P_z1_Gain * localB->rtb_sincos_o1_idx_2 +
                      localDW->DiscreteTimeIntegrator_DSTATE_m) -
        localP->D_z1_Gain * localB->DataTypeConversion2;
    }

    /* Sum: '<S13>/Sum5' incorporates:
     *  Constant: '<S13>/w1'
     *  Switch: '<S13>/TakeoffOrControl_Switch1'
     */
    localB->Abs5 += localP->w1_Value;

    /* Saturate: '<S13>/SaturationThrust1' */
    if (localB->Abs5 > localP->SaturationThrust1_UpperSat) {
      localB->Abs5 = localP->SaturationThrust1_UpperSat;
    } else if (localB->Abs5 < localP->SaturationThrust1_LowerSat) {
      localB->Abs5 = localP->SaturationThrust1_LowerSat;
    }

    /* End of Saturate: '<S13>/SaturationThrust1' */
  } else {
    localB->Abs5 = ((0.0F - (flightControlSystem_P.Kd1[0] *
      localB->Reshapexhat_f[0] + flightControlSystem_P.Kd1[1] *
      localB->Reshapexhat_f[1])) - flightControlSystem_P.Kid1 *
                    localDW->DiscreteTimeIntegrator2_DSTATE_p) +
      localP->Bias_Bias;
  }

  /* End of ManualSwitch: '<S3>/Manual Switch' */

  /* Delay: '<S22>/MemoryX' incorporates:
   *  Constant: '<S22>/X0'
   *  Reshape: '<S22>/ReshapeX0'
   */
  if (localDW->icLoad_h) {
    localDW->MemoryX_DSTATE_c[0] = localP->X0_Value_d[0];
    localDW->MemoryX_DSTATE_c[1] = localP->X0_Value_d[1];
  }

  /* DataTypeConversion: '<S230>/Conversion' incorporates:
   *  Constant: '<S186>/KalmanGainM'
   */
  localB->Reshapexhat_p[0] = (real32_T)localP->KalmanGainM_Value_c[0];
  localB->Reshapexhat_p[1] = (real32_T)localP->KalmanGainM_Value_c[1];
  localB->Reshapexhat_p[2] = (real32_T)localP->KalmanGainM_Value_c[2];
  localB->Reshapexhat_p[3] = (real32_T)localP->KalmanGainM_Value_c[3];

  /* Reshape: '<S22>/Reshapey' */
  localB->Reshapey_f[0] = localB->DataTypeConversion3[0];
  localB->Reshapey_f[1] = localB->Subtract[2];

  /* Outputs for Enabled SubSystem: '<S213>/Enabled Subsystem' */
  /* Constant: '<S22>/Enable' incorporates:
   *  Constant: '<S22>/C'
   *  Delay: '<S22>/MemoryX'
   */
  flightControlSystem_EnabledSubsystem(localP->Enable_Value_n,
    localB->Reshapexhat_p, localP->C_Value_ie, localB->Reshapey_f,
    localDW->MemoryX_DSTATE_c, &localB->EnabledSubsystem_n,
    &localDW->EnabledSubsystem_n, &localP->EnabledSubsystem_n);

  /* End of Outputs for SubSystem: '<S213>/Enabled Subsystem' */

  /* Reshape: '<S22>/Reshapexhat' incorporates:
   *  Delay: '<S22>/MemoryX'
   *  Sum: '<S213>/Add'
   */
  localB->Reshapexhat_e[0] = localB->EnabledSubsystem_n.Product2[0] +
    localDW->MemoryX_DSTATE_c[0];
  localB->Reshapexhat_e[1] = localB->EnabledSubsystem_n.Product2[1] +
    localDW->MemoryX_DSTATE_c[1];

  /* ManualSwitch: '<S3>/Manual Switch1' */
  if (localP->ManualSwitch1_CurrentSetting == 1) {
    /* SignalConversion generated from: '<S9>/Product' incorporates:
     *  BusAssignment: '<S5>/Bus  Assignment'
     *  Gain: '<S12>/D_yaw'
     *  Gain: '<S12>/P_yaw'
     *  Sum: '<S12>/Sum1'
     *  Sum: '<S12>/Sum2'
     */
    localB->Reshapexhat_p[1] = (localB->rtb_sincos_o1_idx_0 -
      localB->DataTypeConversion3[0]) * localP->P_yaw_Gain - localP->D_yaw_Gain *
      localB->Subtract[2];
  } else {
    /* SignalConversion generated from: '<S9>/Product' incorporates:
     *  DiscreteIntegrator: '<S18>/Discrete-Time Integrator2'
     *  Gain: '<S18>/Gain4'
     *  Gain: '<S18>/Gain7'
     *  Sum: '<S18>/Subtract3'
     */
    localB->Reshapexhat_p[1] = (0.0F - (flightControlSystem_P.Kd4[0] *
      localB->Reshapexhat_e[0] + flightControlSystem_P.Kd4[1] *
      localB->Reshapexhat_e[1])) - flightControlSystem_P.Kid4 *
      localDW->DiscreteTimeIntegrator2_DSTATE_d;
  }

  /* End of ManualSwitch: '<S3>/Manual Switch1' */

  /* SignalConversion generated from: '<S9>/Product' */
  localB->Reshapexhat_p[0] = localB->Abs5;
  localB->Reshapexhat_p[2] = localB->Bias_k;
  localB->Reshapexhat_p[3] = localB->Bias1_c;

  /* Product: '<S9>/Product' incorporates:
   *  Constant: '<S9>/TorqueTotalThrustToThrustPerMotor'
   *  Saturate: '<S16>/Saturation5'
   */
  localB->MotorDirections[0] = 0.0F;
  localB->MotorDirections[1] = 0.0F;
  localB->MotorDirections[2] = 0.0F;
  localB->MotorDirections[3] = 0.0F;
  localB->Bias_k = localB->MotorDirections[0];
  localB->Bias1_c = localB->MotorDirections[1];
  localB->Product2_f_b = localB->MotorDirections[2];
  localB->Product2_f_p = localB->MotorDirections[3];
  for (localB->i = 0; localB->i < 4; localB->i++) {
    localB->Abs5 = localB->Reshapexhat_p[localB->i];
    localB->j = localB->i << 2;
    localB->Bias_k += localP->TorqueTotalThrustToThrustPerMotor_Value[localB->j]
      * localB->Abs5;
    localB->Bias1_c += localP->TorqueTotalThrustToThrustPerMotor_Value[localB->j
      + 1] * localB->Abs5;
    localB->Product2_f_b += localP->
      TorqueTotalThrustToThrustPerMotor_Value[localB->j + 2] * localB->Abs5;
    localB->Product2_f_p += localP->
      TorqueTotalThrustToThrustPerMotor_Value[localB->j + 3] * localB->Abs5;
  }

  /* Saturate: '<S16>/Saturation5' incorporates:
   *  Product: '<S9>/Product'
   */
  localB->MotorDirections[3] = localB->Product2_f_p;
  localB->MotorDirections[2] = localB->Product2_f_b;
  localB->MotorDirections[1] = localB->Bias1_c;
  localB->MotorDirections[0] = localB->Bias_k;

  /* Saturate: '<S16>/Saturation5' incorporates:
   *  Gain: '<S16>/ThrustToMotorCommand'
   */
  localB->Abs5 = localP->ThrustToMotorCommand_Gain * localB->MotorDirections[0];
  if (localB->Abs5 > localP->Saturation5_UpperSat) {
    localB->MotorDirections[0] = localP->Saturation5_UpperSat;
  } else if (localB->Abs5 < localP->Saturation5_LowerSat) {
    localB->MotorDirections[0] = localP->Saturation5_LowerSat;
  } else {
    localB->MotorDirections[0] = localB->Abs5;
  }

  localB->Abs5 = localP->ThrustToMotorCommand_Gain * localB->MotorDirections[1];
  if (localB->Abs5 > localP->Saturation5_UpperSat) {
    localB->MotorDirections[1] = localP->Saturation5_UpperSat;
  } else if (localB->Abs5 < localP->Saturation5_LowerSat) {
    localB->MotorDirections[1] = localP->Saturation5_LowerSat;
  } else {
    localB->MotorDirections[1] = localB->Abs5;
  }

  localB->Abs5 = localP->ThrustToMotorCommand_Gain * localB->MotorDirections[2];
  if (localB->Abs5 > localP->Saturation5_UpperSat) {
    localB->MotorDirections[2] = localP->Saturation5_UpperSat;
  } else if (localB->Abs5 < localP->Saturation5_LowerSat) {
    localB->MotorDirections[2] = localP->Saturation5_LowerSat;
  } else {
    localB->MotorDirections[2] = localB->Abs5;
  }

  localB->Abs5 = localP->ThrustToMotorCommand_Gain * localB->MotorDirections[3];
  if (localB->Abs5 > localP->Saturation5_UpperSat) {
    localB->MotorDirections[3] = localP->Saturation5_UpperSat;
  } else if (localB->Abs5 < localP->Saturation5_LowerSat) {
    localB->MotorDirections[3] = localP->Saturation5_LowerSat;
  } else {
    localB->MotorDirections[3] = localB->Abs5;
  }

  /* End of Saturate: '<S16>/Saturation5' */

  /* Product: '<S23>/Product' incorporates:
   *  Constant: '<S23>/TorqueTotalThrustToThrustPerMotor'
   *  Gain: '<S23>/ThrustToMotorCommand'
   */
  localB->Bias_k = 0.0F;
  localB->Bias1_c = 0.0F;
  localB->Product2_f_b = 0.0F;
  localB->Product2_f_p = 0.0F;
  for (localB->i = 0; localB->i < 4; localB->i++) {
    localB->Abs5 = localP->ThrustToMotorCommand_Gain_b * localB->
      MotorDirections[localB->i];
    localB->j = localB->i << 2;
    localB->Bias_k += localP->TorqueTotalThrustToThrustPerMotor_Value_m
      [localB->j] * localB->Abs5;
    localB->Bias1_c += localP->TorqueTotalThrustToThrustPerMotor_Value_m
      [localB->j + 1] * localB->Abs5;
    localB->Product2_f_b += localP->
      TorqueTotalThrustToThrustPerMotor_Value_m[localB->j + 2] * localB->Abs5;
    localB->Product2_f_p += localP->
      TorqueTotalThrustToThrustPerMotor_Value_m[localB->j + 3] * localB->Abs5;
  }

  localB->Product_c[3] = localB->Product2_f_p;
  localB->Product_c[2] = localB->Product2_f_b;
  localB->Product_c[1] = localB->Bias1_c;
  localB->Product_c[0] = localB->Bias_k;

  /* End of Product: '<S23>/Product' */

  /* Bias: '<S10>/Bias' */
  localB->Bias = localB->Product_c[2] + localP->Bias_Bias_o;

  /* Outputs for Enabled SubSystem: '<S152>/MeasurementUpdate' */
  /* Constant: '<S21>/Enable' incorporates:
   *  Constant: '<S21>/C'
   *  Constant: '<S21>/D'
   *  Delay: '<S21>/MemoryX'
   *  Reshape: '<S21>/Reshapeu'
   */
  flightControlSystem_MeasurementUpdate_j(localP->Enable_Value,
    localB->Conversion_c0, localB->Reshapey_h, localP->C_Value_i,
    localDW->MemoryX_DSTATE_b, localP->D_Value_h, localB->Bias,
    &localB->MeasurementUpdate_jc, &localDW->MeasurementUpdate_jc,
    &localP->MeasurementUpdate_jc);

  /* End of Outputs for SubSystem: '<S152>/MeasurementUpdate' */

  /* ToWorkspace: '<S16>/To Workspace' */
  {
    double locTime = flightControlSystem_M->Timing.taskTime0
      ;
    rt_UpdateStructLogVar((StructLogVar *)
                          localDW->ToWorkspace_PWORK_d.LoggedData, &locTime,
                          &localB->MotorDirections[0]);
  }

  /* Gain: '<S16>/MotorDirections' incorporates:
   *  Saturate: '<S16>/Saturation5'
   */
  localB->MotorDirections[0] *= localP->MotorDirections_Gain[0];
  localB->MotorDirections[1] *= localP->MotorDirections_Gain[1];
  localB->MotorDirections[2] *= localP->MotorDirections_Gain[2];
  localB->MotorDirections[3] *= localP->MotorDirections_Gain[3];

  /* ToWorkspace: '<S9>/To Workspace' */
  {
    double locTime = flightControlSystem_M->Timing.taskTime0
      ;
    rt_UpdateStructLogVar((StructLogVar *)
                          localDW->ToWorkspace_PWORK_g.LoggedData, &locTime,
                          &localB->Reshapexhat_p[0]);
  }

  /* Bias: '<S10>/Bias1' */
  localB->Bias1 = localB->Product_c[3] + localP->Bias1_Bias_j;

  /* Outputs for Enabled SubSystem: '<S98>/MeasurementUpdate' */
  /* Constant: '<S20>/Enable' incorporates:
   *  Constant: '<S20>/C'
   *  Constant: '<S20>/D'
   *  Delay: '<S20>/MemoryX'
   *  Reshape: '<S20>/Reshapeu'
   */
  flightControlSystem_MeasurementUpdate_j(localP->Enable_Value_k,
    localB->Conversion_i, localB->MatrixConcatenate, localP->C_Value_k,
    localDW->MemoryX_DSTATE_pv, localP->D_Value_m, localB->Bias1,
    &localB->MeasurementUpdate_j, &localDW->MeasurementUpdate_j,
    &localP->MeasurementUpdate_j);

  /* End of Outputs for SubSystem: '<S98>/MeasurementUpdate' */

  /* Product: '<S98>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S20>/A'
   *  Delay: '<S20>/MemoryX'
   */
  localB->Bias_k = 0.0F;
  localB->Bias1_c = 0.0F;
  localB->Product2_f_b = 0.0F;
  localB->Product2_f_p = 0.0F;
  for (localB->i = 0; localB->i < 4; localB->i++) {
    localB->Abs5 = localDW->MemoryX_DSTATE_pv[localB->i];
    localB->j = localB->i << 2;
    localB->Bias_k += localP->A_Value_j[localB->j] * localB->Abs5;
    localB->Bias1_c += localP->A_Value_j[localB->j + 1] * localB->Abs5;
    localB->Product2_f_b += localP->A_Value_j[localB->j + 2] * localB->Abs5;
    localB->Product2_f_p += localP->A_Value_j[localB->j + 3] * localB->Abs5;

    /* DataTypeConversion: '<S67>/Conversion' incorporates:
     *  Constant: '<S20>/A'
     *  Constant: '<S24>/KalmanGainL'
     *  Delay: '<S20>/MemoryX'
     */
    localB->Reshapey_h[localB->i] = (real32_T)localP->KalmanGainL_Value_d
      [localB->i];

    /* DataTypeConversion: '<S229>/Conversion' incorporates:
     *  Constant: '<S186>/KalmanGainL'
     */
    localB->MatrixConcatenate[localB->i] = (real32_T)localP->
      KalmanGainL_Value_a[localB->i];
  }

  localB->Reshapexhat_p[3] = localB->Product2_f_p;
  localB->Reshapexhat_p[2] = localB->Product2_f_b;
  localB->Reshapexhat_p[1] = localB->Bias1_c;
  localB->Reshapexhat_p[0] = localB->Bias_k;

  /* End of Product: '<S98>/A[k]*xhat[k|k-1]' */

  /* Product: '<S271>/Product' */
  localB->Abs5 = localB->FIR_IMUaccel[1];
  localB->Bias_k = localB->FIR_IMUaccel[0];
  for (localB->i = 0; localB->i < 3; localB->i++) {
    /* Sum: '<S271>/Sum' incorporates:
     *  Constant: '<S271>/gravity'
     *  DiscreteFir: '<S273>/FIR_IMUaccel'
     *  Math: '<S271>/Math Function'
     *  Product: '<S271>/Product'
     */
    localB->Sum[localB->i] = ((localB->MathFunction[localB->i + 3] *
      localB->Abs5 + localB->MathFunction[localB->i] * localB->Bias_k) +
      localB->MathFunction[localB->i + 6] * localB->rtb_SensorCalibration_c) +
      localP->gravity_Value_o[localB->i];
  }

  /* ToWorkspace: '<S272>/To Workspace' */
  {
    double locTime = flightControlSystem_M->Timing.taskTime0
      ;
    rt_UpdateStructLogVar((StructLogVar *)
                          localDW->ToWorkspace_PWORK_l.LoggedData, &locTime,
                          &localB->TmpSignalConversionAtToWorkspaceInport1_of[0]);
  }

  /* DataTypeConversion: '<S438>/Conversion' incorporates:
   *  Constant: '<S396>/KalmanGainL'
   */
  localB->Conversion_d[0] = (real32_T)localP->KalmanGainL_Value_p[0];
  localB->Conversion_d[1] = (real32_T)localP->KalmanGainL_Value_p[1];

  /* Outputs for Enabled SubSystem: '<S415>/MeasurementUpdate' */
  /* DataTypeConversion: '<S395>/DataTypeConversionEnable' incorporates:
   *  Constant: '<S395>/C'
   *  Constant: '<S395>/D'
   *  Delay: '<S395>/MemoryX'
   *  Reshape: '<S395>/Reshapeu'
   *  Reshape: '<S395>/Reshapey'
   */
  flightControlSystem_MeasurementUpdate_o((localB->LogicalOperator != 0),
    localB->Conversion_d, localB->TrigonometricFunction, localP->C_Value_a,
    localDW->MemoryX_DSTATE_p, localP->D_Value_n, localB->inverseIMU_gain[3],
    &localB->MeasurementUpdate_n, &localDW->MeasurementUpdate_n,
    &localP->MeasurementUpdate_n);

  /* End of Outputs for SubSystem: '<S415>/MeasurementUpdate' */

  /* DataTypeConversion: '<S384>/Conversion' incorporates:
   *  Constant: '<S342>/KalmanGainL'
   */
  localB->Conversion_d[0] = (real32_T)localP->KalmanGainL_Value_pv[0];
  localB->Conversion_d[1] = (real32_T)localP->KalmanGainL_Value_pv[1];

  /* Outputs for Enabled SubSystem: '<S361>/MeasurementUpdate' */
  /* DataTypeConversion: '<S341>/DataTypeConversionEnable' incorporates:
   *  Constant: '<S341>/C'
   *  Constant: '<S341>/D'
   *  Delay: '<S341>/MemoryX'
   *  Reshape: '<S341>/Reshapeu'
   *  Reshape: '<S341>/Reshapey'
   */
  flightControlSystem_MeasurementUpdate_o((localB->LogicalOperator != 0),
    localB->Conversion_d, localB->TrigonometricFunction1, localP->C_Value_j,
    localDW->MemoryX_DSTATE_l, localP->D_Value_b, localB->inverseIMU_gain[4],
    &localB->MeasurementUpdate_o, &localDW->MeasurementUpdate_o,
    &localP->MeasurementUpdate_o);

  /* End of Outputs for SubSystem: '<S361>/MeasurementUpdate' */

  /* Outputs for Enabled SubSystem: '<S297>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S327>/Enable'
   */
  /* DataTypeConversion: '<S275>/DataTypeConversionEnable' */
  if (localB->nicemeasurementornewupdateneeded) {
    localDW->MeasurementUpdate_MODE_p = true;

    /* Sum: '<S327>/Sum' incorporates:
     *  Constant: '<S275>/C'
     *  Constant: '<S275>/D'
     *  Delay: '<S275>/MemoryX'
     *  Product: '<S327>/C[k]*xhat[k|k-1]'
     *  Product: '<S327>/D[k]*u[k]'
     *  Reshape: '<S275>/Reshapeu'
     *  Reshape: '<S275>/Reshapey'
     *  Sum: '<S327>/Add1'
     */
    localB->Step4 = localB->invertzaxisGain - ((localP->C_Value[0] *
      localDW->MemoryX_DSTATE[0] + localP->C_Value[1] * localDW->MemoryX_DSTATE
      [1]) + localP->D_Value * localB->Sum[2]);

    /* Product: '<S327>/Product3' incorporates:
     *  Constant: '<S279>/KalmanGainL'
     *  DataTypeConversion: '<S319>/Conversion'
     */
    localB->Product3[0] = localP->KalmanGainL_Value_pe[0] * localB->Step4;
    localB->Product3[1] = localP->KalmanGainL_Value_pe[1] * localB->Step4;
  } else if (localDW->MeasurementUpdate_MODE_p) {
    /* Disable for Product: '<S327>/Product3' incorporates:
     *  Outport: '<S327>/L*(y[k]-yhat[k|k-1])'
     */
    localB->Product3[0] = localP->Lykyhatkk1_Y0;
    localB->Product3[1] = localP->Lykyhatkk1_Y0;
    localDW->MeasurementUpdate_MODE_p = false;
  }

  /* End of Outputs for SubSystem: '<S297>/MeasurementUpdate' */

  /* Outputs for Enabled SubSystem: '<S206>/MeasurementUpdate' */
  /* Constant: '<S22>/Enable' incorporates:
   *  Constant: '<S22>/C'
   *  Constant: '<S22>/D'
   *  Delay: '<S22>/MemoryX'
   *  Reshape: '<S22>/Reshapeu'
   */
  flightControlSystem_MeasurementUpdate(localP->Enable_Value_n,
    localB->MatrixConcatenate, localB->Reshapey_f, localP->C_Value_ie,
    localDW->MemoryX_DSTATE_c, localP->D_Value_he, localB->Product_c[1],
    &localB->MeasurementUpdate_c, &localDW->MeasurementUpdate_c,
    &localP->MeasurementUpdate_c);

  /* End of Outputs for SubSystem: '<S206>/MeasurementUpdate' */

  /* Bias: '<S10>/Bias2' */
  localB->Bias2 = localB->Product_c[0] + localP->Bias2_Bias;

  /* Outputs for Enabled SubSystem: '<S44>/MeasurementUpdate' */
  /* Constant: '<S19>/Enable' incorporates:
   *  Constant: '<S19>/C'
   *  Constant: '<S19>/D'
   *  Delay: '<S19>/MemoryX'
   *  Reshape: '<S19>/Reshapeu'
   */
  flightControlSystem_MeasurementUpdate(localP->Enable_Value_g,
    localB->Reshapey_h, localB->P_pr, localP->C_Value_kb,
    localDW->MemoryX_DSTATE_e, localP->D_Value_m4, localB->Bias2,
    &localB->MeasurementUpdate, &localDW->MeasurementUpdate,
    &localP->MeasurementUpdate);

  /* End of Outputs for SubSystem: '<S44>/MeasurementUpdate' */

  /* Scope: '<S3>/yaw' */
  {
    StructLogVar *svar = (StructLogVar *)localDW->yaw_PWORK.LoggedData;
    LogVar *var = svar->signals.values;

    /* time */
    {
      double locTime = flightControlSystem_M->Timing.taskTime0
        ;
      rt_UpdateLogVar((LogVar *)svar->time, &locTime, 0);
    }

    /* signals */
    {
      real32_T up0[2];
      up0[0] = localB->Reshapexhat_e[0];
      up0[1] = localB->Reshapexhat_e[1];
      rt_UpdateLogVar((LogVar *)var, up0, 0);
    }
  }

  /* Sum: '<S242>/FixPt Sum1' incorporates:
   *  Constant: '<S242>/FixPt Constant'
   *  UnitDelay: '<S241>/Output'
   */
  localDW->Output_DSTATE_n += localP->FixPtConstant_Value_p;

  /* RelationalOperator: '<S4>/GreaterThan' incorporates:
   *  Constant: '<S4>/Wait  3 Seconds'
   *  UnitDelay: '<S251>/Output'
   */
  rtb_Compare_or = (localDW->Output_DSTATE_ir > localP->Wait3Seconds_Value);

  /* Switch: '<S255>/Switch' incorporates:
   *  Constant: '<S255>/ '
   */
  if (rtb_Compare_or) {
    localB->Step4 = rtu_Sensors->VisionSensors.opticalFlow_data[2];
  } else {
    localB->Step4 = localP->_Value;
  }

  /* End of Switch: '<S255>/Switch' */

  /* Sum: '<S255>/Add' incorporates:
   *  Constant: '<S262>/Constant'
   *  DataTypeConversion: '<S255>/   '
   *  Delay: '<S255>/Delay One Step'
   *  Product: '<S255>/  '
   *  RelationalOperator: '<S262>/Compare'
   */
  localDW->DelayOneStep_DSTATE = (real_T)(localB->Step4 ==
    localP->Checkerrorcondition_const) * localDW->DelayOneStep_DSTATE + (real_T)
    (localB->Step4 == localP->Checkerrorcondition_const);

  /* Switch: '<S255>/Switch1' incorporates:
   *  Constant: '<S255>/ Disable OF check'
   *  Constant: '<S261>/Constant'
   *  RelationalOperator: '<S261>/Compare'
   */
  if (localB->OR) {
    localB->Step4 = localP->DisableOFcheck_Value;
  } else {
    localB->Step4 = (localDW->DelayOneStep_DSTATE >
                     localP->u0continuousOFerrors_const);
  }

  /* End of Switch: '<S255>/Switch1' */

  /* Gain: '<S4>/Gain' */
  localB->Abs5 = localP->Gain_Gain_f *
    rtu_Sensors->VisionSensors.opticalFlow_data[0];

  /* RelationalOperator: '<S247>/Compare' incorporates:
   *  Abs: '<S4>/Abs2'
   *  Constant: '<S247>/Constant'
   *  Sum: '<S4>/Subtract'
   */
  rtb_Compare_li = ((real32_T)fabs(localB->Abs5 - localB->Reshapexhat[0]) >
                    localP->CompareToConstant2_const);

  /* Abs: '<S4>/Abs4' */
  localB->Abs5 = (real32_T)fabs(rtu_Sensors->VisionSensors.opticalFlow_data[0]);

  /* RelationalOperator: '<S249>/Compare' incorporates:
   *  Constant: '<S249>/Constant'
   */
  rtb_Compare_nu = (localB->Abs5 > localP->CompareToConstant4_const);

  /* Gain: '<S4>/Gain1' */
  localB->Abs5 = localP->Gain1_Gain_j *
    rtu_Sensors->VisionSensors.opticalFlow_data[1];

  /* RelationalOperator: '<S248>/Compare' incorporates:
   *  Abs: '<S4>/Abs3'
   *  Constant: '<S248>/Constant'
   *  Sum: '<S4>/Subtract1'
   */
  rtb_Compare_cm = ((real32_T)fabs(localB->Abs5 - localB->Reshapexhat[1]) >
                    localP->CompareToConstant3_const);

  /* Abs: '<S4>/Abs5' */
  localB->Abs5 = (real32_T)fabs(rtu_Sensors->VisionSensors.opticalFlow_data[1]);

  /* If: '<S4>/If' incorporates:
   *  Abs: '<S244>/Abs  '
   *  Abs: '<S4>/Abs'
   *  Abs: '<S4>/Abs1'
   *  Constant: '<S244>/0.5 meters'
   *  Constant: '<S245>/Constant'
   *  Constant: '<S246>/Constant'
   *  Constant: '<S250>/Constant'
   *  Constant: '<S260>/Constant'
   *  DataTypeConversion: '<S255>/Data Type Conversion2'
   *  Logic: '<S254>/AND'
   *  Logic: '<S4>/Logical Operator'
   *  Logic: '<S4>/Logical Operator1'
   *  Logic: '<S4>/Logical Operator2'
   *  Logic: '<S4>/Logical Operator3'
   *  RelationalOperator: '<S244>/GreaterThan  '
   *  RelationalOperator: '<S245>/Compare'
   *  RelationalOperator: '<S246>/Compare'
   *  RelationalOperator: '<S250>/Compare'
   *  RelationalOperator: '<S260>/Compare'
   *  Switch: '<S244>/         '
   *  Switch: '<S254>/Switch'
   */
  if (((real32_T)fabs(localB->SimplyIntegrateVelocity[0]) >
       localP->CompareToConstant_const_m) || ((real32_T)fabs
       (localB->SimplyIntegrateVelocity[1]) > localP->CompareToConstant1_const_m))
  {
    /* Outputs for IfAction SubSystem: '<S4>/Geofencing error' incorporates:
     *  ActionPort: '<S252>/Action Port'
     */
    flightControlSystem_Geofencingerror(&localB->Merge, &localP->Geofencingerror);

    /* End of Outputs for SubSystem: '<S4>/Geofencing error' */
  } else if ((rtb_Compare_nu && rtb_Compare_li) || (rtb_Compare_cm &&
              (localB->Abs5 > localP->CompareToConstant5_const))) {
    /* Outputs for IfAction SubSystem: '<S4>/estimator//Optical flow error' incorporates:
     *  ActionPort: '<S257>/Action Port'
     */
    flightControlSystem_Geofencingerror(&localB->Merge,
      &localP->estimatorOpticalflowerror);

    /* End of Outputs for SubSystem: '<S4>/estimator//Optical flow error' */
  } else {
    /* DataTypeConversion: '<S255>/Data Type Conversion2' */
    localB->DiscreteTimeIntegrator_tmp = fabs(localB->Step4);
    if (localB->DiscreteTimeIntegrator_tmp < 4.503599627370496E+15) {
      if (localB->DiscreteTimeIntegrator_tmp >= 0.5) {
        localB->Step4 = floor(localB->Step4 + 0.5);
      } else {
        localB->Step4 *= 0.0;
      }
    }

    if (rtIsNaN(localB->Step4) || rtIsInf(localB->Step4)) {
      localB->Step4 = 0.0;
    } else {
      localB->Step4 = fmod(localB->Step4, 256.0);
    }

    if ((localB->Step4 < 0.0 ? (int32_T)(uint8_T)-(int8_T)(uint8_T)
         -localB->Step4 : (int32_T)(uint8_T)localB->Step4) > 0) {
      /* Outputs for IfAction SubSystem: '<S4>/No optical flow ' incorporates:
       *  ActionPort: '<S253>/Action Port'
       */
      flightControlSystem_Geofencingerror(&localB->Merge, &localP->Noopticalflow);

      /* End of Outputs for SubSystem: '<S4>/No optical flow ' */
    } else {
      if (rtb_Compare_or) {
        /* Switch: '<S244>/         ' incorporates:
         *  DiscreteFilter: '<S276>/pressureFilter_IIR'
         *  Sum: '<S4>/Difference between  sonar and pressure'
         */
        localB->Abs5 = localB->DataTypeConversion - localB->ManualSwitch1;
      } else {
        /* Switch: '<S244>/         ' incorporates:
         *  Constant: '<S244>/    '
         */
        localB->Abs5 = localP->_Value_a;
      }

      if ((real32_T)fabs(localB->Abs5) > localP->u5meters_Value) {
        /* Outputs for IfAction SubSystem: '<S4>/Ultrasound improper' incorporates:
         *  ActionPort: '<S256>/Action Port'
         */
        flightControlSystem_Geofencingerror(&localB->Merge,
          &localP->Ultrasoundimproper);

        /* End of Outputs for SubSystem: '<S4>/Ultrasound improper' */

        /* Outputs for IfAction SubSystem: '<S4>/Normal condition  and landing' incorporates:
         *  ActionPort: '<S254>/Action Port'
         */
      } else if ((localB->DataTypeConversion >
                  localP->Checkifthedroneis03maboveground_const) && localB->OR)
      {
        /* Switch: '<S254>/Switch' incorporates:
         *  Constant: '<S254>/Landed'
         *  Merge: '<S4>/Merge'
         */
        localB->Merge = localP->Landed_Value;
      } else {
        /* Merge: '<S4>/Merge' incorporates:
         *  Constant: '<S254>/No_error'
         *  Switch: '<S254>/Switch'
         */
        localB->Merge = localP->No_error_Value;

        /* End of Outputs for SubSystem: '<S4>/Normal condition  and landing' */
      }
    }
  }

  /* End of If: '<S4>/If' */

  /* Sum: '<S258>/FixPt Sum1' incorporates:
   *  Constant: '<S258>/FixPt Constant'
   *  UnitDelay: '<S251>/Output'
   */
  localDW->Output_DSTATE_ir += localP->FixPtConstant_Value;

  /* Sum: '<S535>/FixPt Sum1' incorporates:
   *  Constant: '<S535>/FixPt Constant'
   *  UnitDelay: '<S534>/Output'
   */
  localDW->Output_DSTATE_i += localP->FixPtConstant_Value_m;

  /* Sum: '<S454>/FixPt Sum1' incorporates:
   *  Constant: '<S454>/FixPt Constant'
   *  UnitDelay: '<S452>/Output'
   */
  localDW->Output_DSTATE += localP->FixPtConstant_Value_f;

  /* Constant: '<S1>/Constant' */
  localB->Constant = localP->Constant_Value_g;

  /* SignalConversion generated from: '<S457>/Product' */
  localB->Bias_k = localB->Reshapexhat[0];
  localB->Bias1_c = localB->Reshapexhat[1];

  /* Product: '<S457>/Product' incorporates:
   *  Math: '<S457>/Math Function'
   *  Reshape: '<S538>/Reshape (9) to [3x3] column-major'
   *  SignalConversion generated from: '<S457>/Product'
   */
  for (localB->i = 0; localB->i < 3; localB->i++) {
    localB->FIR_IMUaccel[localB->i] = (localB->VectorConcatenate[3 * localB->i +
      1] * localB->Bias1_c + localB->VectorConcatenate[3 * localB->i] *
      localB->Bias_k) + localB->VectorConcatenate[3 * localB->i + 2] *
      localB->DataTypeConversion2;
  }

  /* End of Product: '<S457>/Product' */

  /* Update for DiscreteIntegrator: '<S457>/SimplyIntegrateVelocity' incorporates:
   *  Constant: '<S1>/controlModePosVsOrient'
   */
  localDW->SimplyIntegrateVelocity_PrevResetState = (int8_T)
    localP->controlModePosVsOrient_Value;

  /* Update for Delay: '<S275>/MemoryX' */
  localDW->icLoad = false;

  /* Update for DiscreteIntegrator: '<S457>/SimplyIntegrateVelocity' */
  localDW->SimplyIntegrateVelocity_DSTATE[0] +=
    localP->SimplyIntegrateVelocity_gainval * localB->FIR_IMUaccel[0];
  localDW->SimplyIntegrateVelocity_DSTATE[1] +=
    localP->SimplyIntegrateVelocity_gainval * localB->FIR_IMUaccel[1];

  /* Product: '<S297>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S275>/A'
   *  Delay: '<S275>/MemoryX'
   */
  localB->DiscreteTimeIntegrator_tmp = localP->A_Value[0] *
    localDW->MemoryX_DSTATE[0];
  localB->gravity_Value = localDW->MemoryX_DSTATE[0] * localP->A_Value[1];
  localB->Step4 = localDW->MemoryX_DSTATE[1];

  /* Update for Delay: '<S275>/MemoryX' incorporates:
   *  Constant: '<S275>/A'
   *  Constant: '<S275>/B'
   *  Product: '<S297>/A[k]*xhat[k|k-1]'
   *  Product: '<S297>/B[k]*u[k]'
   *  Product: '<S327>/Product3'
   *  Reshape: '<S275>/Reshapeu'
   *  Sum: '<S297>/Add'
   */
  localDW->MemoryX_DSTATE[0] = ((localP->A_Value[2] * localB->Step4 +
    localB->DiscreteTimeIntegrator_tmp) + localP->B_Value[0] * localB->Sum[2]) +
    localB->Product3[0];

  /* Update for DiscreteFilter: '<S276>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[2] = localDW->pressureFilter_IIR_states[1];

  /* Update for DiscreteFilter: '<S276>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[2] = localDW->sonarFilter_IIR_states[1];

  /* Update for Delay: '<S275>/MemoryX' incorporates:
   *  Constant: '<S275>/A'
   *  Constant: '<S275>/B'
   *  Product: '<S297>/A[k]*xhat[k|k-1]'
   *  Product: '<S297>/B[k]*u[k]'
   *  Product: '<S327>/Product3'
   *  Reshape: '<S275>/Reshapeu'
   *  Sum: '<S297>/Add'
   */
  localDW->MemoryX_DSTATE[1] = ((localP->A_Value[3] * localB->Step4 +
    localB->gravity_Value) + localP->B_Value[1] * localB->Sum[2]) +
    localB->Product3[1];

  /* Update for DiscreteFilter: '<S276>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[1] = localDW->pressureFilter_IIR_states[0];

  /* Update for DiscreteFilter: '<S276>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[1] = localDW->sonarFilter_IIR_states[0];

  /* Update for DiscreteFilter: '<S276>/pressureFilter_IIR' */
  localDW->pressureFilter_IIR_states[0] = localB->vbat_V;

  /* Update for DiscreteFilter: '<S276>/sonarFilter_IIR' */
  localDW->sonarFilter_IIR_states[0] = localB->sonarFilter_IIR_tmp;

  /* Update for DiscreteIntegrator: '<S339>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_p +=
    localP->DiscreteTimeIntegrator_gainval_a * localB->Subtract_c;

  /* Update for Delay: '<S341>/MemoryX' */
  localDW->icLoad_a = false;

  /* Product: '<S361>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S341>/A'
   *  Delay: '<S341>/MemoryX'
   */
  localB->Bias_k = localP->A_Value_h[0] * localDW->MemoryX_DSTATE_l[0];
  localB->Bias1_c = localDW->MemoryX_DSTATE_l[0] * localP->A_Value_h[1];
  localB->Abs5 = localDW->MemoryX_DSTATE_l[1];

  /* Update for Delay: '<S341>/MemoryX' incorporates:
   *  Constant: '<S341>/A'
   *  Constant: '<S341>/B'
   *  Product: '<S361>/A[k]*xhat[k|k-1]'
   *  Product: '<S361>/B[k]*u[k]'
   *  Product: '<S392>/Product3'
   *  Reshape: '<S341>/Reshapeu'
   *  Sum: '<S361>/Add'
   */
  localDW->MemoryX_DSTATE_l[0] = ((localP->A_Value_h[2] * localB->Abs5 +
    localB->Bias_k) + localP->B_Value_j[0] * localB->inverseIMU_gain[4]) +
    localB->MeasurementUpdate_o.Product3[0];
  localDW->MemoryX_DSTATE_l[1] = ((localP->A_Value_h[3] * localB->Abs5 +
    localB->Bias1_c) + localP->B_Value_j[1] * localB->inverseIMU_gain[4]) +
    localB->MeasurementUpdate_o.Product3[1];

  /* Update for DiscreteFir: '<S273>/FIR_IMUaccel' */
  /* Update circular buffer index */
  localDW->FIR_IMUaccel_circBuf--;
  if (localDW->FIR_IMUaccel_circBuf < 0) {
    localDW->FIR_IMUaccel_circBuf = 4;
  }

  /* Update circular buffer */
  localDW->FIR_IMUaccel_states[localDW->FIR_IMUaccel_circBuf] =
    localB->inverseIMU_gain[0];
  localDW->FIR_IMUaccel_states[localDW->FIR_IMUaccel_circBuf + 5] =
    localB->inverseIMU_gain[1];
  localDW->FIR_IMUaccel_states[localDW->FIR_IMUaccel_circBuf + 10] =
    localB->inverseIMU_gain[2];

  /* End of Update for DiscreteFir: '<S273>/FIR_IMUaccel' */

  /* Update for Delay: '<S395>/MemoryX' */
  localDW->icLoad_n = false;

  /* Product: '<S415>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S395>/A'
   *  Delay: '<S395>/MemoryX'
   */
  localB->Bias_k = localP->A_Value_d[0] * localDW->MemoryX_DSTATE_p[0];
  localB->Bias1_c = localDW->MemoryX_DSTATE_p[0] * localP->A_Value_d[1];
  localB->Abs5 = localDW->MemoryX_DSTATE_p[1];

  /* Update for Delay: '<S395>/MemoryX' incorporates:
   *  Constant: '<S395>/A'
   *  Constant: '<S395>/B'
   *  Product: '<S415>/A[k]*xhat[k|k-1]'
   *  Product: '<S415>/B[k]*u[k]'
   *  Product: '<S446>/Product3'
   *  Reshape: '<S395>/Reshapeu'
   *  Sum: '<S415>/Add'
   */
  localDW->MemoryX_DSTATE_p[0] = ((localP->A_Value_d[2] * localB->Abs5 +
    localB->Bias_k) + localP->B_Value_nz[0] * localB->inverseIMU_gain[3]) +
    localB->MeasurementUpdate_n.Product3[0];
  localDW->MemoryX_DSTATE_p[1] = ((localP->A_Value_d[3] * localB->Abs5 +
    localB->Bias1_c) + localP->B_Value_nz[1] * localB->inverseIMU_gain[3]) +
    localB->MeasurementUpdate_n.Product3[1];

  /* Switch: '<S455>/FixPt Switch' */
  if (localDW->Output_DSTATE > localP->WrapToZero_Threshold_j) {
    /* Sum: '<S454>/FixPt Sum1' incorporates:
     *  Constant: '<S455>/Constant'
     *  UnitDelay: '<S452>/Output'
     */
    localDW->Output_DSTATE = localP->Constant_Value_n;
  }

  /* End of Switch: '<S455>/FixPt Switch' */

  /* Update for Delay: '<S461>/MemoryX' */
  localDW->icLoad_k = false;

  /* Update for DiscreteFilter: '<S273>/IIR_IMUgyro_r' */
  localDW->IIR_IMUgyro_r_states[4] = localDW->IIR_IMUgyro_r_states[3];

  /* Update for Delay: '<S461>/MemoryX' incorporates:
   *  Reshape: '<S499>/Reshape'
   */
  localDW->MemoryX_DSTATE_a[0] = localB->posVIS_data[0];

  /* Update for DiscreteFilter: '<S273>/IIR_IMUgyro_r' */
  localDW->IIR_IMUgyro_r_states[3] = localDW->IIR_IMUgyro_r_states[2];

  /* Update for Delay: '<S461>/MemoryX' incorporates:
   *  Reshape: '<S499>/Reshape'
   */
  localDW->MemoryX_DSTATE_a[1] = localB->posVIS_data[1];

  /* Update for DiscreteFilter: '<S273>/IIR_IMUgyro_r' */
  localDW->IIR_IMUgyro_r_states[2] = localDW->IIR_IMUgyro_r_states[1];

  /* Update for Delay: '<S461>/MemoryX' incorporates:
   *  Reshape: '<S499>/Reshape'
   */
  localDW->MemoryX_DSTATE_a[2] = localB->posVIS_data[2];

  /* Update for DiscreteFilter: '<S273>/IIR_IMUgyro_r' */
  localDW->IIR_IMUgyro_r_states[1] = localDW->IIR_IMUgyro_r_states[0];

  /* Update for Delay: '<S461>/MemoryX' incorporates:
   *  Reshape: '<S499>/Reshape'
   */
  localDW->MemoryX_DSTATE_a[3] = localB->posVIS_data[3];

  /* Update for DiscreteFilter: '<S273>/IIR_IMUgyro_r' */
  localDW->IIR_IMUgyro_r_states[0] = localB->DiscreteTimeIntegrator_l;

  /* Switch: '<S536>/FixPt Switch' */
  if (localDW->Output_DSTATE_i > localP->WrapToZero_Threshold_l) {
    /* Sum: '<S535>/FixPt Sum1' incorporates:
     *  Constant: '<S536>/Constant'
     *  UnitDelay: '<S534>/Output'
     */
    localDW->Output_DSTATE_i = localP->Constant_Value_i;
  }

  /* End of Switch: '<S536>/FixPt Switch' */
  for (localB->i = 0; localB->i < 2; localB->i++) {
    /* Update for DiscreteFilter: '<S460>/IIRgyroz' */
    localB->memOffset = localB->i * 5;
    localDW->IIRgyroz_states[localB->memOffset + 4] = localDW->
      IIRgyroz_states[localB->memOffset + 3];
    localDW->IIRgyroz_states[localB->memOffset + 3] = localDW->
      IIRgyroz_states[localB->memOffset + 2];
    localDW->IIRgyroz_states[localB->memOffset + 2] = localDW->
      IIRgyroz_states[localB->memOffset + 1];
    localDW->IIRgyroz_states[localB->memOffset + 1] = localDW->
      IIRgyroz_states[localB->memOffset];
    localDW->IIRgyroz_states[localB->memOffset] = localDW->IIRgyroz_tmp
      [localB->i];

    /* Update for UnitDelay: '<S468>/UD' incorporates:
     *  Sum: '<S468>/Diff'
     */
    localDW->UD_DSTATE[localB->i] = localB->Conversion_n[localB->i];

    /* Update for Delay: '<S456>/Delay' */
    localB->vbat_V = localB->Reshapexhat[localB->i];
    localDW->Delay_DSTATE[localB->i] = localB->vbat_V;

    /* Update for Delay: '<S7>/Delay1' */
    localDW->Delay1_DSTATE[localB->i] = localB->vbat_V;
  }

  /* Update for Delay: '<S21>/MemoryX' */
  localDW->icLoad_b = false;

  /* Product: '<S152>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S21>/A'
   *  Delay: '<S21>/MemoryX'
   */
  localB->Bias_k = 0.0F;
  localB->Bias1_c = 0.0F;
  localB->vbat_V = 0.0F;
  localB->ManualSwitch1 = 0.0F;
  for (localB->i = 0; localB->i < 4; localB->i++) {
    localB->Abs5 = localDW->MemoryX_DSTATE_b[localB->i];
    localB->j = localB->i << 2;
    localB->Bias_k += localP->A_Value_l[localB->j] * localB->Abs5;
    localB->Bias1_c += localP->A_Value_l[localB->j + 1] * localB->Abs5;
    localB->vbat_V += localP->A_Value_l[localB->j + 2] * localB->Abs5;
    localB->ManualSwitch1 += localP->A_Value_l[localB->j + 3] * localB->Abs5;
  }

  /* End of Product: '<S152>/A[k]*xhat[k|k-1]' */

  /* Update for Delay: '<S21>/MemoryX' incorporates:
   *  Constant: '<S21>/B'
   *  Product: '<S152>/B[k]*u[k]'
   *  Product: '<S183>/Product3'
   *  Reshape: '<S21>/Reshapeu'
   *  Sum: '<S152>/Add'
   */
  localDW->MemoryX_DSTATE_b[0] = (localP->B_Value_i[0] * localB->Bias +
    localB->Bias_k) + localB->MeasurementUpdate_jc.Product3[0];
  localDW->MemoryX_DSTATE_b[1] = (localP->B_Value_i[1] * localB->Bias +
    localB->Bias1_c) + localB->MeasurementUpdate_jc.Product3[1];
  localDW->MemoryX_DSTATE_b[2] = (localP->B_Value_i[2] * localB->Bias +
    localB->vbat_V) + localB->MeasurementUpdate_jc.Product3[2];
  localDW->MemoryX_DSTATE_b[3] = (localP->B_Value_i[3] * localB->Bias +
    localB->ManualSwitch1) + localB->MeasurementUpdate_jc.Product3[3];

  /* Update for DiscreteIntegrator: '<S8>/Discrete-Time Integrator' incorporates:
   *  Delay: '<S8>/Delay'
   *  Gain: '<S8>/antiWU_Gain'
   *  Gain: '<S8>/antiWU_Gain1'
   *  Sum: '<S8>/Add'
   */
  localB->vbat_V = (localB->rtb_pitchrollerror_l_idx_0 -
                    localP->antiWU_Gain_Gain * localDW->Delay_DSTATE_f[0] *
                    localP->antiWU_Gain1_Gain) *
    localP->DiscreteTimeIntegrator_gainval_i +
    localDW->DiscreteTimeIntegrator_DSTATE_c[0];
  localDW->DiscreteTimeIntegrator_DSTATE_c[0] = localB->vbat_V;
  if (localB->vbat_V > localP->DiscreteTimeIntegrator_UpperSat) {
    localDW->DiscreteTimeIntegrator_DSTATE_c[0] =
      localP->DiscreteTimeIntegrator_UpperSat;
  } else if (localB->vbat_V < localP->DiscreteTimeIntegrator_LowerSat) {
    localDW->DiscreteTimeIntegrator_DSTATE_c[0] =
      localP->DiscreteTimeIntegrator_LowerSat;
  }

  localB->vbat_V = (localB->rtb_sincos_o1_idx_1 - localP->antiWU_Gain_Gain *
                    localDW->Delay_DSTATE_f[1] * localP->antiWU_Gain1_Gain) *
    localP->DiscreteTimeIntegrator_gainval_i +
    localDW->DiscreteTimeIntegrator_DSTATE_c[1];
  localDW->DiscreteTimeIntegrator_DSTATE_c[1] = localB->vbat_V;
  if (localB->vbat_V > localP->DiscreteTimeIntegrator_UpperSat) {
    localDW->DiscreteTimeIntegrator_DSTATE_c[1] =
      localP->DiscreteTimeIntegrator_UpperSat;
  } else if (localB->vbat_V < localP->DiscreteTimeIntegrator_LowerSat) {
    localDW->DiscreteTimeIntegrator_DSTATE_c[1] =
      localP->DiscreteTimeIntegrator_LowerSat;
  }

  /* End of Update for DiscreteIntegrator: '<S8>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S15>/Discrete-Time Integrator2' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  Sum: '<S15>/Subtract1'
   */
  localDW->DiscreteTimeIntegrator2_DSTATE += ((real32_T)localB->Saturation -
    localB->SimplyIntegrateVelocity[0]) *
    localP->DiscreteTimeIntegrator2_gainval;

  /* Update for Delay: '<S20>/MemoryX' incorporates:
   *  Constant: '<S20>/B'
   *  Product: '<S129>/Product3'
   *  Product: '<S98>/B[k]*u[k]'
   *  Reshape: '<S20>/Reshapeu'
   *  Sum: '<S98>/Add'
   */
  localDW->icLoad_i = false;
  localDW->MemoryX_DSTATE_pv[0] = (localP->B_Value_n[0] * localB->Bias1 +
    localB->Reshapexhat_p[0]) + localB->MeasurementUpdate_j.Product3[0];
  localDW->MemoryX_DSTATE_pv[1] = (localP->B_Value_n[1] * localB->Bias1 +
    localB->Reshapexhat_p[1]) + localB->MeasurementUpdate_j.Product3[1];
  localDW->MemoryX_DSTATE_pv[2] = (localP->B_Value_n[2] * localB->Bias1 +
    localB->Reshapexhat_p[2]) + localB->MeasurementUpdate_j.Product3[2];
  localDW->MemoryX_DSTATE_pv[3] = (localP->B_Value_n[3] * localB->Bias1 +
    localB->Reshapexhat_p[3]) + localB->MeasurementUpdate_j.Product3[3];

  /* Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator2' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  Sum: '<S14>/Subtract1'
   */
  localDW->DiscreteTimeIntegrator2_DSTATE_h += ((real32_T)
    localB->rtb_Product1_idx_1 - localB->SimplyIntegrateVelocity[1]) *
    localP->DiscreteTimeIntegrator2_gainval_m;

  /* Switch: '<S243>/FixPt Switch' */
  if (localDW->Output_DSTATE_n > localP->WrapToZero_Threshold_m) {
    /* Sum: '<S242>/FixPt Sum1' incorporates:
     *  Constant: '<S243>/Constant'
     *  UnitDelay: '<S241>/Output'
     */
    localDW->Output_DSTATE_n = localP->Constant_Value_mc;
  }

  /* End of Switch: '<S243>/FixPt Switch' */

  /* Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S13>/I_pr'
   */
  localDW->DiscreteTimeIntegrator_DSTATE_m += localP->I_pr_Gain_b *
    localB->rtb_sincos_o1_idx_2 * localP->DiscreteTimeIntegrator_gainval_b;
  if (localDW->DiscreteTimeIntegrator_DSTATE_m >
      localP->DiscreteTimeIntegrator_UpperSat_n) {
    localDW->DiscreteTimeIntegrator_DSTATE_m =
      localP->DiscreteTimeIntegrator_UpperSat_n;
  } else if (localDW->DiscreteTimeIntegrator_DSTATE_m <
             localP->DiscreteTimeIntegrator_LowerSat_d) {
    localDW->DiscreteTimeIntegrator_DSTATE_m =
      localP->DiscreteTimeIntegrator_LowerSat_d;
  }

  localDW->DiscreteTimeIntegrator_PrevResetState = (int8_T)localB->Compare_e3;

  /* End of Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */

  /* Update for Delay: '<S19>/MemoryX' */
  localDW->icLoad_o = false;

  /* Product: '<S44>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S19>/A'
   *  Delay: '<S19>/MemoryX'
   */
  localB->Bias_k = localP->A_Value_i[0] * localDW->MemoryX_DSTATE_e[0];
  localB->Bias1_c = localDW->MemoryX_DSTATE_e[0] * localP->A_Value_i[1];
  localB->Abs5 = localDW->MemoryX_DSTATE_e[1];

  /* Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator2' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  Sum: '<S17>/Subtract1'
   */
  localDW->DiscreteTimeIntegrator2_DSTATE_p += ((real32_T)
    localB->rtb_Product1_idx_2 - localB->DataTypeConversion) *
    localP->DiscreteTimeIntegrator2_gainval_g;

  /* Update for Delay: '<S22>/MemoryX' */
  localDW->icLoad_h = false;

  /* Update for Delay: '<S19>/MemoryX' incorporates:
   *  Constant: '<S19>/A'
   *  Constant: '<S19>/B'
   *  Product: '<S44>/A[k]*xhat[k|k-1]'
   *  Product: '<S44>/B[k]*u[k]'
   *  Product: '<S75>/Product3'
   *  Reshape: '<S19>/Reshapeu'
   *  Sum: '<S44>/Add'
   */
  localDW->MemoryX_DSTATE_e[0] = ((localP->A_Value_i[2] * localB->Abs5 +
    localB->Bias_k) + localP->B_Value_c[0] * localB->Bias2) +
    localB->MeasurementUpdate.Product3[0];
  localDW->MemoryX_DSTATE_e[1] = ((localP->A_Value_i[3] * localB->Abs5 +
    localB->Bias1_c) + localP->B_Value_c[1] * localB->Bias2) +
    localB->MeasurementUpdate.Product3[1];

  /* Product: '<S206>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S22>/A'
   *  Delay: '<S22>/MemoryX'
   */
  localB->Bias_k = localP->A_Value_cc[0] * localDW->MemoryX_DSTATE_c[0];
  localB->Bias1_c = localDW->MemoryX_DSTATE_c[0] * localP->A_Value_cc[1];
  localB->Abs5 = localDW->MemoryX_DSTATE_c[1];

  /* Update for DiscreteIntegrator: '<S18>/Discrete-Time Integrator2' incorporates:
   *  BusAssignment: '<S5>/Bus  Assignment'
   *  Sum: '<S18>/Subtract1'
   */
  localDW->DiscreteTimeIntegrator2_DSTATE_d += (localB->rtb_sincos_o1_idx_0 -
    localB->DataTypeConversion3[0]) * localP->DiscreteTimeIntegrator2_gainval_mk;

  /* Update for Delay: '<S22>/MemoryX' incorporates:
   *  Constant: '<S22>/A'
   *  Constant: '<S22>/B'
   *  Product: '<S206>/A[k]*xhat[k|k-1]'
   *  Product: '<S206>/B[k]*u[k]'
   *  Product: '<S237>/Product3'
   *  Reshape: '<S22>/Reshapeu'
   *  Sum: '<S206>/Add'
   */
  localDW->MemoryX_DSTATE_c[0] = ((localP->A_Value_cc[2] * localB->Abs5 +
    localB->Bias_k) + localP->B_Value_g[0] * localB->Product_c[1]) +
    localB->MeasurementUpdate_c.Product3[0];

  /* Update for Delay: '<S8>/Delay' */
  localDW->Delay_DSTATE_f[0] = localB->Conversion_f[0];

  /* Update for Delay: '<S22>/MemoryX' incorporates:
   *  Constant: '<S22>/A'
   *  Constant: '<S22>/B'
   *  Product: '<S206>/A[k]*xhat[k|k-1]'
   *  Product: '<S206>/B[k]*u[k]'
   *  Product: '<S237>/Product3'
   *  Reshape: '<S22>/Reshapeu'
   *  Sum: '<S206>/Add'
   */
  localDW->MemoryX_DSTATE_c[1] = ((localP->A_Value_cc[3] * localB->Abs5 +
    localB->Bias1_c) + localP->B_Value_g[1] * localB->Product_c[1]) +
    localB->MeasurementUpdate_c.Product3[1];

  /* Update for Delay: '<S8>/Delay' */
  localDW->Delay_DSTATE_f[1] = localB->Conversion_f[1];

  /* Switch: '<S259>/FixPt Switch' */
  if (localDW->Output_DSTATE_ir > localP->WrapToZero_Threshold) {
    /* Sum: '<S258>/FixPt Sum1' incorporates:
     *  Constant: '<S259>/Constant'
     *  UnitDelay: '<S251>/Output'
     */
    localDW->Output_DSTATE_ir = localP->Constant_Value_d;
  }

  /* End of Switch: '<S259>/FixPt Switch' */
}

/* Model step function for TID0 */
void flightControlSystem_step0(void)   /* Sample time: [0.005s, 0.0s] */
{
  {                                    /* Sample time: [0.005s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* Outputs for Atomic SubSystem: '<Root>/Flight Control System' */

  /* Inport: '<Root>/AC cmd' incorporates:
   *  Inport: '<Root>/Sensors'
   */
  flightControlSystem_FlightControlSystem(flightControlSystem_M, &cmd_inport,
    &sensor_inport, &flightControlSystem_B.FlightControlSystem,
    &flightControlSystem_DW.FlightControlSystem,
    &flightControlSystem_P.FlightControlSystem,
    &flightControlSystem_PrevZCX.FlightControlSystem);

  /* End of Outputs for SubSystem: '<Root>/Flight Control System' */

  /* SignalConversion generated from: '<Root>/Flight Control System' */
  motors_outport[0] = flightControlSystem_B.FlightControlSystem.MotorDirections
    [0];

  /* Outport: '<Root>/Actuators' incorporates:
   *  SignalConversion generated from: '<Root>/Flight Control System'
   */
  flightControlSystem_Y.Actuators[0] =
    flightControlSystem_B.FlightControlSystem.MotorDirections[0];

  /* SignalConversion generated from: '<Root>/Flight Control System' */
  motors_outport[1] = flightControlSystem_B.FlightControlSystem.MotorDirections
    [1];

  /* Outport: '<Root>/Actuators' incorporates:
   *  SignalConversion generated from: '<Root>/Flight Control System'
   */
  flightControlSystem_Y.Actuators[1] =
    flightControlSystem_B.FlightControlSystem.MotorDirections[1];

  /* SignalConversion generated from: '<Root>/Flight Control System' */
  motors_outport[2] = flightControlSystem_B.FlightControlSystem.MotorDirections
    [2];

  /* Outport: '<Root>/Actuators' incorporates:
   *  SignalConversion generated from: '<Root>/Flight Control System'
   */
  flightControlSystem_Y.Actuators[2] =
    flightControlSystem_B.FlightControlSystem.MotorDirections[2];

  /* SignalConversion generated from: '<Root>/Flight Control System' */
  motors_outport[3] = flightControlSystem_B.FlightControlSystem.MotorDirections
    [3];

  /* Outport: '<Root>/Actuators' incorporates:
   *  SignalConversion generated from: '<Root>/Flight Control System'
   */
  flightControlSystem_Y.Actuators[3] =
    flightControlSystem_B.FlightControlSystem.MotorDirections[3];

  /* SignalConversion generated from: '<Root>/Flight Control System' */
  flag_outport = flightControlSystem_B.FlightControlSystem.Constant;

  /* Outport: '<Root>/Flag' */
  flightControlSystem_Y.Flag = flag_outport;

  /* Matfile logging */
  rt_UpdateTXYLogVars(flightControlSystem_M->rtwLogInfo,
                      (&flightControlSystem_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.005s, 0.0s] */
    if ((rtmGetTFinal(flightControlSystem_M)!=-1) &&
        !((rtmGetTFinal(flightControlSystem_M)-
           flightControlSystem_M->Timing.taskTime0) >
          flightControlSystem_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(flightControlSystem_M, "Simulation finished");
    }
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++flightControlSystem_M->Timing.clockTick0)) {
    ++flightControlSystem_M->Timing.clockTickH0;
  }

  flightControlSystem_M->Timing.taskTime0 =
    flightControlSystem_M->Timing.clockTick0 *
    flightControlSystem_M->Timing.stepSize0 +
    flightControlSystem_M->Timing.clockTickH0 *
    flightControlSystem_M->Timing.stepSize0 * 4294967296.0;
}

/* Model step function for TID1 */
void flightControlSystem_step1(void)   /* Sample time: [0.2s, 0.0s] */
{
  /* Outputs for Atomic SubSystem: '<Root>/Image Processing System' */
  /* MATLABSystem: '<S2>/PARROT Image Conversion' incorporates:
   *  Inport: '<Root>/Image Data'
   */
  MW_Build_RGB(&imRGB[0], &flightControlSystem_B.uv[0],
               &flightControlSystem_B.uv1[0], &flightControlSystem_B.uv2[0]);

  /* Constant: '<S2>/Constant' */
  flightControlSystem_B.Constant = flightControlSystem_P.Constant_Value;

  /* End of Outputs for SubSystem: '<Root>/Image Processing System' */
}

/* Model initialize function */
void flightControlSystem_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  flightControlSystem_P.FlightControlSystem.SaturationSonar_LowerSat =
    rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)flightControlSystem_M, 0,
                sizeof(RT_MODEL_flightControlSystem_T));
  rtmSetTFinal(flightControlSystem_M, 200.0);
  flightControlSystem_M->Timing.stepSize0 = 0.005;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    flightControlSystem_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(flightControlSystem_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(flightControlSystem_M->rtwLogInfo, (NULL));
    rtliSetLogT(flightControlSystem_M->rtwLogInfo, "tout");
    rtliSetLogX(flightControlSystem_M->rtwLogInfo, "");
    rtliSetLogXFinal(flightControlSystem_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(flightControlSystem_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(flightControlSystem_M->rtwLogInfo, 2);
    rtliSetLogMaxRows(flightControlSystem_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(flightControlSystem_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &flightControlSystem_Y.Actuators[0],
        &flightControlSystem_Y.Flag
      };

      rtliSetLogYSignalPtrs(flightControlSystem_M->rtwLogInfo,
                            ((LogSignalPtrsType)rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        4,
        1
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1,
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        4,
        1
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0,
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL),
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4,
        4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_SINGLE,
        SS_UINT8
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0,
        0
      };

      static RTWPreprocessingFcnPtr rt_LoggingPreprocessingFcnPtrs[] = {
        (NULL),
        (NULL)
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "motors",
        "flag" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "flightControlSystem/Actuators",
        "flightControlSystem/Flag" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_SINGLE, SS_SINGLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_UINT8, SS_UINT8, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          2,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedCurrentSignalDimensionsSize,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (NULL),
          rt_LoggingPreprocessingFcnPtrs,

          { rt_LoggedOutputLabels },
          (NULL),
          (NULL),
          (NULL),

          { rt_LoggedOutputBlockNames },

          { (NULL) },
          (NULL),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo(flightControlSystem_M->rtwLogInfo,
                            rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[1];
    }

    rtliSetLogY(flightControlSystem_M->rtwLogInfo, "yout");
  }

  /* block I/O */
  (void) memset(((void *) &flightControlSystem_B), 0,
                sizeof(B_flightControlSystem_T));

  /* exported global signals */
  motors_outport[0] = 0.0F;
  motors_outport[1] = 0.0F;
  motors_outport[2] = 0.0F;
  motors_outport[3] = 0.0F;
  flag_outport = 0U;

  /* states (dwork) */
  (void) memset((void *)&flightControlSystem_DW, 0,
                sizeof(DW_flightControlSystem_T));

  /* external inputs */
  (void)memset(&cmd_inport, 0, sizeof(CommandBus));
  (void)memset(&sensor_inport, 0, sizeof(SensorsBus));

  /* external outputs */
  (void)memset(&flightControlSystem_Y, 0, sizeof(ExtY_flightControlSystem_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(flightControlSystem_M->rtwLogInfo, 0.0,
    rtmGetTFinal(flightControlSystem_M), flightControlSystem_M->Timing.stepSize0,
    (&rtmGetErrorStatus(flightControlSystem_M)));

  /* SetupRuntimeResources for Atomic SubSystem: '<Root>/Flight Control System' */
  flightControlSystem_FlightControlSystem_SetupRTR(flightControlSystem_M,
    &flightControlSystem_DW.FlightControlSystem);

  /* End of SetupRuntimeResources for SubSystem: '<Root>/Flight Control System' */

  /* Start for Atomic SubSystem: '<Root>/Flight Control System' */
  flightControlSystem_FlightControlSystem_Start
    (&flightControlSystem_DW.FlightControlSystem);

  /* End of Start for SubSystem: '<Root>/Flight Control System' */

  /* Start for Atomic SubSystem: '<Root>/Image Processing System' */
  /* Start for MATLABSystem: '<S2>/PARROT Image Conversion' */
  flightControlSystem_DW.objisempty = true;
  flightControlSystem_DW.obj.isInitialized = 1;

  /* End of Start for SubSystem: '<Root>/Image Processing System' */
  flightControlSystem_PrevZCX.FlightControlSystem.TriggeredSubsystem_Trig_ZCE =
    UNINITIALIZED_ZCSIG;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Flight Control System' */
  flightControlSystem_FlightControlSystem_Init
    (&flightControlSystem_B.FlightControlSystem,
     &flightControlSystem_DW.FlightControlSystem,
     &flightControlSystem_P.FlightControlSystem,
     &flightControlSystem_PrevZCX.FlightControlSystem);

  /* End of SystemInitialize for SubSystem: '<Root>/Flight Control System' */
}

/* Model terminate function */
void flightControlSystem_terminate(void)
{
  /* (no terminate code required) */
}
