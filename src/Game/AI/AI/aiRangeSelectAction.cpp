#include "Game/AI/AI/aiRangeSelectAction.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

RangeSelectAction::RangeSelectAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RangeSelectAction::~RangeSelectAction() = default;

bool RangeSelectAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RangeSelectAction::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
}

void RangeSelectAction::calc_() {
    auto* child = getCurrentChild();
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (child->isFinished() || child->isFailed())
        return;

    if (child->isChangeable() && *mIsSelectEveryFrame_s)
        m34();
}

void RangeSelectAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RangeSelectAction::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsSelectEveryFrame_s, "IsSelectEveryFrame");
    getStaticParam(&mIsRangeXZ_s, "IsRangeXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: regalloc (operand registers of the shared sqrt tail)
f32 RangeSelectAction::m35() {
    if (*mIsRangeXZ_s)
        return sead::Mathf::sqrt(ksys::util::sqXZDistance(mActor->getMtx().getTranslation(), *mTargetPos_d));
    return (mActor->getMtx().getTranslation() - *mTargetPos_d).length();
}

f32 RangeSelectAction::sub_7100539F84() {
    return sub_71007320F0(mActor, *mWeaponIdx_s);
}

}  // namespace uking::ai
