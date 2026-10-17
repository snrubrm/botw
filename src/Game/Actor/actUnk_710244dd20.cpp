#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectPlayer.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::act {

Unk_710244dd20::Unk_710244dd20(ksys::act::Actor* actor) : Unk_71025ae680(actor) {}

Unk_710244dd20::~Unk_710244dd20() = default;

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

void Unk_710244dd20::m12(int index) {
    switch (index) {
    case 2: {
        if (m17(2))
            return;
        auto* param = sub_71006DF5A4();
        if (!param || !param->mBurnable.ref())
            return;
        if (auto* chemical = _10->getChemicalStuff()) {
            if (chemical->_c0 != 2)
                chemical->sub_7100D90858(false, 2, false, true, false);
        }
        sub_71006D01A0(false);
        return;
    }
    case 3: {
        if (m17(3))
            return;
        auto* param = sub_71006DF5A4();
        if (!param || !param->mIceable.ref())
            return;
        if (auto* chemical = _10->getChemicalStuff()) {
            if (chemical->_c0 != 1)
                chemical->sub_7100D90A40();
        }
        m19();
        return;
    }
    case 4: {
        if (m17(4))
            return;
        auto* param = sub_71006DF5A4();
        if (param && param->mElectricable.ref())
            m18();
        return;
    }
    case 6: {
        auto* param = sub_71006DF5A4();
        if (param && param->mWetAffect.ref())
            sub_71006D03C8();
        return;
    }
    case 7: {
        auto* param = sub_71006DF5A4();
        if (!param || !param->mPoisonBogAffect.ref())
            return;
        param = sub_71006DF5A4();
        _40 = param ? f32(param->mPoisonBogDamageInterval.ref()) : 0.0f;
        _8.set(0x80);
        return;
    }
    case 8: {
        auto* param = sub_71006DF5A4();
        if (!param || !param->mColdWaterAffect.ref())
            return;
        param = sub_71006DF5A4();
        _40 = param ? f32(param->mColdWaterDamageInterval.ref()) : 0.0f;
        _8.set(0x100);
        return;
    }
    case 9: {
        auto* param = sub_71006DF5A4();
        if (!param || !param->mHotWaterHealAffect.ref())
            return;
        param = sub_71006DF5A4();
        _40 = param ? f32(param->mHotWaterHealInterval.ref()) : 0.0f;
        param = sub_71006DF5A4();
        if (param && param->mHotWaterChemCrit.ref()) {
            ConditionDamageInfo info;
            info.mKind = 9;
            info.mDamage = 0;
            info.mFlags = 2;
            sub_71006DF5CC(info);
        }
        _8.set(0x200);
        return;
    }
    case 10: {
        auto* param = sub_71006DF5A4();
        if (param && param->mLavaAffect.ref())
            sub_71006D0490();
        return;
    }
    case 11: {
        auto* param = sub_71006DF5A4();
        if (!param || !param->mCurseAffect.ref())
            return;
        param = sub_71006DF5A4();
        _44 = param ? f32(param->mCurseInterval.ref()) : 0.0f;
        _8.set(0x800);
        param = sub_71006DF5A4();
        if (param && param->mCurseDamage.ref() > 0) {
            ConditionDamageInfo info;
            info.mKind = 11;
            info.mDamage = param->mCurseDamage.ref();
            sub_71006DF5CC(info);
        }
        return;
    }
    }
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
        return !(chemical->_b8 & 0x200);
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

bool Unk_710244dd20::sub_71006D1C34() {
    if (_10->get68f().load() != 0 && _10->get6fc() == ksys::phys::Material::Grudge)
        return true;
    if (auto* controller = _10->getCharacterController()) {
        if (auto* contacts = controller->sub_7100F635E4()) {
            for (auto it = contacts->begin(), end = contacts->end(); it != end; ++it) {
                const auto material = (*it)->material_mask_b.getMaterial();
                if (material == ksys::phys::Material::Grudge ||
                    material == ksys::phys::Material::GrudgeSlow)
                    return true;
            }
        }
    }
    return _50._30 && (_50._34 == 0 || _50._34 == 1);
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


// NON_MATCHING: actor loads across the attack query and shared result-store block.
bool Unk_710244dd20::sub_71006D1AB0(Unk_7100739634Result* request) {
    bool special_attack = false;
    if (!sub_71006D1DC4(request, &special_attack)) {
        request->_c = 0;
        return false;
    }
    auto* chemical = _10->getChemicalStuff();
    switch (request->kind) {
    case 2: {
        auto* param = sub_71006DF5A4();
        if ((!param || !*param->mBurnCritical) &&
            (m17(2) || !(param = sub_71006DF5A4()) || !*param->mBurnable ||
             (*chemical->mMaterial->attribute & 1) == 0 || (chemical->_be & 1) != 0 ||
             (chemical->_180 > 2 && request->_4 <= chemical->_180))) {
            request->_c = 2;
            return true;
        }
        if (special_attack)
            return true;
        request->_c = 3;
        return true;
    }
    case 3: {
        if (!m17(3)) {
            if (auto* param = sub_71006DF5A4()) {
                if (*param->mIceable)
                    return true;
            }
        }
        request->_c = 2;
        return true;
    }
    case 4: {
        if (!m17(4)) {
            if (auto* param = sub_71006DF5A4()) {
                if (*param->mElectricable && (*chemical->mMaterial->attribute & 8) != 0 &&
                    (chemical->_be & 4) == 0)
                    return true;
            }
        }
        request->_c = 2;
        return true;
    }
    default:
        return true;
    }
}


// NON_MATCHING: the attack search and the shared result stores have a different loop shape.
bool Unk_710244dd20::sub_71006D1DC4(Unk_7100739634Result* request, bool* special_attack) {
    auto* actor = _10;
    auto* damage_mgr = sub_710072BA90(actor);
    bool flags[3] = {false, true, false};
    auto* param = sub_71006DF5A4();
    flags[0] = param ? *param->mBurnCritical : false;
    ksys::act::ActorLinkConstDataAccess weapon;
    sub_7100734E68(&weapon, _10);
    flags[2] = sub_71002F1104(weapon);
    auto* chemical = actor->getChemicalStuff();
    if (!chemical)
        return false;

    s32 previous = -1;
    if (damage_mgr && damage_mgr->_6c >= 0) {
        previous = damage_mgr->_6c;
        if (previous < sub_71007A26AC(actor)) {
            auto* info = sub_71007A255C(actor, damage_mgr->_6c);
            if (!sub_71006D7038(actor, info) && sub_7100739634(request, chemical, info, flags)) {
                request->_8 = info->mDamage;
                request->_10 = info->_54;
                request->_14 = previous;
                *special_attack = ksys::act::hasTag(&info->_e8, 0xdf7c57f6);
                return true;
            }
        }
    }
    const s32 count = sub_71007A26AC(actor);
    for (s32 i = 0; i < count; ++i) {
        if (i == previous)
            continue;
        auto* info = sub_71007A255C(actor, i);
        if (info->sub_71007A1F68(0x800) && !sub_71006D7038(actor, info) &&
            sub_7100739634(request, chemical, info, flags)) {
            request->_8 = info->mDamage;
            request->_10 = info->_54;
            request->_14 = i;
            *special_attack = ksys::act::hasTag(&info->_e8, 0xdf7c57f6);
            return true;
        }
    }
    return false;
}


// NON_MATCHING: the request and condition-damage temporaries use separate stack slots.
void Unk_710244dd20::m18() {
    if (m17(4))
        return;
    auto* param = sub_71006DF5A4();
    if (!param || !*param->mElectricable)
        return;
    if (auto* chemical = _10->getChemicalStuff())
        chemical->sub_7100D945BC(chemical->sub_7100D945AC(), 1.0f, 1.0f);
    if ((_a & 8) == 0) {
        Unk_7100739634Result request{};
        request._14 = -1;
        if (sub_71006D1AB0(&request) && request.kind == 4 && request._18) {
            sub_71006DF5A4();
        } else if (auto* damage_param = sub_71006DF5A4()) {
            const s32 damage = s32(static_cast<f32>(*damage_param->mElectricDamage) * _d4);
            if (damage > 0) {
                ConditionDamageInfo info;
                info.mKind = 4;
                info.mDamage = damage;
                sub_71006DF5CC(info);
            }
        }
    }
    if (!_118.sub_7101241B6C())
        xlinkSearchAndEmit(_10, "ElectricShock", 2, &_118);
    _c0 |= 0x10;
    param = sub_71006DF5A4();
    _3c = param ? static_cast<f32>(*param->mElectricTime) : 0.0f;
    _8.set(0x10);
}

// NON_MATCHING: the request and condition-damage temporaries use separate stack slots.
void Unk_710244dd20::m19() {
    if (m17(3))
        return;
    auto* param = sub_71006DF5A4();
    if (!param || !*param->mIceable)
        return;
    param = sub_71006DF5A4();
    _34 = param ? static_cast<f32>(s32(static_cast<f32>(*param->mIceTime) * _d0)) : 0.0f;

    Unk_7100739634Result request{};
    request._14 = -1;
    const bool from_attack = sub_71006D1AB0(&request) && request.kind == 3 && request._18;
    s32 damage = 0;
    bool has_damage = false;
    if (from_attack) {
        sub_71006DF5A4();
        damage = request._c == 2 ? 0 : s32(static_cast<f32>(request._8) * _d0);
        has_damage = true;
    } else if (auto* damage_param = sub_71006DF5A4()) {
        damage = s32(static_cast<f32>(*damage_param->mIceDamage) * _d0);
        has_damage = true;
    }
    if (has_damage && damage > 0) {
        ConditionDamageInfo info;
        info.mKind = 3;
        info.mDamage = damage;
        param = sub_71006DF5A4();
        const bool critical = param && *param->mIceCritical;
        if (critical)
            info.mFlags = 2;
        if (from_attack) {
            info._8 = request._10;
            info.mFlags = critical ? 10 : 8;
            info._10 = request._14;
        }
        sub_71006DF5CC(info);
    }
    if (!_f8.sub_7101241B6C()) {
        xlinkSearchAndEmit(_10, "Frozen_Start", 2, &_f8);
        xlinkSearchAndEmit(_10, "Frozen", 2, &_f8);
    }
    _8.set(8);
}


bool Unk_710244dd20::sub_71006D0150() {
    if (m17(2))
        return false;
    auto* param = sub_71006DF5A4();
    return param && *param->mBurnable;
}

// NON_MATCHING: the actor load for the max-life query moves past the resource query.
// NON_MATCHING: same-TU parameter and classifier helpers inline; request stack slots differ.
void Unk_710244dd20::sub_71006D01A0(bool flag) {
    auto* actor = _10;
    if (m17(2))
        return;
    auto* param = sub_71006DF5A4();
    if (!param || !param->mBurnable.ref())
        return;
    auto* chemical = actor->getChemicalStuff();
    _30 = chemical && chemical->_c0 == 2 ? chemical->_182 : 3;
    param = sub_71006DF5A4();
    if (param && param->mBurnCritical.ref()) {
        ConditionDamageInfo info;
        info.mKind = 2;
        info.mDamage = actor->getMaxLife();
        info.mFlags = 2;
        sub_71006DF5CC(info);
    } else {
        param = sub_71006DF5A4();
        mBurnDuration = param ? f32(s32(f32(param->mBurnTime.ref()) * _cc)) : 0.0f;
        if (!_8.isOnBit(2)) {
            param = sub_71006DF5A4();
            mBurnInterval = param ? f32(param->mBurnDamageInterval.ref()) : 0.0f;
        }
        Unk_7100739634Result request{};
        request._14 = -1;
        if (sub_71006D1AB0(&request) && request.kind == 2 && request._18) {
            auto* source = _10;
            if (sub_71006DF5A4())
                ksys::act::sub_7100EDD308(source, _30);
        } else {
            auto* source = _10;
            if (sub_71006DF5A4()) {
                const s32 damage = s32(f32(ksys::act::sub_7100EDD308(source, _30)) * _cc);
                if (damage > 0) {
                    ConditionDamageInfo info;
                    info.mKind = 2;
                    info.mDamage = damage;
                    param = sub_71006DF5A4();
                    if (param && param->mBurnCritical.ref())
                        info.mFlags = 2;
                    if (flag)
                        info.mFlags |= 0x40;
                    sub_71006DF5CC(info);
                }
            }
        }
    }
    _8.setBit(2);
}

void Unk_710244dd20::sub_71006D03C8() {
    auto* param = sub_71006DF5A4();
    if (!param || !*param->mWetAffect)
        return;
    if (sub_71006DF5A4() && _10->getMaxLife() > 0) {
        ConditionDamageInfo info;
        info.mKind = 6;
        info.mDamage = sub_71006DF5A4() ? _10->getMaxLife() : 0;
        param = sub_71006DF5A4();
        if (param && *param->mWetAffect)
            info.mFlags = 2;
        sub_71006DF5CC(info);
    }
    _8.set(0x40);
}

// NON_MATCHING: the repeated water-depth condition uses a different branch arrangement.
void Unk_710244dd20::sub_71006D0490() {
    auto* param = sub_71006DF5A4();
    _40 = param ? static_cast<f32>(*param->mLavaDamageInterval) : 0.0f;
    auto* actor = _10;
    _8.set(0x400);
    if (actor->get68f().load() && actor->get6fc() == 11) {
        param = sub_71006DF5A4();
        if (param) {
            const f32 depth = *param->mLavaDeepDepth;
            if (depth >= 0.0f &&
                depth <= (actor->get68f().load() ? actor->get6f0() - actor->getMtx().m[1][3] : 0.0f)) {
                if (!_10->getDamageMgr())
                    return;
                ConditionDamageInfo info;
                info.mKind = 10;
                param = sub_71006DF5A4();
                info.mDamage = param ? *param->mLavaDeepDamage : 0;
                info.mFlags = 4;
                sub_71006DF5CC(info);
                return;
            }
        }
    }
    if (_40 >= 0.0f)
        _40 = 3.0f;
}

}  // namespace uking::act

namespace uking::act {
// NON_MATCHING: same-TU damage helpers inline and condition branches use different temporary storage.
void Unk_710244dd20::sub_71006CF338() {
    if (!_8.isOn(0x5c))
        return;
    auto* actor = _10;
    if (_8.isOnBit(2)) {
        auto* chemical = actor->getChemicalStuff();
        auto* param = sub_71006DF5A4();
        const s32 interval = param ? param->mBurnDamageInterval.ref() : 0;
        Unk_7100739634Result request{};
        request._14 = -1;
        const bool attack = sub_71006D1AB0(&request) && request.kind == 2 && request._18;
        bool refresh = attack;
        s32 damage = 0;
        if (attack) {
            auto* source = _10;
            if (sub_71006DF5A4())
                ksys::act::sub_7100EDD308(source, _30);
            if (request._c != 2)
                damage = s32(f32(request._8) * _cc);
        } else {
            refresh = chemical && interval > 0 && (chemical->_b8 & 4);
        }
        if (refresh) {
            ksys::Timer::update(&mBurnInterval, -1.0f);
            param = sub_71006DF5A4();
            mBurnDuration = param ? f32(s32(f32(param->mBurnTime.ref()) * _cc)) : 0.0f;
            if (attack) {
                ConditionDamageInfo info;
                info.mKind = 2;
                info.mDamage = damage;
                if (interval > 0 && mBurnInterval <= 0.0f) {
                    param = sub_71006DF5A4();
                    info.mDamage += param ? s32(f32(param->mBurnContinuousDamage.ref()) * _cc) : 0;
                    mBurnInterval = f32(interval);
                }
                param = sub_71006DF5A4();
                if (param && param->mBurnCritical.ref())
                    info.mFlags |= 2;
                info.mFlags |= 8;
                info._8 = request._10;
                info._10 = request._14;
                sub_71006DF5CC(info);
            } else if (mBurnInterval <= 0.0f) {
                ConditionDamageInfo info;
                info.mKind = 2;
                param = sub_71006DF5A4();
                info.mDamage = param ? s32(f32(param->mBurnContinuousDamage.ref()) * _cc) : 0;
                info.mFlags = 1;
                sub_71006DF5CC(info);
                mBurnInterval = f32(interval);
            }
        } else {
            ksys::Timer::update(&mBurnDuration, -1.0f);
            mBurnInterval = f32(interval);
            if (mBurnDuration <= 0.0f)
                m13(2);
        }
    }
    if (_8.isOnBit(3)) {
        auto* chemical = actor->getChemicalStuff();
        if (_d0 <= 0.0f || _139.isOnBit(1)) {
            _34 = 0.0f;
            m13(3);
        } else {
            f32 rate = 1.0f;
            if (sub_71006DF4F0(actor) ||
                (chemical && ((chemical->_b8 & 4) || chemical->sub_7100D914C0() > 0))) {
                if (auto* globals = ksys::act::GlobalParameter::instance()) {
                    if (auto* param = globals->getGlobalParam())
                        rate = param->mIceMeltSpeedOnContactFire.ref();
                }
            }
            ksys::Timer::update(&_34, -(rate * _38));
            if (_34 <= 0.0f)
                m13(3);
        }
    }
    if (_8.isOnBit(4)) {
        Unk_7100739634Result request{};
        request._14 = -1;
        if (sub_71006D1AB0(&request) && request.kind == 4 && request._18) {
            sub_71006DF5A4();
            ConditionDamageInfo info;
            info.mKind = 4;
            info.mDamage = request._c == 2 ? 0 : s32(f32(request._8) * _d4);
            info._8 = request._10;
            info.mFlags = 8;
            info._10 = request._14;
            sub_71006DF5CC(info);
        }
        ksys::Timer::update(&_3c, -1.0f);
        if (_3c <= 0.0f)
            m13(4);
    }
}

}  // namespace uking::act
