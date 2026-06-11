/*
 * flightControlSystem_data.c
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

/* Block parameters (default storage) */
P_flightControlSystem_T flightControlSystem_P = {
  /* Variable: Sensors
   * Referenced by:
   *   '<S276>/SaturationSonar'
   *   '<S330>/Constant'
   */
  {
    { 1.00596, 1.00383, 0.99454 },

    { 0.99861, 1.00644, 0.99997 },

    {
      { 0.0, 0.0, 0.0 },

      { 0.0, 0.0, 0.0 },
      190.0,
      0.707,

      { 1.00596, 0.0, 0.0, 0.0, 1.00383, 0.0, 0.0, 0.0, 0.99454 },

      { 0.09, -0.06, 0.33699999999999974 },

      { -50.0, -50.0, -50.0, 50.0, 50.0, 50.0 },
      190.0,
      0.707,

      { 0.99861, 0.0, 0.0, 0.0, 1.00644, 0.0, 0.0, 0.0, 0.99997 },

      { -0.0095, -0.0075, 0.0015 },

      { 0.0, 0.0, 0.0 },

      { -10.0, -10.0, -10.0, 10.0, 10.0, 10.0 },

      { 41.0, 41.0, 41.0, 41.0, 41.0, 41.0 },

      { 0.8, 0.8, 0.8, 0.025, 0.025, 0.025 },

      { 0.00021831529882618725, 0.00018641345254680647, 0.00037251068300213613,
        1.0651514622688397e-8, 1.3021327403798377e-8, 1.1929474437781302e-8 }
    },

    {
      1.0,
      41.0
    },
    -99.0,
    -9.0,

    {
      { -99.0, 0.0, 0.0, -9.0 },
      0.0,

      { 3.5, 70.0 }
    },
    1.0,
    1.225,
    12.01725,
    101270.95,

    { 0.99407531114557246, 0.99618461293246863, 1.0054899752649467,
      1.0013919347893572, 0.99360120821906917, 1.0000300009000269 },
    0.44,
    1.0
  },

  /* Variable: Ts
   * Referenced by:
   *   '<S265>/Step'
   *   '<S265>/Step2'
   */
  0.005,

  /* Variable: Kd1
   * Referenced by: '<S17>/Gain7'
   */
  { 0.600377083F, 0.352105677F },

  /* Variable: Kd2
   * Referenced by: '<S14>/Gain7'
   */
  { 0.000590801355F, 0.00526018953F, 0.000769362494F, 0.0015913531F },

  /* Variable: Kd3
   * Referenced by: '<S15>/Gain7'
   */
  { -0.000599167834F, 0.00538746826F, -0.000783628959F, 0.00165457942F },

  /* Variable: Kd4
   * Referenced by: '<S18>/Gain7'
   */
  { 0.0035817863F, 0.0013315531F },

  /* Variable: Kid1
   * Referenced by: '<S17>/Gain4'
   */
  -0.440947562F,

  /* Variable: Kid2
   * Referenced by: '<S14>/Gain4'
   */
  -0.000148514155F,

  /* Variable: Kid3
   * Referenced by: '<S15>/Gain4'
   */
  0.000150300766F,

  /* Variable: Kid4
   * Referenced by: '<S18>/Gain4'
   */
  -0.00331213977F,

  /* Expression: 0
   * Referenced by: '<S2>/Constant'
   */
  0.0,

  /* Start of '<Root>/Flight Control System' */
  {
    /* Mask Parameter: outlierBelowFloor_const
     * Referenced by: '<S278>/Constant'
     */
    0.0,

    /* Mask Parameter: outlierJump_const
     * Referenced by: '<S333>/Constant'
     */
    0.1,

    /* Mask Parameter: currentEstimateVeryOffFromPressure_const
     * Referenced by: '<S331>/Constant'
     */
    0.8,

    /* Mask Parameter: currentStateVeryOffsonarflt_const
     * Referenced by: '<S332>/Constant'
     */
    0.4,

    /* Mask Parameter: ComparewithStoptime_const
     * Referenced by: '<S267>/Constant'
     */
    5.0,

    /* Mask Parameter: Checkerrorcondition_const
     * Referenced by: '<S262>/Constant'
     */
    -1.0,

    /* Mask Parameter: u0continuousOFerrors_const
     * Referenced by: '<S261>/Constant'
     */
    50.0,

    /* Mask Parameter: DiscreteDerivative_ICPrevScaledInput
     * Referenced by: '<S468>/UD'
     */
    0.0F,

    /* Mask Parameter: Checkifthedroneis03maboveground_const
     * Referenced by: '<S260>/Constant'
     */
    -0.3F,

    /* Mask Parameter: CompareToConstant_const
     * Referenced by: '<S335>/Constant'
     */
    6.867F,

    /* Mask Parameter: CompareToConstant1_const
     * Referenced by: '<S336>/Constant'
     */
    12.753F,

    /* Mask Parameter: maxp_const
     * Referenced by: '<S471>/Constant'
     */
    0.6F,

    /* Mask Parameter: maxq_const
     * Referenced by: '<S473>/Constant'
     */
    0.6F,

    /* Mask Parameter: maxw1_const
     * Referenced by: '<S475>/Constant'
     */
    7.0F,

    /* Mask Parameter: maxw2_const
     * Referenced by: '<S476>/Constant'
     */
    7.0F,

    /* Mask Parameter: maxdw1_const
     * Referenced by: '<S469>/Constant'
     */
    80.0F,

    /* Mask Parameter: maxdw2_const
     * Referenced by: '<S470>/Constant'
     */
    80.0F,

    /* Mask Parameter: maxp2_const
     * Referenced by: '<S472>/Constant'
     */
    0.5F,

    /* Mask Parameter: maxq2_const
     * Referenced by: '<S474>/Constant'
     */
    0.5F,

    /* Mask Parameter: maxw3_const
     * Referenced by: '<S477>/Constant'
     */
    5.0F,

    /* Mask Parameter: maxw4_const
     * Referenced by: '<S478>/Constant'
     */
    5.0F,

    /* Mask Parameter: minHeightforOF_const
     * Referenced by: '<S479>/Constant'
     */
    -0.4F,

    /* Mask Parameter: DeactivateAccelerationIfOFisnotusedduetolowaltitude_const
     * Referenced by: '<S463>/Constant'
     */
    -0.4F,

    /* Mask Parameter: donotuseaccifopticalflowneveravailableNoteOF60HzbutZOHto200_con
     * Referenced by: '<S465>/Constant'
     */
    0.0F,

    /* Mask Parameter: donotuseaccifopticalflowneveravailableNoteOF60HzbutZOHto2001_co
     * Referenced by: '<S466>/Constant'
     */
    0.0F,

    /* Mask Parameter: CompareToConstant_const_m
     * Referenced by: '<S245>/Constant'
     */
    10.0F,

    /* Mask Parameter: CompareToConstant1_const_m
     * Referenced by: '<S246>/Constant'
     */
    10.0F,

    /* Mask Parameter: CompareToConstant2_const
     * Referenced by: '<S247>/Constant'
     */
    6.0F,

    /* Mask Parameter: CompareToConstant4_const
     * Referenced by: '<S249>/Constant'
     */
    0.01F,

    /* Mask Parameter: CompareToConstant3_const
     * Referenced by: '<S248>/Constant'
     */
    6.0F,

    /* Mask Parameter: CompareToConstant5_const
     * Referenced by: '<S250>/Constant'
     */
    0.01F,

    /* Mask Parameter: WrapToZero_Threshold
     * Referenced by: '<S259>/FixPt Switch'
     */
    4294967295U,

    /* Mask Parameter: WrapToZero_Threshold_l
     * Referenced by: '<S536>/FixPt Switch'
     */
    4294967295U,

    /* Mask Parameter: WrapToZero_Threshold_j
     * Referenced by: '<S455>/FixPt Switch'
     */
    4294967295U,

    /* Mask Parameter: CompareToConstant_const_p
     * Referenced by: '<S451>/Constant'
     */
    1U,

    /* Mask Parameter: CompareToConstant_const_mg
     * Referenced by: '<S533>/Constant'
     */
    800U,

    /* Mask Parameter: WrapToZero_Threshold_m
     * Referenced by: '<S243>/FixPt Switch'
     */
    65535U,

    /* Mask Parameter: CompareToConstant_const_pa
     * Referenced by: '<S240>/Constant'
     */
    100U,

    /* Expression: 0
     * Referenced by: '<S255>/ Disable OF check'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S255>/ '
     */
    0.0,

    /* Expression: 1.1
     * Referenced by: '<S265>/Saturation'
     */
    1.1,

    /* Expression: 0
     * Referenced by: '<S265>/Saturation'
     */
    0.0,

    /* Expression: -1.1
     * Referenced by: '<S265>/zValue2'
     */
    -1.1,

    /* Expression: 0
     * Referenced by: '<S327>/L*(y[k]-yhat[k|k-1])'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S329>/deltax'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S449>/Constant'
     */
    0.0,

    /* Expression: pInitialization.M
     * Referenced by: '<S132>/KalmanGainM'
     */
    { 0.66899054587941487, -1.6723680814042519E-11, 4.9272455398196021E-8,
      -2.699782739285786E-16, -4.6988665882002928E-8, 0.99881825255467716,
      -5.7247617949721788E-7, 6.8468961604147011E-11, 1.6258577993291225E-5,
      -6.7231767632703613E-8, 0.99011214336900755, -1.6461880801606114E-12,
      -1.0819374525380652E-10, 9.7657552372827914E-9, -1.9992837556107621E-9,
      0.99834449503519529 },

    /* Expression: pInitialization.M
     * Referenced by: '<S78>/KalmanGainM'
     */
    { 0.75405855183284243, 2.5290718145922439E-11, 6.2550159494127452E-8,
      3.4309068202850266E-16, 3.110474313486499E-8, 0.99894715984079441,
      5.1009405844622494E-7, 4.5657726153972918E-11, 1.2070574041000511E-5,
      8.0035803663454454E-8, 0.99011215263978825, 1.646610316684944E-12,
      8.0408768513718254E-11, 8.7004819194496532E-9, 1.99979655887681E-9,
      0.9983444950351954 },

    /* Expression: pInitialization.L
     * Referenced by: '<S78>/KalmanGainL'
     */
    { 0.75405855214559625, 2.529074706871513E-11, 6.2551400008992668E-8,
      3.3912533118551743E-16, 0.00012252955068889853, 0.998947159841022,
      0.04899886828425494, 4.5657723977038777E-11, 0.004962631347054311,
      8.0035811022033476E-8, 0.99011215656554419, 1.6466098397775714E-12,
      2.0412813275566781E-7, 0.0049917311756593587, 0.00012242442025871028,
      0.99834449503519507 },

    /* Expression: pInitialization.L
     * Referenced by: '<S132>/KalmanGainL'
     */
    { 0.66899054612577935, -1.6723670070825957E-11, 4.9273275697359154E-8,
      -2.7083160051175676E-16, -0.00012252993926537784, 0.99881825255501966,
      -0.048992607763994916, 6.8468926518552725E-11, 0.0049668193030824913,
      -6.7231776094989885E-8, 0.99011214666672587, -1.646190373992567E-12,
      -2.0415604598062089E-7, 0.00499173224093086, -0.00012242447199802827,
      0.99834449503519562 },

    /* Expression: 0
     * Referenced by: '<S271>/Delay2'
     */
    0.0,

    /* Expression: pInitialization.X0
     * Referenced by: '<S275>/X0'
     */
    { -0.05, 0.0 },

    /* Expression: -inf
     * Referenced by: '<S276>/SaturationSonar'
     */
    0.0,

    /* Expression: Estimator.alt.filterSonarNum
     * Referenced by: '<S276>/sonarFilter_IIR'
     */
    { 3.7568380197512489E-6, 1.1270514059253748E-5, 1.1270514059253748E-5,
      3.7568380197512489E-6 },

    /* Expression: Estimator.alt.filterSonarDen
     * Referenced by: '<S276>/sonarFilter_IIR'
     */
    { 1.0, -2.9371707284498907, 2.8762997234793319, -0.939098940325283 },

    /* Expression: 0
     * Referenced by: '<S276>/sonarFilter_IIR'
     */
    0.0,

    /* Expression: pInitialization.M
     * Referenced by: '<S279>/KalmanGainM'
     */
    { 0.026241420641871391, 0.069776736071492484 },

    /* Expression: pInitialization.C
     * Referenced by: '<S275>/C'
     */
    { 1.0, 0.0 },

    /* Expression: pInitialization.M
     * Referenced by: '<S342>/KalmanGainM'
     */
    { 0.0011869299883613858, -3.2868164179504482E-5 },

    /* Expression: pInitialization.M
     * Referenced by: '<S396>/KalmanGainM'
     */
    { 0.0011869299883613858, -3.2868164179504482E-5 },

    /* Expression: pInitialization.M
     * Referenced by: '<S480>/KalmanGainM'
     */
    { 0.066408162001371465, 0.0, -0.021605460397766958, 0.0, 0.0,
      0.066408162001371465, 0.0, -0.021605460397766958 },

    /* Expression: pInitialization.L
     * Referenced by: '<S480>/KalmanGainL'
     */
    { 0.066516189303360257, 4.5053399924773407E-19, -0.021605460397767236,
      2.4451005888416897E-19, -1.4532182529622698E-18, 0.066516189303360257,
      4.1595130505436516E-18, -0.021605460397767229 },

    /* Expression: 10
     * Referenced by: '<S265>/Step1'
     */
    10.0,

    /* Expression: 0
     * Referenced by: '<S265>/Step1'
     */
    0.0,

    /* Expression: 0.5
     * Referenced by: '<S265>/Step1'
     */
    0.5,

    /* Computed Parameter: DiscreteTimeIntegrator_gainval
     * Referenced by: '<S265>/Discrete-Time Integrator'
     */
    0.005,

    /* Expression: 0
     * Referenced by: '<S265>/Discrete-Time Integrator'
     */
    0.0,

    /* Expression: 3
     * Referenced by: '<S266>/Step8'
     */
    3.0,

    /* Expression: 0
     * Referenced by: '<S266>/Step8'
     */
    0.0,

    /* Expression: 0.3
     * Referenced by: '<S266>/Step8'
     */
    0.3,

    /* Expression: 20
     * Referenced by: '<S266>/Step9'
     */
    20.0,

    /* Expression: 0
     * Referenced by: '<S266>/Step9'
     */
    0.0,

    /* Expression: -0.3
     * Referenced by: '<S266>/Step9'
     */
    -0.3,

    /* Expression: 0
     * Referenced by: '<S266>/Gain'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S266>/xValue4'
     */
    0.0,

    /* Expression: [0 0 -g]
     * Referenced by: '<S458>/gravity'
     */
    { 0.0, 0.0, -9.81 },

    /* Expression: 1
     * Referenced by: '<S458>/gainaccinput1'
     */
    1.0,

    /* Expression: pInitialization.M
     * Referenced by: '<S24>/KalmanGainM'
     */
    { 0.98414241990097184, 1.2729610817808137E-7, 1.2547769187713996E-6,
      0.98391988651116691 },

    /* Expression: pInitialization.M
     * Referenced by: '<S186>/KalmanGainM'
     */
    { 0.78523843137442406, 1.2538260525384328E-9, 6.7874019852921428E-6,
      0.99364739590393336 },

    /* Expression: pInitialization.L
     * Referenced by: '<S24>/KalmanGainL'
     */
    { 0.98414242053745227, 1.2729610816421046E-7, 0.00492085420947469,
      0.983919886511167 },

    /* Expression: pInitialization.L
     * Referenced by: '<S186>/KalmanGainL'
     */
    { 0.78523843138069271, 1.2538260458157523E-9, 0.0049750243815062413,
      0.99364739590393358 },

    /* Expression: pInitialization.A
     * Referenced by: '<S275>/A'
     */
    { 1.0, 0.0, 0.005, 1.0 },

    /* Expression: [0 0 g]
     * Referenced by: '<S271>/gravity'
     */
    { 0.0, 0.0, 9.81 },

    /* Expression: pInitialization.L
     * Referenced by: '<S396>/KalmanGainL'
     */
    { 0.0011870943291822833, -3.2868164179504543E-5 },

    /* Expression: pInitialization.L
     * Referenced by: '<S342>/KalmanGainL'
     */
    { 0.0011870943291822833, -3.2868164179504543E-5 },

    /* Expression: pInitialization.B
     * Referenced by: '<S275>/B'
     */
    { 0.0, 0.005 },

    /* Expression: pInitialization.D
     * Referenced by: '<S275>/D'
     */
    0.0,

    /* Expression: pInitialization.L
     * Referenced by: '<S279>/KalmanGainL'
     */
    { 0.026590304322228815, 0.06977673607149136 },

    /* Expression: 200*3
     * Referenced by: '<S4>/Wait  3 Seconds'
     */
    600.0,

    /* Expression: 0.0
     * Referenced by: '<S255>/Delay One Step'
     */
    0.0,

    /* Expression: 0.5
     * Referenced by: '<S244>/0.5 meters'
     */
    0.5,

    /* Expression: pInitialization.Z
     * Referenced by: '<S78>/CovarianceZ'
     */
    { 0.32289541248034143, 1.0829738417265948E-11, 2.6784603796980133E-8,
      1.4691486095141464E-16, 1.0829738417265952E-11, 0.00034780343264176941,
      1.775994483292228E-10, 1.589665051502758E-14, 2.678460379698013E-8,
      1.7759944832922285E-10, 0.00219705886670769, 3.6538282927238262E-15,
      1.4691486095141469E-16, 1.5896650515027583E-14, 3.6538282927238254E-15,
      1.8240752268788057E-6 },

    /* Expression: pInitialization.Z
     * Referenced by: '<S132>/CovarianceZ'
     */
    { 0.48984156759836633, -1.224524632884996E-11, 3.6077784567113219E-8,
      -1.9768079195323005E-16, -1.2245246328849962E-11, 0.00026029203661574887,
      -1.4918729237697528E-10, 1.7843011394040083E-14, 3.6077784567113226E-8,
      -1.4918729237697538E-10, 0.0021970588461358276, -3.6528913498764256E-15,
      -1.9768079195323007E-16, 1.7843011394040087E-14, -3.6528913498764256E-15,
      1.8240752268788053E-6 },

    /* Expression: pInitialization.Z
     * Referenced by: '<S480>/CovarianceZ'
     */
    { 1.3281632400274295, 0.0, -0.43210920795533914, 0.0, 0.0,
      1.3281632400274295, 0.0, -0.43210920795533914, -0.43210920795533914, 0.0,
      6.147349862376486, 0.0, 0.0, -0.43210920795533914, 0.0, 6.147349862376486
    },

    /* Expression: pInitialization.Z
     * Referenced by: '<S24>/CovarianceZ'
     */
    { 0.0017724404982416503, 2.2926029082872242E-10, 2.2926029082872242E-10,
      0.00017977200246445532 },

    /* Expression: pInitialization.Z
     * Referenced by: '<S186>/CovarianceZ'
     */
    { 0.03008484002124831, 4.8037837550905165E-11, 4.8037837550905159E-11,
      7.0325394445100878E-6 },

    /* Expression: pInitialization.Z
     * Referenced by: '<S279>/CovarianceZ'
     */
    { 0.0026241420641871386, 0.0069776736071492486, 0.0069776736071492486,
      0.037607692935053887 },

    /* Expression: pInitialization.P0
     * Referenced by: '<S275>/P0'
     */
    { 0.0026948589925820136, 0.0071657120718245319, 0.0071657120718245319,
      0.038107692935053894 },

    /* Expression: pInitialization.Z
     * Referenced by: '<S342>/CovarianceZ'
     */
    { 1097.3834951566071, -30.388465402648372, -30.388465402648375,
      7.2223686232287516 },

    /* Expression: pInitialization.Z
     * Referenced by: '<S396>/CovarianceZ'
     */
    { 1097.3834951566071, -30.388465402648372, -30.388465402648375,
      7.2223686232287516 },

    /* Expression: pInitialization.G
     * Referenced by: '<S275>/G'
     */
    { 0.0, 1.0 },

    /* Expression: 10
     * Referenced by: '<S265>/Step4'
     */
    10.0,

    /* Expression: 0
     * Referenced by: '<S265>/Step4'
     */
    0.0,

    /* Expression: -0.25
     * Referenced by: '<S265>/Step4'
     */
    -0.25,

    /* Expression: 20
     * Referenced by: '<S265>/Step5'
     */
    20.0,

    /* Expression: 0
     * Referenced by: '<S265>/Step5'
     */
    0.0,

    /* Expression: 0.25
     * Referenced by: '<S265>/Step5'
     */
    0.25,

    /* Expression: 0
     * Referenced by: '<S265>/Constant'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S265>/Step'
     */
    0.0,

    /* Expression: 10
     * Referenced by: '<S265>/Step'
     */
    10.0,

    /* Expression: 0
     * Referenced by: '<S265>/Step2'
     */
    0.0,

    /* Expression: 1
     * Referenced by: '<S265>/Step2'
     */
    1.0,

    /* Expression: 0
     * Referenced by: '<S265>/xValue2'
     */
    0.0,

    /* Expression: pInitialization.H
     * Referenced by: '<S275>/H'
     */
    0.0,

    /* Expression: pInitialization.N
     * Referenced by: '<S275>/N'
     */
    0.0,

    /* Expression: pInitialization.Q
     * Referenced by: '<S275>/Q'
     */
    0.0005,

    /* Expression: pInitialization.R
     * Referenced by: '<S275>/R'
     */
    0.1,

    /* Computed Parameter: D_yaw_Gain
     * Referenced by: '<S12>/D_yaw'
     */
    0.0003F,

    /* Computed Parameter: P_yaw_Gain
     * Referenced by: '<S12>/P_yaw'
     */
    0.001F,

    /* Expression: Controller.takeoffGain
     * Referenced by: '<S13>/takeoff_gain1'
     */
    0.45F,

    /* Computed Parameter: D_z1_Gain
     * Referenced by: '<S13>/D_z1'
     */
    0.5F,

    /* Computed Parameter: P_z1_Gain
     * Referenced by: '<S13>/P_z1'
     */
    0.8F,

    /* Computed Parameter: SaturationThrust1_UpperSat
     * Referenced by: '<S13>/SaturationThrust1'
     */
    1.20204329F,

    /* Computed Parameter: SaturationThrust1_LowerSat
     * Referenced by: '<S13>/SaturationThrust1'
     */
    -1.20204329F,

    /* Computed Parameter: Bias_Bias
     * Referenced by: '<S17>/Bias'
     */
    -0.61803F,

    /* Computed Parameter: D_xy_Gain
     * Referenced by: '<S11>/D_xy'
     */
    { 0.15F, -0.15F },

    /* Computed Parameter: Gain_Gain_i
     * Referenced by: '<S11>/Gain'
     */
    -1.0F,

    /* Computed Parameter: Saturation_UpperSat_l
     * Referenced by: '<S11>/Saturation'
     */
    3.0F,

    /* Computed Parameter: Saturation_LowerSat_h
     * Referenced by: '<S11>/Saturation'
     */
    -3.0F,

    /* Computed Parameter: P_xy_Gain
     * Referenced by: '<S11>/P_xy'
     */
    { -0.24F, 0.24F },

    /* Computed Parameter: _Value_a
     * Referenced by: '<S244>/    '
     */
    0.0F,

    /* Computed Parameter: X_Y0
     * Referenced by: '<S268>/X'
     */
    0.0F,

    /* Computed Parameter: Y_Y0
     * Referenced by: '<S268>/Y'
     */
    0.0F,

    /* Computed Parameter: LandingLookaheaddistance_Value
     * Referenced by: '<S264>/Landing Look-ahead distance'
     */
    0.2F,

    /* Computed Parameter: Gain_Gain_b
     * Referenced by: '<S449>/Gain'
     */
    0.00228F,

    /* Computed Parameter: Out1_Y0
     * Referenced by: '<S453>/Out1'
     */
    0.0F,

    /* Computed Parameter: Lykyhatkk1_Y0_e
     * Referenced by: '<S530>/L*(y[k]-yhat[k|k-1])'
     */
    0.0F,

    /* Computed Parameter: deltax_Y0_o
     * Referenced by: '<S532>/deltax'
     */
    0.0F,

    /* Computed Parameter: Gain_Gain_h
     * Referenced by: '<S462>/Gain'
     */
    -1.0F,

    /* Computed Parameter: opticalFlowErrorCorrect_Gain
     * Referenced by: '<S462>/opticalFlowErrorCorrect'
     */
    1.15F,

    /* Computed Parameter: C_Value_i
     * Referenced by: '<S21>/C'
     */
    { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: C_Value_k
     * Referenced by: '<S20>/C'
     */
    { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 1.0F },

    /* Expression: Controller.Q2Ts
     * Referenced by: '<S9>/TorqueTotalThrustToThrustPerMotor'
     */
    { 0.25F, 0.25F, 0.25F, 0.25F, 103.573624F, -103.573624F, 103.573624F,
      -103.573624F, -5.66592F, -5.66592F, 5.66592F, 5.66592F, -5.66592F,
      5.66592F, 5.66592F, -5.66592F },

    /* Expression: Controller.Ts2Q
     * Referenced by: '<S23>/TorqueTotalThrustToThrustPerMotor'
     */
    { 1.0F, 0.00241374201F, -0.0441234633F, -0.0441234633F, 1.0F,
      -0.00241374201F, -0.0441234633F, 0.0441234633F, 1.0F, 0.00241374201F,
      0.0441234633F, 0.0441234633F, 1.0F, -0.00241374201F, 0.0441234633F,
      -0.0441234633F },

    /* Computed Parameter: A_Value_j
     * Referenced by: '<S20>/A'
     */
    { 1.0F, 0.0F, 0.0F, 0.0F, 0.000122625F, 1.0F, 0.04905F, 0.0F, 0.005F, 0.0F,
      1.0F, 0.0F, 2.04375E-7F, 0.005F, 0.000122625F, 1.0F },

    /* Computed Parameter: A_Value_l
     * Referenced by: '<S21>/A'
     */
    { 1.0F, 0.0F, 0.0F, 0.0F, -0.000122625F, 1.0F, -0.04905F, 0.0F, 0.005F, 0.0F,
      1.0F, 0.0F, -2.04375E-7F, 0.005F, -0.000122625F, 1.0F },

    /* Computed Parameter: A_Value_c
     * Referenced by: '<S461>/A'
     */
    { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, -0.005F, 0.0F, 1.0F, 0.0F,
      0.0F, -0.005F, 0.0F, 1.0F },

    /* Computed Parameter: SimplyIntegrateVelocity_gainval
     * Referenced by: '<S457>/SimplyIntegrateVelocity'
     */
    0.005F,

    /* Computed Parameter: SimplyIntegrateVelocity_IC
     * Referenced by: '<S457>/SimplyIntegrateVelocity'
     */
    0.0F,

    /* Computed Parameter: invertzaxisGain_Gain
     * Referenced by: '<S271>/invertzaxisGain'
     */
    -1.0F,

    /* Computed Parameter: prsToAltGain_Gain
     * Referenced by: '<S271>/prsToAltGain'
     */
    0.0832137167F,

    /* Computed Parameter: pressureFilter_IIR_NumCoef
     * Referenced by: '<S276>/pressureFilter_IIR'
     */
    { 3.75683794E-6F, 1.12705138E-5F, 1.12705138E-5F, 3.75683794E-6F },

    /* Computed Parameter: pressureFilter_IIR_DenCoef
     * Referenced by: '<S276>/pressureFilter_IIR'
     */
    { 1.0F, -2.93717074F, 2.87629962F, -0.939098954F },

    /* Computed Parameter: pressureFilter_IIR_InitialStates
     * Referenced by: '<S276>/pressureFilter_IIR'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainval_a
     * Referenced by: '<S339>/Discrete-Time Integrator'
     */
    0.005F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC_b
     * Referenced by: '<S339>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: X0_Value_f
     * Referenced by: '<S341>/X0'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: Assumingthatthepreflightcalibrationwasdoneatlevelorientation_Bi
     * Referenced by: '<S273>/Assuming that the  preflight calibration was done at level orientation'
     */
    { 0.0F, 0.0F, 9.81F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: inverseIMU_gain_Gain
     * Referenced by: '<S273>/inverseIMU_gain'
     */
    { 0.994075298F, 0.996184587F, 1.00549F, 1.00139189F, 0.993601203F, 1.00003F
    },

    /* Computed Parameter: FIR_IMUaccel_InitialStates
     * Referenced by: '<S273>/FIR_IMUaccel'
     */
    0.0F,

    /* Computed Parameter: FIR_IMUaccel_Coefficients
     * Referenced by: '<S273>/FIR_IMUaccel'
     */
    { 0.0264077242F, 0.140531361F, 0.33306092F, 0.33306092F, 0.140531361F,
      0.0264077242F },

    /* Computed Parameter: Gain2_Gain
     * Referenced by: '<S337>/Gain2'
     */
    0.101936802F,

    /* Computed Parameter: Constant_Value_k
     * Referenced by: '<S340>/Constant'
     */
    2.0F,

    /* Computed Parameter: C_Value_j
     * Referenced by: '<S341>/C'
     */
    { 1.0F, 0.0F },

    /* Computed Parameter: X0_Value_fi
     * Referenced by: '<S395>/X0'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: C_Value_a
     * Referenced by: '<S395>/C'
     */
    { 1.0F, 0.0F },

    /* Computed Parameter: IIR_IMUgyro_r_NumCoef
     * Referenced by: '<S273>/IIR_IMUgyro_r'
     */
    { 0.282124132F, 1.27253926F, 2.42084408F, 2.42084408F, 1.27253926F,
      0.282124132F },

    /* Computed Parameter: IIR_IMUgyro_r_DenCoef
     * Referenced by: '<S273>/IIR_IMUgyro_r'
     */
    { 1.0F, 2.22871494F, 2.52446198F, 1.57725322F, 0.54102242F, 0.0795623958F },

    /* Computed Parameter: IIR_IMUgyro_r_InitialStates
     * Referenced by: '<S273>/IIR_IMUgyro_r'
     */
    0.0F,

    /* Computed Parameter: Constant_Value_f
     * Referenced by: '<S339>/Constant'
     */
    0.0F,

    /* Computed Parameter: X0_Value_e
     * Referenced by: '<S461>/X0'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: C_Value_p
     * Referenced by: '<S461>/C'
     */
    { 1.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: Gain1_Gain
     * Referenced by: '<S459>/Gain1'
     */
    -1.0F,

    /* Computed Parameter: Gain_Gain_i3
     * Referenced by: '<S456>/Gain'
     */
    0.0F,

    /* Computed Parameter: IIRgyroz_NumCoef
     * Referenced by: '<S460>/IIRgyroz'
     */
    { 0.282124132F, 1.27253926F, 2.42084408F, 2.42084408F, 1.27253926F,
      0.282124132F },

    /* Computed Parameter: IIRgyroz_DenCoef
     * Referenced by: '<S460>/IIRgyroz'
     */
    { 1.0F, 2.22871494F, 2.52446198F, 1.57725322F, 0.54102242F, 0.0795623958F },

    /* Computed Parameter: IIRgyroz_InitialStates
     * Referenced by: '<S460>/IIRgyroz'
     */
    0.0F,

    /* Computed Parameter: TSamp_WtEt
     * Referenced by: '<S468>/TSamp'
     */
    200.0F,

    /* Computed Parameter: Delay_InitialCondition
     * Referenced by: '<S456>/Delay'
     */
    0.0F,

    /* Computed Parameter: Delay1_InitialCondition
     * Referenced by: '<S7>/Delay1'
     */
    0.0F,

    /* Computed Parameter: B_Value_a
     * Referenced by: '<S461>/B'
     */
    { 0.005F, 0.0F, 0.0F, 0.0F, 0.0F, 0.005F, 0.0F, 0.0F },

    /* Computed Parameter: D_Value_k
     * Referenced by: '<S461>/D'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: X0_Value_p
     * Referenced by: '<S21>/X0'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: D_pr1_Gain
     * Referenced by: '<S8>/D_pr1'
     */
    { 0.003F, 0.003F },

    /* Computed Parameter: DiscreteTimeIntegrator_gainval_i
     * Referenced by: '<S8>/Discrete-Time Integrator'
     */
    0.005F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC_g
     * Referenced by: '<S8>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_UpperSat
     * Referenced by: '<S8>/Discrete-Time Integrator'
     */
    2.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_LowerSat
     * Referenced by: '<S8>/Discrete-Time Integrator'
     */
    -2.0F,

    /* Computed Parameter: I_pr_Gain
     * Referenced by: '<S8>/I_pr'
     */
    0.0F,

    /* Computed Parameter: P_pr2_Gain
     * Referenced by: '<S8>/P_pr2'
     */
    { 0.0075F, 0.0075F },

    /* Computed Parameter: DiscreteTimeIntegrator2_gainval
     * Referenced by: '<S15>/Discrete-Time Integrator2'
     */
    0.005F,

    /* Computed Parameter: DiscreteTimeIntegrator2_IC
     * Referenced by: '<S15>/Discrete-Time Integrator2'
     */
    0.0F,

    /* Computed Parameter: Bias_Bias_e
     * Referenced by: '<S3>/Bias'
     */
    0.0003F,

    /* Computed Parameter: X0_Value_pq
     * Referenced by: '<S20>/X0'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: DiscreteTimeIntegrator2_gainval_m
     * Referenced by: '<S14>/Discrete-Time Integrator2'
     */
    0.005F,

    /* Computed Parameter: DiscreteTimeIntegrator2_IC_l
     * Referenced by: '<S14>/Discrete-Time Integrator2'
     */
    0.0F,

    /* Computed Parameter: Bias1_Bias
     * Referenced by: '<S3>/Bias1'
     */
    0.0003F,

    /* Computed Parameter: w1_Value
     * Referenced by: '<S13>/w1'
     */
    -0.61803F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainval_b
     * Referenced by: '<S13>/Discrete-Time Integrator'
     */
    0.005F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC_j
     * Referenced by: '<S13>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_UpperSat_n
     * Referenced by: '<S13>/Discrete-Time Integrator'
     */
    2.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_LowerSat_d
     * Referenced by: '<S13>/Discrete-Time Integrator'
     */
    -2.0F,

    /* Computed Parameter: X0_Value_l
     * Referenced by: '<S19>/X0'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: C_Value_kb
     * Referenced by: '<S19>/C'
     */
    { 1.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: DiscreteTimeIntegrator2_gainval_g
     * Referenced by: '<S17>/Discrete-Time Integrator2'
     */
    0.005F,

    /* Computed Parameter: DiscreteTimeIntegrator2_IC_i
     * Referenced by: '<S17>/Discrete-Time Integrator2'
     */
    0.0F,

    /* Computed Parameter: X0_Value_d
     * Referenced by: '<S22>/X0'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: C_Value_ie
     * Referenced by: '<S22>/C'
     */
    { 1.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: DiscreteTimeIntegrator2_gainval_mk
     * Referenced by: '<S18>/Discrete-Time Integrator2'
     */
    0.005F,

    /* Computed Parameter: DiscreteTimeIntegrator2_IC_lx
     * Referenced by: '<S18>/Discrete-Time Integrator2'
     */
    0.0F,

    /* Computed Parameter: ThrustToMotorCommand_Gain
     * Referenced by: '<S16>/ThrustToMotorCommand'
     */
    -1530.72681F,

    /* Expression: Vehicle.Motor.maxLimit
     * Referenced by: '<S16>/Saturation5'
     */
    500.0F,

    /* Expression: Vehicle.Motor.minLimit
     * Referenced by: '<S16>/Saturation5'
     */
    10.0F,

    /* Computed Parameter: ThrustToMotorCommand_Gain_b
     * Referenced by: '<S23>/ThrustToMotorCommand'
     */
    -0.000653284427F,

    /* Computed Parameter: Bias_Bias_o
     * Referenced by: '<S10>/Bias'
     */
    -0.0003F,

    /* Computed Parameter: B_Value_i
     * Referenced by: '<S21>/B'
     */
    { -3.56347027E-6F, 0.174359411F, -0.00285077631F, 69.7437592F },

    /* Computed Parameter: D_Value_h
     * Referenced by: '<S21>/D'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: MotorDirections_Gain
     * Referenced by: '<S16>/MotorDirections'
     */
    { 1.0F, -1.0F, 1.0F, -1.0F },

    /* Computed Parameter: Bias1_Bias_j
     * Referenced by: '<S10>/Bias1'
     */
    -0.0003F,

    /* Computed Parameter: D_Value_m
     * Referenced by: '<S20>/D'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: B_Value_n
     * Referenced by: '<S20>/B'
     */
    { 4.38302095E-6F, 0.214459732F, 0.00350641669F, 85.7838898F },

    /* Computed Parameter: A_Value_i
     * Referenced by: '<S19>/A'
     */
    { 1.0F, 0.0F, 0.005F, 1.0F },

    /* Computed Parameter: A_Value_cc
     * Referenced by: '<S22>/A'
     */
    { 1.0F, 0.0F, 0.005F, 1.0F },

    /* Computed Parameter: A_Value_h
     * Referenced by: '<S341>/A'
     */
    { 1.0F, 0.0F, -0.005F, 1.0F },

    /* Computed Parameter: A_Value_d
     * Referenced by: '<S395>/A'
     */
    { 1.0F, 0.0F, -0.005F, 1.0F },

    /* Computed Parameter: B_Value_nz
     * Referenced by: '<S395>/B'
     */
    { 0.005F, 0.0F },

    /* Computed Parameter: D_Value_n
     * Referenced by: '<S395>/D'
     */
    0.0F,

    /* Computed Parameter: B_Value_j
     * Referenced by: '<S341>/B'
     */
    { 0.005F, 0.0F },

    /* Computed Parameter: D_Value_b
     * Referenced by: '<S341>/D'
     */
    0.0F,

    /* Computed Parameter: D_Value_he
     * Referenced by: '<S22>/D'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: B_Value_g
     * Referenced by: '<S22>/B'
     */
    { 0.416666657F, 166.666672F },

    /* Computed Parameter: Bias2_Bias
     * Referenced by: '<S10>/Bias2'
     */
    0.61803F,

    /* Computed Parameter: D_Value_m4
     * Referenced by: '<S19>/D'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: B_Value_c
     * Referenced by: '<S19>/B'
     */
    { 0.000198412701F, 0.0793650821F },

    /* Computed Parameter: Delay_InitialCondition_n
     * Referenced by: '<S8>/Delay'
     */
    0.0F,

    /* Computed Parameter: antiWU_Gain_Gain
     * Referenced by: '<S8>/antiWU_Gain'
     */
    0.001F,

    /* Computed Parameter: antiWU_Gain1_Gain
     * Referenced by: '<S8>/antiWU_Gain1'
     */
    0.0F,

    /* Computed Parameter: P_pr1_Gain
     * Referenced by: '<S8>/P_pr1'
     */
    { 0.013F, 0.01F },

    /* Computed Parameter: D_pr_Gain
     * Referenced by: '<S8>/D_pr'
     */
    { 0.002F, 0.003F },

    /* Computed Parameter: I_pr_Gain_b
     * Referenced by: '<S13>/I_pr'
     */
    0.24F,

    /* Computed Parameter: Gain_Gain_f
     * Referenced by: '<S4>/Gain'
     */
    1.0F,

    /* Computed Parameter: Gain1_Gain_j
     * Referenced by: '<S4>/Gain1'
     */
    1.0F,

    /* Computed Parameter: P0_Value_j
     * Referenced by: '<S20>/P0'
     */
    { 1.31289542F, 4.26611173E-8F, 1.10141718E-5F, 3.72962295E-13F,
      4.26611173E-8F, 0.330347806F, 1.70599378E-5F, 9.12039244E-9F,
      1.10141718E-5F, 1.70599378E-5F, 0.22219789F, 2.23681657E-10F,
      3.72962295E-13F, 9.12039244E-9F, 2.23681657E-10F, 0.00110182411F },

    /* Computed Parameter: G_Value_h
     * Referenced by: '<S20>/G'
     */
    { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: H_Value_d
     * Referenced by: '<S20>/H'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: N_Value_j
     * Referenced by: '<S20>/N'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: Q_Value_p
     * Referenced by: '<S20>/Q'
     */
    { 0.99F, 0.0F, 0.0F, 0.0F, 0.0F, 0.33F, 0.0F, 0.0F, 0.0F, 0.0F, 0.22F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0011F },

    /* Computed Parameter: R_Value_i
     * Referenced by: '<S20>/R'
     */
    { 0.42821F, 0.0F, 0.0F, 0.0F, 0.0F, 0.00034817F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.002219F, 0.0F, 0.0F, 0.0F, 0.0F, 1.8271E-6F },

    /* Computed Parameter: P0_Value_n
     * Referenced by: '<S21>/P0'
     */
    { 1.47984159F, -3.19313038E-8F, 1.10229385E-5F, -3.73020923E-13F,
      -3.19313038E-8F, 0.220260292F, -1.27674748E-5F, 9.12039422E-9F,
      1.10229385E-5F, -1.27674748E-5F, 0.222197682F, -2.23681754E-10F,
      -3.73020923E-13F, 9.12039422E-9F, -2.23681754E-10F, 0.00110182411F },

    /* Computed Parameter: G_Value_hr
     * Referenced by: '<S21>/G'
     */
    { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: H_Value_f
     * Referenced by: '<S21>/H'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: N_Value_e
     * Referenced by: '<S21>/N'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: Q_Value_d
     * Referenced by: '<S21>/Q'
     */
    { 0.99F, 0.0F, 0.0F, 0.0F, 0.0F, 0.22F, 0.0F, 0.0F, 0.0F, 0.0F, 0.22F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.0011F },

    /* Computed Parameter: R_Value_f
     * Referenced by: '<S21>/R'
     */
    { 0.73221F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0002606F, 0.0F, 0.0F, 0.0F, 0.0F,
      0.002219F, 0.0F, 0.0F, 0.0F, 0.0F, 1.8271E-6F },

    /* Computed Parameter: P0_Value_l
     * Referenced by: '<S461>/P0'
     */
    { 1.42263806F, 0.0F, -0.462845951F, 0.0F, 0.0F, 1.42263806F, 0.0F,
      -0.462845951F, -0.462845951F, 0.0F, 6.15735F, 0.0F, 0.0F, -0.462845951F,
      0.0F, 6.15735F },

    /* Computed Parameter: G_Value_n
     * Referenced by: '<S461>/G'
     */
    { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F,
      0.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: Q_Value_b
     * Referenced by: '<S461>/Q'
     */
    { 0.09F, 0.0F, 0.0F, 0.0F, 0.0F, 0.09F, 0.0F, 0.0F, 0.0F, 0.0F, 0.01F, 0.0F,
      0.0F, 0.0F, 0.0F, 0.01F },

    /* Computed Parameter: H_Value_fc
     * Referenced by: '<S461>/H'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: N_Value_eu
     * Referenced by: '<S461>/N'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: P0_Value_o
     * Referenced by: '<S19>/P0'
     */
    { 0.111772448F, 8.99089287E-7F, 8.99089287E-7F, 0.0111797722F },

    /* Computed Parameter: G_Value_k
     * Referenced by: '<S19>/G'
     */
    { 1.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: H_Value_m
     * Referenced by: '<S19>/H'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: N_Value_p
     * Referenced by: '<S19>/N'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: Q_Value_n
     * Referenced by: '<S19>/Q'
     */
    { 0.11F, 0.0F, 0.0F, 0.011F },

    /* Computed Parameter: R_Value_d
     * Referenced by: '<S19>/R'
     */
    { 0.001801F, 0.0F, 0.0F, 0.00018271F },

    /* Computed Parameter: P0_Value_p
     * Referenced by: '<S22>/P0'
     */
    { 0.140084833F, 3.52107357E-8F, 3.52107357E-8F, 0.00110703253F },

    /* Computed Parameter: G_Value_p
     * Referenced by: '<S22>/G'
     */
    { 1.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: H_Value_i
     * Referenced by: '<S22>/H'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: N_Value_jc
     * Referenced by: '<S22>/N'
     */
    { 0.0F, 0.0F, 0.0F, 0.0F },

    /* Computed Parameter: Q_Value_a
     * Referenced by: '<S22>/Q'
     */
    { 0.11F, 0.0F, 0.0F, 0.0011F },

    /* Computed Parameter: R_Value_o
     * Referenced by: '<S22>/R'
     */
    { 0.038313F, 0.0F, 0.0F, 7.0775E-6F },

    /* Computed Parameter: P0_Value_jv
     * Referenced by: '<S341>/P0'
     */
    { 1098.6875F, -30.4245777F, -30.4245777F, 7.22336864F },

    /* Computed Parameter: G_Value_i
     * Referenced by: '<S341>/G'
     */
    { 1.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: Q_Value_f
     * Referenced by: '<S341>/Q'
     */
    { 1.0F, 0.0F, 0.0F, 0.001F },

    /* Computed Parameter: P0_Value_d
     * Referenced by: '<S395>/P0'
     */
    { 1098.6875F, -30.4245777F, -30.4245777F, 7.22336864F },

    /* Computed Parameter: G_Value_n5
     * Referenced by: '<S395>/G'
     */
    { 1.0F, 0.0F, 0.0F, 1.0F },

    /* Computed Parameter: Q_Value_c
     * Referenced by: '<S395>/Q'
     */
    { 1.0F, 0.0F, 0.0F, 0.001F },

    /* Computed Parameter: R_Value_fa
     * Referenced by: '<S461>/R'
     */
    { 20.0F, 0.0F, 0.0F, 20.0F },

    /* Computed Parameter: H_Value_fr
     * Referenced by: '<S341>/H'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: N_Value_d
     * Referenced by: '<S341>/N'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: H_Value_j
     * Referenced by: '<S395>/H'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: N_Value_l
     * Referenced by: '<S395>/N'
     */
    { 0.0F, 0.0F },

    /* Computed Parameter: R_Value_ft
     * Referenced by: '<S341>/R'
     */
    924556.188F,

    /* Computed Parameter: R_Value_l
     * Referenced by: '<S395>/R'
     */
    924556.188F,

    /* Computed Parameter: Output_InitialCondition
     * Referenced by: '<S452>/Output'
     */
    0U,

    /* Computed Parameter: Output_InitialCondition_h
     * Referenced by: '<S534>/Output'
     */
    0U,

    /* Computed Parameter: Output_InitialCondition_m
     * Referenced by: '<S251>/Output'
     */
    0U,

    /* Computed Parameter: FixPtConstant_Value
     * Referenced by: '<S258>/FixPt Constant'
     */
    1U,

    /* Computed Parameter: Constant_Value_d
     * Referenced by: '<S259>/Constant'
     */
    0U,

    /* Computed Parameter: FixPtConstant_Value_m
     * Referenced by: '<S535>/FixPt Constant'
     */
    1U,

    /* Computed Parameter: Constant_Value_i
     * Referenced by: '<S536>/Constant'
     */
    0U,

    /* Computed Parameter: FixPtConstant_Value_f
     * Referenced by: '<S454>/FixPt Constant'
     */
    1U,

    /* Computed Parameter: Constant_Value_n
     * Referenced by: '<S455>/Constant'
     */
    0U,

    /* Computed Parameter: Output_InitialCondition_i
     * Referenced by: '<S241>/Output'
     */
    0U,

    /* Computed Parameter: FixPtConstant_Value_p
     * Referenced by: '<S242>/FixPt Constant'
     */
    1U,

    /* Computed Parameter: Constant_Value_mc
     * Referenced by: '<S243>/Constant'
     */
    0U,

    /* Computed Parameter: controlModePosVsOrient_Value
     * Referenced by: '<S1>/controlModePosVsOrient'
     */
    true,

    /* Computed Parameter: Constant_Value_o
     * Referenced by: '<S5>/Constant'
     */
    false,

    /* Expression: true()
     * Referenced by: '<S21>/Enable'
     */
    true,

    /* Expression: true()
     * Referenced by: '<S20>/Enable'
     */
    true,

    /* Expression: true()
     * Referenced by: '<S19>/Enable'
     */
    true,

    /* Expression: true()
     * Referenced by: '<S22>/Enable'
     */
    true,

    /* Expression: pInitialization.isSqrtUsed
     * Referenced by: '<S127>/isSqrtUsed'
     */
    false,

    /* Expression: pInitialization.isSqrtUsed
     * Referenced by: '<S181>/isSqrtUsed'
     */
    false,

    /* Expression: pInitialization.isSqrtUsed
     * Referenced by: '<S528>/isSqrtUsed'
     */
    false,

    /* Expression: pInitialization.isSqrtUsed
     * Referenced by: '<S73>/isSqrtUsed'
     */
    false,

    /* Expression: pInitialization.isSqrtUsed
     * Referenced by: '<S235>/isSqrtUsed'
     */
    false,

    /* Expression: pInitialization.isSqrtUsed
     * Referenced by: '<S325>/isSqrtUsed'
     */
    false,

    /* Expression: pInitialization.isSqrtUsed
     * Referenced by: '<S390>/isSqrtUsed'
     */
    false,

    /* Expression: pInitialization.isSqrtUsed
     * Referenced by: '<S444>/isSqrtUsed'
     */
    false,

    /* Computed Parameter: Landed_Value
     * Referenced by: '<S254>/Landed'
     */
    255U,

    /* Computed Parameter: No_error_Value
     * Referenced by: '<S254>/No_error'
     */
    0U,

    /* Computed Parameter: Disabletemperaturecompensation_CurrentSetting
     * Referenced by: '<S449>/Disable temperature compensation'
     */
    0U,

    /* Computed Parameter: ManualSwitch2_CurrentSetting
     * Referenced by: '<S3>/Manual Switch2'
     */
    0U,

    /* Computed Parameter: ManualSwitch3_CurrentSetting
     * Referenced by: '<S3>/Manual Switch3'
     */
    0U,

    /* Computed Parameter: ManualSwitch_CurrentSetting
     * Referenced by: '<S3>/Manual Switch'
     */
    0U,

    /* Computed Parameter: ManualSwitch1_CurrentSetting
     * Referenced by: '<S3>/Manual Switch1'
     */
    0U,

    /* Computed Parameter: Merge_InitialOutput
     * Referenced by: '<S4>/Merge'
     */
    0U,

    /* Computed Parameter: Constant_Value_g
     * Referenced by: '<S1>/Constant'
     */
    0U,

    /* Start of '<S422>/Enabled Subsystem' */
    {
      /* Computed Parameter: deltax_Y0
       * Referenced by: '<S448>/deltax'
       */
      0.0F
    }
    ,

    /* End of '<S422>/Enabled Subsystem' */

    /* Start of '<S415>/MeasurementUpdate' */
    {
      /* Computed Parameter: Lykyhatkk1_Y0
       * Referenced by: '<S446>/L*(y[k]-yhat[k|k-1])'
       */
      0.0F
    }
    ,

    /* End of '<S415>/MeasurementUpdate' */

    /* Start of '<S368>/Enabled Subsystem' */
    {
      /* Computed Parameter: deltax_Y0
       * Referenced by: '<S394>/deltax'
       */
      0.0F
    }
    ,

    /* End of '<S368>/Enabled Subsystem' */

    /* Start of '<S361>/MeasurementUpdate' */
    {
      /* Computed Parameter: Lykyhatkk1_Y0
       * Referenced by: '<S392>/L*(y[k]-yhat[k|k-1])'
       */
      0.0F
    }
    ,

    /* End of '<S361>/MeasurementUpdate' */

    /* Start of '<S4>/Ultrasound improper' */
    {
      /* Computed Parameter: Constant_Value
       * Referenced by: '<S256>/Constant'
       */
      88U
    }
    ,

    /* End of '<S4>/Ultrasound improper' */

    /* Start of '<S4>/No optical flow ' */
    {
      /* Computed Parameter: Constant_Value
       * Referenced by: '<S253>/Constant'
       */
      69U
    }
    ,

    /* End of '<S4>/No optical flow ' */

    /* Start of '<S4>/estimator//Optical flow error' */
    {
      /* Computed Parameter: Constant_Value
       * Referenced by: '<S257>/Constant'
       */
      99U
    }
    ,

    /* End of '<S4>/estimator//Optical flow error' */

    /* Start of '<S4>/Geofencing error' */
    {
      /* Computed Parameter: Constant_Value
       * Referenced by: '<S252>/Constant'
       */
      1U
    }
    ,

    /* End of '<S4>/Geofencing error' */

    /* Start of '<S213>/Enabled Subsystem' */
    {
      /* Computed Parameter: deltax_Y0
       * Referenced by: '<S239>/deltax'
       */
      0.0F
    }
    ,

    /* End of '<S213>/Enabled Subsystem' */

    /* Start of '<S206>/MeasurementUpdate' */
    {
      /* Computed Parameter: Lykyhatkk1_Y0
       * Referenced by: '<S237>/L*(y[k]-yhat[k|k-1])'
       */
      0.0F
    }
    ,

    /* End of '<S206>/MeasurementUpdate' */

    /* Start of '<S159>/Enabled Subsystem' */
    {
      /* Computed Parameter: deltax_Y0
       * Referenced by: '<S185>/deltax'
       */
      0.0F
    }
    ,

    /* End of '<S159>/Enabled Subsystem' */

    /* Start of '<S152>/MeasurementUpdate' */
    {
      /* Computed Parameter: Lykyhatkk1_Y0
       * Referenced by: '<S183>/L*(y[k]-yhat[k|k-1])'
       */
      0.0F
    }
    ,

    /* End of '<S152>/MeasurementUpdate' */

    /* Start of '<S105>/Enabled Subsystem' */
    {
      /* Computed Parameter: deltax_Y0
       * Referenced by: '<S131>/deltax'
       */
      0.0F
    }
    ,

    /* End of '<S105>/Enabled Subsystem' */

    /* Start of '<S98>/MeasurementUpdate' */
    {
      /* Computed Parameter: Lykyhatkk1_Y0
       * Referenced by: '<S129>/L*(y[k]-yhat[k|k-1])'
       */
      0.0F
    }
    ,

    /* End of '<S98>/MeasurementUpdate' */

    /* Start of '<S51>/Enabled Subsystem' */
    {
      /* Computed Parameter: deltax_Y0
       * Referenced by: '<S77>/deltax'
       */
      0.0F
    }
    ,

    /* End of '<S51>/Enabled Subsystem' */

    /* Start of '<S44>/MeasurementUpdate' */
    {
      /* Computed Parameter: Lykyhatkk1_Y0
       * Referenced by: '<S75>/L*(y[k]-yhat[k|k-1])'
       */
      0.0F
    }
    /* End of '<S44>/MeasurementUpdate' */
  }
  /* End of '<Root>/Flight Control System' */
};
