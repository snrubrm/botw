#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Utils/Thread/Message.h"

// Defined in actPlayerBase.cpp (0x710084beec).
bool j_eventMgrHasActiveEventMaybe(ksys::act::Actor* actor);

namespace uking::act {


Unk_710244dd20::Unk_710244dd20(ksys::act::Actor* actor) : Unk_71025ae680(actor) {}

f32 Unk_710244dd20::sub_71006D1D48() {
    f32 ratio = 1.0f;
    if (_8.isOn(8)) {
        if (auto* param = sub_71006DF5A4())
            ratio = *param->mIceBreakDamageRatio;
    }
    return ratio;
}

bool Unk_710244dd20::sub_71006D1D7C() {
    if (auto* param = sub_71006DF5A4())
        return *param->mIceBreakableByAtk;
    return false;
}

bool Unk_710244dd20::sub_71006D1DA0() {
    if (auto* param = sub_71006DF5A4())
        return *param->mElecCancelableByAtk;
    return false;
}

bool Unk_710244dd20::m17(s32 bit) const {
    return _139.isOnBit(bit);
}

bool Unk_71008502cc::m9() {
    return j_eventMgrHasActiveEventMaybe(sead::DynamicCast<ksys::act::Player>(_10));
}

void Unk_71008502cc::m12(int index) {
    switch (index) {
    case 0: {
        auto* player = sead::DynamicCast<ksys::act::PlayerBase>(_10);
        if (!player || !player->sub_710084CF24())
            _8.setBit(0);
        break;
    }
    case 1: {
        auto* player = sead::DynamicCast<ksys::act::PlayerBase>(_10);
        if (!player || !player->sub_710084CF24())
            _8.setBit(1);
        break;
    }
    case 5:
        _140 = _10->getParam()->getRes().mGParamList->getPlayer()->mShockTime.ref();
        _8.setBit(5);
        break;
    default:
        Unk_710244dd20::m12(index);
        break;
    }
}

void Unk_71008502cc::m13(int index) {
    switch (index) {
    case 0:
        _8.resetBit(0);
        break;
    case 1:
        _8.resetBit(1);
        break;
    case 5:
        _8.resetBit(5);
        break;
    default:
        Unk_710244dd20::m13(index);
        break;
    }
}

bool Unk_71008502cc::sub_7100850CE4() const {
    return _8.isOn(0x3);
}

bool Unk_71008502cc::sub_7100850CF4() const {
    return _8.isOn(0x587);
}

void Unk_710244dd20::m5() {
    _8 = 0;
    _c0 = 0;
    if (auto* chemical = _10->getChemicalStuff()) {
        chemical->sub_7100D90CD8(false);
        chemical->sub_7100D90C2C(false);
        chemical->sub_7100D90D7C(false);
    }
    _138 = 0;
    _c4 = 1.0f;
    _c8 = 1.0f;
    _cc = 1.0f;
    _d0 = 1.0f;
    _d4 = 1.0f;
    _d8 = 1.0f;
    _dc = 1.0f;
    _e0 = 1.0f;
    _e4 = 1.0f;
    _e8 = 1.0f;
    _ec = 1.0f;
    _f0 = 1.0f;
    _30 = 0;
}

void Unk_710244dd20::m10() {
    m20();
    sub_71006CF338();
    sub_71006CF770();
    sub_71006CF9B4();
}

void Unk_710244dd20::m11(bool enable) {
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

bool Unk_710244dd20::m8(const ksys::Message& message) {
    if (_50.m2(message))
        return true;
    if (message.getType() != 0x800009b)
        return false;
    _88._30 = true;
    _88._18 = message.getSource();
    return true;
}

bool Unk_710244dd20::m16(s32 kind) {
    auto* chemical = _10->getChemicalStuff();
    if (!chemical)
        return true;
    if (kind == 3)
        return !(chemical->_b9[0] & 2);
    if (kind == 4)
        return !(chemical->_1b8 > 0.0f);
    return true;
}

void Unk_710244dd20::m20() {
    sub_71006D0C38();
    sub_71006D15EC();
    sub_71006D19AC();
    if (_88._30)
        sub_71006D0AB8();
    _88.x();
}

// NON_MATCHING: the depth loads (y before _6f0, as in sub_71006CFA80) and the block order of the string compare.
bool Unk_710244dd20::m15() {
    if (!m14())
        return false;

    if (_8.isOn(0x80)) {
        auto* actor = _10;
        if (!actor->get68f() ||
            int(ksys::phys::Material(actor->get6fc())) != ksys::phys::Material::Water) {
            return true;
        }
        return !(ksys::phys::MaterialMask::getSubMaterialName(ksys::phys::Material::Water,
                                                              actor->get700()) == "Water_Poison");
    }
    if (_8.isOn(0x100)) {
        if (!sub_71006DF43C(_10))
            return true;
        auto* param = sub_71006DF5A4();
        if (!param)
            return true;
        const f32 depth = _10->get68f() ? _10->get6f0() - _10->getMtx()(1, 3) : 0.0f;
        return !(depth > param->mColdWaterDamageStartDepth.ref());
    }
    if (_8.isOn(0x400)) {
        auto* actor = _10;
        if (!actor->get68f())
            return true;
        return int(ksys::phys::Material(actor->get6fc())) != ksys::phys::Material::Lava;
    }
    return false;
}

void Unk_710244dd20::sub_71006CF770() {
    if (!_8.isOn(0x780))
        return;
    if (_40 < 0.0f)
        return;
    if (m15())
        return;

    f32 rate;
    if (_8.isOn(0x100))
        rate = -sub_71006CFA80();
    else if (_8.isOn(0x200))
        rate = -sub_71006CFBA0();
    else
        rate = -1.0f;
    ksys::Timer::update(&_40, rate);
    if (!(_40 < 0.0f))
        return;

    if (_8.isOn(0x80)) {
        auto* param = sub_71006DF5A4();
        if (param && param->mPoisonBogDamage.ref() >= 1) {
            act::ConditionDamageInfo info;
            info.mKind = 7;
            info.mDamage = param->mPoisonBogDamage.ref();
            info.mFlags = 1;
            sub_71006DF5CC(info);
        }
        param = sub_71006DF5A4();
        _40 = param ? static_cast<f32>(param->mPoisonBogDamageInterval.ref()) : 0.0f;
    } else if (_8.isOn(0x100)) {
        auto* param = sub_71006DF5A4();
        if (param && param->mColdWaterDamage.ref() >= 1) {
            act::ConditionDamageInfo info;
            info.mKind = 8;
            info.mDamage = param->mColdWaterDamage.ref();
            info.mFlags = 1;
            sub_71006DF5CC(info);
        }
        param = sub_71006DF5A4();
        _40 = param ? static_cast<f32>(param->mColdWaterDamageInterval.ref()) : 0.0f;
    } else if (_8.isOn(0x200)) {
        auto* param = sub_71006DF5A4();
        if (param) {
            const s32 heal = param->mHotWaterHeal.ref();
            if (heal >= 1) {
                const s32* life_ptr = _10->getLife();
                const s32 life = life_ptr ? *life_ptr : 1;
                if (life < _10->getMaxLife())
                    xlinkSearchAndEmit(_10, "HotSpringRecovery", 2, nullptr);
                sub_71006DF67C(heal);
            }
        }
        param = sub_71006DF5A4();
        _40 = param ? static_cast<f32>(param->mHotWaterHealInterval.ref()) : 0.0f;
    } else if (_8.isOn(0x400)) {
        auto* param = sub_71006DF5A4();
        if (param && param->mLavaDamage.ref() >= 1) {
            act::ConditionDamageInfo info;
            info.mKind = 10;
            info.mDamage = param->mLavaDamage.ref();
            info.mFlags = 1;
            sub_71006DF5CC(info);
        }
        param = sub_71006DF5A4();
        _40 = param ? static_cast<f32>(param->mLavaDamageInterval.ref()) : 0.0f;
    }
}

// NON_MATCHING: the original loads the actor's y before _6f0 for both depths (as `-y + _6f0` would) and keeps the
// constant -1 in another register.
f32 Unk_710244dd20::sub_71006CFA80() {
    auto* actor = _10;
    auto* param = sub_71006DF5A4();
    if (!param)
        return 0.0f;
    if (!sub_71006DF43C(_10))
        return 0.0f;
    auto* param2 = sub_71006DF5A4();
    if (!param2)
        return 0.0f;
    const f32 depth = _10->get68f() ? _10->get6f0() - _10->getMtx()(1, 3) : 0.0f;
    if (!(depth > param2->mColdWaterDamageStartDepth.ref()))
        return 0.0f;
    if (_8.isOn(8))
        return 0.0f;

    const s32 interval_deep = param->mColdWaterDamageIntervalDeep.ref();
    const s32 interval = param->mColdWaterDamageInterval.ref();
    if (interval_deep < 0)
        return interval < 0 ? 0.0f : 1.0f;
    if (interval_deep == 0)
        return 1.0f;
    const f32 deep_depth = param->mColdWaterDamageDeepDepth.ref();
    if (deep_depth <= 0.0f)
        return 1.0f;
    const f32 range = deep_depth - param->mColdWaterDamageStartDepth.ref();
    if (range <= 0.0f)
        return static_cast<f32>(interval_deep);
    const f32 actor_depth = actor->get68f() ? actor->get6f0() - actor->getMtx()(1, 3) : 0.0f;
    const f32 diff = actor_depth - param->mColdWaterDamageStartDepth.ref();
    const f32 ratio = (diff < 0.0f ? 0.0f : diff) / range;
    return (static_cast<f32>(interval / interval_deep) - 1.0f) * ratio + 1.0f;
}

// NON_MATCHING: the original loads the actor's y before _6f0 for both depths (as `-y + _6f0` would) and keeps the
// constant -1 in another register.
f32 Unk_710244dd20::sub_71006CFBA0() {
    auto* actor = _10;
    auto* param = sub_71006DF5A4();
    if (!param)
        return 0.0f;
    if (!sub_71006DF4F0(_10))
        return 0.0f;
    auto* param2 = sub_71006DF5A4();
    if (!param2)
        return 0.0f;
    const f32 depth = _10->get68f() ? _10->get6f0() - _10->getMtx()(1, 3) : 0.0f;
    if (!(depth > param2->mHotWaterHealStartDepth.ref()))
        return 0.0f;
    if (_8.isOn(8))
        return 0.0f;

    const s32 interval_deep = param->mHotWaterHealIntervalDeep.ref();
    const s32 interval = param->mHotWaterHealInterval.ref();
    if (interval_deep < 0)
        return interval < 0 ? 0.0f : 1.0f;
    if (interval_deep == 0)
        return 1.0f;
    const f32 deep_depth = param->mHotWaterHealDeepDepth.ref();
    if (deep_depth <= 0.0f)
        return 1.0f;
    const f32 range = deep_depth - param->mHotWaterHealStartDepth.ref();
    if (range <= 0.0f)
        return static_cast<f32>(interval_deep);
    const f32 actor_depth = actor->get68f() ? actor->get6f0() - actor->getMtx()(1, 3) : 0.0f;
    const f32 diff = actor_depth - param->mHotWaterHealStartDepth.ref();
    const f32 ratio = (diff < 0.0f ? 0.0f : diff) / range;
    return (static_cast<f32>(interval / interval_deep) - 1.0f) * ratio + 1.0f;
}

void Unk_710244dd20::sub_71006CF9B4() {
    if (!_8.isOn(0x800))
        return;
    if (_44 < 0.0f)
        return;
    if (_48 < 60.0f)
        return;
    ksys::Timer::update(&_44, -1.0f);
    if (!(_44 < 0.0f))
        return;
    if (!_8.isOn(0x800))
        return;

    auto* param = sub_71006DF5A4();
    if (param && param->mCurseContinuousDamage.ref() >= 1) {
        act::ConditionDamageInfo info;
        info.mKind = 11;
        info.mDamage = param->mCurseContinuousDamage.ref();
        info.mFlags = 1;
        sub_71006DF5CC(info);
    }
    param = sub_71006DF5A4();
    _44 = param ? static_cast<f32>(param->mCurseInterval.ref()) : 0.0f;
}

void Unk_710244dd20::sub_71006D0AB8() {
    if (_138 & 8)
        return;
    auto* param = sub_71006DF5A4();
    if (!param || !param->mGerudoHeroAffect.ref())
        return;

    param = sub_71006DF5A4();
    const s32 time = param ? param->mGerudoHeroTime.ref() : 0;
    param = sub_71006DF5A4();
    const s32 damage = param ? param->mGerudoHeroDamage.ref() : 0;
    if (time <= 0) {
        act::ConditionDamageInfo info;
        info.mKind = 4;
        info.mDamage = damage;
        info._8 = 4;
        info.mFlags = 0x180;
        sub_71006DF5CC(info);
    } else {
        if (!_118.sub_7101241B6C())
            xlinkSearchAndEmit(_10, "ElectricShock", 2, &_118);
        act::ConditionDamageInfo info;
        info.mKind = 4;
        info.mDamage = damage;
        info.mFlags = 0x100;
        sub_71006DF5CC(info);
        _c0 |= 0x10;
        _3c = static_cast<f32>(time);
        _8.set(0x10);
    }
}

void Unk_710244dd20::sub_71006D19AC() {
    if (sub_71006D1C34()) {
        auto* param = sub_71006DF5A4();
        if (param && param->mCurseAffect.ref() && !_8.isOn(0x800)) {
            sub_71006DF750();
            param = sub_71006DF5A4();
            _44 = param ? static_cast<f32>(param->mCurseInterval.ref()) : 0.0f;
            _8.set(0x800);
            param = sub_71006DF5A4();
            if (param && param->mCurseDamage.ref() >= 1) {
                act::ConditionDamageInfo info;
                info.mKind = 11;
                info.mDamage = param->mCurseDamage.ref();
                sub_71006DF5CC(info);
            }
        }
        _48 = 60.0f;
    } else if (_48 > 0.0f) {
        ksys::Timer::update(&_48, -1.0f);
    } else {
        sub_71006DF750();
    }
    _50.x();
}

void Unk_710244dd20::m13(int index) {
    auto* actor = _10;
    switch (index) {
    case 2:
        if (_8.isOnBit(2)) {
            auto* chemical = actor->getChemicalStuff();
            if (chemical && chemical->_c0 == 2) {
                _c0 |= 4;
                chemical->sub_7100D90B78();
                chemical->sub_7100D90C2C(true);
                _30 = 0;
            }
        }
        break;
    case 3:
        if (_8.isOnBit(3)) {
            xlinkSearchAndEmit(actor, "Frozen_End", 2, nullptr);
            _f8.fadeXLink();
            auto* chemical = actor->getChemicalStuff();
            if (chemical && chemical->_c0 == 1) {
                _c0 |= 8;
                chemical->sub_7100D8EEE0();
                chemical->sub_7100D90CD8(true);
                _13a = 1;
            }
        }
        break;
    case 4:
        if (_8.isOnBit(4)) {
            auto* chemical = actor->getChemicalStuff();
            if (chemical && chemical->_1b8 > 0.0f) {
                _c0 |= 0x10;
                chemical->sub_7100D90D7C(true);
            }
            if (_118.sub_7101241B6C())
                _118.fadeXLink();
        }
        break;
    case 6:
        if (_8.isOnBit(6)) {
            if (auto* chemical = actor->getChemicalStuff())
                chemical->_190 = 0;
        }
        break;
    default:
        break;
    }
    _8.resetBit(index);
}

// 0x71006d2130: only forwards to the base implementation.
void Unk_710244dd20::m7() {
    Unk_71025ae680::m7();
}

}  // namespace uking::act

// NON_MATCHING: placeholder destructor; the original (0x7100850314) also destroys members or bases
// this class does not declare yet.
Unk_710246a960::~Unk_710246a960() = default;
