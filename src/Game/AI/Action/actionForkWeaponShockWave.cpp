#include "Game/AI/Action/actionForkWeaponShockWave.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
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

// NON_MATCHING: the position output and scoped request have different stack allocation.
void ForkWeaponShockWave::calc_() {
    sead::Vector3f position;
    if (_48 || !sub_710016A388(&position))
        return;
    _48 = true;
    {
        act::Unk_71002eda38 arg;
        arg._0 = 8;
        arg._8 = position;
        arg._34 = *mShockWaveRadius_s;
        sub_71005D787C(mActor, *mWeaponIdx_s, arg);
    }
    const u32 value = 0;
    sub_71005D8C94(mActor, *mWeaponIdx_s, value);
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
