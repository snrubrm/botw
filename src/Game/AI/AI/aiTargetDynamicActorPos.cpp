#include "Game/AI/AI/aiTargetDynamicActorPos.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

TargetDynamicActorPos::TargetDynamicActorPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetDynamicActorPos::~TargetDynamicActorPos() = default;

bool TargetDynamicActorPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetDynamicActorPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetDynamicActorPos::calc_() {
    TargetPosAI::calc_();
}

void TargetDynamicActorPos::leave_() {
    TargetPosAI::leave_();
}

void TargetDynamicActorPos::loadParams_() {
    TargetPosAI::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void TargetDynamicActorPos::m35(sead::Vector3f* pos) {
    if (mTargetActor_d->hasProc()) {
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(mTargetActor_d, &acc);
        acc.getActorMtx().getTranslation(*pos);
    } else {
        pos->set(sead::Vector3f::zero);
    }
}

}  // namespace uking::ai
