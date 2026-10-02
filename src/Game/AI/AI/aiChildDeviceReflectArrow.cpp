#include "Game/AI/AI/aiChildDeviceReflectArrow.h"

namespace uking::ai {

ChildDeviceReflectArrow::ChildDeviceReflectArrow(const InitArg& arg) : WithoutWeaponArrow(arg) {}

ChildDeviceReflectArrow::~ChildDeviceReflectArrow() = default;

void ChildDeviceReflectArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    WithoutWeaponArrow::enter_(params);
}

void ChildDeviceReflectArrow::loadParams_() {
    WithoutWeaponArrow::loadParams_();
    getStaticParam(&mReflectCountMax_s, "ReflectCountMax");
    getStaticParam(&mReflectAimSpeed_s, "ReflectAimSpeed");
    getStaticParam(&mReflectAccel_s, "ReflectAccel");
}

void ChildDeviceReflectArrow::m35() {
    WithoutWeaponArrow::m35();
}

f32 ChildDeviceReflectArrow::m42() {
    return _15a ? WithoutWeaponArrow::m42() : *mReflectAccel_s;
}

f32 ChildDeviceReflectArrow::m43() {
    return _15a ? WithoutWeaponArrow::m43() : *mReflectAimSpeed_s;
}

s32 ChildDeviceReflectArrow::m47() {
    if (!_15a)
        return 0;
    return WithoutWeaponArrow::m47();
}

bool ChildDeviceReflectArrow::m48() {
    if (WithoutWeaponArrow::m48())
        return true;
    return isCurrentChild("反射");
}

bool ChildDeviceReflectArrow::m49() {
    return _158;
}

void ChildDeviceReflectArrow::m50(bool a1) {
    _158 = a1;
}

s32 ChildDeviceReflectArrow::m51() {
    return _15c;
}

sead::Vector3f* ChildDeviceReflectArrow::m52() {
    return &_174;
}

void ChildDeviceReflectArrow::m53(const sead::Vector3f& a1) {
    _174 = a1;
}

}  // namespace uking::ai
