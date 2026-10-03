#include "Game/AI/AI/aiGuardianBeamAttack.h"

namespace uking::ai {

GuardianBeamAttack::GuardianBeamAttack(const InitArg& arg) : GuardianBeamAttackBase(arg) {}

GuardianBeamAttack::~GuardianBeamAttack() {
    if (_78) {
        delete _78;
        _78 = nullptr;
    }
}

bool Unk_71023f6f80::m5(ksys::act::Actor* actor) {
    _a0->sub_710040FC24(actor);
    return false;
}

bool GuardianBeamAttack::init_(sead::Heap* heap) {
    if (!GuardianBeamAttackBase::init_(heap))
        return false;
    _78 = new (heap) Unk_71023f6f80(this);
    return true;
}

void GuardianBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianBeamAttackBase::enter_(params);
}

void GuardianBeamAttack::leave_() {
    GuardianBeamAttackBase::leave_();
}

void GuardianBeamAttack::loadParams_() {
    GuardianBeamAttackBase::loadParams_();
    getStaticParam(&mLightRadius_s, "LightRadius");
    getStaticParam(&mLightLength_s, "LightLength");
    getStaticParam(&mLightLengthOffset_s, "LightLengthOffset");
    getStaticParam(&mEarSpeed_s, "EarSpeed");
    getStaticParam(&mAdjustRadius_s, "AdjustRadius");
}

}  // namespace uking::ai
