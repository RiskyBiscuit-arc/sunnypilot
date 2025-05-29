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
void err_fun(double *nom_x, double *delta_x, double *out_3898755390867715059) {
   out_3898755390867715059[0] = delta_x[0] + nom_x[0];
   out_3898755390867715059[1] = delta_x[1] + nom_x[1];
   out_3898755390867715059[2] = delta_x[2] + nom_x[2];
   out_3898755390867715059[3] = delta_x[3] + nom_x[3];
   out_3898755390867715059[4] = delta_x[4] + nom_x[4];
   out_3898755390867715059[5] = delta_x[5] + nom_x[5];
   out_3898755390867715059[6] = delta_x[6] + nom_x[6];
   out_3898755390867715059[7] = delta_x[7] + nom_x[7];
   out_3898755390867715059[8] = delta_x[8] + nom_x[8];
   out_3898755390867715059[9] = delta_x[9] + nom_x[9];
   out_3898755390867715059[10] = delta_x[10] + nom_x[10];
   out_3898755390867715059[11] = delta_x[11] + nom_x[11];
   out_3898755390867715059[12] = delta_x[12] + nom_x[12];
   out_3898755390867715059[13] = delta_x[13] + nom_x[13];
   out_3898755390867715059[14] = delta_x[14] + nom_x[14];
   out_3898755390867715059[15] = delta_x[15] + nom_x[15];
   out_3898755390867715059[16] = delta_x[16] + nom_x[16];
   out_3898755390867715059[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_277612785680832411) {
   out_277612785680832411[0] = -nom_x[0] + true_x[0];
   out_277612785680832411[1] = -nom_x[1] + true_x[1];
   out_277612785680832411[2] = -nom_x[2] + true_x[2];
   out_277612785680832411[3] = -nom_x[3] + true_x[3];
   out_277612785680832411[4] = -nom_x[4] + true_x[4];
   out_277612785680832411[5] = -nom_x[5] + true_x[5];
   out_277612785680832411[6] = -nom_x[6] + true_x[6];
   out_277612785680832411[7] = -nom_x[7] + true_x[7];
   out_277612785680832411[8] = -nom_x[8] + true_x[8];
   out_277612785680832411[9] = -nom_x[9] + true_x[9];
   out_277612785680832411[10] = -nom_x[10] + true_x[10];
   out_277612785680832411[11] = -nom_x[11] + true_x[11];
   out_277612785680832411[12] = -nom_x[12] + true_x[12];
   out_277612785680832411[13] = -nom_x[13] + true_x[13];
   out_277612785680832411[14] = -nom_x[14] + true_x[14];
   out_277612785680832411[15] = -nom_x[15] + true_x[15];
   out_277612785680832411[16] = -nom_x[16] + true_x[16];
   out_277612785680832411[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4995735585886133509) {
   out_4995735585886133509[0] = 1.0;
   out_4995735585886133509[1] = 0.0;
   out_4995735585886133509[2] = 0.0;
   out_4995735585886133509[3] = 0.0;
   out_4995735585886133509[4] = 0.0;
   out_4995735585886133509[5] = 0.0;
   out_4995735585886133509[6] = 0.0;
   out_4995735585886133509[7] = 0.0;
   out_4995735585886133509[8] = 0.0;
   out_4995735585886133509[9] = 0.0;
   out_4995735585886133509[10] = 0.0;
   out_4995735585886133509[11] = 0.0;
   out_4995735585886133509[12] = 0.0;
   out_4995735585886133509[13] = 0.0;
   out_4995735585886133509[14] = 0.0;
   out_4995735585886133509[15] = 0.0;
   out_4995735585886133509[16] = 0.0;
   out_4995735585886133509[17] = 0.0;
   out_4995735585886133509[18] = 0.0;
   out_4995735585886133509[19] = 1.0;
   out_4995735585886133509[20] = 0.0;
   out_4995735585886133509[21] = 0.0;
   out_4995735585886133509[22] = 0.0;
   out_4995735585886133509[23] = 0.0;
   out_4995735585886133509[24] = 0.0;
   out_4995735585886133509[25] = 0.0;
   out_4995735585886133509[26] = 0.0;
   out_4995735585886133509[27] = 0.0;
   out_4995735585886133509[28] = 0.0;
   out_4995735585886133509[29] = 0.0;
   out_4995735585886133509[30] = 0.0;
   out_4995735585886133509[31] = 0.0;
   out_4995735585886133509[32] = 0.0;
   out_4995735585886133509[33] = 0.0;
   out_4995735585886133509[34] = 0.0;
   out_4995735585886133509[35] = 0.0;
   out_4995735585886133509[36] = 0.0;
   out_4995735585886133509[37] = 0.0;
   out_4995735585886133509[38] = 1.0;
   out_4995735585886133509[39] = 0.0;
   out_4995735585886133509[40] = 0.0;
   out_4995735585886133509[41] = 0.0;
   out_4995735585886133509[42] = 0.0;
   out_4995735585886133509[43] = 0.0;
   out_4995735585886133509[44] = 0.0;
   out_4995735585886133509[45] = 0.0;
   out_4995735585886133509[46] = 0.0;
   out_4995735585886133509[47] = 0.0;
   out_4995735585886133509[48] = 0.0;
   out_4995735585886133509[49] = 0.0;
   out_4995735585886133509[50] = 0.0;
   out_4995735585886133509[51] = 0.0;
   out_4995735585886133509[52] = 0.0;
   out_4995735585886133509[53] = 0.0;
   out_4995735585886133509[54] = 0.0;
   out_4995735585886133509[55] = 0.0;
   out_4995735585886133509[56] = 0.0;
   out_4995735585886133509[57] = 1.0;
   out_4995735585886133509[58] = 0.0;
   out_4995735585886133509[59] = 0.0;
   out_4995735585886133509[60] = 0.0;
   out_4995735585886133509[61] = 0.0;
   out_4995735585886133509[62] = 0.0;
   out_4995735585886133509[63] = 0.0;
   out_4995735585886133509[64] = 0.0;
   out_4995735585886133509[65] = 0.0;
   out_4995735585886133509[66] = 0.0;
   out_4995735585886133509[67] = 0.0;
   out_4995735585886133509[68] = 0.0;
   out_4995735585886133509[69] = 0.0;
   out_4995735585886133509[70] = 0.0;
   out_4995735585886133509[71] = 0.0;
   out_4995735585886133509[72] = 0.0;
   out_4995735585886133509[73] = 0.0;
   out_4995735585886133509[74] = 0.0;
   out_4995735585886133509[75] = 0.0;
   out_4995735585886133509[76] = 1.0;
   out_4995735585886133509[77] = 0.0;
   out_4995735585886133509[78] = 0.0;
   out_4995735585886133509[79] = 0.0;
   out_4995735585886133509[80] = 0.0;
   out_4995735585886133509[81] = 0.0;
   out_4995735585886133509[82] = 0.0;
   out_4995735585886133509[83] = 0.0;
   out_4995735585886133509[84] = 0.0;
   out_4995735585886133509[85] = 0.0;
   out_4995735585886133509[86] = 0.0;
   out_4995735585886133509[87] = 0.0;
   out_4995735585886133509[88] = 0.0;
   out_4995735585886133509[89] = 0.0;
   out_4995735585886133509[90] = 0.0;
   out_4995735585886133509[91] = 0.0;
   out_4995735585886133509[92] = 0.0;
   out_4995735585886133509[93] = 0.0;
   out_4995735585886133509[94] = 0.0;
   out_4995735585886133509[95] = 1.0;
   out_4995735585886133509[96] = 0.0;
   out_4995735585886133509[97] = 0.0;
   out_4995735585886133509[98] = 0.0;
   out_4995735585886133509[99] = 0.0;
   out_4995735585886133509[100] = 0.0;
   out_4995735585886133509[101] = 0.0;
   out_4995735585886133509[102] = 0.0;
   out_4995735585886133509[103] = 0.0;
   out_4995735585886133509[104] = 0.0;
   out_4995735585886133509[105] = 0.0;
   out_4995735585886133509[106] = 0.0;
   out_4995735585886133509[107] = 0.0;
   out_4995735585886133509[108] = 0.0;
   out_4995735585886133509[109] = 0.0;
   out_4995735585886133509[110] = 0.0;
   out_4995735585886133509[111] = 0.0;
   out_4995735585886133509[112] = 0.0;
   out_4995735585886133509[113] = 0.0;
   out_4995735585886133509[114] = 1.0;
   out_4995735585886133509[115] = 0.0;
   out_4995735585886133509[116] = 0.0;
   out_4995735585886133509[117] = 0.0;
   out_4995735585886133509[118] = 0.0;
   out_4995735585886133509[119] = 0.0;
   out_4995735585886133509[120] = 0.0;
   out_4995735585886133509[121] = 0.0;
   out_4995735585886133509[122] = 0.0;
   out_4995735585886133509[123] = 0.0;
   out_4995735585886133509[124] = 0.0;
   out_4995735585886133509[125] = 0.0;
   out_4995735585886133509[126] = 0.0;
   out_4995735585886133509[127] = 0.0;
   out_4995735585886133509[128] = 0.0;
   out_4995735585886133509[129] = 0.0;
   out_4995735585886133509[130] = 0.0;
   out_4995735585886133509[131] = 0.0;
   out_4995735585886133509[132] = 0.0;
   out_4995735585886133509[133] = 1.0;
   out_4995735585886133509[134] = 0.0;
   out_4995735585886133509[135] = 0.0;
   out_4995735585886133509[136] = 0.0;
   out_4995735585886133509[137] = 0.0;
   out_4995735585886133509[138] = 0.0;
   out_4995735585886133509[139] = 0.0;
   out_4995735585886133509[140] = 0.0;
   out_4995735585886133509[141] = 0.0;
   out_4995735585886133509[142] = 0.0;
   out_4995735585886133509[143] = 0.0;
   out_4995735585886133509[144] = 0.0;
   out_4995735585886133509[145] = 0.0;
   out_4995735585886133509[146] = 0.0;
   out_4995735585886133509[147] = 0.0;
   out_4995735585886133509[148] = 0.0;
   out_4995735585886133509[149] = 0.0;
   out_4995735585886133509[150] = 0.0;
   out_4995735585886133509[151] = 0.0;
   out_4995735585886133509[152] = 1.0;
   out_4995735585886133509[153] = 0.0;
   out_4995735585886133509[154] = 0.0;
   out_4995735585886133509[155] = 0.0;
   out_4995735585886133509[156] = 0.0;
   out_4995735585886133509[157] = 0.0;
   out_4995735585886133509[158] = 0.0;
   out_4995735585886133509[159] = 0.0;
   out_4995735585886133509[160] = 0.0;
   out_4995735585886133509[161] = 0.0;
   out_4995735585886133509[162] = 0.0;
   out_4995735585886133509[163] = 0.0;
   out_4995735585886133509[164] = 0.0;
   out_4995735585886133509[165] = 0.0;
   out_4995735585886133509[166] = 0.0;
   out_4995735585886133509[167] = 0.0;
   out_4995735585886133509[168] = 0.0;
   out_4995735585886133509[169] = 0.0;
   out_4995735585886133509[170] = 0.0;
   out_4995735585886133509[171] = 1.0;
   out_4995735585886133509[172] = 0.0;
   out_4995735585886133509[173] = 0.0;
   out_4995735585886133509[174] = 0.0;
   out_4995735585886133509[175] = 0.0;
   out_4995735585886133509[176] = 0.0;
   out_4995735585886133509[177] = 0.0;
   out_4995735585886133509[178] = 0.0;
   out_4995735585886133509[179] = 0.0;
   out_4995735585886133509[180] = 0.0;
   out_4995735585886133509[181] = 0.0;
   out_4995735585886133509[182] = 0.0;
   out_4995735585886133509[183] = 0.0;
   out_4995735585886133509[184] = 0.0;
   out_4995735585886133509[185] = 0.0;
   out_4995735585886133509[186] = 0.0;
   out_4995735585886133509[187] = 0.0;
   out_4995735585886133509[188] = 0.0;
   out_4995735585886133509[189] = 0.0;
   out_4995735585886133509[190] = 1.0;
   out_4995735585886133509[191] = 0.0;
   out_4995735585886133509[192] = 0.0;
   out_4995735585886133509[193] = 0.0;
   out_4995735585886133509[194] = 0.0;
   out_4995735585886133509[195] = 0.0;
   out_4995735585886133509[196] = 0.0;
   out_4995735585886133509[197] = 0.0;
   out_4995735585886133509[198] = 0.0;
   out_4995735585886133509[199] = 0.0;
   out_4995735585886133509[200] = 0.0;
   out_4995735585886133509[201] = 0.0;
   out_4995735585886133509[202] = 0.0;
   out_4995735585886133509[203] = 0.0;
   out_4995735585886133509[204] = 0.0;
   out_4995735585886133509[205] = 0.0;
   out_4995735585886133509[206] = 0.0;
   out_4995735585886133509[207] = 0.0;
   out_4995735585886133509[208] = 0.0;
   out_4995735585886133509[209] = 1.0;
   out_4995735585886133509[210] = 0.0;
   out_4995735585886133509[211] = 0.0;
   out_4995735585886133509[212] = 0.0;
   out_4995735585886133509[213] = 0.0;
   out_4995735585886133509[214] = 0.0;
   out_4995735585886133509[215] = 0.0;
   out_4995735585886133509[216] = 0.0;
   out_4995735585886133509[217] = 0.0;
   out_4995735585886133509[218] = 0.0;
   out_4995735585886133509[219] = 0.0;
   out_4995735585886133509[220] = 0.0;
   out_4995735585886133509[221] = 0.0;
   out_4995735585886133509[222] = 0.0;
   out_4995735585886133509[223] = 0.0;
   out_4995735585886133509[224] = 0.0;
   out_4995735585886133509[225] = 0.0;
   out_4995735585886133509[226] = 0.0;
   out_4995735585886133509[227] = 0.0;
   out_4995735585886133509[228] = 1.0;
   out_4995735585886133509[229] = 0.0;
   out_4995735585886133509[230] = 0.0;
   out_4995735585886133509[231] = 0.0;
   out_4995735585886133509[232] = 0.0;
   out_4995735585886133509[233] = 0.0;
   out_4995735585886133509[234] = 0.0;
   out_4995735585886133509[235] = 0.0;
   out_4995735585886133509[236] = 0.0;
   out_4995735585886133509[237] = 0.0;
   out_4995735585886133509[238] = 0.0;
   out_4995735585886133509[239] = 0.0;
   out_4995735585886133509[240] = 0.0;
   out_4995735585886133509[241] = 0.0;
   out_4995735585886133509[242] = 0.0;
   out_4995735585886133509[243] = 0.0;
   out_4995735585886133509[244] = 0.0;
   out_4995735585886133509[245] = 0.0;
   out_4995735585886133509[246] = 0.0;
   out_4995735585886133509[247] = 1.0;
   out_4995735585886133509[248] = 0.0;
   out_4995735585886133509[249] = 0.0;
   out_4995735585886133509[250] = 0.0;
   out_4995735585886133509[251] = 0.0;
   out_4995735585886133509[252] = 0.0;
   out_4995735585886133509[253] = 0.0;
   out_4995735585886133509[254] = 0.0;
   out_4995735585886133509[255] = 0.0;
   out_4995735585886133509[256] = 0.0;
   out_4995735585886133509[257] = 0.0;
   out_4995735585886133509[258] = 0.0;
   out_4995735585886133509[259] = 0.0;
   out_4995735585886133509[260] = 0.0;
   out_4995735585886133509[261] = 0.0;
   out_4995735585886133509[262] = 0.0;
   out_4995735585886133509[263] = 0.0;
   out_4995735585886133509[264] = 0.0;
   out_4995735585886133509[265] = 0.0;
   out_4995735585886133509[266] = 1.0;
   out_4995735585886133509[267] = 0.0;
   out_4995735585886133509[268] = 0.0;
   out_4995735585886133509[269] = 0.0;
   out_4995735585886133509[270] = 0.0;
   out_4995735585886133509[271] = 0.0;
   out_4995735585886133509[272] = 0.0;
   out_4995735585886133509[273] = 0.0;
   out_4995735585886133509[274] = 0.0;
   out_4995735585886133509[275] = 0.0;
   out_4995735585886133509[276] = 0.0;
   out_4995735585886133509[277] = 0.0;
   out_4995735585886133509[278] = 0.0;
   out_4995735585886133509[279] = 0.0;
   out_4995735585886133509[280] = 0.0;
   out_4995735585886133509[281] = 0.0;
   out_4995735585886133509[282] = 0.0;
   out_4995735585886133509[283] = 0.0;
   out_4995735585886133509[284] = 0.0;
   out_4995735585886133509[285] = 1.0;
   out_4995735585886133509[286] = 0.0;
   out_4995735585886133509[287] = 0.0;
   out_4995735585886133509[288] = 0.0;
   out_4995735585886133509[289] = 0.0;
   out_4995735585886133509[290] = 0.0;
   out_4995735585886133509[291] = 0.0;
   out_4995735585886133509[292] = 0.0;
   out_4995735585886133509[293] = 0.0;
   out_4995735585886133509[294] = 0.0;
   out_4995735585886133509[295] = 0.0;
   out_4995735585886133509[296] = 0.0;
   out_4995735585886133509[297] = 0.0;
   out_4995735585886133509[298] = 0.0;
   out_4995735585886133509[299] = 0.0;
   out_4995735585886133509[300] = 0.0;
   out_4995735585886133509[301] = 0.0;
   out_4995735585886133509[302] = 0.0;
   out_4995735585886133509[303] = 0.0;
   out_4995735585886133509[304] = 1.0;
   out_4995735585886133509[305] = 0.0;
   out_4995735585886133509[306] = 0.0;
   out_4995735585886133509[307] = 0.0;
   out_4995735585886133509[308] = 0.0;
   out_4995735585886133509[309] = 0.0;
   out_4995735585886133509[310] = 0.0;
   out_4995735585886133509[311] = 0.0;
   out_4995735585886133509[312] = 0.0;
   out_4995735585886133509[313] = 0.0;
   out_4995735585886133509[314] = 0.0;
   out_4995735585886133509[315] = 0.0;
   out_4995735585886133509[316] = 0.0;
   out_4995735585886133509[317] = 0.0;
   out_4995735585886133509[318] = 0.0;
   out_4995735585886133509[319] = 0.0;
   out_4995735585886133509[320] = 0.0;
   out_4995735585886133509[321] = 0.0;
   out_4995735585886133509[322] = 0.0;
   out_4995735585886133509[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2762548597287583938) {
   out_2762548597287583938[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2762548597287583938[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2762548597287583938[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2762548597287583938[3] = dt*state[12] + state[3];
   out_2762548597287583938[4] = dt*state[13] + state[4];
   out_2762548597287583938[5] = dt*state[14] + state[5];
   out_2762548597287583938[6] = state[6];
   out_2762548597287583938[7] = state[7];
   out_2762548597287583938[8] = state[8];
   out_2762548597287583938[9] = state[9];
   out_2762548597287583938[10] = state[10];
   out_2762548597287583938[11] = state[11];
   out_2762548597287583938[12] = state[12];
   out_2762548597287583938[13] = state[13];
   out_2762548597287583938[14] = state[14];
   out_2762548597287583938[15] = state[15];
   out_2762548597287583938[16] = state[16];
   out_2762548597287583938[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8703467420914203037) {
   out_8703467420914203037[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8703467420914203037[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8703467420914203037[2] = 0;
   out_8703467420914203037[3] = 0;
   out_8703467420914203037[4] = 0;
   out_8703467420914203037[5] = 0;
   out_8703467420914203037[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8703467420914203037[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8703467420914203037[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8703467420914203037[9] = 0;
   out_8703467420914203037[10] = 0;
   out_8703467420914203037[11] = 0;
   out_8703467420914203037[12] = 0;
   out_8703467420914203037[13] = 0;
   out_8703467420914203037[14] = 0;
   out_8703467420914203037[15] = 0;
   out_8703467420914203037[16] = 0;
   out_8703467420914203037[17] = 0;
   out_8703467420914203037[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8703467420914203037[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8703467420914203037[20] = 0;
   out_8703467420914203037[21] = 0;
   out_8703467420914203037[22] = 0;
   out_8703467420914203037[23] = 0;
   out_8703467420914203037[24] = 0;
   out_8703467420914203037[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8703467420914203037[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8703467420914203037[27] = 0;
   out_8703467420914203037[28] = 0;
   out_8703467420914203037[29] = 0;
   out_8703467420914203037[30] = 0;
   out_8703467420914203037[31] = 0;
   out_8703467420914203037[32] = 0;
   out_8703467420914203037[33] = 0;
   out_8703467420914203037[34] = 0;
   out_8703467420914203037[35] = 0;
   out_8703467420914203037[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8703467420914203037[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8703467420914203037[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8703467420914203037[39] = 0;
   out_8703467420914203037[40] = 0;
   out_8703467420914203037[41] = 0;
   out_8703467420914203037[42] = 0;
   out_8703467420914203037[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8703467420914203037[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8703467420914203037[45] = 0;
   out_8703467420914203037[46] = 0;
   out_8703467420914203037[47] = 0;
   out_8703467420914203037[48] = 0;
   out_8703467420914203037[49] = 0;
   out_8703467420914203037[50] = 0;
   out_8703467420914203037[51] = 0;
   out_8703467420914203037[52] = 0;
   out_8703467420914203037[53] = 0;
   out_8703467420914203037[54] = 0;
   out_8703467420914203037[55] = 0;
   out_8703467420914203037[56] = 0;
   out_8703467420914203037[57] = 1;
   out_8703467420914203037[58] = 0;
   out_8703467420914203037[59] = 0;
   out_8703467420914203037[60] = 0;
   out_8703467420914203037[61] = 0;
   out_8703467420914203037[62] = 0;
   out_8703467420914203037[63] = 0;
   out_8703467420914203037[64] = 0;
   out_8703467420914203037[65] = 0;
   out_8703467420914203037[66] = dt;
   out_8703467420914203037[67] = 0;
   out_8703467420914203037[68] = 0;
   out_8703467420914203037[69] = 0;
   out_8703467420914203037[70] = 0;
   out_8703467420914203037[71] = 0;
   out_8703467420914203037[72] = 0;
   out_8703467420914203037[73] = 0;
   out_8703467420914203037[74] = 0;
   out_8703467420914203037[75] = 0;
   out_8703467420914203037[76] = 1;
   out_8703467420914203037[77] = 0;
   out_8703467420914203037[78] = 0;
   out_8703467420914203037[79] = 0;
   out_8703467420914203037[80] = 0;
   out_8703467420914203037[81] = 0;
   out_8703467420914203037[82] = 0;
   out_8703467420914203037[83] = 0;
   out_8703467420914203037[84] = 0;
   out_8703467420914203037[85] = dt;
   out_8703467420914203037[86] = 0;
   out_8703467420914203037[87] = 0;
   out_8703467420914203037[88] = 0;
   out_8703467420914203037[89] = 0;
   out_8703467420914203037[90] = 0;
   out_8703467420914203037[91] = 0;
   out_8703467420914203037[92] = 0;
   out_8703467420914203037[93] = 0;
   out_8703467420914203037[94] = 0;
   out_8703467420914203037[95] = 1;
   out_8703467420914203037[96] = 0;
   out_8703467420914203037[97] = 0;
   out_8703467420914203037[98] = 0;
   out_8703467420914203037[99] = 0;
   out_8703467420914203037[100] = 0;
   out_8703467420914203037[101] = 0;
   out_8703467420914203037[102] = 0;
   out_8703467420914203037[103] = 0;
   out_8703467420914203037[104] = dt;
   out_8703467420914203037[105] = 0;
   out_8703467420914203037[106] = 0;
   out_8703467420914203037[107] = 0;
   out_8703467420914203037[108] = 0;
   out_8703467420914203037[109] = 0;
   out_8703467420914203037[110] = 0;
   out_8703467420914203037[111] = 0;
   out_8703467420914203037[112] = 0;
   out_8703467420914203037[113] = 0;
   out_8703467420914203037[114] = 1;
   out_8703467420914203037[115] = 0;
   out_8703467420914203037[116] = 0;
   out_8703467420914203037[117] = 0;
   out_8703467420914203037[118] = 0;
   out_8703467420914203037[119] = 0;
   out_8703467420914203037[120] = 0;
   out_8703467420914203037[121] = 0;
   out_8703467420914203037[122] = 0;
   out_8703467420914203037[123] = 0;
   out_8703467420914203037[124] = 0;
   out_8703467420914203037[125] = 0;
   out_8703467420914203037[126] = 0;
   out_8703467420914203037[127] = 0;
   out_8703467420914203037[128] = 0;
   out_8703467420914203037[129] = 0;
   out_8703467420914203037[130] = 0;
   out_8703467420914203037[131] = 0;
   out_8703467420914203037[132] = 0;
   out_8703467420914203037[133] = 1;
   out_8703467420914203037[134] = 0;
   out_8703467420914203037[135] = 0;
   out_8703467420914203037[136] = 0;
   out_8703467420914203037[137] = 0;
   out_8703467420914203037[138] = 0;
   out_8703467420914203037[139] = 0;
   out_8703467420914203037[140] = 0;
   out_8703467420914203037[141] = 0;
   out_8703467420914203037[142] = 0;
   out_8703467420914203037[143] = 0;
   out_8703467420914203037[144] = 0;
   out_8703467420914203037[145] = 0;
   out_8703467420914203037[146] = 0;
   out_8703467420914203037[147] = 0;
   out_8703467420914203037[148] = 0;
   out_8703467420914203037[149] = 0;
   out_8703467420914203037[150] = 0;
   out_8703467420914203037[151] = 0;
   out_8703467420914203037[152] = 1;
   out_8703467420914203037[153] = 0;
   out_8703467420914203037[154] = 0;
   out_8703467420914203037[155] = 0;
   out_8703467420914203037[156] = 0;
   out_8703467420914203037[157] = 0;
   out_8703467420914203037[158] = 0;
   out_8703467420914203037[159] = 0;
   out_8703467420914203037[160] = 0;
   out_8703467420914203037[161] = 0;
   out_8703467420914203037[162] = 0;
   out_8703467420914203037[163] = 0;
   out_8703467420914203037[164] = 0;
   out_8703467420914203037[165] = 0;
   out_8703467420914203037[166] = 0;
   out_8703467420914203037[167] = 0;
   out_8703467420914203037[168] = 0;
   out_8703467420914203037[169] = 0;
   out_8703467420914203037[170] = 0;
   out_8703467420914203037[171] = 1;
   out_8703467420914203037[172] = 0;
   out_8703467420914203037[173] = 0;
   out_8703467420914203037[174] = 0;
   out_8703467420914203037[175] = 0;
   out_8703467420914203037[176] = 0;
   out_8703467420914203037[177] = 0;
   out_8703467420914203037[178] = 0;
   out_8703467420914203037[179] = 0;
   out_8703467420914203037[180] = 0;
   out_8703467420914203037[181] = 0;
   out_8703467420914203037[182] = 0;
   out_8703467420914203037[183] = 0;
   out_8703467420914203037[184] = 0;
   out_8703467420914203037[185] = 0;
   out_8703467420914203037[186] = 0;
   out_8703467420914203037[187] = 0;
   out_8703467420914203037[188] = 0;
   out_8703467420914203037[189] = 0;
   out_8703467420914203037[190] = 1;
   out_8703467420914203037[191] = 0;
   out_8703467420914203037[192] = 0;
   out_8703467420914203037[193] = 0;
   out_8703467420914203037[194] = 0;
   out_8703467420914203037[195] = 0;
   out_8703467420914203037[196] = 0;
   out_8703467420914203037[197] = 0;
   out_8703467420914203037[198] = 0;
   out_8703467420914203037[199] = 0;
   out_8703467420914203037[200] = 0;
   out_8703467420914203037[201] = 0;
   out_8703467420914203037[202] = 0;
   out_8703467420914203037[203] = 0;
   out_8703467420914203037[204] = 0;
   out_8703467420914203037[205] = 0;
   out_8703467420914203037[206] = 0;
   out_8703467420914203037[207] = 0;
   out_8703467420914203037[208] = 0;
   out_8703467420914203037[209] = 1;
   out_8703467420914203037[210] = 0;
   out_8703467420914203037[211] = 0;
   out_8703467420914203037[212] = 0;
   out_8703467420914203037[213] = 0;
   out_8703467420914203037[214] = 0;
   out_8703467420914203037[215] = 0;
   out_8703467420914203037[216] = 0;
   out_8703467420914203037[217] = 0;
   out_8703467420914203037[218] = 0;
   out_8703467420914203037[219] = 0;
   out_8703467420914203037[220] = 0;
   out_8703467420914203037[221] = 0;
   out_8703467420914203037[222] = 0;
   out_8703467420914203037[223] = 0;
   out_8703467420914203037[224] = 0;
   out_8703467420914203037[225] = 0;
   out_8703467420914203037[226] = 0;
   out_8703467420914203037[227] = 0;
   out_8703467420914203037[228] = 1;
   out_8703467420914203037[229] = 0;
   out_8703467420914203037[230] = 0;
   out_8703467420914203037[231] = 0;
   out_8703467420914203037[232] = 0;
   out_8703467420914203037[233] = 0;
   out_8703467420914203037[234] = 0;
   out_8703467420914203037[235] = 0;
   out_8703467420914203037[236] = 0;
   out_8703467420914203037[237] = 0;
   out_8703467420914203037[238] = 0;
   out_8703467420914203037[239] = 0;
   out_8703467420914203037[240] = 0;
   out_8703467420914203037[241] = 0;
   out_8703467420914203037[242] = 0;
   out_8703467420914203037[243] = 0;
   out_8703467420914203037[244] = 0;
   out_8703467420914203037[245] = 0;
   out_8703467420914203037[246] = 0;
   out_8703467420914203037[247] = 1;
   out_8703467420914203037[248] = 0;
   out_8703467420914203037[249] = 0;
   out_8703467420914203037[250] = 0;
   out_8703467420914203037[251] = 0;
   out_8703467420914203037[252] = 0;
   out_8703467420914203037[253] = 0;
   out_8703467420914203037[254] = 0;
   out_8703467420914203037[255] = 0;
   out_8703467420914203037[256] = 0;
   out_8703467420914203037[257] = 0;
   out_8703467420914203037[258] = 0;
   out_8703467420914203037[259] = 0;
   out_8703467420914203037[260] = 0;
   out_8703467420914203037[261] = 0;
   out_8703467420914203037[262] = 0;
   out_8703467420914203037[263] = 0;
   out_8703467420914203037[264] = 0;
   out_8703467420914203037[265] = 0;
   out_8703467420914203037[266] = 1;
   out_8703467420914203037[267] = 0;
   out_8703467420914203037[268] = 0;
   out_8703467420914203037[269] = 0;
   out_8703467420914203037[270] = 0;
   out_8703467420914203037[271] = 0;
   out_8703467420914203037[272] = 0;
   out_8703467420914203037[273] = 0;
   out_8703467420914203037[274] = 0;
   out_8703467420914203037[275] = 0;
   out_8703467420914203037[276] = 0;
   out_8703467420914203037[277] = 0;
   out_8703467420914203037[278] = 0;
   out_8703467420914203037[279] = 0;
   out_8703467420914203037[280] = 0;
   out_8703467420914203037[281] = 0;
   out_8703467420914203037[282] = 0;
   out_8703467420914203037[283] = 0;
   out_8703467420914203037[284] = 0;
   out_8703467420914203037[285] = 1;
   out_8703467420914203037[286] = 0;
   out_8703467420914203037[287] = 0;
   out_8703467420914203037[288] = 0;
   out_8703467420914203037[289] = 0;
   out_8703467420914203037[290] = 0;
   out_8703467420914203037[291] = 0;
   out_8703467420914203037[292] = 0;
   out_8703467420914203037[293] = 0;
   out_8703467420914203037[294] = 0;
   out_8703467420914203037[295] = 0;
   out_8703467420914203037[296] = 0;
   out_8703467420914203037[297] = 0;
   out_8703467420914203037[298] = 0;
   out_8703467420914203037[299] = 0;
   out_8703467420914203037[300] = 0;
   out_8703467420914203037[301] = 0;
   out_8703467420914203037[302] = 0;
   out_8703467420914203037[303] = 0;
   out_8703467420914203037[304] = 1;
   out_8703467420914203037[305] = 0;
   out_8703467420914203037[306] = 0;
   out_8703467420914203037[307] = 0;
   out_8703467420914203037[308] = 0;
   out_8703467420914203037[309] = 0;
   out_8703467420914203037[310] = 0;
   out_8703467420914203037[311] = 0;
   out_8703467420914203037[312] = 0;
   out_8703467420914203037[313] = 0;
   out_8703467420914203037[314] = 0;
   out_8703467420914203037[315] = 0;
   out_8703467420914203037[316] = 0;
   out_8703467420914203037[317] = 0;
   out_8703467420914203037[318] = 0;
   out_8703467420914203037[319] = 0;
   out_8703467420914203037[320] = 0;
   out_8703467420914203037[321] = 0;
   out_8703467420914203037[322] = 0;
   out_8703467420914203037[323] = 1;
}
void h_4(double *state, double *unused, double *out_5980686185248558188) {
   out_5980686185248558188[0] = state[6] + state[9];
   out_5980686185248558188[1] = state[7] + state[10];
   out_5980686185248558188[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1795325684784663485) {
   out_1795325684784663485[0] = 0;
   out_1795325684784663485[1] = 0;
   out_1795325684784663485[2] = 0;
   out_1795325684784663485[3] = 0;
   out_1795325684784663485[4] = 0;
   out_1795325684784663485[5] = 0;
   out_1795325684784663485[6] = 1;
   out_1795325684784663485[7] = 0;
   out_1795325684784663485[8] = 0;
   out_1795325684784663485[9] = 1;
   out_1795325684784663485[10] = 0;
   out_1795325684784663485[11] = 0;
   out_1795325684784663485[12] = 0;
   out_1795325684784663485[13] = 0;
   out_1795325684784663485[14] = 0;
   out_1795325684784663485[15] = 0;
   out_1795325684784663485[16] = 0;
   out_1795325684784663485[17] = 0;
   out_1795325684784663485[18] = 0;
   out_1795325684784663485[19] = 0;
   out_1795325684784663485[20] = 0;
   out_1795325684784663485[21] = 0;
   out_1795325684784663485[22] = 0;
   out_1795325684784663485[23] = 0;
   out_1795325684784663485[24] = 0;
   out_1795325684784663485[25] = 1;
   out_1795325684784663485[26] = 0;
   out_1795325684784663485[27] = 0;
   out_1795325684784663485[28] = 1;
   out_1795325684784663485[29] = 0;
   out_1795325684784663485[30] = 0;
   out_1795325684784663485[31] = 0;
   out_1795325684784663485[32] = 0;
   out_1795325684784663485[33] = 0;
   out_1795325684784663485[34] = 0;
   out_1795325684784663485[35] = 0;
   out_1795325684784663485[36] = 0;
   out_1795325684784663485[37] = 0;
   out_1795325684784663485[38] = 0;
   out_1795325684784663485[39] = 0;
   out_1795325684784663485[40] = 0;
   out_1795325684784663485[41] = 0;
   out_1795325684784663485[42] = 0;
   out_1795325684784663485[43] = 0;
   out_1795325684784663485[44] = 1;
   out_1795325684784663485[45] = 0;
   out_1795325684784663485[46] = 0;
   out_1795325684784663485[47] = 1;
   out_1795325684784663485[48] = 0;
   out_1795325684784663485[49] = 0;
   out_1795325684784663485[50] = 0;
   out_1795325684784663485[51] = 0;
   out_1795325684784663485[52] = 0;
   out_1795325684784663485[53] = 0;
}
void h_10(double *state, double *unused, double *out_1442181013276762710) {
   out_1442181013276762710[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1442181013276762710[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1442181013276762710[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7595311124708499208) {
   out_7595311124708499208[0] = 0;
   out_7595311124708499208[1] = 9.8100000000000005*cos(state[1]);
   out_7595311124708499208[2] = 0;
   out_7595311124708499208[3] = 0;
   out_7595311124708499208[4] = -state[8];
   out_7595311124708499208[5] = state[7];
   out_7595311124708499208[6] = 0;
   out_7595311124708499208[7] = state[5];
   out_7595311124708499208[8] = -state[4];
   out_7595311124708499208[9] = 0;
   out_7595311124708499208[10] = 0;
   out_7595311124708499208[11] = 0;
   out_7595311124708499208[12] = 1;
   out_7595311124708499208[13] = 0;
   out_7595311124708499208[14] = 0;
   out_7595311124708499208[15] = 1;
   out_7595311124708499208[16] = 0;
   out_7595311124708499208[17] = 0;
   out_7595311124708499208[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7595311124708499208[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7595311124708499208[20] = 0;
   out_7595311124708499208[21] = state[8];
   out_7595311124708499208[22] = 0;
   out_7595311124708499208[23] = -state[6];
   out_7595311124708499208[24] = -state[5];
   out_7595311124708499208[25] = 0;
   out_7595311124708499208[26] = state[3];
   out_7595311124708499208[27] = 0;
   out_7595311124708499208[28] = 0;
   out_7595311124708499208[29] = 0;
   out_7595311124708499208[30] = 0;
   out_7595311124708499208[31] = 1;
   out_7595311124708499208[32] = 0;
   out_7595311124708499208[33] = 0;
   out_7595311124708499208[34] = 1;
   out_7595311124708499208[35] = 0;
   out_7595311124708499208[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7595311124708499208[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7595311124708499208[38] = 0;
   out_7595311124708499208[39] = -state[7];
   out_7595311124708499208[40] = state[6];
   out_7595311124708499208[41] = 0;
   out_7595311124708499208[42] = state[4];
   out_7595311124708499208[43] = -state[3];
   out_7595311124708499208[44] = 0;
   out_7595311124708499208[45] = 0;
   out_7595311124708499208[46] = 0;
   out_7595311124708499208[47] = 0;
   out_7595311124708499208[48] = 0;
   out_7595311124708499208[49] = 0;
   out_7595311124708499208[50] = 1;
   out_7595311124708499208[51] = 0;
   out_7595311124708499208[52] = 0;
   out_7595311124708499208[53] = 1;
}
void h_13(double *state, double *unused, double *out_417783278623543215) {
   out_417783278623543215[0] = state[3];
   out_417783278623543215[1] = state[4];
   out_417783278623543215[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2359927604466507589) {
   out_2359927604466507589[0] = 0;
   out_2359927604466507589[1] = 0;
   out_2359927604466507589[2] = 0;
   out_2359927604466507589[3] = 1;
   out_2359927604466507589[4] = 0;
   out_2359927604466507589[5] = 0;
   out_2359927604466507589[6] = 0;
   out_2359927604466507589[7] = 0;
   out_2359927604466507589[8] = 0;
   out_2359927604466507589[9] = 0;
   out_2359927604466507589[10] = 0;
   out_2359927604466507589[11] = 0;
   out_2359927604466507589[12] = 0;
   out_2359927604466507589[13] = 0;
   out_2359927604466507589[14] = 0;
   out_2359927604466507589[15] = 0;
   out_2359927604466507589[16] = 0;
   out_2359927604466507589[17] = 0;
   out_2359927604466507589[18] = 0;
   out_2359927604466507589[19] = 0;
   out_2359927604466507589[20] = 0;
   out_2359927604466507589[21] = 0;
   out_2359927604466507589[22] = 1;
   out_2359927604466507589[23] = 0;
   out_2359927604466507589[24] = 0;
   out_2359927604466507589[25] = 0;
   out_2359927604466507589[26] = 0;
   out_2359927604466507589[27] = 0;
   out_2359927604466507589[28] = 0;
   out_2359927604466507589[29] = 0;
   out_2359927604466507589[30] = 0;
   out_2359927604466507589[31] = 0;
   out_2359927604466507589[32] = 0;
   out_2359927604466507589[33] = 0;
   out_2359927604466507589[34] = 0;
   out_2359927604466507589[35] = 0;
   out_2359927604466507589[36] = 0;
   out_2359927604466507589[37] = 0;
   out_2359927604466507589[38] = 0;
   out_2359927604466507589[39] = 0;
   out_2359927604466507589[40] = 0;
   out_2359927604466507589[41] = 1;
   out_2359927604466507589[42] = 0;
   out_2359927604466507589[43] = 0;
   out_2359927604466507589[44] = 0;
   out_2359927604466507589[45] = 0;
   out_2359927604466507589[46] = 0;
   out_2359927604466507589[47] = 0;
   out_2359927604466507589[48] = 0;
   out_2359927604466507589[49] = 0;
   out_2359927604466507589[50] = 0;
   out_2359927604466507589[51] = 0;
   out_2359927604466507589[52] = 0;
   out_2359927604466507589[53] = 0;
}
void h_14(double *state, double *unused, double *out_7977669001299524575) {
   out_7977669001299524575[0] = state[6];
   out_7977669001299524575[1] = state[7];
   out_7977669001299524575[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1287462747510708811) {
   out_1287462747510708811[0] = 0;
   out_1287462747510708811[1] = 0;
   out_1287462747510708811[2] = 0;
   out_1287462747510708811[3] = 0;
   out_1287462747510708811[4] = 0;
   out_1287462747510708811[5] = 0;
   out_1287462747510708811[6] = 1;
   out_1287462747510708811[7] = 0;
   out_1287462747510708811[8] = 0;
   out_1287462747510708811[9] = 0;
   out_1287462747510708811[10] = 0;
   out_1287462747510708811[11] = 0;
   out_1287462747510708811[12] = 0;
   out_1287462747510708811[13] = 0;
   out_1287462747510708811[14] = 0;
   out_1287462747510708811[15] = 0;
   out_1287462747510708811[16] = 0;
   out_1287462747510708811[17] = 0;
   out_1287462747510708811[18] = 0;
   out_1287462747510708811[19] = 0;
   out_1287462747510708811[20] = 0;
   out_1287462747510708811[21] = 0;
   out_1287462747510708811[22] = 0;
   out_1287462747510708811[23] = 0;
   out_1287462747510708811[24] = 0;
   out_1287462747510708811[25] = 1;
   out_1287462747510708811[26] = 0;
   out_1287462747510708811[27] = 0;
   out_1287462747510708811[28] = 0;
   out_1287462747510708811[29] = 0;
   out_1287462747510708811[30] = 0;
   out_1287462747510708811[31] = 0;
   out_1287462747510708811[32] = 0;
   out_1287462747510708811[33] = 0;
   out_1287462747510708811[34] = 0;
   out_1287462747510708811[35] = 0;
   out_1287462747510708811[36] = 0;
   out_1287462747510708811[37] = 0;
   out_1287462747510708811[38] = 0;
   out_1287462747510708811[39] = 0;
   out_1287462747510708811[40] = 0;
   out_1287462747510708811[41] = 0;
   out_1287462747510708811[42] = 0;
   out_1287462747510708811[43] = 0;
   out_1287462747510708811[44] = 1;
   out_1287462747510708811[45] = 0;
   out_1287462747510708811[46] = 0;
   out_1287462747510708811[47] = 0;
   out_1287462747510708811[48] = 0;
   out_1287462747510708811[49] = 0;
   out_1287462747510708811[50] = 0;
   out_1287462747510708811[51] = 0;
   out_1287462747510708811[52] = 0;
   out_1287462747510708811[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3898755390867715059) {
  err_fun(nom_x, delta_x, out_3898755390867715059);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_277612785680832411) {
  inv_err_fun(nom_x, true_x, out_277612785680832411);
}
void pose_H_mod_fun(double *state, double *out_4995735585886133509) {
  H_mod_fun(state, out_4995735585886133509);
}
void pose_f_fun(double *state, double dt, double *out_2762548597287583938) {
  f_fun(state,  dt, out_2762548597287583938);
}
void pose_F_fun(double *state, double dt, double *out_8703467420914203037) {
  F_fun(state,  dt, out_8703467420914203037);
}
void pose_h_4(double *state, double *unused, double *out_5980686185248558188) {
  h_4(state, unused, out_5980686185248558188);
}
void pose_H_4(double *state, double *unused, double *out_1795325684784663485) {
  H_4(state, unused, out_1795325684784663485);
}
void pose_h_10(double *state, double *unused, double *out_1442181013276762710) {
  h_10(state, unused, out_1442181013276762710);
}
void pose_H_10(double *state, double *unused, double *out_7595311124708499208) {
  H_10(state, unused, out_7595311124708499208);
}
void pose_h_13(double *state, double *unused, double *out_417783278623543215) {
  h_13(state, unused, out_417783278623543215);
}
void pose_H_13(double *state, double *unused, double *out_2359927604466507589) {
  H_13(state, unused, out_2359927604466507589);
}
void pose_h_14(double *state, double *unused, double *out_7977669001299524575) {
  h_14(state, unused, out_7977669001299524575);
}
void pose_H_14(double *state, double *unused, double *out_1287462747510708811) {
  H_14(state, unused, out_1287462747510708811);
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
