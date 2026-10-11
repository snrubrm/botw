#include "Game/AI/AI/aiMoriblinUnarmedBattle.h"
#include <cmath>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

MoriblinUnarmedBattle::MoriblinUnarmedBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoriblinUnarmedBattle::~MoriblinUnarmedBattle() = default;

void MoriblinUnarmedBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    sub_71004AC4F8();
    _b8 = ksys::Timer(0, 0);
}

// NON_MATCHING: parameter stack slots, timer store grouping and member pointer retention differ.
void MoriblinUnarmedBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("攻撃") || isCurrentChild("追撃ち攻撃")) {
            sub_71004AC4F8();
            return;
        }
        if (getCurrentChild()->isFailed()) {
            setFailed();
            return;
        }
    }
    if (isCurrentChild("待機")) {
        if (!(_b8.value <= sead::Mathf::epsilon()))
            _b8.update();
        if (sub_71004ACA10()) {
            _b8.reset(*mPursuingAttackInterval_s);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("追撃ち攻撃", &pack);
            return;
        }
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        sead::Vector3f diff = sub_71005D9330(mActor) - pos;
        diff.y = 0.0f;
        const f32 dist = diff.length();
        const f32 range = sub_71007320F0(mActor, *mWeaponIdx_s) + (*mBaseDist_s + *mOutDist_s);
        if (!(dist >= range))
            _80.reset(10.0f);
        else
            _80.update();
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
        if (getCurrentChild()->isChangeable()) {
            if (sub_71004ACC4C())
                changeToAttack();
            else if (_80.value <= sead::Mathf::epsilon())
                setFailed();
        }
    } else if (isCurrentChild("攻撃")) {
        getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
}

// NON_MATCHING: normalized direction arithmetic and float register allocation differ.
bool MoriblinUnarmedBattle::sub_71004ACA10() {
    auto* actor = mActor;
    if (!actor)
        return false;
    const auto* level = actor->getParam()->getRes().mGParamList->getEnemyLevel();
    if (!level || !*level->mIsBackSwiftAttack || !(_b8.value <= sead::Mathf::epsilon()))
        return false;
    if (!sub_710072E1B4(actor, false))
        return false;
    if (!sub_710072DDB8(sub_71005D9330(mActor), mActor->getMtx(), *mAttackStartRotate_s))
        return false;
    const auto& target_mtx = sub_71005D96A8(actor);
    sead::Vector3f front(target_mtx.m[0][2], 0.0f, target_mtx.m[2][2]);
    front.normalize();
    sead::Vector3f direction = sub_71005D9330(actor) - actor->getMtx().getTranslation();
    direction.y = 0.0f;
    direction.negate();
    direction.normalize();
    if (front.dot(direction) > std::cos(*mPursuingAttackStartAng_s))
        return false;
    const sead::Vector3f target = sub_71005D9330(actor);
    auto* nav = actor->m45();
    const f32 tolerance = nav ? nav->_2a8 * nav->_2ac : 0.0f;
    return sub_710072F944(actor, target, nullptr, tolerance, 3.0f);
}

// NON_MATCHING: vector load order and float register allocation differ.
bool MoriblinUnarmedBattle::sub_71004ACC4C() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy || !(enemy->_e68.value <= sead::Mathf::epsilon()))
        return false;
    sead::Vector3f diff = sub_71005D9330(mActor) - mActor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 dist = diff.length();
    const f32 range = sub_71007320F0(mActor, *mWeaponIdx_s) + *mBaseDist_s + *mFarDist_s;
    if (!(dist <= range))
        return false;
    sead::Vector3f direction = *mTargetPos_d - mActor->getMtx().getTranslation();
    direction.y = 0.0f;
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    direction.normalize();
    if (!(front.dot(direction) >= std::cos(*mAttackStartRotate_s)))
        return false;
    if (!mActor || !sub_710072E1B4(mActor, false))
        return false;
    return dmg::DamageInfoMgr::instance()->get4f8().sub_7100671A40(
        mActor, 80 + sead::GlobalRandom::instance()->getU32(16));
}

void MoriblinUnarmedBattle::sub_71004AC4F8() {
    if (sub_7100736D98(mActor) || testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1)) {
        const auto* level = mActor->getParam()->getRes().mGParamList->getEnemyLevel();
        if (level && *level->mIsCounterAttack) {
            changeToAttack();
            return;
        }
    } else if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        enemy->startAttackInterval(*mAttackIntervalIntensity_s);
    }

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f diff = sub_71005D9330(mActor);
    diff -= pos;
    diff.y = 0;
    const f32 dist = diff.length();
    const f32 range = sub_71007320F0(mActor, *mWeaponIdx_s) + (*mBaseDist_s + *mOutDist_s);
    changeToWait();
    if (dist >= range)
        setFailed();
}

bool MoriblinUnarmedBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void MoriblinUnarmedBattle::leave_() {
    sub_71005DA114(mActor, &_90);
}

void MoriblinUnarmedBattle::loadParams_() {
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mAttackIntervalIntensity_s, "AttackIntervalIntensity");
    getStaticParam(&mAttackStartRotate_s, "AttackStartRotate");
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
}

void MoriblinUnarmedBattle::changeToAttack() {
    setDamageCallbackTiming(mActor, 4, &_90);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("攻撃", &pack);
}

void MoriblinUnarmedBattle::changeToWait() {
    sub_71005DA114(mActor, &_90);
    _80 = ksys::Timer(10.0f, 10.0f);

    const sead::Vector3f target_pos = *mTargetPos_d;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

}  // namespace uking::ai
