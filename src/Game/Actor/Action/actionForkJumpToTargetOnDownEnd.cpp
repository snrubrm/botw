#include "Game/Actor/Action/actionForkJumpToTargetOnDownEnd.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71007377D4.h"

namespace uking::action {

ForkJumpToTargetOnDownEnd::ForkJumpToTargetOnDownEnd(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkJumpToTargetOnDownEnd::~ForkJumpToTargetOnDownEnd() = default;

bool ForkJumpToTargetOnDownEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: stack layout (the jump speed / time floats sit at the frame top in the original) and the
// order of the landing-point copies.
void ForkJumpToTargetOnDownEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    _68 = *mParams.mTargetPos_d;
    _68 -= pos;
    _68.y = 0.0f;
    const f32 distance = _68.normalize();

    sead::Vector3f end;
    if (!*mParams.mIsBasisByTarget_s) {
        end = pos;
        end += _68 * *mParams.mJumpDist_s * 2.0f;
    } else if (distance + *mParams.mJumpDist_s < *mParams.mJumpMinDist_s) {
        end = pos + _68 * *mParams.mJumpMinDist_s;
    } else {
        end = *mParams.mTargetPos_d;
        end.y = pos.y;
        end.x += *mParams.mJumpDist_s * _68.x;
        end.z += *mParams.mJumpDist_s * _68.z;
    }

    if (*mParams.mOnGround_s) {
        f32 height;
        if (!*mParams.mIsBasisByTarget_s && sub_710072C21C(&height, &end))
            end.y = height;
        else if (*mParams.mIsBasisByTarget_s)
            somePositionCalc(&end, end, -sead::Vector3f::ey, 50.0f);
        else
            somePositionCalc(&end, end, -sead::Vector3f::ey, 25.0f);
    }

    if (auto* controller = mActor->getCharacterController()) {
        f32 time = 0;
        f32 speed = 0;
        sead::Vector3f gravity = getGravity(mActor);
        gravity *= 1.0f / 900.0f;
        sub_710072CD88(*mParams.mJumpHeight_s, &speed, &time, &pos, &end, &gravity);
        _74.value = _74.prev_value = speed;
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5E7F0(speed);
        const f32 angle = *mParams.mAngleDir_s;
        if (!sead::Mathf::equalsEpsilon(angle, 0.0f)) {
            sead::Matrix33f rotation;
            rotation.makeR({0, angle, 0});
            _68.rotate(rotation);
        }
        sub_710072C1B4(controller, _68);
        controller->sub_7100F62B70(*mParams.mJumpHeight_s);
        controller->sub_7100F5EF08(true);
    }
    _80 = true;
    _81 = false;
}

void ForkJumpToTargetOnDownEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkJumpToTargetOnDownEnd::loadParams_() {
    getStaticParam(&mParams.mAngleDir_s, "AngleDir");
    getStaticParam(&mParams.mJumpDist_s, "JumpDist");
    getStaticParam(&mParams.mJumpHeight_s, "JumpHeight");
    getStaticParam(&mParams.mLimitSpeed_s, "LimitSpeed");
    getStaticParam(&mParams.mEndGrSpeed_s, "EndGrSpeed");
    getStaticParam(&mParams.mJumpMinDist_s, "JumpMinDist");
    getStaticParam(&mParams.mOnGround_s, "OnGround");
    getStaticParam(&mParams.mIsBasisByTarget_s, "IsBasisByTarget");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void ForkJumpToTargetOnDownEnd::calc_() {
    if (_80) {
        _80 = false;
        return;
    }

    auto* actor = mActor;
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F5E7F0(_74.value * 30.0f);
        sub_710072C1B4(controller, _68);
    }

    if (actor->getVelocity().y > *mParams.mEndGrSpeed_s)
        _81 = true;
    if ((_81 && actor->getVelocity().y <= *mParams.mEndGrSpeed_s) || isBgGroundHit(actor, false))
        setFinished();
}

}  // namespace uking::action
