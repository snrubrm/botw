#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking {

// Placeholder declaration (name from the CSV: HorseMgr::createInstance 0x7100e81fb0, ctor
// 0x7100e821e4, postCalc 0x7100e8789c, createHorse, ...; instance pointer at 0x7102603c90; namespace
// is a guess). The manager of the owned horse; only what the AI actions use is declared.
// TODO: incomplete.
class HorseMgr {
    SEAD_SINGLETON_DISPOSER(HorseMgr)
    HorseMgr();
    ~HorseMgr();

public:
    /* 0x20 */ ksys::act::BaseProcLink mOwnedHorse;
};

}  // namespace uking
