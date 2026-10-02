#include "Game/AI/Action/actionForkLynelDrawWeaponASPlay.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"

namespace uking::action {

ForkLynelDrawWeaponASPlay::ForkLynelDrawWeaponASPlay(const InitArg& arg)
    : ForkLynelDrawWeapon(arg) {}

ForkLynelDrawWeaponASPlay::~ForkLynelDrawWeaponASPlay() = default;

bool ForkLynelDrawWeaponASPlay::init_(sead::Heap* heap) {
    return ForkLynelDrawWeapon::init_(heap);
}

// NON_MATCHING: the two argument registers are set up in the other order (scheduling)
void ForkLynelDrawWeaponASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkLynelDrawWeapon::enter_(params);
    if (auto* rideable = mActor->m132())
        rideable->_18.sub_7100E786F0(mASName_s);
}

void ForkLynelDrawWeaponASPlay::leave_() {
    ForkLynelDrawWeapon::leave_();
}

void ForkLynelDrawWeaponASPlay::loadParams_() {
    ForkLynelDrawWeapon::loadParams_();
}

void ForkLynelDrawWeaponASPlay::calc_() {
    ForkLynelDrawWeapon::calc_();
}

}  // namespace uking::action
