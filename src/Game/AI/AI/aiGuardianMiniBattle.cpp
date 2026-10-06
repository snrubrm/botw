#include "Game/AI/AI/aiGuardianMiniBattle.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007091AC.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "Game/AI/AI/aiGuardianMiniRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

GuardianMiniBattle::GuardianMiniBattle(const InitArg& arg) : EnemyBattle(arg) {}

GuardianMiniBattle::~GuardianMiniBattle() = default;

bool GuardianMiniBattle::init_(sead::Heap* heap) {
    _144 = 100;
    return true;
}

void GuardianMiniBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    _140 = false;
    _141 = false;
    _188 = ksys::Timer(*mRollingInterval_s, *mRollingInterval_s);
    _1ac = ksys::Timer(5, 5);
    _88 = testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1);

    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) && m45()) {
        sub_7100413A38();
        return;
    }

    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1)) {
        m37();
        return;
    }

    sub_7100381ED4();
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        m37();
        return;
    }

    if (sub_71004282EC(mActor)) {
        const sead::Vector3f target_pos = sub_71005D9330(mActor);
        const auto& pos = mActor->getMtx().getTranslation();
        const f32 dx = pos.x - target_pos.x;
        const f32 dz = pos.z - target_pos.z;
        if (!(dx * dx + dz * dz < *mTurnMoveStartDist_s * *mTurnMoveStartDist_s) &&
            sead::GlobalRandom::instance()->getS32Range(0, 100) < *mTurnMovePer_s) {
            changeToMoveTurning();
        } else {
            m37();
        }
    } else {
        m37();
    }

    _1a0 = ksys::Timer(*mCounterStartTime_s, *mCounterStartTime_s);
}

void GuardianMiniBattle::leave_() {
    if (auto* pe = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
        if (!pe->m151(3)) {
            auto* actor = mActor;
            if (actor && actor->getModel() && actor->getASList()) {
                actor->getASList()->sub_710115C11C();
                actor->getASList()->sub_710115BED4(true);
            }
        }
    }
    EnemyBattle::leave_();
}

void GuardianMiniBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mRootNodeName_s, "RootNodeName");
    getStaticParam(&mArm1NodeName_s, "Arm1NodeName");
    getStaticParam(&mArm2NodeName_s, "Arm2NodeName");
    getStaticParam(&mArm3NodeName_s, "Arm3NodeName");
    getStaticParam(&mASSlotRight_s, "ASSlotRight");
    getStaticParam(&mASSlotLeft_s, "ASSlotLeft");
    getStaticParam(&mASSlotBack_s, "ASSlotBack");
    getStaticParam(&mRollingInterval_s, "RollingInterval");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mIsIgnoreArmCondition_s, "IsIgnoreArmCondition");
    getStaticParam(&mTurnMoveTime_s, "TurnMoveTime");
    getStaticParam(&mTurnMovePer_s, "TurnMovePer");
    getStaticParam(&mTurnMoveStartDist_s, "TurnMoveStartDist");
    getStaticParam(&mCounterStartDamageCount_s, "CounterStartDamageCount");
    getStaticParam(&mCounterStartTime_s, "CounterStartTime");
    getStaticParam(&mCheckOnNoNavMesh_s, "CheckOnNoNavMesh");
    getAITreeVariable(&mDamagedCount_a, "DamagedCount");
}

bool GuardianMiniBattle::isChangeable() const {
    return isCurrentChild("戦闘準備") || isCurrentChild("旋回移動");
}

void GuardianMiniBattle::m44(ksys::act::ai::InlineParamPack* params) {}

void GuardianMiniBattle::sub_7100413A38() {
    auto* actor = mActor;
    if (actor) {
        if (actor->getModel() && actor->getASList()) {
            actor->getASList()->sub_710115C11C();
            actor->getASList()->sub_710115BED4(true);
            actor = mActor;
        }
        if (actor) {
            if (actor->getASList())
                actor->getASList()->sub_710115B01C(*mASSlotRight_s, 0, true);
            actor = mActor;
        }
        if (actor) {
            if (actor->getASList())
                actor->getASList()->sub_710115B01C(*mASSlotLeft_s, 0, true);
            actor = mActor;
        }
        if (actor && actor->getASList())
            actor->getASList()->sub_710115B01C(*mASSlotBack_s, 0, true);
    }
    *mDamagedCount_a = 0;
    _1a0 = ksys::Timer(*mCounterStartTime_s, *mCounterStartTime_s);
    ksys::act::ai::InlineParamPack params;
    m44(&params);
    changeChild("反撃", &params);
}

