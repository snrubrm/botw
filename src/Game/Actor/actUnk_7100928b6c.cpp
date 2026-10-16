// TU of Camera::_1240 (Unk_7100928b6c, 0x7100928874-), in the camera utility code.
#include "Game/Actor/actCamera.h"
#include "KingSystem/Physics/System/physQueryContactPointInfo.h"
#include "KingSystem/Physics/System/physRayCast.h"
#include "KingSystem/Physics/System/physShapeCast.h"

namespace uking::act {

Unk_7100928b6c::Unk_7100928b6c(Camera* camera) : mCamera(camera) {}

void Unk_7100928b6c::sub_7100928C10(u8 mask) {
    _140 |= mask;
}

void Unk_7100928b6c::sub_7100928C20(u8 mask) {
    _140 &= ~mask;
}

void Unk_7100928b6c::sub_7100928C30() {
    _141 |= 1;
}

void Unk_7100928b6c::sub_7100928C40() {
    _141 &= ~1;
}

void Unk_7100928b6c::sub_7100928C50(ksys::phys::RayCast* ray_cast) {
    ray_cast->setGroundHit(ksys::phys::GroundHit::Camera);
    ray_cast->enableLayer(ksys::phys::ContactLayer::EntityGround);
    ray_cast->enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    ray_cast->enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    ray_cast->enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    ray_cast->enableLayer(ksys::phys::ContactLayer::EntityWater);
    if (_144)
        ray_cast->disableLayer(ksys::phys::ContactLayer::EntityGroundObject);
}

void sub_7100928CD4(ksys::phys::ShapeCast* cast) {
    using ksys::phys::ContactLayer;
    auto* info = cast->getContactPointInfo();
    cast->setMode(ksys::phys::ShapeCast::Mode::_0);
    if (!info)
        return;
    info->subscribeLayer(ContactLayer::EntityObject);
    info->subscribeLayer(ContactLayer::EntityGround);
    info->subscribeLayer(ContactLayer::EntityGroundSmooth);
    info->subscribeLayer(ContactLayer::EntityGroundRough);
    info->subscribeLayer(ContactLayer::EntityGroundObject);
    info->subscribeLayer(ContactLayer::EntityTree);
    info->subscribeLayer(ContactLayer::EntityWater);
}

void Unk_7100928b6c::sub_71009298C4() {
    _11c = -1.0f;
    _120 = -1.0f;
    _124 = -1.0f;
    _140 = 0;
    _128 = 0;
    _141 = 0;
    _142 = 0;
}

void Unk_7100928b6c::sub_710092A83C() {
    _11c = -1.0f;
    _120 = -1.0f;
    _124 = -1.0f;
    _140 = 0;
    _128 = 0;
    _141 = 0;
    _142 = 0;
    _145 = 1;
    _148 = false;
}

}  // namespace uking::act
