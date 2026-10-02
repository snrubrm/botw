#include "Game/AI/AI/aiCliffCheckToTargetPosDirSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

CliffCheckToTargetPosDirSelect::CliffCheckToTargetPosDirSelect(const InitArg& arg)
    : CliffCheckSelect(arg) {}

CliffCheckToTargetPosDirSelect::~CliffCheckToTargetPosDirSelect() = default;

bool CliffCheckToTargetPosDirSelect::init_(sead::Heap* heap) {
    return CliffCheckSelect::init_(heap);
}

void CliffCheckToTargetPosDirSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    CliffCheckSelect::enter_(params);
}

void CliffCheckToTargetPosDirSelect::calc_() {
    CliffCheckSelect::calc_();
}

void CliffCheckToTargetPosDirSelect::leave_() {
    CliffCheckSelect::leave_();
}

void CliffCheckToTargetPosDirSelect::loadParams_() {
    CliffCheckSelect::loadParams_();
}

void CliffCheckToTargetPosDirSelect::m34(sead::Vector3f* out) {
    auto* actor = mActor;
    if (!actor)
        *out = sead::Vector3f::ez;
    *out = sub_71005D9330(mActor);
    *out -= actor->getMtx().getTranslation();
    out->normalize();
}

}  // namespace uking::ai
