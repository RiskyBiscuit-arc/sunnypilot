#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_3617824066507182600);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7609445843503775366);
void car_H_mod_fun(double *state, double *out_123298891024053193);
void car_f_fun(double *state, double dt, double *out_3098113541010151714);
void car_F_fun(double *state, double dt, double *out_8403537800293641243);
void car_h_25(double *state, double *unused, double *out_1858934783564706594);
void car_H_25(double *state, double *unused, double *out_8612668563252626436);
void car_h_24(double *state, double *unused, double *out_4289260273971546687);
void car_H_24(double *state, double *unused, double *out_4630345411854858538);
void car_h_30(double *state, double *unused, double *out_5496384311818728944);
void car_H_30(double *state, double *unused, double *out_7315742551949676553);
void car_h_26(double *state, double *unused, double *out_8533170363263061629);
void car_H_26(double *state, double *unused, double *out_4871165244378570212);
void car_h_27(double *state, double *unused, double *out_1557338506084363422);
void car_H_27(double *state, double *unused, double *out_8956238209959450152);
void car_h_29(double *state, double *unused, double *out_8328173732434714358);
void car_H_29(double *state, double *unused, double *out_6805511207635284369);
void car_h_28(double *state, double *unused, double *out_2725082307160505159);
void car_H_28(double *state, double *unused, double *out_6558833849004736673);
void car_h_31(double *state, double *unused, double *out_6022337867189342591);
void car_H_31(double *state, double *unused, double *out_4244957142145218736);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}