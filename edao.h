#ifndef _EDAO_H_5c8a3013_4334_4138_9413_3d0209da878e_
#define _EDAO_H_5c8a3013_4334_4138_9413_3d0209da878e_

#define DIRECTINPUT_VERSION 0x800

#include "MyLibrary.h"
#include <GdiPlus.h>
#include <dinput.h>

#if D3D9_VER
    #define NtGetTickCount (ULONG64)GetTickCount
#endif

#pragma warning (disable: 4201)
#pragma warning (disable: 4996)

ML_OVERLOAD_NEW

class EDAO;
class CGlobal;
class CScript;
class CSSaveData;
class CBattle;

class CMap;
class CInput;
class CSound;
class CCamera;
class CMiniGame;
class CDebug;

#define CActor CSSaveData

#define INIT_STATIC_MEMBER(x) DECL_SELECTANY TYPE_OF(x) x = NULL
#define DECL_STATIC_METHOD_POINTER(cls, method) static TYPE_OF(&cls::method) Stub##method
#define DETOUR_METHOD(cls, method, addr, ...) TYPE_OF(&cls::method) (method); *(PULONG_PTR)&(method) = addr; return (this->*method)(__VA_ARGS__)
#define DETOUR_METHOD_NO_RET(cls, method, addr) TYPE_OF(&cls::method) Stub##method; *(PULONG_PTR)&(Stub##method) = addr


#define MINIMUM_CUSTOM_CHAR_ID          0xB0
#define MINIMUM_CUSTOM_CRAFT_INDEX      0x3E8
#define MAXIMUM_CHR_NUMBER_IN_BATTLE    0x16
#define MAXIMUM_CHR_NUMBER_WITH_STATUS  0xC
#define SCENA_FLAG_COUNT                0x220

#define PSP_WIDTH_F                       480.f
#define PSP_HEIGHT_F                      272.f

#pragma pack(push, 1)

typedef struct
{
    ULONG Magic;
    ULONG CompressedSize;

} UCL_COMPRESS_HEADER;


ML_NAMESPACE_BEGIN(CraftConditions)

    static const ULONG_PTR Poison              = 0x00000001;
    static const ULONG_PTR Frozen              = 0x00000002;
    static const ULONG_PTR Landification       = 0x00000004;
    static const ULONG_PTR Sleeping            = 0x00000008;
    static const ULONG_PTR BanArts             = 0x00000010;
    static const ULONG_PTR Darkness            = 0x00000020;
    static const ULONG_PTR BanCraft            = 0x00000040;
    static const ULONG_PTR Confusion           = 0x00000080;
    static const ULONG_PTR Stun                = 0x00000100;
    static const ULONG_PTR OnehitKill          = 0x00000200;
    static const ULONG_PTR Burning             = 0x00000400;
    static const ULONG_PTR Rage                = 0x00000800;
    static const ULONG_PTR ArtsGuard           = 0x00001000;
    static const ULONG_PTR CraftGuard          = 0x00002000;

    static const ULONG_PTR MaxGuard            = 0x00004000;
    static const ULONG_PTR Vanish              = 0x00008000;
    static const ULONG_PTR StrUp               = 0x00010000;
    static const ULONG_PTR DefUp               = 0x00020000;
    static const ULONG_PTR AtsUp               = 0x00040000;
    static const ULONG_PTR AdfUp               = 0x00080000;
    static const ULONG_PTR DexUp               = 0x00100000;
    static const ULONG_PTR AglUp               = 0x00200000;
    static const ULONG_PTR MovUp               = 0x00400000;
    static const ULONG_PTR SpdUp               = 0x00800000;
    static const ULONG_PTR HPRecovery          = 0x01000000;
    static const ULONG_PTR CPRecovery          = 0x02000000;

    static const ULONG_PTR Stealth             = 0x04000000;
    static const ULONG_PTR ArtsReflect         = 0x08000000;
    static const ULONG_PTR BurningHeart        = 0x10000000;
    static const ULONG_PTR Reserve_1           = 0x10000000;
    static const ULONG_PTR Reserve_2           = 0x20000000;
    static const ULONG_PTR Reserve_3           = 0x40000000;
    static const ULONG_PTR BodyAbnormal        = 0x40000000;

    static const ULONG_PTR Dead                = 0x80000000;

    static const SHORT BodyAbnormal_Little = 0x2;
    static const SHORT BodyAbnormal_GreenPepper = 0x3;

ML_NAMESPACE_END

ML_NAMESPACE_BEGIN(BattleActionScript)
enum
{
    SysCraft_Init           = 0x00,
    SysCraft_Stand          = 0x01,
    SysCraft_Move           = 0x02,
    SysCraft_UnderAttack    = 0x03,
    SysCraft_Dead           = 0x04,
    SysCraft_NormalAttack   = 0x05,
    SysCraft_ArtsAria       = 0x06,
    SysCraft_ArtsCast       = 0x07,
    SysCraft_Win            = 0x08,
    SysCraft_EnterBattle    = 0x09,
    SysCraft_UseItem        = 0x0A,
    SysCraft_Stun           = 0x0B,
    SysCraft_Unknown2       = 0x0C,
    SysCraft_Reserve1       = 0x0D,
    SysCraft_Reserve2       = 0x0E,
    SysCraft_Counter        = 0x0F,
    SysCraft_TeamRushInit   = 0x1E,
    SysCraft_TeamRushAction = 0x1F,

    INVALID_ACTION_OFFSET   = 0xFFFF,
    EMPTY_ACTION            = INVALID_ACTION_OFFSET,
};
ML_NAMESPACE_END

ML_NAMESPACE_BEGIN(T_NAME)
enum
{
    Lloyd       = 0x0,
    Elie        = 0x1,
    Tio         = 0x2,
    Randy       = 0x3,

    Lazy        = 0x4,
    Waji        = 0x4,

    Yin         = 0x5,
    Rixia       = 0x5,
    INNE        = 0x5,

    Zeit        = 0x6,
    Arios       = 0x7,
    Noel        = 0x8,
    Dudley      = 0x9,
    Garcia      = 0xA,
    ReserveB    = 0xB,
    CHR_COUNT   = 0xC,
};

DECL_SELECTANY
char* ChrName[] = {"Lloyd", "Elie", "Tio", "Randy", "Lazy", "Yin", "Zeit", "Arios", "Noel", "Dudley", "Garcia", "ReserveB"};
DECL_SELECTANY
char* ChrNameChs[] = {"������", "����", "�ŷ", "����", "�߼�", "��", "���ǲ���", "����ŷ˹", "ŵ������ʿ", "������Ѳ��", "�Ӷ�����", "����B"};

ML_NAMESPACE_END

typedef struct  // 0x18
{
    BYTE    Condition;
    BYTE    Probability;
    BYTE    Target;
    BYTE    TargetCondition;
    BYTE    AriaActionIndex;
    BYTE    ActionIndex;
    USHORT  CraftIndex;
    ULONG   Parameter[4];

} CRAFT_AI_INFO, *PCRAFT_AI_INFO;

typedef struct
{
    USHORT  ActionIndex;
    BYTE    Target;
    BYTE    Unknown_3;
    BYTE    Attribute;
    BYTE    RangeType;
    BYTE    State1;
    BYTE    State2;
    BYTE    RNG;
    BYTE    RangeSize;
    BYTE    AriaTime;
    BYTE    SkillTime;
    USHORT  EP_CP;
    USHORT  RangeSize2;
    USHORT  State1Parameter;
    USHORT  State1Time;
    USHORT  State2Parameter;
    USHORT  State2Time;

    DUMMY_STRUCT(4);

} CRAFT_INFO, *PCRAFT_INFO;

typedef struct
{
    CHAR Description[0x100];
    CHAR Name[0x20];

} CRAFT_DESCRIPTION;

