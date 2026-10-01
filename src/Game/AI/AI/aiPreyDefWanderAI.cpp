#include "Game/AI/AI/aiPreyDefWanderAI.h"

namespace uking::ai {

PreyDefWanderAI::PreyDefWanderAI(const InitArg& arg) : DefWanderAI(arg) {}

PreyDefWanderAI::~PreyDefWanderAI() = default;

bool PreyDefWanderAI::init_(sead::Heap* heap) {
    return DefWanderAI::init_(heap);
}

void PreyDefWanderAI::enter_(ksys::act::ai::InlineParamPack* params) {
    DefWanderAI::enter_(params);
    _a0 = 0;
}

void PreyDefWanderAI::calc_() {
    if (isCurrentChild("最後の手段") || isCurrentChild("地形嵌り")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            changeChild("待機");
        return;
    }

    if (isCurrentChild("移動")) {
        if (getCurrentChild()->isFinished()) {
            _a0 = 0;
        } else if ((*mIsStuckOnTerrain_a && *mFramesStuckOnTerrain_a >= *mFramesStuckLimit_s) ||
                   getCurrentChild()->isFailed()) {
            *mIsStuckOnTerrain_a = false;
            *mFramesStuckOnTerrain_a = 0;
            if (++_a0 >= *mTimesStuckLimit_s)
                changeChild("最後の手段");
            else
                changeChild("地形嵌り");
            return;
        }
    }

    DefWanderAI::calc_();
}

void PreyDefWanderAI::leave_() {
    DefWanderAI::leave_();
}

void PreyDefWanderAI::loadParams_() {
    DefWanderAI::loadParams_();
    getStaticParam(&mTimesStuckLimit_s, "TimesStuckLimit");
    getStaticParam(&mFramesStuckLimit_s, "FramesStuckLimit");
    getAITreeVariable(&mFramesStuckOnTerrain_a, "FramesStuckOnTerrain");
    getAITreeVariable(&mIsStuckOnTerrain_a, "IsStuckOnTerrain");
}

}  // namespace uking::ai
