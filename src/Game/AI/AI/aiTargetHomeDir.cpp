#include "Game/AI/AI/aiTargetHomeDir.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetHomeDir::TargetHomeDir(const InitArg& arg) : TargetPosAI(arg) {}

TargetHomeDir::~TargetHomeDir() = default;

bool TargetHomeDir::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetHomeDir::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetHomeDir::calc_() {
    TargetPosAI::calc_();
}

void TargetHomeDir::leave_() {
    TargetPosAI::leave_();
}

void TargetHomeDir::loadParams_() {
    TargetPosAI::loadParams_();
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