enum
{
    ACTION_ATTACK       = 0,
    ACTION_MOVE         = 1,
    ACTION_MAGIC        = 2,
    ACTION_CRAFT        = 3,
    ACTION_SCRAFT       = 4,
    ACTION_ITEM         = 5,
    ACTION_ARIA_MAGIC   = 6,
    ACTION_CAST_MAGIC   = 7,
    ACTION_ARIA_CRAFT   = 8,
    ACTION_CAST_CRAFT   = 9,
};

enum
{
    BattleStatusRaw,
    BattleStatusFinal,
};


typedef union
{
    DUMMY_STRUCT(0x34);

    struct
    {
        ULONG                   MaximumHP;                  // 0x0     0x234    0x268
        ULONG                   InitialHP;                  // 0x4     0x238    0x26C
        USHORT                  Level;                      // 0x8     0x23C    0x270
        USHORT                  MaximumEP;                  // 0xA     0x23E    0x272
        USHORT                  InitialEP;                  // 0xC     0x240    0x274
        USHORT                  InitialCP;                  // 0xE     0x242    0x276
        ULONG                   EXP;                        // 0x10    0x244    0x278
        //DUMMY_STRUCT(2);

        SHORT                   STR;                        // 0x14    0x248    0x27C
        SHORT                   DEF;                        // 0x16    0x24A    0x27E
        SHORT                   ATS;                        // 0x18    0x24C    0x280
        SHORT                   ADF;                        // 0x1A    0x24E    0x282
        SHORT                   DEX;                        // 0x1C    0x250    0x284
        SHORT                   AGL;                        // 0x1E    0x252    0x286
        SHORT                   MOV;                        // 0x20    0x254    0x288
        SHORT                   SPD;                        // 0x22    0x256    0x28A
        SHORT                   DEXRate;                    // 0x24    0x258    0x28C
        SHORT                   AGLRate;                    // 0x26    0x25A    0x28E
        USHORT                  MaximumCP;                  // 0x28    0x25C    0x290

        DUMMY_STRUCT(2);                                    // 0x25E

        USHORT                  RNG;                        // 0x2C    0x260    0x294

        DUMMY_STRUCT(2);

        ULONG                   ConditionFlags;             // 0x30    0x264    0x298
    };

} CHAR_STATUS, *PCHAR_STATUS;

typedef struct _CHAR_T_STATUS
{
    USHORT      Level;
    //USHORT      HP;
    //USHORT      EP;
    UINT        HP;
    USHORT      STR;
    USHORT      DEF;
    USHORT      ATS;
    USHORT      ADF;
    USHORT      DEX;
    USHORT      AGL;
    USHORT      AGLRate;
    USHORT      MOV;
    USHORT      SPD;
    USHORT      DEXRate;
    USHORT      RNG;
} CHAR_T_STATUS, *PCHAR_T_STATUS;

typedef struct _CHAR_T_STATUS_RatioX
{
    float      HP;
    float      EP;
    float      STR;
    float      DEF;
    float      ATS;
    float      ADF;
    float      DEX;
    float      AGL;
    float      MOV;
    float      SPD;
    float      DEXRate;
    float      AGLRate;
    float      RNG;
} CHAR_T_STATUS_RatioX;

typedef struct _CHAR_T_STATUS_RatioY
{
    INT      HP;
    INT      EP;
    INT      STR;
    INT      DEF;
    INT      ATS;
    INT      ADF;
    INT      DEX;
    INT      AGL;
    INT      MOV;
    INT      SPD;
    INT      DEXRate;
    INT      AGLRate;
    INT      RNG;
} CHAR_T_STATUS_RatioY;

typedef struct
{
    ULONG               ConditionFlags;
    PVOID               Effect;
    //BYTE                Unknown2[2];
    BYTE                Type; // 1 �غ�; 2 ����; 3 AT�������ٴ�; 4 ����
    BYTE                Flag;
    SHORT               ConditionRate;
    ULONG               ATLeft;
    ULONG               Unknown4;

} MS_EFFECT_INFO, *PMS_EFFECT_INFO;

enum
{
    CHR_FLAG_ENEMY  = 0x1000,
    CHR_FLAG_NPC    = 0x2000,
    CHR_FLAG_PLAYER = 0x4000,
    CHR_FLAG_EMPTY  = 0x8000,
};

enum
{
    CHR_FLAG2_ResistBeatBack    = 0x0200,
    CHR_FLAG2_ResistATDelay     = 0x0800,
    //CHR_FLAG2_AbsoluteMiss      = 0x2000,
};

//typedef union _MONSTER_STATUS
typedef struct _MONSTER_STATUS
{
    //DUMMY_STRUCT(0x2424);

    BOOL IsChrEnemy()
    {
        return AiType != 0xFF && !FLAG_ON(State, CHR_FLAG_NPC | CHR_FLAG_PLAYER | CHR_FLAG_EMPTY);
    }

    BOOL IsChrEnemyOnly()
    {
        return !FLAG_ON(State, CHR_FLAG_NPC | CHR_FLAG_PLAYER | CHR_FLAG_EMPTY);
    }

    BOOL IsChrEmpty()
    {
        return FLAG_ON(State, CHR_FLAG_EMPTY);
    }

    BOOL IsChrCanThinkSCraft(BOOL CheckAiType = FALSE)
    {
        if (!IsChrEnemy())
            return FALSE;

        if (AiType == 0xFF)
            return FALSE;

        if (!CheckAiType)
            return TRUE;

        switch (AiType)
        {
            case 0x00:
            case 0x02:
            case 0x1F:
                return TRUE;
        }

        return FALSE;
    }

    //struct
    //{

        USHORT                  CharPosition;               // 0x00
        USHORT                  State;                      // 0x02
        USHORT                  State2;                     // 0x04
        DUMMY_STRUCT(4);                                    // 0x06
        USHORT                  CharID;                     // 0x0A
        DUMMY_STRUCT(4);                                    // 0x0C
        ULONG                   SymbolIndex;                // 0x10
        ULONG                   MSFileIndex;                // 0x14
        ULONG                   ASFileIndex;                // 0x18
        DUMMY_STRUCT(1);                                    // 0x1C
        BYTE                    TeamRushAddition;           // 0x1D
        USHORT                  MasterQuartzUsedFlag;       // 0x1E
        
        DUMMY_STRUCT(0x16C - 0x20);

        USHORT                  CurrentActionType;          // 0x16C

        DUMMY_STRUCT(2);

        USHORT                  PreviousActionType;         // 0x170
        USHORT                  SelectedActionType;         // 0x172
        USHORT                  Unknown_174;
        USHORT                  Unknown_176;
        USHORT                  Unknown_178;
        USHORT                  Unknown_17A;
        USHORT                  WhoAttackMe;                // 0x17C
        USHORT                  CurrentCraftIndex;          // 0x17E
        USHORT                  LastActionIndex;            // 0x180
        USHORT                  CurrentAiIndex;             // 0x182

        DUMMY_STRUCT(0x1AA - 0x184);

        USHORT                  Target[0x10];               // 0x1AA
        BYTE                    TargetCount;                // 0x1CA
        BYTE                    SelectedTargetIndex;        // 0x1CB
        COORD                   SelectedTargetPos;          // 0x1CC

        DUMMY_STRUCT(0x234 - 0x1D0);

        CHAR_STATUS ChrStatus[2];                           // 0x234

        USHORT MoveSPD;                                     // 0x29C

        DUMMY_STRUCT(2);

        MS_EFFECT_INFO          EffectInfo[32];             // 0x2A0

        DUMMY_STRUCT(0x538 - (0x2A0 + sizeof(MS_EFFECT_INFO) * 32));

        ULONG                   AT;                         // 0x538
        ULONG                   AT2;                        // 0x53C
        USHORT                  AiType;                     // 0x540
        USHORT                  EXPGet;                     // 0x542
        USHORT                  DropItem[2];                // 0x544
        BYTE                    DropRate[2];                // 0x548

        DUMMY_STRUCT(2);

        USHORT                  Equipment[5];               // 0x54C
        USHORT                  Orbment[7];                 // 0x556
        CRAFT_AI_INFO           Attack;                     // 0x564
        CRAFT_AI_INFO           MagicAiInfo[80];            // 0x57C
        CRAFT_AI_INFO           CraftAiInfo[15];            // 0xCFC
        CRAFT_AI_INFO           SCraftAiInfo[5];            // 0xE64
        CRAFT_AI_INFO           SupportAiInfo[3];           // 0xEDC

        struct
        {
            USHORT                  CraftIndex;             // 0xF24
            BYTE                    AriaActionIndex;        // 0xF26
            BYTE                    ActionIndex;            // 0xF27

        } SelectedCraft;

        BYTE                    Runaway[4];                 // 0xF28

        CRAFT_INFO                  CraftInfo[16];          // 0xF2C
        CRAFT_DESCRIPTION           CraftDescription[16];   // 0x10EC

        BYTE                    Sepith[7];                  // 0x22EC
        DUMMY_STRUCT(3);
        USHORT  				AttributeRate[7];           // 0x22F6
        ULONG       			Resistance;					// 0x2304
        DUMMY_STRUCT(0x78);
        char				    CharacterIntro[0x80];		// 0x2380

        //DUMMY_STRUCT(0x2408 - 0x10EC - sizeof(CRAFT_DESCRIPTION) * 10);
        DUMMY_STRUCT(0x2408 - 0x2380 - 0x80);
        ULONG                       SummonCount;            // 0x2408
        DUMMY_STRUCT(0x2424 - 0x2408 - 0x4);

    //};

} MONSTER_STATUS, *PMONSTER_STATUS;

