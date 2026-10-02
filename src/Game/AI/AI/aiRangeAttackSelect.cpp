#include "Game/AI/AI/aiRangeAttackSelect.h"
#include <cmath>
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// NON_MATCHING: store scheduling (the original loads the _58 vtable after the param zeroing)
RangeAttackSelect::RangeAttackSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RangeAttackSelect::~RangeAttackSelect() = default;

void RangeAttackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsIgnoreSmallHit_s)
        setDamageCallbackTiming(mActor, 4, &_58);

    const auto& pos = mActor->getMtx().getTranslation();
    const f32 dx = pos.x - mTargetPos_d->x;
    const f32 dz = pos.z - mTargetPos_d->z;
    const f32 dist = sqrtf(dx * dx + dz * dz);
    if (!(dist >= *mRangeDist_s + sub_71007320F0(mActor, *mWeaponIdx_s))) {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("レンジ内", &child_params);
    } else {
        ksys::act::ai::InlineParamPack child_params;
        child_params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("レンジ外", &child_params);
    }
}

void RangeAttackSelect::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

void RangeAttackSelect::leave_() {
    sub_71005DA114(mActor, &_58);
}

void RangeAttackSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRangeDist_s, "RangeDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
}

bool RangeAttackSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool RangeAttackSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

}  // namespace uking::ai
