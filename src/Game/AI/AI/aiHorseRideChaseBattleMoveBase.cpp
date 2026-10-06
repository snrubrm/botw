#include "Game/AI/AI/aiHorseRideChaseBattleMoveBase.h"
#include "Game/Actor/actRideable.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

using Gear = uking::act::Rideable::Gear;

HorseRideChaseBattleMoveBase::HorseRideChaseBattleMoveBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

HorseRideChaseBattleMoveBase::~HorseRideChaseBattleMoveBase() = default;

bool HorseRideChaseBattleMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: register numbering only (the original loads the target position before the NaN fallback of
// the normalization, keeps the actor position in d12/d13/d9 and spills the target x).
s32 HorseRideChaseBattleMoveBase::sub_71004409D4() {
    auto* target = sub_71005D9050(mActor);
    if (!target)
        return 3;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(target, &accessor);
    const sead::Matrix34f& target_mtx = accessor.getActorMtx();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f forward;
    mActor->getMtx().getBase(forward, 2);
    forward.normalize();
    const f32 dist = (target_mtx.getTranslation() - pos).dot(forward);
    if (static_cast<f32>(static_cast<s32>(*mSpeedUpDist_s)) < dist)
        return 0;
    return static_cast<f32>(static_cast<s32>(*mSlowDownDist_s)) > dist ? 2 : 1;
}

void HorseRideChaseBattleMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _58.x();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D93CC(mActor), "TargetPos", -1);
    changeChild("追跡指令", &pack);
}

// NON_MATCHING: stack layout of the Gear locals / the parameter name temporary (frame 0x70 instead of 0x60) and
// the order of the mode tests (the original tests 0, 1, 2 and tail-duplicates the dispatch into both target-gear
// paths).
void HorseRideChaseBattleMoveBase::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child->isChangeable()) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        if ((pos - sub_71005D9330(mActor)).length() > *mBaseDist_s + *mOutDist_s) {
            setFailed();
            return;
        }
    }

    child->setDynamicParam(sub_71005D93CC(mActor), "TargetPos");
    if (!m36())
        return;

    const s32 mode = sub_71004409D4();
    auto* rideable = sub_710073D3C8(mActor);
    const Gear current(rideable ? (rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b) : 0);
    u64 target_value = 0;
    if (auto* link = sub_71005D9050(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        target_value = accessor.sub_7100D142E0();
    }
    const Gear target(target_value);
    if (mode == 0) {
        const s32 gear = sead::Mathi::min(s32(target) + 1, 4);
        if (current < gear)
            m34(gear);
    } else if (mode == 1) {
        if (current != target)
            m34(target);
    } else if (mode == 2) {
        const Gear min_gear(2);
        const s32 gear = target > min_gear ? s32(target) - 1 : s32(min_gear);
        if (current >= target && gear != s32(current))
            m34(gear);
    }
}

void HorseRideChaseBattleMoveBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideChaseBattleMoveBase::loadParams_() {
    getStaticParam(&mSlowDownDist_s, "SlowDownDist");
    getStaticParam(&mSpeedUpDist_s, "SpeedUpDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
}

bool HorseRideChaseBattleMoveBase::handleMessage_(const ksys::Message* message) {
    if (!_58.m2(*message))
        return false;
    setFailed();
    return true;
}

}  // namespace uking::ai
