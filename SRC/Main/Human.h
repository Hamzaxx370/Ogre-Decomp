#include"YAct.h"
struct tag_SHumanSync
{

};
class CUniversalControlInterface {
    public:
    virtual int __uciGetInterface(void);
    virtual int __uciGetCommunicator(void);
    virtual int __uciGetBasePos(void *);
    virtual int __uciGetBaseYAngle(void);
    virtual int __uciSetPosWithColi(void *);
    virtual int __uciGetYAngle(void);
    virtual int __uciSetYAngle(long);
    virtual int __uciSetMotion(void *, int);
    virtual int __uciSetLip(void *);
    virtual int __uciSetState(unsigned long, unsigned long);
    virtual int __uciGetState(void);
    virtual int __uciGetKind(void);
    virtual int __uciIsMan(void);
    virtual int __uciIsWoman(void);
    virtual int __uciTalkBegin(void);
    virtual int __uciTalkEnd(void);
    virtual int __uciRefresh(void);
    virtual int __uciReset(void);
    virtual int __uciResetPos(void);
    virtual int __uciResetState(void);
};

class CHumanControlInterface : public CUniversalControlInterface {
    public:
    // virtual int __uciGetInterface(void) ;
    // virtual int __uciGetCommunicator(void) ;
    // virtual int __uciGetBasePos(void *) ;
    // virtual int __uciGetBaseYAngle(void) ;
    // // virtual int __uciSetPosWithColi(void *);
    // // virtual int __uciGetYAngle(void);
    // virtual int __uciSetYAngle(long) ;
    // virtual int __uciSetMotion(void *, int) ;
    // virtual int __uciSetLip(void *) ;
    // virtual int __uciSetState(unsigned long, unsigned long) ;
    // virtual int __uciGetState(void) ;
    // virtual int __uciGetKind(void) ;
    // virtual int __uciIsMan(void) ;
    // virtual int __uciIsWoman(void) ;
    // virtual int __uciTalkBegin(void) ;
    // virtual int __uciTalkEnd(void) ;
    // virtual int __uciRefresh(void) ;
    // virtual int __uciReset(void) ;
    // virtual int __uciResetPos(void) ;
    // virtual int __uciResetState(void) ;

};

