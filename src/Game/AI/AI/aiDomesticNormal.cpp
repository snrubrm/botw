#include "Game/AI/AI/aiDomesticNormal.h"

namespace uking::ai {

DomesticNormal::DomesticNormal(const InitArg& arg) : PreyNormal(arg) {}

DomesticNormal::~DomesticNormal() = default;

bool DomesticNormal::init_(sead::Heap* heap) {
    return PreyNormal::init_(heap);
}

void DomesticNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyNormal::enter_(params);
}

void DomesticNormal::leave_() {
    PreyNormal::leave_();
}

bool DomesticNormal::m44() {
    return isCurrentChild("逃走") || isCurrentChild("ダメージ逃走") || isCurrentChild("気づき") ||
           isCurrentChild("ふり向き") || isCurrentChild("興味対象発見") ||
           isCurrentChild("ターゲット通知") || isCurrentChild("最後の手段");
}

void DomesticNormal::loadParams_() {
    PreyNormal::loadParams_();
    getStaticParam(&mWaitFramesAfterRunMax_s, "WaitFramesAfterRunMax");
    getStaticParam(&mNumFailPathHomeFadeout_s, "NumFailPathHomeFadeout");
    getStaticParam(&mDistUntilReturnToHomePos_s, "DistUntilReturnToHomePos");
    getStaticParam(&mWaitFramesAfterRunMin_s, "WaitFramesAfterRunMin");
    getStaticParam(&mStaggerVelocityThreshold_s, "StaggerVelocityThreshold");
    getStaticParam(&mDistHomePosFadeout_s, "DistHomePosFadeout");
    getAITreeVariable(&mDomesticAnimalRailName_a, "DomesticAnimalRailName");
}

}  // namespace uking::ai
