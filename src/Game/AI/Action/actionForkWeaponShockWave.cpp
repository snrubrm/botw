#include "Game/AI/Action/actionForkWeaponShockWave.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkWeaponShockWave::ForkWeaponShockWave(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkWeaponShockWave::~ForkWeaponShockWave() = default;

void ForkWeaponShockWave::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _48 = false;
}

void ForkWeaponShockWave::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mShockWaveRadius_s, "ShockWaveRadius");
    getStaticParam(&mUnderRayLength_s, "UnderRayLength");
}

void ForkWeaponShockWave::calc_() {
    ksys::act::ai::Action::calc_();
}

bool ForkWeaponShockWave::m32() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return false;
    if (as_list->x(3, nullptr, *mTargetBone_s, *mSeqBank_s,
                   &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        return true;
    }
    return as_list->x(3, nullptr, *mTargetBone_s, *mSeqBank_s,
                      &ksys::as::ASList::Unk2::sub_710116388C, true);
}

}  // namespace uking::action
