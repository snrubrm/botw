#include "Game/AI/Action/actionSwarmChemicalDamaged.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageManager.h"

namespace uking::action {

SwarmChemicalDamaged::SwarmChemicalDamaged(const InitArg& arg) : SwarmDamaged(arg) {}

SwarmChemicalDamaged::~SwarmChemicalDamaged() = default;

bool SwarmChemicalDamaged::init_(sead::Heap* heap) {
    return SwarmDamaged::init_(heap);
}

void SwarmChemicalDamaged::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100283004(params);
    SwarmDamaged::enter_(params);
}

void SwarmChemicalDamaged::leave_() {
    SwarmDamaged::leave_();
    sub_71002831E4();
}

void SwarmChemicalDamaged::loadParams_() {
    SwarmDamaged::loadParams_();
    getStaticParam(&mResetChemicalTimer_s, "ResetChemicalTimer");
    getStaticParam(&mIsResetAllObject_s, "IsResetAllObject");
}

void SwarmChemicalDamaged::calc_() {
    if (!(_1e0.mTimer.value <= sead::Mathf::epsilon())) {
        _1e0.sub_7100D3BCE4();
        if (_1e0.mTimer.value <= sead::Mathf::epsilon())
            sub_71002831E4();
    }
    SwarmDamaged::calc_();
}

void SwarmChemicalDamaged::m34(dmg::DamageManager* mgr, sead::Vector3f* pos, sead::Vector3f* dir) {
    if (_1d8 == -1) {
        SwarmDamaged::m34(mgr, pos, dir);
        return;
    }

    auto* swarm = static_cast<act::Swarm*>(mActor);
    if (swarm && swarm->_15f8[_1d8]._20)
        swarm->_15f8[_1d8]._20->getPosition(pos);
    else
        mgr->getPosition(pos);
    sub_71005E2318(dir, mActor, mgr);
}

}  // namespace uking::action
