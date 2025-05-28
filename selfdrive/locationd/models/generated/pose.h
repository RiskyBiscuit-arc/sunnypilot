#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6788482671477646176);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2293652614005689133);
void pose_H_mod_fun(double *state, double *out_6859876955096240212);
void pose_f_fun(double *state, double dt, double *out_7198856022790088301);
void pose_F_fun(double *state, double dt, double *out_782635061309417912);
void pose_h_4(double *state, double *unused, double *out_1764421233415442805);
void pose_H_4(double *state, double *unused, double *out_2721139104072157718);
void pose_h_10(double *state, double *unused, double *out_4355221798934046123);
void pose_H_10(double *state, double *unused, double *out_5312916087312009959);
void pose_h_13(double *state, double *unused, double *out_5531667930420635084);
void pose_H_13(double *state, double *unused, double *out_5933412929404490519);
void pose_h_14(double *state, double *unused, double *out_8913575968829588963);
void pose_H_14(double *state, double *unused, double *out_6684379960411642247);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}