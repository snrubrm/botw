#include "Game/AI/AI/aiEnemyEscape.h"
#include <cfloat>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

EnemyEscape::EnemyEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyEscape::~EnemyEscape() = default;

// NON_MATCHING: the float compares use `b.le` (ours) instead of `b.ls`, and the timer stores are three
// `str` instead of `stp` + `str`; everything else (flow, stack frame, pack handling) matches
void EnemyEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    if (!sub_7100736D98(mActor) && !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        _74 = false;
        const s32 tumble_rand = *mTumbleRand_s;
        const f32 tumble_time = *mTumbleTime_s - tumble_rand * 0.5f +
                                s32(tumble_rand * sead::GlobalRandom::instance()->getF32());
        _68 = ksys::Timer(tumble_time, tumble_time);
        const s32 escape_rand = *mEscapeRand_s;
        const f32 escape_time = *mEscapeTime_s - escape_rand * 0.5f +
                                s32(escape_rand * sead::GlobalRandom::instance()->getF32());
        _78 = ksys::Timer(escape_time, escape_time);
        const sead::Vector3f target = *mTargetPos_d;
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target, "TargetPos", -1);
        changeChild("逃走移動", &pack);
    } else {
        {
            const sead::Vector3f target = *mTargetPos_d;
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("逃走移動", &pack);
        }
        if (_78.value > FLT_EPSILON) {
            const sead::Vector3f& target = *mTargetPos_d;
            const f32 target_x = target.x;
            const f32 target_z = target.z;
            const f32 dx = target_x - mActor->getMtx().getTranslation().x;
            const f32 dz = target_z - mActor->getMtx().getTranslation().z;
            if (sead::Vector3f(dx, 0.0f, dz).length() <= *mEscapeDist_s || !_74)
                return;
        }
        setFinished();
    }
}

bool EnemyEscape::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

// NON_MATCHING: regalloc (w21/w22 swapped for the -1.0 rate and the random mantissa)
void EnemyEscape::loadParams_() {
    if (!mActor->getParam())
        return;

    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mTumbleTime_s, "TumbleTime");
    getStaticParam(&mTumbleRand_s, "TumbleRand");
    getStaticParam(&mEscapeTime_s, "EscapeTime");
    getStaticParam(&mEscapeRand_s, "EscapeRand");
    getStaticParam(&mEscapeDist_s, "EscapeDist");

    const s32 tumble_rand = *mTumbleRand_s;
    const f32 tumble_time = *mTumbleTime_s - tumble_rand * 0.5f +
                            s32(tumble_rand * sead::GlobalRandom::instance()->getF32());
    _68 = ksys::Timer(tumble_time, tumble_time);

    const s32 escape_rand = *mEscapeRand_s;
    const f32 escape_time = *mEscapeTime_s - escape_rand * 0.5f +
                            s32(escape_rand * sead::GlobalRandom::instance()->getF32());
    _78 = ksys::Timer(escape_time, escape_time);
}

}  // namespace uking::ai
