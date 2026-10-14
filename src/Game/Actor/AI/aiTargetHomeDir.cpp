#include "Game/Actor/AI/aiTargetHomeDir.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetHomeDir::TargetHomeDir(const InitArg& arg) : TargetActorPos(arg) {}

TargetHomeDir::~TargetHomeDir() = default;

bool TargetHomeDir::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void TargetHomeDir::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void TargetHomeDir::calc_() {
    TargetActorPos::calc_();
}

void TargetHomeDir::leave_() {
    TargetActorPos::leave_();
}

void TargetHomeDir::loadParams_() {
    TargetActorPos::loadParams_();
}

void TargetHomeDir::m35(sead::Vector3f* pos) {
    mActor->getMtx().getTranslation(*pos);
    sead::Matrix34f mtx;
    mActor->getHomeMtx(&mtx);
    sead::Vector3f dir;
    mtx.getBase(dir, 2);
    *pos += dir * 3.0f;
}

}  // namespace uking::ai
