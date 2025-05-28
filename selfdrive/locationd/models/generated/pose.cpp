#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6788482671477646176) {
   out_6788482671477646176[0] = delta_x[0] + nom_x[0];
   out_6788482671477646176[1] = delta_x[1] + nom_x[1];
   out_6788482671477646176[2] = delta_x[2] + nom_x[2];
   out_6788482671477646176[3] = delta_x[3] + nom_x[3];
   out_6788482671477646176[4] = delta_x[4] + nom_x[4];
   out_6788482671477646176[5] = delta_x[5] + nom_x[5];
   out_6788482671477646176[6] = delta_x[6] + nom_x[6];
   out_6788482671477646176[7] = delta_x[7] + nom_x[7];
   out_6788482671477646176[8] = delta_x[8] + nom_x[8];
   out_6788482671477646176[9] = delta_x[9] + nom_x[9];
   out_6788482671477646176[10] = delta_x[10] + nom_x[10];
   out_6788482671477646176[11] = delta_x[11] + nom_x[11];
   out_6788482671477646176[12] = delta_x[12] + nom_x[12];
   out_6788482671477646176[13] = delta_x[13] + nom_x[13];
   out_6788482671477646176[14] = delta_x[14] + nom_x[14];
   out_6788482671477646176[15] = delta_x[15] + nom_x[15];
   out_6788482671477646176[16] = delta_x[16] + nom_x[16];
   out_6788482671477646176[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2293652614005689133) {
   out_2293652614005689133[0] = -nom_x[0] + true_x[0];
   out_2293652614005689133[1] = -nom_x[1] + true_x[1];
   out_2293652614005689133[2] = -nom_x[2] + true_x[2];
   out_2293652614005689133[3] = -nom_x[3] + true_x[3];
   out_2293652614005689133[4] = -nom_x[4] + true_x[4];
   out_2293652614005689133[5] = -nom_x[5] + true_x[5];
   out_2293652614005689133[6] = -nom_x[6] + true_x[6];
   out_2293652614005689133[7] = -nom_x[7] + true_x[7];
   out_2293652614005689133[8] = -nom_x[8] + true_x[8];
   out_2293652614005689133[9] = -nom_x[9] + true_x[9];
   out_2293652614005689133[10] = -nom_x[10] + true_x[10];
   out_2293652614005689133[11] = -nom_x[11] + true_x[11];
   out_2293652614005689133[12] = -nom_x[12] + true_x[12];
   out_2293652614005689133[13] = -nom_x[13] + true_x[13];
   out_2293652614005689133[14] = -nom_x[14] + true_x[14];
   out_2293652614005689133[15] = -nom_x[15] + true_x[15];
   out_2293652614005689133[16] = -nom_x[16] + true_x[16];
   out_2293652614005689133[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6859876955096240212) {
   out_6859876955096240212[0] = 1.0;
   out_6859876955096240212[1] = 0.0;
   out_6859876955096240212[2] = 0.0;
   out_6859876955096240212[3] = 0.0;
   out_6859876955096240212[4] = 0.0;
   out_6859876955096240212[5] = 0.0;
   out_6859876955096240212[6] = 0.0;
   out_6859876955096240212[7] = 0.0;
   out_6859876955096240212[8] = 0.0;
   out_6859876955096240212[9] = 0.0;
   out_6859876955096240212[10] = 0.0;
   out_6859876955096240212[11] = 0.0;
   out_6859876955096240212[12] = 0.0;
   out_6859876955096240212[13] = 0.0;
   out_6859876955096240212[14] = 0.0;
   out_6859876955096240212[15] = 0.0;
   out_6859876955096240212[16] = 0.0;
   out_6859876955096240212[17] = 0.0;
   out_6859876955096240212[18] = 0.0;
   out_6859876955096240212[19] = 1.0;
   out_6859876955096240212[20] = 0.0;
   out_6859876955096240212[21] = 0.0;
   out_6859876955096240212[22] = 0.0;
   out_6859876955096240212[23] = 0.0;
   out_6859876955096240212[24] = 0.0;
   out_6859876955096240212[25] = 0.0;
   out_6859876955096240212[26] = 0.0;
   out_6859876955096240212[27] = 0.0;
   out_6859876955096240212[28] = 0.0;
   out_6859876955096240212[29] = 0.0;
   out_6859876955096240212[30] = 0.0;
   out_6859876955096240212[31] = 0.0;
   out_6859876955096240212[32] = 0.0;
   out_6859876955096240212[33] = 0.0;
   out_6859876955096240212[34] = 0.0;
   out_6859876955096240212[35] = 0.0;
   out_6859876955096240212[36] = 0.0;
   out_6859876955096240212[37] = 0.0;
   out_6859876955096240212[38] = 1.0;
   out_6859876955096240212[39] = 0.0;
   out_6859876955096240212[40] = 0.0;
   out_6859876955096240212[41] = 0.0;
   out_6859876955096240212[42] = 0.0;
   out_6859876955096240212[43] = 0.0;
   out_6859876955096240212[44] = 0.0;
   out_6859876955096240212[45] = 0.0;
   out_6859876955096240212[46] = 0.0;
   out_6859876955096240212[47] = 0.0;
   out_6859876955096240212[48] = 0.0;
   out_6859876955096240212[49] = 0.0;
   out_6859876955096240212[50] = 0.0;
   out_6859876955096240212[51] = 0.0;
   out_6859876955096240212[52] = 0.0;
   out_6859876955096240212[53] = 0.0;
   out_6859876955096240212[54] = 0.0;
   out_6859876955096240212[55] = 0.0;
   out_6859876955096240212[56] = 0.0;
   out_6859876955096240212[57] = 1.0;
   out_6859876955096240212[58] = 0.0;
   out_6859876955096240212[59] = 0.0;
   out_6859876955096240212[60] = 0.0;
   out_6859876955096240212[61] = 0.0;
   out_6859876955096240212[62] = 0.0;
   out_6859876955096240212[63] = 0.0;
   out_6859876955096240212[64] = 0.0;
   out_6859876955096240212[65] = 0.0;
   out_6859876955096240212[66] = 0.0;
   out_6859876955096240212[67] = 0.0;
   out_6859876955096240212[68] = 0.0;
   out_6859876955096240212[69] = 0.0;
   out_6859876955096240212[70] = 0.0;
   out_6859876955096240212[71] = 0.0;
   out_6859876955096240212[72] = 0.0;
   out_6859876955096240212[73] = 0.0;
   out_6859876955096240212[74] = 0.0;
   out_6859876955096240212[75] = 0.0;
   out_6859876955096240212[76] = 1.0;
   out_6859876955096240212[77] = 0.0;
   out_6859876955096240212[78] = 0.0;
   out_6859876955096240212[79] = 0.0;
   out_6859876955096240212[80] = 0.0;
   out_6859876955096240212[81] = 0.0;
   out_6859876955096240212[82] = 0.0;
   out_6859876955096240212[83] = 0.0;
   out_6859876955096240212[84] = 0.0;
   out_6859876955096240212[85] = 0.0;
   out_6859876955096240212[86] = 0.0;
   out_6859876955096240212[87] = 0.0;
   out_6859876955096240212[88] = 0.0;
   out_6859876955096240212[89] = 0.0;
   out_6859876955096240212[90] = 0.0;
   out_6859876955096240212[91] = 0.0;
   out_6859876955096240212[92] = 0.0;
   out_6859876955096240212[93] = 0.0;
   out_6859876955096240212[94] = 0.0;
   out_6859876955096240212[95] = 1.0;
   out_6859876955096240212[96] = 0.0;
   out_6859876955096240212[97] = 0.0;
   out_6859876955096240212[98] = 0.0;
   out_6859876955096240212[99] = 0.0;
   out_6859876955096240212[100] = 0.0;
   out_6859876955096240212[101] = 0.0;
   out_6859876955096240212[102] = 0.0;
   out_6859876955096240212[103] = 0.0;
   out_6859876955096240212[104] = 0.0;
   out_6859876955096240212[105] = 0.0;
   out_6859876955096240212[106] = 0.0;
   out_6859876955096240212[107] = 0.0;
   out_6859876955096240212[108] = 0.0;
   out_6859876955096240212[109] = 0.0;
   out_6859876955096240212[110] = 0.0;
   out_6859876955096240212[111] = 0.0;
   out_6859876955096240212[112] = 0.0;
   out_6859876955096240212[113] = 0.0;
   out_6859876955096240212[114] = 1.0;
   out_6859876955096240212[115] = 0.0;
   out_6859876955096240212[116] = 0.0;
   out_6859876955096240212[117] = 0.0;
   out_6859876955096240212[118] = 0.0;
   out_6859876955096240212[119] = 0.0;
   out_6859876955096240212[120] = 0.0;
   out_6859876955096240212[121] = 0.0;
   out_6859876955096240212[122] = 0.0;
   out_6859876955096240212[123] = 0.0;
   out_6859876955096240212[124] = 0.0;
   out_6859876955096240212[125] = 0.0;
   out_6859876955096240212[126] = 0.0;
   out_6859876955096240212[127] = 0.0;
   out_6859876955096240212[128] = 0.0;
   out_6859876955096240212[129] = 0.0;
   out_6859876955096240212[130] = 0.0;
   out_6859876955096240212[131] = 0.0;
   out_6859876955096240212[132] = 0.0;
   out_6859876955096240212[133] = 1.0;
   out_6859876955096240212[134] = 0.0;
   out_6859876955096240212[135] = 0.0;
   out_6859876955096240212[136] = 0.0;
   out_6859876955096240212[137] = 0.0;
   out_6859876955096240212[138] = 0.0;
   out_6859876955096240212[139] = 0.0;
   out_6859876955096240212[140] = 0.0;
   out_6859876955096240212[141] = 0.0;
   out_6859876955096240212[142] = 0.0;
   out_6859876955096240212[143] = 0.0;
   out_6859876955096240212[144] = 0.0;
   out_6859876955096240212[145] = 0.0;
   out_6859876955096240212[146] = 0.0;
   out_6859876955096240212[147] = 0.0;
   out_6859876955096240212[148] = 0.0;
   out_6859876955096240212[149] = 0.0;
   out_6859876955096240212[150] = 0.0;
   out_6859876955096240212[151] = 0.0;
   out_6859876955096240212[152] = 1.0;
   out_6859876955096240212[153] = 0.0;
   out_6859876955096240212[154] = 0.0;
   out_6859876955096240212[155] = 0.0;
   out_6859876955096240212[156] = 0.0;
   out_6859876955096240212[157] = 0.0;
   out_6859876955096240212[158] = 0.0;
   out_6859876955096240212[159] = 0.0;
   out_6859876955096240212[160] = 0.0;
   out_6859876955096240212[161] = 0.0;
   out_6859876955096240212[162] = 0.0;
   out_6859876955096240212[163] = 0.0;
   out_6859876955096240212[164] = 0.0;
   out_6859876955096240212[165] = 0.0;
   out_6859876955096240212[166] = 0.0;
   out_6859876955096240212[167] = 0.0;
   out_6859876955096240212[168] = 0.0;
   out_6859876955096240212[169] = 0.0;
   out_6859876955096240212[170] = 0.0;
   out_6859876955096240212[171] = 1.0;
   out_6859876955096240212[172] = 0.0;
   out_6859876955096240212[173] = 0.0;
   out_6859876955096240212[174] = 0.0;
   out_6859876955096240212[175] = 0.0;
   out_6859876955096240212[176] = 0.0;
   out_6859876955096240212[177] = 0.0;
   out_6859876955096240212[178] = 0.0;
   out_6859876955096240212[179] = 0.0;
   out_6859876955096240212[180] = 0.0;
   out_6859876955096240212[181] = 0.0;
   out_6859876955096240212[182] = 0.0;
   out_6859876955096240212[183] = 0.0;
   out_6859876955096240212[184] = 0.0;
   out_6859876955096240212[185] = 0.0;
   out_6859876955096240212[186] = 0.0;
   out_6859876955096240212[187] = 0.0;
   out_6859876955096240212[188] = 0.0;
   out_6859876955096240212[189] = 0.0;
   out_6859876955096240212[190] = 1.0;
   out_6859876955096240212[191] = 0.0;
   out_6859876955096240212[192] = 0.0;
   out_6859876955096240212[193] = 0.0;
   out_6859876955096240212[194] = 0.0;
   out_6859876955096240212[195] = 0.0;
   out_6859876955096240212[196] = 0.0;
   out_6859876955096240212[197] = 0.0;
   out_6859876955096240212[198] = 0.0;
   out_6859876955096240212[199] = 0.0;
   out_6859876955096240212[200] = 0.0;
   out_6859876955096240212[201] = 0.0;
   out_6859876955096240212[202] = 0.0;
   out_6859876955096240212[203] = 0.0;
   out_6859876955096240212[204] = 0.0;
   out_6859876955096240212[205] = 0.0;
   out_6859876955096240212[206] = 0.0;
   out_6859876955096240212[207] = 0.0;
   out_6859876955096240212[208] = 0.0;
   out_6859876955096240212[209] = 1.0;
   out_6859876955096240212[210] = 0.0;
   out_6859876955096240212[211] = 0.0;
   out_6859876955096240212[212] = 0.0;
   out_6859876955096240212[213] = 0.0;
   out_6859876955096240212[214] = 0.0;
   out_6859876955096240212[215] = 0.0;
   out_6859876955096240212[216] = 0.0;
   out_6859876955096240212[217] = 0.0;
   out_6859876955096240212[218] = 0.0;
   out_6859876955096240212[219] = 0.0;
   out_6859876955096240212[220] = 0.0;
   out_6859876955096240212[221] = 0.0;
   out_6859876955096240212[222] = 0.0;
   out_6859876955096240212[223] = 0.0;
   out_6859876955096240212[224] = 0.0;
   out_6859876955096240212[225] = 0.0;
   out_6859876955096240212[226] = 0.0;
   out_6859876955096240212[227] = 0.0;
   out_6859876955096240212[228] = 1.0;
   out_6859876955096240212[229] = 0.0;
   out_6859876955096240212[230] = 0.0;
   out_6859876955096240212[231] = 0.0;
   out_6859876955096240212[232] = 0.0;
   out_6859876955096240212[233] = 0.0;
   out_6859876955096240212[234] = 0.0;
   out_6859876955096240212[235] = 0.0;
   out_6859876955096240212[236] = 0.0;
   out_6859876955096240212[237] = 0.0;
   out_6859876955096240212[238] = 0.0;
   out_6859876955096240212[239] = 0.0;
   out_6859876955096240212[240] = 0.0;
   out_6859876955096240212[241] = 0.0;
   out_6859876955096240212[242] = 0.0;
   out_6859876955096240212[243] = 0.0;
   out_6859876955096240212[244] = 0.0;
   out_6859876955096240212[245] = 0.0;
   out_6859876955096240212[246] = 0.0;
   out_6859876955096240212[247] = 1.0;
   out_6859876955096240212[248] = 0.0;
   out_6859876955096240212[249] = 0.0;
   out_6859876955096240212[250] = 0.0;
   out_6859876955096240212[251] = 0.0;
   out_6859876955096240212[252] = 0.0;
   out_6859876955096240212[253] = 0.0;
   out_6859876955096240212[254] = 0.0;
   out_6859876955096240212[255] = 0.0;
   out_6859876955096240212[256] = 0.0;
   out_6859876955096240212[257] = 0.0;
   out_6859876955096240212[258] = 0.0;
   out_6859876955096240212[259] = 0.0;
   out_6859876955096240212[260] = 0.0;
   out_6859876955096240212[261] = 0.0;
   out_6859876955096240212[262] = 0.0;
   out_6859876955096240212[263] = 0.0;
   out_6859876955096240212[264] = 0.0;
   out_6859876955096240212[265] = 0.0;
   out_6859876955096240212[266] = 1.0;
   out_6859876955096240212[267] = 0.0;
   out_6859876955096240212[268] = 0.0;
   out_6859876955096240212[269] = 0.0;
   out_6859876955096240212[270] = 0.0;
   out_6859876955096240212[271] = 0.0;
   out_6859876955096240212[272] = 0.0;
   out_6859876955096240212[273] = 0.0;
   out_6859876955096240212[274] = 0.0;
   out_6859876955096240212[275] = 0.0;
   out_6859876955096240212[276] = 0.0;
   out_6859876955096240212[277] = 0.0;
   out_6859876955096240212[278] = 0.0;
   out_6859876955096240212[279] = 0.0;
   out_6859876955096240212[280] = 0.0;
   out_6859876955096240212[281] = 0.0;
   out_6859876955096240212[282] = 0.0;
   out_6859876955096240212[283] = 0.0;
   out_6859876955096240212[284] = 0.0;
   out_6859876955096240212[285] = 1.0;
   out_6859876955096240212[286] = 0.0;
   out_6859876955096240212[287] = 0.0;
   out_6859876955096240212[288] = 0.0;
   out_6859876955096240212[289] = 0.0;
   out_6859876955096240212[290] = 0.0;
   out_6859876955096240212[291] = 0.0;
   out_6859876955096240212[292] = 0.0;
   out_6859876955096240212[293] = 0.0;
   out_6859876955096240212[294] = 0.0;
   out_6859876955096240212[295] = 0.0;
   out_6859876955096240212[296] = 0.0;
   out_6859876955096240212[297] = 0.0;
   out_6859876955096240212[298] = 0.0;
   out_6859876955096240212[299] = 0.0;
   out_6859876955096240212[300] = 0.0;
   out_6859876955096240212[301] = 0.0;
   out_6859876955096240212[302] = 0.0;
   out_6859876955096240212[303] = 0.0;
   out_6859876955096240212[304] = 1.0;
   out_6859876955096240212[305] = 0.0;
   out_6859876955096240212[306] = 0.0;
   out_6859876955096240212[307] = 0.0;
   out_6859876955096240212[308] = 0.0;
   out_6859876955096240212[309] = 0.0;
   out_6859876955096240212[310] = 0.0;
   out_6859876955096240212[311] = 0.0;
   out_6859876955096240212[312] = 0.0;
   out_6859876955096240212[313] = 0.0;
   out_6859876955096240212[314] = 0.0;
   out_6859876955096240212[315] = 0.0;
   out_6859876955096240212[316] = 0.0;
   out_6859876955096240212[317] = 0.0;
   out_6859876955096240212[318] = 0.0;
   out_6859876955096240212[319] = 0.0;
   out_6859876955096240212[320] = 0.0;
   out_6859876955096240212[321] = 0.0;
   out_6859876955096240212[322] = 0.0;
   out_6859876955096240212[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7198856022790088301) {
   out_7198856022790088301[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7198856022790088301[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7198856022790088301[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7198856022790088301[3] = dt*state[12] + state[3];
   out_7198856022790088301[4] = dt*state[13] + state[4];
   out_7198856022790088301[5] = dt*state[14] + state[5];
   out_7198856022790088301[6] = state[6];
   out_7198856022790088301[7] = state[7];
   out_7198856022790088301[8] = state[8];
   out_7198856022790088301[9] = state[9];
   out_7198856022790088301[10] = state[10];
   out_7198856022790088301[11] = state[11];
   out_7198856022790088301[12] = state[12];
   out_7198856022790088301[13] = state[13];
   out_7198856022790088301[14] = state[14];
   out_7198856022790088301[15] = state[15];
   out_7198856022790088301[16] = state[16];
   out_7198856022790088301[17] = state[17];
}
void F_fun(double *state, double dt, double *out_782635061309417912) {
   out_782635061309417912[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_782635061309417912[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_782635061309417912[2] = 0;
   out_782635061309417912[3] = 0;
   out_782635061309417912[4] = 0;
   out_782635061309417912[5] = 0;
   out_782635061309417912[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_782635061309417912[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_782635061309417912[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_782635061309417912[9] = 0;
   out_782635061309417912[10] = 0;
   out_782635061309417912[11] = 0;
   out_782635061309417912[12] = 0;
   out_782635061309417912[13] = 0;
   out_782635061309417912[14] = 0;
   out_782635061309417912[15] = 0;
   out_782635061309417912[16] = 0;
   out_782635061309417912[17] = 0;
   out_782635061309417912[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_782635061309417912[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_782635061309417912[20] = 0;
   out_782635061309417912[21] = 0;
   out_782635061309417912[22] = 0;
   out_782635061309417912[23] = 0;
   out_782635061309417912[24] = 0;
   out_782635061309417912[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_782635061309417912[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_782635061309417912[27] = 0;
   out_782635061309417912[28] = 0;
   out_782635061309417912[29] = 0;
   out_782635061309417912[30] = 0;
   out_782635061309417912[31] = 0;
   out_782635061309417912[32] = 0;
   out_782635061309417912[33] = 0;
   out_782635061309417912[34] = 0;
   out_782635061309417912[35] = 0;
   out_782635061309417912[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_782635061309417912[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_782635061309417912[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_782635061309417912[39] = 0;
   out_782635061309417912[40] = 0;
   out_782635061309417912[41] = 0;
   out_782635061309417912[42] = 0;
   out_782635061309417912[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_782635061309417912[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_782635061309417912[45] = 0;
   out_782635061309417912[46] = 0;
   out_782635061309417912[47] = 0;
   out_782635061309417912[48] = 0;
   out_782635061309417912[49] = 0;
   out_782635061309417912[50] = 0;
   out_782635061309417912[51] = 0;
   out_782635061309417912[52] = 0;
   out_782635061309417912[53] = 0;
   out_782635061309417912[54] = 0;
   out_782635061309417912[55] = 0;
   out_782635061309417912[56] = 0;
   out_782635061309417912[57] = 1;
   out_782635061309417912[58] = 0;
   out_782635061309417912[59] = 0;
   out_782635061309417912[60] = 0;
   out_782635061309417912[61] = 0;
   out_782635061309417912[62] = 0;
   out_782635061309417912[63] = 0;
   out_782635061309417912[64] = 0;
   out_782635061309417912[65] = 0;
   out_782635061309417912[66] = dt;
   out_782635061309417912[67] = 0;
   out_782635061309417912[68] = 0;
   out_782635061309417912[69] = 0;
   out_782635061309417912[70] = 0;
   out_782635061309417912[71] = 0;
   out_782635061309417912[72] = 0;
   out_782635061309417912[73] = 0;
   out_782635061309417912[74] = 0;
   out_782635061309417912[75] = 0;
   out_782635061309417912[76] = 1;
   out_782635061309417912[77] = 0;
   out_782635061309417912[78] = 0;
   out_782635061309417912[79] = 0;
   out_782635061309417912[80] = 0;
   out_782635061309417912[81] = 0;
   out_782635061309417912[82] = 0;
   out_782635061309417912[83] = 0;
   out_782635061309417912[84] = 0;
   out_782635061309417912[85] = dt;
   out_782635061309417912[86] = 0;
   out_782635061309417912[87] = 0;
   out_782635061309417912[88] = 0;
   out_782635061309417912[89] = 0;
   out_782635061309417912[90] = 0;
   out_782635061309417912[91] = 0;
   out_782635061309417912[92] = 0;
   out_782635061309417912[93] = 0;
   out_782635061309417912[94] = 0;
   out_782635061309417912[95] = 1;
   out_782635061309417912[96] = 0;
   out_782635061309417912[97] = 0;
   out_782635061309417912[98] = 0;
   out_782635061309417912[99] = 0;
   out_782635061309417912[100] = 0;
   out_782635061309417912[101] = 0;
   out_782635061309417912[102] = 0;
   out_782635061309417912[103] = 0;
   out_782635061309417912[104] = dt;
   out_782635061309417912[105] = 0;
   out_782635061309417912[106] = 0;
   out_782635061309417912[107] = 0;
   out_782635061309417912[108] = 0;
   out_782635061309417912[109] = 0;
   out_782635061309417912[110] = 0;
   out_782635061309417912[111] = 0;
   out_782635061309417912[112] = 0;
   out_782635061309417912[113] = 0;
   out_782635061309417912[114] = 1;
   out_782635061309417912[115] = 0;
   out_782635061309417912[116] = 0;
   out_782635061309417912[117] = 0;
   out_782635061309417912[118] = 0;
   out_782635061309417912[119] = 0;
   out_782635061309417912[120] = 0;
   out_782635061309417912[121] = 0;
   out_782635061309417912[122] = 0;
   out_782635061309417912[123] = 0;
   out_782635061309417912[124] = 0;
   out_782635061309417912[125] = 0;
   out_782635061309417912[126] = 0;
   out_782635061309417912[127] = 0;
   out_782635061309417912[128] = 0;
   out_782635061309417912[129] = 0;
   out_782635061309417912[130] = 0;
   out_782635061309417912[131] = 0;
   out_782635061309417912[132] = 0;
   out_782635061309417912[133] = 1;
   out_782635061309417912[134] = 0;
   out_782635061309417912[135] = 0;
   out_782635061309417912[136] = 0;
   out_782635061309417912[137] = 0;
   out_782635061309417912[138] = 0;
   out_782635061309417912[139] = 0;
   out_782635061309417912[140] = 0;
   out_782635061309417912[141] = 0;
   out_782635061309417912[142] = 0;
   out_782635061309417912[143] = 0;
   out_782635061309417912[144] = 0;
   out_782635061309417912[145] = 0;
   out_782635061309417912[146] = 0;
   out_782635061309417912[147] = 0;
   out_782635061309417912[148] = 0;
   out_782635061309417912[149] = 0;
   out_782635061309417912[150] = 0;
   out_782635061309417912[151] = 0;
   out_782635061309417912[152] = 1;
   out_782635061309417912[153] = 0;
   out_782635061309417912[154] = 0;
   out_782635061309417912[155] = 0;
   out_782635061309417912[156] = 0;
   out_782635061309417912[157] = 0;
   out_782635061309417912[158] = 0;
   out_782635061309417912[159] = 0;
   out_782635061309417912[160] = 0;
   out_782635061309417912[161] = 0;
   out_782635061309417912[162] = 0;
   out_782635061309417912[163] = 0;
   out_782635061309417912[164] = 0;
   out_782635061309417912[165] = 0;
   out_782635061309417912[166] = 0;
   out_782635061309417912[167] = 0;
   out_782635061309417912[168] = 0;
   out_782635061309417912[169] = 0;
   out_782635061309417912[170] = 0;
   out_782635061309417912[171] = 1;
   out_782635061309417912[172] = 0;
   out_782635061309417912[173] = 0;
   out_782635061309417912[174] = 0;
   out_782635061309417912[175] = 0;
   out_782635061309417912[176] = 0;
   out_782635061309417912[177] = 0;
   out_782635061309417912[178] = 0;
   out_782635061309417912[179] = 0;
   out_782635061309417912[180] = 0;
   out_782635061309417912[181] = 0;
   out_782635061309417912[182] = 0;
   out_782635061309417912[183] = 0;
   out_782635061309417912[184] = 0;
   out_782635061309417912[185] = 0;
   out_782635061309417912[186] = 0;
   out_782635061309417912[187] = 0;
   out_782635061309417912[188] = 0;
   out_782635061309417912[189] = 0;
   out_782635061309417912[190] = 1;
   out_782635061309417912[191] = 0;
   out_782635061309417912[192] = 0;
   out_782635061309417912[193] = 0;
   out_782635061309417912[194] = 0;
   out_782635061309417912[195] = 0;
   out_782635061309417912[196] = 0;
   out_782635061309417912[197] = 0;
   out_782635061309417912[198] = 0;
   out_782635061309417912[199] = 0;
   out_782635061309417912[200] = 0;
   out_782635061309417912[201] = 0;
   out_782635061309417912[202] = 0;
   out_782635061309417912[203] = 0;
   out_782635061309417912[204] = 0;
   out_782635061309417912[205] = 0;
   out_782635061309417912[206] = 0;
   out_782635061309417912[207] = 0;
   out_782635061309417912[208] = 0;
   out_782635061309417912[209] = 1;
   out_782635061309417912[210] = 0;
   out_782635061309417912[211] = 0;
   out_782635061309417912[212] = 0;
   out_782635061309417912[213] = 0;
   out_782635061309417912[214] = 0;
   out_782635061309417912[215] = 0;
   out_782635061309417912[216] = 0;
   out_782635061309417912[217] = 0;
   out_782635061309417912[218] = 0;
   out_782635061309417912[219] = 0;
   out_782635061309417912[220] = 0;
   out_782635061309417912[221] = 0;
   out_782635061309417912[222] = 0;
   out_782635061309417912[223] = 0;
   out_782635061309417912[224] = 0;
   out_782635061309417912[225] = 0;
   out_782635061309417912[226] = 0;
   out_782635061309417912[227] = 0;
   out_782635061309417912[228] = 1;
   out_782635061309417912[229] = 0;
   out_782635061309417912[230] = 0;
   out_782635061309417912[231] = 0;
   out_782635061309417912[232] = 0;
   out_782635061309417912[233] = 0;
   out_782635061309417912[234] = 0;
   out_782635061309417912[235] = 0;
   out_782635061309417912[236] = 0;
   out_782635061309417912[237] = 0;
   out_782635061309417912[238] = 0;
   out_782635061309417912[239] = 0;
   out_782635061309417912[240] = 0;
   out_782635061309417912[241] = 0;
   out_782635061309417912[242] = 0;
   out_782635061309417912[243] = 0;
   out_782635061309417912[244] = 0;
   out_782635061309417912[245] = 0;
   out_782635061309417912[246] = 0;
   out_782635061309417912[247] = 1;
   out_782635061309417912[248] = 0;
   out_782635061309417912[249] = 0;
   out_782635061309417912[250] = 0;
   out_782635061309417912[251] = 0;
   out_782635061309417912[252] = 0;
   out_782635061309417912[253] = 0;
   out_782635061309417912[254] = 0;
   out_782635061309417912[255] = 0;
   out_782635061309417912[256] = 0;
   out_782635061309417912[257] = 0;
   out_782635061309417912[258] = 0;
   out_782635061309417912[259] = 0;
   out_782635061309417912[260] = 0;
   out_782635061309417912[261] = 0;
   out_782635061309417912[262] = 0;
   out_782635061309417912[263] = 0;
   out_782635061309417912[264] = 0;
   out_782635061309417912[265] = 0;
   out_782635061309417912[266] = 1;
   out_782635061309417912[267] = 0;
   out_782635061309417912[268] = 0;
   out_782635061309417912[269] = 0;
   out_782635061309417912[270] = 0;
   out_782635061309417912[271] = 0;
   out_782635061309417912[272] = 0;
   out_782635061309417912[273] = 0;
   out_782635061309417912[274] = 0;
   out_782635061309417912[275] = 0;
   out_782635061309417912[276] = 0;
   out_782635061309417912[277] = 0;
   out_782635061309417912[278] = 0;
   out_782635061309417912[279] = 0;
   out_782635061309417912[280] = 0;
   out_782635061309417912[281] = 0;
   out_782635061309417912[282] = 0;
   out_782635061309417912[283] = 0;
   out_782635061309417912[284] = 0;
   out_782635061309417912[285] = 1;
   out_782635061309417912[286] = 0;
   out_782635061309417912[287] = 0;
   out_782635061309417912[288] = 0;
   out_782635061309417912[289] = 0;
   out_782635061309417912[290] = 0;
   out_782635061309417912[291] = 0;
   out_782635061309417912[292] = 0;
   out_782635061309417912[293] = 0;
   out_782635061309417912[294] = 0;
   out_782635061309417912[295] = 0;
   out_782635061309417912[296] = 0;
   out_782635061309417912[297] = 0;
   out_782635061309417912[298] = 0;
   out_782635061309417912[299] = 0;
   out_782635061309417912[300] = 0;
   out_782635061309417912[301] = 0;
   out_782635061309417912[302] = 0;
   out_782635061309417912[303] = 0;
   out_782635061309417912[304] = 1;
   out_782635061309417912[305] = 0;
   out_782635061309417912[306] = 0;
   out_782635061309417912[307] = 0;
   out_782635061309417912[308] = 0;
   out_782635061309417912[309] = 0;
   out_782635061309417912[310] = 0;
   out_782635061309417912[311] = 0;
   out_782635061309417912[312] = 0;
   out_782635061309417912[313] = 0;
   out_782635061309417912[314] = 0;
   out_782635061309417912[315] = 0;
   out_782635061309417912[316] = 0;
   out_782635061309417912[317] = 0;
   out_782635061309417912[318] = 0;
   out_782635061309417912[319] = 0;
   out_782635061309417912[320] = 0;
   out_782635061309417912[321] = 0;
   out_782635061309417912[322] = 0;
   out_782635061309417912[323] = 1;
}
void h_4(double *state, double *unused, double *out_1764421233415442805) {
   out_1764421233415442805[0] = state[6] + state[9];
   out_1764421233415442805[1] = state[7] + state[10];
   out_1764421233415442805[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2721139104072157718) {
   out_2721139104072157718[0] = 0;
   out_2721139104072157718[1] = 0;
   out_2721139104072157718[2] = 0;
   out_2721139104072157718[3] = 0;
   out_2721139104072157718[4] = 0;
   out_2721139104072157718[5] = 0;
   out_2721139104072157718[6] = 1;
   out_2721139104072157718[7] = 0;
   out_2721139104072157718[8] = 0;
   out_2721139104072157718[9] = 1;
   out_2721139104072157718[10] = 0;
   out_2721139104072157718[11] = 0;
   out_2721139104072157718[12] = 0;
   out_2721139104072157718[13] = 0;
   out_2721139104072157718[14] = 0;
   out_2721139104072157718[15] = 0;
   out_2721139104072157718[16] = 0;
   out_2721139104072157718[17] = 0;
   out_2721139104072157718[18] = 0;
   out_2721139104072157718[19] = 0;
   out_2721139104072157718[20] = 0;
   out_2721139104072157718[21] = 0;
   out_2721139104072157718[22] = 0;
   out_2721139104072157718[23] = 0;
   out_2721139104072157718[24] = 0;
   out_2721139104072157718[25] = 1;
   out_2721139104072157718[26] = 0;
   out_2721139104072157718[27] = 0;
   out_2721139104072157718[28] = 1;
   out_2721139104072157718[29] = 0;
   out_2721139104072157718[30] = 0;
   out_2721139104072157718[31] = 0;
   out_2721139104072157718[32] = 0;
   out_2721139104072157718[33] = 0;
   out_2721139104072157718[34] = 0;
   out_2721139104072157718[35] = 0;
   out_2721139104072157718[36] = 0;
   out_2721139104072157718[37] = 0;
   out_2721139104072157718[38] = 0;
   out_2721139104072157718[39] = 0;
   out_2721139104072157718[40] = 0;
   out_2721139104072157718[41] = 0;
   out_2721139104072157718[42] = 0;
   out_2721139104072157718[43] = 0;
   out_2721139104072157718[44] = 1;
   out_2721139104072157718[45] = 0;
   out_2721139104072157718[46] = 0;
   out_2721139104072157718[47] = 1;
   out_2721139104072157718[48] = 0;
   out_2721139104072157718[49] = 0;
   out_2721139104072157718[50] = 0;
   out_2721139104072157718[51] = 0;
   out_2721139104072157718[52] = 0;
   out_2721139104072157718[53] = 0;
}
void h_10(double *state, double *unused, double *out_4355221798934046123) {
   out_4355221798934046123[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4355221798934046123[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4355221798934046123[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5312916087312009959) {
   out_5312916087312009959[0] = 0;
   out_5312916087312009959[1] = 9.8100000000000005*cos(state[1]);
   out_5312916087312009959[2] = 0;
   out_5312916087312009959[3] = 0;
   out_5312916087312009959[4] = -state[8];
   out_5312916087312009959[5] = state[7];
   out_5312916087312009959[6] = 0;
   out_5312916087312009959[7] = state[5];
   out_5312916087312009959[8] = -state[4];
   out_5312916087312009959[9] = 0;
   out_5312916087312009959[10] = 0;
   out_5312916087312009959[11] = 0;
   out_5312916087312009959[12] = 1;
   out_5312916087312009959[13] = 0;
   out_5312916087312009959[14] = 0;
   out_5312916087312009959[15] = 1;
   out_5312916087312009959[16] = 0;
   out_5312916087312009959[17] = 0;
   out_5312916087312009959[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5312916087312009959[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5312916087312009959[20] = 0;
   out_5312916087312009959[21] = state[8];
   out_5312916087312009959[22] = 0;
   out_5312916087312009959[23] = -state[6];
   out_5312916087312009959[24] = -state[5];
   out_5312916087312009959[25] = 0;
   out_5312916087312009959[26] = state[3];
   out_5312916087312009959[27] = 0;
   out_5312916087312009959[28] = 0;
   out_5312916087312009959[29] = 0;
   out_5312916087312009959[30] = 0;
   out_5312916087312009959[31] = 1;
   out_5312916087312009959[32] = 0;
   out_5312916087312009959[33] = 0;
   out_5312916087312009959[34] = 1;
   out_5312916087312009959[35] = 0;
   out_5312916087312009959[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5312916087312009959[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5312916087312009959[38] = 0;
   out_5312916087312009959[39] = -state[7];
   out_5312916087312009959[40] = state[6];
   out_5312916087312009959[41] = 0;
   out_5312916087312009959[42] = state[4];
   out_5312916087312009959[43] = -state[3];
   out_5312916087312009959[44] = 0;
   out_5312916087312009959[45] = 0;
   out_5312916087312009959[46] = 0;
   out_5312916087312009959[47] = 0;
   out_5312916087312009959[48] = 0;
   out_5312916087312009959[49] = 0;
   out_5312916087312009959[50] = 1;
   out_5312916087312009959[51] = 0;
   out_5312916087312009959[52] = 0;
   out_5312916087312009959[53] = 1;
}
void h_13(double *state, double *unused, double *out_5531667930420635084) {
   out_5531667930420635084[0] = state[3];
   out_5531667930420635084[1] = state[4];
   out_5531667930420635084[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5933412929404490519) {
   out_5933412929404490519[0] = 0;
   out_5933412929404490519[1] = 0;
   out_5933412929404490519[2] = 0;
   out_5933412929404490519[3] = 1;
   out_5933412929404490519[4] = 0;
   out_5933412929404490519[5] = 0;
   out_5933412929404490519[6] = 0;
   out_5933412929404490519[7] = 0;
   out_5933412929404490519[8] = 0;
   out_5933412929404490519[9] = 0;
   out_5933412929404490519[10] = 0;
   out_5933412929404490519[11] = 0;
   out_5933412929404490519[12] = 0;
   out_5933412929404490519[13] = 0;
   out_5933412929404490519[14] = 0;
   out_5933412929404490519[15] = 0;
   out_5933412929404490519[16] = 0;
   out_5933412929404490519[17] = 0;
   out_5933412929404490519[18] = 0;
   out_5933412929404490519[19] = 0;
   out_5933412929404490519[20] = 0;
   out_5933412929404490519[21] = 0;
   out_5933412929404490519[22] = 1;
   out_5933412929404490519[23] = 0;
   out_5933412929404490519[24] = 0;
   out_5933412929404490519[25] = 0;
   out_5933412929404490519[26] = 0;
   out_5933412929404490519[27] = 0;
   out_5933412929404490519[28] = 0;
   out_5933412929404490519[29] = 0;
   out_5933412929404490519[30] = 0;
   out_5933412929404490519[31] = 0;
   out_5933412929404490519[32] = 0;
   out_5933412929404490519[33] = 0;
   out_5933412929404490519[34] = 0;
   out_5933412929404490519[35] = 0;
   out_5933412929404490519[36] = 0;
   out_5933412929404490519[37] = 0;
   out_5933412929404490519[38] = 0;
   out_5933412929404490519[39] = 0;
   out_5933412929404490519[40] = 0;
   out_5933412929404490519[41] = 1;
   out_5933412929404490519[42] = 0;
   out_5933412929404490519[43] = 0;
   out_5933412929404490519[44] = 0;
   out_5933412929404490519[45] = 0;
   out_5933412929404490519[46] = 0;
   out_5933412929404490519[47] = 0;
   out_5933412929404490519[48] = 0;
   out_5933412929404490519[49] = 0;
   out_5933412929404490519[50] = 0;
   out_5933412929404490519[51] = 0;
   out_5933412929404490519[52] = 0;
   out_5933412929404490519[53] = 0;
}
void h_14(double *state, double *unused, double *out_8913575968829588963) {
   out_8913575968829588963[0] = state[6];
   out_8913575968829588963[1] = state[7];
   out_8913575968829588963[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6684379960411642247) {
   out_6684379960411642247[0] = 0;
   out_6684379960411642247[1] = 0;
   out_6684379960411642247[2] = 0;
   out_6684379960411642247[3] = 0;
   out_6684379960411642247[4] = 0;
   out_6684379960411642247[5] = 0;
   out_6684379960411642247[6] = 1;
   out_6684379960411642247[7] = 0;
   out_6684379960411642247[8] = 0;
   out_6684379960411642247[9] = 0;
   out_6684379960411642247[10] = 0;
   out_6684379960411642247[11] = 0;
   out_6684379960411642247[12] = 0;
   out_6684379960411642247[13] = 0;
   out_6684379960411642247[14] = 0;
   out_6684379960411642247[15] = 0;
   out_6684379960411642247[16] = 0;
   out_6684379960411642247[17] = 0;
   out_6684379960411642247[18] = 0;
   out_6684379960411642247[19] = 0;
   out_6684379960411642247[20] = 0;
   out_6684379960411642247[21] = 0;
   out_6684379960411642247[22] = 0;
   out_6684379960411642247[23] = 0;
   out_6684379960411642247[24] = 0;
   out_6684379960411642247[25] = 1;
   out_6684379960411642247[26] = 0;
   out_6684379960411642247[27] = 0;
   out_6684379960411642247[28] = 0;
   out_6684379960411642247[29] = 0;
   out_6684379960411642247[30] = 0;
   out_6684379960411642247[31] = 0;
   out_6684379960411642247[32] = 0;
   out_6684379960411642247[33] = 0;
   out_6684379960411642247[34] = 0;
   out_6684379960411642247[35] = 0;
   out_6684379960411642247[36] = 0;
   out_6684379960411642247[37] = 0;
   out_6684379960411642247[38] = 0;
   out_6684379960411642247[39] = 0;
   out_6684379960411642247[40] = 0;
   out_6684379960411642247[41] = 0;
   out_6684379960411642247[42] = 0;
   out_6684379960411642247[43] = 0;
   out_6684379960411642247[44] = 1;
   out_6684379960411642247[45] = 0;
   out_6684379960411642247[46] = 0;
   out_6684379960411642247[47] = 0;
   out_6684379960411642247[48] = 0;
   out_6684379960411642247[49] = 0;
   out_6684379960411642247[50] = 0;
   out_6684379960411642247[51] = 0;
   out_6684379960411642247[52] = 0;
   out_6684379960411642247[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_6788482671477646176) {
  err_fun(nom_x, delta_x, out_6788482671477646176);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2293652614005689133) {
  inv_err_fun(nom_x, true_x, out_2293652614005689133);
}
void pose_H_mod_fun(double *state, double *out_6859876955096240212) {
  H_mod_fun(state, out_6859876955096240212);
}
void pose_f_fun(double *state, double dt, double *out_7198856022790088301) {
  f_fun(state,  dt, out_7198856022790088301);
}
void pose_F_fun(double *state, double dt, double *out_782635061309417912) {
  F_fun(state,  dt, out_782635061309417912);
}
void pose_h_4(double *state, double *unused, double *out_1764421233415442805) {
  h_4(state, unused, out_1764421233415442805);
}
void pose_H_4(double *state, double *unused, double *out_2721139104072157718) {
  H_4(state, unused, out_2721139104072157718);
}
void pose_h_10(double *state, double *unused, double *out_4355221798934046123) {
  h_10(state, unused, out_4355221798934046123);
}
void pose_H_10(double *state, double *unused, double *out_5312916087312009959) {
  H_10(state, unused, out_5312916087312009959);
}
void pose_h_13(double *state, double *unused, double *out_5531667930420635084) {
  h_13(state, unused, out_5531667930420635084);
}
void pose_H_13(double *state, double *unused, double *out_5933412929404490519) {
  H_13(state, unused, out_5933412929404490519);
}
void pose_h_14(double *state, double *unused, double *out_8913575968829588963) {
  h_14(state, unused, out_8913575968829588963);
}
void pose_H_14(double *state, double *unused, double *out_6684379960411642247) {
  H_14(state, unused, out_6684379960411642247);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
