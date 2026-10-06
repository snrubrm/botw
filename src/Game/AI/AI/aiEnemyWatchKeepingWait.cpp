#include "Game/AI/AI/aiEnemyWatchKeepingWait.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

EnemyWatchKeepingWait::EnemyWatchKeepingWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyWatchKeepingWait::~EnemyWatchKeepingWait() = default;

bool EnemyWatchKeepingWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: only the operand order of the last fmul of the angle product differs.
void EnemyWatchKeepingWait::sub_71003C5F34() {
    auto* actor = mActor;
    sead::Matrix34f home;
    actor->getHomeMtx(&home);
    sead::Vector3f dir;
    home.getBase(dir, 2);
    sead::Vector3f target;
    actor->getMtx().getTranslation(target);
    ++_7d;
    if (sead::Mathf::abs(f32(_7d)) >= 4.0f) {
        _7d = 0;
        _7c = -_7c;
    }
    const s32 turns = _7d;
    ksys::util::sub_71011EF010(
        &dir, f32(_7c) * sead::Mathf::deg2rad(*mRotAngle_m) * f32(turns > 2 ? 4 - turns : turns));
    target += dir * 3.0f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("回転", &pack);
}

// NON_MATCHING: Angle registers and the signed absolute-value sequence differ from the original.
void EnemyWatchKeepingWait::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _7e = false;
    sead::Matrix34f home;
    actor->getHomeMtx(&home);
    const sead::Vector3f front = actor->getMtx().getBase(2);
    const sead::Vector3f home_front = home.getBase(2);
    const s32 minimum = *mIdleCheckMin_s;
    const s32 maximum = *mIdleCheckMax_s;
    const s32 interval = sead::GlobalRandom::instance()->getS32Range(minimum, maximum);
    const s32 idle_percentage = *mIdlePer_s;
    _74 = false;
    _6c = interval;
    _70 = s32(f32(idle_percentage));
    _68 = f32(interval);
    const f32 angle = ksys::util::sub_71011EF0CC(
        std::atan2(front.x, front.z) - std::atan2(home_front.x, home_front.z));
    if (!(*mRotAngle_m <= 0.0f) && !(*mWaitTime_m <= 0.0f)) {
        const s8 turns = s8(angle / *mRotAngle_m);
        _7c = sead::MathCalcCommon<s8>::sign(turns);
        _7d = sead::MathCalcCommon<s8>::abs(turns);
        changeToWait();
    } else if (sead::Mathf::abs(angle) < sead::Mathf::deg2rad(3.0f)) {
        _7c = 1;
        _7d = 0;
        changeToWait();
    } else {
        sub_71003C5F34();
    }
}

// NON_MATCHING: The timer reload uses the member address instead of the retained pointer.
void EnemyWatchKeepingWait::calc_() {
    if (!_7e && isCurrentChild("待機")) {
        if (!_74 && _70 > 0) {
            ksys::Timer::update(&_68, -1.0f);
            if (_68 <= 0) {
                _74 = sead::GlobalRandom::instance()->getF32() * 100.0f < f32(_70);
                if (!_74)
                    _68 = f32(_70);
            }
        }
        if (_74) {
            _7e = true;
            _74 = false;
            _68 = f32(_6c);
        }
    }
    if (isCurrentChild("待機") && _78 > 0)
        ksys::Timer::update(&_78, -1.0f);
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("待機"))
            sub_71003C5F34();
        else
            changeToWait();
    } else if (child->isChangeable() && isCurrentChild("待機") && *mWaitTime_m > 0 &&
               sead::Mathf::abs(*mRotAngle_m) > 0) {
        ksys::Timer::update(&_38, -1.0f);
        if (_38 < 0) {
            sub_71003C5F34();
        } else if (_7e && _78 <= 0) {
            _7e = false;
            changeChild("サボり", nullptr);
        }
    }
}

void EnemyWatchKeepingWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyWatchKeepingWait::loadParams_() {
    getStaticParam(&mIdleCheckMin_s, "IdleCheckMin");
    getStaticParam(&mIdleCheckMax_s, "IdleCheckMax");
    getStaticParam(&mIdlePer_s, "IdlePer");
    getMapUnitParam(&mRotAngle_m, "RotAngle");
    getMapUnitParam(&mWaitTime_m, "WaitTime");
}

void EnemyWatchKeepingWait::changeToWait() {
    _38 = *mWaitTime_m;
    _78 = std::min(s32(*mWaitTime_m * 0.5f), 30);
    changeChild("待機", nullptr);
}

}  // namespace uking::ai
