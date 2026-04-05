# Autonomous Drone Control — Optimal Control Project

Laboratory project developed for the Optimal Control (Controlo Ótimo) 
course at Instituto Superior Técnico (IST), Master's in Mechanical 
Engineering — Specialization in Systems, Robotics and AI.

## Contributors
- Pedro Vasques — [@Vasquez-505](https://github.com/Vasquez-505)
- Joao Martinho
- Melchior Poirier-Coutansais
- Orestis Kourounakis

## Project Overview

Design and implementation of a full autonomous controller for the 
**Parrot Mambo Fly** quadcopter, combining nonlinear dynamic modelling, 
optimal estimation, and LQR control — validated in simulation and 
deployed on the physical drone.

## Phase I — Dynamic Modelling & Classical Control (March 2025)

- Nonlinear quadcopter dynamic model implemented in Simulink 
  based on rigid body equations of motion
- Linearised state-space model around hovering equilibrium — 
  four decoupled subsystems (vertical, longitudinal, lateral, yaw)
- Stability, controllability and observability analysis
- Full-state feedback regulator via pole placement — validated 
  for multiple damping coefficients (ζ = 0.3, 0.7, 1.0) and 
  natural frequencies
- Motor saturation modelling — conversion between generalised 
  forces and motor command signals with input constraints

## Phase II — Optimal Estimation & LQR Control (May 2025)

- Kalman-Bucy continuous-time state observer — formulated with 
  realistic measurement and process noise covariance matrices 
  based on sensor specifications
- LQR servo controller designed for Cartesian position and yaw 
  tracking — Q and R matrices tuned for desired response
- Full closed-loop validation on nonlinear Simulink model with 
  sensor noise and motor saturation
- Yaw angle compensation — adjusted observer and tracking error 
  to handle large yaw rotations via in-plane rotation matrix

## Phase III — Discrete-Time Implementation & Hardware Deployment (June 2025)

- Discrete-time LQR servo controller — Zero-Order Hold 
  discretisation at 5ms sampling period
- Discrete-time Kalman Filter — implemented using Simulink 
  kalman filter block, validated against continuous-time observer
- Full validation of discrete controller and observer on 
  nonlinear simulation model
- **Physical deployment on Parrot Mambo Fly drone** — achieved:
  - Stable hovering
  - Vertical movement and stabilisation
  - Longitudinal and lateral movement
  - Multi-waypoint trajectory tracking

## Key Results

- Stable autonomous flight achieved on physical hardware
- LQR controller successfully tracked complex trajectories 
  under realistic noise conditions
- Discrete-time implementation validated at 5ms sampling — 
  consistent with continuous-time performance

## Tech Stack
MATLAB · Simulink · LQR · Kalman Filter · Parrot Mambo Fly SDK
