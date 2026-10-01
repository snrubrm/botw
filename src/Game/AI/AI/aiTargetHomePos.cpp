#include "Game/AI/AI/aiTargetHomePos.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetHomePos::TargetHomePos(const InitArg& arg) : TargetPosAI(arg) {}

TargetHomePos::~TargetHomePos() = default;

bool TargetHomePos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetHomePos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetHomePos::calc_() {
    TargetPosAI::calc_();
}

void TargetHomePos::leave_() {
    TargetPosAI::leave_();
}

void TargetHomePos::loadParams_() {
    TargetPosAI::loadParams_();
}

void TargetHomePos::m35(sead::Vector3f* pos) {
    mActor->getHomePos(pos);
}

}  // namespace uking::ai
