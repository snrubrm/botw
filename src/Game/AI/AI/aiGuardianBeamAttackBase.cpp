#include "Game/AI/AI/aiGuardianBeamAttackBase.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianBeamAttackBase::GuardianBeamAttackBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianBeamAttackBase::~GuardianBeamAttackBase() = default;

bool GuardianBeamAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardianBeamAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianBeamAttackBase::calc_() {}

void GuardianBeamAttackBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianBeamAttackBase::loadParams_() {}

uking::act::Guardian* GuardianBeamAttackBase::sub_7100411DE0() {
    if (mActor) {
        if (auto* component = sead::DynamicCast<act::GuardianComponent>(mActor))
            return component->sub_710003D2B4();
    }
    return nullptr;
}

act::GuardianComponent* GuardianBeamAttackBase::sub_7100411E74() {
    if (mActor)
        return sead::DynamicCast<act::GuardianComponent>(mActor);
    return nullptr;
}

bool GuardianBeamAttackBase::sub_7100411F00() {
    if (mActor) {
        if (auto* component = sead::DynamicCast<act::GuardianComponent>(mActor)) {
            if (auto* guardian = component->sub_710003D2B4())
                return guardian->sub_710003B554();
        }
    }
    return false;
}

}  // namespace uking::ai
