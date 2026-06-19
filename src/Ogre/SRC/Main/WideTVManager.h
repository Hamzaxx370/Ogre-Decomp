/*
    WideTVManager.h
*/

#ifndef WIDETVMAN_H
#define WIDETVMAN_H

#include "Main/Action.h"

enum eWIDETV {
    WIDETV_6 = 6,
    WIDETV_0 = 0
};

class CActWideTVManager : CActBase {
public:
    void SetWideTV(eWIDETV);  
};

extern CActWideTVManager* g_lpActWideTVMan;

#endif