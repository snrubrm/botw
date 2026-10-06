#include "Game/Actor/actOptionalWeapon.h"
#include <basis/seadNew.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

// 0x71011d75cc (declaration only; sends message 0x12... through the actor system; name unknown).
void sub_71011D75CC(ksys::act::Actor* actor);

namespace uking::act {

// NON_MATCHING: store schedule only (the original loads the cElementMax address after the second string's
// terminator store)
OptionalWeapon::OptionalWeapon(const CreateArg& arg) : Actor(arg) {
    _83c = 0;
}

ksys::act::BaseProc* OptionalWeapon::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) OptionalWeapon(arg);
}

ksys::act::Actor* OptionalWeapon::m31() {
    return sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr));
}

bool OptionalWeapon::sub_7100EF1ADC() {
    sead::ScopedLock<sead::CriticalSection> lock(&_898._0);
    _898._40[1].reset();
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_898._40[0], &accessor);
    if (accessor.sub_7100D10F0C())
        sub_71011D75CC(this);
    _898._40[0].reset();
    _898._60 = 1;
    return true;
}

void OptionalWeapon::sub_7100EF10BC() {
    ksys::act::acc::WeaponBase accessor;
    ksys::act::acquireActor(&_850, &accessor);
    if (accessor.isWeaponType0Or1Or2()) {
        if (accessor.m153()) {
            accessor.sub_7100EFB53C(mModel);
            _83e |= 2;
        } else if (_83e & 2) {
            sub_71011C5630(nullptr);
            _83e &= ~2;
        }
    }
}

bool OptionalWeapon::sub_7100EF1308() {
    return isPlayerProfile(sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)));
}

bool OptionalWeapon::sub_7100EF1B70() {
    return !_850.hasProc();
}

bool OptionalWeapon::sub_7100EF1B90() {
    bool result = false;
    ksys::act::acc::WeaponBase accessor;
    ksys::act::acquireActor(&_898._40[1], &accessor);
    if (accessor.hasParentActor_())
        result = _898._60 == 0;
    return result;
}

void OptionalWeapon::updatePositionMaybe() {
    _83c &= ~1;
    sub_7100EF0D44();
    sub_7100EF0FAC();
    sub_7100EF10BC();
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
