#include "Game/AI/Action/actionElectricBlownOff.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"

namespace uking::action {

ElectricBlownOff::ElectricBlownOff(const InitArg& arg) : BlownOff(arg) {}

ElectricBlownOff::~ElectricBlownOff() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->sub_7100D3CFEC(sead::SafeString(mElectricActorKey_s.cstr()));
}

bool ElectricBlownOff::init_(sead::Heap* heap) {
    return BlownOff::init_(heap) && sub_7100103E00(heap);
}

// NON_MATCHING: the byte reset and the timer's current/previous stores are scheduled differently.
void ElectricBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
    if (auto* manager = sub_710072BA90(mActor)) {
        if (manager->checkDamageFlags(0)) {
            _1a8 = 0;
            _19c.reset(sead::Mathi::max(1, *mMaxKeepTimer_s));
            sub_710010441C();
            return;
        }
    }
    _1a8 = 0xff;
}

void ElectricBlownOff::leave_() {
    BlownOff::leave_();
    if (!_1a8) {
        _1a8 = true;
        sub_710010451C();
    }
}

void ElectricBlownOff::loadParams_() {
    BlownOff::loadParams_();
    getStaticParam(&mVoltage_s, "Voltage");
    getStaticParam(&mMaxTimer_s, "MaxTimer");
    getStaticParam(&mMaxKeepTimer_s, "MaxKeepTimer");
    getStaticParam(&mElectricActorName_s, "ElectricActorName");
    getStaticParam(&mElectricActorKey_s, "ElectricActorKey");
}

void ElectricBlownOff::calc_() {
    BlownOff::calc_();
    if (_1a8)
        return;
    if (_19c.value <= sead::Mathf::epsilon()) {
        _1a8 = 1;
        sub_710010451C();
    } else {
        _19c.update();
    }
}

}  // namespace uking::action
