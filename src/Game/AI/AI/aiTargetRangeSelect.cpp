#include "Game/AI/AI/aiTargetRangeSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

TargetRangeSelect::TargetRangeSelect(const InitArg& arg) : RangeSelect(arg) {}

TargetRangeSelect::~TargetRangeSelect() = default;

void TargetRangeSelect::loadParams_() {
    RangeSelect::loadParams_();
    getStaticParam(&mIsXZOnly_s, "IsXZOnly");
}

f32 TargetRangeSelect::m38() {
    if (mIsXZOnly_s) {
        return sead::Mathf::sqrt(ksys::util::sqXZDistance(mActor->getMtx().getTranslation(),
                                                          sub_71005D9330(mActor)));
    }
    return (mActor->getMtx().getTranslation() - sub_71005D9330(mActor)).length();
}

}  // namespace uking::ai
