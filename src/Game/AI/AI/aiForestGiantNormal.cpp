#include "Game/AI/AI/aiForestGiantNormal.h"

namespace uking::ai {

ForestGiantNormal::ForestGiantNormal(const InitArg& arg) : EnemyNormal(arg) {}

ForestGiantNormal::~ForestGiantNormal() = default;

bool ForestGiantNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

// NON_MATCHING: the original stores _3e4 alone and pairs _3dc/_3e0 into one 8-byte store
void ForestGiantNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    _3dc = 0;
    _3e0 = 120;
    _3e4 = 120;
    EnemyNormal::enter_(params);
    _3d8 = false;
}

void ForestGiantNormal::leave_() {
    EnemyNormal::leave_();
}

void ForestGiantNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mSleepingHearAwnRatio_s, "SleepingHearAwnRatio");
}

bool ForestGiantNormal::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x3000015) {
        _3d8 = false;
        return false;
    }
    if (message.getType().value == 0x3000016) {
        _3d8 = true;
        return false;
    }
    return EnemyNormal::handleMessage_(message);
}

}  // namespace uking::ai
