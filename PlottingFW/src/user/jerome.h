// input data files. make sure to edit the other strings accordingly!

#include "../core/LmBackground.h"

TString name[] = {
  "./input/LMEE_1.root", //0
  "./input/LMEE_2.root", //1
  "./input/LMEE_3.root", //2
  "./input/LMEE_4.root", //3
  "./input/LMEE_5.root", //4
  "./input/LMEE_6.root", //5
  "./input/LMEE_7.root", //6
  "./input/LMEE_8.root", //7
  "./input/LMEE_9.root", //8
  "./input/LMEE_10.root", //9
  "./input/LMEE_11.root", //10
  "./input/LMEE_12.root", //11
  "./input/LMEE_13.root", //12
  "./input/LMEE_14.root", //13
  "./input/LMEE_15.root", //14
  "./input/LMEE_16.root", //15
  "./input/LMEE_17.root", //16
  "./input/LMEE_18.root", //17
  "./input/LMEE_19.root", //18
  "./input/LMEE_20.root", //19
  "./input/LMEE_21.root", //20
  "./input/LMEE_22.root", //21
  "./input/LMEE_23.root", //22
  "./input/LMEE_2016-10-11_0203.root", //23
  "./input/LMEE_2016-10-11_0207.root", //24
  "./input/LMEE_2016-10-11_1253.root", //25

  "./input/LMEE_2016-10-12_1633.root", //26
  "./input/LMEE_2016-10-13_0159.root", //27


  "./input/LMEE_2016-10-29_2239.root", //28
  "./input/LMEE_2016-10-29_2244.root", //29
  "./input/LMEE_2016-10-30_1106.root", //30
  "./input/LMEE_2016-10-30_1109.root", //31
  "./input/LMEE_2016-11-02_0212.root", //32

  "./input/LMEE_2016-11-09_2338.root", //33
  "./input/LMEE_2016-11-11_0226.root", //34
  "./input/LMEE_2016-11-11_1359.root", //35
  "./input/LMEE_2016-11-14_0150.root", //36

  "./input/LMEE_2016-11-17_1602.root", //37
  "./input/LMEE_2016-11-19_0254.root", //38

  "./input/LMEE_2016-11-21_0035.root", //39
  "./input/LMEE_2016-11-21_1306.root", //40
  "./input/LMEE_2016-11-24_0136.root", //41

  "./input/LMEE_2016-11-24_1340.root", //42 ref
  "./input/LMEE_2016-11-25_1826.root", //43
  "./input/LMEE_2016-11-26_0217.root", //44
  "./input/LMEE_2016-11-28_1120.root", //45

  "./input/LMEE_2016-12-04_2311.root", //46
  "./input/LMEE_2016-12-05_0144.root", //47
  "./input/LMEE_2016-12-05_0710.root", //48
  "./input/LMEE_2016-12-05_0824.root", //49


  "./input/LMEE_2016-12-08_1040.root", //50
  "./input/LMEE_2016-12-12_0118.root", //51
  "./input/LMEE_2016-12-18_1609.root", //52
  "./input/LMEE_2016-12-12_1436.root", //53

  "./input/LMEE_2016-12-19_1850.root", //54
  "./input/LMEE_2016-12-21_0926.root", //55
  "./input/LMEE_2016-12-21_0930.root", //56
  "./input/LMEE_2016-12-24_0954.root", //57
  "./input/LMEE_2016-12-26_0144.root", //58

  "./input/LMEE_2016-12-27_1714.root", //59
  "./input/LMEE_2017-01-03_1821.root", //60
  "./input/LMEE_2017-01-04_1935.root", //61
  "./input/LMEE_2017-01-05_0019.root", //62

  "./input/LMEE_2017-01-11_0156.root", //63
  "./input/LMEE_2017-01-11_0158.root", //64

  "./input/LMEE_2017-01-12_0130.root", //65
  "./input/LMEE_2017-01-11_1807.root", //66

  "./input/LMEE_2017-01-13_1733.root",
  "./input/LMEE_2017-01-16_1653.root",
  "./input/LMEE_2017-01-16_1656.root",

  "./input/LMEE_2017-01-24_1150.root",  //70
  "./input/LMEE_2017-01-27_2230.root",

  "./input/LMEE_2017-02-21_2133.root",
  "./input/LMEE_2017-02-23_0202.root",
  "./input/LMEE_2017-02-28_1630.root",
  "./input/LMEE_2017-03-01_0250.root",  //75
  "./input/LMEE_2017-03-01_1631.root",
  "./input/LMEE_2017-03-02_1327.root",
  "./input/LMEE_2017-03-09_1845.root",
  "./input/LMEE_2017-03-10_0223.root",
  "./input/LMEE_2017-03-10_1245.root",  //80
  "./input/LMEE_2017-03-10_1526.root",

  "./input/LMEE_2017-03-15_1701.root",
  "./input/LMEE_2017-03-16_0202.root",
  "./input/LMEE_2017-03-16_1041.root",
  "./input/LMEE_2017-03-16_1621.root",  //85

  "./input/LMEE_LEGO623.root",
  "./input/LMEE_2017-03-17_0014.root",
  "./input/LMEE_LEGO624.root",
  "./input/LMEE_2017-03-22_0018.root",
  "./input/LMEE_LEGO627.root",         //90
  "./input/LMEE_LEGO628.root",

  "./input/LMEE_2017-04-03_1837.root",
  "./input/LMEE_LEGO661.root",
  "./input/LMEE_LEGO662.root",
  "./input/LMEE_LEGO668.root",         //95
  "./input/LMEE_2017-05-08_1300.root",

  "./input/LMEE_LEGO710.root",
  "./input/LMEE_LEGO735.root",


  "./input/data/LMEE_LEGO759.root",
  "./input/data/LMEE_LEGO804_LHC16g.root",//100
  "./input/data/LMEE_LEGO805_LHC16f.root",
  "./input/data/LMEE_LEGO806_LHC17g.root",

  "./input/data/LMEE_LEGO812_LHC17g.root",
  "./input/data/LMEE_LEGO813_LHC16f.root",
  "./input/data/LMEE_LEGO814_LHC16g.root",

  "./input/data/LMEE_LEGO815_LHC17g.root",

  "./input/data/LMEE_LEGO821_LHC16f.root",
  "./input/data/LMEE_LEGO822_LHC17g.root",

  "./input/data/LMEE_LEGO860_LHC16f.root",
  "./input/data/LMEE_LEGO861_LHC16g.root",//110

  "./input/data/LMEE_LEGO928_LHC16f.root",

  "./input/data/LMEE_LEGO885_LHC16f.root",
  "./input/data/LMEE_LEGO939_LHC17g.root",

  "./input/data/LMEE_LEGO999_LHC16f.root",
  "./input/data/LMEE_LEGO998_LHC17g.root",

  "./input/data/LMEE_NominalField.root",  //116
  "./input/data/LMEE_LEGO1022_LHC16p.root", //117

  "./input/data/LMEE_LEGO1046_LHC16f.root", //118
  "./input/data/LMEE_LEGO1047_LHC17g.root", //119
  "./input/data/LMEE_systematics_16n17_75MeV_v2.root", //120
  "./input/data/LMEE_systematics_16n17_200MeV_v2.root", //121
  "./input/data/LMEE_FullData_16n17_v1.root", //122
  "./input/data/LMEE_systematics_75MeV_v4.root", //123
  "./input/data/LMEE_systematics_75MeV_v6.root", //124
  "./input/data/FullDataQA_16n17_75MeV_v1.root", //125
  "./input/data/LMEE_systematics_200MeV_v5.root", //126

  "./input/data/LMEE_LEGO1056_LHC16f.root", //127
  "./input/data/LMEE_LEGO1085_LHC16f.root", //128
  "./input/LMEE_LEGO626.root", //129
  "./input/data/LMEE_data2018.root", //130
  "./input/data/LMEE_LEGO1274_LHC18cCent.root", //131
  "./input/data/LMEE_LEGO1275_LHC18cCentwoSDD.root", //132
  "./input/data/LMEE_LEGO1276_LHC18cFAST.root", //133
  "./input/data/LMEE_Fulldata18_v2.root", //134
  "./input/data/LMEE_LEGO1294_LHC18c_FAST.root", //135
  "./input/data/LMEE_LEGO1295_LHC18c_CENTwoSDD.root", //136
  "./input/data/LMEE_LEGO1296_LHC18c_CENT.root", //137
  "./input/data/MultV0/LEGO1310_LHC18c_CENT/LMEE_6.root", //138

  "./input/data/MultV0_2/Combined_LMEE_0_v1.root", //139
  "./input/data/MultV0_2/Combined_LMEE_1_v1.root", //140
  "./input/data/MultV0_2/Combined_LMEE_2_v1.root", //141
  "./input/data/MultV0_2/Combined_LMEE_3_v1.root", //142
  "./input/data/MultV0_2/Combined_LMEE_4_v1.root", //143
  "./input/data/MultV0_2/Combined_LMEE_5_v1.root", //144

  "./input/data/XeXe/LMEE_LEGO336_LHC17n_XeXe.root", //145
  "./input/data/XeXe/LMEE_LEGO337_LHC17n_XeXe_0.root", //146
  "./input/data/XeXe/LMEE_LEGO337_LHC17n_XeXe_1.root", //147
  "./input/data/XeXe/LMEE_LEGO337_LHC17n_XeXe_2.root", //148
  "./input/data/XeXe/LMEE_LEGO337_LHC17n_XeXe_3.root", //149
  "./input/data/XeXe/LMEE_LEGO337_LHC17n_XeXe_4.root", //150
  "./input/data/XeXe/LMEE_LEGO337_LHC17n_XeXe_5.root", //151
  "./input/data/XeXe/LMEE_LEGO337_LHC17n_XeXe_6.root", //152
  "./input/data/XeXe/LMEE_LEGO337_LHC17n_XeXe_7.root", //153

  "./input/data/2018/LMEE_combined18_woSDD.root", //154
  "./input/data/2018/LMEE_LEGO1441_LHC18c_fast.root", //155
  "./input/data/2018/LMEE_LEGO1443_LHC18c_cent.root", //156
  "./input/data/LMEE_LEGO1453_LHC17g.root", //157
  "./input/data/LMEE_LEGO1454_LHC18c_cent.root", //158
  "./input/data/LMEE_LEGO1522_LHC17g.root", //159
  "./input/data/LMEE_mult_16n17.root", //160
  "./input/data/LMEE_mult_18.root", //161
  "./input/data/LMEE_LEGO1527_LHC18c_CENT_wSDD.root", //162
  "./input/data/V0M/LMEE_mult_16n17_0-10.root", //163
  "./input/data/V0M/LMEE_mult_16n17_10-20.root", //164
  "./input/data/V0M/LMEE_mult_16n17_20-40.root", //165
  "./input/data/V0M/LMEE_mult_16n17_40-70.root", //166
  "./input/data/V0M/LMEE_mult_16n17_70-100.root", //167
  "./input/data/V0M/LMEE_LEGO1527_LHC18c_CENT_wSDD_0-10.root", //168
  "./input/data/V0M/LMEE_LEGO1527_LHC18c_CENT_wSDD_10-20.root", //169
  "./input/data/V0M/LMEE_LEGO1527_LHC18c_CENT_wSDD_20-40.root", //170
  "./input/data/V0M/LMEE_LEGO1527_LHC18c_CENT_wSDD_40-70.root", //171
  "./input/data/V0M/LMEE_LEGO1527_LHC18c_CENT_wSDD_70-100.root", //172
  "./input/data/V0M/LMEE_mult_16n17_0-20.root", //173
  "./input/data/V0M/LMEE_LEGO1527_LHC18c_CENT_wSDD_0-20.root", //174
  "./input/data/LMEE_LEGO1529_LHC18c_FAST.root", //175
  "./input/data/V0M/LMEE_LEGO1529_LHC18c_FAST_0-10.root", //176
  "./input/data/V0M/LMEE_LEGO1529_LHC18c_FAST_10-20.root", //177
  "./input/data/V0M/LMEE_LEGO1529_LHC18c_FAST_20-40.root", //178
  "./input/data/V0M/LMEE_LEGO1529_LHC18c_FAST_40-70.root", //179
  "./input/data/V0M/LMEE_LEGO1529_LHC18c_FAST_70-100.root", //180
  "./input/data/LMEE_mult_16n17_test.root", //181
  "./input/data/LMEE_LEGO1523_LHC16f.root", //182
  "./input/data/LMEE_LEGO1524_LHC17g.root", //183

  "./input/data/LMEE_LEGO16n17_post.root", //184

  "./input/data/V0M/LMEE_mult_16n17n18.root", //185
  "./input/data/V0M/LMEE_mult_16n17n18_0-10.root", //186
  "./input/data/V0M/LMEE_mult_16n17n18_10-20.root", //187
  "./input/data/V0M/LMEE_mult_16n17n18_20-40.root", //188
  "./input/data/V0M/LMEE_mult_16n17n18_40-70.root", //189
  "./input/data/V0M/LMEE_mult_16n17n18_70-100.root", //190
  "./input/data/LMEE_mult_16n17_pileup.root", //191

  "./input/data/V0M2/LMEE_LEGO16n17n18_CENT.root", //192
  "./input/data/V0M2/LMEE_LEGO16n17n18.root", //193
  "./input/data/V0M2/LMEE_LEGO1546_LHC18c_CENT_wSDD.root", //194
  "./input/data/V0M2/LMEE_LEGO1547_LHC18c_FAST.root", //195

  "./input/data/V0M3/LMEE_LEGO16n17_0-100.root", //196
  "./input/data/V0M3/LMEE_LEGO16n17.root", //197
  "./input/data/V0M3/LMEE_LEGO16n17n18_CENT_0-100.root", //198
  "./input/data/V0M3/LMEE_LEGO16n17n18_CENT.root", //199
  "./input/data/V0M3/LMEE_LEGO16n17n18_0-100.root", //200
  "./input/data/V0M3/LMEE_LEGO16n17n18.root", //201

  "./input/data/V0M3/LMEE_LEGO1552_LHC18c_FAST_0-100.root", //202
  "./input/data/V0M3/LMEE_LEGO1553_LHC18c_CENT_0-100.root", //203
  "./input/data/V0M3/LMEE_LEGO1552_LHC18c_FAST.root", //204
  "./input/data/V0M3/LMEE_LEGO1553_LHC18c_CENT.root", //205

  "./input/data/V0M4/LMEE_LEGO16n17_0-100.root", //206
  "./input/data/V0M4/LMEE_LEGO16n17.root", //207
  "./input/data/V0M4/LMEE_LEGO16n17n18_CENT_0-100.root", //208
  "./input/data/V0M4/LMEE_LEGO16n17n18_CENT.root", //209
  "./input/data/V0M4/LMEE_LEGO16n17n18_0-100.root", //210
  "./input/data/V0M4/LMEE_LEGO16n17n18.root", //211

  "./input/data/HM/LMEE_LEGO17_HM.root", //212
  "./input/data/V0M4/LMEE_LEGO16n17n18_0-20.root", //213
  "./input/data/V0M4/LMEE_LEGO16n17n18_0-10.root", //214
  "./input/data/V0M4/LMEE_LEGO16n17n18_10-20.root", //215
  "./input/data/V0M4/LMEE_LEGO16n17n18_20-40.root", //216
  "./input/data/V0M4/LMEE_LEGO16n17n18_40-70.root", //217
  "./input/data/V0M4/LMEE_LEGO16n17n18_70-100.root", //218

  "./input/data/V0M4/LMEE_LEGO16n17_0-100.root", //219
  "./input/data/V0M4/LMEE_LEGO1559_LHC18c_CENT_0-100.root", //220
  "./input/data/V0M4/LMEE_LEGO1600_LHC18c_FAST_0-100.root", //221

  "./input/data/V0M4/LMEE_LEGO16n17n18_0-40.root", //222
  "./input/data/V0M4/LMEE_LEGO16n17n18_40-100.root", //223

  "./input/data/V0M4/LMEE_LEGO16n17_0-10.root", //224
  "./input/data/V0M4/LMEE_LEGO1559_LHC18c_CENT_0-10.root", //225
  "./input/data/V0M4/LMEE_LEGO1600_LHC18c_FAST_0-10.root", //226

  "./input/data/Sphero/LMEE_LEGO16n17n18_0-10_all.root",  //227
  "./input/data/Sphero/LMEE_LEGO16n17n18_0-10_soft.root", //228

  "./input/data/Sphero/LMEE_LEGO16n17n18_v1.root", //229

  "./input/data/Sphero/LMEE_LEGO16n17n18_0_40_v1.root", //230
  "./input/data/Sphero/LMEE_LEGO16n17n18_0_40_soft_v1.root", //231
  "./input/data/Sphero/LMEE_LEGO16n17n18_0_40_hard_v1.root", //232

  "./input/data/Sphero/LMEE_LEGO16n17n18_0_20_v1.root", //233
  "./input/data/Sphero/LMEE_LEGO16n17n18_0_20_soft_v1.root", //234
  "./input/data/Sphero/LMEE_LEGO16n17n18_0_20_hard_v1.root", //235

  "./input/data/Sphero/LMEE_LEGO16n17n18_0_20_v2.root", //236
  "./input/data/Sphero/LMEE_LEGO16n17n18_0_20_soft_v2.root", //237
  "./input/data/Sphero/LMEE_LEGO16n17n18_0_20_hard_v2.root", //238

  "./input/data/Sphero/LMEE_LEGO16n17n18_0_40_v2.root", //239
  "./input/data/Sphero/LMEE_LEGO16n17n18_0_40_soft_v2.root", //240
  "./input/data/Sphero/LMEE_LEGO16n17n18_0_40_hard_v2.root", //241

  "./input/data/Sphero/LMEE_LEGO16n17n18_0_20_v3.root", //242
  "./input/data/Sphero/LMEE_LEGO16n17n18_0_20_soft_v3.root", //243
  "./input/data/Sphero/LMEE_LEGO16n17n18_0_20_hard_v3.root", //244

  "./input/data/Sphero2/LMEE_LEGO16n17n18_v1.root", //245

  "./input/mc/Sphero2/LMEE_LEGO16n17n18_v2.root", //246
  "./input/mc/Sphero2/LMEE_LEGO16n17n18_0-20_v2.root", //247
  "./input/mc/Sphero2/LMEE_LEGO16n17n18_0-20_soft_v2.root", //248
  "./input/mc/Sphero2/LMEE_LEGO16n17n18_0-20_hard_v2.root", //249

  "./input/mc/Sphero2/LMEE_LEGO16n17n18_0-10_v2.root", //250
  "./input/mc/Sphero2/LMEE_LEGO16n17n18_0-10_soft_v2.root", //251
  "./input/mc/Sphero2/LMEE_LEGO16n17n18_0-10_hard_v2.root", //252

  "./input/data/sys/LMEE_LEGO1641_LHC18c_CENT.root", //253

  "./input/data/fine/LMEE_16n17n18_fine.root", //254
  "./input/data/fine/LMEE_LEGO1670_LHC16f.root", //255
  "./input/data/fine/LMEE_LEGO1669_LHC17g.root", //256
  "./input/data/fine/LMEE_LEGO1668_LHC18c_FAST.root", //257
  "./input/data/fine/LMEE_LEGO1667_LHC18c_CENT.root", //258

  "./input/data/V0M4/LMEE_LEGO1557_LHC16f.root", //259
  "./input/data/V0M4/LMEE_LEGO1558_LHC17g.root", //260

  "./input/data/check/LMEE_LEGO1784_LHC17g.root", //261
  "./input/data/check/LMEE_LEGO1785_LHC16f.root", //262
  "./input/data/check/LMEE_LEGO1786_LHC18c_CENT.root", //263

  //"./input/data/newGen2/LMEE_LEGO1943_LHC17g.root", //264
  //"./input/data/newGen2/LMEE_LEGO1944_LHC16f.root", //265
  ////"./input/data/newGen2/LMEE_16n17.root", //266
  //"./input/data/newGen2/LMEE_LEGO1945_LHC18c_CENT.root", //266
  //"./input/data/newGen2/LMEE_LEGO1946_LHC18c_FAST.root", //267

  "./input/data/newGen3/LMEE_LEGO1970_LHC17g.root", //264
  "./input/data/newGen3/LMEE_LEGO1971_LHC16f.root", //265
  //"./input/data/newGen2/LMEE_16n17.root", //266
  "./input/data/newGen3/LMEE_LEGO1972_LHC18c_CENT.root", //266
  "./input/data/newGen3/LMEE_LEGO1973_LHC18c_FAST.root", //267


  "./input/data/newGen4/LMEE_LEGO1977_LHC17g.root", //268
  "./input/data/newGen4/LMEE_LEGO1975_LHC16f.root", //269
  "./input/data/newGen4/LMEE_LEGO1979_LHC18c_CENT.root", //270
  "./input/data/newGen4/LMEE_LEGO1978_LHC18c_FAST.root", //271

  "./input/data/newGen_sys/LMEE_LEGO1990_LHC17g.root", //272
  "./input/data/newGen_sys/LMEE_LEGO1991_LHC16f.root", //273
  "./input/data/newGen_sys/LMEE_LEGO1988_LHC18c_CENT.root", //274
  "./input/data/newGen_sys/LMEE_LEGO1989_LHC18c_FAST.root", //275

  "./input/data/newGen4/LMEE_LEGO1977_LHC17g_0-20.root", //276
  "./input/data/newGen4/LMEE_LEGO1975_LHC16f_0-20.root", //277
  "./input/data/newGen4/LMEE_LEGO1979_LHC18c_CENT_0-20.root", //278
  "./input/data/newGen4/LMEE_LEGO1978_LHC18c_FAST_0-20.root", //279

  "./input/data/newGen4/LMEE_LEGO1977_LHC17g_20-40.root", //280
  "./input/data/newGen4/LMEE_LEGO1975_LHC16f_20-40.root", //281
  "./input/data/newGen4/LMEE_LEGO1979_LHC18c_CENT_20-40.root", //282
  "./input/data/newGen4/LMEE_LEGO1978_LHC18c_FAST_20-40.root", //283

  "./input/data/newGen4/LMEE_LEGO1977_LHC17g_40-70.root", //284
  "./input/data/newGen4/LMEE_LEGO1975_LHC16f_40-70.root", //285
  "./input/data/newGen4/LMEE_LEGO1979_LHC18c_CENT_40-70.root", //286
  "./input/data/newGen4/LMEE_LEGO1978_LHC18c_FAST_40-70.root", //287

  "./input/data/newGen4/LMEE_LEGO1977_LHC17g_70-100.root", //288
  "./input/data/newGen4/LMEE_LEGO1975_LHC16f_70-100.root", //289
  "./input/data/newGen4/LMEE_LEGO1979_LHC18c_CENT_70-100.root", //290
  "./input/data/newGen4/LMEE_LEGO1978_LHC18c_FAST_70-100.root", //291

  "./input/data/newGen3/LMEE_LEGO1970_LHC17g_0-20.root", //292
  "./input/data/newGen3/LMEE_LEGO1971_LHC16f_0-20.root", //293
  "./input/data/newGen3/LMEE_LEGO1972_LHC18c_CENT_0-20.root", //294
  "./input/data/newGen3/LMEE_LEGO1973_LHC18c_FAST_0-20.root", //295

  "./input/data/newGen3/LMEE_LEGO1970_LHC17g_20-40.root", //296
  "./input/data/newGen3/LMEE_LEGO1971_LHC16f_20-40.root", //297
  "./input/data/newGen3/LMEE_LEGO1972_LHC18c_CENT_20-40.root", //298
  "./input/data/newGen3/LMEE_LEGO1973_LHC18c_FAST_20-40.root", //299

  "./input/data/newGen3/LMEE_LEGO1970_LHC17g_40-70.root", //300
  "./input/data/newGen3/LMEE_LEGO1971_LHC16f_40-70.root", //301
  "./input/data/newGen3/LMEE_LEGO1972_LHC18c_CENT_40-70.root", //302
  "./input/data/newGen3/LMEE_LEGO1973_LHC18c_FAST_40-70.root", //303

  "./input/data/newGen3/LMEE_LEGO1970_LHC17g_70-100.root", //304
  "./input/data/newGen3/LMEE_LEGO1971_LHC16f_70-100.root", //305
  "./input/data/newGen3/LMEE_LEGO1972_LHC18c_CENT_70-100.root", //306
  "./input/data/newGen3/LMEE_LEGO1973_LHC18c_FAST_70-100.root", //307




  "",
  ""
};
TString nameMC[] = {
  "./input/mc/LMEE_LEGO520_LHC17d1.root",
  "./input/mc/GPMC_16n17_75MeV_v1.root",
  "",
  ""
};
//
// further details of input data
TString tree_name[] = { "Histos_diel_lowmass", "Histos_diel_lowmass_1", "Histos_diel_lowmass_2", "Histos_diel_lowmass_3", "Histos_diel_lowmass_4", "Histos_diel_lowmass_5", "Histos_diel_lowmass_6", "Histos_diel_lowmass_7" , "Histos_diel_lowmass_8", "Histos_diel_lowmass_9"};
TString cut_setting[] = { // always adapt to input data files!
  "pT50_PID",                                                     //0
  "pT50_PID_closed",                                              //1
  "pT150_PF",                                                     //2
  "pT50_PF",
  "pT50_noPF",
  "pT50_noPF",
  "pT50_noPF",
  "pT50_noPF",
  "pT50_noPF",
  "pT75_PF_woITS",
  "pT75_noPF_woITS",                                              //10
  "pT75_PF0wPID0_TrCuts0_PIDCuts0woITS",                          //11
  "pT75_PF0wPID0_TrCuts0_PIDCuts0woITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0woITS",
  "pT75_noPF_TrCuts0_PIDCuts0woITS",
  "pT75_noPF_TrCuts0_PIDCuts0woITS_2",
  "pT75_noPF_TrCuts0_PIDCuts0wITS",
  "pT75_PF0_TrCuts0_PIDCuts0woITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0woITS",
  "pT75_PF0_TrCuts0_PIDCuts0wITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wITS",                           //20
  "pT200_noPF_TrCuts0_PIDCuts6wTOFwITS",                          //21
  "pT75_noPF_TrCuts0_PIDCuts6wTOFwITS",
  "pT200_PF0_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_PF0_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts1wTOFwITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts1wTOFwITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_2",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_3",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_4",                     //30
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_5",                     //31
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_6",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_7",
  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts1wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts2wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts3wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts4wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS",                        //40
  "pT75_PF0wPID0_TrCuts0_PIDCuts1wTOFwITS",                        //41
  "pT75_PF0wPID0_TrCuts0_PIDCuts2wTOFwITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts3wTOFwITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts4wTOFwITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts1wTOFwITS",
  "pT75_PF0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0_TrCuts0_PIDCuts0wTOFwITS_2",
  "pT75_PF0_TrCuts0_PIDCuts0wTOFwITS_3",
  "pT75_PF0_TrCuts0_PIDCuts0wTOFwITS_4",                           //50
  "pT75_PF0_TrCuts0_PIDCuts0wTOFwITS_5",                           //51
  "pT75_PF0_TrCuts0_PIDCuts0wTOFwITS_6",
  "pT75_PF0_TrCuts0_PIDCuts0wTOFwITS_7",
  "pT75_noPF_TrCuts0_PIDCuts5wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts7wTOFwITS",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts1wTOFwITS",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts2wTOFwITS",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts0wTOFwITS_2",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts5wTOFwITS",   //60
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts7wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts1wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts2wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts0wTOFwITS_2",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts5wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts7wTOFwITS",

  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts0wTOFwITS",//70
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts0wTOFwITS_2",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts0wTOFwITS_6",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_4",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_5",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts0wTOFwITS_6",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_7",

  "pT75_PF0wPID0wOp5_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp10_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp15_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp25_TrCuts0_PIDCuts0wTOFwITS", //80
  "pT75_PF0wPID0wOp30_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wInvMass200wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wInvMass100wOp20_TrCuts0_PIDCuts0wTOFwITS",

  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp75_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp100_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp150_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp200_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wInvMass100wOp50_TrCuts0_PIDCuts0wTOFwITS", //90

  "pT75_PF0wPID0wOp0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp10_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp300_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp75_TrCuts0_PIDCuts0wTOFwITS",

  "pT75_PF0wOp0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp10_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts0wTOFwITS", //100
  "pT75_PF0wOp300_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp50_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp75_TrCuts0_PIDCuts0wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts201wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts202wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts203wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts204wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts205wTOFwITS", //110
  "pT75_noPF_TrCuts0_PIDCuts206wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp10_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp30_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp50_TrCuts0_PIDCuts0wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts7wTOFwITS", //120
  "pT75_noPF_TrCuts0_PIDCuts204wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts207wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts208wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts601wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wOp0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0_TrCuts0_PIDCuts0wTOFwITS", //130
  "pT75_PF0wOp50_TrCuts0_PIDCuts0wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wInvMass40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wInvMass40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wInvMass40_TrCuts0_PIDCuts0wTOFwITS_2",
  "pT75_PF0wPID0wInvMass40_TrCuts0_PIDCuts0wTOFwITS_3",
  "pT75_PF0wPID0wInvMass40wOp40_TrCuts0_PIDCuts0wTOFwoITS",
  "pT75_PF0wPID0wInvMass40wOp20_TrCuts0_PIDCuts0wTOFwITS",

  "pT75_PF0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wInvMass10wOp20_TrCuts0_PIDCuts0wTOFwITS", //140
  "pT75_PF0wInvMass20wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wInvMass30wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wInvMass40wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wInvMass50wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wInvMass100wOp20_TrCuts0_PIDCuts0wTOFwITS",

  "pT75_PF0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts7wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts210wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts211wTOFwITS", //150
  "pT75_PF0wOp20_TrCuts0_PIDCuts212wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts213wTOFwITS",

  "pT75_PF0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts7wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts211wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts212wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts213wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts214wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS", //160
  "pT75_PF0wOp0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp10_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp30_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp50_TrCuts0_PIDCuts0wTOFwITS",

  "pT200_noPF_TrCuts0_PIDCuts6wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts7wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts6wTOFwITS", //170
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts7wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwoITS",

  "pT200_noPF_TrCuts0_PIDCuts6wTOFwITS",  //ref
  "pT200_noPF_TrCuts0_PIDCuts7wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts6wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts7wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwoITS", //180

  "pT200_noPF_TrCuts0_PIDCuts6wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts7wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts6wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts7wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwoITS",

  "pT200_noPF_TrCuts0_PIDCuts6wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts7wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts0wTOFwITS", //190
  "pT200_noPF_TrCuts0_PIDCuts10wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts11wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts11wTOFwITS",

  "pT200_noPF_TrCuts0_PIDCuts7wTOFwITS",  //ref
  "pT200_noPF_TrCuts0_PIDCuts10wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts7wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts10wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwITS",  //200
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwoITS",

  "pT75_noPF_TrCuts-1_PIDCuts-1wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwITS",
  "pT75_noPF_TrCuts-1_PIDCuts12wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts12wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts10wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts10wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts10wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts104wTOFwITS",  //210
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts700wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts601wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts214wTOFwITS",

  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts104wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts700wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts600wTOFwITS",  //220
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts601wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts214wTOFwITS",

  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",  //ref
  "pT200_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts700wTOFwoITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts700wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts214wTOFwITS",

  "pT75_noPF_TrCuts-1_PIDCuts302wTOFwITS_Conv", //230
  "pT75_noPF_TrCuts0_PIDCuts302wTOFwITS_Conv",
  "pT75_noPF_TrCuts-1_PIDCuts303wTOFwITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts303wTOFwITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts100woTOFwITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts100woTOFwoITS_Conv",

  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT125_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT150_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS", //240
  "pT175_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_PF0wPID0wOp40_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_PF0wPID0wOp10_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp30_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp40_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp75_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp100_TrCuts0_PIDCuts100wTOFwITS", //250

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT125_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT175_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",

  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT250_noPF_TrCuts0_PIDCuts100wTOFwITS", //260
  "pT300_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT350_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwITS",

  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT250_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT300_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT350_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwITS", //270

  "pT100_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT250_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT300_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT350_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT400_noPF_TrCuts0_PIDCuts600wTOFwITS",

  "pT100_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts600wTOFwITS", //280
  "pT250_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT300_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT350_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT400_noPF_TrCuts0_PIDCuts600wTOFwITS",

  "pT100_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT250_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT300_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT350_noPF_TrCuts0_PIDCuts600wTOFwITS", //290
  "pT400_noPF_TrCuts0_PIDCuts600wTOFwITS",

  "pT100_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT250_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT300_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT350_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT400_noPF_TrCuts0_PIDCuts600wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT100_noPF_TrCuts0_PIDCuts600wTOFwITS", //300
  "pT110_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT120_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT130_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT140_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts600wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT100_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT110_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT120_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT130_noPF_TrCuts0_PIDCuts600wTOFwITS", //310
  "pT140_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts600wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT90_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT110_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT130_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly", //320
  "pT90_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT110_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT130_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT90_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT110_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly", //330
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT130_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT90_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT110_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT130_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly", //340

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT90_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly", //350
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT300_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT300_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly", //360
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",

  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT120_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT140_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT300_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT400_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS", //370
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT300_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched", //380
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched", //390

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_2",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwoITS", //400
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwoITS", //410
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwoITS_2",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT150_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwoITS",
  "pT75_PF0wPID0wInvMass10wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "pT100_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS", //420
  "pT100_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS_2",
  "pT120_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "pT150_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_2",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts100wTOFwITS",  //430
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts-1wTOFwITS",
  "pT75_PF0wPID0wInvMass10wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS_2",
  "pT120_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT150_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwITS", //440
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts-1wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts600wTOFwITS", //460
  "pT400_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT400_PF0wPID0wOp50_TrCuts0_PIDCuts600wTOFwITS",
  "pT100_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts110wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts110wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts600wTOFwoITS",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts600wTOFwoITS",
  "pT200_PF0wPID0wOp75_TrCuts0_PIDCuts100wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwoITS", //460
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS",   //463
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT400_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",

  "pT100_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT100_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts701wTOFwoITS", //470
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts701wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",

  "pT100_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT100_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts111wTOFwITS",  //480
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts111wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts800wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts800wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts801wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts801wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts802wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts802wTOFwITS",

  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp30_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp40_TrCuts0_PIDCuts100wTOFwoITS", //490
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp60_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp75_TrCuts0_PIDCuts100wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts303wTOFwoITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts303woTOFwoITS_Conv",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts130wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts600wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts701wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts304wTOFwoITS", //500
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts304wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts303wTOFwoITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts303woTOFwoITS_Conv",

  "pT75_noPF_TrCuts0_PIDCuts303wTOFwoITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts303woTOFwoITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS", //510
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts120wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts600wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts600wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts701wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS", //520
  "pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut",

  "pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts140wTOFwoITS_SCcut",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts140wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts140wTOFwoITS_SCcut",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts140wTOFwoITS", //530

  "pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts140wTOFwoITS_SCcut",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts140wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut",
  "pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS_SCcut",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut", //540
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut",
  "pT200_noPF_TrCuts0_PIDCuts701wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts701wTOFwoITS_SCcut",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS", //550

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",

  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0wOp50v1_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0v2_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0v3_TrCuts0_PIDCuts100wTOFwoITS_noV0", //560
  "pT75_PF0wPID0v5_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0", //570

  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_SCcut_noV0",

  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_SCcut_noV0",  //580
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_SCcut_noV0",

  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_SCcut_noV0",

  "pT75_noPF_TrCuts150_PIDCuts150wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts151_PIDCuts151wTOFwoITS_SCcut_noV0",  //590
  "pT75_noPF_TrCuts152_PIDCuts152wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts153_PIDCuts153wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts154_PIDCuts154wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts155_PIDCuts155wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts156_PIDCuts156wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts157_PIDCuts157wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts158_PIDCuts158wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts159_PIDCuts159wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts160_PIDCuts160wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts161_PIDCuts161wTOFwoITS_SCcut_noV0",  //600
  "pT75_noPF_TrCuts162_PIDCuts162wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts163_PIDCuts163wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts164_PIDCuts164wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts165_PIDCuts165wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts166_PIDCuts166wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts167_PIDCuts167wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts168_PIDCuts168wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts169_PIDCuts169wTOFwoITS_SCcut_noV0",

  "pT75_noPF_TrCuts170_PIDCuts170wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts171_PIDCuts171wTOFwoITS_SCcut_noV0",  //610
  "pT75_noPF_TrCuts172_PIDCuts172wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts173_PIDCuts173wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts174_PIDCuts174wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts175_PIDCuts175wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts176_PIDCuts176wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts177_PIDCuts177wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts178_PIDCuts178wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts179_PIDCuts179wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts180_PIDCuts180wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts181_PIDCuts181wTOFwoITS_SCcut_noV0",  //620
  "pT75_noPF_TrCuts182_PIDCuts182wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts183_PIDCuts183wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts184_PIDCuts184wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts185_PIDCuts185wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts186_PIDCuts186wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts187_PIDCuts187wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts188_PIDCuts188wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts189_PIDCuts189wTOFwoITS_SCcut_noV0",

  "pT75_noPF_TrCuts-1_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0", //630
  "pT75_noPF_TrCuts-1_PIDCuts100wTOFwoITS_noV0",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",

  "pT200_noPF_TrCuts150_PIDCuts150wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts151_PIDCuts151wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts152_PIDCuts152wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts153_PIDCuts153wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts154_PIDCuts154wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts155_PIDCuts155wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts156_PIDCuts156wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts157_PIDCuts157wTOFwoITS_SCcut_noV0", //640
  "pT200_noPF_TrCuts158_PIDCuts158wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts159_PIDCuts159wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts160_PIDCuts160wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts161_PIDCuts161wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts162_PIDCuts162wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts163_PIDCuts163wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts164_PIDCuts164wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts165_PIDCuts165wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts166_PIDCuts166wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts167_PIDCuts167wTOFwoITS_SCcut_noV0", //650
  "pT200_noPF_TrCuts168_PIDCuts168wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts169_PIDCuts169wTOFwoITS_SCcut_noV0",

  "pT75_noPF_TrCuts150_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts11_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts12_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts11_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts12_PIDCuts100wTOFwoITS_SCcut_noV0",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0wInvMass10wOp50v4_TrCuts0_PIDCuts100wTOFwoITS_noV0", //660
  "pT75_PF0wPID0wInvMass20v2_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0v3_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0v8_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass10wOp50v4_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass20v2_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0v3_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0v8_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",

  "pT75_PF0wPID0wInvMass40v2_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0", //670
  "pT75_PF0wPID0wInvMass40v2_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0_2",
  "pT75_PF0wPID0wInvMass40v2_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0_3",

  "pT75_PF0wPID0wInvMass40v2_TrCuts150_PIDCuts150wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts151_PIDCuts151wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts152_PIDCuts152wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts153_PIDCuts153wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts154_PIDCuts154wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts155_PIDCuts155wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts156_PIDCuts156wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts157_PIDCuts157wTOFwoITS_SCcut_noV0", //680
  "pT75_PF0wPID0wInvMass40v2_TrCuts158_PIDCuts158wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts159_PIDCuts159wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts160_PIDCuts160wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts161_PIDCuts161wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts162_PIDCuts162wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts163_PIDCuts163wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts164_PIDCuts164wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts165_PIDCuts165wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts166_PIDCuts166wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts167_PIDCuts167wTOFwoITS_SCcut_noV0", //690
  "pT75_PF0wPID0wInvMass40v2_TrCuts168_PIDCuts168wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts169_PIDCuts169wTOFwoITS_SCcut_noV0",

  "pT75_PF0wPID0wInvMass40v2_TrCuts12_PIDCuts100wTOFwoITS_SCcut_noV0",

  "pT75_PF0wPID0wInvMass40v2_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts13_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts14_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass40v2_TrCuts15_PIDCuts100wTOFwoITS_SCcut_noV0",

  "pT75_PF0wPID0wInvMass40v21_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0", //698
  "pT75_PF0wPID0wInvMass40v21_TrCuts12_PIDCuts100wTOFwoITS_SCcut_noV0", //699

  "pT75_PF0wPID0wInvMass40v2_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",   //700
  "pT75_PF0wPID0wInvMass40v2_TrCuts12_PIDCuts100wTOFwoITS_SCcut_noV0",  //701
  "pT75_PF0wPID0wInvMass40v2_TrCuts200_PIDCuts100wTOFwoITS_SCcut_noV0", //702
  "pT75_PF0wPID0wInvMass40v2_TrCuts201_PIDCuts100wTOFwoITS_SCcut_noV0", //703
  "pT75_PF0wPID0wInvMass40v2_TrCuts202_PIDCuts100wTOFwoITS_SCcut_noV0", //704
  "pT75_PF0wPID0wInvMass40v2_TrCuts203_PIDCuts100wTOFwoITS_SCcut_noV0", //705

  "pT75_PF0wPID0wInvMass40v2_TrCuts204_PIDCuts100wTOFwoITS_SCcut_noV0", //706
  "pT75_PF0wPID0wInvMass40v2_TrCuts205_PIDCuts100wTOFwoITS_SCcut_noV0", //707
  "pT75_PF0wPID0wInvMass40v2_TrCuts206_PIDCuts100wTOFwoITS_SCcut_noV0", //708
  "pT75_PF0wPID0wInvMass40v2_TrCuts207_PIDCuts100wTOFwoITS_SCcut_noV0", //709
  "pT75_PF0wPID0wInvMass40v2_TrCuts208_PIDCuts100wTOFwoITS_SCcut_noV0", //710
  "pT75_PF0wPID0wInvMass40v2_TrCuts209_PIDCuts100wTOFwoITS_SCcut_noV0", //711

  ""
};
TString cut_settingMC[] = { // always adapt to input data files!
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  ""
};


