#include "Game/AI/AI/aiSetTargetPosToPlayer.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

SetTargetPosToPlayer::SetTargetPosToPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SetTargetPosToPlayer::~SetTargetPosToPlayer() = default;

bool SetTargetPosToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SetTargetPosToPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    _74 = 0;
    sead::Vector3f pos;
    if (!sub_71005694B4(&pos))
        mActor->getMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack child_params;
    child_params.addVec3(pos, "TargetPos", -1);
    changeChild("子アクション", &child_params);
}

void SetTargetPosToPlayer::calc_() {
    _68.update();
    if (*mUpdateTargetInterval_s < 0)
        return;

    if (_68.value <= sead::Mathf::epsilon()) {
        sead::Vector3f pos;
        if (sub_71005694B4(&pos))
            getCurrentChild()->setDynamicParam(pos, "TargetPos");
    }
}

// NON_MATCHING: scheduling / register allocation of the normalisation (the original computes the
// x and z differences before player.y + height; ours keeps source order)
bool SetTargetPosToPlayer::sub_71005694B4(sead::Vector3f* pos) {
    if (_74 > *mMaxUpdateNum_s)
        return false;

    const sead::Vector3f actor_pos = mActor->getMtx().getTranslation();
    const sead::Vector3f& player_pos = getPlayerPosition();
    sead::Vector3f target = player_pos;
    target.y += *mHeightOffset_s;
    sead::Vector3f dir = target - actor_pos;
    dir.normalize();

    sead::Vector3f result = target + dir * *mAddLength_s;
    const f32 range = *mRandRange_s;
    if (sead::GlobalRandom::instance()->getF32() < *mRandRate_s) {
        result.x += sead::GlobalRandom::instance()->getF32Range(-range, range);
        result.z += sead::GlobalRandom::instance()->getF32Range(-range, range);
    }
    *pos = result;

    const f32 interval = *mUpdateTargetInterval_s + 0.5f;
    _68 = ksys::Timer(interval, interval);
    ++_74;
    return true;
}

void SetTargetPosToPlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetTargetPosToPlayer::loadParams_() {
    getStaticParam(&mUpdateTargetInterval_s, "UpdateTargetInterval");
    getStaticParam(&mMaxUpdateNum_s, "MaxUpdateNum");
    getStaticParam(&mAddLength_s, "AddLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mRandRange_s, "RandRange");
    getStaticParam(&mRandRate_s, "RandRate");
}

}  // namespace uking::ai
