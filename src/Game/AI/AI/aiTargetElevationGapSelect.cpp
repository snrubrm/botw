#include "Game/AI/AI/aiTargetElevationGapSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetElevationGapSelect::TargetElevationGapSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetElevationGapSelect::~TargetElevationGapSelect() = default;

bool TargetElevationGapSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetElevationGapSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 y = mActor->getMtx().getTranslation().y;
    const f32 target_y = sub_71005D9330(mActor).y;
    if (y + *mElvGap_s < target_y)
        changeChild("高い", params);
    else
        changeChild("低い", params);
}

void TargetElevationGapSelect::calc_() {}

void TargetElevationGapSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetElevationGapSelect::loadParams_() {
    getStaticParam(&mElvGap_s, "ElvGap");
}

}  // namespace uking::ai
