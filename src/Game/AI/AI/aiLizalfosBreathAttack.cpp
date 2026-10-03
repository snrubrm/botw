#include "Game/AI/AI/aiLizalfosBreathAttack.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LizalfosBreathAttack::LizalfosBreathAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LizalfosBreathAttack::~LizalfosBreathAttack() = default;

void LizalfosBreathAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = ksys::Timer(0, 0, 1.0f);
    changeChild("ブレス攻撃");
}

void LizalfosBreathAttack::calc_() {
    auto* child = getCurrentChild();
    bool is_breath = false;
    if (child->isFinished() || child->isFailed())
        is_breath = isCurrentChild("ブレス攻撃");

    child = getCurrentChild();
    if (is_breath) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        if (_50.value >= f32(*mMinAttackTimeForTired_s))
            sub_7100484734();
        else
            setFinished();
        return;
    }

    if ((child->isFinished() || child->isFailed()) && isCurrentChild("疲れる")) {
        if (getCurrentChild()->isFailed())
            setFailed();
        else
            setFinished();
        return;
    }
    if (isCurrentChild("ブレス攻撃"))
        _50.update();
}

// NON_MATCHING: the original keeps the tired-time product in one FP register computed before the
// param pack initialization loop; ours sinks it below the loop (extra d9 spill pair)
void LizalfosBreathAttack::sub_7100484734() {
    const s32 elapsed = s32(_50.value);
    const s32 over_min = sead::Mathi::max(elapsed - *mMinAttackTimeForTired_s, 0);
    const f32 rate = *mTiredTimeRate_s;
    const f32 tired_time = f32(over_min) * rate;
    const s32 min_tired_time = *mMinTiredTime_s;

    ksys::act::ai::InlineParamPack params;
    params.addInt(s32(tired_time) + min_tired_time, "DynFirstActionTime", -1);
    params.addInt(0, "DynSecondActionTime", -1);
    params.addInt(0, "DynAllActionTime", -1);
    changeChild("疲れる", &params);
}

void LizalfosBreathAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LizalfosBreathAttack::loadParams_() {
    getStaticParam(&mMinAttackTimeForTired_s, "MinAttackTimeForTired");
    getStaticParam(&mMinTiredTime_s, "MinTiredTime");
    getStaticParam(&mTiredTimeRate_s, "TiredTimeRate");
}

}  // namespace uking::ai