typedef union _AS_FILE
{
    ULONG GetActionCount()
    {
        ULONG Count = 0;
        PUSHORT ActionList = (PUSHORT)PtrAdd(this, (ULONG)ActionListOffset);
        while (ActionList < (PUSHORT)PtrAdd(this, sizeof(*this)) && *ActionList != 0)
        {
            Count++;
            ActionList++;
        }
        return Count;
    }

    BOOL IsActionValid(ULONG ActionNo, ULONG ActionCount)
    {
        if (ActionNo >= ActionCount)
            return FALSE;
        PUSHORT ActionList = (PUSHORT)PtrAdd(this, (ULONG)ActionListOffset);
        if (ActionList[ActionNo] == BattleActionScript::EMPTY_ACTION)
            return FALSE;
        return TRUE;
    }

    DUMMY_STRUCT(0x5F00);
    struct
    {
        USHORT      ActionListOffset;
        USHORT      ChrPosFactorOffset;
    };
} AS_FILE, *PAS_FILE;



EDAO* GlobalGetEDAO();

class CSSaveData
{
#pragma pack(push, 1)
    typedef union
    {
        DUMMY_STRUCT(0x4C4);
        struct
        {
            DUMMY_STRUCT(0x4);
            INT     Adapter;        // 0x4
            INT     Device;
            INT     Mode;
            INT     WindowWidth;    // 0x10
            INT     WindowHeight;   // 0x14
            DUMMY_STRUCT(0x475-0x18); 
            BYTE    WindowMode;     // 0x475
            DUMMY_STRUCT(0x484-0x476); 
            BYTE    BgmVolumeIni;   // 0x484    ini
            BYTE    SeVolumeIni;    // 0x485
            BYTE    BgmOff;         // 0x486    ini invalid
            BYTE    SeOff;          // 0x487    ini invalid
            DUMMY_STRUCT(0x34);
            BYTE    BgmVolume;      // 0x4BC    81C68
            BYTE    SeVolume;       // 0x4BD    81C69
            DUMMY_STRUCT(0x2);
            ULONG   Option;         // 0x4C0
            
        } ;
        
    } SystemConfigData;
    
    typedef struct 
    {
        DUMMY_STRUCT(0x7EDD6);
        USHORT  TitleVisualCount1;  // 0x7EDD6
        DUMMY_STRUCT(0x817AC - 0x7EDD6 - 2);   
        //DUMMY_STRUCT(0x817AC);
        SystemConfigData Config;    // 0x817AC                             
        DUMMY_STRUCT(0xC);
        UINT64  Record;             // 0x81C7C
        ULONG   Tokuten;            // 0x81C84
        ULONG   Medal;              // 0x81C88
        DUMMY_STRUCT(0x8);
        ULONG   GameAccount;        // 0x81C94 invalid bug? PomttoAccount
        DUMMY_STRUCT(0x25434 - 0xC);
        ULONG   TitleVisualCount;   // 0xA70C0
        ULONG   ExtraMode;          // 0xA70C4
        DUMMY_STRUCT(0x4);
        ULONG   Unknown_4D4;        // 0xA70CC
        
    } MemorySystemData;
    
    
    typedef union  // 0x504
    {
        DUMMY_STRUCT(0x504);
        struct
        {
            SystemConfigData Config;
            UINT64  Record;             // 0x4C4
            ULONG   ExtraMode;          // 0x4CC
            ULONG   Tokuten;            // 0x4D0
            ULONG   Unknown_4D4;        // 0x4D4
            ULONG   Medal;              // 0x4D8
            ULONG   TitleVisualCount;   // 0x4DC
            ULONG   GameAccount;        // 0x4E0
        };
        
    } LocalSystemData;
#pragma pack(pop)

public:
    VOID SaveData2SystemData();
    VOID SystemData2SaveData();

    EDAO* GetEDAO()
    {
        return (EDAO *)PtrSub(this, 0x78CB8);
    }

    MemorySystemData* GetMemorySystemData()
    {
        return (MemorySystemData*)GetEDAO();
    }

    // SaveData2SystemData()
    VOID THISCALL SaveSystemData(LocalSystemData* pLocal)
    {
        if (pLocal == NULL)
            return;

        MemorySystemData* pMemory = GetMemorySystemData();
        ZeroMemory(pLocal, sizeof(*pLocal));

        pLocal->Config = pMemory->Config;
        pLocal->Record = pMemory->Record;
        pLocal->ExtraMode = pMemory->ExtraMode;
        pLocal->Tokuten = pMemory->Tokuten;
        pLocal->Unknown_4D4 = pMemory->Unknown_4D4;
        pLocal->Medal = pMemory->Medal;
        pLocal->TitleVisualCount = MY_MAX(pMemory->TitleVisualCount, pMemory->TitleVisualCount1);
        pLocal->GameAccount = pMemory->GameAccount;

    }

    // SystemData2SaveData()
    VOID THISCALL LoadSystemData(LocalSystemData* pLocal)
    {
        if (pLocal == NULL)
            return;

        MemorySystemData* pMemory = GetMemorySystemData();

        //pMemory->Config = pLocal->Config;
        if (pLocal->Config.WindowMode == 0 && pLocal->Config.WindowWidth == 0){}
        else
            pMemory->Config.Option = pLocal->Config.Option;
        pMemory->Record = pLocal->Record;
        pMemory->ExtraMode = pLocal->ExtraMode;
        pMemory->Tokuten = pLocal->Tokuten;
        pMemory->Unknown_4D4 = pLocal->Unknown_4D4;
        pMemory->Medal = pLocal->Medal;
        pMemory->TitleVisualCount = pLocal->TitleVisualCount;
        pMemory->GameAccount = pLocal->GameAccount;       
    }

public:

    PUSHORT GetPartyChipMap()
    {
        return (PUSHORT)PtrAdd(this, 0x6140);
    }

    PUSHORT GetPartyList()
    {
        return (PUSHORT)PtrAdd(this, 0x2CC);
    }

    PUSHORT GetPartyListSaved()
    {
        return (PUSHORT)PtrAdd(this, 0x2DC);
    }

