#include "Game/Actor/Action/actionSilentKilled.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"

namespace uking::action {

SilentKilled::SilentKilled(const InitArg& arg) : Ragdoll(arg) {}

SilentKilled::~SilentKilled() = default;

bool SilentKilled::init_(sead::Heap* heap) {
    return Ragdoll::init_(heap);
}

void SilentKilled::enter_(ksys::act::ai::InlineParamPack* params) {
    Ragdoll::enter_(params);
    sub_7100227134();
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        ksys::act::Unk_71006ED100Arg arg;
        arg._5e = !isBgGroundHit(actor, false);
        arg._62 = true;
        actor->sub_71006DD8F8(arg);
    }
    sub_7100227184();
}

void SilentKilled::leave_() {
    Ragdoll::leave_();
}

void SilentKilled::loadParams_() {
    Ragdoll::loadParams_();
}

void SilentKilled::calc_() {
    Ragdoll::calc_();
}

}  // namespace uking::action
