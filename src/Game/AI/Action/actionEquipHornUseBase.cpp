#include "Game/AI/Action/actionEquipHornUseBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EquipHornUseBase::EquipHornUseBase(const InitArg& arg) : TimeredASPlay(arg) {}

EquipHornUseBase::~EquipHornUseBase() = default;

bool EquipHornUseBase::init_(sead::Heap* heap) {
    return TimeredASPlay::init_(heap);
}

void EquipHornUseBase::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(1));
    _70 = *mSignalOnTime_s;
    _74 = false;
}

void EquipHornUseBase::leave_() {
    TimeredASPlay::leave_();
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(0));
}

void EquipHornUseBase::loadParams_() {
    TimeredASPlay::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSignalOnTime_s, "SignalOnTime");
}

void EquipHornUseBase::calc_() {
    TimeredASPlay::calc_();
    sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(1));
    _74 = false;
    if (_70 >= 0.0f) {
        ksys::Timer::update(&_70, -1.0f);
        if (_70 <= 0.0f) {
            mActor->emitBasicSigOn();
            _74 = true;
        }
    }
}

bool EquipHornUseBase::hasPreDeleteCb() {
    return true;
}

void EquipHornUseBase::onPreDelete() {
    mActor->emitBasicSigOff();
}

}  // namespace uking::action
