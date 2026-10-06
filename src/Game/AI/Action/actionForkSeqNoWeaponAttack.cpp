#include <prim/seadFormatPrint.h>
#include "Game/AI/Action/actionForkSeqNoWeaponAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::action {

ForkSeqNoWeaponAttack::ForkSeqNoWeaponAttack(const InitArg& arg)
    : ForkAttackWithWeaponOrWithout(arg) {}

ForkSeqNoWeaponAttack::~ForkSeqNoWeaponAttack() = default;

// NON_MATCHING: the original selects between the two parameter value addresses (+0x70 / +0x90) and loads once; ours
// selects the parameter objects and adds the value offset (0x18) afterwards
bool ForkSeqNoWeaponAttack::init_(sead::Heap* heap) {
    _80.sub_7100720AF4();
    _80._10 = sub_7100146FA0();
    const auto* attack = mActor->getParam()->getRes().mGParamList->getAttack();
    _80._8 = *mIsImpulseLarge_s ? attack->mImpulseLarge.ref() : attack->mImpulse.ref();
    _80._18.pushBack(mExcludeAtkName_s[0]);
    _80._18.pushBack(mExcludeAtkName_s[1]);
    return true;
}

void ForkSeqNoWeaponAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAttackWithWeaponOrWithout::enter_(params);
}

void ForkSeqNoWeaponAttack::leave_() {
    _80.sub_7100720FD0();
}

void ForkSeqNoWeaponAttack::loadParams_() {
    ForkAttackWithWeaponOrWithout::loadParams_();
    getStaticParam(&mAttackType_s, "AttackType");
    getStaticParam(&mIsImpulseLarge_s, "IsImpulseLarge");
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 2; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "ExcludeAtkName%d", i) << sead::flush;
        getStaticParam(&mExcludeAtkName_s[i], key);
    }
}

void ForkSeqNoWeaponAttack::calc_() {
    _80.sub_7100720B28();
}

}  // namespace uking::action
