#include "Game/AI/Action/actionForkNoWeaponAttackBase.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <algorithm>
#include <prim/seadStringBuilder.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::action {
namespace {
const u32 sAttackTypes[] = {0x2000, 0x10, 0x8000, 0x800};
}


ForkNoWeaponAttackBase::ForkNoWeaponAttackBase(const InitArg& arg)
    : ForkAttackWithWeaponOrWithout(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkNoWeaponAttackBase::~ForkNoWeaponAttackBase() {
    ;
}

bool ForkNoWeaponAttackBase::init_(sead::Heap* heap) {
    return ForkAttackWithWeaponOrWithout::init_(heap);
}

void ForkNoWeaponAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAttackWithWeaponOrWithout::enter_(params);
    mFlags.set(Flag::Changeable);
}

void ForkNoWeaponAttackBase::leave_() {
    ForkAttackWithWeaponOrWithout::leave_();
}

// NON_MATCHING: regalloc (&mAttackType_s kept in x20 from before the first call)
void ForkNoWeaponAttackBase::loadParams_() {
    ForkAttackWithWeaponOrWithout::loadParams_();
    getStaticParam(&mIsImpulseLarge_s, "IsImpulseLarge");
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mAttackPowerScale_s, "AttackPowerScale");
    getStaticParam(&mIsUseAttackParam_s, "IsUseAttackParam");
    sead::FixedStringBuilder<64> name;
    for (int i = 0; i < 3; ++i) {
        name.format("AtkBodyName%d", i + 1);
        getStaticParam(&mAtkBodyName_s[i], name.cstr());
    }
    getStaticParam(&mChmName1_s, "ChmName1");
}

void ForkNoWeaponAttackBase::calc_() {
    ForkAttackWithWeaponOrWithout::calc_();
}

// NON_MATCHING: the original loads mActor after the flag byte (hoisted out of both arms); ours loads it first
int ForkNoWeaponAttackBase::m33() {
    auto* actor = mActor;
    s32 power;
    if (*mIsUseAttackParam_s)
        power = actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref();
    else
        power = std::max(static_cast<ksys::act::PlayerOrEnemy*>(actor)->getEnemyAtkPower(), 1);
    return s32(power * *mAttackPowerScale_s);
}

// NON_MATCHING: the checked unsigned type index is loaded before the sensor query.
void ForkNoWeaponAttackBase::sub_710015E4E8(const sead::SafeString& direction) {
    auto* actor = mActor;
    if (mAtkBodyName_s[0].isEmpty()) {
        if (auto* bodies = actor->getRigidBodyByName(ksys::act::getStr_Atk().cstr())) {
            for (int i = 0; i < bodies->getRigidBodies().size(); ++i)
                sub_71007A2B64(bodies->getRigidBody(i), nullptr);
        }
    } else {
        sub_71007A2C30(actor, mAtkBodyName_s[0], nullptr);
        if (!mAtkBodyName_s[1].isEmpty()) {
            sub_71007A2C30(actor, mAtkBodyName_s[1], nullptr);
            if (!mAtkBodyName_s[2].isEmpty())
                sub_71007A2C30(actor, mAtkBodyName_s[2], nullptr);
        }
    }

    u32 type = *mAttackType_s;
    getActorAttackSensor(actor)->activateAttackSensor(
        type < 4 ? sAttackTypes[type] : 0x2000, sub_7100146FA0(), m33(), m32(), 0.0f,
        m34(), 1, sub_71007A3A8C(&direction), false, m35(), -1);

    ksys::act::Chemical* chemical;
    if (mChmName1_s.isEmpty())
        chemical = mActor->getChemicalStuff();
    else
        chemical = mActor->sub_71011D8A54(mChmName1_s);
    if (chemical)
        chemical->_c |= 0x20;
}

// NON_MATCHING: probably the same loop shape as PunchAttack::calc_ (the original loads *cNullChar once up front)
void ForkNoWeaponAttackBase::sub_710015E71C() {
    if (!mAtkBodyName_s[0].isEmpty()) {
        auto* actor = mActor;
        sub_71007A2D7C(actor, mAtkBodyName_s[0]);
        if (!mAtkBodyName_s[1].isEmpty()) {
            sub_71007A2D7C(actor, mAtkBodyName_s[1]);
            if (!mAtkBodyName_s[2].isEmpty())
                sub_71007A2D7C(actor, mAtkBodyName_s[2]);
        }
    }
    ksys::act::Chemical* chemical;
    if (mChmName1_s.isEmpty())
        chemical = mActor->getChemicalStuff();
    else
        chemical = mActor->sub_71011D8A54(mChmName1_s);
    if (chemical)
        chemical->_c &= ~0x20u;
}

int ForkNoWeaponAttackBase::m35() {
    return 1;
}

// NON_MATCHING: the original selects the parameter value address (+0x70/+0x90) instead of folding +0x18 into the load
int ForkNoWeaponAttackBase::m32() {
    if (!*mIsImpulseLarge_s)
        return mActor->getParam()->getRes().mGParamList->getAttack()->mImpulse.ref();
    return mActor->getParam()->getRes().mGParamList->getAttack()->mImpulseLarge.ref();
}

int ForkNoWeaponAttackBase::m34() {
    return mActor->getParam()->getRes().mGParamList->getAttack()->mGuardBreakPower.ref();
}

}  // namespace uking::action