TString pairMC[] = {
"",
"/Pair_MCpair_sameMother",
"/Pair_MCpair_diffMother/ULS",
"/Pair_MCpair_sameGamma"
};


// corresponding input efficiency files
TString effi_name[] = {
  "./input/efficiency/ppToyMCpairEff_raw_pt75_LHC17d1.root",
  "./input/efficiency/ppToyMCpairEff_raw_pt75_LHC17h3.root",
  "./input/efficiency/ppToyMCpairEff_raw_pt200_LHC17d1_LEGO443.root",
  "./input/efficiency/ppToyMCpairEff_raw_pt200_LHC17h3_LEGO444.root",
  "./input/efficiency/ppToyMCpairEff_raw_pt75_LHC17d1_LEGO443_test.root",
  "./input/efficiency/ppToyMCpairEff_raw_pt200_LHC17d1_LEGO443_test.root",
  "./input/efficiency/FullMC_200MeV/FullMCEfficiency_17.root",
  "./input/efficiency/FullMC_200MeV/FullMCEfficiency_16n17Sum.root",
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17Sum_75MeV.root",
  "./input/efficiency/FullMC_200MeV/FullMCEfficiency_16n17Sum2.root",
  "./input/efficiency/FullMC_200MeV/FullMCEfficiency_16n17Sum_new.root", //10
  "./input/efficiency/FullMC_200MeV/LMEE_LEGO654_LHC17d20a1.root",
  "./input/efficiency/FullMC_200MeV_wPileUp/FullMCEfficiency_16n17Sum_wPileUp.root",
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_75MeV_sys.root", //13
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_150_v2.root", //14
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_151_v2.root", //15
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_152_v2.root", //16
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_153_v2.root", //17
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_154_v2.root", //18
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_155_v2.root", //19
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_156_v2.root", //20
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_157_v2.root", //21
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_158_v2.root", //22
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_159_v2.root", //23
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_160_v2.root", //24
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_161_v2.root", //25
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_162_v2.root", //26
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_163_v2.root", //27
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_164_v2.root", //28
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_165_v2.root", //29
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_166_v2.root", //30
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_167_v2.root", //31
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_168_v2.root", //32
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_169_v2.root", //33
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_75MeV_v3.root", //34
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_75MeV_v4_100.root", //35
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_100_v2.root", //36
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v5_all.root", //37
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v6_all.root", //38
  "./input/efficiency/FullMC_200MeV/FullMCEfficiency_16n17_sys_200MeV_v5_all.root", //39
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_v7_all.root", //40
  "./input/efficiency/FullMC_75MeV/FullMCEfficiency_16n17_sys_75MeV_noSCcut.root", //41
  "./input/efficiency/FullMC_75MeV/test_weighted.root", //42
  "./input/efficiency/FullMC_75MeV/test_weighted_1.root", //43
  "./input/efficiency/FullMC_75MeV/MultV0/input/Combined_LMEE_6_weighted_v1.root", //44
  "./input/efficiency/FullMC_75MeV/MultV0/input/LHC18h1_CENT_LMEE_6_weighted_v1.root", //45
//  "./input/efficiency/FullMC_75MeV/MultV0/input/LHC18h1_CENT_LMEE_6_weighted_v1_1.root", //46
  "./input/efficiency/FullMC_75MeV/MultV0/input/LHC18h1_test.root", //46
  "./input/efficiency/FullMC_75MeV/test_ResoOnly.root", //47
  "./input/efficiency/FullMC_75MeV/test_HFOnly.root", //48
  "./input/efficiency/FullMC_75MeV/MultV0_2/Combined_LMEE_0_weighted_v1.root", //49
  "./input/efficiency/FullMC_75MeV/MultV0_2/Combined_LMEE_1_weighted_v1.root", //50
  "./input/efficiency/FullMC_75MeV/MultV0_2/Combined_LMEE_2_weighted_v1.root", //51
  "./input/efficiency/FullMC_75MeV/MultV0_2/Combined_LMEE_3_weighted_v1.root", //52
  "./input/efficiency/FullMC_75MeV/MultV0_2/Combined_LMEE_4_weighted_v1.root", //53
  "./input/efficiency/FullMC_75MeV/MultV0_2/Combined_LMEE_5_weighted_v1.root", //54
  "./input/efficiency/FullMC_75MeV/test_2018new.root", //55
  "./input/efficiency/FullMC_75MeV/test_2017weighted_v1.root", //56
  "./input/efficiency/FullMC_75MeV/test_2017weighted_v2.root", //57
  "./input/efficiency/FullMC_75MeV/2017_ResoOnly.root", //58
  "./input/efficiency/FullMC_75MeV/test_2018weighted_fast_v1.root", //59
  "./input/efficiency/FullMC_75MeV/test_2018weighted_fast_v2.root", //60
  "./input/efficiency/FullMC_75MeV/test_2018weighted_v2.root", //61
  "./input/efficiency/FullMC_75MeV/test_2017weighted_v2.root", //62
  "./input/efficiency/FullMC_200MeV/test_2018weighted200_fast_v2.root", //63
  "./input/efficiency/FullMC_200MeV/test_2018weighted200_v2.root", //64
  "./input/efficiency/FullMC_200MeV/test_2017weighted200_v2.root", //65
  "./input/efficiency/FullMC_75MeV/test_2018weightedsmooth_fast_v1.root", //66
  "./input/efficiency/FullMC_75MeV/test_2018weightedsmooth_v1.root", //67
  "./input/efficiency/FullMC_75MeV/test_2017weightedsmooth_v1.root", //68
  "./input/efficiency/FullMC_75MeV/test_StatWeighted_v7.root", //69
  "./input/efficiency/FullMC_75MeV/test_StatWeighted_70-100_v2.root", //70
  "./input/efficiency/FullMC_75MeV/test_StatWeighted_70-100_v5.root", //71
  "./input/efficiency/FullMC_75MeV/test_StatWeighted_wSDD_v1.root", //72
  "./input/efficiency/FullMC_75MeV/Eff_CockWeighted_16n17_v6.root", //73
  "./input/efficiency/FullMC_75MeV/Eff_CockWeighted_18c_CENT_v6.root", //74
  "./input/efficiency/FullMC_75MeV/Eff_CockWeighted_18c_FAST_v6.root", //75
  "./input/efficiency/FullMC_75MeV/Eff_all_StatWeighted_v1.root", //76

  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys150_v6.root", //77
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys151_v6.root", //78
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys152_v6.root", //79
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys153_v6.root", //80
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys154_v6.root", //81
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys155_v6.root", //82
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys156_v6.root", //83
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys157_v6.root", //84
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys158_v6.root", //85
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys159_v6.root", //86
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys160_v6.root", //87
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys161_v6.root", //88
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys162_v6.root", //89
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys163_v6.root", //90  //not working
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys164_v6.root", //91
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys165_v6.root", //92
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys166_v6.root", //93
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys167_v6.root", //94
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys168_v6.root", //95
  "./input/efficiency/FullMC_75MeV/sys/Eff_CockWeighted_18cent_sys169_v6.root", //96

  "./input/efficiency/FullMC_75MeV/Eff_CockWeighted_16_v4.root", //97
  "./input/efficiency/FullMC_75MeV/Eff_CockWeighted_17_v3.root", //98

  "./input/efficiency/FullMC_75MeV/check2/Eff_CockWeighted_18_v0_2.root", //99
  "./input/efficiency/FullMC_75MeV/check2/Eff_CockWeighted_18_v13_2.root", //100
  "./input/efficiency/FullMC_75MeV/check2/Eff_CockWeighted_18_v14_2.root", //101
  "./input/efficiency/FullMC_75MeV/check2/Eff_CockWeighted_18_v15_2.root", //102

  "./input/efficiency/FullMC_75MeV/newGen3/Eff_CockWeighted_1617_fine_v1.root", //103
  "./input/efficiency/FullMC_75MeV/newGen3/Eff_CockWeighted_18c_CENT_fine_v1.root", //104
  "./input/efficiency/FullMC_75MeV/newGen3/Eff_CockWeighted_18c_FAST_fine_v1.root", //105

  "./input/efficiency/FullMC_75MeV/newGen3/Eff_CockWeighted_1617_v2.root", //106
  "./input/efficiency/FullMC_75MeV/newGen3/Eff_CockWeighted_18c_CENT_v2.root", //107
  "./input/efficiency/FullMC_75MeV/newGen3/Eff_CockWeighted_18c_FAST_v2.root", //108

  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_16_v3.root", //109
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_17_v3.root", //110
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_18c_CENT_v3.root", //111
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_18c_FAST_v3.root", //112

  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_16_v3_sys1.root", //113
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_17_v3_sys1.root", //114
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_18c_CENT_v3_sys1.root", //115
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_18c_FAST_v3_sys1.root", //116

  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_16_v3_sys2.root", //117
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_17_v3_sys2.root", //118
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_18c_CENT_v3_sys2.root", //119
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_18c_FAST_v3_sys2.root", //120

  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_1617_v3.root", //121
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_1617_v3_sys1.root", //122
  "./input/efficiency/FullMC_75MeV/newGen4/Eff_CockWeighted_1617_v3_sys2.root", //123


  "./input/efficiency/FullMC_75MeV/newGen_sys/Eff_CockWeighted_1617_v3_sys3.root", //124
  "./input/efficiency/FullMC_75MeV/newGen_sys/Eff_CockWeighted_18c_CENT_v3_sys3.root", //125
  "./input/efficiency/FullMC_75MeV/newGen_sys/Eff_CockWeighted_18c_FAST_v3_sys3.root", //126

  "./input/efficiency/FullMC_75MeV/newGen_sys/Eff_CockWeighted_1617_v3_sys4.root", //127
  "./input/efficiency/FullMC_75MeV/newGen_sys/Eff_CockWeighted_18c_CENT_v3_sys4.root", //128
  "./input/efficiency/FullMC_75MeV/newGen_sys/Eff_CockWeighted_18c_FAST_v3_sys4.root", //129

  "./input/efficiency/FullMC_75MeV/newGen_sys/Eff_CockWeighted_1617_v3_sys5.root", //130
  "./input/efficiency/FullMC_75MeV/newGen_sys/Eff_CockWeighted_18c_CENT_v3_sys5.root", //131
  "./input/efficiency/FullMC_75MeV/newGen_sys/Eff_CockWeighted_18c_FAST_v3_sys5.root", //132



  "",
  "",
  "",
  ""
};
// name of 2D generated and reconstructed histogram
TString effi_gen[] = {
  "NGenPairs_pt75",
  "NGenPairs_pt200",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NgenPairsRecResonances:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/charm/NgenPairsRecCharm:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/beauty/NgenPairsRecBeauty",
  "NgenPairsRec",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NgenPairsRecResonances",
  "NgenPairsRecResonances",
  "NgenPairsRecUnity",
  "NgenPairsRecAdded",
  ""
};
TString effi_rec[] = {
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_pt75",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS_pt75",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts600wTOFwoITS_pt75",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts701wTOFwoITS_pt75",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_pt75",
  "NRecPairs_hEff_Ele_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_pt200",
  "NRecPairs_hEff_Ele_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_pt200",
  "NRecPairs_hEff_Ele_pT200_noPF_TrCuts0_PIDCuts701wTOFwoITS_pt200",
  "NRecPairs_hEff_Ele_pT200_noPF_TrCuts0_PIDCuts701wTOFwoITS_SCcut_pt200",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_pt200",
  "NRecPairs_hEff_Ele_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_pt200",  //10
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/charm/NrecoPairsCharm_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/beauty/NrecoPairsRecBeauty_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/charm/NrecoPairsCharm_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/beauty/NrecoPairsRecBeauty_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/charm/NrecoPairsCharm_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/beauty/NrecoPairsRecBeauty_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_pT75_noPF_TrCuts0_PIDCuts100,wTOFwoITS_SCcut_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/charm/NrecoPairsCharm_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0:jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/beauty/NrecoPairsRecBeauty_pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "NrecoPairsRec",
  "jjung_ElectronEfficiency/pairEfficiency/reconstructedBinning/resonances/NrecoPairsRecResonances_pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "NrecoPairsRecResonances",
  "NrecoPairsRecCharm",
  "NrecoPairsRecAdded",
  "NrecoPairsRecEfficiency", //20
  "NrecoPairsRecResonancesSmooth",
  "",
  ""
};

// cocktail files
TString cocktail_files[] = { // TODO: implement correct scaling if files have different centrality percentiles!!!
  // if this order here is changed, then check the use of 'which_cockt_files' in <main>.cpp file!!!
 // "./input/cocktail_LF/LFcocktail_jerome3.root",
 // "./input/cocktail_LF/LFcocktail_carsten2.root",
  //"./input/cocktail_LF/AnalysisResults_merged3.root",
//  "./input/cocktail_LF/LFcocktail_NewResolution75MeV.root",
 // "./input/cocktail_LF/LFcocktail_newVersion.root",
 // "./input/cocktail_LF/LFcocktail_NewVersionNewResolution.root",
  //"./input/cocktail_LF/LFcocktail_NewVersionNewResolution_central.root",
  //"./input/cocktail_LF/LFcocktail_NewVersionNewResolution_low.root",
  //"./input/cocktail_LF/LFcocktail_NewVersionNewResolution_high.root",
 // "./input/cocktail_LF/LFcocktail_v3.root",
  //  "./input/cocktail_LF/LFcocktail_low_75MeV_v2.root",
  //"./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_0404_v1.root",
  //"./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_0404_v1.root",
  //"./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_worseReso_2104_v1.root",
  //"./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_worseReso_2104_v1.root",
  //"./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_betterReso_2104_v1.root",
  //"./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_betterReso_2104_v1.root",
  //     "./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_newPCMEta2_0611_v1.root",
  //     "./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_newPCMEta2_0611_v1.root",
  //     "./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_newEtaPara_1704_test.root",
  //       "./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_newEtaPara_1704_test.root",
  //       "./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_newEtaPara_1704_test.root",
  //       "./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_noRatios_1004.root",
  //       "./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_newEtaPara_1704_test.root",
  //       "./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_newEtaPara_1704_test.root",
  //       "./input/cocktail_LF/LFcocktail_Jerome_75MeV_low_newEtaPara_1704_test.root",

     "./input/cocktail_LF/LFcocktail_CeresLow_v11.root",  //0
     "./input/cocktail_LF/LFcocktail_CeresComb_v11.root",
     "./input/cocktail_LF/LFcocktail_CeresHigh_v11.root",
       "./input/cocktail_LF/LFcocktail_CeresLow_v11.root",
       "./input/cocktail_LF/LFcocktail_CeresComb_v11.root",
       "./input/cocktail_LF/LFcocktail_mTscaling_v11.root",
    "./input/cocktail_LF/LFcocktail_HM_0_10_Comb_v1.root",
    "./input/cocktail_LF/LFcocktail_HM_10_20_Comb_v1.root",
    "./input/cocktail_LF/LFcocktail_HM_20_40_Comb_v1.root",
    "./input/cocktail_LF/LFcocktail_HM_40_70_Comb_v1.root",
    "./input/cocktail_LF/LFcocktail_HM_70_100_Comb_v1.root", //10


     "./input/cocktail_LF/LFcocktail_0_10_newPion_v1.root",
     "./input/cocktail_LF/LFcocktail_10_20_newPion_v1.root",
     "./input/cocktail_LF/LFcocktail_20_40_newPion_v1.root",
     "./input/cocktail_LF/LFcocktail_40_70_newPion_v1.root",
     "./input/cocktail_LF/LFcocktail_70_100_newPion_v1.root",
     "./input/cocktail_LF/LFcocktail_MB_newPion_v1.root",

    "./input/cocktail_LF/LFcocktail_test7_all.root",
    "./input/cocktail_LF/LFcocktail_HM13TeV_all_v4.root",

   // "./input/cocktail_LF/LFcocktail_pi0_test12.root", //19
   // "./input/cocktail_LF/LFcocktail_pi0_up.root", //20
   // "./input/cocktail_LF/LFcocktail_pi0_low.root", //21

    "./input/cocktail_LF/LFcocktail_pi0_comb_v2.root", //19
    "./input/cocktail_LF/LFcocktail_pi0_high_v2.root", //20
    "./input/cocktail_LF/LFcocktail_pi0_low_v2.root", //21



    "./input/cocktail_LF/LFcocktail_pi0_mult_comb_v5.root", //22
    "./input/cocktail_LF/LFcocktail_pi0_mult_high_v5.root", //23
    "./input/cocktail_LF/LFcocktail_pi0_mult_low_v5.root", //24



//  "./input/cocktail_LF/newLF_Cocktail_normalEta_v1.root",
//  "./input/cocktail_LF/newLF_Cocktail_normalEta_v1.root",
//  "./input/cocktail_LF/newLF_Cocktail_mTscalingEta_v1.root",
//  "./input/cocktail_LF/newLF_Cocktail_newPCMEta_v1.root",
//  "./input/cocktail_LF/newLF_Cocktail_newPCMEta_v1.root",
//  "./input/cocktail_LF/newLF_Cocktail_normalEta_v1.root",

  //"./input/cocktail_LF/AnalysisResults_merged_low.root",
  //"./input/cocktail_LF/AnalysisResults_merged_high.root",
  //"./input/cocktail_LF/LFcocktail_Ivan200MeV.root",
  //"./input/cocktail_LF/LFcocktail_ratios_200MeV.root",
  //"./input/cocktail_LF/LFcocktail_AllNew.root",
  //"./input/cocktail_LF/LFcocktail_low_200MeV_v2.root",
  //"./input/cocktail_LF/LFcocktail_nom_200MeV_v3.root",
  "./input/cocktail_LF/LFcocktail_Jerome_200MeV_low_0404_v1.root",
  "./input/cocktail_LF/LFcocktail_Jerome_200MeV_low_0404_v1.root",
  "./input/cocktail_LF/LFcocktail_Jerome_200MeV_low_noRatios_1004_final.root",
  //"./input/cocktail_LF/LFcocktail_v2.root",
  //"./input/cocktail_LF/LFcocktail_v2nom.root",
 // "./input/cocktail_LF/LFcocktail_NewVersionNewResolution_central_200MeV.root",
  //"./input/cocktail_LF/AnalysisResults_merged_low.root",
  //"./input/cocktail_LF/AnalysisResults_merged_high.root",
  "",
  "",
};

TString cocktail_list[] = {
  "LMeeCocktailMC/LMeeCocktailMC_0.80",
  ""
};


// cocktail histograms
TString cocktail_histograms[] = {
//  "pteevsmee_Pi0", //:pteevsmeeJPsi
//  "pteevsmee_Pi0:pteevsmee_Eta:pteevsmee_EtaPrim:pteevsmee_rho0:pteevsmee_omega:pteevsmee_phi", //:pteevsmeeJPsi
//  "pteevsmee_orig_Pi0:pteevsmee_orig_Eta:pteevsmee_orig_EtaP:pteevsmee_orig_Rho:pteevsmee_orig_Omega:pteevsmee_orig_Phi:pteevsmee_orig_Virtual_Photon",
  "pteevsmee_Pi0:pteevsmee_Eta:pteevsmee_EtaP:pteevsmee_Rho:pteevsmee_Omega:pteevsmee_Phi",
  "pteevsmee_Pi0:pteevsmee_EtaP:pteevsmee_Rho:pteevsmee_Omega:pteevsmee_Phi",
  "pteevsmee_Eta",
  "pteevsmee_wALT_Pi0:pteevsmee_wALT_Eta:pteevsmee_wALT_EtaP:pteevsmee_wALT_Rho:pteevsmee_wALT_Omega:pteevsmee_wALT_Phi",

  "pteevsmee_wALT_Pi0_1:pteevsmee_wALT_Eta_1:pteevsmee_wALT_EtaP_1:pteevsmee_wALT_Rho_1:pteevsmee_wALT_Omega_1:pteevsmee_wALT_Phi_1",
  "pteevsmee_wALT_Pi0_2:pteevsmee_wALT_Eta_2:pteevsmee_wALT_EtaP_2:pteevsmee_wALT_Rho_2:pteevsmee_wALT_Omega_2:pteevsmee_wALT_Phi_2",
  "pteevsmee_wALT_Pi0_3:pteevsmee_wALT_Eta_3:pteevsmee_wALT_EtaP_3:pteevsmee_wALT_Rho_3:pteevsmee_wALT_Omega_3:pteevsmee_wALT_Phi_3",
  "pteevsmee_wALT_Pi0_4:pteevsmee_wALT_Eta_4:pteevsmee_wALT_EtaP_4:pteevsmee_wALT_Rho_4:pteevsmee_wALT_Omega_4:pteevsmee_wALT_Phi_4",
  "pteevsmee_wALT_Pi0_5:pteevsmee_wALT_Eta_5:pteevsmee_wALT_EtaP_5:pteevsmee_wALT_Rho_5:pteevsmee_wALT_Omega_5:pteevsmee_wALT_Phi_5",

  "pteevsmee_Pi0:pteevsmee_Eta",
  "pteevsmee_EtaP:pteevsmee_Rho:pteevsmee_Omega:pteevsmee_Phi", //10

  "pteevsmee_wALT_Pi0_1:pteevsmee_wALT_Eta_1",
  "pteevsmee_wALT_EtaP_1:pteevsmee_wALT_Rho_1:pteevsmee_wALT_Omega_1:pteevsmee_wALT_Phi_1",
  "pteevsmee_wALT_Pi0_2:pteevsmee_wALT_Eta_2",
  "pteevsmee_wALT_EtaP_2:pteevsmee_wALT_Rho_2:pteevsmee_wALT_Omega_2:pteevsmee_wALT_Phi_2",
  "pteevsmee_wALT_Pi0_3:pteevsmee_wALT_Eta_3",
  "pteevsmee_wALT_EtaP_3:pteevsmee_wALT_Rho_3:pteevsmee_wALT_Omega_3:pteevsmee_wALT_Phi_3",

  "pteevsmee_wALT_Pi0_6:pteevsmee_wALT_Eta_6:pteevsmee_wALT_EtaP_6:pteevsmee_wALT_Rho_6:pteevsmee_wALT_Omega_6:pteevsmee_wALT_Phi_6",
  "pteevsmee_wALT_Pi0_7:pteevsmee_wALT_Eta_7:pteevsmee_wALT_EtaP_7:pteevsmee_wALT_Rho_7:pteevsmee_wALT_Omega_7:pteevsmee_wALT_Phi_7",
  "pteevsmee_wALT_Pi0_8:pteevsmee_wALT_Eta_8:pteevsmee_wALT_EtaP_8:pteevsmee_wALT_Rho_8:pteevsmee_wALT_Omega_8:pteevsmee_wALT_Phi_8",
  "pteevsmee_wALT_Pi0_9:pteevsmee_wALT_Eta_9:pteevsmee_wALT_EtaP_9:pteevsmee_wALT_Rho_9:pteevsmee_wALT_Omega_9:pteevsmee_wALT_Phi_9", //20
  "pteevsmee_wALT_Pi0_10:pteevsmee_wALT_Eta_10:pteevsmee_wALT_EtaP_10:pteevsmee_wALT_Rho_10:pteevsmee_wALT_Omega_10:pteevsmee_wALT_Phi_10",
  "pteevsmee_wALT_Pi0_11:pteevsmee_wALT_Eta_11:pteevsmee_wALT_EtaP_11:pteevsmee_wALT_Rho_11:pteevsmee_wALT_Omega_11:pteevsmee_wALT_Phi_11",
  "pteevsmee_wALT_Pi0_12:pteevsmee_wALT_Eta_12:pteevsmee_wALT_EtaP_12:pteevsmee_wALT_Rho_12:pteevsmee_wALT_Omega_12:pteevsmee_wALT_Phi_12",
  "pteevsmee_wALT_Pi0_13:pteevsmee_wALT_Eta_13:pteevsmee_wALT_EtaP_13:pteevsmee_wALT_Rho_13:pteevsmee_wALT_Omega_13:pteevsmee_wALT_Phi_13",
  "pteevsmee_wALT_Pi0_14:pteevsmee_wALT_Eta_14:pteevsmee_wALT_EtaP_14:pteevsmee_wALT_Rho_14:pteevsmee_wALT_Omega_14:pteevsmee_wALT_Phi_14",
  "pteevsmee_wALT_Pi0_15:pteevsmee_wALT_Eta_15:pteevsmee_wALT_EtaP_15:pteevsmee_wALT_Rho_15:pteevsmee_wALT_Omega_15:pteevsmee_wALT_Phi_15",




//  "pteevsmee_wEff_Pi0:pteevsmee_wEff_Eta:pteevsmee_wEff_EtaP:pteevsmee_wEff_Rho:pteevsmee_wEff_Omega:pteevsmee_wEff_Phi:pteevsmee_wEff_Virtual_Photon",
  ""
};

//Short useCocktailVersion = 0;



// heavy flavour files
TString heavyfl_files[] = {
//  "input/cocktail_HF/AnalysisResults_charm-pp-kPythiaPerugia11_pp13TeV-300x40000.root:input/cocktail_HF/HFcocktail_beauty.root"
  //  "input/cocktail_HF/HFcocktail_charm_new.root:input/cocktail_HF/HFcocktail_BEAUTY.root"
  //"input/cocktail_HF/newHFcocktail_charm_fine.root:input/cocktail_HF/newHFcocktail_beauty_fine_tot.root",
  "input/cocktail_HF/HFE_charm_POWHEG_pp13TeV.root:input/cocktail_HF/newHFcocktail_beauty_fine_tot.root"
  //"input/cocktail_HF/HFcocktail_charm_newMNR.root:input/cocktail_HF/HFcocktail_BEAUTY.root"
  //"input/cocktail_HF/HFcocktail_charm_nomRes.root:input/cocktail_HF/HFcocktail_BEAUTY.root"
  //"input/cocktail_HF/HFcocktail_charm_noForce.root:input/cocktail_HF/HFcocktail_BEAUTY.root"
};

//TString heavyfl_list = "lowee:lowee";
TString heavyfl_list = "loweepp_LHC17d1_new:lowee";


// heavy flavour histograms
TString heavyfl_histograms[] = {

  "hMeePtee_ULS_eta08_pt075-hMeePtee_LS_eta08_pt075:hMeePtee_ULS_eta08_pt075-hMeePtee_LS_eta08_pt075",
  //"hMeePtee_ULS_eta08_pt075:hMeePtee_ULS_eta08_pt075-hMeePtee_LS_eta08_pt075",

  "hMeePtee_ULS_eta08_pt200-hMeePtee_LS_eta08_pt200:hMeePtee_ULS_eta08_pt200-hMeePtee_LS_eta08_pt200",
  ""
};
// heavy flavour histograms for nevents
TString heavyfl_hist_Nevents[] = {
  "hRapCharmQuarkMethod1:hRapBeautyQuarkMethod1",
  "hNEvents:hNEvents",//"" ,hRapCharmQuarkMethod1
  ""
};

// j/psi files
TString jpsi_files[] = {
  "input/cocktail_jpsi/JPsi-kpp-Std_low.root",
  "input/cocktail_jpsi/JPsi-kpp-Low_low.root",
  "input/cocktail_jpsi/JPsi-kpp-High_low.root",
  //"input/cocktail_jpsi/JPsi-kpp-Std_nom.root",
  //"input/cocktail_jpsi/JPsi-kpp-Low_nom.root",
  //"input/cocktail_jpsi/JPsi-kpp-High_nom.root",
  "input/cocktail_jpsi/jpsi-pp2016f-pt75.root",
  "input/cocktail_jpsi/jpsi-pp2016f-pt200.root"
};

//TString jpsi_list = "Mee_Ptee_angleSmeared";  //_angleSmeared
TString jpsi_list[] = {
  "cocktailPt200rec",
  "cocktailPt075rec",
  ""
};

// j/psi histograms
TString jpsi_histograms[] = {
  "Mee_Ptee_Jpsi_std_angleSmeared",  //_angleSmeared
  "Mee_Ptee_Jpsi_low_angleSmeared",  //_angleSmeared
  "Mee_Ptee_Jpsi_high_angleSmeared",  //_angleSmeared
  "MeePteeJPsi"
};
// j/psi histograms for nevents
TString jspi_hist_Nevents[] = {
  ""
};






