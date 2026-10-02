#include "Game/AI/AI/aiReuseBulletPartsRoot.h"

namespace uking::ai {

ReuseBulletPartsRoot::ReuseBulletPartsRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReuseBulletPartsRoot::~ReuseBulletPartsRoot() = default;

bool ReuseBulletPartsRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReuseBulletPartsRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ReuseBulletPartsRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReuseBulletPartsRoot::loadParams_() {}

bool ReuseBulletPartsRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType() == 0x3000007) {
        sub_7100551DAC();
        return true;
    }
    if (_38.m2(message)) {
        _88 = true;
        return true;
    }
    return false;
}

bool ReuseBulletPartsRoot::m34() {
    return true;
}

}  // namespace uking::ai
