#include "Game/AI/Action/actionGetUpLinear.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

GetUpLinear::GetUpLinear(const InitArg& arg) : GetUpBase(arg) {}

GetUpLinear::~GetUpLinear() = default;

bool GetUpLinear::init_(sead::Heap* heap) {
    return GetUpBase::init_(heap);
}

void GetUpLinear::enter_(ksys::act::ai::InlineParamPack* params) {
    GetUpBase::enter_(params);
    _150 = 0;
}

// NON_MATCHING: same operations as the original but the 3x3 product / sum scheduling differs (register allocation)
void GetUpLinear::leave_() {
    GetUpBase::leave_();
    auto* controller = mActor->getCharacterController();
    auto* body = mActor->findPhysicsBodyByName("Ragdoll", "Base");
    if (controller && body) {
        f32 half_height = 0.5f;
        controller->sub_7100F62EC0(&half_height, 0);
        sead::Matrix34f mtx;
        controller->physicsXXXGetMtx_1(&mtx);
        sead::Vector3f offset = half_height * sead::Vector3f::ey;
        offset.rotate(mtx);
        mtx.setTranslation(mtx.getTranslation() + offset);
        body->setTransform(mtx);
    }
}

void GetUpLinear::loadParams_() {
    GetUpBase::loadParams_();
    getStaticParam(&mRotCenterPos_s, "RotCenterPos");
}

void GetUpLinear::calc_() {
    GetUpBase::calc_();
}

// NON_MATCHING: scheduling of the two rotations (the original loads mActor first) and the MotionType compare
// goes through a stack slot in the original
void GetUpLinear::m32(ksys::phys::CharacterController* controller) {
    sead::Vector3f from = *mRotCenterPos_s;
    from.rotate(_44);
    sead::Vector3f to = *mRotCenterPos_s;
    to.rotate(mActor->getMtx());
    sead::Vector3f velocity = to - from;
    const ksys::act::MotionType motion_type = controller->sub_7100F5F0E4();
    if (motion_type != ksys::act::MotionType::Hover)
        velocity.y += mActor->getVelocity().y;
    sub_7100737710(controller, velocity);
}

bool GetUpLinear::m33() {
    if (!GetUpBase::m33())
        return false;
    sead::Vector3f dir;
    mActor->getMtx().getBase(dir, 1);
    dir.normalize();
    sead::Vector3f axis;
    f32 angle = 0.0f;
    ksys::util::sub_71011EEB08(&axis, &angle, dir, sead::Vector3f::ey, sead::Vector3f::ey);
    _150 = _40 > 0.0f ? angle / _40 : angle;
    if (mActor->getMtx()(1, 2) >= 0.0f)
        _154 = -dir;
    else
        _154 = dir;
    return true;
}

bool GetUpLinear::m34() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return true;
    if (_68.value <= sead::Mathf::epsilon()) {
        sub_71007419B4(&_44, getUpDir(controller->get70()));
        sub_71007419F4(_44, controller);
        return true;
    }
    sub_710074191C(&_44, _154, getUpDir(controller->get70()), true, _150);
    _68.update();
    sub_71007419F4(_44, controller);
    return false;
}

}  // namespace uking::action