TString coll_system = "pp #sqrt{#it{s}} = 13 TeV, #it{B} = 0.2 T";
TString inputhist   = "InvMass_PairPt_PhivPair";
Int_t   inputdim    = 3;
TString projoption  = "yx"; // option="ab" means: a vertical, b horizontal (ROOT-convention)
// text for legend and maybe signal name
TString caption[] = { // do not use a colon(:)!
  "p_{T}>50",                                // (0)
  "p_{T}>50, wtf",                           // (1)
  "p_{T}>150 ,open PID, TOFreq",                         // (2)
  "p_{T}>50, 150<TOFreq<220",                         // (3)
  "p_{T}>50, 160<TOFreq<200",
  "p_{T}>50, new PID cuts",
  "p_{T}>50, new PID",
  "p_{T}>50, newer PID cuts wo muon excl",
  "p_{T}>50, newer PID cuts closed pi",
  "p_{T}>75, newer PID & PF",
  "p_{T}>75, newer PID", //10
  "p_{T}>75, newer PID & PFwPID",   //11
  "p_{T}>75, newer PID & PFwPID wMuon",
  "p_{T}>75, newerer PID & PFwPID",
  "p_{T}>75,TPC only cut out",
  "p_{T}>75, baseline woITS",  //TPC+TOFincl
  "p_{T}>75,TPC+TOFincl+ITSincl",
  "p_{T}>75,TPC+TOFincl, PF",
  "p_{T}>75,TPC+TOFincl, PF&PID",
  "p_{T}>75,TPC+TOFincl+ITSincl, PF",
  "p_{T}>75,TPC+TOFincl+ITSincl, PF&PID",  //20
  "pT200_noPF_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts6wTOFwITS",
  "pT200_PF0_TrCuts0_PIDCuts6wTOFwITS",
  "p_{T}>75, PF0_TrCuts0_PIDCuts6wTOFwITS",
  "p_{T}>75, noPF_TrCuts0_PIDCuts1wTOFwITS",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts1wTOFwITS",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts0wTOFwITS",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_2",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_3",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_4",  //30
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_5",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_6",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts0wTOFwITS_7",
  "p_{T}>75, NewPID, baseline", //34
  "p_{T}>75, NewPID, woMuonCut",
  "p_{T}>75, NewPID, only ITS exclusion",
  "p_{T}>75, NewPID,  PIDCuts3wTOFwITS",
  "p_{T}>75, NewPID,  PIDCuts4wTOFwITS",
  "p_{T}>75, TheoCut6",
  "p_{T}>75, NewPID, baseline wPF incl PID",     //40
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts1wTOFwITS",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts2wTOFwITS",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts3wTOFwITS",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts4wTOFwITS",
  "p_{T}>75, PF0wPID0_TrCuts0_PIDCuts6wTOFwITS",
  "p_{T}>75, NewPID, baseline wPF",
  "p_{T}>75, PF0_TrCuts0_PIDCuts0wTOFwITS_2",
  "p_{T}>75, PF0_TrCuts0_PIDCuts0wTOFwITS_3",
  "p_{T}>75, PF0_TrCuts0_PIDCuts0wTOFwITS_4",
  "p_{T}>75, PF0_TrCuts0_PIDCuts0wTOFwITS_5",  //50
  "p_{T}>75, PF0_TrCuts0_PIDCuts0wTOFwITS_6",
  "p_{T}>75, PF0_TrCuts0_PIDCuts0wTOFwITS_7",
  "p_{T}>75, NewPID, closed Cuts, woMuonCut",
  "p_{T}>75, TheoCut6 & opened TPC cut",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts1wTOFwITS",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts2wTOFwITS",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts0wTOFwITS_2",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts5wTOFwITS",
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts6wTOFwITS",  //60
  "pT75_PF0wInvMass0_TrCuts0_PIDCuts7wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts1wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts2wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts0wTOFwITS_2",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts5wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_PF0wPID0wInvMass0_TrCuts0_PIDCuts7wTOFwITS",
  "InvMass 000 && OpAngle 020",  //"InvMass: 0.00 && OpAngle: 0.020",
  "InvMass 000 && OpAngle 040",  //"InvMass: 0.00 && OpAngle: 0.040",  //70
  "InvMass 000 && OpAngle 060",  //"InvMass: 0.00 && OpAngle: 0.060",
  "InvMass 040 && OpAngle 020",  //"InvMass: 0.04 && OpAngle: 0.020",
  "InvMass 040 && OpAngle 040",  //"InvMass: 0.04 && OpAngle: 0.040",
  "InvMass 000 && OpAngle 060",  //"InvMass: 0.00 && OpAngle: 0.060",
  "InvMass 020 && OpAngle 020",  //"InvMass: 0.02 && OpAngle: 0.020",
  "InvMass 000 && OpAngle 005",
  "InvMass 000 && OpAngle 010",
  "InvMass 000 && OpAngle 015",
  "InvMass 000 && OpAngle 025",
  "InvMass 000 && OpAngle 030",  //80
  "InvMass 200 && OpAngle 020",
  "InvMass 100 && OpAngle 020",
  "InvMass 000 && OpAngle 020",
  "InvMass 000 && OpAngle 050",
  "InvMass 000 && OpAngle 075",
  "InvMass 000 && OpAngle 100",
  "InvMass 000 && OpAngle 150",
  "InvMass 000 && OpAngle 200",
  "InvMass 100 && OpAngle 050",
  "p_{T}>75, PF0wPID0wOp0",      //90
  "p_{T}>75, PF0wPID0wOp10",
  "p_{T}>75, PF0wPID0wOp20",
  "p_{T}>75, PF0wPID0wOp300",
  "p_{T}>75, PF0wPID0wOp40",
  "p_{T}>75, PF0wPID0wOp50",
  "p_{T}>75, PF0wPID0wOp75",
  "p_{T}>75, PF0wOp0",
  "p_{T}>75, PF0wOp10",
  "p_{T}>75, PF0wOp20",
  "p_{T}>75, PF0wOp300",    //100
  "p_{T}>75, PF0wOp40",
  "p_{T}>75, PF0wOp50",
  "p_{T}>75, PF0wOp75",
  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts201wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts202wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts203wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts204wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts205wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts206wTOFwITS",//110

  "p_{T}>75, no PF",
  "p_{T}>75, PFwOp0",
  "p_{T}>75, PFwOp10",
  "p_{T}>75, PFwOp20",
  "p_{T}>75, PFwOp30",
  "p_{T}>75, PFwOp40",
  "p_{T}>75, PFwOp50",

  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts7wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts204wTOFwITS",//120
  "pT75_noPF_TrCuts0_PIDCuts207wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts208wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts601wTOFwITS",

  "p_{T}>75, no PF II",
  "p_{T}>75, PFwOp0",
  "p_{T}>75, PFwPID0wOp0",
  "p_{T}>75, PF neg Value",
  "p_{T}>75, PFwPID0 neg Value",
  "p_{T}>75, PFwOp50_TrCuts0_PIDCuts0wTOFwITS", //130

  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PFwPID0wInvMass40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PFwPID0wInvMass40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PFwPID0wInvMass40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PFwPID0wInvMass40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PFwPID0wInvMass40_TrCuts0wOp40_PIDCuts0wTOFwITS",
  "pT75_PFwPID0wInvMass40_TrCuts0wOp20_PIDCuts0wTOFwITS",

  "p_{T}>75, PFwOp20",
  "p_{T}>75, PFwOp20 wInvMass10",
  "p_{T}>75, PFwOp20 wInvMass20",  //140
  "p_{T}>75, PFwOp20 wInvMass30",
  "p_{T}>75, PFwOp20 wInvMass40",
  "p_{T}>75, PFwOp20 wInvMass50",
  "p_{T}>75, PFwOp20 wInvMass100",

  "pT75_PF0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts7wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts210wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts211wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts212wTOFwITS", //150
  "pT75_PF0wOp20_TrCuts0_PIDCuts213wTOFwITS",

  "pT75_PF0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts6wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts7wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts211wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts212wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts213wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts214wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp0_TrCuts0_PIDCuts0wTOFwITS",  //160
  "pT75_PF0wOp10_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp30_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp40_TrCuts0_PIDCuts0wTOFwITS",
  "pT75_PF0wOp50_TrCuts0_PIDCuts0wTOFwITS",

  "pT200_noPF_TrCuts0_PIDCuts6wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts7wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts0wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts6wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts7wTOFwITS",//170
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwoITS",

  "pT200_noPF_TrCuts0_PIDCuts6wTOFwITS_ref",  //ref
  "pT200_noPF_TrCuts0_PIDCuts7wTOFwITS_ref",
  "pT200_noPF_TrCuts0_PIDCuts0wTOFwITS_ref",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts6wTOFwITS_ref",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts7wTOFwITS_ref",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwITS_ref",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts0wTOFwoITS_ref",

  "p_{T}>200, noPF_PIDCuts6",//180
  "p_{T}>200, noPF_PIDCuts7",
  "p_{T}>200, noPF_PIDCuts0",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts6",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts7",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts0",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts0woITS",

  "p_{T}>200, noPF_PIDCuts6",
  "p_{T}>200, noPF_PIDCuts7",
  "p_{T}>200, noPF_PIDCuts0",
  "p_{T}>200, noPF_PIDCuts10",//190
  "p_{T}>200, noPF_PIDCuts11",
  "p_{T}>200, PF Op20 PID0 low",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts11",

  "p_{T}>200, noPF_PIDCuts7_ref",  //ref
  "p_{T}>200, noPF_PIDCuts10_ref",
  "p_{T}>200, noPF_PIDCuts0_ref",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts7_ref",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts10_ref",
  "p_{T}>200, PF Op20_PID0 ref",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts0woITS_ref",  //200

  "pT75_noPF_TrCuts-1_PIDCuts-1wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwITS",
  "pT75_noPF_TrCuts-1_PIDCuts12wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts12wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts10wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts10wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts10wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts104wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS", //210
  "pT75_noPF_TrCuts0_PIDCuts700wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts601wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts214wTOFwITS",

  "p_{T}>75, PF0 Op20, PID0 low",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts104wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts700wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts600wTOFwITS",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts601wTOFwITS", //220
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts214wTOFwITS",

  "p_{T}>200, noPF_PIDCuts0",  //ref
  "p_{T}>200, noPF_PIDCuts6",
  "p_{T}>200, noPF_PIDCuts700wTOFwITS",
  "p_{T}>200, PF0 Op20, PID0 ref",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts6",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts700wTOFwITS",
  "p_{T}>200, PF0wPID0wOp20_PIDCuts214wTOFwoITS",

  "p_{T}>75, noPF_TrCuts-1_PIDCuts302wTOFwITS",
  "p_{T}>75, noPF Conv. ohne TOF",  //230
  "p_{T}>75, noPF_TrCuts-1_PIDCuts303wTOFwoITS",
  "p_{T}>75, noPF Conv mit TOF",
  "p_{T}>75, noPF_TrCuts0_PIDCuts100wTOFwITS",
  "p_{T}>75, noPF_TrCuts0_PIDCuts100woTOFwITS",
  "p_{T}>75, noPF_TrCuts0_PIDCuts100woTOFwoITS",

  "p_{T}>75,  PF wOp20",
  "p_{T}>100, PF wOp20",
  "p_{T}>125, PF wOp20",
  "p_{T}>150, PF wOp20",
  "p_{T}>175, PF wOp20",   //240
  "p_{T}>200, PF wOp20",
  "p_{T}>100, PF wOp40",

  "pT75_PF0wPID0wOp10_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp30_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp40_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp75_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp100_TrCuts0_PIDCuts100wTOFwITS",

  "p_{T}> 75, noPF PID100 low",  //250
  "p_{T}>100, noPF PID100 low",
  "p_{T}>125, noPF PID100 low",
  "p_{T}>150, noPF PID100 low",
  "p_{T}>175, noPF PID100 low",
  "p_{T}>200, noPF PID100 low",

  "p_{T}>100, noPF PID100 ref",
  "p_{T}>150, noPF PID100 ref",
  "p_{T}>200, noPF PID100 ref",
  "p_{T}>250, noPF PID100 ref",
  "p_{T}>300, noPF PID100 ref",  //260
  "p_{T}>350, noPF PID100 ref",
  "p_{T}>400, noPF PID100 ref",

  "p_{T}>100, noPF PID100 low",
  "p_{T}>150, noPF PID100 low",
  "p_{T}>200, noPF PID100 low",
  "p_{T}>250, noPF PID100 low",
  "p_{T}>300, noPF PID100 low",
  "p_{T}>350, noPF PID100 low",
  "p_{T}>400, noPF PID100 low",

  "p_{T}>100, noPF PID Theo6 low",  //270
  "p_{T}>150, noPF PID Theo6 low",
  "p_{T}>200, noPF PID Theo6 low",
  "p_{T}>250, noPF PID Theo6 low",
  "p_{T}>300, noPF PID Theo6 low",
  "p_{T}>350, noPF PID Theo6 low",
  "p_{T}>400, noPF PID Theo6 low",

  "p_{T}>100, noPF PID Theo6 low, no matching",
  "p_{T}>150, noPF PID Theo6 low, no matching",
  "p_{T}>200, noPF PID Theo6 low, no matching",
  "p_{T}>250, noPF PID Theo6 low, no matching",  //280
  "p_{T}>300, noPF PID Theo6 low, no matching",
  "p_{T}>350, noPF PID Theo6 low, no matching",
  "p_{T}>400, noPF PID Theo6 low, no matching",

  "p_{T}>100, noPF PID Theo6 low, weird",
  "p_{T}>150, noPF PID Theo6 low, weird",
  "p_{T}>200, noPF PID Theo6 low, weird",
  "p_{T}>250, noPF PID Theo6 low, weird",
  "p_{T}>300, noPF PID Theo6 low, weird",
  "p_{T}>350, noPF PID Theo6 low, weird",
  "p_{T}>400, noPF PID Theo6 low, weird",       //290

  "p_{T}>100, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>150, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>200, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>250, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>300, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>350, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>400, noPF PID Theo6 low, InnerTPC momentum",

  "p_{T}>075, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>100, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>110, noPF PID Theo6 low, InnerTPC momentum",  //300
  "p_{T}>120, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>130, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>140, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>150, noPF PID Theo6 low, InnerTPC momentum",

  "p_{T}>075, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>100, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>110, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>120, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>130, noPF PID Theo6 low, InnerTPC momentum",
  "p_{T}>140, noPF PID Theo6 low, InnerTPC momentum",  //310
  "p_{T}>150, noPF PID Theo6 low, InnerTPC momentum",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT90_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT110_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT130_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT90_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",  //320
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT110_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT130_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT90_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT110_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",  //330
  "pT130_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT90_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT110_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT130_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",  //340
  "pT90_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",  //350
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT300_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT140_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT300_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwITS_matchedOnly",  //360

  "p_{T}>75,  PF PID100 low", //wOp20
  "p_{T}>100, PF PID100 low", //wOp20
  "p_{T}>120, PF PID100 low", //wOp20
  "p_{T}>140, PF PID100 low", //wOp20
  "p_{T}>200, PF PID100 low", //wOp20
  "p_{T}>300, PF PID100 low", //wOp20
  "p_{T}>400, PF PID100 low", //wOp20

  "p_{T}>75,  PF PID100 low sCluCut", //wOp20
  "p_{T}>100, PF PID100 low sCluCut", //wOp20
  "p_{T}>120, PF PID100 low sCluCut", //wOp20  //370
  "p_{T}>140, PF PID100 low sCluCut", //wOp20
  "p_{T}>200, PF PID100 low sCluCut", //wOp20
  "p_{T}>300, PF PID100 low sCluCut", //wOp20
  "p_{T}>400, PF PID100 low sCluCut", //wOp20

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_noUpdate",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched_noUpdate",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched_noUpdate",  //380

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_fix1",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched_fix1",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched_fix1",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_fix2",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched_fix2",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched_fix2",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_fix3",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched_fix3",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched_fix3",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_fix4",     //390
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched_fix4",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched_fix4",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_2",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS",   //400
  "pT150_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_OnlyMatched",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS_NotMatched",

  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwoITS",
  "low field, p_{T}>75 MeV",    //410
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwoITS_2",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT150_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwoITS",
  "pT75_PF0wPID0wInvMass10wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "low field, p_{T}>75 MeV, PF",
  "pT100_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "pT100_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS_2",  //420
  "pT120_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "pT150_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "low field, p_{T}>200 MeV, PF",

  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_noPF_TrCuts0_PIDCuts100wTOFwITS_2",
  "pT120_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "pT150_noPF_TrCuts0_PIDCuts100wTOFwITS",
  "nominal field",                             //430

  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts-1wTOFwITS",
  "pT75_PF0wPID0wInvMass10wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT100_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS_2",
  "pT120_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "pT150_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "nominal field & prefilter",

  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",           //440
  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "low field",
  "pT200_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwITS",
  "low field & prefilter, p_{T}>75 MeV",

  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts-1wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts600wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts600wTOFwITS",
  "nominal field",
  "nominal field & prefilter",
  "pT400_noPF_TrCuts0_PIDCuts600wTOFwITS",          //450
  "pT400_PF0wPID0wOp50_TrCuts0_PIDCuts600wTOFwITS",
  "pT100_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwITS",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts110wTOFwoITS",
  "low field & prefilter, p_{T}>75 MeV",
  "pT200_noPF_TrCuts0_PIDCuts600wTOFwoITS",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts600wTOFwoITS",
  "pT200_PF0wPID0wOp75_TrCuts0_PIDCuts100wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts-1wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",           //460
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "nominal field, no prefilter",
  "nominal field with prefilter",
  "pT400_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT400_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT200_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",

  "pT100_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT100_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts701wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts701wTOFwoITS",   //470
  "low field, no prefilter ",
  "low field with prefilter",

  "pT100_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT100_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "low field & PF, p_{T}>75 MeV",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "low field & PF, p_{T}>200 MeV",

  "pT75_noPF_TrCuts0_PIDCuts111wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts111wTOFwITS",    //480
  "pT75_noPF_TrCuts0_PIDCuts800wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts800wTOFwITS",
  "pT75_noPF_TrCuts0_PIDCuts801wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts801wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts802wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts802wTOFwITS",


  "pT75_PF0wPID0wOp20_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp30_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp40_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS",  //490
  "pT75_PF0wPID0wOp60_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_PF0wPID0wOp75_TrCuts0_PIDCuts100wTOFwoITS",

  "pT75_noPF_TrCuts0_PIDCuts303wTOFwoITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts303woTOFwoITS_Conv",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts130wTOFwITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts600wTOFwITS",
  "low field & PF & TOFreq",

  "pT75_noPF_TrCuts0_PIDCuts304wTOFwoITS",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts304wTOFwoITS",  //500

  "pT75_noPF_TrCuts0_PIDCuts303wTOFwoITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts303woTOFwoITS_Conv",

  "pT75_noPF_TrCuts0_PIDCuts303wTOFwoITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts303woTOFwoITS_Conv",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwITS",


  "TPC+TOF",
  "TPC+TOF, prefilter",
  "TPC+TOF+ITS",
  "TPC+TOF+ITS, prefilter", //510
  "pT75_noPF_TrCuts0_PIDCuts120wTOFwITS",
  "Theo6",
  "Theo6, prefilter",

  "New PID",
  "pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts600wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts701wTOFwoITS",
  "New PID & sClusterCut",

  "New PID",
  "New PID", //520
  "low field, LHC16f",

  "p_{T}>75 MeV/c, low field, no PF",
  "p_{T}>200 MeV/c, low field, no PF",
  "p_{T}>75 MeV/c, low field, PF",
  "p_{T}>200 MeV/c, low field, PF",

  "p_{T}>75 MeV/c, low field, no PF",
  "p_{T}>200 MeV/c, low field, no PF",
  "p_{T}>75 MeV/c, low field, PF",
  "p_{T}>200 MeV/c, low field, PF",

  "p_{T}>75 MeV/c, nom field, no PF", //530
  "p_{T}>200 MeV/c, nom field, no PF",
  "p_{T}>75 MeV/c, nom field, PF",
  "p_{T}>200 MeV/c, nom field, PF",


  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "low field, LHC17g",
  "pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts140wTOFwoITS_SCcut",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS", //540
  "low field, new PID",
  "pT200_noPF_TrCuts0_PIDCuts701wTOFwoITS",
  "low field, old PID",

  "low field",
  "low field, ITS SCcut",
  "low field, PF",
  "low field",
  "low field, ITS SCcut",
  "low field, PF",

  "nom field", //550
  "nom field, ITS SCcut",
  "nom field, PF",
  "nom field",
  "nom field, ITS SCcut",
  "nom field, PF",

  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0wOp50v1_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0v2_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0v3_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0v5_TrCuts0_PIDCuts100wTOFwoITS_noV0", //560
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",

  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0", //570
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_SCcut_noV0",

   "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_noV0", //580
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_SCcut_noV0",

  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts142wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_noV0",
  "pT200_noPF_TrCuts0_PIDCuts140wTOFwoITS_SCcut_noV0",

  //"pT75_noPF_TrCuts150_PIDCuts150wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts151_PIDCuts151wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts152_PIDCuts152wTOFwoITS_SCcut_noV0",  //590
  //"pT75_noPF_TrCuts153_PIDCuts153wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts154_PIDCuts154wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts155_PIDCuts155wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts156_PIDCuts156wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts157_PIDCuts157wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts158_PIDCuts158wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts159_PIDCuts159wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts160_PIDCuts160wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts161_PIDCuts161wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts162_PIDCuts162wTOFwoITS_SCcut_noV0",  //600
  //"pT75_noPF_TrCuts163_PIDCuts163wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts164_PIDCuts164wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts165_PIDCuts165wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts166_PIDCuts166wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts167_PIDCuts167wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts168_PIDCuts168wTOFwoITS_SCcut_noV0",
  //"pT75_noPF_TrCuts169_PIDCuts169wTOFwoITS_SCcut_noV0",

  "cut variation 1",
  "cut variation 2",
  "cut variation 3",  //590
  "cut variation 4",
  "cut variation 5",
  "cut variation 6",
  "cut variation 7",
  "cut variation 8",
  "cut variation 9",
  "cut variation 10",
  "cut variation 11",
  "cut variation 12",
  "cut variation 13", //600
  "cut variation 14",
  "cut variation 15",
  "cut variation 16",
  "cut variation 17",
  "cut variation 18",
  "cut variation 19",
  "cut variation 20",
  "cut variation 0",

  "cut variation 21",
  "cut variation 22",  //610
  "cut variation 23",
  "cut variation 24",
  "cut variation 25",
  "cut variation 26",
  "cut variation 27",
  "cut variation 28",
  "cut variation 29",
  "cut variation 30",
  "cut variation 31",
  "cut variation 32",  //620
  "cut variation 33",
  "cut variation 34",
  "cut variation 35",
  "cut variation 36",
  "cut variation 37",
  "cut variation 38",
  "cut variation 39",
  "cut variation 40",
  "cut variation 0",

  "pT75_noPF_TrCuts-1_PIDCuts100wTOFwoITS_SCcut_noV0", //630
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_noPF_TrCuts-1_PIDCuts100wTOFwoITS_noV0",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",

  "pT200_noPF_TrCuts150_PIDCuts150wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts151_PIDCuts151wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts152_PIDCuts152wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts153_PIDCuts153wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts154_PIDCuts154wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts155_PIDCuts155wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts156_PIDCuts156wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts157_PIDCuts157wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts158_PIDCuts158wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts159_PIDCuts159wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts160_PIDCuts160wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts161_PIDCuts161wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts162_PIDCuts162wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts163_PIDCuts163wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts164_PIDCuts164wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts165_PIDCuts165wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts166_PIDCuts166wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts167_PIDCuts167wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts168_PIDCuts168wTOFwoITS_SCcut_noV0",
  "pT200_noPF_TrCuts169_PIDCuts169wTOFwoITS_SCcut_noV0",

  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0wInvMass10wOp50v4_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0wInvMass20v2_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0v3_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_PF0wPID0v8_TrCuts0_PIDCuts100wTOFwoITS_noV0",
  "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0", //660
  "pT75_PF0wPID0wOp50_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass10wOp50v4_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0wInvMass20v2_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0v3_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",
  "pT75_PF0wPID0v8_TrCuts0_PIDCuts100wTOFwoITS_SCcut_noV0",

  ""
};
// config string for manager
TString cconfig[] = { // this determines which settings will really be analysed! check to select the correct cut_setting!
  //cut16 cent
  //(coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[0]  + ":" + caption[0] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[0] ), // pt>50
//  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[1]  + ":" + caption[1] +":"+effi_name[1]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[2]  + ":" + caption[2] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[2] ),
//  (coll_system + ":" + name[0] + ":" + tree_name[0] + ":" + cut_setting[3]  + ":" + caption[3] +":"+effi_name[1]+":"+effi_gen[1]+":"+effi_rec[3] ),
  //cut16 semi
//  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[0]  + ":" + caption[0] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[0] ),
  //(coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[1]  + ":" + caption[1] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ), // closed PID
//  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[2]  + ":" + caption[2] +":"+effi_name[2]+":"+effi_gen[0]+":"+effi_rec[2] ),
//  (coll_system + ":" + name[1] + ":" + tree_name[0] + ":" + cut_setting[3]  + ":" + caption[3] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[3] ),
  //(coll_system + ":" + name[2] + ":" + tree_name[0] + ":" + cut_setting[2]  + ":" + caption[2] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[3] + ":" + tree_name[0] + ":" + cut_setting[3]  + ":" + caption[3] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[4] + ":" + tree_name[0] + ":" + cut_setting[4]  + ":" + caption[4] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[5] + ":" + tree_name[0] + ":" + cut_setting[5]  + ":" + caption[5] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[6] + ":" + tree_name[0] + ":" + cut_setting[6]  + ":" + caption[6] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[7] + ":" + tree_name[0] + ":" + cut_setting[7]  + ":" + caption[7] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[8] + ":" + tree_name[0] + ":" + cut_setting[8]  + ":" + caption[8] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[10] + ":" + tree_name[0] + ":" + cut_setting[10]  + ":" + caption[10] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[9] + ":" + tree_name[0] + ":" + cut_setting[9]  + ":" + caption[9] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[11] + ":" + tree_name[0] + ":" + cut_setting[11]  + ":" + caption[11] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
 // (coll_system + ":" + name[12] + ":" + tree_name[0] + ":" + cut_setting[12]  + ":" + caption[12] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[13] + ":" + tree_name[0] + ":" + cut_setting[13]  + ":" + caption[13] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //
  //(coll_system + ":" + name[14] + ":" + tree_name[0] + ":" + cut_setting[14]  + ":" + caption[14] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[14] + ":" + tree_name[0] + ":" + cut_setting[15]  + ":" + caption[15] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[14] + ":" + tree_name[0] + ":" + cut_setting[16]  + ":" + caption[16] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[14] + ":" + tree_name[0] + ":" + cut_setting[17]  + ":" + caption[17] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[14] + ":" + tree_name[0] + ":" + cut_setting[18]  + ":" + caption[18] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[14] + ":" + tree_name[0] + ":" + cut_setting[19]  + ":" + caption[19] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[14] + ":" + tree_name[0] + ":" + cut_setting[20]  + ":" + caption[20] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID

  //(coll_system + ":" + name[15] + ":" + tree_name[0] + ":" + cut_setting[21]  + ":" + caption[21] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[15] + ":" + tree_name[0] + ":" + cut_setting[22]  + ":" + caption[22] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[15] + ":" + tree_name[0] + ":" + cut_setting[23]  + ":" + caption[23] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[15] + ":" + tree_name[0] + ":" + cut_setting[24]  + ":" + caption[24] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[15] + ":" + tree_name[0] + ":" + cut_setting[25]  + ":" + caption[25] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[15] + ":" + tree_name[0] + ":" + cut_setting[26]  + ":" + caption[26] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID

  //(coll_system + ":" + name[17] + ":" + tree_name[0] + ":" + cut_setting[34]  + ":" + caption[34] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //PF parameter test with PID
  //(coll_system + ":" + name[16] + ":" + tree_name[0] + ":" + cut_setting[27]  + ":" + caption[27] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[16] + ":" + tree_name[0] + ":" + cut_setting[28]  + ":" + caption[28] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[16] + ":" + tree_name[0] + ":" + cut_setting[29]  + ":" + caption[29] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[16] + ":" + tree_name[0] + ":" + cut_setting[30]  + ":" + caption[30] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[16] + ":" + tree_name[0] + ":" + cut_setting[31]  + ":" + caption[31] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[16] + ":" + tree_name[0] + ":" + cut_setting[32]  + ":" + caption[32] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[16] + ":" + tree_name[0] + ":" + cut_setting[33]  + ":" + caption[33] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PI

//  	(coll_system + ":" + name[17] + ":" + tree_name[0] + ":" + cut_setting[34]  + ":" + caption[34] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
//  	(coll_system + ":" + name[17] + ":" + tree_name[0] + ":" + cut_setting[35]  + ":" + caption[35] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
//  	(coll_system + ":" + name[17] + ":" + tree_name[0] + ":" + cut_setting[36]  + ":" + caption[36] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
//  //(coll_system + ":" + name[17] + ":" + tree_name[0] + ":" + cut_setting[37]  + ":" + caption[37] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
//  //(coll_system + ":" + name[17] + ":" + tree_name[0] + ":" + cut_setting[38]  + ":" + caption[38] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
//          (coll_system + ":" + name[22] + ":" + tree_name[0] + ":" + cut_setting[54]  + ":" + caption[53] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  	(coll_system + ":" + name[17] + ":" + tree_name[0] + ":" + cut_setting[39]  + ":" + caption[39] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // THEO PID noPF
//
  //(coll_system + ":" + name[19] + ":" + tree_name[0] + ":" + cut_setting[47]  + ":" + caption[46] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[18] + ":" + tree_name[0] + ":" + cut_setting[40]  + ":" + caption[40] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[18] + ":" + tree_name[0] + ":" + cut_setting[41]  + ":" + caption[41] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[18] + ":" + tree_name[0] + ":" + cut_setting[42]  + ":" + caption[42] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[18] + ":" + tree_name[0] + ":" + cut_setting[43]  + ":" + caption[43] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[18] + ":" + tree_name[0] + ":" + cut_setting[44]  + ":" + caption[44] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[18] + ":" + tree_name[0] + ":" + cut_setting[45]  + ":" + caption[45] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID

  //PF parameter test without PID
  //(coll_system + ":" + name[19] + ":" + tree_name[0] + ":" + cut_setting[47]  + ":" + caption[46] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[19] + ":" + tree_name[0] + ":" + cut_setting[48]  + ":" + caption[47] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[19] + ":" + tree_name[0] + ":" + cut_setting[49]  + ":" + caption[48] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[19] + ":" + tree_name[0] + ":" + cut_setting[50]  + ":" + caption[49] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[19] + ":" + tree_name[0] + ":" + cut_setting[51]  + ":" + caption[50] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[19] + ":" + tree_name[0] + ":" + cut_setting[52]  + ":" + caption[51] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[19] + ":" + tree_name[0] + ":" + cut_setting[53]  + ":" + caption[52] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PI

  //PF parameter test without PID
  //(coll_system + ":" + name[20] + ":" + tree_name[0] + ":" + cut_setting[47]  + ":" + caption[46] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[20] + ":" + tree_name[0] + ":" + cut_setting[48]  + ":" + caption[47] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[20] + ":" + tree_name[0] + ":" + cut_setting[49]  + ":" + caption[48] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[20] + ":" + tree_name[0] + ":" + cut_setting[50]  + ":" + caption[49] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[20] + ":" + tree_name[0] + ":" + cut_setting[51]  + ":" + caption[50] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[20] + ":" + tree_name[0] + ":" + cut_setting[52]  + ":" + caption[51] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[20] + ":" + tree_name[0] + ":" + cut_setting[53]  + ":" + caption[52] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PI

  //PF parameter test without PID
  //(coll_system + ":" + name[21] + ":" + tree_name[0] + ":" + cut_setting[47]  + ":" + caption[46] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[21] + ":" + tree_name[0] + ":" + cut_setting[48]  + ":" + caption[47] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[21] + ":" + tree_name[0] + ":" + cut_setting[49]  + ":" + caption[48] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[21] + ":" + tree_name[0] + ":" + cut_setting[50]  + ":" + caption[49] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[21] + ":" + tree_name[0] + ":" + cut_setting[51]  + ":" + caption[50] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[21] + ":" + tree_name[0] + ":" + cut_setting[52]  + ":" + caption[51] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID
  //(coll_system + ":" + name[21] + ":" + tree_name[0] + ":" + cut_setting[53]  + ":" + caption[52] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PI
  	//(coll_system + ":" + name[22] + ":" + tree_name[0] + ":" + cut_setting[54]  + ":" + caption[53] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //	(coll_system + ":" + name[22] + ":" + tree_name[0] + ":" + cut_setting[55]  + ":" + caption[54] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[23] + ":" + tree_name[0] + ":" + cut_setting[56]  + ":" + caption[55] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[23] + ":" + tree_name[0] + ":" + cut_setting[57]  + ":" + caption[56] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[23] + ":" + tree_name[0] + ":" + cut_setting[58]  + ":" + caption[57] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  ////(coll_system + ":" + name[23] + ":" + tree_name[0] + ":" + cut_setting[59]  + ":" + caption[58] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[23] + ":" + tree_name[0] + ":" + cut_setting[60]  + ":" + caption[59] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[23] + ":" + tree_name[0] + ":" + cut_setting[61]  + ":" + caption[60] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[23] + ":" + tree_name[0] + ":" + cut_setting[62]  + ":" + caption[61] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //
  //(coll_system + ":" + name[24] + ":" + tree_name[0] + ":" + cut_setting[63]  + ":" + caption[62] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[24] + ":" + tree_name[0] + ":" + cut_setting[64]  + ":" + caption[63] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[24] + ":" + tree_name[0] + ":" + cut_setting[65]  + ":" + caption[64] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  ////(coll_system + ":" + name[24] + ":" + tree_name[0] + ":" + cut_setting[66]  + ":" + caption[65] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[24] + ":" + tree_name[0] + ":" + cut_setting[67]  + ":" + caption[66] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[24] + ":" + tree_name[0] + ":" + cut_setting[68]  + ":" + caption[67] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[24] + ":" + tree_name[0] + ":" + cut_setting[69]  + ":" + caption[68] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[25] + ":" + tree_name[0] + ":" + cut_setting[70]  + ":" + caption[69] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[25] + ":" + tree_name[0] + ":" + cut_setting[71]  + ":" + caption[70] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[25] + ":" + tree_name[0] + ":" + cut_setting[72]  + ":" + caption[71] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[25] + ":" + tree_name[0] + ":" + cut_setting[73]  + ":" + caption[72] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[25] + ":" + tree_name[0] + ":" + cut_setting[74]  + ":" + caption[73] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[25] + ":" + tree_name[0] + ":" + cut_setting[75]  + ":" + caption[74] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[25] + ":" + tree_name[0] + ":" + cut_setting[76]  + ":" + caption[75] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[26] + ":" + tree_name[0] + ":" + cut_setting[77]  + ":" + caption[76] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[26] + ":" + tree_name[0] + ":" + cut_setting[78]  + ":" + caption[77] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[26] + ":" + tree_name[0] + ":" + cut_setting[79]  + ":" + caption[78] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[27] + ":" + tree_name[0] + ":" + cut_setting[84]  + ":" + caption[83] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[26] + ":" + tree_name[0] + ":" + cut_setting[80]  + ":" + caption[79] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[26] + ":" + tree_name[0] + ":" + cut_setting[81]  + ":" + caption[80] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[26] + ":" + tree_name[0] + ":" + cut_setting[82]  + ":" + caption[81] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[26] + ":" + tree_name[0] + ":" + cut_setting[83]  + ":" + caption[82] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[27] + ":" + tree_name[0] + ":" + cut_setting[84]  + ":" + caption[83] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[27] + ":" + tree_name[0] + ":" + cut_setting[85]  + ":" + caption[84] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[27] + ":" + tree_name[0] + ":" + cut_setting[86]  + ":" + caption[85] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[27] + ":" + tree_name[0] + ":" + cut_setting[87]  + ":" + caption[86] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[27] + ":" + tree_name[0] + ":" + cut_setting[88]  + ":" + caption[87] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[27] + ":" + tree_name[0] + ":" + cut_setting[89]  + ":" + caption[88] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[27] + ":" + tree_name[0] + ":" + cut_setting[90]  + ":" + caption[89] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[14] + ":" + tree_name[0] + ":" + cut_setting[15]  + ":" + caption[15] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),  // fancy PID

  //(coll_system + ":" + name[28] + ":" + tree_name[0] + ":" + cut_setting[91]  + ":" + caption[90] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[28] + ":" + tree_name[0] + ":" + cut_setting[92]  + ":" + caption[91] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[28] + ":" + tree_name[0] + ":" + cut_setting[93]  + ":" + caption[92] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[28] + ":" + tree_name[0] + ":" + cut_setting[94]  + ":" + caption[93] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[28] + ":" + tree_name[0] + ":" + cut_setting[95]  + ":" + caption[94] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[28] + ":" + tree_name[0] + ":" + cut_setting[96]  + ":" + caption[95] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[28] + ":" + tree_name[0] + ":" + cut_setting[97]  + ":" + caption[96] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[29] + ":" + tree_name[0] + ":" + cut_setting[98]  + ":" + caption[97] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[29] + ":" + tree_name[0] + ":" + cut_setting[99]  + ":" + caption[98] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[29] + ":" + tree_name[0] + ":" + cut_setting[100] + ":" + caption[99] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[29] + ":" + tree_name[0] + ":" + cut_setting[101] + ":" + caption[100]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[29] + ":" + tree_name[0] + ":" + cut_setting[102] + ":" + caption[101]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[29] + ":" + tree_name[0] + ":" + cut_setting[103] + ":" + caption[102]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[29] + ":" + tree_name[0] + ":" + cut_setting[104] + ":" + caption[103]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[30] + ":" + tree_name[0] + ":" + cut_setting[105] + ":" + caption[104] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[30] + ":" + tree_name[0] + ":" + cut_setting[106] + ":" + caption[105] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[30] + ":" + tree_name[0] + ":" + cut_setting[107] + ":" + caption[106] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[30] + ":" + tree_name[0] + ":" + cut_setting[108] + ":" + caption[107]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[30] + ":" + tree_name[0] + ":" + cut_setting[109] + ":" + caption[108]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[30] + ":" + tree_name[0] + ":" + cut_setting[110] + ":" + caption[109]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[30] + ":" + tree_name[0] + ":" + cut_setting[111] + ":" + caption[110]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),


      //(coll_system + ":" + name[33] + ":" + tree_name[0] + ":" + cut_setting[112] + ":" + caption[111] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
      //(coll_system + ":" + name[33] + ":" + tree_name[0] + ":" + cut_setting[113] + ":" + caption[112] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
      //(coll_system + ":" + name[33] + ":" + tree_name[0] + ":" + cut_setting[114] + ":" + caption[113] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
      //(coll_system + ":" + name[33] + ":" + tree_name[0] + ":" + cut_setting[115] + ":" + caption[114]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
      //(coll_system + ":" + name[33] + ":" + tree_name[0] + ":" + cut_setting[116] + ":" + caption[115]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
      //(coll_system + ":" + name[33] + ":" + tree_name[0] + ":" + cut_setting[117] + ":" + caption[116]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
      //(coll_system + ":" + name[33] + ":" + tree_name[0] + ":" + cut_setting[118] + ":" + caption[117]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[34] + ":" + tree_name[0] + ":" + cut_setting[119] + ":" + caption[118] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[34] + ":" + tree_name[0] + ":" + cut_setting[120] + ":" + caption[119] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[34] + ":" + tree_name[0] + ":" + cut_setting[121] + ":" + caption[120] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[34] + ":" + tree_name[0] + ":" + cut_setting[122] + ":" + caption[121]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[34] + ":" + tree_name[0] + ":" + cut_setting[123] + ":" + caption[122]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[34] + ":" + tree_name[0] + ":" + cut_setting[124] + ":" + caption[123]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[34] + ":" + tree_name[0] + ":" + cut_setting[125] + ":" + caption[124]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[35] + ":" + tree_name[0] + ":" + cut_setting[126] + ":" + caption[125] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //   (coll_system + ":" + name[35] + ":" + tree_name[0] + ":" + cut_setting[127] + ":" + caption[126] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //   (coll_system + ":" + name[35] + ":" + tree_name[0] + ":" + cut_setting[128] + ":" + caption[127]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //   (coll_system + ":" + name[35] + ":" + tree_name[0] + ":" + cut_setting[129] + ":" + caption[128]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //   (coll_system + ":" + name[35] + ":" + tree_name[0] + ":" + cut_setting[130] + ":" + caption[129]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[35] + ":" + tree_name[0] + ":" + cut_setting[131] + ":" + caption[130]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[36] + ":" + tree_name[0] + ":" + cut_setting[132] + ":" + caption[131] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[36] + ":" + tree_name[0] + ":" + cut_setting[133] + ":" + caption[132] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[36] + ":" + tree_name[0] + ":" + cut_setting[134] + ":" + caption[133] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[36] + ":" + tree_name[0] + ":" + cut_setting[135] + ":" + caption[134]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[36] + ":" + tree_name[0] + ":" + cut_setting[136] + ":" + caption[135]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[36] + ":" + tree_name[0] + ":" + cut_setting[137] + ":" + caption[136]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[36] + ":" + tree_name[0] + ":" + cut_setting[138] + ":" + caption[137]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //coll_system + ":" + name[37] + ":" + tree_name[0] + ":" + cut_setting[139] + ":" + caption[138] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //coll_system + ":" + name[37] + ":" + tree_name[0] + ":" + cut_setting[140] + ":" + caption[139] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //coll_system + ":" + name[37] + ":" + tree_name[0] + ":" + cut_setting[141] + ":" + caption[140] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //coll_system + ":" + name[37] + ":" + tree_name[0] + ":" + cut_setting[142] + ":" + caption[141]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //coll_system + ":" + name[37] + ":" + tree_name[0] + ":" + cut_setting[143] + ":" + caption[142]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //coll_system + ":" + name[37] + ":" + tree_name[0] + ":" + cut_setting[144] + ":" + caption[143]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //coll_system + ":" + name[37] + ":" + tree_name[0] + ":" + cut_setting[145] + ":" + caption[144]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[38] + ":" + tree_name[0] + ":" + cut_setting[146] + ":" + caption[145] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[38] + ":" + tree_name[0] + ":" + cut_setting[147] + ":" + caption[146] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[38] + ":" + tree_name[0] + ":" + cut_setting[148] + ":" + caption[147] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[38] + ":" + tree_name[0] + ":" + cut_setting[149] + ":" + caption[148]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[38] + ":" + tree_name[0] + ":" + cut_setting[150] + ":" + caption[149]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[38] + ":" + tree_name[0] + ":" + cut_setting[151] + ":" + caption[150]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[38] + ":" + tree_name[0] + ":" + cut_setting[152] + ":" + caption[151]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[153] + ":" + caption[152] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[154] + ":" + caption[153] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[155] + ":" + caption[154] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[156] + ":" + caption[155]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[157] + ":" + caption[156]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[158] + ":" + caption[157]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[39] + ":" + tree_name[0] + ":" + cut_setting[159] + ":" + caption[158]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[160] + ":" + caption[159] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[161] + ":" + caption[160] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[162] + ":" + caption[161] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[163] + ":" + caption[162]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[164] + ":" + caption[163]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[165] + ":" + caption[164]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[40] + ":" + tree_name[0] + ":" + cut_setting[166] + ":" + caption[165]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[41] + ":" + tree_name[0] + ":" + cut_setting[167] + ":" + caption[166] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[41] + ":" + tree_name[0] + ":" + cut_setting[168] + ":" + caption[167] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[41] + ":" + tree_name[0] + ":" + cut_setting[169] + ":" + caption[168] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[41] + ":" + tree_name[0] + ":" + cut_setting[170] + ":" + caption[169]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[41] + ":" + tree_name[0] + ":" + cut_setting[171] + ":" + caption[170]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[41] + ":" + tree_name[0] + ":" + cut_setting[172] + ":" + caption[171]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[41] + ":" + tree_name[0] + ":" + cut_setting[173] + ":" + caption[172]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[174] + ":" + caption[173] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[175] + ":" + caption[174] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[176] + ":" + caption[175] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[177] + ":" + caption[176]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[178] + ":" + caption[177]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[179] + ":" + caption[178]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[42] + ":" + tree_name[0] + ":" + cut_setting[180] + ":" + caption[179]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[181] + ":" + caption[180] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  ////  (coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[182] + ":" + caption[181] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //  (coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[183] + ":" + caption[182] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[184] + ":" + caption[183]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  ////  (coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[185] + ":" + caption[184]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //  (coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[186] + ":" + caption[185]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  ////(coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[187] + ":" + caption[186]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[44] + ":" + tree_name[0] + ":" + cut_setting[188] + ":" + caption[187] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[44] + ":" + tree_name[0] + ":" + cut_setting[189] + ":" + caption[188] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[44] + ":" + tree_name[0] + ":" + cut_setting[190] + ":" + caption[189] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[44] + ":" + tree_name[0] + ":" + cut_setting[191] + ":" + caption[190]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[44] + ":" + tree_name[0] + ":" + cut_setting[192] + ":" + caption[191]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[44] + ":" + tree_name[0] + ":" + cut_setting[193] + ":" + caption[192]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[44] + ":" + tree_name[0] + ":" + cut_setting[194] + ":" + caption[193]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[195] + ":" + caption[194] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[196] + ":" + caption[195] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[197] + ":" + caption[196] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[198] + ":" + caption[197]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[199] + ":" + caption[198]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //  (coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[200] + ":" + caption[199]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[201] + ":" + caption[200]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

    //(coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[182] + ":" + caption[181] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
    //(coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[183] + ":" + caption[182] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
    //(coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[195] + ":" + caption[194] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
    //(coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[197] + ":" + caption[196] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
    //(coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[185] + ":" + caption[184]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
    //(coll_system + ":" + name[43] + ":" + tree_name[0] + ":" + cut_setting[186] + ":" + caption[185]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
    //(coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[198] + ":" + caption[197]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
    //(coll_system + ":" + name[45] + ":" + tree_name[0] + ":" + cut_setting[200] + ":" + caption[199]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[202] + ":" + caption[201] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[203] + ":" + caption[202] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[204] + ":" + caption[203] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[205] + ":" + caption[204]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[206] + ":" + caption[205]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[207] + ":" + caption[206]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[46] + ":" + tree_name[0] + ":" + cut_setting[208] + ":" + caption[207]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[209] + ":" + caption[208] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[210] + ":" + caption[209] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[211] + ":" + caption[210] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[212] + ":" + caption[211]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[213] + ":" + caption[212]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[214] + ":" + caption[213]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[47] + ":" + tree_name[0] + ":" + cut_setting[215] + ":" + caption[214]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[216] + ":" + caption[215] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[217] + ":" + caption[216] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[218] + ":" + caption[217] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[219] + ":" + caption[218]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[220] + ":" + caption[219]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[221] + ":" + caption[220]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[222] + ":" + caption[221]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[223] + ":" + caption[222] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[224] + ":" + caption[223] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[225] + ":" + caption[224] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[226] + ":" + caption[225]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[227] + ":" + caption[226]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[228] + ":" + caption[227]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[229] + ":" + caption[228]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[50] + ":" + tree_name[0] + ":" + cut_setting[230] + ":" + caption[229] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[50] + ":" + tree_name[0] + ":" + cut_setting[231] + ":" + caption[230] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[50] + ":" + tree_name[0] + ":" + cut_setting[232] + ":" + caption[231] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[50] + ":" + tree_name[0] + ":" + cut_setting[233] + ":" + caption[232]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[50] + ":" + tree_name[0] + ":" + cut_setting[234] + ":" + caption[233]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[50] + ":" + tree_name[0] + ":" + cut_setting[235] + ":" + caption[234]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[50] + ":" + tree_name[0] + ":" + cut_setting[236] + ":" + caption[235]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),


  //plot

  //(coll_system + ":" + name[49] + ":" + tree_name[0] + ":" + cut_setting[226] + ":" + caption[225]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[44] + ":" + tree_name[0] + ":" + cut_setting[193] + ":" + caption[192]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[48] + ":" + tree_name[0] + ":" + cut_setting[216] + ":" + caption[215] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[237] + ":" + caption[236] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[238] + ":" + caption[237] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[239] + ":" + caption[238] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[240] + ":" + caption[239]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[241] + ":" + caption[240]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[242] + ":" + caption[241]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[52] + ":" + tree_name[0] + ":" + cut_setting[243] + ":" + caption[242]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[53] + ":" + tree_name[0] + ":" + cut_setting[244] + ":" + caption[243] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[53] + ":" + tree_name[0] + ":" + cut_setting[245] + ":" + caption[244] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[53] + ":" + tree_name[0] + ":" + cut_setting[246] + ":" + caption[245] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[53] + ":" + tree_name[0] + ":" + cut_setting[247] + ":" + caption[246]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[53] + ":" + tree_name[0] + ":" + cut_setting[248] + ":" + caption[247]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[53] + ":" + tree_name[0] + ":" + cut_setting[249] + ":" + caption[248]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[53] + ":" + tree_name[0] + ":" + cut_setting[250] + ":" + caption[249]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[251] + ":" + caption[250] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[252] + ":" + caption[251] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[253] + ":" + caption[252] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[254] + ":" + caption[253] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[255] + ":" + caption[254] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[256] + ":" + caption[255] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[55] + ":" + tree_name[0] + ":" + cut_setting[257] + ":" + caption[256] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[55] + ":" + tree_name[0] + ":" + cut_setting[258] + ":" + caption[257] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[55] + ":" + tree_name[0] + ":" + cut_setting[259] + ":" + caption[258] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[55] + ":" + tree_name[0] + ":" + cut_setting[260] + ":" + caption[259]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[55] + ":" + tree_name[0] + ":" + cut_setting[261] + ":" + caption[260]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[55] + ":" + tree_name[0] + ":" + cut_setting[262] + ":" + caption[261]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[55] + ":" + tree_name[0] + ":" + cut_setting[263] + ":" + caption[262]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),





        //(coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[251] + ":" + caption[250] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//      (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[264] + ":" + caption[263] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//        (coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[253] + ":" + caption[252] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//      (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[265] + ":" + caption[264] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//        (coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[255] + ":" + caption[254] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//      (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[266] + ":" + caption[265] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//      (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[267] + ":" + caption[266]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//      (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[268] + ":" + caption[267]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//      (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[269] + ":" + caption[268]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//      (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[270] + ":" + caption[269]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

 // (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[270] + ":" + caption[269]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[269] + ":" + caption[268]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[266] + ":" + caption[265] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[253] + ":" + caption[252] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[56] + ":" + tree_name[0] + ":" + cut_setting[264] + ":" + caption[263] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[54] + ":" + tree_name[0] + ":" + cut_setting[251] + ":" + caption[250] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),




  //(coll_system + ":" + name[57] + ":" + tree_name[0] + ":" + cut_setting[271] + ":" + caption[270] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[57] + ":" + tree_name[0] + ":" + cut_setting[272] + ":" + caption[271] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[57] + ":" + tree_name[0] + ":" + cut_setting[273] + ":" + caption[272] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[57] + ":" + tree_name[0] + ":" + cut_setting[274] + ":" + caption[273]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[57] + ":" + tree_name[0] + ":" + cut_setting[275] + ":" + caption[274]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[57] + ":" + tree_name[0] + ":" + cut_setting[276] + ":" + caption[275]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[57] + ":" + tree_name[0] + ":" + cut_setting[277] + ":" + caption[276]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
////
//
//
//
//  (coll_system + ":" + name[58] + ":" + tree_name[0] + ":" + cut_setting[278] + ":" + caption[277] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[58] + ":" + tree_name[0] + ":" + cut_setting[279] + ":" + caption[278] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[58] + ":" + tree_name[0] + ":" + cut_setting[280] + ":" + caption[279] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[58] + ":" + tree_name[0] + ":" + cut_setting[281] + ":" + caption[280]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[58] + ":" + tree_name[0] + ":" + cut_setting[282] + ":" + caption[281]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[58] + ":" + tree_name[0] + ":" + cut_setting[283] + ":" + caption[282]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[58] + ":" + tree_name[0] + ":" + cut_setting[284] + ":" + caption[283]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),




 // (coll_system + ":" + name[59] + ":" + tree_name[0] + ":" + cut_setting[285] + ":" + caption[284] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[59] + ":" + tree_name[0] + ":" + cut_setting[286] + ":" + caption[285] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[59] + ":" + tree_name[0] + ":" + cut_setting[287] + ":" + caption[286] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[59] + ":" + tree_name[0] + ":" + cut_setting[288] + ":" + caption[287]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[59] + ":" + tree_name[0] + ":" + cut_setting[289] + ":" + caption[288]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[59] + ":" + tree_name[0] + ":" + cut_setting[290] + ":" + caption[289]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[59] + ":" + tree_name[0] + ":" + cut_setting[291] + ":" + caption[290]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),


  //(coll_system + ":" + name[60] + ":" + tree_name[0] + ":" + cut_setting[292] + ":" + caption[291] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[60] + ":" + tree_name[0] + ":" + cut_setting[293] + ":" + caption[292] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[60] + ":" + tree_name[0] + ":" + cut_setting[294] + ":" + caption[293] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[60] + ":" + tree_name[0] + ":" + cut_setting[295] + ":" + caption[294]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[60] + ":" + tree_name[0] + ":" + cut_setting[296] + ":" + caption[295]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[60] + ":" + tree_name[0] + ":" + cut_setting[297] + ":" + caption[296]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[60] + ":" + tree_name[0] + ":" + cut_setting[298] + ":" + caption[297]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[61] + ":" + tree_name[0] + ":" + cut_setting[299] + ":" + caption[298] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[61] + ":" + tree_name[0] + ":" + cut_setting[300] + ":" + caption[299] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[61] + ":" + tree_name[0] + ":" + cut_setting[301] + ":" + caption[300] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[61] + ":" + tree_name[0] + ":" + cut_setting[302] + ":" + caption[301]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[61] + ":" + tree_name[0] + ":" + cut_setting[303] + ":" + caption[302]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[61] + ":" + tree_name[0] + ":" + cut_setting[304] + ":" + caption[303]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[61] + ":" + tree_name[0] + ":" + cut_setting[305] + ":" + caption[304]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  //(coll_system + ":" + name[62] + ":" + tree_name[0] + ":" + cut_setting[306] + ":" + caption[305] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[62] + ":" + tree_name[0] + ":" + cut_setting[307] + ":" + caption[306] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[62] + ":" + tree_name[0] + ":" + cut_setting[308] + ":" + caption[307] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[62] + ":" + tree_name[0] + ":" + cut_setting[309] + ":" + caption[308]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[62] + ":" + tree_name[0] + ":" + cut_setting[310] + ":" + caption[309]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[62] + ":" + tree_name[0] + ":" + cut_setting[311] + ":" + caption[310]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //(coll_system + ":" + name[62] + ":" + tree_name[0] + ":" + cut_setting[312] + ":" + caption[311]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

 // (coll_system + ":" + name[63] + ":" + tree_name[0] + ":" + cut_setting[313] + ":" + caption[312] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[63] + ":" + tree_name[0] + ":" + cut_setting[314] + ":" + caption[313] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[63] + ":" + tree_name[0] + ":" + cut_setting[315] + ":" + caption[314] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[63] + ":" + tree_name[0] + ":" + cut_setting[316] + ":" + caption[315]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[63] + ":" + tree_name[0] + ":" + cut_setting[317] + ":" + caption[316]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[63] + ":" + tree_name[0] + ":" + cut_setting[318] + ":" + caption[317]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 // (coll_system + ":" + name[63] + ":" + tree_name[0] + ":" + cut_setting[319] + ":" + caption[318]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//  (coll_system + ":" + name[64] + ":" + tree_name[0] + ":" + cut_setting[320] + ":" + caption[319] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[64] + ":" + tree_name[0] + ":" + cut_setting[321] + ":" + caption[320] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[64] + ":" + tree_name[0] + ":" + cut_setting[322] + ":" + caption[321] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[64] + ":" + tree_name[0] + ":" + cut_setting[323] + ":" + caption[322]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[64] + ":" + tree_name[0] + ":" + cut_setting[324] + ":" + caption[323]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[64] + ":" + tree_name[0] + ":" + cut_setting[325] + ":" + caption[324]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[64] + ":" + tree_name[0] + ":" + cut_setting[326] + ":" + caption[325]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

 //(coll_system + ":" + name[65] + ":" + tree_name[0] + ":" + cut_setting[327] + ":" + caption[326] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 //(coll_system + ":" + name[65] + ":" + tree_name[0] + ":" + cut_setting[328] + ":" + caption[327] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 //(coll_system + ":" + name[65] + ":" + tree_name[0] + ":" + cut_setting[329] + ":" + caption[328] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 //(coll_system + ":" + name[65] + ":" + tree_name[0] + ":" + cut_setting[330] + ":" + caption[329]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 //(coll_system + ":" + name[65] + ":" + tree_name[0] + ":" + cut_setting[331] + ":" + caption[330]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 //(coll_system + ":" + name[65] + ":" + tree_name[0] + ":" + cut_setting[332] + ":" + caption[331]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
 //(coll_system + ":" + name[65] + ":" + tree_name[0] + ":" + cut_setting[333] + ":" + caption[332]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

  // (coll_system + ":" + name[66] + ":" + tree_name[0] + ":" + cut_setting[334] + ":" + caption[333] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[66] + ":" + tree_name[0] + ":" + cut_setting[335] + ":" + caption[334] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[66] + ":" + tree_name[0] + ":" + cut_setting[336] + ":" + caption[335] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[66] + ":" + tree_name[0] + ":" + cut_setting[337] + ":" + caption[336]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[66] + ":" + tree_name[0] + ":" + cut_setting[338] + ":" + caption[337]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[66] + ":" + tree_name[0] + ":" + cut_setting[339] + ":" + caption[338]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[66] + ":" + tree_name[0] + ":" + cut_setting[340] + ":" + caption[339]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  //
  // (coll_system + ":" + name[67] + ":" + tree_name[0] + ":" + cut_setting[341] + ":" + caption[340] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[67] + ":" + tree_name[0] + ":" + cut_setting[342] + ":" + caption[341] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[67] + ":" + tree_name[0] + ":" + cut_setting[343] + ":" + caption[342] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[67] + ":" + tree_name[0] + ":" + cut_setting[344] + ":" + caption[343]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[67] + ":" + tree_name[0] + ":" + cut_setting[345] + ":" + caption[344]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[67] + ":" + tree_name[0] + ":" + cut_setting[346] + ":" + caption[345]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
  // (coll_system + ":" + name[67] + ":" + tree_name[0] + ":" + cut_setting[347] + ":" + caption[346]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

// (coll_system + ":" + name[68] + ":" + tree_name[0] + ":" + cut_setting[348] + ":" + caption[347] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[68] + ":" + tree_name[0] + ":" + cut_setting[349] + ":" + caption[348] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[68] + ":" + tree_name[0] + ":" + cut_setting[350] + ":" + caption[349] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[68] + ":" + tree_name[0] + ":" + cut_setting[351] + ":" + caption[350]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[68] + ":" + tree_name[0] + ":" + cut_setting[352] + ":" + caption[351]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[68] + ":" + tree_name[0] + ":" + cut_setting[353] + ":" + caption[352]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[68] + ":" + tree_name[0] + ":" + cut_setting[354] + ":" + caption[353]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

// (coll_system + ":" + name[69] + ":" + tree_name[0] + ":" + cut_setting[355] + ":" + caption[354] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[69] + ":" + tree_name[0] + ":" + cut_setting[356] + ":" + caption[355] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[69] + ":" + tree_name[0] + ":" + cut_setting[357] + ":" + caption[356] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[69] + ":" + tree_name[0] + ":" + cut_setting[358] + ":" + caption[357]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[69] + ":" + tree_name[0] + ":" + cut_setting[359] + ":" + caption[358]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[69] + ":" + tree_name[0] + ":" + cut_setting[360] + ":" + caption[359]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[69] + ":" + tree_name[0] + ":" + cut_setting[361] + ":" + caption[360]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

// (coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[362] + ":" + caption[361] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[363] + ":" + caption[362] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[364] + ":" + caption[363] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[365] + ":" + caption[364]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[366] + ":" + caption[365]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[367] + ":" + caption[366]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
// (coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[368] + ":" + caption[367]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[362] + ":" + caption[361] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[364] + ":" + caption[363] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[368] + ":" + caption[367]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[366] + ":" + caption[365]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[70] + ":" + tree_name[0] + ":" + cut_setting[363] + ":" + caption[362] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),


//(coll_system + ":" + name[71] + ":" + tree_name[0] + ":" + cut_setting[369] + ":" + caption[368] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[71] + ":" + tree_name[0] + ":" + cut_setting[370] + ":" + caption[369] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[71] + ":" + tree_name[0] + ":" + cut_setting[371] + ":" + caption[370] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[71] + ":" + tree_name[0] + ":" + cut_setting[372] + ":" + caption[371]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[71] + ":" + tree_name[0] + ":" + cut_setting[373] + ":" + caption[372]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[71] + ":" + tree_name[0] + ":" + cut_setting[374] + ":" + caption[373]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[71] + ":" + tree_name[0] + ":" + cut_setting[375] + ":" + caption[374]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[72] + ":" + tree_name[0] + ":" + cut_setting[376] + ":" + caption[375]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[72] + ":" + tree_name[0] + ":" + cut_setting[377] + ":" + caption[376]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[72] + ":" + tree_name[0] + ":" + cut_setting[378] + ":" + caption[377]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[73] + ":" + tree_name[0] + ":" + cut_setting[379] + ":" + caption[378]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[73] + ":" + tree_name[0] + ":" + cut_setting[380] + ":" + caption[379]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[73] + ":" + tree_name[0] + ":" + cut_setting[381] + ":" + caption[380]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[74] + ":" + tree_name[0] + ":" + cut_setting[382] + ":" + caption[381]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[74] + ":" + tree_name[0] + ":" + cut_setting[383] + ":" + caption[382]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[74] + ":" + tree_name[0] + ":" + cut_setting[384] + ":" + caption[383]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[75] + ":" + tree_name[0] + ":" + cut_setting[385] + ":" + caption[384]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[75] + ":" + tree_name[0] + ":" + cut_setting[386] + ":" + caption[385]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[75] + ":" + tree_name[0] + ":" + cut_setting[387] + ":" + caption[386]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[76] + ":" + tree_name[0] + ":" + cut_setting[388] + ":" + caption[387]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[76] + ":" + tree_name[0] + ":" + cut_setting[389] + ":" + caption[388]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[76] + ":" + tree_name[0] + ":" + cut_setting[390] + ":" + caption[389]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[77] + ":" + tree_name[0] + ":" + cut_setting[391] + ":" + caption[390]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[77] + ":" + tree_name[0] + ":" + cut_setting[392] + ":" + caption[391]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[77] + ":" + tree_name[0] + ":" + cut_setting[393] + ":" + caption[392]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[78] + ":" + tree_name[0] + ":" + cut_setting[394] + ":" + caption[393]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[78] + ":" + tree_name[0] + ":" + cut_setting[395] + ":" + caption[394]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[78] + ":" + tree_name[0] + ":" + cut_setting[396] + ":" + caption[395]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[79] + ":" + tree_name[0] + ":" + cut_setting[397] + ":" + caption[396] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[79] + ":" + tree_name[0] + ":" + cut_setting[398] + ":" + caption[397] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[79] + ":" + tree_name[0] + ":" + cut_setting[399] + ":" + caption[398] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[79] + ":" + tree_name[0] + ":" + cut_setting[400] + ":" + caption[399]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[79] + ":" + tree_name[0] + ":" + cut_setting[401] + ":" + caption[400]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[79] + ":" + tree_name[0] + ":" + cut_setting[402] + ":" + caption[401]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[79] + ":" + tree_name[0] + ":" + cut_setting[403] + ":" + caption[402]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[80] + ":" + tree_name[0] + ":" + cut_setting[404] + ":" + caption[403]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[80] + ":" + tree_name[0] + ":" + cut_setting[405] + ":" + caption[404]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[80] + ":" + tree_name[0] + ":" + cut_setting[406] + ":" + caption[405]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[81] + ":" + tree_name[0] + ":" + cut_setting[407] + ":" + caption[406]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[81] + ":" + tree_name[0] + ":" + cut_setting[408] + ":" + caption[407]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[81] + ":" + tree_name[0] + ":" + cut_setting[409] + ":" + caption[408]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),


//(coll_system + ":" + name[82] + ":" + tree_name[0] + ":" + cut_setting[410] + ":" + caption[409] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[82] + ":" + tree_name[0] + ":" + cut_setting[411] + ":" + caption[410] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[82] + ":" + tree_name[0] + ":" + cut_setting[412] + ":" + caption[411] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[82] + ":" + tree_name[0] + ":" + cut_setting[413] + ":" + caption[412]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[82] + ":" + tree_name[0] + ":" + cut_setting[414] + ":" + caption[413]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[82] + ":" + tree_name[0] + ":" + cut_setting[415] + ":" + caption[414]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[82] + ":" + tree_name[0] + ":" + cut_setting[416] + ":" + caption[415]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[83] + ":" + tree_name[0] + ":" + cut_setting[417] + ":" + caption[416] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[83] + ":" + tree_name[0] + ":" + cut_setting[418] + ":" + caption[417] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[83] + ":" + tree_name[0] + ":" + cut_setting[419] + ":" + caption[418] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[83] + ":" + tree_name[0] + ":" + cut_setting[420] + ":" + caption[419]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[83] + ":" + tree_name[0] + ":" + cut_setting[421] + ":" + caption[420]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[83] + ":" + tree_name[0] + ":" + cut_setting[422] + ":" + caption[421]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[83] + ":" + tree_name[0] + ":" + cut_setting[423] + ":" + caption[422]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[83] + ":" + tree_name[0] + ":" + cut_setting[424] + ":" + caption[423]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[84] + ":" + tree_name[0] + ":" + cut_setting[425] + ":" + caption[424] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[84] + ":" + tree_name[0] + ":" + cut_setting[426] + ":" + caption[425] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[84] + ":" + tree_name[0] + ":" + cut_setting[427] + ":" + caption[426] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[84] + ":" + tree_name[0] + ":" + cut_setting[428] + ":" + caption[427]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[84] + ":" + tree_name[0] + ":" + cut_setting[429] + ":" + caption[428]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[84] + ":" + tree_name[0] + ":" + cut_setting[430] + ":" + caption[429]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[84] + ":" + tree_name[0] + ":" + cut_setting[431] + ":" + caption[430]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[85] + ":" + tree_name[0] + ":" + cut_setting[432] + ":" + caption[431] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[85] + ":" + tree_name[0] + ":" + cut_setting[433] + ":" + caption[432] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[85] + ":" + tree_name[0] + ":" + cut_setting[434] + ":" + caption[433] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[85] + ":" + tree_name[0] + ":" + cut_setting[435] + ":" + caption[434]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[85] + ":" + tree_name[0] + ":" + cut_setting[436] + ":" + caption[435]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[85] + ":" + tree_name[0] + ":" + cut_setting[437] + ":" + caption[436]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[85] + ":" + tree_name[0] + ":" + cut_setting[438] + ":" + caption[437]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[85] + ":" + tree_name[0] + ":" + cut_setting[439] + ":" + caption[438]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[84] + ":" + tree_name[0] + ":" + cut_setting[431] + ":" + caption[430]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[85] + ":" + tree_name[0] + ":" + cut_setting[439] + ":" + caption[438]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[82] + ":" + tree_name[0] + ":" + cut_setting[411] + ":" + caption[410] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[83] + ":" + tree_name[0] + ":" + cut_setting[419] + ":" + caption[418] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[86] + ":" + tree_name[0] + ":" + cut_setting[440] + ":" + caption[439] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[86] + ":" + tree_name[0] + ":" + cut_setting[441] + ":" + caption[440] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[86] + ":" + tree_name[0] + ":" + cut_setting[442] + ":" + caption[441] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[86] + ":" + tree_name[0] + ":" + cut_setting[443] + ":" + caption[442]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[86] + ":" + tree_name[0] + ":" + cut_setting[444] + ":" + caption[443]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[86] + ":" + tree_name[0] + ":" + cut_setting[445] + ":" + caption[444]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[87] + ":" + tree_name[0] + ":" + cut_setting[446] + ":" + caption[445] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[87] + ":" + tree_name[0] + ":" + cut_setting[447] + ":" + caption[446] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[87] + ":" + tree_name[0] + ":" + cut_setting[448] + ":" + caption[447] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[87] + ":" + tree_name[0] + ":" + cut_setting[449] + ":" + caption[448]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[87] + ":" + tree_name[0] + ":" + cut_setting[450] + ":" + caption[449]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[87] + ":" + tree_name[0] + ":" + cut_setting[451] + ":" + caption[450]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[87] + ":" + tree_name[0] + ":" + cut_setting[452] + ":" + caption[451] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[87] + ":" + tree_name[0] + ":" + cut_setting[453] + ":" + caption[452] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[88] + ":" + tree_name[0] + ":" + cut_setting[454] + ":" + caption[453] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[88] + ":" + tree_name[0] + ":" + cut_setting[455] + ":" + caption[454] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[88] + ":" + tree_name[0] + ":" + cut_setting[456] + ":" + caption[455] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[88] + ":" + tree_name[0] + ":" + cut_setting[457] + ":" + caption[456]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[88] + ":" + tree_name[0] + ":" + cut_setting[458] + ":" + caption[457]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[88] + ":" + tree_name[0] + ":" + cut_setting[459] + ":" + caption[458]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[89] + ":" + tree_name[0] + ":" + cut_setting[460] + ":" + caption[459] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[89] + ":" + tree_name[0] + ":" + cut_setting[461] + ":" + caption[460] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[89] + ":" + tree_name[0] + ":" + cut_setting[462] + ":" + caption[461] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
        //  (coll_system + ":" + name[89] + ":" + tree_name[0] + ":" + cut_setting[463] + ":" + caption[462]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[89] + ":" + tree_name[0] + ":" + cut_setting[464] + ":" + caption[463]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[89] + ":" + tree_name[0] + ":" + cut_setting[465] + ":" + caption[464]+":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[89] + ":" + tree_name[0] + ":" + cut_setting[466] + ":" + caption[465] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[89] + ":" + tree_name[0] + ":" + cut_setting[467] + ":" + caption[466] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[90] + ":" + tree_name[0] + ":" + cut_setting[468] + ":" + caption[467] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[90] + ":" + tree_name[0] + ":" + cut_setting[469] + ":" + caption[468] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[90] + ":" + tree_name[0] + ":" + cut_setting[470] + ":" + caption[469] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[90] + ":" + tree_name[0] + ":" + cut_setting[471] + ":" + caption[470] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
      //  (coll_system + ":" + name[90] + ":" + tree_name[0] + ":" + cut_setting[472] + ":" + caption[471] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[90] + ":" + tree_name[0] + ":" + cut_setting[473] + ":" + caption[472] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//       (coll_system + ":" + name[88] + ":" + tree_name[0] + ":" + cut_setting[456] + ":" + caption[455] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[91] + ":" + tree_name[0] + ":" + cut_setting[474] + ":" + caption[473] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[91] + ":" + tree_name[0] + ":" + cut_setting[475] + ":" + caption[474] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[91] + ":" + tree_name[0] + ":" + cut_setting[476] + ":" + caption[475] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[91] + ":" + tree_name[0] + ":" + cut_setting[477] + ":" + caption[476] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[91] + ":" + tree_name[0] + ":" + cut_setting[478] + ":" + caption[477] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[91] + ":" + tree_name[0] + ":" + cut_setting[479] + ":" + caption[478] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//  (coll_system + ":" + name[91] + ":" + tree_name[0] + ":" + cut_setting[477] + ":" + caption[476] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),


//(coll_system + ":" + name[92] + ":" + tree_name[0] + ":" + cut_setting[480] + ":" + caption[479] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[92] + ":" + tree_name[0] + ":" + cut_setting[481] + ":" + caption[480] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[92] + ":" + tree_name[0] + ":" + cut_setting[482] + ":" + caption[481] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[92] + ":" + tree_name[0] + ":" + cut_setting[483] + ":" + caption[482] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[92] + ":" + tree_name[0] + ":" + cut_setting[484] + ":" + caption[483] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[92] + ":" + tree_name[0] + ":" + cut_setting[485] + ":" + caption[484] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[92] + ":" + tree_name[0] + ":" + cut_setting[486] + ":" + caption[485] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[92] + ":" + tree_name[0] + ":" + cut_setting[487] + ":" + caption[486] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[93] + ":" + tree_name[0] + ":" + cut_setting[488] + ":" + caption[487] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[93] + ":" + tree_name[0] + ":" + cut_setting[489] + ":" + caption[488] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[93] + ":" + tree_name[0] + ":" + cut_setting[490] + ":" + caption[489] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[93] + ":" + tree_name[0] + ":" + cut_setting[491] + ":" + caption[490] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[93] + ":" + tree_name[0] + ":" + cut_setting[492] + ":" + caption[491] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[93] + ":" + tree_name[0] + ":" + cut_setting[493] + ":" + caption[492] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[94] + ":" + tree_name[0] + ":" + cut_setting[494] + ":" + caption[493] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[94] + ":" + tree_name[0] + ":" + cut_setting[495] + ":" + caption[494] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[94] + ":" + tree_name[0] + ":" + cut_setting[496] + ":" + caption[495] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[94] + ":" + tree_name[0] + ":" + cut_setting[497] + ":" + caption[496] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[94] + ":" + tree_name[0] + ":" + cut_setting[498] + ":" + caption[497] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[94] + ":" + tree_name[0] + ":" + cut_setting[499] + ":" + caption[498] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[91] + ":" + tree_name[0] + ":" + cut_setting[477] + ":" + caption[476] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[95] + ":" + tree_name[0] + ":" + cut_setting[500] + ":" + caption[499] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[95] + ":" + tree_name[0] + ":" + cut_setting[501] + ":" + caption[500] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[96] + ":" + tree_name[0] + ":" + cut_setting[502] + ":" + caption[501] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[96] + ":" + tree_name[0] + ":" + cut_setting[503] + ":" + caption[502] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//
//(coll_system + ":" + name[97] + ":" + tree_name[0] + ":" + cut_setting[504] + ":" + caption[503] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[97] + ":" + tree_name[0] + ":" + cut_setting[505] + ":" + caption[504] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[97] + ":" + tree_name[0] + ":" + cut_setting[506] + ":" + caption[505] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[97] + ":" + tree_name[0] + ":" + cut_setting[507] + ":" + caption[506] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[98] + ":" + tree_name[0] + ":" + cut_setting[508] + ":" + caption[507] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[98] + ":" + tree_name[0] + ":" + cut_setting[509] + ":" + caption[508] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[98] + ":" + tree_name[0] + ":" + cut_setting[510] + ":" + caption[509] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[98] + ":" + tree_name[0] + ":" + cut_setting[511] + ":" + caption[510] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[98] + ":" + tree_name[0] + ":" + cut_setting[512] + ":" + caption[511] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[98] + ":" + tree_name[0] + ":" + cut_setting[513] + ":" + caption[512] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),
//(coll_system + ":" + name[98] + ":" + tree_name[0] + ":" + cut_setting[514] + ":" + caption[513] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[1] ),

//(coll_system + ":" + name[99] + ":" + tree_name[0] + ":" + cut_setting[515] + ":" + caption[514] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[0] ),
//(coll_system + ":" + name[99] + ":" + tree_name[0] + ":" + cut_setting[516] + ":" + caption[515] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[1] ),
//(coll_system + ":" + name[99] + ":" + tree_name[0] + ":" + cut_setting[517] + ":" + caption[516] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[2] ),
//(coll_system + ":" + name[99] + ":" + tree_name[0] + ":" + cut_setting[518] + ":" + caption[517] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[3] ),
//(coll_system + ":" + name[99] + ":" + tree_name[0] + ":" + cut_setting[519] + ":" + caption[518] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[4] ),

//(coll_system + ":" + name[100] + ":" + tree_name[0] + ":" + cut_setting[520] + ":" + caption[519] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[0] ),
//(coll_system + ":" + name[100] + ":" + tree_name[0] + ":" + cut_setting[521] + ":" + caption[520] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[1] ),
//(coll_system + ":" + name[100] + ":" + tree_name[0] + ":" + cut_setting[522] + ":" + caption[521] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[4] ),

//(coll_system + ":" + name[101] + ":" + tree_name[0] + ":" + cut_setting[520] + ":" + caption[519] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[0] ),
////(coll_system + ":" + name[101] + ":" + tree_name[0] + ":" + cut_setting[521] + ":" + caption[520] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[1] ),
//(coll_system + ":" + name[101] + ":" + tree_name[0] + ":" + cut_setting[522] + ":" + caption[521] +":"+effi_name[0]+":"+effi_gen[0]+":"+effi_rec[4] ),
//
//(coll_system + ":" + name[102] + ":" + tree_name[0] + ":" + cut_setting[520] + ":" + caption[519] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[0] ),
////(coll_system + ":" + name[102] + ":" + tree_name[0] + ":" + cut_setting[521] + ":" + caption[520] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[1] ),
//(coll_system + ":" + name[102] + ":" + tree_name[0] + ":" + cut_setting[522] + ":" + caption[521] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),


//(coll_system + ":" + name[103] + ":" + tree_name[0] + ":" + cut_setting[523] + ":" + caption[522] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//(coll_system + ":" + name[103] + ":" + tree_name[0] + ":" + cut_setting[524] + ":" + caption[523] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//(coll_system + ":" + name[103] + ":" + tree_name[0] + ":" + cut_setting[525] + ":" + caption[524] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//(coll_system + ":" + name[103] + ":" + tree_name[0] + ":" + cut_setting[526] + ":" + caption[525] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),

//(coll_system + ":" + name[105] + ":" + tree_name[0] + ":" + cut_setting[531] + ":" + caption[530] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//(coll_system + ":" + name[105] + ":" + tree_name[0] + ":" + cut_setting[532] + ":" + caption[531] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//(coll_system + ":" + name[105] + ":" + tree_name[0] + ":" + cut_setting[533] + ":" + caption[532] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//  (coll_system + ":" + name[105] + ":" + tree_name[0] + ":" + cut_setting[534] + ":" + caption[533] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),


//(coll_system + ":" + name[104] + ":" + tree_name[0] + ":" + cut_setting[527] + ":" + caption[526] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//(coll_system + ":" + name[104] + ":" + tree_name[0] + ":" + cut_setting[528] + ":" + caption[527] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//  (coll_system + ":" + name[104] + ":" + tree_name[0] + ":" + cut_setting[529] + ":" + caption[528] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//(coll_system + ":" + name[104] + ":" + tree_name[0] + ":" + cut_setting[530] + ":" + caption[529] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),

//(coll_system + ":" + name[106] + ":" + tree_name[0] + ":" + cut_setting[535] + ":" + caption[534] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//(coll_system + ":" + name[106] + ":" + tree_name[0] + ":" + cut_setting[536] + ":" + caption[535] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//(coll_system + ":" + name[106] + ":" + tree_name[0] + ":" + cut_setting[537] + ":" + caption[536] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),
//(coll_system + ":" + name[106] + ":" + tree_name[0] + ":" + cut_setting[538] + ":" + caption[537] +":"+effi_name[1]+":"+effi_gen[0]+":"+effi_rec[4] ),

//(coll_system + ":" + name[107] + ":" + tree_name[0] + ":" + cut_setting[539] + ":" + caption[538] +":"+effi_name[1]+":"+effi_gen[1]+":"+effi_rec[4] ),
//(coll_system + ":" + name[107] + ":" + tree_name[0] + ":" + cut_setting[540] + ":" + caption[539] +":"+effi_name[1]+":"+effi_gen[1]+":"+effi_rec[4] ),
     //(coll_system + ":" + name[107] + ":" + tree_name[0] + ":" + cut_setting[541] + ":" + caption[540] +":"+effi_name[2]+":"+effi_gen[1]+":"+effi_rec[5] ),

     //(coll_system + ":" + name[107] + ":" + tree_name[0] + ":" + cut_setting[543] + ":" + caption[542] +":"+effi_name[2]+":"+effi_gen[1]+":"+effi_rec[7] ),
       //(coll_system + ":" + name[107] + ":" + tree_name[0] + ":" + cut_setting[544] + ":" + caption[543] +":"+effi_name[2]+":"+effi_gen[1]+":"+effi_rec[8] ),
         // (coll_system + ":" + name[107] + ":" + tree_name[0] + ":" + cut_setting[542] + ":" + caption[541] +":"+effi_name[2]+":"+effi_gen[1]+":"+effi_rec[6] ),
       //(coll_system + ":" + name[107] + ":" + tree_name[0] + ":" + cut_setting[544] + ":" + caption[543] +":"+effi_name[5]+":"+effi_gen[1]+":"+effi_rec[8] ),
//200         (coll_system + ":" + name[107] + ":" + tree_name[0] + ":" + cut_setting[542] + ":" + caption[541] +":"+effi_name[5]+":"+effi_gen[1]+":"+effi_rec[6+4] ),

//(coll_system + ":" + name[108] + ":" + tree_name[0] + ":" + cut_setting[539] + ":" + caption[538] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[4] ),
//(coll_system + ":" + name[108] + ":" + tree_name[0] + ":" + cut_setting[540] + ":" + caption[539] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[4] ),
// (coll_system + ":" + name[108] + ":" + tree_name[0] + ":" + cut_setting[541] + ":" + caption[540] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[5] ),
// (coll_system + ":" + name[108] + ":" + tree_name[0] + ":" + cut_setting[542] + ":" + caption[541] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[6] ),
// (coll_system + ":" + name[108] + ":" + tree_name[0] + ":" + cut_setting[543] + ":" + caption[542] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[7] ),
// (coll_system + ":" + name[108] + ":" + tree_name[0] + ":" + cut_setting[544] + ":" + caption[543] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[8] ),
//


//(coll_system + ":" + name[110] + ":" + tree_name[0] + ":" + cut_setting[551] + ":" + caption[550] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[4] ),
//(coll_system + ":" + name[110] + ":" + tree_name[0] + ":" + cut_setting[552] + ":" + caption[551] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[4] ),
//(coll_system + ":" + name[110] + ":" + tree_name[0] + ":" + cut_setting[553] + ":" + caption[552] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[5] ),
//(coll_system + ":" + name[110] + ":" + tree_name[0] + ":" + cut_setting[554] + ":" + caption[553] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[6] ),
//(coll_system + ":" + name[110] + ":" + tree_name[0] + ":" + cut_setting[555] + ":" + caption[554] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[7] ),
//(coll_system + ":" + name[110] + ":" + tree_name[0] + ":" + cut_setting[556] + ":" + caption[555] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[8] ),


//(coll_system + ":" + name[109] + ":" + tree_name[0] + ":" + cut_setting[545] + ":" + caption[544] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[4] ),
//(coll_system + ":" + name[109] + ":" + tree_name[0] + ":" + cut_setting[546] + ":" + caption[545] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[4] ),
//(coll_system + ":" + name[109] + ":" + tree_name[0] + ":" + cut_setting[547] + ":" + caption[546] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[5] ),
//(coll_system + ":" + name[109] + ":" + tree_name[0] + ":" + cut_setting[548] + ":" + caption[547] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[6] ),
//(coll_system + ":" + name[109] + ":" + tree_name[0] + ":" + cut_setting[549] + ":" + caption[548] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[7] ),
//(coll_system + ":" + name[109] + ":" + tree_name[0] + ":" + cut_setting[550] + ":" + caption[549] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[8] ),

//(coll_system + ":" + name[111] + ":" + tree_name[0] + ":" + cut_setting[557] + ":" + caption[556] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[4] ),
//(coll_system + ":" + name[111] + ":" + tree_name[0] + ":" + cut_setting[558] + ":" + caption[557] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[4] ),
//(coll_system + ":" + name[111] + ":" + tree_name[0] + ":" + cut_setting[559] + ":" + caption[558] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[5] ),
//(coll_system + ":" + name[111] + ":" + tree_name[0] + ":" + cut_setting[560] + ":" + caption[559] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[6] ),
//(coll_system + ":" + name[111] + ":" + tree_name[0] + ":" + cut_setting[561] + ":" + caption[560] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[7] ),
//(coll_system + ":" + name[111] + ":" + tree_name[0] + ":" + cut_setting[562] + ":" + caption[561] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[8] ),

//(coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + cut_setting[563] + ":" + caption[562] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[5] ),
//(coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[563] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[6] ),
//(coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + cut_setting[565] + ":" + caption[564] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[9] ),
//  (coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + cut_setting[566] + ":" + caption[565] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[10] ),

//(coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS_noV0" + ":" + "no SCcut" +":"+effi_name[41]+":"+"NgenPairsRec"+":"+"NrecoPairsRec" ),
//(coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[563] +":"+effi_name[6]+":"+effi_gen[2]+":"+effi_rec[13] ),
//(coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + cut_setting[565] + ":" + caption[564] +":"+effi_name[6]+":"+effi_gen[2]+":"+effi_rec[12] ),
//(coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + cut_setting[566] + ":" + caption[565] +":"+effi_name[6]+":"+effi_gen[2]+":"+effi_rec[12] ),

//(coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[563] + ":" + caption[562] +":"+effi_name[6]+":"+effi_gen[2]+":"+effi_rec[14] ),
//(coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[563] +":"+effi_name[6]+":"+effi_gen[2]+":"+effi_rec[13] ),
//(coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[565] + ":" + caption[564] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[9] ),
//  (coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[566] + ":" + caption[565] +":"+effi_name[3]+":"+effi_gen[1]+":"+effi_rec[10] ),



//(coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[563] + ":" + caption[562] +":"+effi_name[6]+":"+effi_gen[2]+":"+effi_rec[14] ),
//(coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[563] +":"+effi_name[6]+":"+effi_gen[2]+":"+effi_rec[13] ),
//(coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[565] + ":" + caption[564] +":"+effi_name[6]+":"+effi_gen[2]+":"+effi_rec[12] ),
//(coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[566] + ":" + caption[565] +":"+effi_name[6]+":"+effi_gen[2]+":"+effi_rec[12] ),



//(coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + cut_setting[569] + ":" + caption[568] +":"+effi_name[9]+":"+effi_gen[3]+":"+effi_rec[15] ),//200 no Sccut
//(coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[569] + ":" + caption[568] +":"+effi_name[9]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[116] + ":" + tree_name[0] + ":" + cut_setting[578] + ":" + caption[577] +":"+effi_name[11]+":"+effi_gen[4]+":"+effi_rec[16] ), //200 nominal pileup rej
//(coll_system + ":" + name[117] + ":" + tree_name[0] + ":" + cut_setting[584] + ":" + caption[583] +":"+effi_name[11]+":"+effi_gen[4]+":"+effi_rec[16] ),

//(coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + cut_setting[570] + ":" + caption[569] +":"+effi_name[7]+":"+effi_gen[3]+":"+effi_rec[15] ),//200 SCcut
//(coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[570] + ":" + caption[569] +":"+effi_name[7]+":"+effi_gen[3]+":"+effi_rec[15] ),


//(coll_system + ":" + name[111] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[563] +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ), //75 QA
//(coll_system + ":" + nameMC[0] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "MC"         +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ), //75 SCcut

//(coll_system + ":" + name[112] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[563] +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[113] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[563] +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17, new eff" +":"+effi_name[42]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17, new eff weighted" +":"+effi_name[43]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17, Reso eff only       " +":"+effi_name[47]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17, HF eff only       " +":"+effi_name[48]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18,    new eff weighted" +":"+effi_name[44]+":"+effi_gen[3]+":"+effi_rec[15] ),
// (coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18, eff  weighted" +":"+effi_name[45]+":"+effi_gen[3]+":"+effi_rec[15] ),
// (coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18, eff  weighted" +":"+effi_name[45]+":"+effi_gen[3]+":"+effi_gen[3] ),
// (coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18, eff  weighted & filled" +":"+effi_name[46]+":"+effi_gen[3]+":"+effi_rec[15] ),
//   (coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18, eff  weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18, eff  weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_gen[3] ),
//(coll_system + ":" + name[131] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18, eff  weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17" +":"+effi_name[56]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 reso" +":"+effi_name[56]+":"+effi_gen[3]+":"+effi_rec[17] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 charm" +":"+effi_name[56]+":"+effi_gen[3]+":"+effi_rec[18] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 reso" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[17] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 charm" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[18] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 added" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[19] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 reso old" +":"+effi_name[58]+":"+effi_gen[3]+":"+effi_rec[15] ),
// (coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 reso new" +":"+effi_name[58]+":"+effi_gen[6]+":"+effi_rec[20] ),
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 reso new" +":"+effi_name[57]+":"+effi_gen[5]+":"+effi_rec[17] ),

//      (coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17, eff  weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//      (coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18wSDD, eff  weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
      //(coll_system + ":" + name[155] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18fast, eff  weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//      (coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17, eff  weighted" +":"+effi_name[57]+":"+effi_gen[3]+":" +effi_gen[3] ),
//      (coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18wSDD, eff  weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_gen[3] ),
//      (coll_system + ":" + name[155] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18fast, eff  weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_gen[3] ),

//smooth
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17, eff  weighted" +":"+effi_name[68]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18wSDD, eff  weighted" +":"+effi_name[67]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[155] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18fast, eff  weighted" +":"+effi_name[66]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_gen[3] ),
//(coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18wSDD, eff  weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_gen[3] ),
//(coll_system + ":" + name[155] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18fast, eff  weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_gen[3] ),

//(coll_system + ":" + name[154] + ":" + tree_name[0] + ":" + cut_setting[654] + ":" + "Data 18woSDD, eff weighted" +":"+effi_name[59]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[154] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18woSDD, eff  weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[154] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18woSDD, eff  weighted" +":"+effi_name[60]+":"+effi_gen[7]+":"+effi_rec[19] ),
//(coll_system + ":" + name[154] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18woSDD, eff  charm" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[18] ),
//(coll_system + ":" + name[154] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18woSDD, eff  reso" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[17] ),
//(coll_system + ":" + name[154] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18woSDD, eff  reso" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[21] ),

//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17wSDD weighted" +":"+effi_name[62]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18wSDD, eff  weighted" +":"+effi_name[61]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[155] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18fast, eff  weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17wSDD eff charm" +":"+effi_name[62]+":"+effi_gen[3]+":"+effi_rec[18] ),
//(coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18wSDD, eff charm" +":"+effi_name[61]+":"+effi_gen[3]+":"+effi_rec[18] ),
//(coll_system + ":" + name[155] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18fast, eff charm" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[18] ),

//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17wSDD eff reso" +":"+effi_name[62]+":"+effi_gen[3]+":"+effi_rec[17] ),
//(coll_system + ":" + name[138] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18wSDD, eff reso" +":"+effi_name[61]+":"+effi_gen[3]+":"+effi_rec[17] ),
//(coll_system + ":" + name[155] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18fast, eff reso" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[17] ),


//(coll_system + ":" + name[139] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17, 0" +":"+effi_name[49]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[140] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 16/17, 1" +":"+effi_name[50]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[141] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 16/17, 2" +":"+effi_name[51]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[142] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 16/17, 3" +":"+effi_name[52]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[143] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 16/17, 4" +":"+effi_name[53]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[144] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 16/17, 5" +":"+effi_name[54]+":"+effi_gen[3]+":"+effi_rec[15] ),


//(coll_system + ":" + name[130] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 Fast+CentwoSDD" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[131] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 CENT" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[132] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 CENTwoSDD" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[133] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 FAST" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[134] + ":" + tree_name[0] + ":" + cut_setting[653] + ":" + "Data 18" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[135] + ":" + tree_name[0] + ":" + cut_setting[654] + ":" + "Data 18 FAST" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[136] + ":" + tree_name[0] + ":" + cut_setting[654] + ":" + "Data 18 CENTwoSDD" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[137] + ":" + tree_name[0] + ":" + cut_setting[654] + ":" + "Data 18 CENT" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),



//(coll_system + ":" + name[114] + ":" + tree_name[0] + ":" + cut_setting[572] + ":" + caption[571] +":"+effi_name[12]+":"+effi_gen[3]+":"+effi_rec[15] ), //200 pileup rej
//(coll_system + ":" + name[115] + ":" + tree_name[0] + ":" + cut_setting[572] + ":" + caption[571] +":"+effi_name[12]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "data, no #phi_{V} corr." +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//  (coll_system + ":" + nameMC[0] + ":" + tree_name[0] + ":" + cut_setting[564]+pairMC[1] + ":" + "MC,same Mother" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ), //75 SCcut
//  (coll_system + ":" + nameMC[0] + ":" + tree_name[0] + ":" + cut_setting[564]+pairMC[3] + ":" + "MC,same Gamma" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ), //75 SCcut
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "data, template correction" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "data, flat corr" +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ), //75

