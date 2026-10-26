#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"

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

void Unk_710244ff68::m11(bool enable) {
    auto* chemicals = _10->getChemicalContainer();
    if (!chemicals)
        return;
    const s32 count = chemicals->_80;
    if (count <= 0)
        return;
    if (enable) {
        for (s32 i = 0; i < count; ++i) {
            auto* chemical = chemicals->sub_7100E380FC(i);
            if (!chemical)
                return;
            chemical->sub_7100D8EEE0();
            chemical->sub_7100D90C2C(true);
            chemical->sub_7100D90CD8(true);
            chemical->sub_7100D90D7C(true);
            chemical->sub_7100D90F60(true);
        }
    } else {
        for (s32 i = 0; i < count; ++i) {
            auto* chemical = chemicals->sub_7100E380FC(i);
            if (!chemical)
                return;
            chemical->sub_7100D90C2C(false);
            chemical->sub_7100D90CD8(false);
            chemical->sub_7100D90D7C(false);
            chemical->sub_7100D90F60(false);
        }
    }
}

// Preserves the original own D1, as in upstream
// GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
Unk_710244ff68::~Unk_710244ff68() {
    ;
}

bool Unk_710244ff68::m8(const ksys::Message& message) {
    if (message.getType() != 0x800009b)
        return false;
    _30._30 = true;
    _30._18 = message.getSource();
    return true;
}

// Keep each original own D1, following upstream GameDataFlagSelector's user-provided
// destructor form (commit 96101229).
Unk_710244ebc8::~Unk_710244ebc8() { ; }
Unk_710244eb48::~Unk_710244eb48() { ; }
Unk_710244fee8::~Unk_710244fee8() { ; }

bool Unk_710244ebc8::m8(const ksys::Message& message) {
    if (message.getType() != 0x800009b)
        return false;
    _40._30 = true;
    _40._18 = message.getSource();
    return true;
}

void Unk_710244ebc8::m10() {
    if (_40._30) {
        sub_71006E3060();
        _40._30 = false;
        _40._8.reset();
        // called through a pointer in the original (not devirtualised)
        (&_40)->m3();
    }
    sub_71006E2A3C();
    if (!_8.isOn(0x5c))
        return;
    ksys::Timer::update(&_1c, -1.0f);
    if (_1c <= 0.0f) {
        if (_8.isOnBit(2) && !sub_71006E2CA0())
            m13(2);
        if (_8.isOnBit(4) && !sub_71006E2E38())
            m13(4);
    }
}

void Unk_710244ebc8::m13(int index) {
    if (index == 4)
        _20.fadeXLink();
    _8.resetBit(index);
}

// NON_MATCHING: same-TU parameter and electric helpers inline into the condition branches.
void Unk_710244ebc8::m12(int index) {
    switch (index) {
    case 2: {
        auto* param = sub_71006DF5A4();
        if (!param || !param->mIceable.ref())
            break;
        param = sub_71006DF5A4();
        if (!param || !param->mIceable.ref())
            break;
        param = sub_71006DF5A4();
        if (param) {
            ConditionDamageInfo info;
            info.mKind = 2;
            info.mDamage = param->mIceDamage.ref();
            sub_71006DF5CC(info);
        }
        _8.setBit(2);
        break;
    }
    case 4: {
        auto* param = sub_71006DF5A4();
        if (param && param->mElectricable.ref())
            sub_71006E2BAC();
        break;
    }
    default:
        break;
    }
}

// NON_MATCHING: same-TU parameter and requested-damage helpers inline into the body.
void Unk_710244ebc8::sub_71006E2BAC() {
    auto* param = sub_71006DF5A4();
    if (!param || !param->mElectricable.ref())
        return;
    param = sub_71006DF5A4();
    if (param) {
        ConditionDamageInfo info;
        info.mKind = 4;
        info.mDamage = param->mElectricDamage.ref();
        sub_71006DF5CC(info);
    }
    _1c = static_cast<f32>(param->mElectricTime.ref());
    if (!_20.sub_7101241B6C())
        xlinkSearchAndEmit(_10, "ElectricShock", 2, &_20);
    _8.setBit(4);
}

// NON_MATCHING: same-TU parameter and requested-damage helpers inline into both branches.
void Unk_710244ebc8::sub_71006E3060() {
    auto* param = sub_71006DF5A4();
    if (!param || !param->mGerudoHeroAffect.ref())
        return;
    param = sub_71006DF5A4();
    const s32 time = param ? param->mGerudoHeroTime.ref() : 0;
    param = sub_71006DF5A4();
    const s32 damage = param ? param->mGerudoHeroDamage.ref() : 0;
    if (time > 0) {
        if (!_20.sub_7101241B6C())
            xlinkSearchAndEmit(_10, "ElectricShock", 2, &_20);
        ConditionDamageInfo info;
        info.mKind = 4;
        info.mDamage = damage;
        sub_71006DF5CC(info);
        _8.setBit(4);
        _1c = static_cast<f32>(time);
    } else {
        ConditionDamageInfo info;
        info.mKind = 4;
        info.mDamage = damage;
        info._8 = 4;
        info.mFlags = 0x80;
        sub_71006DF5CC(info);
    }
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

}  // namespace uking::act
