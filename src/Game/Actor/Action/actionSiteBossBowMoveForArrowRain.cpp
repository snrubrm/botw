#include "Game/Actor/Action/actionSiteBossBowMoveForArrowRain.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

SiteBossBowMoveForArrowRain::SiteBossBowMoveForArrowRain(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossBowMoveForArrowRain::~SiteBossBowMoveForArrowRain() = default;

bool SiteBossBowMoveForArrowRain::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original adds the translation after the rotated vector (t + (R * v)) with the
// translation loaded first; Matrix34 * Vector3 adds it inside the product.
void SiteBossBowMoveForArrowRain::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _58 = 0.0f;
    _5c = mActor->getMtx() * *mMoveTarget_s;
    _68 = 0.0f;
    _6c = 120.0f;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5FB24(sead::Vector3f::zero);
}

void SiteBossBowMoveForArrowRain::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

void SiteBossBowMoveForArrowRain::loadParams_() {
    getStaticParam(&mFirstMoveSpeed_s, "FirstMoveSpeed");
    getStaticParam(&mFirstAccelFrame_s, "FirstAccelFrame");
    getStaticParam(&mSecondMoveSpeed_s, "SecondMoveSpeed");
    getStaticParam(&mSecondAccelFrame_s, "SecondAccelFrame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mMoveTarget_s, "MoveTarget");
}

// NON_MATCHING: parameter loads, direction registers and final add operands differ.
void SiteBossBowMoveForArrowRain::calc_() {
    ksys::Timer::update(&_68, 1.0f);
    ksys::Timer::update(&_6c, -1.0f);
    if (_6c < 0.0f) {
        setFailed();
        return;
    }
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    sead::Vector3f direction = _5c - position;
    const f32 distance = direction.normalize();
    if (distance < _58) {
        controller->sub_7100F5FBE0(_5c);
        setFinished();
        return;
    }
    const f32 first_frames = *mFirstAccelFrame_s;
    if (_68 < first_frames) {
        if (first_frames > 0.0f)
            sead::Mathf::chase(&_58, *mFirstMoveSpeed_s, *mFirstMoveSpeed_s / first_frames);
    } else {
        const f32 second_frames = *mSecondAccelFrame_s;
        if (_68 < first_frames + second_frames) {
            if (second_frames > 0.0f)
                sead::Mathf::chase(&_58, *mSecondMoveSpeed_s, *mSecondMoveSpeed_s / second_frames);
        } else if (distance < _58 * 8.0f) {
            const f32 target = *mFirstMoveSpeed_s;
            const f32 difference = target - _58;
            const f32 magnitude = sead::Mathf::abs(difference);
            if (magnitude <= 0.01f) {
                _58 = target;
            } else {
                const f32 max_step = _58 * 0.5f;
                f32 step = difference * 0.33f;
                if (magnitude * 0.33f > max_step)
                    step = difference < 0.0f ? -max_step : max_step;
                else if (magnitude * 0.33f < 0.01f)
                    step = difference < 0.0f ? -0.01f : 0.01f;
                _58 += step;
            }
        } else {
            _58 = *mSecondMoveSpeed_s;
        }
    }
    controller->sub_7100F5FBE0(position + direction * _58);
}

}  // namespace uking::action
