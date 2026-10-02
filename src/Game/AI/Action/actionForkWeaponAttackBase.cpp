#include "Game/AI/Action/actionForkWeaponAttackBase.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkWeaponAttackBase::ForkWeaponAttackBase(const InitArg& arg)
    : ForkAttackWithWeaponOrWithout(arg) {}

ForkWeaponAttackBase::~ForkWeaponAttackBase() = default;

bool ForkWeaponAttackBase::init_(sead::Heap* heap) {
    return ForkAttackWithWeaponOrWithout::init_(heap);
}

void ForkWeaponAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAttackWithWeaponOrWithout::enter_(params);
    mFlags.set(Flag::Changeable);
    _68 = false;
}

void ForkWeaponAttackBase::leave_() {
    m33();
}

void ForkWeaponAttackBase::loadParams_() {
    ForkAttackWithWeaponOrWithout::loadParams_();
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mIsNoRod_s, "IsNoRod");
}

void ForkWeaponAttackBase::calc_() {
    ksys::as::ASList::Unk4 query;
    if (m34(&query)) {
        m32(m36(), query.name, _68, 1.0f);
        _68 = true;
    } else if (m35()) {
        m33();
    }
}

int ForkWeaponAttackBase::m36() {
    return 0;
}

bool ForkWeaponAttackBase::m34(ksys::as::ASList::Unk4* query) {
    return sub_71005DD66C(mActor, query, *mTargetBone_s, *mSeqBank_s);
}

bool ForkWeaponAttackBase::m35() {
    return sub_71005DD74C(mActor, nullptr, *mTargetBone_s, *mSeqBank_s);
}

void ForkWeaponAttackBase::m33() {
    sub_71005D79AC(mActor, m36(), act::Unk_71002edaec(1));
}

}  // namespace uking::action
