#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace uking {

// Placeholder declaration (names from the CSV: WolfLinkMgr::createInstance 0x71006828a8, init_ 0x7100682b94,
// postCalc 0x71006836d0; instance pointer at 0x71025c6ff8; namespace is a guess, like HorseMgr's). The manager of
// the Wolf Link (amiibo) actor; only what the AI actions use is declared.
// TODO: incomplete.
class WolfLinkMgr {
    SEAD_SINGLETON_DISPOSER(WolfLinkMgr)
    WolfLinkMgr();
    virtual ~WolfLinkMgr();

public:
    // 0x7100682ce8 (declared only; WolfLinkAmiiboRegister::enter_): registers the amiibo Wolf Link at `pos`.
    void sub_7100682CE8(const sead::Vector3f* pos, u8 flags);
    // 0x7100683088 (declared only; WolfLinkEvent::enter_ with 1).
    bool sub_7100683088(bool a1);
    // 0x710068367c / 0x7100683698 (declared only; WolfLinkAmiiboRegister::calc_).
    bool sub_710068367C();
    bool sub_7100683698();

    u8 _28[0x54 - 0x28];
    /* 0x54 */ sead::Vector3f _54;  // warp destination (WolfLinkAmiiboWarp::enter_)
    u8 _60[0x68 - 0x60];
    /* 0x68 */ ksys::MesTransceiverId _68;
};

}  // namespace uking
