#include "Game/AI/AI/aiCliffCheckTargetDirSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CliffCheckTargetDirSelect::CliffCheckTargetDirSelect(const InitArg& arg) : CliffCheckSelect(arg) {}

CliffCheckTargetDirSelect::~CliffCheckTargetDirSelect() = default;

void CliffCheckTargetDirSelect::calc_() {
    CliffCheckSelect::calc_();
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void CliffCheckTargetDirSelect::loadParams_() {
    CliffCheckSelect::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void CliffCheckTargetDirSelect::m34(sead::Vector3f* out) {
    if (!mActor) {
        *out = sead::Vector3f::ez;
        return;
    }
    *out = *mTargetPos_d - mActor->getMtx().getTranslation();
    out->y = 0;
    out->normalize();
}

}  // namespace uking::ai
