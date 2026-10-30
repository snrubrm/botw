#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace uking::act {

bool Unk_710244edc0::m4(sead::Heap*) {
    return true;
}

void Unk_710244edc0::m5() {
    _68 = false;
    _8.makeAllZero();
}

void Unk_710244edc0::m10() {
    if (sub_71006DFB58())
        return;
    sub_71006E8770();
    sub_71006E8AD0();
    sub_71006E8D00();
    sub_71006E8E04();
    sub_71006E8F20();
    sub_71006E90A0();
    sub_71006E916C();
}

void Unk_710244edc0::m13(int index) {
    _8.resetBit(index);
}

void Unk_710244edc0::m7() {
    Unk_71025ae680::m7();
}

void Unk_710244edc0::m11(bool enable) {
    auto* chemical = _10->getChemicalStuff();
    if (!chemical)
        return;
    if (enable)
        chemical->sub_7100D8EEE0();
    chemical->sub_7100D90C2C(enable);
    chemical->sub_7100D90CD8(enable);
    chemical->sub_7100D90D7C(enable);
    chemical->sub_7100D90F60(enable);
}

bool Unk_710244edc0::m8(const ksys::Message& message) {
    return _30.m2(message);
}

void Unk_710244edc0::sub_71006E8D00() {
    if (sub_71006E9780()) {
        auto* param = sub_71006DF5A4();
        if (param && param->mCurseAffect.ref() && !_8.isOn(0x800)) {
            sub_71006DF750();
            param = sub_71006DF5A4();
            _24 = param ? static_cast<f32>(param->mCurseInterval.ref()) : 0.0f;
            _8.set(0x800);
            param = sub_71006DF5A4();
            if (param && param->mCurseDamage.ref() >= 1) {
                act::ConditionDamageInfo info;
                info.mKind = 11;
                info.mDamage = param->mCurseDamage.ref();
                sub_71006DF5CC(info);
            }
        }
        _28 = 60.0f;
    } else if (_28 > 0.0f) {
        ksys::Timer::update(&_28, -1.0f);
    } else {
        sub_71006DF750();
    }
    _30.x();
}

// 60.0f at 0x7101DA2354 (read by sub_71006E90A0).
extern const f32 sUnk_7101DA2354;
const f32 sUnk_7101DA2354 = 60.0f;

void Unk_710244edc0::sub_71006E90A0() {
    if (!_8.isOnBit(11))
        return;
    if (_24 < 0.0f)
        return;
    if (_28 < sUnk_7101DA2354)
        return;
    ksys::Timer::update(&_24, -1.0f);
    if (_24 < 0.0f) {
        if (_8.isOnBit(11)) {
            if (auto* param = sub_71006DF5A4()) {
                const s32 damage = param->mCurseContinuousDamage.ref();
                if (damage >= 1) {
                    ConditionDamageInfo info{};
                    info.mKind = 11;
                    info.mDamage = damage;
                    info.mFlags = 1;
                    sub_71006DF5CC(info);
                }
            }
            if (auto* param = sub_71006DF5A4())
                _24 = f32(param->mCurseInterval.ref());
            else
                _24 = 0.0f;
        }
    }
}

void Unk_710244edc0::sub_71006E916C() {
    if (!_8.isOnBit(1))
        return;
    if (_20 < 0.0f)
        return;
    ksys::Timer::update(&_20, -1.0f);
    if (_20 <= 0.0f) {
        auto* param = sub_71006DF5A4();
        if (!param)
            return;
        if (!param->mIsDeadIce.ref() && !param->mIsMetamorIce.ref())
            return;
        ConditionDamageInfo info{};
        info.mKind = 3;
        info.mDamage = _10->getMaxLife();
        if (auto* metamor = sub_71006DF5A4()) {
            if (metamor->mIsMetamorIce.ref())
                info.mFlags = 0x20;
        }
        sub_71006DF5CC(info);
        _8.setBit(3);
    }
}

