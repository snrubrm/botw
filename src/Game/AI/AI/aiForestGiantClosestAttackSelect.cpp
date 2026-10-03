#include "Game/AI/AI/aiForestGiantClosestAttackSelect.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

ForestGiantClosestAttackSelect::ForestGiantClosestAttackSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

ForestGiantClosestAttackSelect::~ForestGiantClosestAttackSelect() = default;

bool ForestGiantClosestAttackSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original keeps the two getU32(100) rolls (and the multiply) in the near / far arms
// and only merges from the rate dereference on; ours merges the arms right after the call
void ForestGiantClosestAttackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f& target_pos = sub_71005D9330(mActor);
    const sead::Vector3f& target_vel = sub_71005D9548(mActor);
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f forward;
    sub_71000891C8(&forward, mActor);
    sead::Vector3f to_target = target_pos - pos;
    to_target.normalize();

    bool hip_drop;
    if (forward.dot(to_target) < 0) {
        hip_drop = true;
    } else {
        const f32 dx = pos.x - target_pos.x;
        const f32 dz = pos.z - target_pos.z;
        s32 roll;
        const s32* rate;
        if (target_vel.dot(to_target) >= 0 && dx * dx + dz * dz >= *mFarDist_s * *mFarDist_s) {
            roll = sead::GlobalRandom::instance()->getU32(100);
            rate = mHipDropRateFar_s;
        } else {
            roll = sead::GlobalRandom::instance()->getU32(100);
            rate = mHipDropRate_s;
        }
        hip_drop = roll < *rate - _50 * 5;
    }

    if (hip_drop) {
        _50 = _50 < 0 ? 0 : _50 + 1;
        changeChild("ヒップドロップ", params);
    } else {
        _50 = _50 > 0 ? 0 : _50 - 1;
        changeChild("足踏み", params);
    }
}

void ForestGiantClosestAttackSelect::calc_() {}

bool ForestGiantClosestAttackSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool ForestGiantClosestAttackSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void ForestGiantClosestAttackSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ForestGiantClosestAttackSelect::loadParams_() {
    getStaticParam(&mHipDropRate_s, "HipDropRate");
    getStaticParam(&mHipDropRateFar_s, "HipDropRateFar");
    getStaticParam(&mFarDist_s, "FarDist");
}

}  // namespace uking::ai
