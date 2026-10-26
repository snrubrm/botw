#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"

namespace uking::act {

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

void Unk_710244ff68::m10() {
    if (_30._30) {
        auto* param = sub_71006DF5A4();
        if (param && param->mGerudoHeroAffect.ref()) {
            param = sub_71006DF5A4();
            const s32 damage = param ? param->mGerudoHeroDamage.ref() : 0;
            ConditionDamageInfo info{};
            info.mKind = 4;
            info.mDamage = damage;
            info._8 = 0x800;
            info.mFlags = 0x80;
            sub_71006DF5CC(info);
        }
        _30._30 = false;
        _30._8.reset();
        // called through a pointer in the original (not devirtualised)
        (&_30)->m3();
    }
    sub_71006EE838();
    sub_71006EED1C();
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
        if (!param || !param->mBurnable.ref())
            break;
        param = sub_71006DF5A4();
        if (!param || !param->mBurnable.ref())
            break;
        param = sub_71006DF5A4();
        if (param) {
            ConditionDamageInfo info;
            info.mKind = 2;
            info.mDamage = param->mBurnDamage.ref();
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
// NON_MATCHING: clang canonicalises the `time` test to `cmp #1; b.ge` here; the original keeps
// `cmp #0; b.gt`. Every other instruction matches.
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

void Unk_710244eb48::m5() {
    sub_71006E252C();
}

// lane4 s64: out-of-line copy of m5's body (the original has both: m5 inlines this).
void Unk_710244eb48::sub_71006E252C() {
    if (_58.sub_7101241B6C())
        _58.fadeXLink();
}

void Unk_710244eb48::sub_71006E264C() {
    auto* param = sub_71006DF5A4();
    if (!param || !param->mGerudoHeroAffect.ref() || _1c)
        return;

    param = sub_71006DF5A4();
    const s32 damage = param ? param->mGerudoHeroDamage.ref() : 0;
    ConditionDamageInfo info;
    info.mKind = 4;
    info.mDamage = damage;
    info._8 = 4;
    info.mFlags = 0x80;
    sub_71006DF5CC(info);

    if (auto* boss = sead::DynamicCast<LastBoss>(_10)) {
        if (!boss->_14f8._30.isOnBit(4) && !boss->_14e8.isOnBit(10)) {
            if (boss->_14e8.isOnBit(3))
                boss->_14e8.setBit(18);
            else
                boss->_14f8._30.set(0x300);
        }
    }

    if (!_58.sub_7101241B6C())
        xlinkSearchAndEmit(_10, "ElectricShock", 2, &_58);
}

bool Unk_710244eb48::m8(const ksys::Message& message) {
    if (message.getType() != 0x800009b)
        return false;
    _20._30 = true;
    _20._18 = message.getSource();
    return true;
}

void Unk_710244eb48::m10() {
    if (!_20._30)
        return;
    sub_71006E264C();
    _20._30 = false;
    _20._8.reset();
    // called through a pointer in the original (not devirtualised)
    (&_20)->m3();
}

void Unk_710244fee8::m5() {
    sub_71006EE354();
}

// lane4 s64: out-of-line copy of m5's body (the original has both: m5 inlines this).
void Unk_710244fee8::sub_71006EE354() {
    if (_58.sub_7101241B6C())
        _58.fadeXLink();
}

void Unk_710244fee8::sub_71006EE474() {
    auto* param = sub_71006DF5A4();
    if (!param || !param->mGerudoHeroAffect.ref() || _1c)
        return;

    param = sub_71006DF5A4();
    const s32 damage = param ? param->mGerudoHeroDamage.ref() : 0;
    ConditionDamageInfo info;
    info.mKind = 4;
    info.mDamage = damage;
    info._8 = 4;
    info.mFlags = 0x180;
    sub_71006DF5CC(info);

    if (auto* boss = sead::DynamicCast<SiteBoss>(_10)) {
        if (!boss->_14c8._30.isOnBit(9))
            boss->_1558.setBit(26);
    }

    if (!_58.sub_7101241B6C())
        xlinkSearchAndEmit(_10, "ElectricShock", 2, &_58);
}

bool Unk_710244fee8::m8(const ksys::Message& message) {
    if (message.getType() != 0x800009b)
        return false;
    _20._30 = true;
    _20._18 = message.getSource();
    return true;
}

void Unk_710244fee8::m10() {
    if (!_20._30)
        return;
    sub_71006EE474();
    _20._30 = false;
    _20._8.reset();
    // called through a pointer in the original (not devirtualised)
    (&_20)->m3();
}

}  // namespace uking::act
