#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/System/VFR.h"

Unk_7102459708::Unk_7102459708(ksys::act::ai::ActionBase* owner) : mOwner(owner) {}

uking::act::Camera* Unk_7102459708::getCamera() const {
    if (!mOwner)
        return nullptr;
    auto* actor = mOwner->getActor();
    if (!actor)
        return nullptr;
    return sead::DynamicCast<uking::act::Camera>(actor);
}

uking::act::Camera* Unk_7102459708::getCameraActor() const {
    if (!mOwner)
        return nullptr;
    auto* actor = mOwner->getActor();
    if (!actor)
        return nullptr;
    return sead::DynamicCast<uking::act::Camera>(actor);
}

f32 Unk_7102459708::sub_7100791E44(f32 t) const {
    return sub_710092523C(sub_71009251C4(getCamera()), t);
}

namespace uking::act {

bool sub_710079BE9C(int idx) {
    return idx < 1;
}

Unk_710079a8e8::~Unk_710079a8e8() = default;

void Camera::sub_71007953C8() {
    if (sub_7100922078())
        return;
    const f32 rate = sub_710092523C(Unk_7102459cc0::_8, 0.6f);
    _860._0._28 += rate * (0.0f - _860._0._28);
}

void Camera::sub_71007929E0() {
    _860._0 = _860._38 = _860._70 = _860._a8 = _860._e0;
    _860._150 = _860._0._c;
    _1240.sub_710092A83C();
    _860.sub_710079AEE0();
    _860._7fc.sub_710079B62C(0x8000);
    _13f8 = 0;
    _13fd &= ~0x80;
    _860._7c0[!(_860._81a & 1)].reset();
}

void Camera::sub_7100799920() {}

void Camera::m148() {}

void Camera::m149() {}

void Camera::m155(f32 degrees) {
    m154(sead::Mathf::deg2rad(degrees), true);
}

sead::Vector3f Camera::m156() {
    return {_860._e0.sub_7100921C04(), _860._e0.sub_7100921C50(), _860._e0.sub_7100921C98()};
}

void Camera::m157(void* a1, const sead::Matrix34f& mtx) {
    _1088 = a1;
    _1090 = mtx;
}

void* Camera::m158() {
    return _1088;
}

sead::Matrix34f* Camera::m159() {
    return &_1090;
}

void Camera::m160() {
    if (sub_7100922428())
        return;
    sub_7100793924();
}

void Camera::m161() {
    if (sub_7100922428())
        return;
    sub_7100793BD8();
}

void Camera::m162() {
    _860._804.sub_710079AE20(1);
}

void* Camera::m165() {
    return _1088;
}

bool Camera::sub_7100794FD0() const {
    return _860._800.sub_710079C0CC(0x8000);
}

bool Camera::sub_710079614C() const {
    return (_13fd & 0xc) == 4;
}

bool Camera::sub_7100796164() const {
    return _13fd & 4;
}

}  // namespace uking::act
