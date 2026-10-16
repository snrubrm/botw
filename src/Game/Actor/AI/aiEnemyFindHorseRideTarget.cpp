#include "Game/Actor/AI/aiEnemyFindHorseRideTarget.h"
#include <random/seadGlobalRandom.h>
#include <limits>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

EnemyFindHorseRideTarget::EnemyFindHorseRideTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyFindHorseRideTarget::~EnemyFindHorseRideTarget() = default;

bool EnemyFindHorseRideTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFindHorseRideTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _a4 = *mLostTimer_s;
    _a8 = _a4 + 5;
    _a0 = sead::GlobalRandom::instance()->getS32Range(_a4, _a8);
    _ac = sead::GlobalRandom::instance()->getS32Range(*mChaseTime_s, *mChaseTime_s + 5);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("追跡", &pack);
}

// NON_MATCHING: scheduling / register allocation (timer address kept in a register, argument load order)
void EnemyFindHorseRideTarget::calc_() {
    sub_71005DB248(mActor);
    ksys::Timer::update(&_ac, -1.0f);
    if (_b4 & 2) {
        if (_b0 > 0.0f)
            ksys::Timer::update(&_b0, -1.0f);
        else
            _b4 &= ~3;
    }

    auto* child = getCurrentChild();
    if (sub_7100730BB8(mActor, *mLostRange_s, *mLostVMin_s, *mLostVMax_s)) {
        ksys::Timer::update(&_a0, -1.0f);
    } else {
        _a0 = sead::GlobalRandom::instance()->getS32Range(_a4, _a8);
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
    }

    const auto changeTo = [this](const char* name) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild(name, &pack);
    };
    const auto canSurpriseAttack = [this] {
        return inlineIsTargetInReach(sub_71005D9330(mActor), *mSurpriseAttackRange_s, *mAttackVMin_s,
                                     *mAttackVMax_s, mActor->getMtx(), sead::Mathf::pi(),
                                     sead::Mathf::maxNumber(), 0.8f);
    };
    // Tries the surprise attack; returns whether it started.
    const auto trySurpriseAttack = [&] {
        if (sead::GlobalRandom::instance()->getU32(100) < u32(*mSurpriseAttackPer_s) &&
            act::DamageInfoMgr::instance()->get4f8().sub_7100671A40(
                mActor, s32(sead::GlobalRandom::instance()->getU32(24)) + 120)) {
            changeTo("不意討ち");
            return true;
        }
        _b4 |= 1;
        return false;
    };
    const auto isTargetClose = [this] {
        const sead::Vector3f& velocity = sub_71005D9548(mActor);
        if (sead::Mathf::sqrt(velocity.x * velocity.x + velocity.z * velocity.z) < *mAttackTargetSpeed_s) {
            const auto& target = sub_71005D9330(mActor);
            const f32 dx = target.x - mActor->getMtx()(0, 3);
            const f32 dz = target.z - mActor->getMtx()(2, 3);
            return sead::Mathf::sqrt(dx * dx + dz * dz) < *mReChaseDist_s + sub_71007320F0(mActor, *mWeaponIdx_s);
        }
        return false;
    };

    if (child->isFinished() || child->isFailed()) {
        if (_a0 <= 0.0f) {
            setFailed();
            return;
        }
        if (isCurrentChild("追跡諦め")) {
            if (sub_710038D018())
                enemyFindHorseRideStuff();
            else
                setFailed();
        } else if (isCurrentChild("戦闘")) {
            changeTo("追跡");
        } else if (sub_710038D018()) {
            enemyFindHorseRideStuff();
        } else {
            changeTo("追跡諦め");
        }
        return;
    }

    if (!child->isChangeable())
        return;

    if (_a0 <= 0.0f) {
        setFailed();
        return;
    }

    if (isCurrentChild("追跡")) {
        if (sub_710038D018()) {
            enemyFindHorseRideStuff();
            return;
        }
        if (canSurpriseAttack()) {
            if (!(_b4 & 1) && canSurpriseAttack())
                trySurpriseAttack();
            return;
        }
        if (!isTargetClose() && _ac < 0.0f)
            changeTo("追跡諦め");
    } else if (isCurrentChild("追跡諦め")) {
        if (sub_710038D018()) {
            enemyFindHorseRideStuff();
            return;
        }
        if (canSurpriseAttack() && !(_b4 & 1) && canSurpriseAttack() && trySurpriseAttack())
            return;
        if (isTargetClose()) {
            _ac = sead::GlobalRandom::instance()->getS32Range(*mChaseTime_s, *mChaseTime_s + 5);
            changeTo("追跡");
        }
    }
}

bool EnemyFindHorseRideTarget::sub_710038D018() {
    const sead::Vector3f& velocity = sub_71005D9548(mActor);
    if (sead::Mathf::sqrt(velocity.x * velocity.x + velocity.z * velocity.z) < *mAttackTargetSpeed_s) {
        const auto& target = sub_71005D9330(mActor);
        auto* actor = mActor;
        const f32 max_dist = *mAttackRange_s + sub_71007320F0(actor, *mWeaponIdx_s);
        return inlineIsTargetInReach(target, max_dist, *mAttackVMin_s, *mAttackVMax_s,
                                     actor->getMtx(), sead::Mathf::pi(), sead::Mathf::maxNumber(),
                                     0.8f);
    }
    return false;
}

void EnemyFindHorseRideTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyFindHorseRideTarget::loadParams_() {
    getStaticParam(&mSurpriseAttackPer_s, "SurpriseAttackPer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mChaseTime_s, "ChaseTime");
    getStaticParam(&mSurpriseAttackRange_s, "SurpriseAttackRange");
    getStaticParam(&mAttackRange_s, "AttackRange");
    getStaticParam(&mAttackVMin_s, "AttackVMin");
    getStaticParam(&mAttackVMax_s, "AttackVMax");
    getStaticParam(&mLostVMin_s, "LostVMin");
    getStaticParam(&mLostVMax_s, "LostVMax");
    getStaticParam(&mLostRange_s, "LostRange");
    getStaticParam(&mAttackTargetSpeed_s, "AttackTargetSpeed");
    getStaticParam(&mReChaseDist_s, "ReChaseDist");
}

}  // namespace uking::ai
