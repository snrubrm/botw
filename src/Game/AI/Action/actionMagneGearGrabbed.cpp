#include "Game/AI/Action/actionMagneGearGrabbed.h"
#include <limits>
#include <math/seadQuat.h>
#include "Game/gameSceneSubsysMisc.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

MagneGearGrabbed::MagneGearGrabbed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MagneGearGrabbed::~MagneGearGrabbed() = default;

bool MagneGearGrabbed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original loads _1c first and stores the two 60.0f floats as one 64-bit constant (ours: stp w8, w8)
void MagneGearGrabbed::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = ksys::Timer(60.0f, 60.0f);
    _34 = false;
    if (_1c) {
        if (auto* body = mActor->getMainBody())
            body->changeMotionType(ksys::phys::MotionType::Dynamic);
        _1c = 0;
    }
    mFlags.set(Flag::Changeable);
}

void MagneGearGrabbed::leave_() {
    if (_1c) {
        if (auto* body = mActor->getMainBody())
            body->changeMotionType(ksys::phys::MotionType::Dynamic);
        _1c = 0;
    }
    if (isActorDeletedOrDeleting()) {
        if (auto* scene = GameSceneSubsys5::instance())
            scene->sub_7100905C70();
    }
}

void MagneGearGrabbed::loadParams_() {
    getStaticParam(&mConnectDistance_s, "ConnectDistance");
}

void MagneGearGrabbed::calc_() {
    if (!(_28.value <= sead::Mathf::epsilon()))
        _28.update();
    if (!(_28.value <= sead::Mathf::epsilon()))
        return;
    sub_71001E4DDC();
    sub_71001E501C();
}

// NON_MATCHING: paired matrix component loads and accessor cleanup scheduling differ.
void MagneGearGrabbed::sub_71001E4DDC() {
    auto* actor = mActor;
    const sead::Vector3f position = actor->getMtx().getTranslation();
    s32 index = 0;
    ksys::act::ActorConstDataAccess closest;
    if (auto* object = ksys::act::findLinkReferenceObj(actor, "MagneGearAcceptor", "", &index)) {
        f32 closest_sq_distance = std::numeric_limits<f32>::max();
        do {
            ksys::act::ActorConstDataAccess accessor;
            object->getActorWithAccessor(accessor);
            const f32 sq_distance = (accessor.getActorMtx().getTranslation() - position).squaredLength();
            if (sq_distance < closest_sq_distance) {
                closest.acquireActor(accessor);
                closest_sq_distance = sq_distance;
            }
            ++index;
        } while ((object = ksys::act::findLinkReferenceObj(actor, "MagneGearAcceptor", "", &index)));
        if (closest.hasProc()) {
            _34 = true;
            const auto& matrix = closest.getActorMtx();
            sead::Vector3f front = matrix.getBase(2);
            const sead::Vector3f target_position = matrix.getTranslation();
            if (actor->getMtx().getBase(2).dot(front) < 0.0f)
                front = -front;
            front.normalize();
            ksys::util::sub_71011F0260(&_38, front, sead::Vector3f::ey, target_position, false);
            return;
        }
    }
    _34 = false;
}

// NON_MATCHING: matrix/axis stack storage and motion-reset block folding differ.
void MagneGearGrabbed::sub_71001E501C() {
    if (!_34) {
        if (_1c) {
            if (auto* body = mActor->getMainBody())
                body->changeMotionType(ksys::phys::MotionType::Dynamic);
            _1c = 0;
        }
        return;
    }
    const sead::Matrix34f current = mActor->getMtx();
    const sead::Vector3f position = current.getTranslation();
    const sead::Vector3f difference = _38.getTranslation() - position;
    if (!(difference.length() > *mConnectDistance_s)) {
        if (_1c != 1) {
            if (auto* body = mActor->getMainBody())
                body->changeMotionType(ksys::phys::MotionType::Keyframed);
            _1c = 1;
        }
        sead::Vector3f axis = sead::Vector3f::ey;
        f32 angle = 0.0f;
        ksys::util::sub_71011EF51C(&axis, &angle, current, _38, sead::Vector3f::ey);
        const f32 max_angle = ksys::VFR::instance()->getDeltaFrame() * 0.10471976f;
        sead::Quatf quaternion;
        quaternion.setAxisRadian(axis, angle <= sead::Mathf::abs(max_angle) ? angle : max_angle);
        sead::Matrix34f rotation;
        rotation.fromQuat(quaternion);
        sead::Matrix34f result;
        result.setMul(current, rotation);
        result.setTranslation(position + difference *
            (1.0f - std::pow(0.5f, ksys::VFR::instance()->getDeltaFrame())));
        if (auto* body = mActor->getMainBody())
            body->changePositionAndRotation(result, sead::Mathf::epsilon());
    } else if (_1c) {
        if (auto* body = mActor->getMainBody())
            body->changeMotionType(ksys::phys::MotionType::Dynamic);
        _1c = 0;
    }
}

// NON_MATCHING: return block order and matrix argument setup differ.
bool MagneGearGrabbed::isFinished() const {
    if (!mFlags.isOn(Flag::Finished)) {
        if (_28.value <= sead::Mathf::epsilon() && _34 &&
            (_38.getTranslation() - mActor->getMtx().getTranslation()).length() <
                *mConnectDistance_s * 0.1f) {
            sead::Vector3f axis = sead::Vector3f::ey;
            f32 angle = 0.0f;
            ksys::util::sub_71011EF51C(&axis, &angle, mActor->getMtx(), _38, sead::Vector3f::ey);
            return sead::Mathf::abs(angle) <= 0.08726646f;
        }
        return false;
    }
    return true;
}

}  // namespace uking::action
