#include "Game/AI/Action/actionSwarmChemicalDamaged.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
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

void SwarmChemicalDamaged::sub_7100283004(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _1d4 = -1;
    _1d8 = -1;
    _1d0 = false;

    auto* manager = sub_710072BA90(actor);
    auto* unit = sead::DynamicCast<act::Unk_710244ff68>(static_cast<ksys::act::DynamicActor*>(actor)->m159());
    if (manager && unit) {
        if (manager->getField54() == 0x12) {
            _1d4 = 2;
            _1d8 = unit->_20;
        } else if (manager->getField54() == 3) {
            _1d4 = 3;
            _1d8 = unit->_1c;
        } else if (manager->getField54() == 4) {
            _1d4 = 4;
            _1d8 = unit->_24;
        }
    }
    if (_1d4 != -1)
        _1d0 = true;

    if (*mResetChemicalTimer_s > 0.0f)
        _1e0.mTimer.reset(*mResetChemicalTimer_s);
    else
        sub_71002831E4();
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

// NON_MATCHING: the original loads `_1d4` into w1 before the `mIsResetAllObject` test and `_1d8` after it.
void SwarmChemicalDamaged::sub_71002831E4() {
    if (_1d0) {
        _1d0 = false;
        if (auto* unk = sead::DynamicCast<act::Unk_71025ae680>(static_cast<ksys::act::DynamicActor*>(mActor)->m159())) {
            if (*mIsResetAllObject_s)
                unk->sub_71006EF05C();
            else
                unk->sub_71006EEFB4(_1d4, _1d8);
        }
    }
}

}  // namespace uking::action
