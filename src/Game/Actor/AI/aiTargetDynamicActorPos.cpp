#include "Game/Actor/AI/aiTargetDynamicActorPos.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::ai {

TargetDynamicActorPos::TargetDynamicActorPos(const InitArg& arg) : TargetActorPos(arg) {}

TargetDynamicActorPos::~TargetDynamicActorPos() = default;

bool TargetDynamicActorPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetDynamicActorPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetDynamicActorPos::calc_() {
    TargetActorPos::calc_();
}

void TargetDynamicActorPos::leave_() {
    TargetActorPos::leave_();
}

void TargetDynamicActorPos::loadParams_() {
    TargetActorPos::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void TargetDynamicActorPos::m35(sead::Vector3f* pos) {
    if (mTargetActor_d->hasProc()) {
        ksys::act::ActorLinkConstDataAccess acc;
        ksys::act::acquireActor(mTargetActor_d, &acc);
        acc.getActorMtx().getTranslation(*pos);
    } else {
        pos->set(sead::Vector3f::zero);
    }
}

}  // namespace uking::ai
