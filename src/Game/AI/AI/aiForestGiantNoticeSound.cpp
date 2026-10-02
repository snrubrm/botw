#include "Game/AI/AI/aiForestGiantNoticeSound.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

ForestGiantNoticeSound::ForestGiantNoticeSound(const InitArg& arg) : EnemyNoticeSound(arg) {}

ForestGiantNoticeSound::~ForestGiantNoticeSound() = default;

bool ForestGiantNoticeSound::init_(sead::Heap* heap) {
    return EnemyNoticeSound::init_(heap);
}

void ForestGiantNoticeSound::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeSound::enter_(params);
}

void ForestGiantNoticeSound::calc_() {
    EnemyNoticeSound::calc_();
}

void ForestGiantNoticeSound::leave_() {
    EnemyNoticeSound::leave_();
}

void ForestGiantNoticeSound::loadParams_() {
    EnemyNoticeSound::loadParams_();
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mUseSimpleOffset_s, "UseSimpleOffset");
}

void ForestGiantNoticeSound::m35() {
    if (*mUseSimpleOffset_s)
        sub_71005DB1D8(mActor, *mTargetPos_d);
    else
        sub_71005DB068(mActor, *mTargetPos_d);
}

}  // namespace uking::ai
