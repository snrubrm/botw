#include "Game/AI/AI/aiGuardianMiniBeamToExplosives.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

GuardianMiniBeamToExplosives::GuardianMiniBeamToExplosives(const InitArg& arg)
    : GuardianMiniBeamAttack(arg) {}

GuardianMiniBeamToExplosives::~GuardianMiniBeamToExplosives() = default;

void GuardianMiniBeamToExplosives::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMiniBeamAttack::enter_(params);
}

// NON_MATCHING: in the second branch the original loads mActor after copying the position
// into the argument temporary; we load it first
void GuardianMiniBeamToExplosives::calc_() {
    if (getCurrentChild()->isChangeable() &&
        sub_71005DEC08(mTargetActor_d, mActor, 999.0f, 999.0f, sead::Mathf::pi())) {
        setFailed();
        return;
    }

    if (isCurrentChild("後ずさり")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            sub_710033EA88();
            changeToPrepareBattle();
            return;
        }
        sead::Vector3f pos;
        m46(&pos);
        const sead::Vector3f target(pos.x, pos.y, pos.z);
        sub_71005DB1D8(mActor, target);
        getCurrentChild()->setDynamicParam(pos, "TargetPos");
    } else {
        GuardianMiniBeamAttack::calc_();
        if (isCurrentChild("戦闘攻撃")) {
            sead::Vector3f pos;
            if (m46(&pos)) {
                sub_71005DB1D8(mActor, pos);
                getCurrentChild()->setDynamicParam(pos, "TargetPos");
            }
        }
    }
}

void GuardianMiniBeamToExplosives::loadParams_() {
    GuardianMiniBeamAttack::loadParams_();
    getStaticParam(&mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool GuardianMiniBeamToExplosives::m39() {
    return m40();
}

void GuardianMiniBeamToExplosives::m42() {}

bool GuardianMiniBeamToExplosives::m46(sead::Vector3f* out) {
    if (!out)
        return false;
    if (!mTargetActor_d)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(*out);
    return true;
}

}  // namespace uking::ai
