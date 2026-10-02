#include "Game/AI/Action/actionThrowWeaponRight.h"

namespace uking::action {

ThrowWeaponRight::ThrowWeaponRight(const InitArg& arg) : ThrowWeapon(arg) {}

ThrowWeaponRight::~ThrowWeaponRight() = default;

void ThrowWeaponRight::m33() {
    playAS("ThrowRight", false, 0, 0, -1.0f);
}

}  // namespace uking::action