    BOOL IsCustomChar(ULONG_PTR ChrId)
    {
        //mark
        if (ChrId >= 0xC)
            return FALSE;
        return GetPartyChipMap()[ChrId] >= MINIMUM_CUSTOM_CHAR_ID;
    }

    PUSHORT GetChrMagicList()
    {
        return (PUSHORT)PtrAdd(this, 0x5D4);
    }

    PBYTE GetScenaFlags()
    {
        return (PBYTE)PtrAdd(this, 0x9C);
    }

    BOOL IsYinRixia()
    {
        return FLAG_ON(GetScenaFlags()[0x165], 1 << 5);
    }

    BOOL IsLazyKnight()
    {
        return FLAG_ON(GetScenaFlags()[0x1A0], 1);
    }

    ULONG FASTCALL GetTeamAttackMemberId(ULONG ChrId);


    // mark
    VOID THISCALL SetChrPositionAuto(ULONG ChrId, PUSHORT pPartyList, ULONG ChrCount)
    {
        DETOUR_METHOD(CActor, SetChrPositionAuto, 0x676628, ChrId, pPartyList, ChrCount);
    }

public:
    DUMMY_STRUCT(0x9C);
    BYTE        Flag[SCENA_FLAG_COUNT];     // 0x9C
    PVOID       pScenaCharacterInf[2];
    ULONG       ScenaCharacterCount[2];
    USHORT      PartyList[8];               // 0x2CC
    USHORT      PartyListSaved[8];          // 0x2DC
    CHAR_STATUS ChrStatus[MAXIMUM_CHR_NUMBER_WITH_STATUS]; // 0x2EC

};
#pragma pack(pop)

typedef union
{
    ULONG Flags;
    struct
    {
        UCHAR   HP              : 1;        // 0x00000001
        UCHAR   Level           : 1;        // 0x00000002
        UCHAR   EXP             : 1;        // 0x00000004
        UCHAR   Information     : 1;
        UCHAR   Resist          : 1;        // 0x00000020
        UCHAR   AttributeRate   : 1;        // 0x00000040

                                            // 0x10000000   orb
    };

    BOOL AllValid()
    {
        ULONG AllFlags = 0x01 | 0x02 | 0x04 | 0x20 | 0x40;
        return (Flags & AllFlags) == AllFlags;
    }

    BOOL IsShowByOrbment()
    {
        return FLAG_ON(Flags, 0x10000000);
    }

} MONSTER_INFO_FLAGS, *PMONSTER_INFO_FLAGS;



enum
{
    COLOR_WHITE     = 0,
    COLOR_ORANGE    = 1,
    COLOR_RED       = 2,
    COLOR_BLUE      = 3,
    COLOR_YELLOW    = 4,
    COLOR_GREEN     = 5,
    COLOR_GRAY      = 6,
    COLOR_PINK      = 7,
    COLOR_GOLD      = 8,
    COLOR_BLACK     = 9,
    COLOR_YELLOWB   = 10,


    COLOR_MAXIMUM   = 21,
};

class CBattleInfoBox
{
public:
    EDAO* GetEDAO()
    {
        return *(EDAO **)PtrAdd(this, 0xC);
    }

    CBattle* GetBattle()
    {
        return (CBattle *)PtrSub(this, 0xF0D24);
    }

    PCOORD GetUpperLeftCoord()
    {
        return (PCOORD)PtrAdd(*(PULONG_PTR)PtrAdd(this, 0x20), 0xF2);
    }

    ULONG_PTR GetBackgroundColor()
    {
        return *(PULONG)PtrAdd(*(PULONG_PTR)PtrAdd(this, 0x20), 0x100);
    }

    VOID SetTargetIsEnemy(BOOL Is)
    {
        *(PULONG)PtrAdd(*(PULONG_PTR)PtrAdd(this, 0x20), 0xEC) = Is ? 0 : 1;
    }

    ULONG_PTR IsTargetEnemy()
    {
        return *(PULONG)PtrAdd(*(PULONG_PTR)PtrAdd(this, 0x20), 0xEC) != 1;
    }

    VOID SetMonsterInfoFlags(ULONG_PTR Flags)
    {
        *(PULONG_PTR)PtrAdd(this, 0x1028) = Flags;
    }

    MONSTER_INFO_FLAGS GetMonsterInfoFlags()
    {
        return *(PMONSTER_INFO_FLAGS)PtrAdd(this, 0x1028);
    }

    NoInline VOID DrawSimpleText(LONG X, LONG Y, PCSTR Text, ULONG ColorIndex, LONG Weight = FW_NORMAL, ULONG ZeroU1 = 1, FLOAT ZeroF1 = 1)
    {
        TYPE_OF(&CBattleInfoBox::DrawSimpleText) StubDrawSimpleText;

        *(PVOID *)&StubDrawSimpleText = (PVOID)0x67A101;

        return (this->*StubDrawSimpleText)(X, Y, Text, ColorIndex, Weight, ZeroU1, ZeroF1);
    }

public:
    VOID THISCALL SetMonsterInfoBoxSize(LONG X, LONG Y, LONG Width, LONG Height);
    VOID THISCALL DrawMonsterStatus();

    DECL_STATIC_METHOD_POINTER(CBattleInfoBox, DrawMonsterStatus);
};

INIT_STATIC_MEMBER(CBattleInfoBox::StubDrawMonsterStatus);

typedef union
{
    DUMMY_STRUCT(0x78);
    struct
    {
        DUMMY_STRUCT(0x60);

        PMONSTER_STATUS MSData;     // 0x60

        CBattle* Battle;

        ULONG   IconAT;             // 0x68
        USHORT  Flags;              // 0x6C ����20 ��; ��10 AT���ƶ�; ��04 �ж���delay���([20A]0����); ��40 ��ǰ�ж���(1����)
        BYTE    Sequence;           // 0x6E

        DUMMY_STRUCT(2);
        BYTE    RNo;		        // 0x71

        DUMMY_STRUCT(1);

        BYTE    Pri;	            // 0x73
        BOOLEAN IsSBreaking;

        DUMMY_STRUCT(3);
    };

} AT_BAR_ENTRY, *PAT_BAR_ENTRY;

class CBattleATBar
{
public:
    AT_BAR_ENTRY   Entry[0x3C];
    PAT_BAR_ENTRY  EntryPointer[0x3C];      // 0x1C20

    BOOL IsCurrentChrSBreak()
    {
        return EntryPointer[0]->IsSBreaking;
    }

    // -1 for null
    BYTE THISCALL GetChrAT0()
    {
        TYPE_OF(&CBattleATBar::GetChrAT0) f;
        *(PVOID *)&f = (PVOID)0x00677230;
		return (this->*f)();
    }

    VOID AdvanceChrInATBar(PMONSTER_STATUS MSData, BOOL InsertToFirstPos)
    {
        TYPE_OF(&CBattleATBar::AdvanceChrInATBar) AdvanceChrInATBar;

        *(PVOID *)&AdvanceChrInATBar = (PVOID)0x676D3F;

        return (this->*AdvanceChrInATBar)(MSData, InsertToFirstPos);
    }

    NoInline PAT_BAR_ENTRY FindATBarEntry(PMONSTER_STATUS MSData)
    {
        PAT_BAR_ENTRY *Entry;

        FOR_EACH(Entry, EntryPointer, countof(EntryPointer))
        {
            if (Entry[0]->MSData == MSData)
                return Entry[0];
        }

        return NULL;
    }
/*
    NoInline PAT_BAR_ENTRY FindATBarEntry0NoSecond()
    {
        PAT_BAR_ENTRY *Entry;
        static PAT_BAR_ENTRY PreEntry;

        if (PreEntry == EntryPointer[0])
            return PreEntry;
        
        FOR_EACH(Entry, &EntryPointer[1], countof(EntryPointer))
        {
            //if (Entry[0]->MSData == NULL) //�в����������
                //break;
            if (Entry[0]->MSData == EntryPointer[0]->MSData)
            {
                PreEntry = Entry[0];
                return Entry[0];
            }
        }
        
        return NULL;
    }
*/
    PAT_BAR_ENTRY THISCALL LookupReplaceAtBarEntry(PMONSTER_STATUS MSData, BOOL IsFirst);
};

