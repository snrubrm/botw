#include "Game/Actor/Action/actionTornadoMove.h"
#include <cmath>
#include "KingSystem/System/VFR.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

TornadoMove::TornadoMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TornadoMove::~TornadoMove() = default;

bool TornadoMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TornadoMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _64 = ksys::Timer(*mDeleteTimer_s, *mDeleteTimer_s);
    _58 = ksys::Timer(*mIgnoreHitFrame_s, *mIgnoreHitFrame_s);
    _a4 = ksys::Timer(0.0f, 0.0f, 1.0f);
    _70 = *mMinAmplitude_s;
    const sead::Matrix34f transform = mActor->getMtx();
    const sead::Vector3f translation = transform.getTranslation();
    const sead::Matrix33f rotation(transform);
    _98 = translation;
    _74 = rotation;
    if (auto* body = mActor->getMainBody())
        body->setGravityFactor(0.0f);
}

void TornadoMove::leave_() {
    if (_b0 && _b0->isAddedToWorld()) {
        _b0->removeFromWorld();
        _b0 = nullptr;
    }
}

void TornadoMove::loadParams_() {
    getStaticParam(&mMaxAmplitude_s, "MaxAmplitude");
    getStaticParam(&mMinAmplitude_s, "MinAmplitude");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mAmplitudeAddRate_s, "AmplitudeAddRate");
    getStaticParam(&mDeleteTimer_s, "DeleteTimer");
    getStaticParam(&mFrequency_s, "Frequency");
    getStaticParam(&mIgnoreHitFrame_s, "IgnoreHitFrame");
}

// NON_MATCHING: float scheduling of the rotated forward step and the side wave.
void TornadoMove::calc_() {
    sead::Mathf::chase(&_70, *mMaxAmplitude_s,
                       *mAmplitudeAddRate_s * ksys::VFR::instance()->getDeltaFrame());

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f move = sead::Vector3f(0, 0, *mMaxSpeed_s) * _a4.value;
    move.rotate(_74);
    sead::Vector3f side;
    side.setCross(move, sead::Vector3f::ey);
    side.normalize();
    const f32 wave = std::sin(_a4.value * *mFrequency_s) * _70;
    _a4.update();
    sead::Vector3f dir = side * wave + move + _98 - pos;
    f32 distance = dir.normalize();
    distance = sead::Mathf::min(distance, *mMaxSpeed_s + _70 * 0.05f);
    const sead::Matrix34f mtx(
        _74, {pos.x + dir.x * distance, _98.y, pos.z + dir.z * distance});
    if (auto* body = mActor->getMainBody())
        body->changePositionAndRotation(mtx);
    if (_b0 && _b0->isAddedToWorld())
        _b0->setTransform(mtx);

    _58.update();
    if (_58.value <= sead::Mathf::epsilon() && !_b0) {
        _b0 = mActor->findPhysicsBodyByName(sub_71007A250C()->cstr(), "BgSensor");
        if (_b0 && !_b0->isAddedToWorld()) {
            _b0->setTransform(mtx);
            _b0->addToWorld();
            _b0->setFlag1000000();
            _b0->setGravityFactor(0.0f);
        }
    }

    if ((_58.value <= sead::Mathf::epsilon() && _b0 && _b0->getCollisionInfo() &&
         _b0->getCollisionInfo()->getCollidingBodies().size() != 0) ||
        hasAttackInfo(mActor) || (_64.update(), _64.value <= sead::Mathf::epsilon())) {
        setFinished();
    }
}

}  // namespace uking::action