//(coll_system + ":" + nameMC[0] + ":" + tree_name[0] + ":" + cut_setting[570]+pairMC[1] + ":" + "MC,same Mother" +":"+effi_name[7]+":"+effi_gen[3]+":"+effi_rec[15]),  //200) SCcut
//(coll_system + ":" + nameMC[0] + ":" + tree_name[0] + ":" + cut_setting[570]+pairMC[3] + ":" + "MC,same Gamma" +":"+effi_name[7]+":"+effi_gen[3]+":"+effi_rec[15]),  //200) SCcut

//(coll_system + ":" + name[122] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[563] +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[563] +":"+effi_name[35]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[608] +":"+effi_name[36]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
////
////
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[589] + ":" + caption[588] +":"+effi_name[14]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[590] + ":" + caption[589] +":"+effi_name[15]+":"+effi_gen[3]+":"+effi_rec[15] ),
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[591] + ":" + caption[590] +":"+effi_name[16]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[592] + ":" + caption[591] +":"+effi_name[17]+":"+effi_gen[3]+":"+effi_rec[15] ),
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[593] + ":" + caption[592] +":"+effi_name[18]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[594] + ":" + caption[593] +":"+effi_name[19]+":"+effi_gen[3]+":"+effi_rec[15] ),
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[595] + ":" + caption[594] +":"+effi_name[20]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[596] + ":" + caption[595] +":"+effi_name[21]+":"+effi_gen[3]+":"+effi_rec[15] ),
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[597] + ":" + caption[596] +":"+effi_name[22]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[598] + ":" + caption[597] +":"+effi_name[23]+":"+effi_gen[3]+":"+effi_rec[15] ),
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[599] + ":" + caption[598] +":"+effi_name[24]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[600] + ":" + caption[599] +":"+effi_name[25]+":"+effi_gen[3]+":"+effi_rec[15] ),
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[601] + ":" + caption[600] +":"+effi_name[26]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[602] + ":" + caption[601] +":"+effi_name[27]+":"+effi_gen[3]+":"+effi_rec[15] ),
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[603] + ":" + caption[602] +":"+effi_name[28]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[604] + ":" + caption[603] +":"+effi_name[29]+":"+effi_gen[3]+":"+effi_rec[15] ),
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[605] + ":" + caption[604] +":"+effi_name[30]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[606] + ":" + caption[605] +":"+effi_name[31]+":"+effi_gen[3]+":"+effi_rec[15] ),
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[607] + ":" + caption[606] +":"+effi_name[32]+":"+effi_gen[3]+":"+effi_rec[15] ),
//  (coll_system + ":" + name[123] + ":" + tree_name[0] + ":" + cut_setting[608] + ":" + caption[607] +":"+effi_name[33]+":"+effi_gen[3]+":"+effi_rec[15] ),

   //  (coll_system + ":" + name[210] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] +":"+"./input/acceptance/ppToyMCpairAcc_pt75_pt75_v5.root"+":"+"NGenPairs_eta2pt0"+":"+"NGenPairs_pt1_75-pt2_75" ),