class CBattle
{
public:
    VOID THISCALL SetSelectedAttack(PMONSTER_STATUS MSData);
    VOID THISCALL SetSelectedMagic(PMONSTER_STATUS MSData, USHORT CraftIndex, USHORT CurrentCraftIndex);
    VOID THISCALL SetSelectedCraft(PMONSTER_STATUS MSData, USHORT CraftIndex, USHORT AiIndex);
    VOID THISCALL SetSelectedSCraft(PMONSTER_STATUS MSData, USHORT CraftIndex, USHORT AiIndex);

    CSSaveData* GetSaveData()
    {
        return *(CSSaveData **)PtrAdd(this, 0x38D28);
    }


    CBattleInfoBox* GetBattleInfoBox()
    {
        return (CBattleInfoBox *)PtrAdd(this, 0xF0D24);
    }

    BOOL IsCustomChar(ULONG_PTR ChrId)
    {
        return GetSaveData()->IsCustomChar(ChrId);
    }

    EDAO* GetEDAO()
    {
        return *(EDAO **)PtrAdd(this, 0x38D24);
    }

    CBattleATBar* GetBattleATBar()
    {
        return (CBattleATBar *)PtrAdd(this, 0x103148);
    }

    BOOL IsForceInsertToFirst()
    {
        return *(PBOOL)PtrAdd(this, 0x3A7B0);
    }

    PVOID GetMSFileBuffer()
    {
        return PtrAdd(this, 0x114ED0);
    }

    PMONSTER_STATUS GetMonsterStatus()
    {
        return (PMONSTER_STATUS)PtrAdd(this, 0x4DE4);
    }

    LONG_PTR GetCurrentChrIndex()
    {
        return *(PLONG)PtrAdd(this, 0x113080);
    }

    LONG_PTR GetCurrentTargetIndex()
    {
        return *(PLONG)PtrAdd(this, 0x113090);
    }

    VOID ShowConditionText(PMONSTER_STATUS MSData, PCSTR Text, ULONG Color = RGBA(255, 136, 0, 255), ULONG Unknown = 0)
    {
        TYPE_OF(&CBattle::ShowConditionText) ShowConditionText;
        *(PULONG_PTR)&ShowConditionText = 0xA17420;
        return (this->*ShowConditionText)(MSData, Text, Color, Unknown);
    }

    // mark
    PMS_EFFECT_INFO THISCALL FindEffectInfoByCondition(PMONSTER_STATUS MSData, ULONG_PTR Condition, INT ConditionRateType = 0)
    {
        DETOUR_METHOD(CBattle, FindEffectInfoByCondition, 0x673CC5, MSData, Condition, ConditionRateType);
    }

    PMS_EFFECT_INFO THISCALL FindEffectInfoByConditionEx(PMONSTER_STATUS MSData, ULONG_PTR Condition, INT ConditionRateType = 0, BOOL IsCheckSum = TRUE);

    VOID THISCALL ShowSkipAnimeButton()
    {
        DETOUR_METHOD(CBattle, ShowSkipAnimeButton, 0x673513);
    }

    VOID THISCALL CancelAria(PMONSTER_STATUS MSData, BOOL Reset)
    {
        DETOUR_METHOD(CBattle, CancelAria, 0x99DDC0, MSData, Reset);
    }

    VOID THISCALL UpdateHP(PMONSTER_STATUS MSData, LONG Increment, LONG Initial, BOOL What = TRUE)
    {
        TYPE_OF(&CBattle::UpdateHP) UpdateHP;
        *(PULONG_PTR)&UpdateHP = 0x9ED1F0;
        return (this->*UpdateHP)(MSData, Increment, Initial, What);
    }

    /************************************************************************
      bug fix
    ************************************************************************/
    VOID
    THISCALL
    ExecuteActionScript(
        PMONSTER_STATUS MSData,
        PBYTE           ActionScript,
        BYTE            ChrThreadId,
        USHORT          ScriptOffset,
        ULONG           Unknown1,
        ULONG           Unknown2,
        ULONG           Unknown3
    );

    /************************************************************************
      tweak
    ************************************************************************/

    VOID NakedNoResistConditionUp();

    static LONG CDECL FormatBattleChrAT(PSTR Buffer, PCSTR Format, LONG Index, LONG No, LONG IcoAT, LONG ObjAT, LONG Pri);
    static LONG CDECL ShowSkipCraftAnimeButton(...);

    /************************************************************************
      hack for use enemy
    ************************************************************************/

    PMONSTER_STATUS FASTCALL OverWriteBattleStatusWithChrStatus(PMONSTER_STATUS MSData, PCHAR_STATUS ChrStatus);
    VOID NakedOverWriteBattleStatusWithChrStatus();

    VOID NakedIsChrStatusNeedRefresh();
    BOOL FASTCALL IsChrStatusNeedRefresh(ULONG_PTR ChrPosition, PCHAR_STATUS CurrentStatus, ULONG_PTR PrevLevel);

    ULONG NakedGetChrIdForSCraft();

    VOID NakedGetTurnVoiceChrId();
    VOID NakedGetReplySupportVoiceChrId();
    VOID NakedGetRunawayVoiceChrId();
    VOID NakedGetTeamRushVoiceChrId();
    VOID NakedGetUnderAttackVoiceChrId();
    VOID NakedGetUnderAttackVoiceChrId2();
    VOID NakedGetSBreakVoiceChrId();

    ULONG FASTCALL GetVoiceChrIdWorker(PMONSTER_STATUS MSData);

    VOID NakedCopyMagicAndCraftData();
    VOID FASTCALL CopyMagicAndCraftData(PMONSTER_STATUS MSData);



    typedef struct
    {
        BYTE    OpCode;
        BYTE    Function;

        union
        {
            ULONG Param[4];

        };

    } AS_8D_PARAM, *PAS_8D_PARAM;

    enum
    {
        AS_8D_FUNCTION_MINIMUM  = 0x70,

        AS_8D_FUNCTION_REI_JI_MAI_GO    =   AS_8D_FUNCTION_MINIMUM,
    };

    VOID NakedAS8DDispatcher();
    VOID FASTCALL AS8DDispatcher(PMONSTER_STATUS MSData, PAS_8D_PARAM ASBuffer);


    /************************************************************************
      enemy sbreak
    ************************************************************************/

#define THINK_SBREAK_FILTER TAG4('THSB')

    VOID NakedGetBattleState();
    VOID FASTCALL HandleBattleState(ULONG_PTR CurrentState);
    VOID THISCALL SetCurrentActionChrInfo(USHORT Type, PMONSTER_STATUS MSData);

    LONG NakedEnemyThinkAction();
    BOOL FASTCALL EnemyThinkAction(PMONSTER_STATUS MSData);

    BOOL THISCALL ThinkRunaway(PMONSTER_STATUS MSData);
    BOOL THISCALL ThinkSCraft(PMONSTER_STATUS MSData);

    BOOL ThinkSBreak(PMONSTER_STATUS MSData, PAT_BAR_ENTRY Entry);


    /************************************************************************
      acgn beg
    ************************************************************************/

    VOID THISCALL LoadMSFile(PMONSTER_STATUS MSData, ULONG MSFileIndex);
    VOID THISCALL LoadMonsterIt3(ULONG CharPosition, ULONG par2, PSTR it3Path);
    VOID NakedAS_8D_5F();
	VOID THISCALL AS_8D_5F(PMONSTER_STATUS);

