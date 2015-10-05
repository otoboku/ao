// t_btrev
typedef struct _SSRATE_BASE // 0x20
{
    ULONG   MSFile;
    USHORT  HP;     // 0x4
    USHORT  STR;    // 0x6
    USHORT  DEF;    // 0x8
    USHORT  ATS;    // 0xA
    USHORT  ADF;    // 0xC
    USHORT  SPD;    // 0xE
    ULONG   N_REG;  // 0x10
    ULONG   E_REG;  // 0x14
    ULONG   N_AI;   // 0x18
    ULONG   E_AI;   // 0x1C
} SSRATE_BASE;

typedef struct _STATUS_RATE_DIF // 0xC
{
    USHORT  HP;     // 0x0
    USHORT  STR;    // 0x2
    USHORT  DEF;    // 0x4
    USHORT  ATS;    // 0x6
    USHORT  ADF;    // 0x8
    USHORT  _uA;    // 0xA
} SSRATE_DIF;

/*
SSRATE_BASE sRateBaseDefault = { 0, 100, 100, 100, 100, 100, 100, };
INT         sRevise[4]  = { 0, -4, -9, 6 };
SSRATE_DIF  sRateDif[4] = 
{
    { 100, 100, 100, 100, 100, 100, },
    {  85,  90,  90, 100, 100, 100, },
    {  70,  70,  70,  70,  70, 100, },
    { 100, 100, 100, 100, 100, 100, },
};

//[int(i * 20 / 100 + 100) for i in [85,  90,  90, 100, 100, 100]]
//[int(i * 45 / 100 + 100) for i in [70,  70,  70,  70,  70, 100]]
SSRATE_DIF  sRateDifFinal[4] = 
{
    { 100, 100, 100, 100, 100, 100, },
    { 117, 118, 118, 120, 120, 120, },
    { 131, 131, 131, 131, 131, 145, },
    {  70,  70,  70,  70,  70,  70, },
};
*/