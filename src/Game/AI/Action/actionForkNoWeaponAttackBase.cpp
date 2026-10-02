#include "Game/AI/Action/actionForkNoWeaponAttackBase.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <prim/seadStringBuilder.h>

namespace uking::action {

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