    // mark
    // ������������ģ����Ч��ȡ��vanishҲ�������
    VOID THISCALL UnsetCondition(PMONSTER_STATUS MSData, ULONG condition)
    {
        DETOUR_METHOD(CBattle, UnsetCondition, 0x672AE1, MSData, condition);
    }

    VOID THISCALL RemoveCondition(PMONSTER_STATUS MSData, ULONG condition, INT type) // >0 Rate>0; <0 Rate <0; 0 all
    {
        DETOUR_METHOD(CBattle, RemoveCondition, 0x67B0BA, MSData, condition, type);
    }

    // ���������Լ��
    VOID THISCALL SetCondition(PMONSTER_STATUS dst, PMONSTER_STATUS src, ULONG condition, ULONG at, ULONG conditionRate)
    {
        DETOUR_METHOD(CBattle, SetCondition, 0x676EA2, dst, src, condition, at, conditionRate);
	}

    VOID THISCALL AddCondition(PMONSTER_STATUS dst, PMONSTER_STATUS src, ULONG condition, ULONG at, ULONG conditionRate)
    {
        DETOUR_METHOD(CBattle, AddCondition, 0x677D11, dst, src, condition, at, conditionRate);
    }

    BOOL CheckCondition(PMONSTER_STATUS MSData, ULONG condition, ULONG par3=0)
    {
        return FindEffectInfoByCondition(MSData, condition, par3) != NULL;
    }

    VOID THISCALL SubHPWhenAttack(PMONSTER_STATUS dst, INT HP)
    {
        DETOUR_METHOD(CBattle, SubHPWhenAttack, 0x679869, dst, HP);
    }
    
    VOID THISCALL SubHPEveryAct(PMONSTER_STATUS dst, INT HP)
    {
        DETOUR_METHOD(CBattle, SubHPEveryAct, 0x674157, dst, HP);
    }

    VOID THISCALL AnalyzeMonsInf(PMONSTER_STATUS MSData, BOOL IsSkipBattleEvaluation = FALSE)
    {
        DETOUR_METHOD(CBattle, AnalyzeMonsInf, 0x6747D3, MSData, IsSkipBattleEvaluation);
    }
    
    DECL_STATIC_METHOD_POINTER(CBattle, LoadMSFile);

    /************************************************************************
      acgn end
    ************************************************************************/

    // mark
    PAS_FILE GetASFile()
    {
        return (PAS_FILE)PtrAdd(this, 0x3A800);
    }
    
    PAS_FILE GetASFile(PMONSTER_STATUS MSData)
    {
        if (MSData->CharPosition >= MAXIMUM_CHR_NUMBER_IN_BATTLE || MSData->IsChrEmpty())
            return NULL;
        else
            return &(GetASFile()[MSData->CharPosition]);
    }


    VOID NakedCheckAliveBeforeHeal();
    VOID FASTCALL CheckAliveBeforeHeal(ULONG CharPosition);
    VOID THISCALL SubHPEveryAct2WhenAttack(PMONSTER_STATUS dst, PCHAR_STATUS pChrStatusFinal, INT HP);
    VOID NakedHandleConditionBeforeMasterQuartzKipaTakeEffect();
    VOID FASTCALL HandleConditionBeforeMasterQuartzKipaTakeEffect(PMONSTER_STATUS MSData);
    BOOL THISCALL IsNeedBattleEvaluationSuperKill(ULONG ChrPosition);

    VOID THISCALL SetBattleStatusFinalByDifficulty(PMONSTER_STATUS MSData);
    DECL_STATIC_METHOD_POINTER(CBattle, SetBattleStatusFinalByDifficulty);

    BOOL THISCALL CheckQuartz(ULONG ChrPosition, ULONG ItemId, PULONG EquippedIndex = NULL);
    DECL_STATIC_METHOD_POINTER(CBattle, CheckQuartz);

    PMS_EFFECT_INFO THISCALL CheckConditionGreenPepperWhenThinkCraft(PMONSTER_STATUS MSData, ULONG_PTR Condition, INT ConditionRateType);

    BOOL IsChrCanTeamRush(PMONSTER_STATUS MSData, PCRAFT_INFO pCraft);
    DECL_STATIC_METHOD_POINTER(CBattle, IsChrCanTeamRush);

    DECL_STATIC_METHOD_POINTER(CBattle, SetCurrentActionChrInfo);
    DECL_STATIC_METHOD_POINTER(CBattle, ThinkRunaway);
    DECL_STATIC_METHOD_POINTER(CBattle, ThinkSCraft);
    DECL_STATIC_METHOD_POINTER(CBattle, ExecuteActionScript);

    static PCHAR_STATUS pChrStatusBackup;
};

INIT_STATIC_MEMBER(CBattle::StubSetCurrentActionChrInfo);
INIT_STATIC_MEMBER(CBattle::StubThinkRunaway);
INIT_STATIC_MEMBER(CBattle::StubThinkSCraft);
INIT_STATIC_MEMBER(CBattle::StubLoadMSFile);
INIT_STATIC_MEMBER(CBattle::StubExecuteActionScript);
INIT_STATIC_MEMBER(CBattle::StubSetBattleStatusFinalByDifficulty);
INIT_STATIC_MEMBER(CBattle::StubCheckQuartz);
INIT_STATIC_MEMBER(CBattle::StubIsChrCanTeamRush);

INIT_STATIC_MEMBER(CBattle::pChrStatusBackup);

class CSound
{
public:

    VOID THISCALL PlaySound(ULONG SeIndex, ULONG v1 = 1, ULONG v2 = 0, ULONG v3 = 100, ULONG v4 = 0, ULONG v5 = 35, ULONG v6 = 0)
    {
        TYPE_OF(&CSound::PlaySound) PlaySound;

        *(PVOID *)&PlaySound = (PVOID)0x677271;

        return (this->*PlaySound)(SeIndex, v1, v2, v3, v4, v5, v6);
    }
};

typedef struct
{
    DUMMY_STRUCT(0x30);

    FLOAT Vertical;         // 0x30
    FLOAT Obliquity;        // 0x34
    FLOAT Horizon;          // 0x38

    DUMMY_STRUCT(0x54 - 0x38 - sizeof(FLOAT));

    FLOAT Distance;         // 0x54

} CAMERA_INFO, *PCAMERA_INFO;

class CCamera
{
public:
    PCAMERA_INFO GetCameraInfo()
    {
        return (PCAMERA_INFO)*(PVOID *)PtrAdd(this, 0xB88);
    }
};

typedef struct
{
    USHORT  State;
    BYTE    ScenaIndex;

    DUMMY_STRUCT(1);

    ULONG   FunctionOffset;
    ULONG   CurrentOffset;

} *PSCENA_ENV_BLOCK;

class CScript
{
public:
    EDAO* GetEDAO()
    {
        return (EDAO *)PtrSub(this, 0x384EC);
    }

    CCamera* GetCamera()
    {
        return *(CCamera **)PtrAdd(this, 0x524);
    }

    CSSaveData* GetSaveData()
    {
        return *(CSSaveData **)this;
    }

    PBYTE* GetScenaTable()
    {
        return (PBYTE *)PtrAdd(this, 0x7D4);
    }


    BOOL THISCALL ScpSaveRestoreParty(PSCENA_ENV_BLOCK Block);
    // mark
    BOOL THISCALL ScpLeaveParty(PSCENA_ENV_BLOCK Block);
    ULONG THISCALL ScpGetFunctionAddress(ULONG_PTR pScena, ULONG function);

    VOID FASTCALL InheritSaveData(PBYTE ScenarioFlags);
    VOID NakedInheritSaveData();

    DECL_STATIC_METHOD_POINTER(CScript, InheritSaveData);
    DECL_STATIC_METHOD_POINTER(CScript, ScpLeaveParty);
    DECL_STATIC_METHOD_POINTER(CScript, ScpGetFunctionAddress);
    DECL_STATIC_METHOD_POINTER(CScript, ScpSaveRestoreParty);
};

