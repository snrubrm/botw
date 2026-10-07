#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

// Name from the CSV (RadarMgr::createInstance 0x710067b9c0, threadFn, calc, ...; no namespace). A singleton whose
// instance pointer is at 0x71025c6118. Only the members used so far are declared (layout incomplete).
class RadarMgr {
public:
    static RadarMgr* instance() { return sInstance; }
    static RadarMgr* sInstance;

    u8 _0[0x52];
    /* 0x52 */ bool _52;
    u8 _53[0x9c - 0x53];
    /* 0x9c */ f32 _9c;  // compared with the Sheikah sensor lead distance by WolfLinkNormalRoot
};
