#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3898755390867715059);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_277612785680832411);
void pose_H_mod_fun(double *state, double *out_4995735585886133509);
void pose_f_fun(double *state, double dt, double *out_2762548597287583938);
void pose_F_fun(double *state, double dt, double *out_8703467420914203037);
void pose_h_4(double *state, double *unused, double *out_5980686185248558188);
void pose_H_4(double *state, double *unused, double *out_1795325684784663485);
void pose_h_10(double *state, double *unused, double *out_1442181013276762710);
void pose_H_10(double *state, double *unused, double *out_7595311124708499208);
void pose_h_13(double *state, double *unused, double *out_417783278623543215);
void pose_H_13(double *state, double *unused, double *out_2359927604466507589);
void pose_h_14(double *state, double *unused, double *out_7977669001299524575);
void pose_H_14(double *state, double *unused, double *out_1287462747510708811);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}