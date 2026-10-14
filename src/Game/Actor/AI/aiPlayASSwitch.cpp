#include "Game/Actor/AI/aiPlayASSwitch.h"

namespace uking::ai {

PlayASSwitch::PlayASSwitch(const InitArg& arg) : SimpleLiftable(arg) {}

PlayASSwitch::~PlayASSwitch() = default;

bool PlayASSwitch::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void PlayASSwitch::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
    _f8 = false;
    changeAS(mOffAS_s.cstr(), *mIsIgnoreSameOffAS_s, 0, 0);
}

void PlayASSwitch::calc_() {
    SimpleLiftable::calc_();
    if (_f8) {
        changeAS(mOnAS_s.cstr(), *mIsIgnoreSameOnAS_s, 0, 0);
        _f8 = false;
    } else {
        changeAS(mOffAS_s.cstr(), *mIsIgnoreSameOffAS_s, 0, 0);
    }
}

bool PlayASSwitch::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000009)
        _f8 = true;
    return SimpleLiftable::handleMessage_(message);
}

void PlayASSwitch::leave_() {
    SimpleLiftable::leave_();
}

void PlayASSwitch::loadParams_() {
    getStaticParam(&mIsIgnoreSameOnAS_s, "IsIgnoreSameOnAS");
    getStaticParam(&mIsIgnoreSameOffAS_s, "IsIgnoreSameOffAS");
    getStaticParam(&mOnAS_s, "OnAS");
    getStaticParam(&mOffAS_s, "OffAS");
}

}  // namespace uking::ai
