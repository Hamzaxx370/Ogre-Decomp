#include"Base.cpp"
class CActMan {
    // total size: 0x2780
public:
    CActMan();
    void systemInit();
    class CActHumanManager* GetAction(int);
    class CActBase * m_lpRootAction; // offset 0x0, size 0x4
    class CActBase * m_lpActExecRoot[4]; // offset 0x4, size 0x10
    class CActBase * * m_lplpActExecPtr[4]; // offset 0x14, size 0x10
    class CActBase * m_lpExecYetRoot[4]; // offset 0x24, size 0x10
    class CActBase * * m_lplpExecYetPtr[4]; // offset 0x34, size 0x10
    class CActBase * m_lpDelSameRoot; // offset 0x44, size 0x4
    class CActBase * * m_lplpDelSamePtr; // offset 0x48, size 0x4
    class CActBase * m_lpDelNextRoot; // offset 0x4C, size 0x4
    class CActBase * * m_lplpDelNextPtr; // offset 0x50, size 0x4
    class CActBase * m_pActTypeListRoot[5][16]; // offset 0x54, size 0x140
    class CActBase * * m_ppActTypeListPtr[5][16]; // offset 0x194, size 0x140
    unsigned int m_dwActTypeIDCount[5]; // offset 0x2D4, size 0x14
    class CActBase * m_lpActTbl[1755]; // offset 0x2E8, size 0x1D6C

    union {
        unsigned int m_dwWork[7]; // offset 0x1E54, size 0x1C
        signed int m_lWork[7]; // offset 0x1E54, size 0x1C
        float m_fWork[7]; // offset 0x1E54, size 0x1C
        void * m_lpWork[7]; // offset 0x1E54, size 0x1C
    };

    class CVisible * m_lpVisibleRoot; // offset 0x1E70, size 0x4
    class CVisible * * m_lplpVisiblePtr; // offset 0x1E74, size 0x4
    class CDrawBase * m_lpDrawBaseRoot[32]; // offset 0x1E78, size 0x80
    class CDrawBase * * m_lplpDrawBasePtr[32]; // offset 0x1EF8, size 0x80
    class CDrawBase * m_lpDrawBaseSortRoot[32]; // offset 0x1F78, size 0x80
    class CDrawBase * * m_lplpDrawBaseSortPtr[32]; // offset 0x1FF8, size 0x80
    class CDrawBase * m_lpDrawBaseSortedRoot[32]; // offset 0x2078, size 0x80
    enum eACTMODE m_ActMode; // offset 0x20F8, size 0x4
    enum eACTMODE m_ChangeActMode; // offset 0x20FC, size 0x4
    enum eACTMODE m_SaveFileWaitActMode; // offset 0x2100, size 0x4
    unsigned int m_dwFrameCount; // offset 0x2104, size 0x4
    unsigned int m_dwAnimCount; // offset 0x2108, size 0x4
    unsigned int m_dwAnimStep; // offset 0x210C, size 0x4
    class CCamera * m_lpCurrentCamera; // offset 0x2110, size 0x4
    unsigned int m_dwDrawSkipFrame; // offset 0x2114, size 0x4
    unsigned int m_dwDrawSkipFrameRegist; // offset 0x2118, size 0x4
    unsigned int m_dwInt; // offset 0x211C, size 0x4
    unsigned int m_dwIntRegist; // offset 0x2120, size 0x4
    float m_fActSpeedRatio; // offset 0x2124, size 0x4
    float m_fActSpeedSquareRatio; // offset 0x2128, size 0x4
    unsigned int m_pDrawListBuf[256]; // offset 0x212C, size 0x400
    class CDrawBase * m_pCurrentDraw; // offset 0x252C, size 0x4
    int GetActiom(long);
};


CActMan* D_1572A0;