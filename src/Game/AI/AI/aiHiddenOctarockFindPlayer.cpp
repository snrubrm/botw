#include "Game/AI/AI/aiHiddenOctarockFindPlayer.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HiddenOctarockFindPlayer::HiddenOctarockFindPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HiddenOctarockFindPlayer::~HiddenOctarockFindPlayer() = default;

bool HiddenOctarockFindPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HiddenOctarockFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HiddenOctarockFindPlayer::leave_() {
    mActor->m93(0, 0.0f);
}

void HiddenOctarockFindPlayer::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mActorRadius_s, "ActorRadius");
    getStaticParam(&mLostDistOffset_s, "LostDistOffset");
    getStaticParam(&mNoticeDelayTime_s, "NoticeDelayTime");
}

bool HiddenOctarockFindPlayer::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable() && !isCurrentChild("近づき");
}

void HiddenOctarockFindPlayer::sub_71004312D8() {
    mActor->m93(4, 0.0f);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("気づき", &pack);
}

void HiddenOctarockFindPlayer::sub_7100430EE0() {
    s32 value = _78;
    if (_7c != _78)
        value = sead::GlobalRandom::instance()->getS32Range(_78, _7c);
    _74 = value;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("近づき", &pack);
}

}  // namespace uking::ai
