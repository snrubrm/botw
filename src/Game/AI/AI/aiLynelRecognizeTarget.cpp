#include "Game/AI/AI/aiLynelRecognizeTarget.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LynelRecognizeTarget::LynelRecognizeTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRecognizeTarget::~LynelRecognizeTarget() = default;

bool LynelRecognizeTarget::sub_7100497BE8(ksys::act::acc::PlayerOrEnemy* actor) {
    const s32 num_slots = actor->getNumWeaponSlots();
    for (s32 i = 0; i < num_slots; ++i) {
        ksys::act::ActorConstDataAccess weapon;
        actor->getWeapon(&weapon, i);
        if (weapon.hasProc() && sub_71002F0258(weapon) != 4 && !actor->sub_7100009AA8(i))
            return true;
    }
    return false;
}

bool LynelRecognizeTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelRecognizeTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _118 = *mForceBattleStartTime_s;
// NON_MATCHING: the original keeps two copies of the 0x518 load + bit-25 test (one reached from
// the _f4-unset paths, one from the _f4-set paths); ours merges them. Ours also picks different
// registers for the `*mLynelAIFlags_a & 1` result (w9 vs w8), reloads mActor for the m93 call
// instead of reusing it, and loads the 0x38 pointer before _f0 in the second compare. All calls,
// branches, values and the float-compare shapes match.
    if (!_f4) {
        if (actor->getRootAi()->testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0)) {
            _f4 = true;
        } else {
            _f4 = *mLynelAIFlags_a & 1;
            if (!_f4 && sead::IsDerivedFrom<act::Enemy>(actor)) {
                auto* enemy = static_cast<act::Enemy*>(actor);
                _f4 = enemy->_e08._0 == enemy->_c48._8;
            }
        }
    }
    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000)) {
        sub_71004963F8(1);
        if ((f32)_f0 >= (f32)*mObserveEndPoint_s)
            sub_7100496564();
    } else if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_1000000)) {
        sub_71004963F8(1);
        if ((f32)_f0 >= (f32)*mAttensionStartPoint_s)
            changeToAlert();
        else
            changeToObserve();
    } else {
        _f0 = 0;
        actor->m93(4, 1.0f);
        _f8 = 20.0f;
        changeToNotice();
    }
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_1000000);
}

// 0x7100496564 (CSV placeholder): set flag 0x2000000, change to 戦闘 with the target position,
// and mark the enemy's _e84 bit 1.
void LynelRecognizeTarget::sub_7100496564() {
    auto* actor = mActor;
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(actor), "TargetPos", -1);
    changeChild("戦闘", &pack);
    auto* enemy = static_cast<act::Enemy*>(mActor);
    if (sead::IsDerivedFrom<act::Enemy>(enemy))
        enemy->_e84.setBit(1);
}

void LynelRecognizeTarget::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    mActor->m93(0, 0.0f);
}

void LynelRecognizeTarget::loadParams_() {
    getStaticParam(&mAttensionStartPoint_s, "AttensionStartPoint");
    getStaticParam(&mObserveEndPoint_s, "ObserveEndPoint");
    getStaticParam(&mDrawnWeaponPoint_s, "DrawnWeaponPoint");
    getStaticParam(&mWeaponAimPoint_s, "WeaponAimPoint");
    getStaticParam(&mAttackPoint_s, "AttackPoint");
    getStaticParam(&mDashPoint_s, "DashPoint");
    getStaticParam(&mAppPoint_s, "AppPoint");
    getStaticParam(&mHorseRidePoint_s, "HorseRidePoint");
    getStaticParam(&mDamagePoint_s, "DamagePoint");
    getStaticParam(&mTrickedMaskPoint_s, "TrickedMaskPoint");
    getStaticParam(&mBombPoint_s, "BombPoint");
    getStaticParam(&mAimPoint_s, "AimPoint");
    getStaticParam(&mNearDistPoint_s, "NearDistPoint");
    getStaticParam(&mMiddleDistPoint_s, "MiddleDistPoint");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mTiredPoint_s, "TiredPoint");
    getStaticParam(&mForceBattleStartTime_s, "ForceBattleStartTime");
    getStaticParam(&mNearDistance_s, "NearDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mAimAngle_s, "AimAngle");
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
    getAITreeVariable(&mLynelAreaAlarmPoint_a, "LynelAreaAlarmPoint");
}

void LynelRecognizeTarget::changeToReturn() {
    sead::Vector3f pos;
    mActor->getHomePos(&pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("帰還", &pack);
}

void LynelRecognizeTarget::changeToNotice() {
    _108 = 0;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("気づき", &pack);
}

void LynelRecognizeTarget::changeToAlert() {
    const f32 time = *mForceBattleStartTime_s;
    _108 = 0;
    _118 = time;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("警戒", &pack);
}

void LynelRecognizeTarget::changeToObserve() {
    const f32 time = *mForceBattleStartTime_s;
    _108 = 0;
    _118 = time;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("観察", &pack);
}

void LynelRecognizeTarget::changeToStartBattle() {
    auto* actor = mActor;
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(actor), "TargetPos", -1);
    changeChild("戦闘開始", &pack);

    actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor))
        static_cast<act::Enemy*>(actor)->_e84.setBit(1);
}

void LynelRecognizeTarget::changeToForceStartBattle() {
    auto* actor = mActor;
    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(actor), "TargetPos", -1);
    changeChild("強制戦闘開始", &pack);

    actor = mActor;
    if (sead::IsDerivedFrom<act::Enemy>(actor))
        static_cast<act::Enemy*>(actor)->_e84.setBit(1);
}

}  // namespace uking::ai
