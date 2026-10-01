#include "Game/AI/AI/aiForestGiantRecognizeTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

ForestGiantRecognizeTarget::ForestGiantRecognizeTarget(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

ForestGiantRecognizeTarget::~ForestGiantRecognizeTarget() = default;

bool ForestGiantRecognizeTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForestGiantRecognizeTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ForestGiantRecognizeTarget::leave_() {
    sub_71005DB3EC(mActor);
}

void ForestGiantRecognizeTarget::loadParams_() {}

}  // namespace uking::ai
