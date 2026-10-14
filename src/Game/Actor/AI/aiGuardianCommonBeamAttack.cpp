#include "Game/Actor/AI/aiGuardianCommonBeamAttack.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GuardianCommonBeamAttack::GuardianCommonBeamAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianCommonBeamAttack::~GuardianCommonBeamAttack() = default;

bool GuardianCommonBeamAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardianCommonBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianCommonBeamAttack::calc_() {}

void GuardianCommonBeamAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianCommonBeamAttack::loadParams_() {}

uking::act::Guardian* GuardianCommonBeamAttack::sub_7100411DE0() {
    if (mActor) {
        if (auto* component = sead::DynamicCast<act::GuardianComponent>(mActor))
            return component->sub_710003D2B4();
    }
    return nullptr;
}

act::GuardianComponent* GuardianCommonBeamAttack::sub_7100411E74() {
    if (mActor)
        return sead::DynamicCast<act::GuardianComponent>(mActor);
    return nullptr;
}

bool GuardianCommonBeamAttack::sub_7100411F00() {
    if (mActor) {
        if (auto* component = sead::DynamicCast<act::GuardianComponent>(mActor)) {
            if (auto* guardian = component->sub_710003D2B4())
                return guardian->sub_710003B554();
        }
    }
    return false;
}

}  // namespace uking::ai
