#include "Game/AI/Behavior/behaviorPlayerParasailAltitude.h"
#include <math/seadMathCalcCommon.h>
#include <xlink2/xlink2UserInstanceELink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::behavior {

PlayerParasailAltitude::PlayerParasailAltitude(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

PlayerParasailAltitude::~PlayerParasailAltitude() = default;

bool PlayerParasailAltitude::m6(sead::Heap* heap) {
    return true;
}

void PlayerParasailAltitude::loadParams() {

}

void PlayerParasailAltitude::m8() {
    _30 = 0;
    mActor->getXLink()->_50->setPropertyValue(31, _30);
    mActor->getXLink()->_48->setPropertyValue(31, _30);

    _28 = ksys::phys::RayCastForRequest::allocRequest();
    if (_28) {
        _28->enableLayer(ksys::phys::ContactLayer::EntityGround);
        _28->enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        _28->enableLayer(ksys::phys::ContactLayer::EntityWater);
    }
    if (_28) {
        mActor->getMtx().getTranslation(_34);
        _28->setStartAndDisplacement(_34, {0, -50, 0});
        _28->submitRequest(ksys::phys::ContactLayerType::Entity);
    }
    _44 = true;
}

void PlayerParasailAltitude::m7() {
    if (!_28) {
        _28 = ksys::phys::RayCastForRequest::allocRequest();
        if (_28) {
            _28->enableLayer(ksys::phys::ContactLayer::EntityGround);
            _28->enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
            _28->enableLayer(ksys::phys::ContactLayer::EntityWater);
        }
        if (!_28) {
            ++_40;
            return;
        }
    }

    if (_28->get70() != 1) {
        ++_40;
        return;
    }

    f32 altitude;
    if (_28->hasHit()) {
        sead::Vector3f hit_pos;
        _28->getHitPosition(&hit_pos);
        altitude = (_34 - hit_pos).length();
    } else {
        altitude = 50.0f;
    }

    if (_44) {
        _30 = altitude;
        _44 = false;
    } else {
        const f32 diff = altitude - _30;
        const f32 max_step = _40;
        if (sead::Mathf::abs(diff) < max_step)
            _30 = altitude;
        else
            _30 += diff > 0 ? max_step : -max_step;
    }

    _28->resetCastResult();
    _40 = 1;
    mActor->getXLink()->_50->setPropertyValue(31, _30);
    mActor->getXLink()->_48->setPropertyValue(31, _30);
    mActor->getMtx().getTranslation(_34);
    _28->setStartAndDisplacement(_34, {0, -50, 0});
    _28->submitRequest(ksys::phys::ContactLayerType::Entity);
}

void PlayerParasailAltitude::m9() {
    _28->release();
    _30 = 0;
    mActor->getXLink()->_50->setPropertyValue(31, _30);
    mActor->getXLink()->_48->setPropertyValue(31, _30);
}

}  // namespace uking::behavior
