#include "Game/AI/Action/actionLandRagdoll.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::action {

LandRagdoll::LandRagdoll(const InitArg& arg) : Ragdoll(arg) {}

LandRagdoll::~LandRagdoll() = default;

bool LandRagdoll::init_(sead::Heap* heap) {
    return Ragdoll::init_(heap);
}

void LandRagdoll::enter_(ksys::act::ai::InlineParamPack* params) {
    Ragdoll::enter_(params);
}

void LandRagdoll::leave_() {
    Ragdoll::leave_();
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor))
        actor->sub_71006DD92C(true);
    sub_71007A3540(mActor);
}

void LandRagdoll::loadParams_() {
    Ragdoll::loadParams_();
}

void LandRagdoll::calc_() {
    Ragdoll::calc_();
}

}  // namespace uking::action
