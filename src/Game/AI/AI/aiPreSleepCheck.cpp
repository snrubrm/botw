#include "Game/AI/AI/aiPreSleepCheck.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

PreSleepCheck::PreSleepCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreSleepCheck::~PreSleepCheck() = default;

bool PreSleepCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: vector copies and parameter-pack setup use different scheduling and stack slots.
void PreSleepCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f basis = mActor->getMtx().getBase(2);
    const sead::Vector3f direction = -basis;
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f query_position = position - basis * *mCheckDist_s;
    if (sub_710072F7D0(mActor, position, query_position, nullptr, -1)) {
        changeChild("睡眠");
        return;
    }

    for (s32 i = 1; i <= 15; ++i) {
        sead::Vector3f rotated = direction;
        ksys::util::sub_71011EF010(&rotated, f32(i) * (sead::Mathf::pi() / 16.0f));
        query_position = position + rotated * *mCheckDist_s;
        if (sub_710072F7D0(mActor, position, query_position, nullptr, -1)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(position - rotated, "TargetPos", -1);
            changeChild("回転", &pack);
            return;
        }

        rotated = direction;
        ksys::util::sub_71011EF010(&rotated, f32(-i) * (sead::Mathf::pi() / 16.0f));
        query_position = position + rotated * *mCheckDist_s;
        if (sub_710072F7D0(mActor, position, query_position, nullptr, -1)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(position - rotated, "TargetPos", -1);
            changeChild("回転", &pack);
            return;
        }
    }
    changeChild("睡眠");
}

void PreSleepCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreSleepCheck::loadParams_() {
    getStaticParam(&mCheckDist_s, "CheckDist");
    getStaticParam(&mCheckRadius_s, "CheckRadius");
}

void PreSleepCheck::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("回転"))
            changeChild("睡眠");
    }
}

bool PreSleepCheck::isFailed() const {
    return isCurrentChild("睡眠") && getCurrentChild()->isFailed();
}

bool PreSleepCheck::isFinished() const {
    return isCurrentChild("睡眠") && getCurrentChild()->isFinished();
}

}  // namespace uking::ai
