#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

// Name from the CSV (RadarMgr::createInstance 0x710067b9c0, threadFn, calc, ...; no namespace). A singleton whose
// instance pointer is at 0x71025c6118. Only the members used so far are declared (layout incomplete).
// Vtable 0x710243c588 (slot 0 is the destructor, no RTTI); the singleton disposer sits at 0x8.
class RadarMgr {
    SEAD_SINGLETON_DISPOSER(RadarMgr)
    RadarMgr();
    virtual ~RadarMgr();

public:

    // 0x710067bfe8 (CSV RadarMgr::calc; declaration only)
    void calc();
    // 0x710067cb84 (CSV RadarMgr::__auto0; not decompiled): copies `name` into the search target name at
    // 0x168 (UiSubsys1::sub_7100966EA8 passes an empty string).
    void __auto0(const sead::SafeString& name);

    u8 _28[0x52 - 0x28];
    /* 0x52 */ bool _52;
    u8 _53[0x6c - 0x53];
    /* 0x6c */ sead::Vector3f _6c;  // the Sheikah sensor target position (WolfLinkShiekSensorRoot::calc_)
    u8 _78[0x9c - 0x78];
    /* 0x9c */ f32 _9c;  // compared with the Sheikah sensor lead distance by WolfLinkNormalRoot
    u8 _a0[0x108 - 0xa0];
    /* 0x108 */ sead::FixedSafeString<64> _108;  // actor group name used by calc and the search thread
    u8 _160[0x200 - 0x160];
};
KSYS_CHECK_SIZE_NX150(RadarMgr, 0x200);
