#include "Game/AI/AI/aiLynelRecognizeTarget.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include "KingSystem/System/Timer.h"
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
    _110.mValue = *mForceBattleStartTime_s;
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

// 0x7100496ee4 (CSV placeholder): whether the threat score passes.
bool LynelRecognizeTarget::sub_7100496EE4() {
    if (!isCurrentChild("観察") && !isCurrentChild("警戒")) {
        if (!isCurrentChild("帰還"))
            return false;
    } else if (_100.mValue >= (f32)*mTiredTime_s) {
        // Reached the tired threshold: skip the 帰還 check below.
    } else if (!isCurrentChild("帰還")) {
        return false;
    }
// NON_MATCHING: the original keeps a dead w21 flag (!isCurrentChild(観察)) with a duplicated
// 帰還 test diamond (both arms do the same thing); ours folds it. Ours also lays out the stack
// strings/request differently (NSDMI zero grouping, home slot) and the request leaves _20/_24
// uninitialised where the header NSDMIs zero them (same family as DistanceLostCheck::enter_).
// All calls, strings, float shapes, cond codes and values match.
    if (_f0 > 0)
        return false;
    auto* actor = mActor;
    const sead::Vector3f& target = sub_71005D9330(actor);
    sead::Vector3f home;
    actor->getHomePos(&home);
    f32 range = 5.0f;
    if (auto* awareness = actor->getAwareness()) {
        range = 0.0f;
        if (auto* sensor = awareness->_260[0]) {
            Unk_71023e26d8 request;
            sensor->m4(&request);
            range = request._20;
        }
    }
    const f32 dx = home.x - target.x;
    const f32 dz = home.z - target.z;
    if (sead::Mathf::sqrt(dx * dx + dz * dz) > range)
        return (*mLynelAIFlags_a & 0x10) == 0;
    return false;
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
    _100.mValue = 0;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("気づき", &pack);
}

void LynelRecognizeTarget::changeToAlert() {
    const f32 time = *mForceBattleStartTime_s;
    _100.mValue = 0;
    _110.mValue = time;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("警戒", &pack);
}

void LynelRecognizeTarget::changeToObserve() {
    const f32 time = *mForceBattleStartTime_s;
    _100.mValue = 0;
    _110.mValue = time;

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

void LynelRecognizeTarget::calc_() {
    if (auto* dmg = mActor->getDamageMgr()) {
// NON_MATCHING: everything matches except register allocation and the 0x60-vs-0x70 frame (ours
// keeps two more values in callee-saved registers across the isCurrentChild calls; the string
// address-points are recomputed per call instead of hoisted). All calls, branches, strings,
// float shapes, cond codes and values match.
        // s32 (not > 0): cmp-#1+b.lt (LastBossFlyWait precedent); bare && would ccmp-fold and
        // named locals would grow the frame, so nested ifs with no locals.
        if (s32(dmg->getDamage()) >= 1) {
            if (dmg->getField54() >= 2)
                _f4 = true;
        }
    }
    if (_f8 > 0.0f) {
        ksys::Timer::update(&_f8, -1.0f);
        if (_f8 <= 0.0f)
            mActor->m93(0, 0.0f);
    }
    auto* child = getCurrentChild();
    const bool changeable = child->isChangeable();
    if (!isCurrentChild("戦闘")) {
        sub_71004963F8(!changeable);
        *mLynelAreaAlarmPoint_a = 0;
    }
    if (isCurrentChild("帰還"))
        sub_71005DB3EC(mActor);
    else
        sub_71005DB068(mActor, sub_71005D960C(mActor));
    if (isCurrentChild("観察") || isCurrentChild("警戒")) {
        if (_f0 > 0)
            _100.mValue = 0;
        else
            _100.sub_7100D3BC4C(1.0f);
        _110.sub_7100D3BC4C(-1.0f);
    }
    if (child->isFinished() || child->isFailed()) {
        if (child->isFailed()) {
            setFailed();
            return;
        }
        if (isCurrentChild("気づき")) {
            if ((f32)_f0 >= (f32)*mObserveEndPoint_s) {
                changeToStartBattle();
                return;
            }
            if ((f32)_f0 >= (f32)*mAttensionStartPoint_s) {
                changeToAlert();
                return;
            }
            changeToObserve();
            return;
        }
        if (isCurrentChild("戦闘開始")) {
            sub_7100496564();
            return;
        }
        if (isCurrentChild("強制戦闘開始")) {
            changeToStartBattle();
            return;
        }
        setFinished();
        return;
    }
    if (changeable) {
        if (isCurrentChild("観察")) {
            if ((f32)_f0 >= (f32)*mObserveEndPoint_s) {
                changeToStartBattle();
                return;
            }
            if ((f32)_f0 < (f32)*mAttensionStartPoint_s) {
                if (sub_7100496EE4()) {
                    changeToReturn();
                    return;
                }
                if (_110.mValue < 0.0f)
                    changeToForceStartBattle();
            } else {
                changeToAlert();
                return;
            }
        } else if (isCurrentChild("警戒")) {
            if ((f32)_f0 >= (f32)*mObserveEndPoint_s) {
                changeToStartBattle();
                return;
            }
            if (sub_7100496EE4()) {
                changeToReturn();
                return;
            }
            if (_110.mValue < 0.0f)
                changeToForceStartBattle();
        } else if (isCurrentChild("帰還") && _f0 >= 1) {
            changeToStartBattle();
            return;
        }
    }
    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

}  // namespace uking::ai
