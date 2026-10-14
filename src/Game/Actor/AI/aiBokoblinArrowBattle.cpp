#include "Game/Actor/AI/aiBokoblinArrowBattle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_71007377D4.h"

namespace uking::ai {

BokoblinArrowBattle::BokoblinArrowBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}


void BokoblinArrowBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mParams.mIsUpdateNoticeState_s) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    }
    _114 = 0;
    const s32 min_num = *mParams.mBlindlyAttackMinNum_s;
    const s32 max_num = *mParams.mBlindlyAttackMaxNum_s;
    _118 = sead::GlobalRandom::instance()->getS32Range(min_num, max_num + 1);
    _11c = *mParams.mTargetPos_d;
    _11c.y += sub_71005D960C(mActor).y - sub_71005D9330(mActor).y;
    changeToWait();
}

// NON_MATCHING: load/scheduling order only; the original loads *mParams.mHoldIntervalRand_s and the selected
// hold interval before calling getF32 (the float math, timers and pack match)
void BokoblinArrowBattle::changeToWait() {
    sub_71005DA114(mActor, &_c8);
    const s32* hold_interval = _114 == _118 - 1 ? mParams.mHoldIntervalLast_s : mParams.mHoldInterval_s;
    _f0.reset(s32(*hold_interval +
                  *mParams.mHoldIntervalRand_s * sead::GlobalRandom::instance()->getF32() * -0.5f) +
              *mParams.mHoldIntervalRand_s);
    _108.reset(*mParams.mLeaveWaitTime_s);

    const sead::Vector3f target_pos = *mParams.mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

void BokoblinArrowBattle::changeToReadyBow() {
    sub_71005DA114(mActor, &_c8);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_11c, "TargetPos", -1);
    changeChild("弓構え", &pack);
}

void BokoblinArrowBattle::changeToWithdraw() {
    setDamageCallbackTiming(mActor, 4, &_c8);
    _fc.reset(*mParams.mLeaveTime_s);

    const sead::Vector3f target_pos = *mParams.mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("離脱", &pack);
}

bool BokoblinArrowBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

// NON_MATCHING: load scheduling of the target / actor positions in the distance tests (same operations).
void BokoblinArrowBattle::calc_() {
    // Whether the target is outside the shooting distance or height band.
    const auto isOutOfShootRange = [this] {
        const sead::Vector3f target = *mParams.mTargetPos_d;
        const sead::Matrix34f& mtx = mActor->getMtx();
        const f32 dist = sead::Vector3f(target.x - mtx(0, 3), 0.0f, target.z - mtx(2, 3)).length();
        const f32 height = target.y - mtx(1, 3);
        return dist >= *mParams.mBaseDist_s +
                           sub_71007320F0(mActor, *mParams.mWeaponIdx_s) *
                               *mParams.mShootDistRatio_s +
                           *mParams.mOutDist_s ||
               height <= *mParams.mOutDistVMin_s || height >= *mParams.mOutDistVMax_s;
    };
    // Updates the aim point (_11c) while the target is visible and passes it to the child.
    const auto updateAimTarget = [this] {
        if (sub_710072E1B4(mActor, false) || sub_71005D9744(mActor) == 3) {
            _11c = *mParams.mTargetPos_d;
            _11c.y += sub_71005D960C(mActor).y - sub_71005D9330(mActor).y;
        }
        getCurrentChild()->setDynamicParam(_11c, "TargetPos");
    };

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("離脱")) {
            if (getCurrentChild()->isFinished())
                changeToWait();
            else
                changeToReadyBow();
            return;
        }
        if (isCurrentChild("弓構え")) {
            if (*mParams.mIsEndAfterAttack_s) {
                if (getCurrentChild()->isFinished())
                    setFinished();
                else
                    setFailed();
            }
            if (sub_710072E1B4(mActor, false) || sub_71005D9744(mActor) == 3) {
                _114 = 0;
                changeToWait();
                return;
            }
            if (++_114 < _118) {
                changeToWait();
                return;
            }
            setFailed();
            changeToWait();
            return;
        }
    }

    if (isCurrentChild("待機")) {
        if (isOutOfShootRange()) {
            setFailed();
            changeToWait();
            return;
        }
        updateAimTarget();
        if ((*mParams.mTargetPos_d - mActor->getMtx().getTranslation()).length() <=
            *mParams.mLeaveStartDist_s)
            _108.update();
        else
            _108 = ksys::Timer(*mParams.mLeaveWaitTime_s, *mParams.mLeaveWaitTime_s);
        _f0.update();
        if (_f0.value <= sead::Mathf::epsilon()) {
            _f0 = ksys::Timer(0, 0);
            if ((*mParams.mTargetPos_d - mActor->getMtx().getTranslation()).length() >
                *mParams.mLeaveStartDist_s) {
                changeToReadyBow();
                return;
            }
        }
        if (_108.value > sead::Mathf::epsilon())
            return;
        changeToWithdraw();
    } else if (isCurrentChild("離脱")) {
        getCurrentChild()->setDynamicParam(*mParams.mTargetPos_d, "TargetPos");
        _fc.update();
        if (_fc.value <= sead::Mathf::epsilon() ||
            sead::Vector2f(mParams.mTargetPos_d->x - mActor->getMtx()(0, 3),
                           mParams.mTargetPos_d->z - mActor->getMtx()(2, 3))
                    .length() >= *mParams.mLeaveEndDist_s) {
            changeToWait();
        }
    } else if (isCurrentChild("弓構え")) {
        if (getCurrentChild()->isChangeable() && isOutOfShootRange()) {
            setFailed();
            changeToWait();
            return;
        }
        updateAimTarget();
    }
}

void BokoblinArrowBattle::leave_() {
    sub_71005DA114(mActor, &_c8);
}

void BokoblinArrowBattle::loadParams_() {
    getStaticParam(&mParams.mHoldInterval_s, "HoldInterval");
    getStaticParam(&mParams.mHoldIntervalLast_s, "HoldIntervalLast");
    getStaticParam(&mParams.mHoldIntervalRand_s, "HoldIntervalRand");
    getStaticParam(&mParams.mLeaveStartDist_s, "LeaveStartDist");
    getStaticParam(&mParams.mLeaveEndDist_s, "LeaveEndDist");
    getStaticParam(&mParams.mLeaveWaitTime_s, "LeaveWaitTime");
    getStaticParam(&mParams.mLeaveTime_s, "LeaveTime");
    getStaticParam(&mParams.mBaseDist_s, "BaseDist");
    getStaticParam(&mParams.mOutDist_s, "OutDist");
    getStaticParam(&mParams.mOutDistVMin_s, "OutDistVMin");
    getStaticParam(&mParams.mOutDistVMax_s, "OutDistVMax");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mLeaveTime_s, "LeaveTime");
    getStaticParam(&mParams.mBlindlyAttackMinNum_s, "BlindlyAttackMinNum");
    getStaticParam(&mParams.mBlindlyAttackMaxNum_s, "BlindlyAttackMaxNum");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mShootDistRatio_s, "ShootDistRatio");
    getStaticParam(&mParams.mIsEndAfterAttack_s, "IsEndAfterAttack");
    getStaticParam(&mParams.mIsUpdateNoticeState_s, "IsUpdateNoticeState");
}

}  // namespace uking::ai
