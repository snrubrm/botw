#include "Game/AI/Action/actionForkWeaponShockWaveCheckValue.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkWeaponShockWaveCheckValue::ForkWeaponShockWaveCheckValue(const InitArg& arg)
    : ForkWeaponShockWave(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkWeaponShockWaveCheckValue::~ForkWeaponShockWaveCheckValue() {
    ;
}

bool ForkWeaponShockWaveCheckValue::init_(sead::Heap* heap) {
    return ForkWeaponShockWave::init_(heap);
}

void ForkWeaponShockWaveCheckValue::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkWeaponShockWave::enter_(params);
}

void ForkWeaponShockWaveCheckValue::leave_() {
    ForkWeaponShockWave::leave_();
}

void ForkWeaponShockWaveCheckValue::loadParams_() {
    ForkWeaponShockWave::loadParams_();
    getStaticParam(&mAtEventValue_s, "AtEventValue");
}

void ForkWeaponShockWaveCheckValue::calc_() {
    ForkWeaponShockWave::calc_();
}

bool ForkWeaponShockWaveCheckValue::m32() {
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD7B0(mActor, &query, *mTargetBone_s, *mSeqBank_s) ||
        sub_71005DD74C(mActor, &query, *mTargetBone_s, *mSeqBank_s)) {
        return query.name == mAtEventValue_s;
    }
    return false;
}

}  // namespace uking::action
