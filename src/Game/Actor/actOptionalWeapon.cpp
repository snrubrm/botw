#include "Game/Actor/actOptionalWeapon.h"
#include <basis/seadNew.h>

namespace uking::act {

// NON_MATCHING: store schedule only (the original loads the cElementMax address after the second string's
// terminator store)
OptionalWeapon::OptionalWeapon(const CreateArg& arg) : Actor(arg) {
    _83c = 0;
    _83d = 0;
}

ksys::act::BaseProc* OptionalWeapon::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) OptionalWeapon(arg);
}

ksys::act::Actor* OptionalWeapon::m31() {
    return sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr));
}

void OptionalWeapon::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    sub_7100EF0A44();
}

bool OptionalWeapon::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

OptionalWeapon::IsSpecialJobTypeResult OptionalWeapon::isSpecialJobType_(ksys::act::JobType type) {
    if (_94c)
        return IsSpecialJobTypeResult::Yes;
    return Actor::isSpecialJobType_(type);
}

}  // namespace uking::act