INIT_STATIC_MEMBER(CScript::StubInheritSaveData);
INIT_STATIC_MEMBER(CScript::StubScpSaveRestoreParty);
INIT_STATIC_MEMBER(CScript::StubScpLeaveParty);
INIT_STATIC_MEMBER(CScript::StubScpGetFunctionAddress);

class CMap
{
public:
    PULONG GetFrameNumber()
    {
        return (PULONG)PtrAdd(this, 0x1C7C);
    }
};

class CInput
{
public:
    BOOL UseJoyStick()
    {
        return *(PBOOL)this;
    }

    LPDIRECTINPUTDEVICE8A GetDInputDevice()
    {
        return *(LPDIRECTINPUTDEVICE8A *)PtrAdd(this, 0x218);
    }

    VOID THISCALL HandleMainInterfaceInputState(PVOID Parameter1, CInput *Input, PVOID Parameter3);

    DECL_STATIC_METHOD_POINTER(CInput, HandleMainInterfaceInputState);
};

INIT_STATIC_MEMBER(CInput::StubHandleMainInterfaceInputState);


class EDAO
{
    // battle

public:

    static EDAO* GlobalGetEDAO()
    {
        return ::GlobalGetEDAO();
    }

    static VOID JumpToMap()
    {
        return ((TYPE_OF(&EDAO::JumpToMap))0x6A0DF0)();
    }

    CMap* GetMap()
    {
        return (CMap *)PtrAdd(this, 0x141C);
    }

    CGlobal* GetGlobal()
    {
        return (CGlobal *)PtrAdd(this, 0x4D3E8);
    }

    CBattle* GetBattle()
    {
        return *(CBattle **)PtrAdd(this, 0x82BA4);
    }

    CSound* GetSound()
    {
        return (CSound *)PtrAdd(this, 0x3A628);
    }

    CScript* GetScript()
    {
        return (CScript *)PtrAdd(this, 0x384EC);
    }

    CSSaveData* GetSaveData()
    {
        //return GetScript()->GetSaveData();
        return (CSSaveData*)PtrAdd(this, 0x78CB8);
    }

    CDebug* GetDebug()
    {
        return (CDebug *)PtrAdd(this, 0xB80D8);
    }

    BOOL IsCustomChar(ULONG_PTR ChrId)
    {
        return GetSaveData()->IsCustomChar(ChrId);
    }

    PUSHORT GetSBreakList()
    {
        return (PUSHORT)PtrAdd(this, 0x7EE10);
    }

    PFLOAT GetChrCoord()
    {
        return (PFLOAT)(*(PULONG_PTR)PtrAdd(EDAO::GlobalGetEDAO(), 0x78CB8 + 0x2BC));
    }

    VOID UpdateChrCoord(PVOID Parameter)
    {
        DETOUR_METHOD(EDAO, UpdateChrCoord, 0x74F490, Parameter);
    }

    ULONG_PTR GetLayer()
    {
        return *(PUSHORT)PtrAdd(this, 0xA6FA8);
    }

    PSIZE GetWindowSize()
    {
        return (PSIZE)PtrAdd(this, 0x3084);
    }

    VOID LoadFieldAttackData(ULONG_PTR Dummy = 0)
    {
        TYPE_OF(&EDAO::LoadFieldAttackData) LoadFieldAttackData;
        *(PULONG_PTR)&LoadFieldAttackData = 0x6F8D30;
        return (this->*LoadFieldAttackData)(Dummy);
    }

    LONG THISCALL AoMessageBox(PCSTR Text, BOOL CanUseCancelButton = TRUE)
    {
        typedef struct
        {
            PVOID Callbacks[4];

        } MSGBOX_CALLBACK;

        LONG (FASTCALL *AoMessageBoxWorker)(EDAO*, PVOID, BOOL CanUseCancelButton, PCSTR Text, MSGBOX_CALLBACK, ULONG, ULONG, ULONG);

        MSGBOX_CALLBACK cb = { (PVOID)0x676056, NULL, NULL, NULL };

        *(PULONG_PTR)&AoMessageBoxWorker = 0x67A4D5;
        return AoMessageBoxWorker(this, 0, CanUseCancelButton, Text, cb, 0, 0, -1);
    }

    VOID StubDrawNumber(LONG X, LONG Y, PCSTR Text, ULONG OneU1, ULONG Color, ULONG ZeroU1);

    NoInline VOID DrawNumber(LONG X, LONG Y, PCSTR Text, ULONG_PTR Color, ULONG OneU1 = 1, ULONG ZeroU1 = 0)
    {
        TYPE_OF(&EDAO::StubDrawNumber) StubDrawNumber;

        *(PVOID *)&StubDrawNumber = (PVOID)0x734A00;

        return (this->*StubDrawNumber)(X, Y, Text, OneU1, Color, ZeroU1);
    }

    VOID THISCALL StubDrawRectangle(USHORT Layer, LONG Left, LONG Top, LONG Right, LONG Bottom, FLOAT ZeroF1, FLOAT ZeroF2, FLOAT ZeroF3, FLOAT ZeroF4, ULONG UpperLeftColor, ULONG UpperRightColor, ULONG ZeroU1,ULONG ZeroU2,ULONG ZeroU3,ULONG ZeroU4,ULONG ZeroU5,ULONG ZeroU6,FLOAT ZeroF5);

    NoInline
    VOID
    THISCALL
    DrawRectangle(
        /* USHORT Layer */
        LONG    Left,
        LONG    Top,
        LONG    Right,
        LONG    Bottom,

        ULONG   UpperLeftColor,
        ULONG   UpperRightColor,

        FLOAT   ZeroF1 = 0,
        FLOAT   ZeroF2 = 0,
        FLOAT   ZeroF3 = 0,
        FLOAT   ZeroF4 = 0,

        ULONG   ZeroU1 = 0,
        ULONG   ZeroU2 = 0,
        ULONG   ZeroU3 = 0,
        ULONG   ZeroU4 = 0,
        ULONG   ZeroU5 = 0,
        ULONG   ZeroU6 = 0,

        FLOAT   ZeroF5 = 0
    )
    {
        TYPE_OF(&EDAO::StubDrawRectangle) StubDrawRectangle;
        *(PVOID *)&StubDrawRectangle = (PVOID)0x6726EA;

        return (PtrAdd(this, 0x254)->*StubDrawRectangle)(
                    GetLayer(),
                    Left,
                    Top,
                    Right,
                    Bottom,

                    ZeroF1,
                    ZeroF2,
                    ZeroF3,
                    ZeroF4,

                    UpperLeftColor,
                    UpperRightColor,

                    ZeroU1,
                    ZeroU2,
                    ZeroU3,
                    ZeroU4,
                    ZeroU5,
                    ZeroU6,

                    ZeroF5
                );
    }

    VOID CalcChrRawStatusFromLevel(ULONG ChrId, ULONG Level, ULONG Unknown = 0)
    {
        DETOUR_METHOD(EDAO, CalcChrRawStatusFromLevel, 0x675FF7, ChrId, Level, Unknown);
    }


    /************************************************************************
      hack for boss
    ************************************************************************/

    VOID NakedGetChrSBreak();
    VOID FASTCALL GetChrSBreak(PMONSTER_STATUS MSData);
    LONG FASTCALL GetStatusIcon(ULONG ChrId);
    LONG FASTCALL GetCFace(ULONG ChrId);
    LONG FASTCALL GetLeaderChangeVoice(ULONG ChrId);

    static LONG CDECL GetCampImage(PSTR Buffer, PCSTR Format, LONG ChrId);
    static LONG CDECL GetBattleFace(PSTR Buffer, PCSTR Format, PCSTR DataPath, LONG ChrId);
    static LONG CDECL GetFieldAttackChr(PSTR Buffer, PCSTR Format, LONG ChrId);

    /************************************************************************
      tweak
    ************************************************************************/