//   (coll_system + ":" + name[220] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted PF" +":"+effi_name[74]+":"+effi_gen[3]+":"+effi_rec[15] ),


   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[673] + ":" + caption[588] +":"+effi_name[77]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[674] + ":" + caption[589] +":"+effi_name[78]+":"+effi_gen[3]+":"+effi_rec[15] ),
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[675] + ":" + caption[590] +":"+effi_name[79]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[676] + ":" + caption[591] +":"+effi_name[80]+":"+effi_gen[3]+":"+effi_rec[15] ),
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[677] + ":" + caption[592] +":"+effi_name[81]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[678] + ":" + caption[593] +":"+effi_name[82]+":"+effi_gen[3]+":"+effi_rec[15] ),
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[679] + ":" + caption[594] +":"+effi_name[83]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[680] + ":" + caption[595] +":"+effi_name[84]+":"+effi_gen[3]+":"+effi_rec[15] ),
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[681] + ":" + caption[596] +":"+effi_name[85]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[682] + ":" + caption[597] +":"+effi_name[86]+":"+effi_gen[3]+":"+effi_rec[15] ),
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[683] + ":" + caption[598] +":"+effi_name[87]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[684] + ":" + caption[599] +":"+effi_name[88]+":"+effi_gen[3]+":"+effi_rec[15] ),
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[685] + ":" + caption[600] +":"+effi_name[89]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[686] + ":" + caption[601] +":"+effi_name[90]+":"+effi_gen[3]+":"+effi_rec[15] ),
// (coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[687] + ":" + caption[602] +":"+effi_name[91]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[688] + ":" + caption[603] +":"+effi_name[92]+":"+effi_gen[3]+":"+effi_rec[15] ),
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[689] + ":" + caption[604] +":"+effi_name[93]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[690] + ":" + caption[605] +":"+effi_name[94]+":"+effi_gen[3]+":"+effi_rec[15] ),
   //(coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[691] + ":" + caption[606] +":"+effi_name[95]+":"+effi_gen[3]+":"+effi_rec[15] ),
//   (coll_system + ":" + name[253] + ":" + tree_name[0] + ":" + cut_setting[692] + ":" + caption[607] +":"+effi_name[96]+":"+effi_gen[3]+":"+effi_rec[15] ),


//
// (coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[609] + ":" + caption[608] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[609]+":"+effi_rec[15]+"_"+ cut_setting[609] ), //75
// (coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[610] + ":" + caption[609] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[610]+":"+effi_rec[15]+"_"+ cut_setting[610] ),
// (coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[611] + ":" + caption[610] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[611]+":"+effi_rec[15]+"_"+ cut_setting[611] ), //75
// (coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[612] + ":" + caption[611] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[612]+":"+effi_rec[15]+"_"+ cut_setting[612] ),
// (coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[613] + ":" + caption[612] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[613]+":"+effi_rec[15]+"_"+ cut_setting[613] ), //75
// (coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[614] + ":" + caption[613] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[614]+":"+effi_rec[15]+"_"+ cut_setting[614] ),
// (coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[615] + ":" + caption[614] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[615]+":"+effi_rec[15]+"_"+ cut_setting[615] ), //75
// (coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[616] + ":" + caption[615] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[616]+":"+effi_rec[15]+"_"+ cut_setting[616] ),
//(coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[617] + ":" + caption[616] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[617]+":"+effi_rec[15]+"_"+ cut_setting[617] ), //75
//(coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[618] + ":" + caption[617] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[618]+":"+effi_rec[15]+"_"+ cut_setting[618] ),
//(coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[619] + ":" + caption[618] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[619]+":"+effi_rec[15]+"_"+ cut_setting[619] ), //75
// (coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[620] + ":" + caption[619] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[620]+":"+effi_rec[15]+"_"+ cut_setting[620] ),
//(coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[621] + ":" + caption[620] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[621]+":"+effi_rec[15]+"_"+ cut_setting[621] ), //75
//(coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[622] + ":" + caption[621] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[622]+":"+effi_rec[15]+"_"+ cut_setting[622] ),
//(coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[623] + ":" + caption[622] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[623]+":"+effi_rec[15]+"_"+ cut_setting[623] ), //75
//(coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[624] + ":" + caption[623] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[624]+":"+effi_rec[15]+"_"+ cut_setting[624] ),
// (coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[625] + ":" + caption[624] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[625]+":"+effi_rec[15]+"_"+ cut_setting[625] ), //75
//(coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[626] + ":" + caption[625] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[626]+":"+effi_rec[15]+"_"+ cut_setting[626] ),
//(coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[627] + ":" + caption[626] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[627]+":"+effi_rec[15]+"_"+ cut_setting[627] ),
//(coll_system + ":" + name[124] + ":" + tree_name[0] + ":" + cut_setting[628] + ":" + caption[627] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),

//(coll_system + ":" + name[125] + ":" + tree_name[0] + ":" + cut_setting[629] + ":" + caption[630] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),
//(coll_system + ":" + name[125] + ":" + tree_name[0] + ":" + cut_setting[630] + ":" + "Data - After track cuts" +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),
//(coll_system + ":" + name[125] + ":" + tree_name[0] + ":" + cut_setting[631] + ":" + "Data - Before track cuts" +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),
//(coll_system + ":" + name[125] + ":" + tree_name[0] + ":" + cut_setting[632] + ":" + caption[633] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),

//(coll_system + ":" + nameMC[1] + ":" + tree_name[0] + ":" + cut_setting[629] + ":" + caption[630] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),
//(coll_system + ":" + nameMC[1] + ":" + tree_name[0] + ":" + cut_setting[630] + ":" + "MC - After track cuts" +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),
//(coll_system + ":" + nameMC[1] + ":" + tree_name[0] + ":" + cut_setting[631] + ":" + "MC - Before track cuts" +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),
//(coll_system + ":" + nameMC[1] + ":" + tree_name[0] + ":" + cut_setting[632] + ":" + caption[633] +":"+effi_name[38]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),


//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[633] + ":" + caption[634] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[633]+":"+effi_rec[15]+"_"+ cut_setting[633] ), //200
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[634] + ":" + caption[635] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[634]+":"+effi_rec[15]+"_"+ cut_setting[634] ),
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[635] + ":" + caption[636] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[635]+":"+effi_rec[15]+"_"+ cut_setting[635] ), //200
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[636] + ":" + caption[637] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[636]+":"+effi_rec[15]+"_"+ cut_setting[636] ),
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[637] + ":" + caption[638] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[637]+":"+effi_rec[15]+"_"+ cut_setting[637] ), //200
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[638] + ":" + caption[639] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[638]+":"+effi_rec[15]+"_"+ cut_setting[638] ),
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[639] + ":" + caption[640] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[639]+":"+effi_rec[15]+"_"+ cut_setting[639] ), //200
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[640] + ":" + caption[641] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[640]+":"+effi_rec[15]+"_"+ cut_setting[640] ),
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[641] + ":" + caption[642] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[641]+":"+effi_rec[15]+"_"+ cut_setting[641] ), //200
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[642] + ":" + caption[643] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[642]+":"+effi_rec[15]+"_"+ cut_setting[642] ),
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[643] + ":" + caption[644] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[643]+":"+effi_rec[15]+"_"+ cut_setting[643] ), //200
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[644] + ":" + caption[645] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[644]+":"+effi_rec[15]+"_"+ cut_setting[644] ),
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[645] + ":" + caption[646] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[645]+":"+effi_rec[15]+"_"+ cut_setting[645] ), //200
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[646] + ":" + caption[647] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[646]+":"+effi_rec[15]+"_"+ cut_setting[646] ),
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[647] + ":" + caption[648] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[647]+":"+effi_rec[15]+"_"+ cut_setting[647] ), //200
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[648] + ":" + caption[649] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[648]+":"+effi_rec[15]+"_"+ cut_setting[648] ),
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[649] + ":" + caption[650] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[649]+":"+effi_rec[15]+"_"+ cut_setting[649] ), //200
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[650] + ":" + caption[651] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[650]+":"+effi_rec[15]+"_"+ cut_setting[650] ),
//(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[651] + ":" + caption[652] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[651]+":"+effi_rec[15]+"_"+ cut_setting[651] ),
////(coll_system + ":" + name[126] + ":" + tree_name[0] + ":" + cut_setting[652] + ":" + caption[653] +":"+effi_name[39]+":"+effi_gen[3]+"_"+ cut_setting[652]+":"+effi_rec[15]+"_"+ cut_setting[652] ),


//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[608] +":"+effi_name[36]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[589] + ":" + caption[588] +":"+effi_name[14]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[590] + ":" + caption[589] +":"+effi_name[15]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[591] + ":" + caption[590] +":"+effi_name[16]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[592] + ":" + caption[591] +":"+effi_name[17]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[593] + ":" + caption[592] +":"+effi_name[18]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[594] + ":" + caption[593] +":"+effi_name[19]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[595] + ":" + caption[594] +":"+effi_name[20]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[596] + ":" + caption[595] +":"+effi_name[21]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[597] + ":" + caption[596] +":"+effi_name[22]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[598] + ":" + caption[597] +":"+effi_name[23]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[599] + ":" + caption[598] +":"+effi_name[24]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[600] + ":" + caption[599] +":"+effi_name[25]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[601] + ":" + caption[600] +":"+effi_name[26]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[602] + ":" + caption[601] +":"+effi_name[27]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[603] + ":" + caption[602] +":"+effi_name[28]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[604] + ":" + caption[603] +":"+effi_name[29]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[605] + ":" + caption[604] +":"+effi_name[30]+":"+effi_gen[3]+":"+effi_rec[15] ), //75
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[606] + ":" + caption[605] +":"+effi_name[31]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[607] + ":" + caption[606] +":"+effi_name[32]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[127] + ":" + tree_name[0] + ":" + cut_setting[608] + ":" + caption[607] +":"+effi_name[33]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + caption[608] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[564]+":"+effi_rec[15] +"_"+ cut_setting[564] ), //75
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[609] + ":" + caption[608] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[609]+":"+effi_rec[15]+"_"+ cut_setting[609] ), //75
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[610] + ":" + caption[609] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[610]+":"+effi_rec[15]+"_"+ cut_setting[610] ),
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[611] + ":" + caption[610] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[611]+":"+effi_rec[15]+"_"+ cut_setting[611] ), //75
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[612] + ":" + caption[611] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[612]+":"+effi_rec[15]+"_"+ cut_setting[612] ),
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[613] + ":" + caption[612] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[613]+":"+effi_rec[15]+"_"+ cut_setting[613] ), //75
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[614] + ":" + caption[613] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[614]+":"+effi_rec[15]+"_"+ cut_setting[614] ),
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[615] + ":" + caption[614] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[615]+":"+effi_rec[15]+"_"+ cut_setting[615] ), //75
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[616] + ":" + caption[615] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[616]+":"+effi_rec[15]+"_"+ cut_setting[616] ),
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[617] + ":" + caption[616] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[617]+":"+effi_rec[15]+"_"+ cut_setting[617] ), //75
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[618] + ":" + caption[617] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[618]+":"+effi_rec[15]+"_"+ cut_setting[618] ),
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[619] + ":" + caption[618] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[619]+":"+effi_rec[15]+"_"+ cut_setting[619] ), //75
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[620] + ":" + caption[619] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[620]+":"+effi_rec[15]+"_"+ cut_setting[620] ),
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[621] + ":" + caption[620] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[621]+":"+effi_rec[15]+"_"+ cut_setting[621] ), //75
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[622] + ":" + caption[621] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[622]+":"+effi_rec[15]+"_"+ cut_setting[622] ),
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[623] + ":" + caption[622] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[623]+":"+effi_rec[15]+"_"+ cut_setting[623] ), //75
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[624] + ":" + caption[623] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[624]+":"+effi_rec[15]+"_"+ cut_setting[624] ),
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[625] + ":" + caption[624] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[625]+":"+effi_rec[15]+"_"+ cut_setting[625] ), //75
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[626] + ":" + caption[625] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[626]+":"+effi_rec[15]+"_"+ cut_setting[626] ),
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[627] + ":" + caption[626] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[627]+":"+effi_rec[15]+"_"+ cut_setting[627] ),
//(coll_system + ":" + name[128] + ":" + tree_name[0] + ":" + cut_setting[628] + ":" + caption[627] +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),

//(coll_system + ":" + name[129] + ":" + tree_name[0] + ":" + "pT75_noPF_TrCuts0_PIDCuts100wTOFwoITS" + ":" + "analysis cuts pT75" +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),
//(coll_system + ":" + name[129] + ":" + tree_name[0] + ":" + "pT200_noPF_TrCuts0_PIDCuts100wTOFwoITS" + ":" + "analysis cuts pT200" +":"+effi_name[40]+":"+effi_gen[3]+"_"+ cut_setting[628]+":"+effi_rec[15]+"_"+ cut_setting[628] ),


//(coll_system + ":" + name[146] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "XeXe Data pT>75MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[147] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "XeXe Data pT>75MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[148] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "XeXe Data pT>75MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[149] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "XeXe Data pT>75MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[150] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "XeXe Data pT>75MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[151] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "XeXe Data pT>75MeV" +":"+effi_name[43]+":"+effi_gen[3]+":"+effi_rec[15]),
//(coll_system + ":" + name[152] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "XeXe Data pT>75MeV" +":"+effi_name[43]+":"+effi_gen[3]+":"+effi_rec[15]),
//(coll_system + ":" + name[153] + ":" + tree_name[7] + ":" + cut_setting[564] + ":" + "XeXe Data pT>75MeV"  +":"+effi_name[43]+":"+effi_gen[3]+":"+effi_rec[15]),



//(coll_system + ":" + name[146] + ":" + tree_name[0] + ":" + cut_setting[566] + ":" + "XeXe Data pT>200MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[147] + ":" + tree_name[1] + ":" + cut_setting[566] + ":" + "XeXe Data pT>200MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[148] + ":" + tree_name[2] + ":" + cut_setting[566] + ":" + "XeXe Data pT>200MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[149] + ":" + tree_name[3] + ":" + cut_setting[566] + ":" + "XeXe Data pT>200MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[150] + ":" + tree_name[4] + ":" + cut_setting[566] + ":" + "XeXe Data pT>200MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[151] + ":" + tree_name[5] + ":" + cut_setting[566] + ":" + "XeXe Data pT>200MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[152] + ":" + tree_name[6] + ":" + cut_setting[566] + ":" + "XeXe Data pT>200MeV" +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[153] + ":" + tree_name[7] + ":" + cut_setting[566] + ":" + "XeXe Data pT>200MeV" +":"+""+":"+""+":"+"" ),


//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[658] + ":" + caption[654] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[659] + ":" + caption[655] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[660] + ":" + caption[656] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[661] + ":" + caption[657] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[662] + ":" + caption[658] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[663] + ":" + caption[659] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[664] + ":" + caption[660] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[665] + ":" + caption[661] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[666] + ":" + caption[662] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[667] + ":" + caption[663] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[668] + ":" + caption[664] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[669] + ":" + caption[665] +":"+""+":"+""+":"+"" ),

//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[658] + ":" + caption[654] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[659] + ":" + caption[655] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[660] + ":" + caption[656] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[661] + ":" + caption[657] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[662] + ":" + caption[658] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[663] + ":" + caption[659] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[664] + ":" + caption[660] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[665] + ":" + caption[661] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[666] + ":" + caption[662] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[667] + ":" + caption[663] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[668] + ":" + caption[664] +":"+""+":"+""+":"+"" ),
//(coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[669] + ":" + caption[665] +":"+""+":"+""+":"+"" ),


 // (coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[664] + ":" + caption[660] +":"+""+":"+""+":"+"" ),
 // (coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[664] + ":" + caption[660] +":"+""+":"+""+":"+"" ),
 // (coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[665] + ":" + caption[661] +":"+""+":"+""+":"+"" ),
 // (coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[665] + ":" + caption[661] +":"+""+":"+""+":"+"" ),
 // (coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[666] + ":" + caption[662] +":"+""+":"+""+":"+"" ),
 // (coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[666] + ":" + caption[662] +":"+""+":"+""+":"+"" ),
 // (coll_system + ":" + name[157] + ":" + tree_name[0] + ":" + cut_setting[667] + ":" + caption[663] +":"+""+":"+""+":"+"" ),
//  (coll_system + ":" + name[158] + ":" + tree_name[0] + ":" + cut_setting[667] + ":" + caption[663] +":"+""+":"+""+":"+"" ),

//(coll_system + ":" + name[159] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + caption[563] +":"+effi_name[8]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[182] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16 MB weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[183] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 17 MB weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[160] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 MB weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[159] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 17 HM weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[160] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 MB weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[184] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 MB weighted post" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[181] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 16/17 MBx2 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[162] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD MB weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[175] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18fast MB  weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//////
//(coll_system + ":" + name[160] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 16/17 0-5 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[162] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 0-5 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[175] + ":" + tree_name[1] + ":" + cut_setting[655] + ":" + "Data 18fast MB 0-5 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[160] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 16/17 5-10 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[162] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 5-10 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[175] + ":" + tree_name[2] + ":" + cut_setting[655] + ":" + "Data 18fast MB 5-10 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[160] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 16/17 10-15 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[162] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 10-15 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[175] + ":" + tree_name[3] + ":" + cut_setting[655] + ":" + "Data 18fast MB 10-15 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//
//(coll_system + ":" + name[160] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 16/17 15-20 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[162] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 15-20 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[175] + ":" + tree_name[4] + ":" + cut_setting[655] + ":" + "Data 18fast MB 15-20 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[160] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 16/17 20-30 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[162] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 20-30 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[175] + ":" + tree_name[5] + ":" + cut_setting[655] + ":" + "Data 18fast MB 20-30 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[160] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 16/17 30-40 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[162] + ":" + tree_name[6] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 30-40 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[175] + ":" + tree_name[6] + ":" + cut_setting[655] + ":" + "Data 18fast MB 30-40 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//
//(coll_system + ":" + name[160] + ":" + tree_name[7] + ":" + cut_setting[564] + ":" + "Data 16/17 40-50 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[162] + ":" + tree_name[7] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 40-50 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[175] + ":" + tree_name[7] + ":" + cut_setting[655] + ":" + "Data 18fast MB 40-50 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[160] + ":" + tree_name[8] + ":" + cut_setting[564] + ":" + "Data 16/17 50-70 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[162] + ":" + tree_name[8] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 50-70 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[175] + ":" + tree_name[8] + ":" + cut_setting[655] + ":" + "Data 18fast MB 50-70 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[160] + ":" + tree_name[9] + ":" + cut_setting[564] + ":" + "Data 16/17 70-100 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[162] + ":" + tree_name[9] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 70-100 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[175] + ":" + tree_name[9] + ":" + cut_setting[655] + ":" + "Data 18fast MB 70-100 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),




//(coll_system + ":" + name[163] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 0-10 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[168] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 0-10 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[176] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18 FAST 0-10 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[164] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 10-20 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[169] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 10-20 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[177] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18 FAST 10-20 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[165] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 20-40 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[170] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 20-40 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[178] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18 FAST 20-40 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[166] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 40-70 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[171] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 40-70 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[179] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18 FAST 40-70 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[167] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 70-100 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[172] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 70-100 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[180] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 18 FAST 70-100 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),


//(coll_system + ":" + name[173] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 0-20 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[174] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 CentwSDD 0-20 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),


//(coll_system + ":" + name[185] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 MB weighted" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[186] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 0-10 weighted" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[187] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 10-20 weighted" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[188] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 20-40 weighted" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[189] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 40-70 weighted" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[190] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 70-100 weighted" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[190] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 70-100 weighted" +":"+effi_name[70]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[190] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 70-100 weighted" +":"+effi_name[71]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[191] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 MB weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[191] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 16/17 0-10 post pileup" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[191] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 16/17 10-20 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[191] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 16/17 20-40 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[191] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 16/17 40-70 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[191] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 16/17 70-100 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),


//(coll_system + ":" + name[192] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 CENT MB weighted"     +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[192] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 16/17/18 CENT 0-10 weighted"   +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[192] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 16/17/18 CENT 10-20 weighted"  +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[192] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 16/17/18 CENT 20-40 weighted"  +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[192] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 16/17/18 CENT 40-70 weighted"  +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[192] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 16/17/18 CENT 70-100 weighted" +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[193] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 MB weighted"     +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[193] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 16/17/18 0-10 weighted"   +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[193] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 16/17/18 10-20 weighted"  +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[193] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 16/17/18 20-40 weighted"  +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[193] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 16/17/18 40-70 weighted"  +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[193] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 16/17/18 70-100 weighted" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[194] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 MB weighted"     +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[194] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 18 CENT 0-10 weighted"   +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[194] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 16/17/18 10-20 weighted"  +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[194] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 16/17/18 20-40 weighted"  +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[194] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 16/17/18 40-70 weighted"  +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[194] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 16/17/18 70-100 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[195] + ":" + tree_name[0] + ":" + cut_setting[655] + ":" + "Data 16/17/18 MB weighted"     +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[195] + ":" + tree_name[1] + ":" + cut_setting[655] + ":" + "Data 18 FAST 0-10 weighted"   +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[195] + ":" + tree_name[2] + ":" + cut_setting[655] + ":" + "Data 16/17/18 10-20 weighted"  +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[195] + ":" + tree_name[3] + ":" + cut_setting[655] + ":" + "Data 16/17/18 20-40 weighted"  +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[195] + ":" + tree_name[4] + ":" + cut_setting[655] + ":" + "Data 16/17/18 40-70 weighted"  +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[195] + ":" + tree_name[5] + ":" + cut_setting[655] + ":" + "Data 16/17/18 70-100 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//
//(coll_system + ":" + name[196] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 MB weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[197] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 16/17 0-10 post pileup" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[197] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 16/17 10-20 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[197] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 16/17 20-40 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[197] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 16/17 40-70 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[197] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 16/17 70-100 weighted" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[202] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 MB FAST" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[204] + ":" + tree_name[1] + ":" + cut_setting[655] + ":" + "Data 16/17 0-10 post pileup" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[204] + ":" + tree_name[2] + ":" + cut_setting[655] + ":" + "Data 16/17 10-20 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[204] + ":" + tree_name[3] + ":" + cut_setting[655] + ":" + "Data 16/17 20-40 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[204] + ":" + tree_name[4] + ":" + cut_setting[655] + ":" + "Data 16/17 40-70 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[204] + ":" + tree_name[5] + ":" + cut_setting[655] + ":" + "Data 16/17 70-100 weighted" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[203] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 18 MB CENT" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[205] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 16/17 0-10 post pileup" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[205] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 16/17 10-20 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[205] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 16/17 20-40 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[205] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 16/17 40-70 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[205] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 16/17 70-100 weighted" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[198] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 CENT MB weighted" +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[199] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 16/17 0-10 post pileup" +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[199] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 16/17 10-20 weighted" +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[199] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 16/17 20-40 weighted" +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[199] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 16/17 40-70 weighted" +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[199] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 16/17 70-100 weighted" +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[200] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 MB " +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[201] + ":" + tree_name[1] + ":" + cut_setting[564] + ":" + "Data 16/17/18 0-10 " +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[201] + ":" + tree_name[2] + ":" + cut_setting[564] + ":" + "Data 16/1718 10-20 " +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[201] + ":" + tree_name[3] + ":" + cut_setting[564] + ":" + "Data 16/17/18 20-40 weighted" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[201] + ":" + tree_name[4] + ":" + cut_setting[564] + ":" + "Data 16/17/18 40-70 " +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[201] + ":" + tree_name[5] + ":" + cut_setting[564] + ":" + "Data 16/17/18 70-100 " +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),

//


//(coll_system + ":" + name[206] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17 MB weighted PF" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[208] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 Cent MB weighted PF" +":"+effi_name[72]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[210] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 MB PF" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[214] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-10 PF" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[215] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 10-20 PF" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[216] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 20-40 PF" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[217] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 40-70 PF" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[218] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 70-100 PF" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[213] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-20 PF" +":"+effi_name[69]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[212] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 17 HM" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),