enum eHUMANID_MTB_NORMAL
{

};
class CActHumanBase : public CActYActBase, public CHumanControlInterface {
    // total size: 0x370
public:
    CActHumanBase(CActBase *, int, unsigned int);
    int CActHumanBase_unk0;
    int CActHumanBase_unk4;
    int CActHumanBase_unk8;
    char CActHumanBase_unkC;
    char CActHumanBase_unkD;
    char CActHumanBase_unkE;
    char CActHumanBase_unkF;
    char CActHumanBase_unk10;
    char CActHumanBase_unk11;
    char CActHumanBase_unk12;
    char CActHumanBase_unk13;
    int CActHumanBase_unk14;
    int CActHumanBase_unk18;
    int CActHumanBase_unk1C;
    int CActHumanBase_unk20;
    class CArrow* CActHumanBase_unk24;
    char CActHumanBase_unk28[0x108];
    int CActHumanBase_unk130;
    int CActHumanBase_unk134;
    int CActHumanBase_unk138;
    int CActHumanBase_unk13C;
    int CActHumanBase_unk140;
    int CActHumanBase_unk144;
    float CActHumanBase_unk148;
    int CActHumanBase_unk14C;
    int CActHumanBase_unk150;
    int CActHumanBase_unk154;
    int CActHumanBase_unk158;
    int CActHumanBase_unk15C;
    int CActHumanBase_unk160;
    int CActHumanBase_unk164;
    int CActHumanBase_unk168;
    int CActHumanBase_unk16C;
    int CActHumanBase_unk170;
    int CActHumanBase_unk174;
    int CActHumanBase_unk178;
    int CActHumanBase_unk17C;
    int CActHumanBase_unk180;
    int CActHumanBase_unk184;
    int CActHumanBase_unk188;
    int CActHumanBase_unk18C;
    int CActHumanBase_unk190;
    int CActHumanBase_unk194;
    int CActHumanBase_unk198;
    int CActHumanBase_unk19C;
    int CActHumanBase_unk1A0;
    int CActHumanBase_unk1A4;
    int CActHumanBase_unk1A8;
    int CActHumanBase_unk1AC;
    int CActHumanBase_unk1B0;
    int CActHumanBase_unk1B4;
    int CActHumanBase_unk1B8;
    int CActHumanBase_unk1BC;
    int CActHumanBase_unk1C0;
    int CActHumanBase_unk1C4;
    int CActHumanBase_unk1C8;
    int CActHumanBase_unk1CC;
    int CActHumanBase_unk1D0;
    int CActHumanBase_unk1D4;
    int CActHumanBase_unk1D8;
    int CActHumanBase_unk1DC;
    int CActHumanBase_unk1E0;
    int CActHumanBase_unk1E4;
    int CActHumanBase_unk1E8;
    int CActHumanBase_unk1EC;
    int CActHumanBase_unk1F0;
    int CActHumanBase_unk1F4;
    int CActHumanBase_unk1F8;
    int CActHumanBase_unk1FC;
    int CActHumanBase_unk200;
    int CActHumanBase_unk204;
    int CActHumanBase_unk208;
    int CActHumanBase_unk20C;
    int CActHumanBase_unk210;
    int CActHumanBase_unk214;
    int CActHumanBase_unk218;
    int CActHumanBase_unk21C;
    int CActHumanBase_unk220;
    int CActHumanBase_unk224;
    int CActHumanBase_unk228;
    int CActHumanBase_unk22C;
    int CActHumanBase_unk230;
    int CActHumanBase_unk234;
    int CActHumanBase_unk238;
    int CActHumanBase_unk23C;
    int CActHumanBase_unk240;
    int CActHumanBase_unk244;
    int CActHumanBase_unk248;
    int CActHumanBase_unk24C;
    int CActHumanBase_unk250;
    int CActHumanBase_unk254;
    int CActHumanBase_unk258;
    int CActHumanBase_unk25C;
    int CActHumanBase_unk260;
    int CActHumanBase_unk264;
    int CActHumanBase_unk268;
    int CActHumanBase_unk26C;
    int CActHumanBase_unk270;
    int CActHumanBase_unk274;
    int CActHumanBase_unk278;
    int CActHumanBase_unk27C;
    int CActHumanBase_unk280;
    int CActHumanBase_unk284;
    int CActHumanBase_unk288;
    int CActHumanBase_unk28C;
    int CActHumanBase_unk290;
    int CActHumanBase_unk294;
    int CActHumanBase_unk298;
    int CActHumanBase_unk29C;
    int CActHumanBase_unk2A0;
    int CActHumanBase_unk2A4;
    int CActHumanBase_unk2A8;
    int CActHumanBase_unk2AC;
    int CActHumanBase_unk2B0;
    int CActHumanBase_unk2B4;
    int CActHumanBase_unk2B8;
    int CActHumanBase_unk2BC;
    int CActHumanBase_unk2C0;
    int CActHumanBase_unk2C4;
    int CActHumanBase_unk2C8;
    int CActHumanBase_unk2CC;
    int CActHumanBase_unk2D0;
    int CActHumanBase_unk2D4;
    int CActHumanBase_unk2D8;
    int CActHumanBase_unk2DC;
    int CActHumanBase_unk2E0;
    int CActHumanBase_unk2E4;
    int CActHumanBase_unk2E8;
    int CActHumanBase_unk2EC;
    int CActHumanBase_unk2F0;
    int CActHumanBase_unk2F4;
    int CActHumanBase_unk2F8;
    int CActHumanBase_unk2FC;
    int CActHumanBase_unk300;
    int CActHumanBase_unk304;
    int CActHumanBase_unk308;
    int CActHumanBase_unk30C;
    int CActHumanBase_unk310;
    int CActHumanBase_unk314;
    int CActHumanBase_unk318;
    int CActHumanBase_unk31C;
    int CActHumanBase_unk320;
    int CActHumanBase_unk324;
    int CActHumanBase_unk328;
    int CActHumanBase_unk32C;
    int CActHumanBase_unk330;
    int CActHumanBase_unk334;
    int CActHumanBase_unk338;
    int CActHumanBase_unk33C;
    int CActHumanBase_unk340;
    int CActHumanBase_unk344;
    int CActHumanBase_unk348;
    int CActHumanBase_unk34C;
    int CActHumanBase_unk350;
    int CActHumanBase_unk354;
    int CActHumanBase_unk358;
    int CActHumanBase_unk35C;
    int CActHumanBase_unk360;
    int CActHumanBase_unk364;
    int CActHumanBase_unk368;
    char CActHumanBase_unk36C[0x18];
    int CActHumanBase_unk384;
    int CActHumanBase_unk388;
    int CActHumanBase_unk38C;
    int CActHumanBase_unk390;
    int CActHumanBase_unk394;
    int CActHumanBase_unk398;
    int CActHumanBase_unk39C;
    int CActHumanBase_unk3A0;
    int CActHumanBase_unk3A4;
    int CActHumanBase_unk3A8;
    short CActHumanBase_unk3AC;
    char CActHumanBase_unk3AE;
    char CActHumanBase_unk3AF;
    int CActHumanBase_unk3B0;
    int CActHumanBase_unk3B4;
    int CActHumanBase_unk3B8;
    int CActHumanBase_unk3BC;
    class tag_CSysArmsSearch* CActHumanBase_unk3C0;
    class tag_CSysArmsSearch* CActHumanBase_unk3C4;
    class tag_CSysRecoverSearch* CActHumanBase_unk3C8;
    class tag_CSysRecoverSearch* CActHumanBase_unk3CC;
    int CActHumanBase_unk3D0;
    int CActHumanBase_unk3D4;
    int CActHumanBase_unk3D8;
    class CColMapPoint *CActHumanBase_unk3DC;
    class CActArms* CActHumanBase_unk3E0;
    class CActArms* CActHumanBase_unk3E4;
    // char m_cDecEnduReq; // offset 0xE4, size 0x1
    // enum eEFFECT_HUMAN_TYPE m_eEffectHumanType; // offset 0xE8, size 0x4
    // enum eCOLI_MAPITEM_TYPE m_eMapIcon; // offset 0xEC, size 0x4
    // unsigned int m_dwFloorType; // offset 0xF0, size 0x4
    // unsigned int m_dwLastDamageFloorTime; // offset 0xF4, size 0x4
    // unsigned int m_dwHitIDMask; // offset 0xF8, size 0x4
    // unsigned int m_dwHitObjectMask[3]; // offset 0xFC, size 0xC
    // class tag_MGLSPHERE m_ColiSphere; // offset 0x110, size 0x10
    // unsigned int m_dwColiPointMask; // offset 0x120, size 0x4
    // float m_vColiPoint[32][4]; // offset 0x130, size 0x200
    // class tag_SColStageQuad * m_lpHiPriorityWall; // offset 0x330, size 0x4
    // class CCommunicator * m_pCommunicator; // offset 0x334, size 0x4
    // float m_ReacVector[4]; // offset 0x340, size 0x10
    // unsigned int m_dwParticleType; // offset 0x350, size 0x4
    // unsigned short m_wTime0; // offset 0x354, size 0x2
    // unsigned short m_wTime1; // offset 0x356, size 0x2
    // unsigned short m_wTime0Max; // offset 0x358, size 0x2
    // unsigned short m_wTime1Max; // offset 0x35A, size 0x2
    // class CColMapPoint * m_lpMapPoint; // offset 0x35C, size 0x4
    // class HumanMotion * m_pHumanMotion; // offset 0x360, size 0x4
    // ~CActHumanBase() ;
    // virtual int __uciGetCommunicator(void) ;
    // virtual int __uciGetBasePos(void *) ;
    // virtual int __uciGetBaseYAngle(void) ;
    // virtual int __uciGetPos(void *) ;
    // virtual int __uciSetPos(void *) ;
    // virtual int __uciSetPosWithColi(void *) ;
    // virtual int __uciGetYAngle(void) ;
    // virtual int __uciSetYAngle(long) ;
    // virtual int __uciSetMotion(void *, int) ;
    // virtual int __uciSetLip(void *) ;
    eHUMANID_MTB_NORMAL GetSyncAttackMotion();
    int SetSyncAttack(tag_SHumanSync *, CActHumanBase *, int);
};