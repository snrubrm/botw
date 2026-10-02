#include "Game/AI/AI/aiRemainsWaterRoot.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

RemainsWaterRoot::RemainsWaterRoot(const InitArg& arg) : RemainsRoot(arg) {}

RemainsWaterRoot::~RemainsWaterRoot() = default;

bool RemainsWaterRoot::init_(sead::Heap* heap) {
    return RemainsRoot::init_(heap);
}

void RemainsWaterRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsRoot::enter_(params);
}

void RemainsWaterRoot::calc_() {
    RemainsRoot::calc_();
    m35(false);
}

void RemainsWaterRoot::leave_() {
    RemainsRoot::leave_();
}

void RemainsWaterRoot::loadParams_() {
    RemainsRoot::loadParams_();
    getAITreeVariable(&mRemainsWaterBattleInfo_a, "RemainsWaterBattleInfo");
}

void RemainsWaterRoot::m35(bool x) {
    if (x) {
        sub_710054BAC8(true);
        return;
    }

    auto* child = getCurrentChild();
    if (child && (child->isFinished() || child->isFailed() || child->isChangeable()))
        sub_710054BAC8(false);
}

void RemainsWaterRoot::m36() {
    xlinkEventOn(mActor, 25, 1, false);
    changeChild("通常行動");
}

}  // namespace uking::ai
