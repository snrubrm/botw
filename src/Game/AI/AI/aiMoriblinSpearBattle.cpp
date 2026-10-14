#include "Game/AI/AI/aiMoriblinSpearBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

MoriblinSpearBattle::MoriblinSpearBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoriblinSpearBattle::~MoriblinSpearBattle() = default;

// NON_MATCHING: clang inlines changeToShortRange/sub_71004AA888 here; the original tail-calls them
void MoriblinSpearBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        sead::Vector3f diff = sub_71005D9330(mActor);
        diff -= mActor->getMtx().getTranslation();
        diff.y = 0;
        if (diff.length() <= sub_71007320F0(mActor, *mWeaponIdx_s) + *mNearDist_s) {
            changeToShortRange();
            return;
        }
    }
    sub_71004AA888();
}

// NON_MATCHING: as in enter_, clang inlines sub_71004AA888 / changeToWait here while the original calls them; the
// direction test registers differ.
void MoriblinSpearBattle::calc_() {
    // The XZ distance to the target.
    const auto calcTargetDist = [this] {
        sead::Vector3f diff = sub_71005D9330(mActor);
        diff -= mActor->getMtx().getTranslation();
        diff.y = 0;
        return diff.length();
    };

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("中距離") || isCurrentChild("近距離") || isCurrentChild("強制小攻撃")) {
            sub_71004AA888();
            return;
        }
        if (isCurrentChild("待機") && getCurrentChild()->isFailed()) {
            setFailed();
            return;
        }
    }

    if (isCurrentChild("待機")) {
        if (calcTargetDist() >= sub_71007320F0(mActor, *mWeaponIdx_s) + *mBaseDist_s + *mOutDist_s)
            _80.update();
        else
            _80 = ksys::Timer(10, 10);
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
        if (!getCurrentChild()->isChangeable())
            return;
        if (sub_71004AAEAC()) {
            changeToShortRange();
            return;
        }
        const sead::Vector3f& target = sub_71005D9330(mActor);
        const sead::Vector2f diff(target.x - mActor->getMtx()(0, 3),
                                  target.z - mActor->getMtx()(2, 3));
        if (diff.length() <= *mForceAttackDist_s) {
            sead::Vector3f dir = *mTargetPos_d - mActor->getMtx().getTranslation();
            dir.y = 0;
            const sead::Vector3f forward = mActor->getMtx().getBase(2);
            dir.normalize();
            if (forward.dot(dir) >= sead::Mathf::cos(*mAttackStartRotate_s)) {
                changeToForcedSmallAttack();
                return;
            }
        }
        if (sub_71004AB0E0()) {
            changeToMidRange();
            return;
        }
    } else if (isCurrentChild("中距離")) {
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
        return;
    } else if (isCurrentChild("近距離")) {
        if (calcTargetDist() >= sub_71007320F0(mActor, *mWeaponIdx_s) + *mBaseDist_s + *mOutDist_s)
            _80.update();
        else
            _80 = ksys::Timer(10, 10);
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
        if (!getCurrentChild()->isChangeable())
            return;
        if (calcTargetDist() > sub_71007320F0(mActor, *mWeaponIdx_s) + *mBaseDist_s) {
            changeToWait();
            return;
        }
    } else {
        return;
    }

    if (_80.value > sead::Mathf::epsilon())
        return;
    setFailed();
}

bool MoriblinSpearBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

// NON_MATCHING: load order / register numbering of the second (direction) part: the original loads the actor
// pointer before the TargetPos pointer, interleaves the x / z loads and loads the forward axis after the sqrt.
bool MoriblinSpearBattle::sub_71004AAEAC() {
    sead::Vector3f diff = sub_71005D9330(mActor);
    diff -= mActor->getMtx().getTranslation();
    diff.y = 0;
    if (!(diff.length() <= sub_71007320F0(mActor, *mWeaponIdx_s) + *mNearDist_s))
        return false;
    sead::Vector3f dir = *mTargetPos_d - mActor->getMtx().getTranslation();
    dir.y = 0;
    const sead::Vector3f forward = mActor->getMtx().getBase(2);
    dir.normalize();
    return forward.dot(dir) >= sead::Mathf::cos(*mAttackStartRotate_s);
}

void MoriblinSpearBattle::leave_() {
    sub_71005DA114(mActor, &_90);
}

void MoriblinSpearBattle::loadParams_() {
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mAttackStartRotate_s, "AttackStartRotate");
    getStaticParam(&mForceAttackDist_s, "ForceAttackDist");
}

void MoriblinSpearBattle::changeToShortRange() {
    setDamageCallbackTiming(mActor, 4, &_90);
    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target_pos, "TargetPos", -1);
    changeChild("近距離", &params);
}

void MoriblinSpearBattle::sub_71004AA888() {
    sead::Vector3f diff = sub_71005D9330(mActor);
    diff -= mActor->getMtx().getTranslation();
    diff.y = 0;
    if (diff.length() >= sub_71007320F0(mActor, *mWeaponIdx_s) + (*mBaseDist_s + *mOutDist_s))
        setFailed();
    changeToWait();
}

void MoriblinSpearBattle::changeToWait() {
    sub_71005DA114(mActor, &_90);
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->startAttackInterval(*mAttackIntervalIntensity_s);
    _80 = ksys::Timer(10, 10);

    sead::Vector3f pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

void MoriblinSpearBattle::changeToForcedSmallAttack() {
    setDamageCallbackTiming(mActor, 4, &_90);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("強制小攻撃", &pack);
}

void MoriblinSpearBattle::changeToMidRange() {
    setDamageCallbackTiming(mActor, 4, &_90);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("中距離", &pack);
}

}  // namespace uking::ai
