#include "Game/AI/AI/aiHiddenOctarockFindPlayer.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_7100D8C538.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HiddenOctarockFindPlayer::HiddenOctarockFindPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HiddenOctarockFindPlayer::~HiddenOctarockFindPlayer() = default;

bool HiddenOctarockFindPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HiddenOctarockFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    {
        const s32 a = *mLostTimer_s;
        const s32 b = static_cast<s32>(a * 1.1f);
        _6c = sead::Mathi::min(a, b);
        _70 = sead::Mathi::max(a, b);
        s32 value = _6c;
        if (_70 != _6c)
            value = sead::GlobalRandom::instance()->getS32Range(_6c, _70);
        _68 = value;
    }
    {
        const s32 a = static_cast<s32>(*mNoticeDelayTime_s);
        const s32 b = static_cast<s32>(*mNoticeDelayTime_s * 1.1f);
        _78 = sead::Mathi::min(a, b);
        _7c = sead::Mathi::max(a, b);
        s32 value = _78;
        if (_7c != _78)
            value = sead::GlobalRandom::instance()->getS32Range(_78, _7c);
        _74 = value;
    }
    if (sub_7100430DF0())
        changeToApproaching();
    else
        changeChild("戦闘", nullptr);
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

// NON_MATCHING: the original converts the weapon index int -> float -> int before the call
bool HiddenOctarockFindPlayer::sub_7100430DF0() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const f32 weapon_dist = sub_71007320F0(mActor, *mWeaponIdx_s);
    const f32 dist = (sub_71005D9330(mActor) - pos).length();
    if (dist >= weapon_dist + *mFarDist_s) {
        sead::Vector3f actor_pos;
        mActor->getMtx().getTranslation(actor_pos);
        return !visibilityCheckMaybe(actor_pos, *mActorRadius_s);
    }
    return false;
}

void HiddenOctarockFindPlayer::changeToNotice() {
    mActor->m93(4, 0.0f);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("気づき", &pack);
}

void HiddenOctarockFindPlayer::changeToApproaching() {
    s32 value = _78;
    if (_7c != _78)
        value = sead::GlobalRandom::instance()->getS32Range(_78, _7c);
    _74 = value;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("近づき", &pack);
}

}  // namespace uking::ai