//(coll_system + ":" + name[219] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17 MB weighted PF" +":"+effi_name[57]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[220] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted PF" +":"+effi_name[55]+":"+effi_gen[3]+":"+effi_rec[15] ),
////(coll_system + ":" + name[220] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted PF" +":"+effi_name[61]+":"+effi_gen[3]+":"+effi_rec[15] ),
//(coll_system + ":" + name[221] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 FAST MB weighted PF" +":"+effi_name[60]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[219] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17 MB weighted PF" +":"+effi_name[73]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
    (coll_system + ":" + name[220] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted PF" +":"+effi_name[74]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
    (coll_system + ":" + name[221] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 FAST MB weighted PF" +":"+effi_name[75]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

       (coll_system + ":" + name[210] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data all" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),


    (coll_system + ":" + name[214] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-10 PF" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[215] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 10-20 PF" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[216] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 20-40 PF" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[217] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 40-70 PF" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[218] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 70-100 PF" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[196] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17 MB weighted" +":"+effi_name[73]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[210] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 MB PF" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_gen[3] ),

    (coll_system + ":" + name[222] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-40 PF" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[223] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 40-100 PF" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[224] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17 0-10 weighted PF" +":"+effi_name[73]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[225] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17 0-10 weighted PF" +":"+effi_name[74]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[226] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17 0-10 weighted PF" +":"+effi_name[75]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[213] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-20 PF" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[229] + ":" + tree_name[1] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-10 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[229] + ":" + tree_name[1] + ":" + cut_setting[671] + ":" + "Data 16/17/18 0-10 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[229] + ":" + tree_name[1] + ":" + cut_setting[672] + ":" + "Data 16/17/18 0-10 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[229] + ":" + tree_name[2] + ":" + cut_setting[670] + ":" + "Data 16/17/18 10-20 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[229] + ":" + tree_name[2] + ":" + cut_setting[671] + ":" + "Data 16/17/18 10-20 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[229] + ":" + tree_name[2] + ":" + cut_setting[672] + ":" + "Data 16/17/18 10-20 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[229] + ":" + tree_name[3] + ":" + cut_setting[670] + ":" + "Data 16/17/18 20-40 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[229] + ":" + tree_name[3] + ":" + cut_setting[671] + ":" + "Data 16/17/18 20-40 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[229] + ":" + tree_name[3] + ":" + cut_setting[672] + ":" + "Data 16/17/18 20-40 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[230] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-40 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[231] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-40 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[232] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-40 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[233] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-20 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[234] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-20 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[235] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-20 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[236] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 0-20% V0M " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[237] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 0-20% V0M & iso (S_{0}^{#{p}_{T}=1}>0.83)" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[238] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 0-20% V0M & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[239] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-40 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[240] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-40 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[241] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-40 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[242] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Spherocity integrated" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[243] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Isotrope (S_{0}^{#it{p}_{T}=1}>0.83)" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[244] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Jetty (S_{0}^{#it{p}_{T}=1}<0.62)" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

  //___________________________________________________________________________________________________________________________________________________________________________________
    (coll_system + ":" + name[245] + ":" + tree_name[1] + ":" + cut_setting[670] + ":" + "Data 16/17/18 0-10 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[245] + ":" + tree_name[1] + ":" + cut_setting[671] + ":" + "Data 16/17/18 0-10 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[245] + ":" + tree_name[1] + ":" + cut_setting[672] + ":" + "Data 16/17/18 0-10 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[245] + ":" + tree_name[2] + ":" + cut_setting[670] + ":" + "Data 16/17/18 10-20 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[245] + ":" + tree_name[2] + ":" + cut_setting[671] + ":" + "Data 16/17/18 10-20 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[245] + ":" + tree_name[2] + ":" + cut_setting[672] + ":" + "Data 16/17/18 10-20 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[245] + ":" + tree_name[3] + ":" + cut_setting[670] + ":" + "Data 16/17/18 20-40 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[245] + ":" + tree_name[3] + ":" + cut_setting[671] + ":" + "Data 16/17/18 20-40 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[245] + ":" + tree_name[3] + ":" + cut_setting[672] + ":" + "Data 16/17/18 20-40 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[245] + ":" + tree_name[4] + ":" + cut_setting[670] + ":" + "Data 16/17/18 40-70 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[245] + ":" + tree_name[4] + ":" + cut_setting[671] + ":" + "Data 16/17/18 40-70 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[245] + ":" + tree_name[4] + ":" + cut_setting[672] + ":" + "Data 16/17/18 40-70 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[245] + ":" + tree_name[5] + ":" + cut_setting[670] + ":" + "Data 16/17/18 70-100 PF " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[245] + ":" + tree_name[5] + ":" + cut_setting[671] + ":" + "Data 16/17/18 70-100 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[245] + ":" + tree_name[5] + ":" + cut_setting[672] + ":" + "Data 16/17/18 70-100 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

  //___________________________________________________________________________________________________________________________________________________________________________________
    (coll_system + ":" + name[246] + ":" + tree_name[1] + ":" + cut_setting[670] + ":" + "MC 16/17/18 0-10 PF integrated" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[246] + ":" + tree_name[1] + ":" + cut_setting[671] + ":" + "MC 16/17/18 0-10 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[246] + ":" + tree_name[1] + ":" + cut_setting[672] + ":" + "MC 16/17/18 0-10 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),


    (coll_system + ":" + name[246] + ":" + tree_name[2] + ":" + cut_setting[670] + ":" + "MC 16/17/18 10-20 PF integrated" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[246] + ":" + tree_name[2] + ":" + cut_setting[671] + ":" + "MC 16/17/18 10-20 PF & jetty" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[246] + ":" + tree_name[2] + ":" + cut_setting[672] + ":" + "MC 16/17/18 10-20 PF & iso" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[247] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "MC Spherocity integrated" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[248] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "MC Isotrope (S_{0}^{#it{p}_{T}=1}>0.83)" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[249] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "MC Jetty (S_{0}^{#it{p}_{T}=1}<0.62)" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    (coll_system + ":" + name[250] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "MC 0-10 Spherocity integrated" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[251] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "MC 0-10 Isotrope (S_{0}^{#it{p}_{T}=1}>0.83)" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    (coll_system + ":" + name[252] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "MC 0-10 Jetty (S_{0}^{#it{p}_{T}=1}<0.62)" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),


    (coll_system + ":" + name[259] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted PF" +":"+effi_name[97]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
    (coll_system + ":" + name[260] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted PF" +":"+effi_name[98]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),


    (coll_system + ":" + name[200] + ":" + tree_name[0] + ":" + cut_setting[564] + ":" + "Data 16/17/18 " +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ), //69

    (coll_system + ":" + name[263] + ":" + tree_name[0] + ":" + cut_setting[694] + ":" + "Data 18 CENT base" +":"+effi_name[99]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
    (coll_system + ":" + name[263] + ":" + tree_name[0] + ":" + cut_setting[695] + ":" + "Data 18 CENT PID cluster" +":"+effi_name[100]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
    (coll_system + ":" + name[263] + ":" + tree_name[0] + ":" + cut_setting[696] + ":" + "Data 18 CENT geom length1" +":"+effi_name[101]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
    (coll_system + ":" + name[263] + ":" + tree_name[0] + ":" + cut_setting[697] + ":" + "Data 18 CENT geom length2" +":"+effi_name[102]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),


    //(coll_system + ":" + name[254] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "merged" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

    //(coll_system + ":" + name[255] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "16f" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    //(coll_system + ":" + name[256] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "17g" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    //(coll_system + ":" + name[257] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "18c FAST" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),
    //(coll_system + ":" + name[258] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "18c CENT" +":"+effi_name[76]+":"+effi_gen[3]+":"+effi_rec[15] ),

 //75
  (coll_system + ":" + name[265] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[97]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[264] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[98]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

    //(coll_system + ":" + name[266] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17 MB weighted new PF" +":"+effi_name[73]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[266] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[74]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[267] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[75]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),


  (coll_system + ":" + name[265] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[106]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[264] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[106]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  //  //(coll_system + ":" + name[266] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16/17 MB weighted new PF" +":"+effi_name[73]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[266] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[107]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[267] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[108]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),


  // sys checks
  (coll_system + ":" + name[269] + ":" + tree_name[0] + ":" + cut_setting[700] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[268] + ":" + tree_name[0] + ":" + cut_setting[700] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  (coll_system + ":" + name[270] + ":" + tree_name[0] + ":" + cut_setting[700] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[111]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[271] + ":" + tree_name[0] + ":" + cut_setting[701] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[112]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // sys checks
  (coll_system + ":" + name[269] + ":" + tree_name[0] + ":" + cut_setting[702] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[122]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[268] + ":" + tree_name[0] + ":" + cut_setting[702] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[122]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  (coll_system + ":" + name[270] + ":" + tree_name[0] + ":" + cut_setting[702] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[115]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[271] + ":" + tree_name[0] + ":" + cut_setting[703] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[116]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // sys checks
  (coll_system + ":" + name[269] + ":" + tree_name[0] + ":" + cut_setting[704] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[123]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[268] + ":" + tree_name[0] + ":" + cut_setting[704] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[123]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  (coll_system + ":" + name[270] + ":" + tree_name[0] + ":" + cut_setting[704] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[119]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[271] + ":" + tree_name[0] + ":" + cut_setting[705] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[120]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),




 // // sys checks
  //(coll_system + ":" + name[273] + ":" + tree_name[0] + ":" + cut_setting[706] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  //(coll_system + ":" + name[272] + ":" + tree_name[0] + ":" + cut_setting[706] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  //(coll_system + ":" + name[274] + ":" + tree_name[0] + ":" + cut_setting[706] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[111]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  //(coll_system + ":" + name[275] + ":" + tree_name[0] + ":" + cut_setting[707] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[112]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  //// sys checks
  //(coll_system + ":" + name[273] + ":" + tree_name[0] + ":" + cut_setting[708] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[122]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  //(coll_system + ":" + name[272] + ":" + tree_name[0] + ":" + cut_setting[708] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[122]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  //(coll_system + ":" + name[274] + ":" + tree_name[0] + ":" + cut_setting[708] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[115]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  //(coll_system + ":" + name[275] + ":" + tree_name[0] + ":" + cut_setting[709] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[116]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  //// sys checks
  //(coll_system + ":" + name[273] + ":" + tree_name[0] + ":" + cut_setting[710] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[123]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  //(coll_system + ":" + name[272] + ":" + tree_name[0] + ":" + cut_setting[710] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[123]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  //(coll_system + ":" + name[274] + ":" + tree_name[0] + ":" + cut_setting[710] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[119]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  //(coll_system + ":" + name[275] + ":" + tree_name[0] + ":" + cut_setting[711] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[120]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // sys checks  95
  (coll_system + ":" + name[273] + ":" + tree_name[0] + ":" + cut_setting[706] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[124]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[272] + ":" + tree_name[0] + ":" + cut_setting[706] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[124]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  (coll_system + ":" + name[274] + ":" + tree_name[0] + ":" + cut_setting[706] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[125]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[275] + ":" + tree_name[0] + ":" + cut_setting[707] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[126]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // sys checks
  (coll_system + ":" + name[273] + ":" + tree_name[0] + ":" + cut_setting[708] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[127]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[272] + ":" + tree_name[0] + ":" + cut_setting[708] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[127]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  (coll_system + ":" + name[274] + ":" + tree_name[0] + ":" + cut_setting[708] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[128]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[275] + ":" + tree_name[0] + ":" + cut_setting[709] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[129]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // sys checks
  (coll_system + ":" + name[273] + ":" + tree_name[0] + ":" + cut_setting[710] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[130]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[272] + ":" + tree_name[0] + ":" + cut_setting[710] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[130]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  (coll_system + ":" + name[274] + ":" + tree_name[0] + ":" + cut_setting[710] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[131]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[275] + ":" + tree_name[0] + ":" + cut_setting[711] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[132]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),


  // 0-20 //107
  (coll_system + ":" + name[277] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[106]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[276] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[106]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[278] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[107]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[279] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[108]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // 20-40
  (coll_system + ":" + name[281] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[106]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[280] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[106]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[282] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[107]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[283] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[108]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // 40-70
  (coll_system + ":" + name[285] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[106]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[284] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[106]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[286] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[107]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[287] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[108]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // 70-100
  (coll_system + ":" + name[289] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[106]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[288] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[106]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[290] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[107]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[291] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[108]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),



  // 0-20 //123
  (coll_system + ":" + name[293] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[292] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[294] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[111]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[295] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[112]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // 20-40
  (coll_system + ":" + name[297] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[296] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[298] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[111]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[299] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[112]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // 40-70
  (coll_system + ":" + name[301] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[300] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[302] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[111]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[303] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[112]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),

  // 70-100
  (coll_system + ":" + name[305] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 16 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[304] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 17 MB weighted new PF" +":"+effi_name[121]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[306] + ":" + tree_name[0] + ":" + cut_setting[670] + ":" + "Data 18 CENT MB weighted new PF" +":"+effi_name[111]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),
  (coll_system + ":" + name[307] + ":" + tree_name[0] + ":" + cut_setting[693] + ":" + "Data 18 FAST MB weighted new PF" +":"+effi_name[112]+":"+effi_gen[3]+":"+effi_rec[15]  +":"+"./input/acceptance/AcceptanceToyWresoWrapWcockV19.root"+":"+"NMeasPairs_eta2pt0"+":"+"NRecPairs_pt1_75-pt2_75" ),




  "empty" // needed to avoid anger with ',' at the end of the last active line
};

Int_t n_config = sizeof(cconfig)/sizeof(*cconfig) -1; // '-1' to neglect the "empty" entry.















//
// desired binning for output. will also be used for efficiency correction.
// binning has to be compatible with input. [PR/CK: see function GetVector() of Config_user_LMEEPbPb.C]

//Double_t mee_bins[] = {0.0, 0.14, 1.1, 1.8, 3.3 };
//Double_t mee_bins[] = {0.0, 0.14, 1.04, 3.5 };
//Double_t mee_bins[] = {0.0, 0.14, 0.3,0.7,1.1, 1.8, 3.3 };
//Double_t mee_bins[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.20, 0.30, 0.50, 0.70, 0.80, 0.90, 1.05, 1.30, 1.60, 2.00, 2.50, 3.00, 3.12, 3.50, 4.00 };
//Double_t mee_bins[] = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.20, 0.30, 0.50, 0.60, 0.70, 0.74, 0.80, 0.90, 1.00, 1.06, 1.30, 1.80, 2.30, 2.80, 3.00, 3.06, 3.12, 4.00 };  //Basti
//Double_t mee_bins[]  = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.20, 0.30, 0.50, 0.70, 0.80, 0.90, 1.04, 1.40, 1.80, 2.30, 2.80, 3.00, 3.12, 3.50, 4.00}; //Jerome rebin
//Double_t mee_bins[]  = { 0.00,0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.14, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.12, 3.50, 4.00}; //Jerome rebin
//Double_t mee_bins[]  = { 0.00,0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.14, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.10, 3.50, 4.00}; //Jerome rebin
//Double_t mee_bins_plotting[]  = { 0.00,0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.14, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.10, 3.50, 4.00}; //Jerome rebin

//Double_t mee_bins[]  = { 0.00,0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.12, 0.14, 0.16, 0.20, 0.22, 0.26, 0.32, 0.40, 0.50, 0.60, 0.70,0.76, 0.80, 0.90, 0.98, 1.02, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.06, 3.10, 3.30, 3.50, 4.00}; //Jerome rebin
//hier  Double_t mee_bins_plotting[]  = { 0.00,0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.12, 0.14, 0.16, 0.20, 0.22, 0.26, 0.32, 0.40, 0.50, 0.60, 0.70, 0.76, 0.80, 0.90, 0.98, 1.02, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.06, 3.10, 3.30, 3.50, 4.00}; //Jerome rebin

//Double_t mee_bins_plotting_0[]  = { 0.00,0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.12, 0.14, 0.16, 0.20, 0.22, 0.26, 0.32, 0.40, 0.50, 0.60, 0.70, 0.76, 0.80, 0.90, 0.98, 1.02, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.06, 3.10, 3.30, 3.50, 4.00}; //Jerome rebin
//Double_t mee_bins_plotting_1[]  = { 0.00,0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.12, 0.14, 0.16, 0.20, 0.22, 0.26, 0.32, 0.40, 0.50, 0.60, 0.70, 0.76, 0.80, 0.90, 0.98, 1.02, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.06, 3.10, 3.30, 3.50, 4.00}; //Jerome rebin
//Double_t mee_bins_plotting_2[]  = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14, 0.20, 0.26, 0.32, 0.40, 0.50, 0.70, 0.90, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.10, 3.30, 3.50, 4.00}; //Jerome rebin
//Double_t mee_bins_plotting_3[]  = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14, 0.20, 0.26, 0.32, 0.40, 0.50, 0.70, 0.90, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.10, 3.30, 3.50, 4.00}; //Jerome rebin
//Double_t mee_bins_plotting_4[]  = { 0.00, 0.04, 0.08, 0.14, 0.20, 0.26, 0.32, 0.40, 0.50, 0.70, 0.90, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.10, 3.30, 3.50, 4.00}; //Jerome rebin
//Double_t mee_bins_plotting_5[]  = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14, 0.20, 0.26, 0.32, 0.40, 0.50, 0.70, 0.90, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.10, 3.30, 3.50, 4.00}; //Jerome rebin


//  Double_t mee_bins[]  = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.10, 3.50, 4.00}; //Jerome rebin
//  Double_t mee_bins_plotting[]  = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.14, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.10, 3.50, 4.00}; //Jerome rebin

//Double_t mee_bins[]  = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.32, 0.38, 0.54, 0.66, 0.72, 0.76, 0.78, 0.86, 0.98, 1.02, 1.20, 1.40,/* 1.64, 1.96, 2.34, 2.84, 2.95, */3.05, 3.10,/* 3.15,*/ 3.30 ,3.50/*, 3.75, 4.25*/}; //Ivan Binning
//Double_t mee_bins_plotting[]  = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.32, 0.38, 0.54, 0.66, 0.72, 0.76, 0.78, 0.86, 0.98, 1.02, 1.20, 1.40,/* 1.64, 1.96, 2.34, 2.84, 2.95, */3.05, 3.10,/* 3.15,*/ 3.30 ,3.50/*, 3.75, 4.25*/}; //Ivan Binning

//Double_t mee_bins_plotting[]  = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.32, 0.38, 0.54, 0.66, 0.72, 0.76, 0.78, 0.86, 0.98, 1.02, 1.20, 1.40, 1.60, 2.00, 2.4, 2.8, 3.00, 3.05, 3.10, /*3.15,*/ 3.30 ,3.50/*, 3.75, 4.25*/}; //Ivan Binning

//Double_t mee_bins[]  = { 0.00, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.32, 0.38, 0.54, 0.66, 0.72, 0.76, 0.78, 0.86, 0.98, 1.02, 1.20, 1.40, 1.64, 1.96, 2.34, 2.84, 2.95, 3.05, 3.10, 3.15, 3.30 ,3.50, 3.75, 4.25}; //Ivan Binning

//Double_t mee_bins_plotting[]  = {
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,//0.09,
//    0.10,/*0.12,*/0.14,/*0.16,*/0.20,
//    0.24,
//    0.30,
//    0.40,
//    0.50,
//    0.60,
//    0.70,0.75,
//    0.80,0.85,
//    0.90,0.95,
//    1.00,1.05,
//    1.10,1.20,1.40,1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00
//
//}; //Jerome data

  ////LMR spectra
  Double_t mee_bins_plotting[]  = {
      0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.08,
      0.10,0.12,0.15,//0.16,0.18,
      0.20,0.25,
      0.30,
      0.40,
      0.50,
      0.60,
      0.70,
      0.80,//0.85,
      0.90,//0.95,
      1.00,//1.05,
      1.10,1.20,1.40,1.60,/*1.80,*/2.00,
      /*2.20,*/2.40,/*2.60,*/2.80,3.00,
      /*3.06,*/3.10,3.30,3.50,4.00
  }; //Jerome data

  Double_t mee_bins[]  = {
      0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.08,
      0.10,0.12,0.15,//0.16,0.18,
      0.20,0.25,
      0.30,0.35,
      0.40,
      0.50,
      0.60,
      0.70,
      0.80,0.85,
      0.90,0.95,
      1.00,1.05,
      1.10,1.20,1.40,1.60,1.80,2.00,
      2.20,2.40,2.60,2.80,3.00,
      3.06,3.10,3.30,3.50,4.00
  }; //Jerome data

 Double_t mee_bins_cocktail[]  = {
     0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.08,
     0.10,0.12,0.15,//0.18,
     0.20,0.25,
     0.30,0.35,
     0.40,
     0.50,0.59,
     0.60,
     0.70,
     0.80,0.85,
     0.90,0.95,
     1.00,1.05,
     1.10,1.20,1.40,1.60,1.80,2.00,
     2.20,2.40,2.60,2.80,3.00,
     3.06,3.10,3.30,3.50,4.00
 }; //Jerome data


//  Double_t mee_bins[]  = {
//
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//    0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
//    0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
//    0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
//    0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
//    0.50,0.51,0.52,0.53,0.54,0.55,0.56,0.57,0.58,0.59,
//    0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,
//    0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,
//    0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,
//    0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,
//    1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,
//    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.01,3.02,3.03,3.04,3.05,
//    3.06,3.07,3.08,3.09,3.10,3.30,3.50,4.00

//  }; //Jerome data

  Double_t mee_bins_plotting_0[]  = {

    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,0.40,0.42,0.44,0.46,0.48,0.50,0.52,0.54,0.56,0.58,
    0.60,0.62,0.64,0.66,0.68,
    0.70,0.72,0.74,0.76,0.78,
    0.80,0.82,0.84,0.86,0.88,
    0.90,0.92,0.94,0.96,0.98,
    1.00,1.02,1.04,1.06,1.08,
    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data

  Double_t mee_bins_plotting_1[]  = {

    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,0.40,0.42,0.44,0.46,0.48,0.50,0.52,0.54,0.56,0.58,
    0.60,0.62,0.64,0.66,0.68,
    0.70,0.72,0.74,0.76,0.78,
    0.80,0.82,0.84,0.86,0.88,
    0.90,0.92,0.94,0.96,0.98,
    1.00,1.02,1.04,1.06,1.08,
    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data

  Double_t mee_bins_plotting_2[]  = {

    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,
    0.60,0.65,
    0.70,0.75,
    0.80,0.85,
    0.90,0.95,
    1.00,1.05,
    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data

  Double_t mee_bins_plotting_3[]  = {

    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,
    0.60,0.65,
    0.70,0.75,
    0.80,0.85,
    0.90,0.95,
    1.00,1.05,
    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data

  Double_t mee_bins_plotting_4[]  = {

    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.30,0.40,0.50,
    0.60,//0.64,0.68,
    0.70,//0.72,0.74,0.76,0.78,
    0.80,//0.82,0.84,0.86,0.88,
    0.90,//0.92,0.94,0.96,0.98,
    1.00,//1.02,1.04,1.06,
    1.10,1.30,1.50,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data

  Double_t mee_bins_plotting_5[]  = {

    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,0.40,0.42,0.44,0.46,0.48,0.50,0.52,0.54,0.56,0.58,
    0.60,0.62,0.64,0.66,0.68,
    0.70,0.72,0.74,0.76,0.78,
    0.80,0.82,0.84,0.86,0.88,
    0.90,0.92,0.94,0.96,0.98,
    1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,
    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,2.20,2.40,2.60,2.80,3.00,3.10,3.30,3.50,4.00

  }; //Jerome data




//  Double_t mee_bins_plotting[]  = {
//      0.00,0.02,0.04,0.06,
//      0.16,
//      0.20,
//      0.30,
//      0.40,
//      0.50,
//      0.60,
//      0.70,
//      0.80,0.85,
//      0.90,0.95,
//      1.00,1.05,
//      1.10,1.20,1.40,1.60,1.80,2.00,
//      2.20,2.40,2.60,2.80,3.00,
//      3.06,3.10,3.30,3.50,4.00
//  }; //Jerome data
//
//  Double_t mee_bins[]  = {
//      0.00,0.02,0.04,0.06,
//      0.16,
//      0.20,
//      0.30,
//      0.40,
//      0.50,
//      0.60,
//      0.70,
//      0.80,0.85,
//      0.90,0.95,
//      1.00,1.05,
//      1.10,1.20,1.40,1.60,1.80,2.00,
//      2.20,2.40,2.60,2.80,3.00,
//      3.06,3.10,3.30,3.50,4.00
//  }; //Jerome data
//  Double_t mee_bins_cocktail[]  = {
//      0.00,0.02,0.08,
//      0.16,
//      0.20,
//      0.30,
//      0.40,
//      0.50,
//      0.60,
//      0.70,
//      0.80,0.85,
//      0.90,0.95,
//      1.00,1.05,
//      1.10,1.20,1.40,1.60,1.80,2.00,
//      2.20,2.40,2.60,2.80,3.00,
//      3.06,3.10,3.30,3.50,4.00
//  }; //Jerome data




////_________________________________________________________________________________________
//  Double_t mee_bins_plotting[]  = {
//      0.00,//0.01,0.02,0.03,
//      //0.04,//0.05,0.06,0.07,
//      //0.08,//0.10,
//      0.15,//0.20,0.30,0.40,0.50,
//      0.60,//0.70,0.80,0.85,0.90,0.95,
//      1.00,1.05,
//      1.10,1.20,1.40,1.60,1.80,2.00,
//      2.20,2.40,2.60,2.80,3.00,
//      3.06,3.10,3.30,3.50,4.00
//  }; //mult study
//
//   Double_t mee_bins[]  = {
//      0.00,0.01,0.02,0.03,
//      0.04,//0.05,//0.06,0.07,
//      0.08,//0.10,
//      0.15,//0.20,0.30,0.40,0.50,
//      0.60,//0.70,0.80,0.85,0.90,0.95,
//      1.00,1.05,
//      1.10,1.20,1.40,1.60,1.80,2.00,
//      2.20,2.40,2.60,2.80,3.00,
//      3.06,3.10,3.30,3.50,4.00
//  }; //mult study
//
//  Double_t mee_bins_cocktail[]  = {
//      0.00,//0.01,0.02,0.03,
//      //0.04,//0.05,0.06,0.07,
//      //0.08,//0.10,
//      0.15,//0.20,0.30,0.40,0.50,
//      0.60,//0.70,0.80,0.85,0.90,0.95,
//      1.00,1.05,
//      1.10,1.20,1.40,1.60,1.80,2.00,
//      2.20,2.40,2.60,2.80,3.00,
//      3.06,3.10,3.30,3.50,4.00
//  }; //mult study

//  Double_t* mee_bins_cocktail = mee_bins_plotting;
//__________________________________________________________________________________________

//Double_t mee_bins_plotting[]  = {
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,/*0.07,*/0.08,//0.09,
//    //0.00,0.04,/*0.07,*/0.08,//0.09,
//
//    0.10,/*0.12,*/0.15,/*0.16,0.20,*/0.20,
//    0.25,
//    0.30,
//    0.40,
//    0.50,
//    0.60,
//    0.70,//0.75,
//    0.80,0.85,
//    /*0.90,0.95,*/
//    1.00,//1.04,
//    /*1.10,1.20,1.40,*/1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00
//0.00,0.04,0.15,0.60,1.1,2.80,3.10,4.00// Realistic binning

//0.00,0.01,0.02,0.03,0.04,0.05,0.06,/*0.07,*/0.08,//0.09,
//0.10,0.12,0.15,/*0.16,0.20,*/0.20,
//0.25,
//0.30,0.35,
//0.40,
//0.50,
//0.60,
//0.70,0.75,
//0.80,0.85,
//0.90,0.95,
//1.00,1.04,
//1.10,1.20,1.40,1.60,1.80,2.00,
//2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00

//    0.00,0.05,0.10,0.15,0.20,
//    0.25,0.30,
//    0.40,
//    0.50,
//    0.60,
//    0.70,//0.75,
//    0.80,0.85,
//    /*0.90,0.95,*/
//    1.00,//1.04,
//    /*1.10,1.20,1.40,*/1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00
//
//
//
//}; //Jerome data


//Double_t mee_bins[]  = {
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,/*0.07,*/0.08,//0.09,
//    //0.00,0.04,/*0.07,*/0.08,//0.09,
//
//    0.10,0.12,0.15,/*0.16,0.20,*/0.20,
//    0.25,
//    0.30,
//    0.40,
//    0.50,
//    0.60,
//    0.70,//0.75,
//    0.80,0.85,
//    /*0.90,0.95,*/
//    1.00,//1.04,
//    /*1.10,1.20,1.40,*/1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00
//};

//Double_t mee_bins[]  = {
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,/*0.07,*/0.08,//0.09,
//    0.10,0.12,0.15,/*0.16,0.20,*/0.20,
//    0.25,
//    0.30,0.35,
//    0.40,
//    0.50,
//    0.60,
//    0.70,0.75,
//    0.80,0.85,
//    0.90,0.95,
//    1.00,1.04,
//    1.10,1.20,1.40,1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00
//
//}; //Jerome data



//Double_t mee_bins_plotting[]  = {
//    0.00,/*0.01,*/0.02,/*0.03,*/0.04,/*0.05,0.06,0.07,*/0.08,/*0.09,
//    0.10,0.12,*/0.14,/*0.16,0.20,
//    0.24,*/
//    //0.30,
//    //0.40,
//    //0.50,
//    0.60,
//    /*0.70,*///0.75,
//    //0.80,//0.85,
//    /*0.90,0.95,*/
//    1.00,//1.04,
//    /*1.10,1.20,1.40,1.60,*///1.80,2.00,
//    /*2.20,2.40,2.60,*/2.80/*,3.00,3.06,3.10*/,3.30/*,3.50*/,4.00
//
//}; //Jerome data

//excess extraction
//   Double_t mee_bins_plotting[]  = {
//       0.00,/*0.04,0.05,0.06,0.07,0.08,0.09,
//       0.10,0.12,*/0.14,/*0.16,0.20,
//       0.24,*/
//       //0.30,
//       //0.40,
//       //0.50,
//       0.60,
//       /*0.70,*///0.75,
//       //0.80,//0.85,
//       /*0.90,0.95,*/
//       1.10,//1.04,
//       /*1.10,1.20,1.40,1.60,*///1.80,2.00,
//       /*2.20,2.40,2.60,*/2.70/*,3.00,3.06,3.10,3.30,3.50*/,4.00
//
//   }; //Jerome data



//Double_t mee_bins_plotting[]  = {
//    0.00,0.04,/*0.05,0.06,0.07,*/0.08,/*0.09,
//    0.10,0.12,*/0.14,/*0.16,0.20,
//    0.24,*/
//    //0.30,
//    //0.40,
//    //0.50,
//    0.60,
//    /*0.70,*///0.75,
//    //0.80,//0.85,
//    /*0.90,0.95,*/
//    1.00,//1.04,
//    /*1.10,1.20,1.40,1.60,*///1.80,2.00,
//    /*2.20,2.40,2.60,*/2.80/*,3.00,3.06,3.10,3.30,3.50*/,4.00
//
//}; //Jerome data




//Full
//Double_t mee_bins_plotting[]  = {
//    0.00,0.02,0.04,0.05,0.08,
//    0.10,0.14,
//    0.20,0.25,
//    0.30,0.35,
//    0.40,
//    0.50,
//    0.60,
//    0.70,
//    0.80,0.85,
//    0.90,0.95,
//    1.00,1.05,
//    1.10,1.20,1.40,1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,
//    3.06,3.10,3.30,3.50,4.00
//
//
//}; //Jerome data


//Double_t mee_bins_plotting[]  = {
//    0.00,0.02,0.04,0.06,0.08,
//    0.10,0.15,0.20,
//    0.60,
//    1.10,
//    1.60,
//    2.60,3.00,3.10,3.50,4.00
//
//}; //Jerome data




//.Double_t mee_bins[]  = {
//.    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//.    0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
//.    0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
//.    0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
//.    0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
//.    0.50,0.51,0.52,0.53,0.54,0.55,0.56,0.57,0.58,0.59,
//.    0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,
//.    0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,
//.    0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,
//.    0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,
//.    1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,
//.    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
//.    2.20,2.40,2.60,2.80,3.00,3.01,3.02,3.03,3.04,3.05,
//.    3.06,3.07,3.08,3.09,3.10,3.30,3.50,4.00
//.
//.
//.}; //Jerome data

//Double_t mee_bins[]  = {
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,//0.09,
//    0.10,/*0.12,*/0.14,0.16,0.20,
//    0.24,
//    0.30,
//    0.40,0.45,
//    0.50,0.55,
//    0.60,
//    0.70,0.75,
//    0.80,0.85,
//    0.90,0.95,
//    1.00,1.05,
//    1.10,1.20,1.40,1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00
//
//}; //Jerome data


////LMR spectra
//Double_t mee_bins[]  = {
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.08,
//    0.10,0.14,//0.16,0.18,
//    0.20,0.25,
//    0.30,
//    0.40,
//    0.50,
//    0.60,
//    0.70,
//    0.80,0.85,
//    0.90,0.95,
//    1.00,1.05,
//    1.10,1.20,1.40,1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,
//    3.06,3.10,3.30,3.50,4.00
//
//
//}; //Jerome data



//    Double_t mee_bins[]  = {
//        0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,
//        0.10,0.14,
//        //0.20,
//        //0.30,
//        //0.40,
//        //0.50,
//        0.60,
//        //0.70,
//        //0.80,0.85,
//        //0.90,0.95,
//        1.00,1.05,1.10,
//        1.20,1.40,1.60,1.80,2.00,
//        2.20,2.40,2.60,2.80,3.00,
//        3.06,3.10,3.30,3.50,4.00
//
//
//    }; //Jerome data

//pTee slices
//  Double_t mee_bins[]  = {
//      0.00,0.05,
//      0.10,0.14,
//      0.20,
//      0.30,
//      //0.40,
//      //0.50,
//      0.60,
//      //0.70,
//      0.80,0.85,
//      0.90,0.95,
//      1.00,1.05,1.10,
//      1.20,1.40,1.60,1.80,2.00,
//      2.20,2.40,2.60,2.80,3.00,
//      3.06,3.10,3.30,3.50,4.00
//
//
//  }; //Jerome data


//excess extraction
//  Double_t mee_bins[]  = {
//      0.00,0.01,0.02,0.03,0.04,/*0.05,0.06,0.07,*/0.08,/*0.09,
//      0.10,0.12,*/0.15,/*0.16,0.20,
//      0.24,*/
//      //0.30,
//      //0.40,
//      //0.50,
//      0.60,
//      /*0.70,*///0.75,
//      //0.80,//0.85,
//      /*0.90,0.95,*/
//      1.10,//1.04,
//      /*1.10,1.20,1.40,1.60,*///1.80,2.00,
//      /*2.20,2.40,2.60,*/2.70/*,3.00,3.06,3.10,3.30,3.50*/,4.00
//
//  }; //Jerome data

//Full
//Double_t mee_bins[]  = {
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.08,
//    0.10,0.14,0.16,0.18,
//    0.20,0.25,
//    0.30,0.35,
//    0.40,
//    0.50,
//    0.60,
//    0.70,
//    0.80,0.85,
//    0.90,0.95,
//    1.00,1.05,
//    1.10,1.20,1.40,1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,
//    3.06,3.10,3.30,3.50,4.00
//
//
//}; //Jerome data



//Double_t ptee_bins[] = { 0.0,0.5,1.0,2.0,3.0,4.5,6.0 };
//Double_t ptee_bins[] = { 0.0,0.4,0.7,1.0,1.5,2.0,2.5,3.0,3.5,4.5,6.0 };
//Double_t ptee_bins_plotting[] = { 0.00,0.05,0.10,0.15,0.20,0.25,0.30,0.40,0.50,0.60,0.70,0.80,0.90,1.00,1.50,2.00,2.50,3.00,3.50,4.50,6.00}; //new Binning 1
//Double_t ptee_bins[] = { 0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.10,0.12, 0.14, 0.16, 0.18,0.20,0.24, 0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.5,2.0,2.5,3.0,3.5,4.5,6.0}; //new Binning 2
// Double_t ptee_bins[] = { 0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.10,0.12, 0.14, 0.16, 0.18,0.20,0.25, 0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.5,2.0,2.5,3.0,3.5,4.5,6.0}; //new Binning 2
// Double_t ptee_bins_plotting[] = { 0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.10,0.12,0.15, 0.14, 0.16, 0.18,0.20,0.25, 0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.5,2.0,2.2,2.4,2.6,2.8,3.0,4.0,6.0,8.0,10.}; //new Binning 2
//  Double_t ptee_bins_plotting[] = { 0.000,0.050,0.080,0.100,0.150,0.200,0.250,0.300,0.400,0.500,0.600,0.700,0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,1.600,1.700,1.800,1.900,2.000,2.200,2.400,2.60, 3.000,3.200,3.400,3.600,3.800,4.000,4.500,5.5,6.000,6.5,7.,8.000,10.}; //new Binning 2

Double_t ptee_bins_plotting[] = {0.00,0.02,0.04,0.06,0.07,0.08,0.09,
                                 0.10,0.12,0.14,0.16,0.18,
                                 0.20,0.22,0.24,0.26,0.28,
                                 0.30,0.32,0.34,0.36,0.38,
                                 0.40,0.42,0.44,0.46,0.48,
                                 0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,
                                 1.00,1.10,1.20,1.30,1.40,
                                 1.50,
                                 2.00,
                                 2.50,3.00,3.50,
                                 4.00,5.00,
                                 6.00,8.00,10.0
};

//  Double_t ptee_bins_plotting_0[] = { 0.00,0.050,0.10,0.15,0.20,0.25,0.30,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,4.0,6.0,8.0,10.}; //new Binning 2
//  Double_t ptee_bins_plotting_0[] = { 0.00,0.020,0.040,0.060,0.080,0.10,0.12,0.14,0.16,0.18,0.20,0.24,0.30,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,2.0,2.5,3.0,4.0,6.0,8.0,10.}; //new Binning 2
//  Double_t ptee_bins_plotting_1[] = { 0.00,0.040,0.10,0.14,0.20,0.24,0.30,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,2.0,2.5,3.0,4.0,6.0,8.0,10.}; //new Binning 2
//Double_t ptee_bins_plotting_2[] = { 0.00,0.10,0.20,0.25,0.30,0.35,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,4.0,6.0,8.0,10.}; //new Binning 2


//Double_t ptee_bins_plotting_0[] = {0.00,0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,1.00,1.10,1.20,1.30,1.40,1.50,2.00,2.50,3.00,4.00,6.00,8.00,10.0};


//   Double_t ptee_bins_plotting_0[] = { 0.00,0.05,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.25,0.30,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.5,5.,6.0,6.5,7.,8.0,10.}; //new Binning 2
//    Double_t ptee_bins_plotting_0[] = { 0.00,0.10,0.20,0.30,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.2,2.4,2.6,2.8,3.0,4.0,6.0,8.0,10.}; //new Binning 2
//      Double_t ptee_bins_plotting_0[] = { 0.00,0.20,0.4,0.6,0.8,1.0,1.4,2.0,3.0,5.0,10.}; //new Binning 2
//  Double_t ptee_bins_plotting_1[] = { 0.00,0.050,0.10,0.15,0.20,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.5,2.0,3.0,4.0,6.0,8.0,10.}; //new Binning 2
//    Double_t ptee_bins_plotting_1[] = { 0.00,0.10,0.20,0.30,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.5,2.0,3.0,4.0,6.0,8.0,10.}; //new Binning 2
//      Double_t ptee_bins_plotting_1[] = { 0.00,0.20,0.30,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,4.0,6.0,8.0,10.}; //new Binning 2
//Double_t ptee_bins_plotting_0[] = { 0.00,0.4,0.8,1.4,2.0,3.0,6.0,10.}; //new Binning 2
Double_t ptee_bins_plotting_0[] = {
    0.000,0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    4.000,4.500,5.000,6.000,8.000,10.
};

Double_t ptee_bins_plotting_1[] = {

    //0.000,0.020,0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    //0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    //1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    //2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    //3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    //4.000,4.500,5.000,6.000,8.000,10.

    //0.000,0.001,0.002,0.003,0.004,0.005,0.006,0.008,
    //0.010,0.012,0.016,
    //0.020,0.025,0.030,0.035,0.040,0.045,
    //0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    //0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    //1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    //2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    //3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    //4.000,4.500,5.000,6.000,8.000,10.

   // 0.000,0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    0.000,0.100,0.200,0.300,0.400,0.500,0.600,0.700,

    0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    4.000,4.500,5.000,6.000,8.000,10.


    //0.000,0.100,0.200,0.400,0.600,
    //0.800,1.000,1.200,1.400,
    //1.600,1.800,2.000,2.200,
    //2.400,2.600,2.800,3.000,
    //3.200,3.400,3.600,3.800,
    //4.000,4.500,5.000,6.000,8.000,10.

};

Double_t ptee_bins_plotting_2[] = {

    //0.000,0.020,0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    //0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    //1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    //2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    //3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    //4.000,4.500,5.000,6.000,8.000,10.

    //0.000,0.002,0.004,0.006,0.008,
    //0.010,0.015,
    //0.020,0.025,0.030,0.035,0.040,0.045,
    //0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    //0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    //1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    //2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    //3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    //4.000,4.500,5.000,6.000,8.000,10.



    0.000,0.100,0.200,0.400,0.600,
    0.800,1.000,1.200,1.400,
    1.600,1.800,2.000,2.200,
    2.400,2.600,2.800,3.000,
    3.200,3.400,3.600,3.800,
    4.000,4.500,5.000,6.000,8.000,10.

};

//Double_t ptee_bins_plotting_1[] = { 0.00,0.8,2.0,6.0,10.}; //new Binning 2

//Double_t ptee_bins_plotting_1[] = { 0.00,0.4,0.8,1.4,2.0,3.0,6.0,10.}; //new Binning 2
//Double_t ptee_bins_plotting_1[] = { 0.00,0.20,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,2.0,2.5,3.0,3.5,4.5,6.0,8.0,10.}; //new Binning 2
//Double_t ptee_bins_plotting_2[] = { 0.00,2.0,6.0,10.}; //new Binning 2
Double_t ptee_bins_plotting_3[] = { 0.00,2.0,6.0,10.}; //new Binning 2
Double_t ptee_bins_plotting_4[] = { 0.00,2.0,6.0,10.}; //new Binning 2
Double_t ptee_bins_plotting_5[] = { 0.00,2.0,6.0,10.}; //new Binning 2

//Double_t ptee_bins_plotting_3[] = { 0.00,0.5,1.0,1.5,2.0,2.5,3.0,4.0,6.0,8.0,10.}; //new Binning 2
//Double_t ptee_bins_plotting_4[] = { 0.00,0.5,1.0,2.0,3.0,4.0,6.0,8.0,10.}; //new Binning 2
//Double_t ptee_bins_plotting_5[] = { 0.00,1.0,2.0,4.0,8.0,10.}; //new Binning 2


//Double_t ptee_bins[] = { 0.0,0.4,0.7,1.0,1.5,2.0,2.5,3.0,3.5,4.5};

//Double_t ptee_bins[] = {
//                                0.000,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
//                                0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
//                                1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
//                                2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
//                                3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
//                                4.000,4.100,4.200,4.300,4.400,4.500,6.000,8.000,10.
//};

//Double_t ptee_bins[] = {
//                                0.000,0.050,0.100,0.150,0.200,0.250,0.300,0.400,0.500,0.600,0.700,
//                                0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
//                                1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
//                                2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
//                                3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
//                                4.000,4.100,4.200,4.300,4.400,4.500,6.000,8.000,10.
//};

//Double_t ptee_bins[] = {
//                                0.000,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
//                                0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
//                                1.600,1.700,1.800,1.900,2.000,2.200,
//                                2.400,2.600,2.800,3.000,
//                                4.000,6.000,8.000,10.
//};


//Double_t ptee_bins[] = {
//
//    0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,
//    0.20,0.22,0.24,0.26,0.28,
//    0.30,0.32,0.34,0.36,0.38,
//    0.40,0.42,0.44,0.46,0.48,
//    0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,
//    1.00,1.05,1.10,1.15,1.20,1.25,1.30,1.35,1.40,1.45,
//    1.50,1.55,1.60,1.65,1.70,1.75,1.80,1.85,1.90,1.95,
//    2.00,2.05,2.10,2.15,2.20,2.25,2.30,2.35,2.40,2.45,
//    2.50,2.60,2.70,2.80,2.90,3.00,3.10,3.20,3.30,3.40,
//    3.50,3.60,3.70,3.80,3.90,4.00,4.10,4.20,4.30,4.40,
//    4.50,5.00,5.50,6.00,6.50,7.00,8.00,10.0
//};


//Double_t ptee_bins[] = {
//
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//    0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
//    0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
//    0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
//    0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
//    0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,
//    1.00,1.05,1.10,1.15,1.20,1.25,1.30,1.35,1.40,1.45,
//    1.50,1.55,1.60,1.65,1.70,1.75,1.80,1.85,1.90,1.95,
//    2.00,2.05,2.10,2.15,2.20,2.25,2.30,2.35,2.40,2.45,
//    2.50,2.60,2.70,2.80,2.90,3.00,3.10,3.20,3.30,3.40,
//    3.50,3.60,3.70,3.80,3.90,4.00,4.10,4.20,4.30,4.40,
//    4.50,5.00,5.50,6.00,6.50,7.00,8.00,10.0
//};

Double_t ptee_bins[] = {


    0.000,0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    4.000,4.500,5.000,6.000,8.000,10.

    //0.000,0.001,0.002,0.003,0.004,0.005,0.006,0.007,0.008,0.009,
    //0.010,0.011,0.012,0.013,0.014,0.015,0.016,0.017,0.018,0.019,
    //0.020,0.021,0.022,0.023,0.024,0.025,0.026,0.027,0.028,0.029,
    //0.030,0.031,0.032,0.033,0.034,0.035,0.036,0.037,0.038,0.039,
    //0.040,0.041,0.042,0.043,0.044,0.045,0.046,0.047,0.048,0.049,
    //0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    //0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    //1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    //2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    //3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    //4.000,4.500,5.000,6.000,8.000,10.




//    0.00,0.04,0.08,0.12,0.16,
//    0.20,0.24,0.28,0.32,0.36,
//    0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,
//    1.00,1.10,1.20,1.30,1.40,
//    1.50,
//    2.00,
//    2.50,3.00,3.50,
//    4.00,5.00,
//    6.00,8.00,10.0
};




//Double_t ptee_bins[] = {

 //   0.00,0.05,
 //   0.10,0.15,
 //   0.20,//0.25,
 //   //0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
 //   //0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
 //   0.30,//0.35,
 //   0.40,//0.45,
 //   0.50,//0.55,
 //   0.60,//0.65,
 //   0.70,0.75,0.80,0.85,0.90,0.95,
 //   1.00,1.10,1.20,1.30,1.40,
 //   1.50,1.6,1.7,1.8,1.9,
 //   2.00,2.2,2.4,2.6,2.8,
 //   3.00,
 //   4.00,
 //   6.00,8.00,10.0

 // 0.00,0.4,0.8,1.4,2.0,3.0,6.0,10.

//0.00,0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,1.00,1.10,1.20,1.30,1.40,1.50,2.00,2.50,3.00,4.00,6.00,8.00,10.0



//    0.00,0.05,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.25,0.30,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.2,2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.5,5.,5.5,6.0,6.5,7.0,8.0,10.


//};



//Double_t ptee_bins[] = {
//                                0.000,0.050,0.100,0.150,0.200,0.250,0.300,0.400,0.500,0.600,0.700,
//                                0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
//                                1.600,1.700,1.800,1.900,2.000,2.100,2.15,2.20,2.25,2.30,2.35,2.40,2.45,
//                                2.50,2.60,2.70,2.80,2.90,3.00,3.10,3.20,3.30,3.40,
//                                3.50,3.60,3.70,3.80,3.90,4.00,4.10,4.20,4.30,4.40,
//                                4.50,5.00,5.50,6.00,6.50,7.00,8.00,10.0
//};

//Double_t ptee_bins[] = {
//0.00,0.050, 0.075, 0.080, 0.085, 0.090, 0.095, 0.10, 0.105, 0.11, 0.115, 0.12, 0.125, 0.13, 0.135, 0.14, 0.145, 0.15, 0.155, 0.16, 0.165, 0.170, 0.175, 0.180, 0.185, 0.190, 0.195, 0.20,0.21,0.22,0.23,0.24,0.25,
//  0.26,0.27,0.28,0.29,0.30,0.32,0.34,0.36,0.38,0.40,0.42, 0.44,0.46, 0.48, 0.49,0.52,0.54,0.56,0.58,0.60,0.65,0.70,0.75,0.80,0.90,1.00,1.10,1.20,
//  1.40,1.60,1.80,2.00,2.40,2.80,3.20,3.70,4.50,6.00,8.00,10.0
//};


Int_t n_mee_bin = sizeof(mee_bins)/sizeof(*mee_bins) -1;
Int_t n_ptee_bin = sizeof(ptee_bins)/sizeof(*ptee_bins) -1;

Int_t n_mee_bin_plotting  = sizeof(mee_bins_plotting)/sizeof(*mee_bins_plotting) -1;
Int_t n_ptee_bin_plotting = sizeof(ptee_bins_plotting)/sizeof(*ptee_bins_plotting) -1;

Int_t n_mee_bin_plotting_0 = sizeof(mee_bins_plotting_0)/sizeof(*mee_bins_plotting_0) -1;
Int_t n_mee_bin_plotting_1 = sizeof(mee_bins_plotting_1)/sizeof(*mee_bins_plotting_1) -1;
Int_t n_mee_bin_plotting_2 = sizeof(mee_bins_plotting_2)/sizeof(*mee_bins_plotting_2) -1;
Int_t n_mee_bin_plotting_3 = sizeof(mee_bins_plotting_3)/sizeof(*mee_bins_plotting_3) -1;
Int_t n_mee_bin_plotting_4 = sizeof(mee_bins_plotting_4)/sizeof(*mee_bins_plotting_4) -1;
Int_t n_mee_bin_plotting_5 = sizeof(mee_bins_plotting_5)/sizeof(*mee_bins_plotting_5) -1;



Int_t n_ptee_bin_plotting_0 = sizeof(ptee_bins_plotting_0)/sizeof(*ptee_bins_plotting_0) -1;
Int_t n_ptee_bin_plotting_1 = sizeof(ptee_bins_plotting_1)/sizeof(*ptee_bins_plotting_1) -1;
Int_t n_ptee_bin_plotting_2 = sizeof(ptee_bins_plotting_2)/sizeof(*ptee_bins_plotting_2) -1;
Int_t n_ptee_bin_plotting_3 = sizeof(ptee_bins_plotting_3)/sizeof(*ptee_bins_plotting_3) -1;
Int_t n_ptee_bin_plotting_4 = sizeof(ptee_bins_plotting_4)/sizeof(*ptee_bins_plotting_4) -1;
Int_t n_ptee_bin_plotting_5 = sizeof(ptee_bins_plotting_5)/sizeof(*ptee_bins_plotting_5) -1;


std::vector<Double_t> mee_bin(mee_bins, mee_bins + sizeof(mee_bins)/sizeof(*mee_bins));
std::vector<Double_t> ptee_bin(ptee_bins, ptee_bins + sizeof(ptee_bins)/sizeof(*ptee_bins));

//std::vector<Double_t> mee_bin_cock(mee_bins_cock, mee_bins_cock + sizeof(mee_bins_cock)/sizeof(*mee_bins_cock));
//std::vector<Double_t> ptee_bin_cock(ptee_bins_cock, ptee_bins_cock + sizeof(ptee_bins_cock)/sizeof(*ptee_bins_cock));


Double_t phiv_bin[] = { 1 }; // if only one number is given, it will be used for Rebin(n).
Int_t n_phiv_bin = sizeof(phiv_bin)/sizeof(*phiv_bin) -1;
//
// systematic
// bin edges must match with the projection bins of the final data handler!
Double_t* mee_bin_sys = mee_bins_plotting;
Double_t* ptee_bin_sys = ptee_bins_plotting;
Int_t n_mee_bin_sys = sizeof(mee_bin_sys)/sizeof(*mee_bin_sys) -1;
Int_t n_ptee_bin_sys = sizeof(ptee_bin_sys)/sizeof(*ptee_bin_sys) -1;

std::vector<double> mee_bin_systematic_coarse{
  //0.0, 4.
  0.00,0.04,0.14,0.60,1.1,2.80,3.10,4.00// Realistic binning
 // 0.00,0.14,4.00// Realistic binning
  //0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
  //0.10,0.12,0.14,0.16,0.20,
  //0.24,
  //0.30,
  //0.40,
  //0.50,
  //0.60,
  //0.70,0.75,
  //0.80,0.85,
  //0.90,0.95,
  //1.00,1.04,
  //1.10,1.20,1.40,1.60,1.80,2.00,
  //2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00
};
std::vector<double> ptee_bin_systematic_coarse{
  0.0, 10.
  //0.00,1.0,2.0,4.0,8.0  //75
  //0.00,1.0,2.0,3.0,4.0,8.0  //75
  //0.00,0.40,0.6,1.0,2.0,3.0,4.0,8.0 //200
  //0.00,0.10,0.20,0.30,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.8,2.0,2.2,2.4,2.6,2.8,3.0,3.5,4.0,4.5,6.0,8.0,10.
};

std::vector<double> unc_bins_mee = {0.00,0.04,0.14,1.1,2.8,3.1,4.0};
//std::vector<double> unc_bins_mee  = {0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//				     0.10,0.12,0.14,0.16,0.20,0.24,0.30,0.40,0.50,0.60,
//                                     0.70,0.75,0.80,0.85,0.90,0.95,1.00,1.04,1.10,1.20,
//                                     1.40,1.60,1.80,2.00,2.20,2.40,2.60,2.80,3.00,3.06,
//                                     3.10,3.30,3.50,4.00};
std::vector<double> unc_bins_ptee = {0., 10.};
//std::vector<double> unc_bins_ptee = {
//
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//    0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
//    0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
//    0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
//    0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
//    0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,
//    1.00,1.05,1.10,1.15,1.20,1.25,1.30,1.35,1.40,1.45,
//    1.50,1.55,1.60,1.65,1.70,1.75,1.80,1.85,1.90,1.95,
//    2.00,2.05,2.10,2.15,2.20,2.25,2.30,2.35,2.40,2.45,
//    2.50,2.60,2.70,2.80,2.90,3.00,3.10,3.20,3.30,3.40,
//    3.50,3.60,3.70,3.80,3.90,4.00,4.10,4.20,4.30,4.40,
//    4.50,5.00,5.50,6.00,6.50,7.00,8.00,10.0
//};




// desired binning for cocktail.
// may be much finer than for data, but the bin edges should overlap to avoid inconsistencies when doing projections!

//Double_t mee_bins_cocktail[] = { 0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.20,0.30,0.50,0.70,0.80,0.90,1.04,1.40,1.80,2.30,2.80,3.00,3.12,3.50,4.00};
//Double_t mee_bin_cocktail[] = { 0.00,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.20,0.30,0.40,0.50,0.60,0.70,0.80,0.90,1.04,1.10,1.20,1.40,1.60,1.80,2.00,2.30,2.50,2.80,3.00,3.12,3.25,3.50,4.00, 5.00 };
//Double_t mee_bins_cocktail[]  = { 0.00,0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.14, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00, 1.20, 1.40, 1.80, 2.30, 2.80, 3.00, 3.10, 3.50, 4.00}; //Jerome rebin
//Double_t mee_bins_cocktail[]  = { 0.00,0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.38, 0.40, 0.50, 0.54, 0.60, 0.62, 0.64, 0.66, 0.68, 0.70, 0.71, 0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79, 0.80, 0.81, 0.82, 0.83, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.90, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1.00, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.10, 1.20, 1.40, 1.60, 1.80, 2.00, 2.20, 2.30, 2.40, 2.60, 2.80, 2.90, 3.00,3.05, 3.06, 3.10, 3.20, 3.30, 3.40, 3.50, 3.60, 3.70, 3.80, 3.90, 4.00}; //Jerome rebin
//Double_t mee_bins_cocktail[]  = {
//
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//    0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
//    0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
//    0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
//    0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
//    0.50,0.51,0.52,0.53,0.54,0.55,0.56,0.57,0.58,0.59,
//    0.60,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,
//    0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,
//    0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,
//    0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,
//    1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,
//    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.01,3.02,3.03,3.04,3.05,
//    3.06,3.07,3.08,3.09,3.10,3.30,3.50,4.00
//
//
//}; //Jerome data
//Double_t ptee_bins_cocktail[] = { 0.0,0.4,0.7,1.0,1.5,2.0,2.5,3.0,3.5,4.5};
//Double_t ptee_bins_cocktail[] = { 0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.8,1.0,1.5,2.0,2.5,3.0,3.5,4.5,6.0};
//Double_t ptee_bins_cocktail[] = { 0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.20,0.22,0.24,0.26,0.28,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.5,2.0,2.5,3.0,3.5,4.5,6.0}; //new Binning 2
//Double_t ptee_bins_cocktail[] = { 0.00,0.05,0.10,0.15,0.20,0.25,0.30,0.40,0.50,0.60,0.70,0.80,0.90,1.00,1.50,2.00,2.50,3.00,3.50,4.50,6.00}; //new Binning 1
//Double_t ptee_bins_cocktail[] = { 0.00,0.10,0.20,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.5,4.0,4.5,5.0,5.5,6.0,7.0,7.5,8.0,9.0,10.0}; //new Binning 2

//Double_t mee_bins_cocktail[]  = {
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//    0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.25,0.26,0.28,
//    0.30,0.35,
//    0.40,0.45,
//    0.50,0.55,
//    0.60,0.65,
//    0.70,0.75,
//    0.80,0.85,
//    0.90,0.95,
//    1.00,1.05,
//    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00
//
////0.00,0.02,0.05,0.14,0.70,1.04,2.80,3.10,4.00// Realistic binningLHC15o
//}; //Jerome data

//Double_t mee_bins_cocktail[]  = {
//    0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//    0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
//    0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.28,
//    0.30,0.32,0.34,0.35,0.36,0.38,
//    0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
//    0.50,0.52,0.54,0.55,0.56,0.58,
//    0.60,0.62,0.64,0.65,0.66,0.68,
//    0.70,0.75,
//    0.80,0.85,
//    0.90,0.95,
//    1.00,1.05,
//    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
//    2.20,2.40,2.60,2.80,3.00,
//    3.06,3.10,3.30,3.50,4.00
//
//
//}; //Jerome data



//    Double_t mee_bins_cocktail[]  = {
//        0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
//        0.10,0.12,0.14,0.16,0.18,0.20,0.25,
// //       0.25,
//        0.30,0.35,
//        0.40,0.45,
//        0.50,0.55,
//        0.60,0.65,
//        0.70,0.75,
//        0.80,0.85,
//        0.90,0.95,
//        1.00,1.05,
//        1.10,1.20,1.40,1.60,1.80,2.00,
//        2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00


//aa    0.00,0.01,0.02,0.03,0.04,0.05,0.06,/*0.07,*/0.08,//0.09,
//aa    //0.00,0.04,/*0.07,*/0.08,//0.09,
//aa
//aa    0.10,0.12,0.15,/*0.16,0.20,*/0.20,
//aa    0.25,
//aa    0.30,0.35,
//aa    0.40,
//aa    0.50,
//aa    0.60,
//aa    0.70,//0.75,
//aa    0.80,0.85,
//aa    /*0.90,0.95,*/
//aa    1.00,1.10,//1.04,
//aa    /*1.10,1.20,1.40,*/1.60,1.80,2.00,
//aa    2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00


//    0.00,0.05,0.10,0.15,0.16,0.20,
//    0.25,0.30,
//    0.40,
//    0.50,0.59,
//    0.60,
//    0.70,//0.75,
//    0.80,0.85,
//    /*0.90,0.95,*/
//    1.00,//1.04,
//    /*1.10,1.20,1.40,*/1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00
//
//
//
//
//    //0.00,0.02,0.05,0.14,0.70,1.04,2.80,3.10,4.00// Realistic binningLHC15o
//    }; //Jerome data


//excess extraction
//Double_t mee_bins_cocktail[]  = {
//    0.00,/*0.04,0.05,0.06,0.07,0.08,0.09,
//    0.10,0.12,*/0.14,/*0.16,0.20,
//    0.24,*/
//    //0.30,
//    //0.40,
//    //0.50,
//    0.60,
//    /*0.70,*///0.75,
//    //0.80,//0.85,
//    /*0.90,0.95,*/
//    1.10,//1.04,
//    /*1.10,1.20,1.40,1.60,*///1.80,2.00,
//    /*2.20,2.40,2.60,*/2.70/*,3.00,3.06,3.10,3.30,3.50*/,4.00
//
//}; //Jerome data


//Double_t mee_bins_cocktail[]  = {
//    0.00,0.04,/*0.05,0.06,0.07,*/0.08,/*0.09,
//    0.10,0.12,*/0.14,/*0.16,0.20,
//    0.24,*/
//    //0.30,
//    //0.40,
//    //0.50,
//    0.60,
//    /*0.70,*///0.75,
//    //0.80,//0.85,
//    /*0.90,0.95,*/
//    1.00,//1.04,
//    /*1.10,1.20,1.40,1.60,*///1.80,2.00,
//    /*2.20,2.40,2.60,*/2.80/*,3.00,3.06,3.10,3.30,3.50*/,4.00
//
//}; //Jerome data




//Double_t mee_bins_cocktail[]  = {
//    0.00,/*0.01,*/0.02,/*0.03,0.04,*/0.05,/*0.06,0.07,*/0.08,/*0.09,
//    0.10,0.12,*/0.14,/*0.16,0.20,*/
//    //0.24,
//    /*0.30,
//    0.40,
//    0.50,*/
//    0.60,
//    /*0.70,*/0.75,
//    0.80,0.85,
//    /*0.90,0.95,*/
//    1.00,//1.04,
//    /*1.10,1.20,1.40,*/1.60,1.80,2.00,
//    2.20,2.40,2.60,2.80,3.00,3.06,3.10,3.30,3.50,4.00
//
//}; //Jerome data

//Double_t mee_bins_cocktail[]  = {
//    0.00,0.01,0.02,0.03,0.04,0.05,0.08,
//    0.10,0.14,0.16,0.18,
//    0.20,0.25,
//    0.30,0.35,
//    0.40,0.45,
//    0.50,0.55,
//    0.60,0.65,
//    0.70,0.75,
//    0.80,0.85,
//    0.90,0.95,
//    1.00,1.05,
//    1.10,1.20,1.30,1.40,1.50,1.60,1.70,1.80,1.90,2.00,
//    2.20,2.40,2.60,2.80,3.00,
//    3.06,3.10,3.30,3.50,4.00
//
//
//}; //Jerome data



Double_t ptee_bins_cocktail[] = {

    //0.00,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,
    //0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,
    //0.20,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,
    //0.30,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,
    //0.40,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,
    //0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,
    //1.00,1.05,1.10,1.15,1.20,1.25,1.30,1.35,1.40,1.45,
    //1.50,1.55,1.60,1.65,1.70,1.75,1.80,1.85,1.90,1.95,
    //2.00,2.05,2.10,2.15,2.20,2.25,2.30,2.35,2.40,2.45,
    //2.50,2.60,2.70,2.80,2.90,3.00,3.10,3.20,3.30,3.40,
    //3.50,3.60,3.70,3.80,3.90,4.00,4.10,4.20,4.30,4.40,
    //4.50,5.00,5.50,6.00,6.50,7.00,8.00,10.0



    0.000,0.050,0.100,0.200,0.300,0.400,0.500,0.600,0.700,
    0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
    1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
    2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
    3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
    4.000,4.500,5.000,6.000,8.000,10.

//    0.000,0.050,0.100,0.200,
//    0.800,1.200,1.400,
//    1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
//    2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
//    3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
//    4.000,4.500,5.000,6.000,8.000,10.




//    0.000,0.050,0.100,0.150,0.200,0.250,0.300,0.350,0.400,0.450,0.500,0.600,0.700,
//    0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
//    1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
//    2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
//    3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
//    4.000,4.500,5.000,6.000,8.000,10.



//                                0.000,0.010,0.020,0.030,0.040,0.050,0.060,0.070,0.080,0.090,0.100,
//                                0.110,0.120,0.130,0.140,0.150,0.160,0.170,0.180,0.190,0.200,0.300,0.400,0.500,0.600,0.700,
//                                0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
//                                1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
//                                2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
//                                3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
//                                4.000,4.100,4.200,4.300,4.400,4.500,6.000,8.000,10.
//

//   0.000,0.020,0.040,0.050,0.060,0.080,
//   0.100,0.120,0.140,0.150,0.160,0.180,
//   0.200,0.220,0.240,0.250,0.260,0.280,
//   0.300,0.320,0.340,0.360,0.380,
//   0.400,0.420,0.440,0.460,0.480,
//   0.500,0.550,
//   0.600,0.700,
//   0.800,0.900,1.000,1.100,1.200,1.300,1.400,1.500,
//   1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
//   2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
//   3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
//   4.000,4.100,4.200,4.300,4.400,4.500,6.000,8.000,10.

//                                0.000,0.050,0.100,0.120,0.140,
//                                0.150,0.160,0.180,0.200,0.250,0.300,0.350,0.400,0.450,0.500,0.550,0.600,0.650,0.700,0.750,
//                                0.800,0.850,0.900,0.950,1.000,1.100,1.200,1.300,1.400,1.500,
//                                1.600,1.700,1.800,1.900,2.000,2.100,2.200,2.300,
//                                2.400,2.500,2.600,2.700,2.800,2.900,3.000,3.100,
//                                3.200,3.300,3.400,3.500,3.600,3.700,3.800,3.900,
//                                4.000,4.100,4.200,4.300,4.400,4.500,5.000,6.000,8.000,10.


};




Int_t n_mee_bin_cocktail = sizeof(mee_bins_cocktail)/sizeof(*mee_bins_cocktail) -1;
Int_t n_ptee_bin_cocktail = sizeof(ptee_bins_cocktail)/sizeof(*ptee_bins_cocktail) -1;

std::vector<Double_t> mee_bin_cocktail(mee_bins_cocktail, mee_bins_cocktail + sizeof(mee_bins_cocktail)/sizeof(*mee_bins_cocktail));
std::vector<Double_t> ptee_bin_cocktail(ptee_bins_cocktail, ptee_bins_cocktail + sizeof(ptee_bins_cocktail)/sizeof(*ptee_bins_cocktail));



//Double_t mee_slices[]  = {0.00, 0.05, 0.14, 0.60, 1., 2.6, 3.50};
Double_t mee_slices[]  = {0.00,0.06,0.6,1.1, 4.0};
//Double_t mee_slices[]  = {0.00,0.010, 0.050, 0.140, 0.600, 4.00};
//Double_t mee_slices[]  = {0.00,0.02, 0.150, 0.4, 0.8, 3.50}; //Ivan
//Double_t ptee_slices[] = {0.00, 10.};
//Double_t ptee_slices[] = {0.00,0.50, 1.0,1.5,3.0, 10.};
Double_t ptee_slices[] = {0.00,0.40, 1.0,6., 10.};

//Double_t ptee_slices[] = {0.00, 1.00, 2.00, 6.00, 10.};

Int_t n_mee_slices = sizeof(mee_slices)/sizeof(*mee_slices) -1;
Int_t n_ptee_slices = sizeof(ptee_slices)/sizeof(*ptee_slices) -1;



// PhiV-cut that shall be applied
// to disable, it's most efficient to call mgr.SetEnableExclusionCutZ(kFALSE);
//Double_t cutPhiVbelow[] = { 0, 0 };
//Double_t cutPhiVabove[] = { 0.75*TMath::Pi(), 0.90*TMath::Pi() };  //3./4.  0.6
//Double_t cutEdgesMee[]  = { 0.01, 0.02 };

//Double_t cutPhiVbelow[] = { 0, 0};
//Double_t cutPhiVabove[] = { 0.4*TMath::Pi(), 0.7*TMath::Pi()};  //3./4.  0.6
//Double_t cutEdgesMee[]  = { 0.01, 0.02 };

//Double_t cutPhiVbelow[] = { 0.};
//Double_t cutPhiVabove[] = { 2.};  //3./4.  0.6
//Double_t cutEdgesMee[]  = { 0.04 };

Double_t cutPhiVbelow[] = { 0., 0., 0., 0.};
Double_t cutPhiVabove[] = { 2., 2., 2., 2.};  //3./4.  0.6
Double_t cutEdgesMee[]  = { 0.01, 0.02 ,0.03, 0.04};



Int_t    n_cutPhiVbelow = sizeof(cutPhiVbelow)/sizeof(*cutPhiVbelow);
Int_t    n_cutPhiVabove = sizeof(cutPhiVabove)/sizeof(*cutPhiVabove);
Int_t    n_cutEdgesMee  = sizeof(cutEdgesMee)/sizeof(*cutEdgesMee);


Double_t plotMeeMin  = 0., plotMeeMax = 1.1;    //3.5
Double_t plotPteeMin = 0.0, plotPteeMax = 1.;  //6.0

Int_t     kBkgEstimator          = LmBackground::kHybrid;  //LmBackground::kHybrid, LmBackground::kArith, LmBackground::kGeom
Int_t     kDoPhiVCut             = 6; // 0:noCut  2:DoCut  4:FlatCorrSub  6:kTemplUnsub  7:kTemplSub

Bool_t    kDoSignifRaw           = kTRUE;
Bool_t    kDoNormNevents         = kTRUE;
Bool_t    kDoNormBinwidth        = kTRUE;
Bool_t    kDoRfactor             = kTRUE;
Bool_t    kDoEffiCorrection      = kTRUE;
Bool_t    kDoEffiCorrectionFirst = kTRUE;
Bool_t    kDoConfLevel           = kTRUE;
Double_t  confLevel              = 0.84;
Bool_t    kDoRatio               = kTRUE;
Bool_t    kDoBinominal           = kFALSE;
Double_t  kRatioLow              = 0.2; //0.2 0.6
Double_t  kRatioHigh             = 3.29;//53.49; //2.29, 3.69
Bool_t    kDoRatioLog            = kFALSE;
Bool_t    kDoCocktail            = kTRUE;
Int_t     debug                  = 1000;
Bool_t    doPhiVtemplates        = kFALSE;  //with MC cut settings, without effcorr otherwise mee_ptee efficiency will be applied on phiV_ptee
Bool_t    doPhiVstudy            = kFALSE;  //without effcorr
Bool_t    DoCorrelationPlots     = kFALSE;
Bool_t    doVirtualPhotonFits    = kFALSE;


Bool_t    DoQA                   = kFALSE;
Bool_t    DoTOFeffPlots          = kFALSE;

//Bool_t    kDoMassSlices          = kTRUE;  //kTRUE: do mass slices  kFALSE: do pair pt slices
Bool_t    kDoIntegrated          = kFALSE;
Bool_t    kDoCombineSpectra      = kTRUE;
Bool_t    kDoMergeMultiple       = kFALSE;
Int_t     kStartMergeAt          = 0;
Int_t     kStopMergeAt           = 99;
Int_t     kMergeNSettings        = 4;
Bool_t    kDoPlotOnlyFirstIn     = kFALSE;
Bool_t    kDoPlotCombineOnly     = kTRUE;

Bool_t    kDoSystematics         = kTRUE;
Bool_t    kDoFixedSystematics    = kTRUE;
Bool_t    kDoNonLogY             = kFALSE;
Bool_t    kDoNonLogX             = kTRUE;

Bool_t    kDoCocktailSubtraction  = kFALSE;
Bool_t    kDoCocktailSubtraction2D= kFALSE;
Bool_t    kDoAcceptanceCorrection = kFALSE;
Bool_t    kDoCocktailOnly         = kFALSE;
Bool_t    kDoVirtGamma            = kFALSE;
Bool_t    kDo200MeVCocktail       = kFALSE;
Bool_t    kDoNormMidRap           = kTRUE;
Bool_t    kDoPublished13TeVpythia = kTRUE;
Bool_t    kDoPublished13TeVpowheg = kFALSE;

Bool_t    kDoLFsum                = kFALSE;
Bool_t    kDoLFonly               = kFALSE;
Bool_t    kDoHFonly               = kFALSE;
Bool_t    kDoJPsi                 = kTRUE;
Bool_t    kDoSUMonly              = kFALSE;
Bool_t    kDoSUMnot               = kFALSE;
Bool_t    kDoScaleEtaSeperate     = kFALSE;
Bool_t    kDoReducedCocktail      = kTRUE;
Bool_t    kDoDrawOnlyFirstCock    = kTRUE;
Bool_t    kDoRapp                 = kFALSE; //reduce cocktail bins to projection
Bool_t    kDoAddRapp              = kFALSE;
Double_t  kRappScaling            = 7./(10.);//5 mee 10 ptee
Bool_t    kDoBrems                = kFALSE; //reduce cocktail bins to projection
Bool_t    kDoAddBrems             = kFALSE;
//Double_t  kBremsScaling           = 10./340000*0.4 * 2;
Double_t  kBremsScaling           = 1/(10. * 57.8);//3bins of cocktail * cross section
Bool_t    kDoMultiTheo            = kFALSE;
//Int_t     kCocktailVersion       = 3; //1: EtaSeperate 2:DONT 3:MultDep

Bool_t    kDoNormCrossSection    = kTRUE;
Bool_t    kDoNormCrossSectionCocktail = kTRUE;
Double_t  kCrossSectionLF        = 0.79; //+-2.9
Double_t  kCrossSection          = 57.8; //+-2.9
Bool_t    kDoNormTrgEff          = kTRUE;
//Double_t  kTriggerEfficiency     = 0.990;//+-0.01
Bool_t    kDoNormRecEff          = kTRUE;
Bool_t    kDoNormVtxRecEff       = kTRUE;
Double_t  kVtxRecEff             = 0.975;//0.977; //0.949
Bool_t    kDoNormVtxRecEffee     = kTRUE;
Double_t  kVtxRecEffee           = 1.0;

Double_t kLFscaling              = 1.;//0.5153; //0.79

//MB - 0-100
Int_t     kLowerCent             = 0;
Int_t     kUpperCent             = 10;
Double_t  kTriggerEfficiency     = 0.921*0.97;//+-0.01
Double_t  kDoResoScaling         = 1.;
Double_t  kDoHFScaling           = 1.;
//HM - 0-1
//Int_t     kLowerCent             = 0;
//Int_t     kUpperCent             = 1;
//Double_t  kTriggerEfficiency     = 1.;//+-0.01
//Double_t  kDoResoScaling         = 2.90;
//Double_t  kDoHFScaling           = 2.90;//5.5; //6

//Mult - 0-10
//Int_t     kLowerCent             = 0;
//Int_t     kUpperCent             = 10;
//Double_t  kTriggerEfficiency     = 1.*0.97;
//Double_t  kDoResoScaling         = 1.9;//2.37 //2.69
//Double_t  kDoHFScaling           = 1.9;//3.3;  //3.3  //3.5
//Mult - 10-20
//Int_t     kLowerCent             = 10;
//Int_t     kUpperCent             = 20;
//Double_t  kTriggerEfficiency     = 0.9975*0.97;//+-0.01
//Double_t  kDoResoScaling         = 1.45;  //1.86
//Double_t  kDoHFScaling           = 1.45;//2.375;
//Mult - 20-40
//Int_t     kLowerCent             = 20;
//Int_t     kUpperCent             = 40;
//Double_t  kTriggerEfficiency     = 0.9915*0.97;//+-0.01
//Double_t  kDoResoScaling         = 1.15; //1.36
//Double_t  kDoHFScaling           = 1.15;//1.35;  //1.42
//Mult - 40-70
//Int_t     kLowerCent             = 40;
//Int_t     kUpperCent             = 70;
//Double_t  kTriggerEfficiency     = 0.953*0.97;//+-0.01
//Double_t  kDoResoScaling         = 0.75; //0.826 //0.74
//Double_t  kDoHFScaling           = 0.75;//0.8;  //0.83
//Mult - 70-100
//Int_t     kLowerCent             = 70;
//Int_t     kUpperCent             = 100;
//Double_t  kTriggerEfficiency     = 0.8;//+-0.01 //0.795
//Double_t  kDoResoScaling         = 0.56;
//Double_t  kDoHFScaling           = 0.56;//0.5;


////Mult - 0-20
//Int_t     kLowerCent             = 0;
//Int_t     kUpperCent             = 20;
//Double_t  kTriggerEfficiency     = 1*0.97;
//Double_t  kDoResoScaling         = 1.65;
//Double_t  kDoHFScaling           = 1.65;//2.5;

Double_t  kDoKWScaling           = 1.;

Double_t  kSetMinPtLabel         = 0.075;
Double_t  kSetMaxPtLabel         = -1;

Double_t  kPlotLow               = 0.0;
Double_t  kPlotHigh              = 0.0;
Bool_t    kDoSaveData            = kFALSE;


////Mult - 0-5
//Int_t     kLowerCent             = 0;
//Int_t     kUpperCent             = 5;
//Double_t  kTriggerEfficiency     = 1.;//+-0.01
//Double_t  kDoResoScaling         = 3.06;
//Double_t  kDoHFScaling           = 4.0;
////Mult - 5-10
//Int_t     kLowerCent             = 5;
//Int_t     kUpperCent             = 10;
//Double_t  kTriggerEfficiency     = 0.999;//+-0.01
//Double_t  kDoResoScaling         = 2.33;
//Double_t  kDoHFScaling           = 2.5;
////Mult - 10-15
//Int_t     kLowerCent             = 10;
//Int_t     kUpperCent             = 15;
//Double_t  kTriggerEfficiency     = 0.998;//+-0.01
//Double_t  kDoResoScaling         = 1.98;
//Double_t  kDoHFScaling           = 2.2;
////Mult - 15-20
//Int_t     kLowerCent             = 15;
//Int_t     kUpperCent             = 20;
//Double_t  kTriggerEfficiency     = 0.997;//+-0.01
//Double_t  kDoResoScaling         = 1.73;
//Double_t  kDoHFScaling           = 1.8;
////Mult - 20-30
//Int_t     kLowerCent             = 20;
//Int_t     kUpperCent             = 30;
//Double_t  kTriggerEfficiency     = 0.995;//+-0.01
//Double_t  kDoResoScaling         = 1.44;
//Double_t  kDoHFScaling           = 1.5;
////Mult - 30-40
//Int_t     kLowerCent             = 30;
//Int_t     kUpperCent             = 40;
//Double_t  kTriggerEfficiency     = 0.988;//+-0.01
//Double_t  kDoResoScaling         = 1.15;
//Double_t  kDoHFScaling           = 1.2;
////Mult - 40-50
//Int_t     kLowerCent             = 40;
//Int_t     kUpperCent             = 50;
//Double_t  kTriggerEfficiency     = 0.975;//+-0.01
//Double_t  kDoResoScaling         = 0.91;
//Double_t  kDoHFScaling           = 1.;
////Mult - 50-70
//Int_t     kLowerCent             = 50;
//Int_t     kUpperCent             = 70;
//Double_t  kTriggerEfficiency     = 0.942;//+-0.01
//Double_t  kDoResoScaling         = 0.65;
//Double_t  kDoHFScaling           = 0.7;
////Mult - 70-100
//Int_t     kLowerCent             = 70;
//Int_t     kUpperCent             = 100;
//Double_t  kTriggerEfficiency     = 0.795;//+-0.01
//Double_t  kDoResoScaling         = 0.37;
//Double_t  kDoHFScaling           = 0.4;




struct SuperConfig{

  TString   DataConfig;
  //Double_t  mee_bins[];
  //Double_t  ptee_bins[];
  Int_t     BkgEstimator;//          = LmBackground::kHybrid;  //LmBackground::kHybrid, LmBackground::kArith, LmBackground::kGeom

  Int_t     LowerCent;//             = 0;
  Int_t     UpperCent;//             = 100;

  Double_t  CrossSection;//          = 57.8; //+-2.9
  Double_t  TriggerEfficiency;//     = 0.921*0.97;//+-0.01
  Double_t  VtxRecEff;//             = 0.975;//0.977; //0.949
  Double_t  VtxRecEffee;//           = 1.0;
  //Double_t  kDoEtaScaling          = 1.;

  TString   LFCocktail;
  TString   LFCocktailUpper;
  TString   LFCocktailLower;
  Double_t  DoResoScaling;//         = 1.;
  TString   HFCocktail;
  TString   HFCocktailHistograms;
  Double_t  DoHFScaling;//           = 1.;

  TString   JPsiCocktail;
  Int_t     CocktailVersion;//       = 3; //1: EtaSeperate 2:DONT 3:MultDep
};





SuperConfig NewPreFilter_0_100_1617 = {
  cconfig[81], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 1.02*0.921*0.97*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig NewPreFilter_0_100_16f = {
  cconfig[75], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 1.02*0.921*0.97*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig NewPreFilter_0_100_17g = {
  cconfig[76], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 1.02*0.921*0.97*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};


SuperConfig NewPreFilter_0_100_18FAST = {
  cconfig[78], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.98*0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};


SuperConfig NewPreFilter_0_100_18Cent = {
  cconfig[77], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 1.04*0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};




SuperConfig NewPreFilter_0_100_16f_2 = {
  cconfig[79], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig NewPreFilter_0_20_16f_2 = {
  cconfig[107+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 2.155/2.13 *0.9,
  heavyfl_files[0], heavyfl_histograms[0], 2.155,
  jpsi_list[1],4
};

SuperConfig NewPreFilter_20_40_16f_2 = {
  cconfig[111+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  20, 40,
  57.8, 0.9915*0.96*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  heavyfl_files[0], heavyfl_histograms[0], 1.15, //1.3
  jpsi_list[1],5
};

SuperConfig NewPreFilter_40_70_16f_2 = {
  cconfig[115+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  40, 70,
  57.8, 0.99*0.97*0.99, 0.975, 1.0, //0.943
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[17], cocktail_files[17], cocktail_files[17], .68/0.66,//1.01,//0.79, 1.15776 1.0
  cocktail_files[22], cocktail_files[23], cocktail_files[24], .68/0.66,//1.01,//0.79, 1.15776 1.0
  heavyfl_files[0], heavyfl_histograms[0], .68, //0.6
  jpsi_list[1],6
};

SuperConfig NewPreFilter_70_100_16f_2 = {
  cconfig[119+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  70, 100,
  57.8, /*0.92**/0.9*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
 // cocktail_files[17], cocktail_files[17], cocktail_files[17], 0.4/0.37,//1.05,// 0.54,  1.135587 , 1.09
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 0.4/0.37,//1.05,// 0.54,  1.135587 , 1.09
  heavyfl_files[0], heavyfl_histograms[0], 0.4, //0.3
  jpsi_list[1],8
};








SuperConfig NewPreFilter_0_100_17g_2 = {
  cconfig[80], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};


SuperConfig NewPreFilter_0_20_17g_2 = {
  cconfig[108+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 2.155/2.13 *0.9,
  heavyfl_files[0], heavyfl_histograms[0], 2.155,
  jpsi_list[1],4
};

SuperConfig NewPreFilter_20_40_17g_2 = {
  cconfig[112+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  20, 40,
  57.8, 0.9915*0.96*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  heavyfl_files[0], heavyfl_histograms[0], 1.15, //1.3
  jpsi_list[1],5
};

SuperConfig NewPreFilter_40_70_17g_2 = {
  cconfig[116+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  40, 70,
  57.8, 0.99*0.97*0.99, 0.975, 1.0, //0.943
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[17], cocktail_files[17], cocktail_files[17], .68/0.66,//1.01,//0.79, 1.15776 1.0
  cocktail_files[22], cocktail_files[23], cocktail_files[24], .68/0.66,//1.01,//0.79, 1.15776 1.0
  heavyfl_files[0], heavyfl_histograms[0], .68, //0.6
  jpsi_list[1],6
};

SuperConfig NewPreFilter_70_100_17g_2 = {
  cconfig[120+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  70, 100,
  57.8, /*0.92**/0.9*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
 // cocktail_files[17], cocktail_files[17], cocktail_files[17], 0.4/0.37,//1.05,// 0.54,  1.135587 , 1.09
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 0.4/0.37,//1.05,// 0.54,  1.135587 , 1.09
  heavyfl_files[0], heavyfl_histograms[0], 0.4, //0.3
  jpsi_list[1],8
};





SuperConfig NewPreFilter_0_100_18FAST_2 = {
  cconfig[82], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig NewPreFilter_0_20_18FAST_2 = {
  cconfig[109+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 2.155/2.13 *0.9,
  heavyfl_files[0], heavyfl_histograms[0], 2.155,
  jpsi_list[1],4
};

SuperConfig NewPreFilter_20_40_18FAST_2 = {
  cconfig[113+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  20, 40,
  57.8, 0.9915*0.96*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  heavyfl_files[0], heavyfl_histograms[0], 1.15, //1.3
  jpsi_list[1],5
};

SuperConfig NewPreFilter_40_70_18FAST_2 = {
  cconfig[117+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  40, 70,
  57.8, 0.99*0.97*0.99, 0.975, 1.0, //0.943
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[17], cocktail_files[17], cocktail_files[17], .68/0.66,//1.01,//0.79, 1.15776 1.0
  cocktail_files[22], cocktail_files[23], cocktail_files[24], .68/0.66,//1.01,//0.79, 1.15776 1.0
  heavyfl_files[0], heavyfl_histograms[0], .68, //0.6
  jpsi_list[1],6
};

SuperConfig NewPreFilter_70_100_18FAST_2 = {
  cconfig[121+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  70, 100,
  57.8, /*0.92**/0.9*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
 // cocktail_files[17], cocktail_files[17], cocktail_files[17], 0.4/0.37,//1.05,// 0.54,  1.135587 , 1.09
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 0.4/0.37,//1.05,// 0.54,  1.135587 , 1.09
  heavyfl_files[0], heavyfl_histograms[0], 0.4, //0.3
  jpsi_list[1],8
};


SuperConfig NewPreFilter_0_100_18Cent_2 = {
  cconfig[81], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig NewPreFilter_0_20_18Cent_2 = {
  cconfig[110+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 2.155/2.13 *0.9,
  heavyfl_files[0], heavyfl_histograms[0], 2.155,
  jpsi_list[1],4
};

SuperConfig NewPreFilter_20_40_18Cent_2 = {
  cconfig[114+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  20, 40,
  57.8, 0.9915*0.96*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  heavyfl_files[0], heavyfl_histograms[0], 1.15, //1.3
  jpsi_list[1],5
};

SuperConfig NewPreFilter_40_70_18Cent_2 = {
  cconfig[118+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  40, 70,
  57.8, 0.99*0.97*0.99, 0.975, 1.0, //0.943
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[17], cocktail_files[17], cocktail_files[17], .68/0.66,//1.01,//0.79, 1.15776 1.0
  cocktail_files[22], cocktail_files[23], cocktail_files[24], .68/0.66,//1.01,//0.79, 1.15776 1.0
  heavyfl_files[0], heavyfl_histograms[0], .68, //0.6
  jpsi_list[1],6
};

SuperConfig NewPreFilter_70_100_18Cent_2 = {
  cconfig[122+16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  70, 100,
  57.8, /*0.92**/0.9*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
 // cocktail_files[17], cocktail_files[17], cocktail_files[17], 0.4/0.37,//1.05,// 0.54,  1.135587 , 1.09
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 0.4/0.37,//1.05,// 0.54,  1.135587 , 1.09
  heavyfl_files[0], heavyfl_histograms[0], 0.4, //0.3
  jpsi_list[1],8
};





SuperConfig NewPreFilter_0_100_16f_sys = {
  cconfig[83], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig NewPreFilter_0_100_17g_sys = {
  cconfig[84], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};


SuperConfig NewPreFilter_0_100_18FAST_sys = {
  cconfig[86], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};


SuperConfig NewPreFilter_0_100_18Cent_sys = {
  cconfig[85], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};


SuperConfig NewPreFilter_0_100_16f_sys1 = {
  cconfig[87], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig NewPreFilter_0_100_17g_sys1 = {
  cconfig[88], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};


SuperConfig NewPreFilter_0_100_18FAST_sys1 = {
  cconfig[90], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};


SuperConfig NewPreFilter_0_100_18Cent_sys1 = {
  cconfig[89], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};



SuperConfig NewPreFilter_0_100_16f_sys2 = {
  cconfig[91], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig NewPreFilter_0_100_17g_sys2 = {
  cconfig[92], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};


SuperConfig NewPreFilter_0_100_18FAST_sys2 = {
  cconfig[94], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};


SuperConfig NewPreFilter_0_100_18Cent_sys2 = {
  cconfig[93], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};




SuperConfig NewPreFilter_0_100_16f_sys3 = {
  cconfig[95], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig NewPreFilter_0_100_17g_sys3 = {
  cconfig[96], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};


SuperConfig NewPreFilter_0_100_18FAST_sys3 = {
  cconfig[98], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};


SuperConfig NewPreFilter_0_100_18Cent_sys3 = {
  cconfig[97], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};


SuperConfig NewPreFilter_0_100_16f_sys4 = {
  cconfig[99], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig NewPreFilter_0_100_17g_sys4 = {
  cconfig[100], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};


SuperConfig NewPreFilter_0_100_18FAST_sys4 = {
  cconfig[102], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};


SuperConfig NewPreFilter_0_100_18Cent_sys4 = {
  cconfig[101], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};


SuperConfig NewPreFilter_0_100_16f_sys5 = {
  cconfig[103], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig NewPreFilter_0_100_17g_sys5 = {
  cconfig[104], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};


SuperConfig NewPreFilter_0_100_18FAST_sys5 = {
  cconfig[106], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};


SuperConfig NewPreFilter_0_100_18Cent_sys5 = {
  cconfig[105], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

















SuperConfig PreFilter_0_100 = {
  cconfig[0], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97, 0.975, 1.0,
  cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig PreFilter_0_100_2 = {
  cconfig[0], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97, 0.975, 1.0,
  cocktail_files[3], cocktail_files[4], cocktail_files[5], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig PreFilter_0_100_3 = {
  cconfig[0], /*mee_bins, ptee_bins,*/ LmBackground::kReal,
  0, 100,
  57.8, 0.921*0.97, 0.975, 1.0,
  cocktail_files[0], cocktail_files[1], cocktail_files[5], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};


SuperConfig PreFilter_0_100_1617_woPF = {
  cconfig[9], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.99, 0.975, 1.0,
  cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig PreFilter_0_100_1617 = {
  cconfig[0], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.96*0.99, 0.975, 1.0,
  cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],0
};

SuperConfig PreFilter_0_10_1617 = {
  cconfig[13], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 10,
  57.8, 1.*0.96*0.99, 0.975, 1.0,
  cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.77,
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],0
};



SuperConfig PreFilter_0_100_18FAST = {
  cconfig[2], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig PreFilter_0_10_18FAST = {
  cconfig[15], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 10,
  57.8, 1.*0.97*0.99, 0.975, 1.0,
  cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.77,
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],0
};



SuperConfig PreFilter_0_100_18Cent = {
  cconfig[1], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.921*0.97*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig PreFilter_0_10_18Cent = {
  cconfig[14], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 10,
  57.8, 1.*0.97*0.99, 0.975, 1.0,
  cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.77,
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],0
};



SuperConfig PreFilter_0_100_all = {
  cconfig[3], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92*0.97*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1., //.94
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1., //.94
  //cocktail_files[19], cocktail_files[19], cocktail_files[19], 1., //.94

  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig PreFilter_0_100_all2 = {
  cconfig[3], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92*0.97*0.99, 0.975, 1.0,
  //cocktail_files[3], cocktail_files[4], cocktail_files[5], 1.,
  //cocktail_files[19], cocktail_files[19], cocktail_files[19], 1., //.94
  cocktail_files[19], cocktail_files[19], cocktail_files[19], 1., //.94
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig PreFilter_0_100_all3 = {
  cconfig[3], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92*0.97*0.99, 0.975, 1.0,
  //cocktail_files[1], cocktail_files[1], cocktail_files[1], 1.,
  cocktail_files[19], cocktail_files[19], cocktail_files[19], 1., //.94
  //cocktail_files[20], cocktail_files[20], cocktail_files[20], 1., //.94
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],5
};

SuperConfig PreFilter_0_100_all4 = {
  cconfig[3], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92*0.97*0.99, 0.975, 1.0,
  //cocktail_files[2], cocktail_files[2], cocktail_files[2], 1.,
  //cocktail_files[19], cocktail_files[19], cocktail_files[19], 1., //.94
  cocktail_files[19], cocktail_files[19], cocktail_files[19], 1., //.94
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],6
};


SuperConfig PreFilter_0_100_16f = {
  cconfig[68], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92*0.97*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1., //.94
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig PreFilter_0_100_17g = {
  cconfig[69], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92*0.97*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1., //.94
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig NoPreFilter_0_100_all = {
  cconfig[70], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1., //.94
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig check_0_100_0 = {
  cconfig[71], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1., //.94
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig check_0_100_13 = {
  cconfig[72], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1., //.94
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig check_0_100_14 = {
  cconfig[73], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1., //.94
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

SuperConfig check_0_100_15 = {
  cconfig[74], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 100,
  57.8, 0.92, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[0], cocktail_files[1], cocktail_files[2], 1., //.94
  cocktail_files[19], cocktail_files[20], cocktail_files[21], 1.,
  heavyfl_files[0], heavyfl_histograms[0], 1.0,
  jpsi_list[1],4
};

//_____________________________________________________________________________________________________________________________

SuperConfig PreFilter_0_10 = {
  cconfig[4], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 10,
  57.8, 1.*0.92*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 2.53/2.53*0.90,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 3.0,
  jpsi_list[1],4
};

SuperConfig PreFilter_10_20 = {
	cconfig[5], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  10, 20,
  57.8, 0.9975*0.945*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.78/1.68*0.96,//0.9,//1.49, 0.926456 0.93
  heavyfl_files[0], heavyfl_histograms[0], 2.0,//1.49,
  jpsi_list[1],5
};

SuperConfig PreFilter_20_40 = {
  cconfig[6], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  20, 40,
  57.8, 0.9915*0.96*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  heavyfl_files[0], heavyfl_histograms[0], 1.15, //1.3
  jpsi_list[1],5
};

SuperConfig PreFilter_40_70 = {
  cconfig[7], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  40, 70,
  57.8, 0.99*0.97*0.99, 0.975, 1.0, //0.943
  //57.8, 0.96*0.99, 0.975, 1.0,
  //cocktail_files[17], cocktail_files[17], cocktail_files[17], .68/0.66,//1.01,//0.79, 1.15776 1.0
  cocktail_files[22], cocktail_files[23], cocktail_files[24], .68/0.66,//1.01,//0.79, 1.15776 1.0
  heavyfl_files[0], heavyfl_histograms[0], .68, //0.6
  jpsi_list[1],6
};

SuperConfig PreFilter_70_100 = {
  cconfig[8], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  70, 100,
  57.8, /*0.92**/0.9*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
 // cocktail_files[17], cocktail_files[17], cocktail_files[17], 0.4/0.37,//1.05,// 0.54,  1.135587 , 1.09
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 0.4/0.37,//1.05,// 0.54,  1.135587 , 1.09
  heavyfl_files[0], heavyfl_histograms[0], 0.4, //0.3
  jpsi_list[1],8
};

SuperConfig PreFilter_0_40 = {
  cconfig[11], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 40,
  57.8, 0.995*0.96*0.99, 0.975, 1.0,
  cocktail_files[0], cocktail_files[1], cocktail_files[2], 1.40,
  heavyfl_files[0], heavyfl_histograms[0], 1.40,
  jpsi_list[1],0
};

SuperConfig PreFilter_40_100 = {
	cconfig[12], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  40, 100,
  57.8, 0.87*0.96*0.99, 0.975, 1.0,
  cocktail_files[0], cocktail_files[1], cocktail_files[2], 0.70,
  heavyfl_files[0], heavyfl_histograms[0], 0.70,
  jpsi_list[1],0
};

SuperConfig PreFilter_0_20 = {
  cconfig[16], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  //cocktail_files[18], cocktail_files[18], cocktail_files[18], 2.155/2.13 *0.9,
  cocktail_files[22], cocktail_files[23], cocktail_files[24], 2.155/2.13 *0.9,
  heavyfl_files[0], heavyfl_histograms[0], 2.155,//2.5
  jpsi_list[1],4
};

//____________________________________________________________________________________________________________

SuperConfig PreFilter_0_10_all = {
  cconfig[17+3*7], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  cocktail_files[18], cocktail_files[18], cocktail_files[18], 2.155/2.13 *0.93,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};

SuperConfig PreFilter_0_10_soft = {
  cconfig[18+3*7], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  cocktail_files[18], cocktail_files[18], cocktail_files[18], 2.155/2.13 *0.93*1.126,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};

SuperConfig PreFilter_0_10_hard = {
  cconfig[19+3*7], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  cocktail_files[18], cocktail_files[18], cocktail_files[18], 2.155/2.13 *0.93*0.836,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};




SuperConfig Sphero_0_10_all = {
  cconfig[41], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 10,
  57.8, 0.99*0.92*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 2.53/2.53*0.90,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};

SuperConfig Sphero_0_10_soft = {
  cconfig[43], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 10,
  57.8, 0.99*0.92*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 2.53/2.53*0.90,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};

SuperConfig Sphero_0_10_hard = {
  cconfig[42], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 10,
  57.8, 0.99*0.92*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 2.53/2.53*0.90,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};

SuperConfig Sphero_10_20_all = {
  cconfig[44], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  10, 20,
  57.8, 0.9975*0.945*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.78/1.68*0.96,//0.9,//1.49, 0.926456 0.93
  heavyfl_files[0], heavyfl_histograms[0], 2.0,//1.49,
  jpsi_list[1],5
};

SuperConfig Sphero_10_20_soft = {
  cconfig[46], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  10, 20,
  57.8, 0.9975*0.945*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.78/1.68*0.96,//0.9,//1.49, 0.926456 0.93
  heavyfl_files[0], heavyfl_histograms[0], 2.0,//1.49,
  jpsi_list[1],5
};

SuperConfig Sphero_10_20_hard = {
  cconfig[45], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  10, 20,
  57.8, 0.9975*0.945*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.78/1.68*0.96,//0.9,//1.49, 0.926456 0.93
  heavyfl_files[0], heavyfl_histograms[0], 2.0,//1.49,
  jpsi_list[1],5
};

SuperConfig Sphero_20_40_all = {
  cconfig[47], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  20, 40,
  57.8, 0.9915*0.96*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  heavyfl_files[0], heavyfl_histograms[0], 1.3,
  jpsi_list[1],6
};

SuperConfig Sphero_20_40_hard = {
  cconfig[48], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  20, 40,
  57.8, 0.9915*0.96*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  heavyfl_files[0], heavyfl_histograms[0], 1.3,
  jpsi_list[1],6
};

SuperConfig Sphero_20_40_soft = {
  cconfig[49], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  20, 40,
  57.8, 0.9915*0.96*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.15/1.15,//1.0,//1.18, 1.01888 0.96
  heavyfl_files[0], heavyfl_histograms[0], 1.3,
  jpsi_list[1],6
};

SuperConfig Sphero_40_70_all = {
  cconfig[50], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  40, 70,
  57.8, 0.99*0.97*0.99, 0.975, 1.0, //0.943
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], .68/0.66,//1.01,//0.79, 1.15776 1.0
  heavyfl_files[0], heavyfl_histograms[0], 0.6,
  jpsi_list[1],7
};

SuperConfig Sphero_40_70_hard = {
  cconfig[51], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  40, 70,
  57.8, 0.99*0.97*0.99, 0.975, 1.0, //0.943
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], .68/0.66,//1.01,//0.79, 1.15776 1.0
  heavyfl_files[0], heavyfl_histograms[0], 0.6,
  jpsi_list[1],7
};

SuperConfig Sphero_40_70_soft = {
  cconfig[52], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  40, 70,
  57.8, 0.99*0.97*0.99, 0.975, 1.0, //0.943
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], .68/0.66,//1.01,//0.79, 1.15776 1.0
  heavyfl_files[0], heavyfl_histograms[0], 0.6,
  jpsi_list[1],7
};

SuperConfig Sphero_70_100_all = {
  cconfig[53], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  70, 100,
  57.8, /*0.92**/0.9*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 0.4/0.37*1.0,//1.05,// 0.54,  1.135587 , 1.08
  heavyfl_files[0], heavyfl_histograms[0], 0.30,
  jpsi_list[1],8
};

SuperConfig Sphero_70_100_hard = {
  cconfig[54], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  70, 100,
  57.8, /*0.92**/0.9*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 0.4/0.37*1.0,//1.05,// 0.54,  1.135587 , 1.08
  heavyfl_files[0], heavyfl_histograms[0], 0.30,
  jpsi_list[1],8
};

SuperConfig Sphero_70_100_soft = {
  cconfig[55], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  70, 100,
  57.8, /*0.92**/0.9*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 0.4/0.37*1.0,//1.05,// 0.54,  1.135587 , 1.08
  heavyfl_files[0], heavyfl_histograms[0], 0.30,
  jpsi_list[1],8
};



SuperConfig SpheroMC_0_10_all = {
  cconfig[65], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 10,
  57.8, 0.99*0.92*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 2.53/2.53*0.90,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};

SuperConfig SpheroMC_0_10_hard = {
  cconfig[66], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 10,
  57.8, 0.99*0.92*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 2.53/2.53*0.90,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};

SuperConfig SpheroMC_0_10_soft = {
  cconfig[67], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 10,
  57.8, 0.99*0.92*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 2.53/2.53*0.90,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};


SuperConfig SpheroMC_10_20_all = {
  cconfig[59], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  10, 20,
  57.8, 0.9975*0.945*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.78/1.68*0.96,//0.9,//1.49, 0.926456 0.93
  heavyfl_files[0], heavyfl_histograms[0], 2.0,//1.49,
  jpsi_list[1],5
};

SuperConfig SpheroMC_10_20_hard = {
  cconfig[60], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  10, 20,
  57.8, 0.9975*0.945*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.78/1.68*0.96,//0.9,//1.49, 0.926456 0.93
  heavyfl_files[0], heavyfl_histograms[0], 2.0,//1.49,
  jpsi_list[1],5
};

SuperConfig SpheroMC_10_20_soft = {
  cconfig[61], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  10, 20,
  57.8, 0.9975*0.945*0.99, 0.975, 1.0,
  //57.8, 0.96*0.99, 0.975, 1.0,
  cocktail_files[17], cocktail_files[17], cocktail_files[17], 1.78/1.68*0.96,//0.9,//1.49, 0.926456 0.93
  heavyfl_files[0], heavyfl_histograms[0], 2.0,//1.49,
  jpsi_list[1],5
};


SuperConfig SpheroMC_0_20_all = {
  cconfig[62], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  cocktail_files[18], cocktail_files[18], cocktail_files[18], 2.155/2.13 *0.93,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};

SuperConfig SpheroMC_0_20_soft = {
  cconfig[63], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  cocktail_files[18], cocktail_files[18], cocktail_files[18], 2.155/2.13 *0.93*1.126,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};

SuperConfig SpheroMC_0_20_hard = {
  cconfig[64], /*mee_bins, ptee_bins,*/ LmBackground::kHybrid,
  0, 20,
  57.8, 0.99*0.95*0.99, 0.975, 1.0,
  cocktail_files[18], cocktail_files[18], cocktail_files[18], 2.155/2.13 *0.93*0.836,//.80,//1.78 0.82952 0.84
  heavyfl_files[0], heavyfl_histograms[0], 2.5,
  jpsi_list[1],4
};



Bool_t    kUseSuperConfig        = kTRUE;
Bool_t    kDoMassSlices          = kTRUE;  //kTRUE: do mass slices  kFALSE: do pair pt slices
Double_t  kDoEtaScaling          = 1.0;

//SuperConfig sconfig[] = {NewPreFilter_0_100_18Cent, NewPreFilter_0_100_18FAST};
//SuperConfig sconfig[] = {NewPreFilter_0_100_18FAST,PreFilter_0_100_18FAST};
//  SuperConfig sconfig[] = {NewPreFilter_0_100_16f,NewPreFilter_0_100_17g, NewPreFilter_0_100_18Cent, NewPreFilter_0_100_18FAST, PreFilter_0_100_all};
//    SuperConfig sconfig[] = {NewPreFilter_0_100_16f,NewPreFilter_0_100_17g, NewPreFilter_0_100_18Cent, NewPreFilter_0_100_18FAST};

//  SuperConfig sconfig[] = {NewPreFilter_0_100_16f_2,NewPreFilter_0_100_17g_2, NewPreFilter_0_100_18Cent_sys, NewPreFilter_0_100_18FAST};
//    SuperConfig sconfig[] = {NewPreFilter_0_100_16f_2,NewPreFilter_0_100_17g_2, NewPreFilter_0_100_18Cent_2, NewPreFilter_0_100_18FAST_2};
//  SuperConfig sconfig[] = {NewPreFilter_0_20_16f_2,NewPreFilter_0_20_17g_2, NewPreFilter_0_20_18Cent_2, NewPreFilter_0_20_18FAST_2};
//  SuperConfig sconfig[] = {NewPreFilter_20_40_16f_2,NewPreFilter_20_40_17g_2, NewPreFilter_20_40_18Cent_2, NewPreFilter_20_40_18FAST_2};
//  SuperConfig sconfig[] = {NewPreFilter_40_70_16f_2,NewPreFilter_40_70_17g_2, NewPreFilter_40_70_18Cent_2, NewPreFilter_40_70_18FAST_2};
//  SuperConfig sconfig[] = {NewPreFilter_70_100_16f_2,NewPreFilter_70_100_17g_2, NewPreFilter_70_100_18Cent_2, NewPreFilter_70_100_18FAST_2};
//  SuperConfig sconfig[] = {NewPreFilter_0_20_17g_2,NewPreFilter_20_40_17g_2,NewPreFilter_40_70_17g_2,NewPreFilter_70_100_17g_2};
//  SuperConfig sconfig[] = {NewPreFilter_70_100_17g_2,NewPreFilter_40_70_17g_2,NewPreFilter_20_40_17g_2,NewPreFilter_0_20_17g_2};


//  SuperConfig sconfig[] = {
//    NewPreFilter_0_100_16f_2,NewPreFilter_0_100_17g_2, NewPreFilter_0_100_18Cent_2, NewPreFilter_0_100_18FAST_2,
//    NewPreFilter_0_20_16f_2,NewPreFilter_0_20_17g_2, NewPreFilter_0_20_18Cent_2, NewPreFilter_0_20_18FAST_2,
//    NewPreFilter_20_40_16f_2,NewPreFilter_20_40_17g_2, NewPreFilter_20_40_18Cent_2, NewPreFilter_20_40_18FAST_2,
//    NewPreFilter_40_70_16f_2,NewPreFilter_40_70_17g_2, NewPreFilter_40_70_18Cent_2, NewPreFilter_40_70_18FAST_2,
//    NewPreFilter_70_100_16f_2,NewPreFilter_70_100_17g_2, NewPreFilter_70_100_18Cent_2, NewPreFilter_70_100_18FAST_2
//  };




//  SuperConfig sconfig[] = {NewPreFilter_0_100_16f_sys,NewPreFilter_0_100_17g_sys, NewPreFilter_0_100_18Cent_sys, NewPreFilter_0_100_18FAST_sys};
//  SuperConfig sconfig[] = {NewPreFilter_0_100_16f_sys1,NewPreFilter_0_100_17g_sys1, NewPreFilter_0_100_18Cent_sys1, NewPreFilter_0_100_18FAST_sys1, PreFilter_0_100_all};
//  SuperConfig sconfig[] = {NewPreFilter_0_100_16f_sys2,NewPreFilter_0_100_17g_sys2, NewPreFilter_0_100_18Cent_sys2, NewPreFilter_0_100_18FAST_sys2, PreFilter_0_100_all};

//SuperConfig sconfig[] = {NewPreFilter_0_100_18FAST_sys,NewPreFilter_0_100_18FAST_2,NewPreFilter_0_100_18FAST};
//SuperConfig sconfig[] = {NewPreFilter_0_100_18Cent_sys,NewPreFilter_0_100_18Cent_2,NewPreFilter_0_100_18Cent};
//SuperConfig sconfig[] = {NewPreFilter_0_100_17g_sys,NewPreFilter_0_100_17g_2,NewPreFilter_0_100_17g};
//SuperConfig sconfig[] = {NewPreFilter_0_100_16f_sys,NewPreFilter_0_100_16f_2,NewPreFilter_0_100_16f};



//SuperConfig sconfig[] = {NewPreFilter_0_100_18FAST_sys2,NewPreFilter_0_100_18FAST_sys1,NewPreFilter_0_100_18FAST_sys,NewPreFilter_0_100_18FAST_2,NewPreFilter_0_100_18FAST,PreFilter_0_100_18FAST};
//SuperConfig sconfig[] = {PreFilter_0_100_18Cent,NewPreFilter_0_100_18Cent_sys2,NewPreFilter_0_100_18Cent_sys1,NewPreFilter_0_100_18Cent_sys,NewPreFilter_0_100_18Cent_2,NewPreFilter_0_100_18Cent};
//SuperConfig sconfig[] = {NewPreFilter_0_100_17g_sys2,NewPreFilter_0_100_17g_sys1,NewPreFilter_0_100_17g_sys,NewPreFilter_0_100_17g_2,NewPreFilter_0_100_17g,PreFilter_0_100_17g};
//SuperConfig sconfig[] = {NewPreFilter_0_100_16f_sys2,NewPreFilter_0_100_16f_sys1,NewPreFilter_0_100_16f_sys,NewPreFilter_0_100_16f_2,NewPreFilter_0_100_16f,PreFilter_0_100_16f};
//SuperConfig sconfig[] = {NewPreFilter_0_100_18Cent_sys2,NewPreFilter_0_100_18Cent_sys1,NewPreFilter_0_100_18Cent_sys,NewPreFilter_0_100_18Cent_2,NewPreFilter_0_100_18Cent,PreFilter_0_100_18Cent};


//  SuperConfig sconfig[] = {NewPreFilter_0_100_16f,NewPreFilter_0_100_17g, NewPreFilter_0_100_18Cent, NewPreFilter_0_100_18FAST,
//	                   NewPreFilter_0_100_16f_2,NewPreFilter_0_100_17g_2, NewPreFilter_0_100_18Cent_2, NewPreFilter_0_100_18FAST_2,
//                           NewPreFilter_0_100_16f_sys,NewPreFilter_0_100_17g_sys, NewPreFilter_0_100_18Cent_sys, NewPreFilter_0_100_18FAST_sys,
//                           NewPreFilter_0_100_16f_sys1,NewPreFilter_0_100_17g_sys1, NewPreFilter_0_100_18Cent_sys1, NewPreFilter_0_100_18FAST_sys1,
//                           NewPreFilter_0_100_16f_sys2,NewPreFilter_0_100_17g_sys2, NewPreFilter_0_100_18Cent_sys2, NewPreFilter_0_100_18FAST_sys2};
//

//  SuperConfig sconfig[] = {NewPreFilter_0_100_16f_sys,NewPreFilter_0_100_17g_sys, NewPreFilter_0_100_18Cent_sys, NewPreFilter_0_100_18FAST_sys,
//                           NewPreFilter_0_100_16f_sys1,NewPreFilter_0_100_17g_sys1, NewPreFilter_0_100_18Cent_sys1, NewPreFilter_0_100_18FAST_sys1,
//                           NewPreFilter_0_100_16f_sys2,NewPreFilter_0_100_17g_sys2, NewPreFilter_0_100_18Cent_sys2, NewPreFilter_0_100_18FAST_sys2};


//  SuperConfig sconfig[] = {
//                           NewPreFilter_0_100_16f_sys1,NewPreFilter_0_100_17g_sys1, NewPreFilter_0_100_18Cent_sys1, NewPreFilter_0_100_18FAST_sys1,
//                           NewPreFilter_0_100_16f_sys,NewPreFilter_0_100_17g_sys, NewPreFilter_0_100_18Cent_sys, NewPreFilter_0_100_18FAST_sys,
//                           NewPreFilter_0_100_16f_sys2,NewPreFilter_0_100_17g_sys2, NewPreFilter_0_100_18Cent_sys2, NewPreFilter_0_100_18FAST_sys2};
//

//  SuperConfig sconfig[] = {
//	                   NewPreFilter_0_100_16f,NewPreFilter_0_100_17g, NewPreFilter_0_100_18Cent, NewPreFilter_0_100_18FAST,
//	                   NewPreFilter_0_100_16f_2,NewPreFilter_0_100_17g_2, NewPreFilter_0_100_18Cent_2, NewPreFilter_0_100_18FAST_2,
//	                   NewPreFilter_0_100_16f_sys,NewPreFilter_0_100_17g_sys, NewPreFilter_0_100_18Cent_sys, NewPreFilter_0_100_18FAST_sys,
//                           NewPreFilter_0_100_16f_sys1,NewPreFilter_0_100_17g_sys1, NewPreFilter_0_100_18Cent_sys1, NewPreFilter_0_100_18FAST_sys1,
//                           NewPreFilter_0_100_16f_sys2,NewPreFilter_0_100_17g_sys2, NewPreFilter_0_100_18Cent_sys2, NewPreFilter_0_100_18FAST_sys2,
//                           NewPreFilter_0_100_16f_sys3,NewPreFilter_0_100_17g_sys3, NewPreFilter_0_100_18Cent_sys3, NewPreFilter_0_100_18FAST_sys3,
//                           NewPreFilter_0_100_16f_sys4,NewPreFilter_0_100_17g_sys4, NewPreFilter_0_100_18Cent_sys4, NewPreFilter_0_100_18FAST_sys4,
//                           NewPreFilter_0_100_16f_sys5,NewPreFilter_0_100_17g_sys5, NewPreFilter_0_100_18Cent_sys5, NewPreFilter_0_100_18FAST_sys5,
//
//
//  };

  SuperConfig sconfig[] = {
//                           PreFilter_0_100_16f,PreFilter_0_100_17g, PreFilter_0_100_18Cent, PreFilter_0_100_18FAST,
  			   NewPreFilter_0_100_16f_2,NewPreFilter_0_100_17g_2, NewPreFilter_0_100_18Cent_sys, NewPreFilter_0_100_18FAST
//	                   NewPreFilter_0_100_16f,NewPreFilter_0_100_17g, NewPreFilter_0_100_18Cent, NewPreFilter_0_100_18FAST,
//	                   NewPreFilter_0_100_16f_2,NewPreFilter_0_100_17g_2, NewPreFilter_0_100_18Cent_2, NewPreFilter_0_100_18FAST_2,
// //                          NewPreFilter_0_100_16f_sys3,NewPreFilter_0_100_17g_sys3, NewPreFilter_0_100_18Cent_sys3, NewPreFilter_0_100_18FAST_sys3,
// //                          NewPreFilter_0_100_16f_sys4,NewPreFilter_0_100_17g_sys4, NewPreFilter_0_100_18Cent_sys4, NewPreFilter_0_100_18FAST_sys4,
// //                          NewPreFilter_0_100_16f_sys5,NewPreFilter_0_100_17g_sys5, NewPreFilter_0_100_18Cent_sys5, NewPreFilter_0_100_18FAST_sys5,
// //                          NewPreFilter_0_100_16f_sys,NewPreFilter_0_100_17g_sys, NewPreFilter_0_100_18Cent_sys, NewPreFilter_0_100_18FAST_sys,
// //                          NewPreFilter_0_100_16f_sys1,NewPreFilter_0_100_17g_sys1, NewPreFilter_0_100_18Cent_sys1, NewPreFilter_0_100_18FAST_sys1,
// //                          NewPreFilter_0_100_16f_sys2,NewPreFilter_0_100_17g_sys2, NewPreFilter_0_100_18Cent_sys2, NewPreFilter_0_100_18FAST_sys2,
//
//
//
  };








//SuperConfig sconfig[] = {PreFilter_0_100_all,PreFilter_0_100_all3/*,PreFilter_0_100_all3*/, PreFilter_0_100_all};
//  SuperConfig sconfig[] = {PreFilter_0_100_16f,PreFilter_0_100_17g, PreFilter_0_100_18Cent, PreFilter_0_100_18FAST};
//SuperConfig sconfig[] = {PreFilter_0_100_18Cent};

//SuperConfig sconfig[] = {PreFilter_0_100_18Cent, PreFilter_0_100_18FAST, PreFilter_0_100_all};

//SuperConfig sconfig[] = {check_0_100_0};
//  SuperConfig sconfig[] = {check_0_100_0,check_0_100_13, check_0_100_14};

//SuperConfig sconfig[] = {PreFilter_0_100_1617,PreFilter_0_100_all};//, PreFilter_0_10, PreFilter_70_100};
//SuperConfig sconfig[] = {PreFilter_0_100_all, PreFilter_0_10, PreFilter_10_20, PreFilter_20_40, PreFilter_40_70, PreFilter_70_100};
//SuperConfig sconfig[] = {PreFilter_0_20, PreFilter_20_40, PreFilter_40_70, PreFilter_70_100};
//  SuperConfig sconfig[] = {PreFilter_0_100_all2,PreFilter_0_100_all3,PreFilter_0_100_all4};
//SuperConfig sconfig[] = {PreFilter_0_100_all, PreFilter_0_40, PreFilter_40_100};
//  SuperConfig sconfig[] = {PreFilter_0_100_all};
//  SuperConfig sconfig[] = {PreFilter_0_20};
//  SuperConfig sconfig[] = {PreFilter_0_10_all,PreFilter_0_10_hard,PreFilter_0_10_soft};
//SuperConfig sconfig[] = {PreFilter_0_10_hard,PreFilter_0_10_soft};
//SuperConfig sconfig[] = {PreFilter_0_10_hard};

//SuperConfig sconfig[] = {Sphero_0_10_hard,Sphero_0_10_soft};
//SuperConfig sconfig[] = {Sphero_0_10_all,Sphero_0_10_hard,Sphero_0_10_soft};

//SuperConfig sconfig[] = {Sphero_20_40_soft,Sphero_10_20_soft,Sphero_0_10_soft};
//SuperConfig sconfig[] = {Sphero_20_40_hard,Sphero_10_20_hard,Sphero_0_10_hard};

//  SuperConfig sconfig[] = {SpheroMC_0_20_all,SpheroMC_0_20_hard,SpheroMC_0_20_soft};
//SuperConfig sconfig[] = {SpheroMC_0_20_all};


//SuperConfig sconfig[] = {PreFilter_0_20};
//SuperConfig sconfig[] = {PreFilter_0_100_1617_woPF};
//SuperConfig sconfig[] = {PreFilter_0_100_18Cent,PreFilter_0_10_18Cent};//, PreFilter_0_10, PreFilter_70_100};

Int_t n_sconfig = sizeof(sconfig)/sizeof(*sconfig);
