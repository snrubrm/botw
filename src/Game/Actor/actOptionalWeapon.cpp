#include "Game/Actor/actOptionalWeapon.h"
#include <basis/seadNew.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponOption.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Sound/sndUnk_7102502138.h"
#include "KingSystem/Utils/Thread/Message.h"

// 0x71011d75cc (declaration only; sends message 0x12... through the actor system; name unknown).
void sub_71011D75CC(ksys::act::Actor* actor);

namespace uking::act {

OptionalWeapon::OptionalWeapon(const CreateArg& arg) : Actor(arg) {
    _83c = 0;
}

ksys::act::BaseProc* OptionalWeapon::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) OptionalWeapon(arg);
}

ksys::act::Actor* OptionalWeapon::m31() {
    return sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr));
}

void OptionalWeapon::initMaybe() {
    if (_850.hasProc() && _840.hasProc()) {
        _898._60 = 0;
        if (auto* parent = sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr))) {
            if (parent->isSleep())
                sleep(SleepWakeReason::_0);
        }
    }
    _83c = 0;
    _83e = 0;
    _938 = sead::Color4f(0.0f, 0.0f, 0.0f, 0.0f);
    _948 = 0.0f;
    _94c = 0;
}

void OptionalWeapon::sub_7100EF0D44() {
    auto* model = mModel;
    if (!model)
        return;
    if (isPlayerProfile(sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)))) {
        auto* player = ksys::act::ActorSystem::instance()->getPlayerLink();
        if (!player)
            return;
        sub_71011CCB1C(player->m315());
        x_3(player->m316());
        const f32 value = player->m317();
        if (_948 != value) {
            Unk_710260af28::instance()->sub_7100F1EAF8(model, value);
            _948 = value;
        }
        const sead::Color4f color = player->m314();
        if (!(_938 == color)) {
            Unk_710260af28::instance()->sub_7100F1E2F4(model, color);
            _938 = color;
        }
    } else if (isNPCProfile(sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)))) {
        sub_7100EF1F30();
    }
}

void OptionalWeapon::sub_7100EF13AC(sead::Vector3f* out) {
    ksys::act::acc::WeaponBase weapon;
    ksys::act::acquireActor(&_850, &weapon);
    if (!weapon.hasProc() || !weapon.isStateCalc()) {
        *out = sead::Vector3f::zero;
        return;
    }
    if (!weapon.isWeaponType3()) {
        if (weapon.isWeaponType0Or1Or2())
            weapon.m167(out);
        else
            *out = sead::Vector3f::zero;
        return;
    }
    if (isPlayerProfile(sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr))) ||
        ksys::act::sub_7100EFD8E4(sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)))) {
        *out = getParam()->getRes().mGParamList->getWeaponOption()->mPlayerHoldRotOffset.ref();
    } else if (isNPCProfile(sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)))) {
        *out = getParam()->getRes().mGParamList->getWeaponOption()->mNPCHoldRotOffset.ref();
    }
}

void OptionalWeapon::sub_7100EF1680(sead::Vector3f* out) {
    ksys::act::acc::WeaponBase weapon;
    ksys::act::acquireActor(&_850, &weapon);
    if (!weapon.hasProc() || !weapon.isStateCalc()) {
        *out = sead::Vector3f::zero;
        return;
    }
    if (!weapon.isWeaponType3()) {
        if (weapon.isWeaponType0Or1Or2())
            weapon.m168(out);
        else
            *out = sead::Vector3f::zero;
        return;
    }
    if (isPlayerProfile(sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr))) ||
        ksys::act::sub_7100EFD8E4(sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)))) {
        *out = getParam()->getRes().mGParamList->getWeaponOption()->mPlayerHoldTransOffset.ref();
    } else if (isNPCProfile(sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)))) {
        *out = getParam()->getRes().mGParamList->getWeaponOption()->mNPCHoldTransOffset.ref();
    }
}

bool OptionalWeapon::sub_7100EF1954(ksys::act::Actor* parent, ksys::act::WeaponBase* weapon,
                                    const sead::SafeString& name) {
    sead::ScopedLock<sead::CriticalSection> lock(&_898._0);
    if (!weapon || !_898._60 || _840.hasProc())
        return false;
    _898._40[1].acquire(weapon, false);
    _898._40[0].acquire(parent, false);
    _898._60 = 0;
    _900.copy(name);
    auto* obj = parent->getMapObject();
    if (parent->get1a0() || (obj && obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000)))
        sub_71011D7650(this, parent);
    return true;
}

bool OptionalWeapon::sub_7100EF1ADC() {
    sead::ScopedLock<sead::CriticalSection> lock(&_898._0);
    _898._40[1].reset();
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_898._40[0], &accessor);
    if (accessor.sub_7100D10F0C())
        sub_71011D75CC(this);
    _898._40[0].reset();
    _898._60 = 1;
    return true;
}

