#include "Game/AI/Action/actionTakeoffFromCeilLook.h"
#include <cmath>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

TakeoffFromCeilLook::TakeoffFromCeilLook(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TakeoffFromCeilLook::~TakeoffFromCeilLook() = default;

bool TakeoffFromCeilLook::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TakeoffFromCeilLook::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710073FA90(&_50, mActor);
    playAS("WaitEnd", false, 0, 0, -1.0f);
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    actor->getMtx().getBase(_74, 2);
    _74 = -_74;
    ksys::util::sub_71011EFA00(&_74, _74, controller->get7c());
    _74.normalize();
}

void TakeoffFromCeilLook::leave_() {
    ksys::act::ai::Action::leave_();
}

void TakeoffFromCeilLook::loadParams_() {
    getStaticParam(&mDescentSpeed_s, "DescentSpeed");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
}

// NON_MATCHING: the original keeps the scaled velocity in registers (s12-s14) across the powf call
// (the reload only happens on the out-of-line getDeltaFrame path);
// ours reloads it from the stack after the call (the vector's address escaped through sub_7100F5F598)
void TakeoffFromCeilLook::calc_() {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    if (auto* as_list = actor->getASList()) {
        if (as_list->x(0x2f, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
            const sead::Vector3f target_vel = *mDescentSpeed_s * controller->get7c();
            sead::Vector3f velocity;
            controller->sub_7100F5F598(&velocity);
            velocity = velocity * (1.0f / 30);
            ksys::VFR::lerp(&velocity, target_vel, *mAccRatio_s);
            sub_7100737710(controller, velocity);
        } else {
            sub_71007377D4(controller, *mPosReduceRatio_s);
        }
        if (as_list->x(0x29, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
            sub_710073FA94(&_50, actor);
            const sead::Vector3f up = getUpDir(actor);
            sub_710074006C(&_50, _74, up, true, *mRotRatio_s, *mRotSpeed_s, 0.0f);
            sub_7100740E04(_50, controller);
        } else {
            sub_7100738660(controller, *mRotReduceRatio_s);
        }
    }
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
