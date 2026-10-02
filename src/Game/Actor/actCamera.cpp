#include "Game/Actor/actCamera.h"
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
