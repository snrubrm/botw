#include "Game/AI/AI/aiOctarockBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100D8C538.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

OctarockBattle::OctarockBattle(const InitArg& arg) : ShootingEnemyBattle(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
OctarockBattle::~OctarockBattle() {
    ;
}

bool OctarockBattle::init_(sead::Heap* heap) {
    if (!ShootingEnemyBattle::init_(heap))
        return false;
    _118 = 0;
    return true;
}

void OctarockBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootingEnemyBattle::enter_(params);
    _b0 = _118;
    if (*mIsFirstAttackIntervalZero_s && !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) &&
        !testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        sub_7100381E58(0);
    }
}

// NON_MATCHING: the original reads _b4 before the sub_71005D93CC call (same as ShootingEnemyBattle::calc_)
void OctarockBattle::calc_() {
    auto* child = getCurrentChild();
    if (isCurrentChild("吐き出し攻撃") || isCurrentChild("画面外吐き出し攻撃")) {
        if (!_b4 && !m44())
            _b4 = true;

        if (child->isFinished() || child->isFailed()) {
            if (child->isFailed()) {
                setFailed();
            } else {
                sub_7100381ED4();
                m37();
            }
        } else {
            const sead::Vector3f& target = sub_71005D93CC(mActor);
            if (_b4)
                child->setDynamicParam(target, "TargetPos");
            else
                child->setDynamicParam(target + _b8, "TargetPos");
        }
    } else {
        ShootingEnemyBattle::calc_();
    }
    child->setDynamicParam(sub_71005D9548(mActor), "TargetVel");
}

void OctarockBattle::leave_() {
    _118 = _b0;
    ShootingEnemyBattle::leave_();
}

void OctarockBattle::loadParams_() {
    ShootingEnemyBattle::loadParams_();
    getStaticParam(&mActorDisplayRadius_s, "ActorDisplayRadius");
    getStaticParam(&mAttackDistMin_s, "AttackDistMin");
    getStaticParam(&mIsAttackOnlyOutScreen_s, "IsAttackOnlyOutScreen");
    getStaticParam(&mIsHideMode_s, "IsHideMode");
    getStaticParam(&mIsFirstAttackIntervalZero_s, "IsFirstAttackIntervalZero");
    getStaticParam(&mIsLostAttack_s, "IsLostAttack");
    getStaticParam(&mShootActorKey_s, "ShootActorKey");
    getStaticParam(&mVacuumPartsKey_s, "VacuumPartsKey");
}

// NON_MATCHING: stack layout only (the original puts the InlineParamPack at the lowest address, the position and the
// SafeString / accessor slot above it; ours has the SafeString slot lowest)
void OctarockBattle::m38() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!_b4 && _b0 < *mOutScreenAttackNum_s) {
        sub_7100569DC8(&_b8);
        const sead::Vector3f position = sub_71005D93CC(mActor) + _b8;
        const sead::Vector3f& velocity = sub_71005D9548(mActor);
        ksys::act::ai::InlineParamPack params;
        params.addVec3(position, "TargetPos", -1);
        params.addVec3(velocity, "TargetVel", -1);
        const char* next = nullptr;
        if (enemy->getActorPartsActor(mVacuumPartsKey_s).hasProc()) {
            next = "画面外吐き出し攻撃";
        } else {
            auto& shoot_actor = enemy->getActorPartsActor(mShootActorKey_s);
            if (shoot_actor.hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&shoot_actor, &accessor);
                if (accessor.isStateSleep())
                    next = "画面外攻撃";
            }
        }
        if (next) {
            changeChild(next, &params);
            ++_b0;
        } else if (!isCurrentChild("戦闘準備")) {
            m37();
        }
        return;
    }

    const sead::Vector3f& position = sub_71005D93CC(mActor);
    const sead::Vector3f& velocity = sub_71005D9548(mActor);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(position, "TargetPos", -1);
    params.addVec3(velocity, "TargetVel", -1);
    const char* next = nullptr;
    if (enemy->getActorPartsActor(mVacuumPartsKey_s).hasProc()) {
        next = "吐き出し攻撃";
    } else {
        auto& shoot_actor = enemy->getActorPartsActor(mShootActorKey_s);
        if (shoot_actor.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&shoot_actor, &accessor);
            if (accessor.isStateSleep())
                next = "戦闘攻撃";
        }
    }
    if (next)
        changeChild(next, &params);
    else if (!isCurrentChild("戦闘準備"))
        m37();
}

bool OctarockBattle::m39() {
    auto* actor = mActor;
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    if (!enemy->getActorPartsActor(mVacuumPartsKey_s).hasProc()) {
        auto& shoot_actor = enemy->getActorPartsActor(mShootActorKey_s);
        if (!shoot_actor.hasProc())
            return false;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&shoot_actor, &accessor);
        if (!accessor.isStateSleep())
            return false;
    }

    if (!mActor->getConnectedCalcChild())
        return false;

    if (enemy->_c48._7c != 2 && enemy->_c48._7c != 5 && !*mIsLostAttack_s)
        return false;

    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    if ((position - sub_71005D9330(mActor)).squaredLength() >=
        *mAttackDistMin_s * *mAttackDistMin_s) {
        if (!*mIsAttackOnlyOutScreen_s || !visibilityCheckMaybe(position, *mActorDisplayRadius_s)) {
            if (m40())
                return sub_7100382558();
        }
    }
    return false;
}

bool OctarockBattle::m44() {
    if (*mIsHideMode_s)
        return true;
    return ShootingEnemyBattle::m44();
}

}  // namespace uking::ai
