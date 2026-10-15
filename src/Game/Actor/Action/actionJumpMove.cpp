#include "Game/Actor/Action/actionJumpMove.h"
#include <cmath>
#include <math/seadMatrix.h>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

JumpMove::JumpMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

JumpMove::~JumpMove() = default;

bool JumpMove::isFinished() const {
    return _8a;
}

bool JumpMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: matrix registers, position copies and stack slots.
void JumpMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    _58 = ksys::Timer(*mPreJumpWait_s, *mPreJumpWait_s, -1.0f);
    _64 = mActor->getMtx().getTranslation();
    const sead::Vector3f forward = controller->get64();
    const f32 limit = *mRandAngleLimit_s;
    sead::Matrix33f rotation;
    rotation.makeR({0.0f, sead::GlobalRandom::instance()->getF32Range(-limit, limit), 0.0f});
    sead::Vector3f direction = forward;
    direction.rotate(rotation);
    sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f candidate = position + direction * 5.0f;
    bool blocked = sub_710072E928(position, candidate, nullptr, nullptr, nullptr, 0.5f);
    if (blocked) {
        rotation.makeR({0.0f, sead::GlobalRandom::instance()->getF32Range(-limit, limit), 0.0f});
        direction = forward;
        direction.rotate(rotation);
        position = mActor->getMtx().getTranslation();
        candidate = position + direction * 5.0f;
        blocked = sub_710072E928(position, candidate, nullptr, nullptr, nullptr, 0.5f);
    }
    if (!blocked) {
        const sead::Vector3f position = candidate + sead::Vector3f::ey * 5.0f;
        somePositionCalc(&_64, position, -sead::Vector3f::ey, 10.0f);
    } else {
        const f32 angle = sead::GlobalRandom::instance()->getF32Range(-2.0f * limit, 2.0f * limit);
        sead::Matrix33f rotation;
        rotation.makeR({0.0f, angle, 0.0f});
        sead::Vector3f direction = -forward;
        direction.rotate(rotation);
        _64 = mActor->getMtx().getTranslation() + direction * 5.0f;
    }
    const f32 height = *mJumpHeight_s;
    _80 = sead::GlobalRandom::instance()->getF32Range(height, height * 1.5f);
    _8a = false;
    _88 = false;
    _89 = false;
    _84 = 0;
    const auto& current_position = mActor->getMtx().getTranslation();
    _70 = {_64.x - current_position.x, 0.0f, _64.z - current_position.z};
    _70.normalize();
    if (_70.x == 0.0f && _70.z == 0.0f) {
        _70 = controller->get64();
        _80 = 0.0f;
        setFailed();
        return;
    }
    _7c = sead::GlobalRandom::instance()->getF32Range(*mMinMoveSpeed_s, *mMaxMoveSpeed_s) * 30.0f;
    controller->sub_7100F5E7F0(0.0f);
    if (!mASKey_s.isEmpty())
        playAS(mASKey_s.cstr(), false, 0, 0, -1.0f);
}

void JumpMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void JumpMove::loadParams_() {
    getStaticParam(&mPreJumpWait_s, "PreJumpWait");
    getStaticParam(&mMaxMoveSpeed_s, "MaxMoveSpeed");
    getStaticParam(&mMinMoveSpeed_s, "MinMoveSpeed");
    getStaticParam(&mRandAngleLimit_s, "RandAngleLimit");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mASKey_s, "ASKey");
}

// NON_MATCHING: direction loads and angle/rotation registers.
void JumpMove::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    const bool grounded = controller->sub_7100F5F14C();
    if (_89 && grounded) {
        _8a = true;
    } else if (!grounded) {
        _89 = true;
    } else if (!_89 && _88 && _84++ >= 5) {
        _88 = false;
        _89 = true;
    }
    _58.update();
    if (_58.hasEnded(0.0f) && _80 > 0.0f) {
        controller->sub_7100F5E7F0(_7c);
        controller->sub_7100F62B70(_80);
        controller->sub_7100F5EF08(true);
        _84 = 0;
        _88 = true;
    }
    sead::Vector3f direction = controller->get64();
    sead::Vector2f horizontal{direction.x, direction.z};
    horizontal.normalize();
    sead::Vector2f target{_70.x, _70.z};
    target.normalize();
    const f32 angle = std::atan2(direction.cross(_70).length(), direction.dot(_70));
    if (angle > sead::Mathf::deg2rad(15.0f)) {
        const f32 turn = horizontal.y * target.x - horizontal.x * target.y >= 0.0f ?
                             sead::Mathf::deg2rad(15.0f) : -sead::Mathf::deg2rad(15.0f);
        sead::Matrix33f rotation;
        rotation.makeR({0.0f, turn, 0.0f});
        direction.rotate(rotation);
    } else {
        direction = _70;
        direction.normalize();
    }
    sub_710072C1B4(controller, direction);
    controller->sub_7100F5FDF0(direction);
}

}  // namespace uking::action
