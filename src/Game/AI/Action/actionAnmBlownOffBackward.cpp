#include "Game/AI/Action/actionAnmBlownOffBackward.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

AnmBlownOffBackward::AnmBlownOffBackward(const InitArg& arg) : AnmBlownOff(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
AnmBlownOffBackward::~AnmBlownOffBackward() {
    ;
}

bool AnmBlownOffBackward::init_(sead::Heap* heap) {
    return AnmBlownOff::init_(heap);
}

void AnmBlownOffBackward::enter_(ksys::act::ai::InlineParamPack* params) {
    AnmBlownOff::enter_(params);
    sub_710073FA90(&_a4, mActor);
}

void AnmBlownOffBackward::leave_() {
    AnmBlownOff::leave_();
}

void AnmBlownOffBackward::loadParams_() {
    AnmBlownOff::loadParams_();
}

void AnmBlownOffBackward::calc_() {
    AnmBlownOff::calc_();
}

void AnmBlownOffBackward::m32(ksys::phys::CharacterController* controller) {
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    if (velocity.x == 0 && velocity.z == 0) {
        AnmBlownOff::m32(controller);
        return;
    }

    sead::Vector3f dir = velocity;
    dir.y = 0;
    dir.negate();
    dir.normalize();
    const sead::Vector3f up = -controller->get7c();
    sub_710073FA94(&_a4, mActor);
    sub_71007407F0(&_a4, dir, up, true, sead::Mathf::pi() / 6);
    sub_7100740E04(_a4, controller);
}

}  // namespace uking::action
