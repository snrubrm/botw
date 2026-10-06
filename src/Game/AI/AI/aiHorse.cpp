#include "Game/AI/AI/aiHorse.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

Horse::Horse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

Horse::~Horse() = default;

void Horse::sub_7100435180(u64 value) {
    _48.reset(0x70);
    _48.set(0x50);
    _50 = value;
    _4c = 0;
    if (auto* rideable = mActor->getHorseOptionsMaybe()) {
        rideable->sub_7100E8BE10();
        rideable->Unk_7100e8b2b8::_8 = 0x200;
    }
    if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor))
        horse->sub_7100E6C0E0(true);
}

void Horse::sub_7100435420() {
    if (_48.isOn(0x30)) {
        mActor->x_3(0.0f);
        _48.reset(0x30);
        _50 = 0;
        if (auto* rideable = mActor->getHorseOptionsMaybe()) {
            rideable->sub_7100E8BD80();
            rideable->Unk_7100e8b2b8::_8.setBitOff(9);
        }
        if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor)) {
            horse->sub_7100E6C0E0(false);
            horse->_b74.resetBit(3);
        }
    }
}

void Horse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void Horse::leave_() {
    sub_7100435420();
}

void Horse::loadParams_() {
    getStaticParam(&mDistanceFall_s, "DistanceFall");
    getStaticParam(&mDistanceFallDie_s, "DistanceFallDie");
}

}  // namespace uking::ai
