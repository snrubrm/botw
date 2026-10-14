#include "Game/Actor/Action/actionPunchAttack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include <prim/seadStringBuilder.h>

namespace uking::action {

PunchAttack::PunchAttack(const InitArg& arg) : ActionWithAS(arg) {}

PunchAttack::~PunchAttack() = default;

bool PunchAttack::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void PunchAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
    setDamageCallbackTiming(mActor, 4, &_a8);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

void PunchAttack::leave_() {
    auto* actor = mActor;
    for (int i = 0; i < 3; ++i) {
        if (mAtkBodyName_s[i].isEmpty())
            break;
        sub_71007A2D7C(actor, mAtkBodyName_s[i]);
    }
    sub_71005DA114(mActor, &_a8);
    StopBase::leave_();
}

void PunchAttack::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mIsGuardPierce_s, "IsGuardPierce");
    getStaticParam(&mIsForceGuardBreak_s, "IsForceGuardBreak");
    getStaticParam(&mIsIniviciblePierce_s, "IsIniviciblePierce");
    getStaticParam(&mIsImpulseLarge_s, "IsImpulseLarge");
    getStaticParam(&mIsHeavy_s, "IsHeavy");
    getStaticParam(&mIsHammer_s, "IsHammer");
    getStaticParam(&mASName_s, "ASName");
    sead::FixedStringBuilder<64> name;
    for (int i = 0; i < 3; ++i) {
        name.format("AtkBodyName%d", i + 1);
        getStaticParam(&mAtkBodyName_s[i], name.cstr());
    }
}

// NON_MATCHING: identical except the scheduler loads `*cNullChar` (w21) before the first name character
// instead of after it
void PunchAttack::calc_() {
    ActionWithAS::calc_();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0)) {
        sub_710022424C(&query);
    } else if (sub_71005DD74C(mActor, nullptr, 0, 0)) {
        if (!mAtkBodyName_s[0].isEmpty()) {
            auto* actor = mActor;
            sub_71007A2D7C(actor, mAtkBodyName_s[0]);
            if (!mAtkBodyName_s[1].isEmpty()) {
                sub_71007A2D7C(actor, mAtkBodyName_s[1]);
                if (!mAtkBodyName_s[2].isEmpty())
                    sub_71007A2D7C(actor, mAtkBodyName_s[2]);
            }
        }
    }
}

// NON_MATCHING: the original selects the parameter value address (+0x70 / +0x90) for the impulse, as in
// ForkNoWeaponAttackBase::m32; register allocation follows from it.
void PunchAttack::sub_710022424C(ksys::as::ASList::Unk4* query) {
    sead::FixedSafeString<64> name;
    sub_71005D7C94(&name, &query->name);
    auto* actor = mActor;
    if (!mAtkBodyName_s[0].isEmpty()) {
        sub_71007A2C30(actor, mAtkBodyName_s[0], nullptr);
        if (!mAtkBodyName_s[1].isEmpty()) {
            sub_71007A2C30(actor, mAtkBodyName_s[1], nullptr);
            if (!mAtkBodyName_s[2].isEmpty())
                sub_71007A2C30(actor, mAtkBodyName_s[2], nullptr);
        }
    }
    auto* sensor = getActorAttackSensor(actor);

    u32 flags;
    switch (*mAttackIntensity_s) {
    case 1:
        flags = 1;
        break;
    case 2:
        flags = 2;
        break;
    case 3:
        flags = 4;
        break;
    default:
        flags = 0;
        break;
    }
    if (*mIsGuardPierce_s)
        flags |= 0x8;
    if (*mIsIniviciblePierce_s)
        flags |= 0x40;
    if (*mIsForceGuardBreak_s)
        flags |= 0x100;
    if (*mIsHeavy_s)
        flags |= 0x8000;
    if (*mIsHammer_s)
        flags |= 0x1000;

    const s32 atk_power = static_cast<ksys::act::PlayerOrEnemy*>(actor)->getEnemyAtkPower();
    const s32 power = atk_power > 1 ? atk_power : 1;
    const auto* attack = mActor->getParam()->getRes().mGParamList->getAttack();
    const s32 impulse = *mIsImpulseLarge_s ? attack->mImpulseLarge.ref() : attack->mImpulse.ref();
    const s32 guard_break =
        actor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref();
    sensor->activateAttackSensor(0x2000, flags, power, impulse, 0.0f, guard_break, 1,
                                 sub_71007A3A8C(&name), false, 1, -1);
}

}  // namespace uking::action
