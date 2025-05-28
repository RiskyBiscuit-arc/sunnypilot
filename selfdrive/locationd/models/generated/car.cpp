#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3617824066507182600) {
   out_3617824066507182600[0] = delta_x[0] + nom_x[0];
   out_3617824066507182600[1] = delta_x[1] + nom_x[1];
   out_3617824066507182600[2] = delta_x[2] + nom_x[2];
   out_3617824066507182600[3] = delta_x[3] + nom_x[3];
   out_3617824066507182600[4] = delta_x[4] + nom_x[4];
   out_3617824066507182600[5] = delta_x[5] + nom_x[5];
   out_3617824066507182600[6] = delta_x[6] + nom_x[6];
   out_3617824066507182600[7] = delta_x[7] + nom_x[7];
   out_3617824066507182600[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7609445843503775366) {
   out_7609445843503775366[0] = -nom_x[0] + true_x[0];
   out_7609445843503775366[1] = -nom_x[1] + true_x[1];
   out_7609445843503775366[2] = -nom_x[2] + true_x[2];
   out_7609445843503775366[3] = -nom_x[3] + true_x[3];
   out_7609445843503775366[4] = -nom_x[4] + true_x[4];
   out_7609445843503775366[5] = -nom_x[5] + true_x[5];
   out_7609445843503775366[6] = -nom_x[6] + true_x[6];
   out_7609445843503775366[7] = -nom_x[7] + true_x[7];
   out_7609445843503775366[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_123298891024053193) {
   out_123298891024053193[0] = 1.0;
   out_123298891024053193[1] = 0.0;
   out_123298891024053193[2] = 0.0;
   out_123298891024053193[3] = 0.0;
   out_123298891024053193[4] = 0.0;
   out_123298891024053193[5] = 0.0;
   out_123298891024053193[6] = 0.0;
   out_123298891024053193[7] = 0.0;
   out_123298891024053193[8] = 0.0;
   out_123298891024053193[9] = 0.0;
   out_123298891024053193[10] = 1.0;
   out_123298891024053193[11] = 0.0;
   out_123298891024053193[12] = 0.0;
   out_123298891024053193[13] = 0.0;
   out_123298891024053193[14] = 0.0;
   out_123298891024053193[15] = 0.0;
   out_123298891024053193[16] = 0.0;
   out_123298891024053193[17] = 0.0;
   out_123298891024053193[18] = 0.0;
   out_123298891024053193[19] = 0.0;
   out_123298891024053193[20] = 1.0;
   out_123298891024053193[21] = 0.0;
   out_123298891024053193[22] = 0.0;
   out_123298891024053193[23] = 0.0;
   out_123298891024053193[24] = 0.0;
   out_123298891024053193[25] = 0.0;
   out_123298891024053193[26] = 0.0;
   out_123298891024053193[27] = 0.0;
   out_123298891024053193[28] = 0.0;
   out_123298891024053193[29] = 0.0;
   out_123298891024053193[30] = 1.0;
   out_123298891024053193[31] = 0.0;
   out_123298891024053193[32] = 0.0;
   out_123298891024053193[33] = 0.0;
   out_123298891024053193[34] = 0.0;
   out_123298891024053193[35] = 0.0;
   out_123298891024053193[36] = 0.0;
   out_123298891024053193[37] = 0.0;
   out_123298891024053193[38] = 0.0;
   out_123298891024053193[39] = 0.0;
   out_123298891024053193[40] = 1.0;
   out_123298891024053193[41] = 0.0;
   out_123298891024053193[42] = 0.0;
   out_123298891024053193[43] = 0.0;
   out_123298891024053193[44] = 0.0;
   out_123298891024053193[45] = 0.0;
   out_123298891024053193[46] = 0.0;
   out_123298891024053193[47] = 0.0;
   out_123298891024053193[48] = 0.0;
   out_123298891024053193[49] = 0.0;
   out_123298891024053193[50] = 1.0;
   out_123298891024053193[51] = 0.0;
   out_123298891024053193[52] = 0.0;
   out_123298891024053193[53] = 0.0;
   out_123298891024053193[54] = 0.0;
   out_123298891024053193[55] = 0.0;
   out_123298891024053193[56] = 0.0;
   out_123298891024053193[57] = 0.0;
   out_123298891024053193[58] = 0.0;
   out_123298891024053193[59] = 0.0;
   out_123298891024053193[60] = 1.0;
   out_123298891024053193[61] = 0.0;
   out_123298891024053193[62] = 0.0;
   out_123298891024053193[63] = 0.0;
   out_123298891024053193[64] = 0.0;
   out_123298891024053193[65] = 0.0;
   out_123298891024053193[66] = 0.0;
   out_123298891024053193[67] = 0.0;
   out_123298891024053193[68] = 0.0;
   out_123298891024053193[69] = 0.0;
   out_123298891024053193[70] = 1.0;
   out_123298891024053193[71] = 0.0;
   out_123298891024053193[72] = 0.0;
   out_123298891024053193[73] = 0.0;
   out_123298891024053193[74] = 0.0;
   out_123298891024053193[75] = 0.0;
   out_123298891024053193[76] = 0.0;
   out_123298891024053193[77] = 0.0;
   out_123298891024053193[78] = 0.0;
   out_123298891024053193[79] = 0.0;
   out_123298891024053193[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3098113541010151714) {
   out_3098113541010151714[0] = state[0];
   out_3098113541010151714[1] = state[1];
   out_3098113541010151714[2] = state[2];
   out_3098113541010151714[3] = state[3];
   out_3098113541010151714[4] = state[4];
   out_3098113541010151714[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3098113541010151714[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3098113541010151714[7] = state[7];
   out_3098113541010151714[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8403537800293641243) {
   out_8403537800293641243[0] = 1;
   out_8403537800293641243[1] = 0;
   out_8403537800293641243[2] = 0;
   out_8403537800293641243[3] = 0;
   out_8403537800293641243[4] = 0;
   out_8403537800293641243[5] = 0;
   out_8403537800293641243[6] = 0;
   out_8403537800293641243[7] = 0;
   out_8403537800293641243[8] = 0;
   out_8403537800293641243[9] = 0;
   out_8403537800293641243[10] = 1;
   out_8403537800293641243[11] = 0;
   out_8403537800293641243[12] = 0;
   out_8403537800293641243[13] = 0;
   out_8403537800293641243[14] = 0;
   out_8403537800293641243[15] = 0;
   out_8403537800293641243[16] = 0;
   out_8403537800293641243[17] = 0;
   out_8403537800293641243[18] = 0;
   out_8403537800293641243[19] = 0;
   out_8403537800293641243[20] = 1;
   out_8403537800293641243[21] = 0;
   out_8403537800293641243[22] = 0;
   out_8403537800293641243[23] = 0;
   out_8403537800293641243[24] = 0;
   out_8403537800293641243[25] = 0;
   out_8403537800293641243[26] = 0;
   out_8403537800293641243[27] = 0;
   out_8403537800293641243[28] = 0;
   out_8403537800293641243[29] = 0;
   out_8403537800293641243[30] = 1;
   out_8403537800293641243[31] = 0;
   out_8403537800293641243[32] = 0;
   out_8403537800293641243[33] = 0;
   out_8403537800293641243[34] = 0;
   out_8403537800293641243[35] = 0;
   out_8403537800293641243[36] = 0;
   out_8403537800293641243[37] = 0;
   out_8403537800293641243[38] = 0;
   out_8403537800293641243[39] = 0;
   out_8403537800293641243[40] = 1;
   out_8403537800293641243[41] = 0;
   out_8403537800293641243[42] = 0;
   out_8403537800293641243[43] = 0;
   out_8403537800293641243[44] = 0;
   out_8403537800293641243[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8403537800293641243[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8403537800293641243[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8403537800293641243[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8403537800293641243[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8403537800293641243[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8403537800293641243[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8403537800293641243[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8403537800293641243[53] = -9.8000000000000007*dt;
   out_8403537800293641243[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8403537800293641243[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8403537800293641243[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8403537800293641243[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8403537800293641243[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8403537800293641243[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8403537800293641243[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8403537800293641243[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8403537800293641243[62] = 0;
   out_8403537800293641243[63] = 0;
   out_8403537800293641243[64] = 0;
   out_8403537800293641243[65] = 0;
   out_8403537800293641243[66] = 0;
   out_8403537800293641243[67] = 0;
   out_8403537800293641243[68] = 0;
   out_8403537800293641243[69] = 0;
   out_8403537800293641243[70] = 1;
   out_8403537800293641243[71] = 0;
   out_8403537800293641243[72] = 0;
   out_8403537800293641243[73] = 0;
   out_8403537800293641243[74] = 0;
   out_8403537800293641243[75] = 0;
   out_8403537800293641243[76] = 0;
   out_8403537800293641243[77] = 0;
   out_8403537800293641243[78] = 0;
   out_8403537800293641243[79] = 0;
   out_8403537800293641243[80] = 1;
}
void h_25(double *state, double *unused, double *out_1858934783564706594) {
   out_1858934783564706594[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8612668563252626436) {
   out_8612668563252626436[0] = 0;
   out_8612668563252626436[1] = 0;
   out_8612668563252626436[2] = 0;
   out_8612668563252626436[3] = 0;
   out_8612668563252626436[4] = 0;
   out_8612668563252626436[5] = 0;
   out_8612668563252626436[6] = 1;
   out_8612668563252626436[7] = 0;
   out_8612668563252626436[8] = 0;
}
void h_24(double *state, double *unused, double *out_4289260273971546687) {
   out_4289260273971546687[0] = state[4];
   out_4289260273971546687[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4630345411854858538) {
   out_4630345411854858538[0] = 0;
   out_4630345411854858538[1] = 0;
   out_4630345411854858538[2] = 0;
   out_4630345411854858538[3] = 0;
   out_4630345411854858538[4] = 1;
   out_4630345411854858538[5] = 0;
   out_4630345411854858538[6] = 0;
   out_4630345411854858538[7] = 0;
   out_4630345411854858538[8] = 0;
   out_4630345411854858538[9] = 0;
   out_4630345411854858538[10] = 0;
   out_4630345411854858538[11] = 0;
   out_4630345411854858538[12] = 0;
   out_4630345411854858538[13] = 0;
   out_4630345411854858538[14] = 1;
   out_4630345411854858538[15] = 0;
   out_4630345411854858538[16] = 0;
   out_4630345411854858538[17] = 0;
}
void h_30(double *state, double *unused, double *out_5496384311818728944) {
   out_5496384311818728944[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7315742551949676553) {
   out_7315742551949676553[0] = 0;
   out_7315742551949676553[1] = 0;
   out_7315742551949676553[2] = 0;
   out_7315742551949676553[3] = 0;
   out_7315742551949676553[4] = 1;
   out_7315742551949676553[5] = 0;
   out_7315742551949676553[6] = 0;
   out_7315742551949676553[7] = 0;
   out_7315742551949676553[8] = 0;
}
void h_26(double *state, double *unused, double *out_8533170363263061629) {
   out_8533170363263061629[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4871165244378570212) {
   out_4871165244378570212[0] = 0;
   out_4871165244378570212[1] = 0;
   out_4871165244378570212[2] = 0;
   out_4871165244378570212[3] = 0;
   out_4871165244378570212[4] = 0;
   out_4871165244378570212[5] = 0;
   out_4871165244378570212[6] = 0;
   out_4871165244378570212[7] = 1;
   out_4871165244378570212[8] = 0;
}
void h_27(double *state, double *unused, double *out_1557338506084363422) {
   out_1557338506084363422[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8956238209959450152) {
   out_8956238209959450152[0] = 0;
   out_8956238209959450152[1] = 0;
   out_8956238209959450152[2] = 0;
   out_8956238209959450152[3] = 1;
   out_8956238209959450152[4] = 0;
   out_8956238209959450152[5] = 0;
   out_8956238209959450152[6] = 0;
   out_8956238209959450152[7] = 0;
   out_8956238209959450152[8] = 0;
}
void h_29(double *state, double *unused, double *out_8328173732434714358) {
   out_8328173732434714358[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6805511207635284369) {
   out_6805511207635284369[0] = 0;
   out_6805511207635284369[1] = 1;
   out_6805511207635284369[2] = 0;
   out_6805511207635284369[3] = 0;
   out_6805511207635284369[4] = 0;
   out_6805511207635284369[5] = 0;
   out_6805511207635284369[6] = 0;
   out_6805511207635284369[7] = 0;
   out_6805511207635284369[8] = 0;
}
void h_28(double *state, double *unused, double *out_2725082307160505159) {
   out_2725082307160505159[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6558833849004736673) {
   out_6558833849004736673[0] = 1;
   out_6558833849004736673[1] = 0;
   out_6558833849004736673[2] = 0;
   out_6558833849004736673[3] = 0;
   out_6558833849004736673[4] = 0;
   out_6558833849004736673[5] = 0;
   out_6558833849004736673[6] = 0;
   out_6558833849004736673[7] = 0;
   out_6558833849004736673[8] = 0;
}
void h_31(double *state, double *unused, double *out_6022337867189342591) {
   out_6022337867189342591[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4244957142145218736) {
   out_4244957142145218736[0] = 0;
   out_4244957142145218736[1] = 0;
   out_4244957142145218736[2] = 0;
   out_4244957142145218736[3] = 0;
   out_4244957142145218736[4] = 0;
   out_4244957142145218736[5] = 0;
   out_4244957142145218736[6] = 0;
   out_4244957142145218736[7] = 0;
   out_4244957142145218736[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_3617824066507182600) {
  err_fun(nom_x, delta_x, out_3617824066507182600);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7609445843503775366) {
  inv_err_fun(nom_x, true_x, out_7609445843503775366);
}
void car_H_mod_fun(double *state, double *out_123298891024053193) {
  H_mod_fun(state, out_123298891024053193);
}
void car_f_fun(double *state, double dt, double *out_3098113541010151714) {
  f_fun(state,  dt, out_3098113541010151714);
}
void car_F_fun(double *state, double dt, double *out_8403537800293641243) {
  F_fun(state,  dt, out_8403537800293641243);
}
void car_h_25(double *state, double *unused, double *out_1858934783564706594) {
  h_25(state, unused, out_1858934783564706594);
}
void car_H_25(double *state, double *unused, double *out_8612668563252626436) {
  H_25(state, unused, out_8612668563252626436);
}
void car_h_24(double *state, double *unused, double *out_4289260273971546687) {
  h_24(state, unused, out_4289260273971546687);
}
void car_H_24(double *state, double *unused, double *out_4630345411854858538) {
  H_24(state, unused, out_4630345411854858538);
}
void car_h_30(double *state, double *unused, double *out_5496384311818728944) {
  h_30(state, unused, out_5496384311818728944);
}
void car_H_30(double *state, double *unused, double *out_7315742551949676553) {
  H_30(state, unused, out_7315742551949676553);
}
void car_h_26(double *state, double *unused, double *out_8533170363263061629) {
  h_26(state, unused, out_8533170363263061629);
}
void car_H_26(double *state, double *unused, double *out_4871165244378570212) {
  H_26(state, unused, out_4871165244378570212);
}
void car_h_27(double *state, double *unused, double *out_1557338506084363422) {
  h_27(state, unused, out_1557338506084363422);
}
void car_H_27(double *state, double *unused, double *out_8956238209959450152) {
  H_27(state, unused, out_8956238209959450152);
}
void car_h_29(double *state, double *unused, double *out_8328173732434714358) {
  h_29(state, unused, out_8328173732434714358);
}
void car_H_29(double *state, double *unused, double *out_6805511207635284369) {
  H_29(state, unused, out_6805511207635284369);
}
void car_h_28(double *state, double *unused, double *out_2725082307160505159) {
  h_28(state, unused, out_2725082307160505159);
}
void car_H_28(double *state, double *unused, double *out_6558833849004736673) {
  H_28(state, unused, out_6558833849004736673);
}
void car_h_31(double *state, double *unused, double *out_6022337867189342591) {
  h_31(state, unused, out_6022337867189342591);
}
void car_H_31(double *state, double *unused, double *out_4244957142145218736) {
  H_31(state, unused, out_4244957142145218736);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
