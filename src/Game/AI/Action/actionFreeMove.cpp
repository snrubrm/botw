#include "Game/AI/Action/actionFreeMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

// NON_MATCHING: store scheduling of the zero-initialised members
FreeMove::FreeMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FreeMove::~FreeMove() = default;

bool FreeMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original passes the motion type through the stack (MotionType is probably a
// SEAD_ENUM in the original; it is a plain enum class in actCCAccessor.h)
void FreeMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    _a0 = controller->sub_7100F5F0E4();
    if (controller->sub_7100F5F0E4() != ksys::act::MotionType::Hover)
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);

    mActor->getMtx().getTranslation(_1c);
    _28 = {0, 0, 1};

    if (m32(controller))
        playAS(mASKeyName_s.cstr(), *mIsIgnoreSameAS_s, 0, 0, -1.0f);
    else
        setFailed();
    _40 = 0;
}

void FreeMove::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(_a0);
}

void FreeMove::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mSpeedAddRate_s, "SpeedAddRate");
    getStaticParam(&mAngleSpeed_s, "AngleSpeed");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mAllowPitchRotation_s, "AllowPitchRotation");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void FreeMove::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (m34()) {
        setFinished();
        return;
    }
    if (m35()) {
        setFailed();
        return;
    }
    ++_40;
    m33(controller);
}

bool FreeMove::isChangeable() const {
    return *mIsChangeable_s;
}

bool FreeMove::m32(ksys::phys::CharacterController* controller) {
    if (!controller)
        return false;
    _28 = controller->get64();
    const f32 speed = controller->sub_7100F5EF00();
    _34.value = speed;
    _34.prev_value = speed;
    return true;
}

bool FreeMove::m34() {
    return true;
}

bool FreeMove::m35() {
    return false;
}

f32 FreeMove::m36() {
    return *mSpeed_s;
}

void FreeMove::m37(f32 speed, ksys::phys::CharacterController* controller) {
    const f32 target = speed * 30.0f;
    _34.lerp(target, *mSpeedAddRate_s, target, 0.005f);
    controller->sub_7100F5E7F0(_34.value);
}

}  // namespace uking::action
