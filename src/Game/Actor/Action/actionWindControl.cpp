#include "Game/Actor/Action/actionWindControl.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

WindControl::WindControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}


bool WindControl::init_(sead::Heap* heap) {
    _118.sub_71010C42B4();
    if (mActor) {
        if (mActor->getName() == "WindGeneratorLength")
            _118._80 = true;
    }
    return true;
}

void WindControl::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _110 = actor->hasPlacementLinkForBasicSig() ? 0.0f : *mMaxRadSpeed_s;
    if (!mTargetNodeName_s.isEmpty() && !_20._8) {
        _20.setName(mTargetNodeName_s);
        actor->boneHandleStuff(&_20, false);
    }
    _1a0 = 0.1f;
    _1a4 = 1.0f;
}

void WindControl::leave_() {
    if (_20._8)
        mActor->sub_71011DA868(&_20);
    _118.destroy(false);
}

void WindControl::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mMaxRadSpeed_s, "MaxRadSpeed");
    getStaticParam(&mRadAccel_s, "RadAccel");
    getStaticParam(&mTemperature_s, "Temperature");
    getStaticParam(&mUseEnvTemperature_s, "UseEnvTemperature");
    getStaticParam(&mIsModelControlOnly_s, "IsModelControlOnly");
    getStaticParam(&mTargetNodeName_s, "TargetNodeName");
}

// NON_MATCHING: vector temporaries and matrix stores use different registers and stack slots;
// clang retains the actor member address across the raycast and wind update.
void WindControl::calc_() {
    if (!*mIsModelControlOnly_s) {
        const f32 radius = *mRadius_s;
        const f32 speed = *mMaxSpeed_s * 30.0f * (_110 / *mMaxRadSpeed_s);
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        const sead::Vector3f direction = mActor->getMtx().getBase(2);
        {
            ksys::phys::RayCastBodyQuery ray(nullptr, ksys::phys::GroundHit::HitAll);
            ray.setGroundHit(ksys::phys::GroundHit::HitAll);
            ray.enableLayer(ksys::phys::ContactLayer::EntityGround);
            ray.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
            ray.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
            const sead::Vector3f start = position + direction * _1a0;
            _1a0 += 9.0f;
            const sead::Vector3f end = direction * (_1a0 + 1.0f) + position;
            ray.setStart(start);
            ray.setEnd(end);
            if (ray.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
                sead::Vector3f hit;
                ray.getHitPosition(&hit);
                _1a4 = (hit - position).length();
                _1a0 = 0.1f;
            } else if (_1a4 < _1a0) {
                _1a4 = _1a0;
            }
            _1a4 = m32(_1a4);
        }
        if (speed > 0.0f)
            _118.sub_71010C449C(_1a4, radius, speed, mActor->getMtx());
        else
            _118.destroy(false);
        if (_1a0 > 200.0f)
            _1a0 = 0.1f;
    }

    const f32 target = !mActor->hasPlacementLinkForBasicSig() || mActor->checkBasicSig() ?
                           *mMaxRadSpeed_s : 0.0f;
    const bool reached = ksys::VFR::chase(&_110, target, *mRadAccel_s);
    if (_20._8)
        _20._68.makeR({0, 0, _110});
    if (mActor->hasPlacementLinkForBasicSig() && !mActor->checkBasicSig() && reached)
        setFinished();
}

bool WindControl::hasUpdateForPreDeleteCb() {
    return true;
}

bool WindControl::updateForPreDelete() {
    return _118.sub_71010C4284();
}

}  // namespace uking::action
