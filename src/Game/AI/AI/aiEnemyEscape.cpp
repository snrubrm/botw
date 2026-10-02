#include "Game/AI/AI/aiEnemyEscape.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyEscape::EnemyEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyEscape::~EnemyEscape() = default;

void EnemyEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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
