#include "Game/AI/Action/actionLynelDrawWeapon.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LynelDrawWeapon::LynelDrawWeapon(const InitArg& arg) : ForkLynelDrawWeaponASPlay(arg) {}

LynelDrawWeapon::~LynelDrawWeapon() = default;

bool LynelDrawWeapon::init_(sead::Heap* heap) {
    return ForkLynelDrawWeaponASPlay::init_(heap);
}

void LynelDrawWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkLynelDrawWeaponASPlay::enter_(params);
}

void LynelDrawWeapon::leave_() {
    ForkLynelDrawWeaponASPlay::leave_();
}

void LynelDrawWeapon::loadParams_() {
    ForkLynelDrawWeaponASPlay::loadParams_();
}

void LynelDrawWeapon::calc_() {
    ForkLynelDrawWeaponASPlay::calc_();
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    auto* rideable = mActor->m132();
    if (as_list && controller && rideable)
        uking::act::sub_7100E7F698(rideable, as_list, controller);
}

}  // namespace uking::action
