#include"OutputBase.h"
class CActYActBase : public CActOutputBase {
    // total size: 0xE0
public:
    CActYActBase();
    CActYActBase(CActBase *, int);
    enum eYACT_MODE m_eYActMode; // offset 0x88, size 0x4
    float m_YActMatrix[16] __attribute__((aligned(16))); // offset 0x90, size 0x40
    class CTrtMotion * m_pYActMotion; // offset 0xD0, size 0x4

    virtual void __YActSetMotion(int *, int *) ;
    virtual int YActGetStatus(void) ;
    virtual int YActGetCtrlID(void) ;
    virtual int YActGetKindID(void) ;
    virtual int YActGetMotionID(void) ;
    virtual int YActGetArms(void) ;
    virtual void YActBoot(int, int *, long, unsigned long) ;
    virtual void YActFinish(int) ;
    virtual void YActDamage(unsigned long) ;
    virtual void YActDisableDraw(int) ;
    virtual void YActSetArm(char *, char *) ;
    virtual int YActReleaseArm(void) ;
    virtual void YActCatchArm(int *, unsigned long) ;
    virtual int YActGetArm(void) ;
    virtual void YActSetCollision(unsigned long, unsigned long) ;
    virtual int GetMesh(void) ;
    virtual void CreateIKControlPoint(unsigned long, unsigned long, int *) ;
    virtual void EffectIK(unsigned long, int *) ;
    virtual void ReleaseIKControlPoint(unsigned long) ;
};
enum eYACT_MODE {
    eYACT_MODE_NON = 0,
    eYACT_MODE_YACT = 1,
    eYACT_MODE_REACTION = 2,
    eYACT_MODE_WAIT = 3,
    eYACT_MODE_INVISIBLE = 4,
    eYACT_MODE_BREAK = 5,
    eYACT_MODE_YET = 6,
    eYACT_MODE_NUM = 7,
    eYACT_MODE_FORCE_DWORD = 2147483647,
};