// NON_MATCHING: stack slot assignment of the string temporaries and accessors only.
// Placeholder name: for owners other than shields and bows, copies the owner weapon's m155 / m154 / m156 states
// into _83c bits 2 / 1 / 3, setting bit 0 and stopping at the first one that changed.
void OptionalWeapon::sub_7100EF0A44() {
    ksys::act::ActorLinkConstDataAccess owner;
    ksys::act::acquireActor(&_850, &owner);
    if (owner.getProfile().findIndex("Shield") != -1 || owner.getProfile().findIndex("Bow") != -1)
        return;

    bool on;
    {
        ksys::act::acc::WeaponBase weapon;
        ksys::act::acquireActor(&_850, &weapon);
        on = weapon.m155();
    }
    if (on) {
        if (!(_83c & 4))
            _83c |= 1;
        _83c |= 4;
    } else {
        if (_83c & 4)
            _83c |= 1;
        _83c &= ~4;
    }
    if (_83c & 1)
        return;

    {
        ksys::act::acc::WeaponBase weapon;
        ksys::act::acquireActor(&_850, &weapon);
        on = weapon.m154();
    }
    if (on) {
        if (!(_83c & 2))
            _83c |= 1;
        _83c |= 2;
    } else {
        if (_83c & 2)
            _83c |= 1;
        _83c &= ~2;
    }
    if (_83c & 1)
        return;

    {
        ksys::act::acc::WeaponBase weapon;
        ksys::act::acquireActor(&_850, &weapon);
        on = weapon.m156();
    }
    if (on) {
        if (!(_83c & 8))
            _83c |= 1;
        _83c |= 8;
    } else {
        if (_83c & 8)
            _83c |= 1;
        _83c &= ~8;
    }
}

// NON_MATCHING: stack slot order of the locals and `count < 4` compiled as cmp #3 / b.gt.
// Placeholder name: for a Bow owner, sets the AS rate to the arrows missing from 4 and tells the sound unit.
void OptionalWeapon::sub_7100EF0FAC() {
    ksys::act::ActorLinkConstDataAccess owner;
    ksys::act::acquireActor(&_850, &owner);
    if (owner.getProfile().findIndex("Bow") == -1)
        return;
    s32 count = 0;
    {
        ksys::act::acc::WeaponBase weapon;
        ksys::act::acquireActor(&_850, &weapon);
        if (weapon.hasProc())
            weapon.m223(&count);
    }
    if (count < 4)
        mASList->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, 4.0f - count);
    else
        mASList->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163298, 0.0f);
    if (auto* sound = ksys::snd::Unk_7102502138::instance())
        sound->sub_710103B474(count);
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

bool OptionalWeapon::sub_7100EF1EA4() {
    ksys::act::acc::WeaponBase accessor;
    ksys::act::acquireActor(&_850, &accessor);
    return accessor.getProfile().findIndex("Bow") != -1 && accessor.m222();
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

sead::FixedSafeString<32>& OptionalWeapon::sub_7100EF13A4() {
    return _860;
}

}  // namespace uking::act

// NON_MATCHING: the original casts the owner to Actor twice (two RTTI checks).
// Placeholder name: applies the opacity requested by sub_7100EF2290: the owner's m139() when `_994` is set,
// else `_990` plus m139() clamped to [0, 1] (setting ActorFlag2::_20 when it is zero).
void uking::act::OptionalWeapon::sub_7100EF1F30() {
    if (!mModel || !_995)
        return;
    if (_994) {
        if (auto* owner = sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)))
            sub_71011CCB1C(owner->m139());
        return;
    }
    f32 alpha = sead::Mathf::clamp(_990 + m139(), 0.0f, 1.0f);
    if (sead::Mathf::abs(alpha) <= sead::Mathf::epsilon())
        mActorFlags2.set(ActorFlag2::_20);
    sub_71011CCB1C(alpha);
    _995 = false;
}

void uking::act::OptionalWeapon::sub_7100EF2290(f32 value, bool use_parent) {
    sead::ScopedLock<sead::CriticalSection> lock(&_950);
    _990 = value;
    _994 = use_parent;
    _995 = true;
}

int uking::act::OptionalWeapon::handleMessage(const ksys::Message* message) {
    if (isDelete() || isDeleteRequested())
        return 0;
    if (message->getType() == 0x3000001) {
        _83e |= 1;
        mActorFlags2.set(ActorFlag2::_20);
    } else if (message->getType() == 0x3000002) {
        _83e &= ~1;
        mActorFlags2.reset(ActorFlag2::_20);
    } else {
        return Actor::handleMessage(message);
    }
    return 1;
}

bool uking::act::OptionalWeapon::shouldUnload(s32* value) {
    if (sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)))
        return false;
    return shouldUnloadBecauseOfDistance(value);
}

void uking::act::OptionalWeapon::calcMaybe() {
    if (_898._60 == 1) {
        _850.reset();
        _840.reset();
        return;
    }
    if (_83e & 1) {
        mActorFlags2.set(ActorFlag2::_20);
    } else if (auto* parent = sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr))) {
        x_57(parent);
    }
}

f32 uking::act::OptionalWeapon::m139() {
    if ((isPlayerProfile(sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr))) || m142()) &&
        _4f0 < 1.0f)
        return _4f0;
    return Actor::m139();
}
