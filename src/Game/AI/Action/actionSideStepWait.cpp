#include "Game/AI/Action/actionSideStepWait.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SideStepWait::SideStepWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SideStepWait::~SideStepWait() = default;

void SideStepWait::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    f32 speed = 0.0f;
    if (auto* controller = mActor->getCharacterController())
        speed = -controller->get70().length() * controller->get110();
    _b4 = speed;
    f32 gravity_scale = 0.0f;
    if (auto* controller = mActor->getCharacterController())
        gravity_scale = controller->sub_7100F62B78();
    _b8 = gravity_scale;
    _bd = true;
    playAS("BattleWait", false, 0, 0, -1.0f);
    _bc = 0;
}

// NON_MATCHING: operand order of the normalisation multiplies (`s10 * s0` in the original)
void SideStepWait::leave_() {
    const f32 speed = _b4;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f dir;
        dir.set(controller->get70());
        dir.normalize();
        dir.multScalar(-speed);
        controller->sub_7100F5EE1C(dir);
    }
    const f32 gravity_scale = _b8;
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62B70(gravity_scale);
}

void SideStepWait::loadParams_() {
    getStaticParam(&mParams.mFirstStepDist_s, "FirstStepDist");
    getStaticParam(&mParams.mSecondStepDist_s, "SecondStepDist");
    getStaticParam(&mParams.mThirdStepDist_s, "ThirdStepDist");
    getStaticParam(&mParams.mFourthStepDist_s, "FourthStepDist");
    getStaticParam(&mParams.mGravity_s, "Gravity");
    getStaticParam(&mParams.mFirstStepHeight_s, "FirstStepHeight");
    getStaticParam(&mParams.mSecondStepHeight_s, "SecondStepHeight");
    getStaticParam(&mParams.mThirdStepHeight_s, "ThirdStepHeight");
    getStaticParam(&mParams.mFourthStepHeight_s, "FourthStepHeight");
    getStaticParam(&mParams.mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mParams.mStopRotSpeedRatio_s, "StopRotSpeedRatio");
}

void SideStepWait::calc_() {
    switch (_bc) {
    case 0:
        sub_7100738428(mActor, *mParams.mStopSpeedRatio_s);
        sub_7100738AA8(mActor, *mParams.mStopRotSpeedRatio_s);
        if (mActor->getASList()->x(0x44, nullptr, 0, 0,
                                  &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            sub_710025384C(*mParams.mFirstStepDist_s, *mParams.mFirstStepHeight_s);
            _bc = 1;
        }
        _bd = true;
        break;
    case 1:
        if (isBgGroundHit(mActor, false))
            _bc = 2;
        _bd = false;
        break;
    case 2:
        sub_7100738428(mActor, *mParams.mStopSpeedRatio_s);
        sub_7100738AA8(mActor, *mParams.mStopRotSpeedRatio_s);
        if (mActor->getASList()->x(0x44, nullptr, 0, 0,
                                  &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            sub_710025384C(*mParams.mSecondStepDist_s, *mParams.mSecondStepHeight_s);
            _bc = 3;
        }
        _bd = true;
        break;
    case 3:
        if (isBgGroundHit(mActor, false))
            _bc = 4;
        _bd = false;
        break;
    case 4:
        sub_7100738428(mActor, *mParams.mStopSpeedRatio_s);
        sub_7100738AA8(mActor, *mParams.mStopRotSpeedRatio_s);
        if (mActor->getASList()->x(0x44, nullptr, 0, 0,
                                  &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            sub_710025384C(*mParams.mThirdStepDist_s, *mParams.mThirdStepHeight_s);
            _bc = 5;
        }
        _bd = true;
        break;
    case 5:
        if (isBgGroundHit(mActor, false))
            _bc = 6;
        _bd = false;
        break;
    case 6:
        sub_7100738428(mActor, *mParams.mStopSpeedRatio_s);
        sub_7100738AA8(mActor, *mParams.mStopRotSpeedRatio_s);
        if (mActor->getASList()->x(0x44, nullptr, 0, 0,
                                  &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            sub_710025384C(*mParams.mFourthStepDist_s, *mParams.mFourthStepHeight_s);
            _bc = 7;
        }
        _bd = true;
        break;
    case 7:
        if (isBgGroundHit(mActor, false))
            _bc = 0;
        _bd = false;
        break;
    }
}

bool SideStepWait::isChangeable() const {
    return _bd;
}

// NON_MATCHING: normalisation multiply operand order and vector math register allocation.
void SideStepWait::sub_710025384C(f32 distance, f32 height) {
    const f32 gravity = *mParams.mGravity_s;
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f direction = controller->get70();
        direction.normalize();
        direction.multScalar(-gravity);
        controller->sub_7100F5EE1C(direction);
    }
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F62B70(height);

    sead::Vector3f target = mActor->getMtx().getBase(0);
    target.multScalar(distance);
    target += mActor->getMtx().getTranslation();
    sead::Vector3f velocity;
    sub_71005DF66C(&velocity, mActor, &target, nullptr, height, *mParams.mGravity_s / 900.0f);
    const f32 speed = velocity.normalize();
    _78.value = speed;
    _78.prev_value = speed;
    _78.updateStats();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5E7F0(_78.value * 30.0f);
        sub_710072C1B4(controller, velocity);
        controller->sub_7100F5EF08(true);
    }
}

}  // namespace uking::action
