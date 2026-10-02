#include "Game/AI/Behavior/behaviorForceConfront.h"
#include <mc/seadCoreInfo.h>
#include "Game/Damage/dmgInfoManager.h"

namespace uking::behavior {

ForceConfront::ForceConfront(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ForceConfront::~ForceConfront() = default;

bool ForceConfront::m6(sead::Heap* heap) {
    return true;
}

void ForceConfront::m7() {}

void ForceConfront::m8() {
    if (auto* mgr = dmg::DamageInfoMgr::instance()) {
        const sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
        ++mgr->_11eb[core];
    }
}

void ForceConfront::m9() {
    if (auto* mgr = dmg::DamageInfoMgr::instance()) {
        const sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
        --mgr->_11eb[core];
    }
}

void ForceConfront::loadParams() {

}

}  // namespace uking::behavior
