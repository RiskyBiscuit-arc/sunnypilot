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
void car_err_fun(double *nom_x, double *delta_x, double *out_6612536747917768367);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6433317979744346352);
void car_H_mod_fun(double *state, double *out_7740403684461857356);
void car_f_fun(double *state, double dt, double *out_910252998081659384);
void car_F_fun(double *state, double dt, double *out_7788395741319871081);
void car_h_25(double *state, double *unused, double *out_648000575332102416);
void car_H_25(double *state, double *unused, double *out_5802648564063029420);
void car_h_24(double *state, double *unused, double *out_6771383046451654828);
void car_H_24(double *state, double *unused, double *out_6443062829795360770);
void car_h_30(double *state, double *unused, double *out_2145191154539041252);
void car_H_30(double *state, double *unused, double *out_5931987511206269490);
void car_h_26(double *state, double *unused, double *out_8128114993845183005);
void car_H_26(double *state, double *unused, double *out_8902592190772465972);
void car_h_27(double *state, double *unused, double *out_7001344597979231926);
void car_H_27(double *state, double *unused, double *out_8106750823006694401);
void car_h_29(double *state, double *unused, double *out_891594896905291433);
void car_H_29(double *state, double *unused, double *out_8626630523833306182);
void car_h_28(double *state, double *unused, double *out_1180078273490515425);
void car_H_28(double *state, double *unused, double *out_7856483278310919183);
void car_h_31(double *state, double *unused, double *out_4285450103586124766);
void car_H_31(double *state, double *unused, double *out_5772002602186068992);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}