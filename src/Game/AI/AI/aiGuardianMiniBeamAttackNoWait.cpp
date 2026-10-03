#include "Game/AI/AI/aiGuardianMiniBeamAttackNoWait.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianMiniBeamAttackNoWait::GuardianMiniBeamAttackNoWait(const InitArg& arg)
    : GuardianMiniBeamAttack(arg) {}

GuardianMiniBeamAttackNoWait::~GuardianMiniBeamAttackNoWait() = default;

bool GuardianMiniBeamAttackNoWait::init_(sead::Heap* heap) {
    return GuardianMiniBeamAttack::init_(heap);
}

void GuardianMiniBeamAttackNoWait::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMiniBeamAttack::enter_(params);
    _2e0 = true;
}

void GuardianMiniBeamAttackNoWait::calc_() {
    GuardianMiniBeamAttack::calc_();
    if (_2e0)
        _2e0 = false;
}

void GuardianMiniBeamAttackNoWait::leave_() {
    GuardianMiniBeamAttack::leave_();
}

bool GuardianMiniBeamAttackNoWait::m40() {
    sead::Vector3f pos;
    sub_710033EDD0(&pos);
    if (_2e0)
        return false;
    return sub_710072DDB8(pos, mActor->getMtx(), *mAttackAngle_s);
}

void GuardianMiniBeamAttackNoWait::loadParams_() {
    GuardianMiniBeamAttack::loadParams_();
    getStaticParam(&mAttackAngle_s, "AttackAngle");
}

}  // namespace uking::ai
