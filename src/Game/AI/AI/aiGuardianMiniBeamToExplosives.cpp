#include "Game/AI/AI/aiGuardianMiniBeamToExplosives.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianMiniBeamToExplosives::GuardianMiniBeamToExplosives(const InitArg& arg)
    : GuardianMiniBeamAttack(arg) {}

GuardianMiniBeamToExplosives::~GuardianMiniBeamToExplosives() = default;

void GuardianMiniBeamToExplosives::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71004195B4()) {
        sead::Vector3f pos;
        m46(&pos);
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("後ずさり", &pack);
    } else {
        GuardianMiniBeamAttack::enter_(params);
    }
}

// NON_MATCHING: the original copies `pos` to a temporary before the call (load/store scheduling only)
void GuardianMiniBeamToExplosives::calc_() {
    if (getCurrentChild()->isChangeable() &&
        sub_71005DEC08(mTargetActor_d, mActor, 999.0f, 999.0f, sead::Mathf::pi())) {
        setFailed();
        return;
    }

    const bool back_step = isCurrentChild("後ずさり");
    sead::Vector3f pos;
    if (back_step) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            sub_710033EA88();
            changeToPrepareBattle();
            return;
        }
        m46(&pos);
        sub_71005DB1D8(mActor, pos);
        getCurrentChild()->setDynamicParam(pos, "TargetPos");
    } else {
        GuardianMiniBeamAttack::calc_();
        if (isCurrentChild("戦闘攻撃") && m46(&pos)) {
            sub_71005DB1D8(mActor, pos);
            getCurrentChild()->setDynamicParam(pos, "TargetPos");
        }
    }
}

// NON_MATCHING: register allocation only (ours keeps the actor's x / z in s9 / s8 and the differences in s12 / s11,
// the original the other way round)
bool GuardianMiniBeamToExplosives::sub_71004195B4() {
    auto* actor = mActor;
    if (!actor)
        return false;
    sead::Vector3f target;
    if (!m46(&target))
        return false;
    const sead::Vector3f& pos = actor->getMtx().getTranslation();
    sead::Vector3f dir{pos.x - target.x, 0.0f, pos.z - target.z};
    dir.normalize();
    sead::Vector3f probe;
    probe.x = dir.x * 5.0f + pos.x;
    probe.y = dir.y * 5.0f + pos.y;
    probe.z = dir.z * 5.0f + pos.z;
    const f32 dist =
        sead::Mathf::sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.z - target.z) * (pos.z - target.z));
    if (!sub_710072F8E4(actor, probe, nullptr, 3.0f))
        return false;
    return dist <= *mExplosivesAvoidDist_s;
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