bool Unk_710244edc0::sub_71006E9780() {
    if (_10->get68f().load() != 0 && _10->get6fc() == ksys::phys::Material::Grudge)
        return true;
    if (auto* controller = _10->getCharacterController()) {
        if (auto* contacts = controller->sub_7100F635E4()) {
            for (auto it = contacts->begin(), end = contacts->end(); it != end; ++it) {
                if ((*it)->material_mask_b.getMaterial() == ksys::phys::Material::Grudge)
                    return true;
            }
        }
    }
    return _30._30 && (_30._34 == 0 || _30._34 == 1);
}

void Unk_710244edc0::sub_71006E8E04() {
    bool affected = false;
    if (auto* world = ksys::world::Manager::instance()) {
        if (auto* weather_mgr = world->getWeatherMgrMaybe()) {
            const auto weather = weather_mgr->getWeather();
            // This predicate observes the low byte of the signed weather request.
            affected = u8(weather) < ksys::world::NumWeatherTypes &&
                       (weather == ksys::world::WeatherType::HeavySnow ||
                        u8(world->getWeatherRequest()) == 2);
        }
    }
    if (affected && !_68) {
        auto* chemical = _10->getChemicalStuff();
        if (!chemical || (chemical->_c0 != 2 && (chemical->_b8 & 4) == 0)) {
            if (_8.isOnBit(1))
                return;
            auto* param = sub_71006DF5A4();
            if (!param || param->mHeavySnowColdTime.ref() < 0)
                return;
            param = sub_71006DF5A4();
            if (!param || param->mHeavySnowColdTime.ref() < 0)
                return;
            param = sub_71006DF5A4();
            _20 = param ? f32(param->mHeavySnowColdTime.ref()) : -1.0f;
            _8.setBit(1);
            return;
        }
    }
    if (_8.isOnBit(1))
        m13(1);
}

void Unk_710244edc0::sub_71006E8F20() {
    if (!_8.isOn(0x780))
        return;
    if (_1c < 0.0f)
        return;
    ksys::Timer::update(&_1c, -1.0f);
    if (_1c <= 0.0f) {
        if (_8.isOnBit(8)) {
            auto* param = sub_71006DF5A4();
            if (param && (param->mIsDeadIce.ref() || param->mIsMetamorIce.ref())) {
                ConditionDamageInfo info{};
                info.mKind = 3;
                info.mDamage = _10->getMaxLife();
                if (auto* metamor = sub_71006DF5A4()) {
                    if (metamor->mIsMetamorIce.ref())
                        info.mFlags = 0x20;
                }
                sub_71006DF5CC(info);
                _8.setBit(3);
            }
        } else if (_8.isOnBit(9)) {
            ConditionDamageInfo info{};
            info.mKind = 9;
            info.mDamage = _10->getMaxLife();
            info.mFlags = 0x20;
            sub_71006DF5CC(info);
        } else if (_8.isOnBit(10)) {
            auto* param = sub_71006DF5A4();
            if (param && param->mLavaDamage.ref() >= 1) {
                ConditionDamageInfo info{};
                info.mKind = 10;
                info.mDamage = param->mLavaDamage.ref();
                info.mFlags = 1;
                sub_71006DF5CC(info);
            }
            param = sub_71006DF5A4();
            _1c = param ? static_cast<f32>(param->mLavaDamageInterval.ref()) : 0.0f;
        }
    }
}
void Unk_710244edc0::sub_71006E9578() {
    auto* actor = _10;
    auto* param = sub_71006DF5A4();
    if (!param || !(param->mIsDeadElectric.ref() || param->mIsMetamorElectric.ref()))
        return;
    if (auto* chemical = actor->getChemicalStuff())
        chemical->sub_7100D945BC(chemical->sub_7100D945AC(), 1.0f, 1.0f);
    ConditionDamageInfo info{};
    info.mKind = 4;
    info.mDamage = _10->getMaxLife();
    if (auto* p = sub_71006DF5A4()) {
        if (p->mIsMetamorElectric.ref())
            info.mFlags = 0x20;
    }
    sub_71006DF5CC(info);
    _8.setBit(4);
}

}  // namespace uking::act
