#include "table.h"

// for i in range(0,128):
//     print '%.f, ' % (i * 16384.0 / 120.0)
const int table_n[128] = {
    0,     137,   273,   410,   546,   683,   819,   956,   1092,  1229,  1365,
    1502,  1638,  1775,  1911,  2048,  2185,  2321,  2458,  2594,  2731,  2867,
    3004,  3140,  3277,  3413,  3550,  3686,  3823,  3959,  4096,  4233,  4369,
    4506,  4642,  4779,  4915,  5052,  5188,  5325,  5461,  5598,  5734,  5871,
    6007,  6144,  6281,  6417,  6554,  6690,  6827,  6963,  7100,  7236,  7373,
    7509,  7646,  7782,  7919,  8055,  8192,  8329,  8465,  8602,  8738,  8875,
    9011,  9148,  9284,  9421,  9557,  9694,  9830,  9967,  10103, 10240, 10377,
    10513, 10650, 10786, 10923, 11059, 11196, 11332, 11469, 11605, 11742, 11878,
    12015, 12151, 12288, 12425, 12561, 12698, 12834, 12971, 13107, 13244, 13380,
    13517, 13653, 13790, 13926, 14063, 14199, 14336, 14473, 14609, 14746, 14882,
    15019, 15155, 15292, 15428, 15565, 15701, 15838, 15974, 16111, 16247, 16384,
    16521, 16657, 16794, 16930, 17067, 17203, 17340
};

// const int table_v[11] = {0, 3277, 6554, 9830, 13107, 16384, 19661, 22938,
// 26214, 29491, 32768 };
const int table_v[11] = { 0,    1638,  3277,  4915,  6554, 8192,
                          9830, 11469, 13107, 14746, 16384 };


const int table_vv[100] = {
    0,    16,   33,   49,   66,   82,   98,   115,  131,  147,  164,  180,
    197,  213,  229,  246,  262,  279,  295,  311,  328,  344,  360,  377,
    393,  410,  426,  442,  459,  475,  492,  508,  524,  541,  557,  573,
    590,  606,  623,  639,  655,  672,  688,  705,  721,  737,  754,  770,
    786,  803,  819,  836,  852,  868,  885,  901,  918,  934,  950,  967,
    983,  999,  1016, 1032, 1049, 1065, 1081, 1098, 1114, 1130, 1147, 1163,
    1180, 1196, 1212, 1229, 1245, 1262, 1278, 1294, 1311, 1327, 1343, 1360,
    1376, 1393, 1409, 1425, 1442, 1458, 1475, 1491, 1507, 1524, 1540, 1556,
    1573, 1589, 1606, 1622
};

//>>> for i in range(0,256):
//...     print '%.0f, ' % (math.pow(i/64.,4)*16384./256.)
const int table_exp[256] = {
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,     0,     0,     0,     0,     0,     0,     0,     0,     1,     1,
    1,     1,     1,     1,     2,     2,     2,     3,     3,     4,     4,
    5,     5,     6,     6,     7,     8,     9,     10,    11,    12,    13,
    14,    16,    17,    19,    20,    22,    24,    26,    28,    30,    32,
    35,    38,    40,    43,    46,    49,    53,    56,    60,    64,    68,
    72,    77,    82,    86,    92,    97,    103,   108,   114,   121,   127,
    134,   141,   149,   156,   164,   172,   181,   190,   199,   209,   219,
    229,   239,   250,   262,   273,   285,   298,   311,   324,   338,   352,
    366,   381,   397,   413,   429,   446,   464,   482,   500,   519,   538,
    559,   579,   600,   622,   644,   667,   691,   715,   740,   765,   791,
    818,   845,   873,   902,   931,   961,   992,   1024,  1056,  1090,  1123,
    1158,  1194,  1230,  1267,  1305,  1344,  1383,  1424,  1465,  1508,  1551,
    1595,  1640,  1686,  1733,  1781,  1830,  1880,  1931,  1983,  2036,  2090,
    2146,  2202,  2259,  2318,  2377,  2438,  2500,  2563,  2627,  2693,  2760,
    2827,  2897,  2967,  3039,  3112,  3186,  3262,  3339,  3417,  3497,  3578,
    3660,  3744,  3829,  3916,  4005,  4094,  4185,  4278,  4373,  4468,  4566,
    4665,  4765,  4868,  4971,  5077,  5184,  5293,  5403,  5516,  5630,  5745,
    5863,  5982,  6104,  6227,  6351,  6478,  6607,  6737,  6870,  7004,  7140,
    7279,  7419,  7561,  7706,  7852,  8000,  8151,  8304,  8459,  8616,  8775,
    8936,  9100,  9266,  9434,  9604,  9777,  9952,  10129, 10309, 10491, 10675,
    10862, 11051, 11243, 11437, 11634, 11833, 12035, 12240, 12447, 12656, 12869,
    13083, 13301, 13521, 13744, 13970, 14199, 14430, 14664, 14901, 15141, 15384,
    15629, 15878, 16129
};