bool GuardianMiniBattle::m45() {
    if (!sub_71004282EC(mActor))
        return false;
    auto* nav = mActor->m45();
    if (nav && (nav->_2a4 & 0xffff) == 0x17)
        return false;
    if (*mCounterStartTime_s < 1)
        return false;
    return _1a0.value <= sead::Mathf::epsilon();
}

bool GuardianMiniBattle::handleMessage_(const ksys::Message* message) {
    return _148.m2(*message);
}

void GuardianMiniBattle::changeToMoveTurning() {
    _194 = ksys::Timer(*mTurnMoveTime_s, *mTurnMoveTime_s);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("旋回移動", &params);
}

bool GuardianMiniBattle::sub_7100415140(s32 idx) {
    auto* actor = mActor;
    if (!sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return false;
    auto* weapon = static_cast<uking::act::Enemy*>(actor)->getWeapons()->getEquippedWeapon(idx);
    if (!sead::IsDerivedFrom<uking::act::Weapon>(weapon))
        return false;
    return static_cast<uking::act::Weapon*>(weapon)->_cf0 != 4;
}

// NON_MATCHING: same as GuardianMiniRangeKeepMove::m35 (the original reads `a` before the getWeapons() vcall
// and returns through a pointer select; our frame differs)
// Same slot selection as GuardianMiniRangeKeepMove::m35 (see there).
s32 GuardianMiniBattle::sub_7100415EAC() {
    s32 a;
    s32 b;
    s32 c = -1;
    sub_71007091AC(mActor, &a, &b, &c);
    auto* actor = mActor;
    if (!sead::IsDerivedFrom<uking::act::Enemy>(actor))
        return a;
    auto* weapon = static_cast<uking::act::Enemy*>(actor)->getWeapons()->getEquippedWeapon(a);
    if (sead::IsDerivedFrom<uking::act::Weapon>(weapon) && weapon->getProfile() != "WeaponShield")
        return a;
    return b;
}

bool GuardianMiniBattle::m40() {
    if (!mActor)
        return false;

    const s32 slot = sub_7100415EAC();
    if (*mIsIgnoreArmCondition_s)
        return EnemyBattle::m40();

    auto* actor = mActor;
    if (!actor)
        return false;
    const f32 x = actor->getMtx().m[0][3];
    const f32 z = actor->getMtx().m[2][3];
    const auto& target = sub_71005D9330(actor);
    const sead::Vector2f diff(x - target.x, z - target.z);
    if (diff.length() <= *mBaseDist_s + *mFarDist_s + sub_71007320F0(mActor, slot))
        return EnemyBattle::m40();
    return false;
}

// NON_MATCHING: the original re-tests the AS list at each step without threading the null case to the end
// (it reloads `mActor` after every call); same behaviour otherwise.
void GuardianMiniBattle::m43(ksys::act::ai::InlineParamPack* params) {
    if (!params)
        return;
    auto* actor = mActor;
    if (actor) {
        if (actor->getModel() && actor->getASList()) {
            actor->getASList()->sub_710115C11C();
            actor->getASList()->sub_710115BED4(true);
            actor = mActor;
        }
        if (actor && actor->getASList()) {
            actor->getASList()->sub_710115B01C(*mASSlotRight_s, 0, true);
            actor = mActor;
        }
        if (actor && actor->getASList()) {
            actor->getASList()->sub_710115B01C(*mASSlotLeft_s, 0, true);
            actor = mActor;
        }
        if (actor && actor->getASList()) {
            actor->getASList()->sub_710115B01C(*mASSlotBack_s, 0, true);
            actor = mActor;
        }
    }
    s32 a;
    s32 b;
    s32 c = -1;
    sub_71007091AC(mActor, &a, &b, &c);
    sub_7100415258(a, b, c, 0);
    params->addInt(a, "DynWeaponIdx", -1);
}

void GuardianMiniBattle::m37() {
    s32 a;
    s32 b;
    s32 c = -1;
    sub_71007091AC(mActor, &a, &b, &c);
    sub_7100415258(a, b, c, -1);
    EnemyBattle::m37();
}

}  // namespace uking::ai
