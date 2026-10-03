#include "Game/AI/Action/actionAirOctaFloat.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

namespace {
// Placeholder name: the user data of message 0x80000c8 when `_0` is 0xc.
struct Unk_80000c8_Payload {
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _c;
    u32 _10;
    f32 _14;
};
}  // namespace

AirOctaFloat::AirOctaFloat(const InitArg& arg) : AirOctaFloatBase(arg) {}

AirOctaFloat::~AirOctaFloat() = default;

bool AirOctaFloat::init_(sead::Heap* heap) {
    return AirOctaFloatBase::init_(heap);
}

void AirOctaFloat::enter_(ksys::act::ai::InlineParamPack* params) {
    AirOctaFloatBase::enter_(params);
}

void AirOctaFloat::leave_() {
    AirOctaFloatBase::leave_();
}

void AirOctaFloat::loadParams_() {
    AirOctaFloatBase::loadParams_();
}

bool AirOctaFloat::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x80000c8) {
        const auto* data = static_cast<const Unk_80000c8_Payload*>(message->getUserData());
        if (data && data->_0 == 0xc) {
            _1f8 = data->_14;
            return true;
        }
    }
    return false;
}

void AirOctaFloat::calc_() {
    AirOctaFloatBase::calc_();
}

}  // namespace uking::action
