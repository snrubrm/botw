#include "Game/AI/Action/actionForkNoWeaponAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkNoWeaponAttack::ForkNoWeaponAttack(const InitArg& arg) : ForkNoWeaponAttackBase(arg) {}

ForkNoWeaponAttack::~ForkNoWeaponAttack() = default;

bool ForkNoWeaponAttack::init_(sead::Heap* heap) {
    return ForkNoWeaponAttackBase::init_(heap);
}

void ForkNoWeaponAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkNoWeaponAttackBase::enter_(params);
}

void ForkNoWeaponAttack::leave_() {
    sub_710015E71C();
    ForkNoWeaponAttackBase::leave_();
}

void ForkNoWeaponAttack::loadParams_() {
    ForkNoWeaponAttackBase::loadParams_();
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mSeqBank_s, "SeqBank");
}

void ForkNoWeaponAttack::calc_() {
    ForkNoWeaponAttackBase::calc_();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, *mTargetBone_s, *mSeqBank_s)) {
        sead::FixedSafeString<9> direction;
        sub_71005D7C94(&direction, &query.name);
        sub_710015E4E8(direction);
    }
    if (sub_71005DD74C(mActor, nullptr, *mTargetBone_s, *mSeqBank_s))
        sub_710015E71C();
}

}  // namespace uking::action
