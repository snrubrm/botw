#include "Game/Actor/Behavior/behaviorForceConfront.h"
#include <mc/seadCoreInfo.h>
#include "Game/Actor/Damage/dmgInfoManager.h"

namespace uking::behavior {

ForceConfront::ForceConfront(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ForceConfront::~ForceConfront() = default;

bool ForceConfront::init_(sead::Heap* heap) {
    return true;
}

void ForceConfront::calc() {}

void ForceConfront::enter() {
    if (auto* mgr = act::DamageInfoMgr::instance()) {
        const sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
        ++mgr->_11eb[core];
    }
}

void ForceConfront::leave() {
    if (auto* mgr = act::DamageInfoMgr::instance()) {
        const sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
        --mgr->_11eb[core];
    }
}

void ForceConfront::loadParams() {

}

}  // namespace uking::behavior