    static VOID NakedLoadSaveDataThumb();
    static VOID NakedSetSaveDataScrollStep();

    // hook
public:
    VOID THISCALL Fade(ULONG Param1, ULONG Param2, ULONG Param3, ULONG Param4, ULONG Param5, ULONG Param6);
    BOOL THISCALL CheckItemEquipped(ULONG ItemId, PULONG EquippedIndex);

    //mark
    ULONG THISCALL GetDifficulty();

    VOID THISCALL SetBattleStatusFinalByEquipment(ULONG ChrPosition, PCHAR_STATUS pStatusFinal, PCHAR_STATUS pStatusBasic)
    {
        DETOUR_METHOD(EDAO, SetBattleStatusFinalByEquipment, 0x00676ECA, ChrPosition, pStatusFinal, pStatusBasic);
    }

    // ľż ����
    VOID THISCALL SetBattleStatusFinalWhenRecover(ULONG ChrPosition, PCHAR_STATUS pStatusFinal, PCHAR_STATUS pStatusBasic);

    DECL_STATIC_METHOD_POINTER(EDAO, CheckItemEquipped);
    DECL_STATIC_METHOD_POINTER(EDAO, GetDifficulty);

    static CHAR_T_STATUS ChrT_Status;
    static PCHAR_T_STATUS CalcChrT_StatusNew(PCHAR_T_STATUS pStatus, INT ChrNo, INT Level);
    PCHAR_T_STATUS THISCALL CalcChrT_Status(INT ChrNo, INT Level);
    DECL_STATIC_METHOD_POINTER(EDAO, CalcChrT_Status);

    VOID THISCALL CalcChrRawStatusFromLevelNew(ULONG ChrId, ULONG Level, ULONG Unknown = 0);
    DECL_STATIC_METHOD_POINTER(EDAO, CalcChrRawStatusFromLevel);

    PCHAR_STATUS CalcChrRawStatusByFinalStatus(PCHAR_STATUS RawStatus, ULONG ChrID, PCHAR_STATUS FinalStatus);
    DECL_STATIC_METHOD_POINTER(EDAO, CalcChrRawStatusByFinalStatus);
/*
    static ULONG GetWindowWidth()
    {
        return *(PULONG)PtrAdd(GlobalGetEDAO(), 0x3084);
    }

    static ULONG GetWindowHeight()
    {
        return *(PULONG)PtrAdd(GlobalGetEDAO(), 0x3088);
    }

    VOID THISCALL ShowDebugText(LPCSTR lpText, INT x, INT y, INT color, INT par5, INT par6, INT par7)
    {
        DETOUR_METHOD(EDAO, ShowDebugText, 0x006729FB, lpText, x, y, color, par5, par6, par7);
    }

    VOID THISCALL ShowDebugTextPositionRestore1(LPCSTR lpText, INT x, INT y, INT color, INT par5, INT par6, INT par7)
    {
        x = (x-1)  * 480 / EDAO::GetWindowWidth() + 1;
        y = (y-1) * 272 / EDAO::GetWindowHeight() + 1;
        ShowDebugText(lpText, x, y, color, par5, par6, par7);
    }

    VOID THISCALL ShowDebugTextPositionRestore2(LPCSTR lpText, INT x, INT y, INT color, INT par5, INT par6, INT par7)
    {
        x = x * 480 / EDAO::GetWindowWidth();
        y = y * 272 / EDAO::GetWindowHeight();
        ShowDebugText(lpText, x, y, color, par5, par6, par7);
    }
*/
};

INIT_STATIC_MEMBER(EDAO::StubCheckItemEquipped);
INIT_STATIC_MEMBER(EDAO::StubGetDifficulty);
INIT_STATIC_MEMBER(EDAO::StubCalcChrT_Status);
INIT_STATIC_MEMBER(EDAO::StubCalcChrRawStatusFromLevel);
INIT_STATIC_MEMBER(EDAO::StubCalcChrRawStatusByFinalStatus);
DECL_SELECTANY TYPE_OF(EDAO::ChrT_Status) EDAO::ChrT_Status;

class CCoordConverter
{
public:
    VOID MapPSPCoordToPC(Gdiplus::PointF Source[2], Gdiplus::PointF Target[2], PFLOAT Transform = NULL)
    {
        DETOUR_METHOD(CCoordConverter, MapPSPCoordToPC, 0x6A7030, Source, Target, Transform);
    }
};

class CMiniGame
{
public:

    static VOID FASTCALL HorrorHouse_GetMonsterPosition(CCoordConverter *Converter, PVOID, Gdiplus::PointF *PSPCoord, Gdiplus::PointF *PCCoord, PFLOAT Transform)
    {
        EDAO *edao = EDAO::GlobalGetEDAO();

        Converter->MapPSPCoordToPC(PSPCoord, PCCoord, Transform);

        PCCoord->X *= PSP_WIDTH_F / edao->GetWindowSize()->cx;
        PCCoord->Y *= PSP_HEIGHT_F / edao->GetWindowSize()->cy;
    }
};

class CGlobal
{
public:
    PCRAFT_INFO THISCALL GetMagicData(USHORT MagicId);
    PCSTR       THISCALL GetMagicDescription(USHORT MagicId);
    PBYTE       THISCALL GetMagicQueryTable(USHORT MagicId);

    EDAO* GetEDAO()
    {
        return (EDAO *)PtrSub(this, 0x4D3E8);
    }

    BOOL IsCustomChar(ULONG_PTR ChrId)
    {
        return GetEDAO()->GetSaveData()->IsCustomChar(ChrId);
    }

    PCHAR_STATUS GetChrStatus(ULONG_PTR ChrId)
    {
        return &((PCHAR_STATUS)PtrAdd(this, 0x2BBBC))[ChrId];
    }

    VOID CalcChrFinalStatus(ULONG ChrId, PCHAR_STATUS FinalStatus, PCHAR_STATUS RawStatus)
    {
        TYPE_OF(&CGlobal::CalcChrFinalStatus) f;

        *(PVOID *)&f = (PVOID)0x677B36;

        return (this->*f)(ChrId, FinalStatus, RawStatus);
    }

    static TYPE_OF(&CGlobal::GetMagicData)          StubGetMagicData;
    static TYPE_OF(&CGlobal::GetMagicDescription)   StubGetMagicDescription;
    static TYPE_OF(&CGlobal::GetMagicQueryTable)    StubGetMagicQueryTable;
};

DECL_SELECTANY TYPE_OF(CGlobal::StubGetMagicData)           CGlobal::StubGetMagicData = NULL;
DECL_SELECTANY TYPE_OF(CGlobal::StubGetMagicDescription)    CGlobal::StubGetMagicDescription = NULL;
DECL_SELECTANY TYPE_OF(CGlobal::StubGetMagicQueryTable)     CGlobal::StubGetMagicQueryTable = NULL;

BOOL AoIsFileExist(PCSTR FileName);

//mark
class CDebug
{
public:
    VOID THISCALL SelectPartyChr()
    {
        DETOUR_METHOD(CDebug, SelectPartyChr, 0x672F82);
    }

    VOID THISCALL MainControl()
    {
        TYPE_OF(&GetAsyncKeyState) StubGetAsyncKeyState;
        *(PULONG_PTR)&StubGetAsyncKeyState = *(PULONG_PTR)0xDD5A18;

        if (StubGetAsyncKeyState(VK_CONTROL) & 0xF000)
        {
            if (StubGetAsyncKeyState('P') & 0x1)
            {
                SelectPartyChr();
                return;
            }
        }

        return (this->*StubMainControl)();
    }

    BOOL THISCALL IsFileExist(PCSTR FileName);
    DECL_STATIC_METHOD_POINTER(CDebug, MainControl);
};

INIT_STATIC_MEMBER(CDebug::StubMainControl);

#endif // _EDAO_H_5c8a3013_4334_4138_9413_3d0209da878e_
