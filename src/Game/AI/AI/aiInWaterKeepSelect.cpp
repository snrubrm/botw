#include "Game/AI/AI/aiInWaterKeepSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

InWaterKeepSelect::InWaterKeepSelect(const InitArg& arg) : InWaterSelect(arg) {}

InWaterKeepSelect::~InWaterKeepSelect() = default;

bool InWaterKeepSelect::init_(sead::Heap* heap) {
    return InWaterSelect::init_(heap);
}

void InWaterKeepSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!*mIsKeepInWater_a) {
        InWaterSelect::enter_(params);
        return;
    }

    f32 depth = 0.0f;
    if (mActor->get68f().load()) {
        const f32 y = mActor->getMtx().m[1][3];
        depth = mActor->get6f0() - y;
    }

    if (depth <= *mOutWaterDepth_s)
        changeChild("水上", params);
    else
        changeChild("水中", params);
}

void InWaterKeepSelect::calc_() {
    InWaterSelect::calc_();
}

void InWaterKeepSelect::leave_() {
    *mIsKeepInWater_a = isCurrentChild("水中");
    InWaterSelect::leave_();
}

void InWaterKeepSelect::loadParams_() {
    InWaterSelect::loadParams_();
    getAITreeVariable(&mIsKeepInWater_a, "IsKeepInWater");
}

}  // namespace uking::ai
