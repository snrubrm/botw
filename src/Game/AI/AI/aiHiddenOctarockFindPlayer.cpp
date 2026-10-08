#include "Game/AI/AI/aiHiddenOctarockFindPlayer.h"
#include <math/seadVector.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_7100D8C538.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include "KingSystem/System/Timer.h"

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

// NON_MATCHING: all dispatch, visibility, awareness-request, distance, range-timer and revival
// logic matches; remaining diffs are backend scheduling/allocation only: vtable loads hoisted
// above branch tests, request _8-zero store scheduled before the vtable GOT load, &_68 not
// hoisted above the dist branch (in-arm adds), _6c rematerialized after getU32 instead of kept
// in w21 (subs+b.eq vs sub+cbz, w-reg coloring follows)
void HiddenOctarockFindPlayer::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        if (child->isChangeable()) {
            if (_68 <= 0.0f && !isCurrentChild("近づき")) {
                setFailed();
            } else {
                if (isCurrentChild("戦闘")) {
                    if (sub_7100430DF0())
                        changeToApproaching();
                } else {
                    // The result is discarded, but the call really is in the target asm.
                    isCurrentChild("近づき");
                }
            }
        }
    } else if (child->isFailed()) {
        setFailed();
    } else {
        if (isCurrentChild("近づき")) {
            sead::Vector3f pos;
            mActor->getMtx().getTranslation(pos);
            if (visibilityCheckMaybe(pos, *mActorRadius_s))
                changeToNotice();
            else {
                mActor->m93(0, 0.0f);
                changeChild("隠れる", nullptr);
            }
        } else if (isCurrentChild("気づき")) {
            mActor->m93(0, 0.0f);
            changeChild("隠れる", nullptr);
        } else {
            if (sub_7100430DF0())
                changeToApproaching();
            else
                changeChild("戦闘", nullptr);
        }
    }

    const f32 x = mActor->getMtx()(0, 3);
    const f32 z = mActor->getMtx()(2, 3);
    f32 value = 0.0f;
    if (auto* awareness = mActor->getAwareness()) {
        Unk_71023e2780 request;
        if (auto* sensor = awareness->_260[3])
            value = sensor->m4(&request) ? request._8 : 0.0f;
    }
    const sead::Vector3f& target = sub_71005D9330(mActor);
    const sead::Vector2f diff(target.x - x, target.z - z);
    const f32 dist = diff.length();
    // Ordered-compare branch-away form (NaN takes the randomize path): b.le, not b.ls.
    if (!(dist > value + *mLostDistOffset_s)) {
        const u32 range = _70 - _6c;
        if (range != 0) {
            const u32 r = sead::GlobalRandom::instance()->getU32();
            _68 = _6c + s32((u64(r) * range) >> 32);
        }
    } else {
        ksys::Timer::update(&_68, -1.0f);
    }
}

}  // namespace uking::ai
