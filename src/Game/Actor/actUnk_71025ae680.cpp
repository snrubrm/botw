#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/actLastBoss.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710072BA90.h"

namespace uking::act {


bool sub_71006DF43C(ksys::act::Actor* actor) {
    if (!actor->get68f() || int(ksys::phys::Material(actor->get6fc())) != ksys::phys::Material::Water)
        return false;
    return ksys::phys::MaterialMask::getSubMaterialName(ksys::phys::Material::Water, actor->get700()) == "Water_Ice";
}

bool sub_71006DF4F0(ksys::act::Actor* actor) {
    if (!actor->get68f() || int(ksys::phys::Material(actor->get6fc())) != ksys::phys::Material::Water)
        return false;
    return ksys::phys::MaterialMask::getSubMaterialName(ksys::phys::Material::Water, actor->get700()) == "Water_Hot";
}

void Unk_71025ae680::sub_71006DF5CC(const act::ConditionDamageInfo& info) {
    auto* manager = sead::DynamicCast<act::DamageManagerBase>(_10->getDamageMgr());
    if (manager)
        manager->applyRequestedDamage(info);
}

void Unk_71025ae680::m6() {
    if (!(_a & 3))
        m10();
    _a &= ~0x24;
}

void Unk_71025ae680::m7() {
    auto* actor = _10;
    if (!actor->m50())
        _a &= ~8;
    else
        _a |= 8;
    _a &= ~0x10;

    sub_71006DF8AC();

    if (auto* chemical = actor->getChemicalStuff()) {
        if (chemical->_c & 1)
            _a |= 0x20;
        else
            _a &= ~0x20;
    }

    if (_18 < 0)
        return;
    if (sub_71007A26AC(_10) <= _18)
        return;
    auto* attack = sub_71007A255C(_10, _18);
    if (!attack)
        return;
    if (sub_71006D7038(actor, attack))
        return;
    if (attack->_18 & 9)
        _a |= 0x10;
    if (!attack->sub_71007A1F68(0x800) || (attack->_18 & 2))
        return;
    if (attack->_18 & 9)
        sub_7100732664(actor, &attack->_e8, attack->_c0, 1, attack->_f8);
    else
        sub_710073278C(actor, &attack->_e8, attack->_c0, 0, attack->_f8);
}

// NON_MATCHING: the flags array sits at sp+0x2c here, at sp+0x28 in the original (4-byte stack slot
// difference); every instruction and store is otherwise identical.
void Unk_71025ae680::sub_71006DF8AC() {
    auto* actor = _10;
    _18 = -1;
    auto* damage_mgr = sub_710072BA90(actor);
    Unk_7100739634Result result{};
    result._14 = -1;
    bool flags[3] = {};
    auto* chemical = actor->getChemicalStuff();
    if (!chemical)
        return;

    s32 previous = -1;
    if (damage_mgr && damage_mgr->_6c >= 0) {
        previous = damage_mgr->_6c;
        if (sub_71007A26AC(actor) > previous) {
            auto* attack = sub_71007A255C(actor, damage_mgr->_6c);
            if (!sub_71006D7038(actor, attack) &&
                sub_7100739634(&result, chemical, attack, flags)) {
                _18 = previous;
                return;
            }
        }
    }

    const s32 count = sub_71007A26AC(actor);
    if (count < 1)
        return;
    for (s32 i = 0; i < count; ++i) {
        if (i == previous)
            continue;
        auto* attack = sub_71007A255C(actor, i);
        if (attack->sub_71007A1F68(0x800) && !sub_71006D7038(actor, attack) &&
            sub_7100739634(&result, chemical, attack, flags)) {
            _18 = i;
            return;
        }
    }
}

void Unk_71025ae680::sub_71006DF67C(s32 value) {
    auto* actor = _10;
    if (auto* life = actor->getLife()) {
        const s32 max_life = actor->getMaxLife();
        *life += value;
        if (*life > max_life)
            *life = max_life;
        else if (*life < 0)
            *life = 0;
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

// NON_MATCHING: our build inlines sub_71006DF5A4 / sub_71006DF5CC (same TU); the original calls them.
void Unk_710244eb48::sub_71006E264C() {
    auto* param = sub_71006DF5A4();
    if (!param || !param->mGerudoHeroAffect.ref() || _1c)
        return;

    param = sub_71006DF5A4();
    ConditionDamageInfo info;
    info.mKind = 4;
    info.mDamage = param ? param->mGerudoHeroDamage.ref() : 0;
    info._8 = 4;
    info.mFlags = 0x80;
    info._10 = -1;
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

// NON_MATCHING: our build inlines sub_71006DF5A4 / sub_71006DF5CC (same TU); the original calls them.
void Unk_710244fee8::sub_71006EE474() {
    auto* param = sub_71006DF5A4();
    if (!param || !param->mGerudoHeroAffect.ref() || _1c)
        return;

    param = sub_71006DF5A4();
    ConditionDamageInfo info;
    info.mKind = 4;
    info.mDamage = param ? param->mGerudoHeroDamage.ref() : 0;
    info._8 = 4;
    info.mFlags = 0x180;
    info._10 = -1;
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

// NON_MATCHING: the final bit update is a branch in the original (ours: csel)
void Unk_71025ae680::sub_71006DFA04(bool enable) {
    const bool enabled = _a & 1;
    if (enable) {
        if (enabled)
            return;
        for (s32 i = 0; i < 12; ++i)
            m13(i);
    } else if (!enabled) {
        return;
    }
    m11(enable);
    if (enable)
        _a |= 1;
    else
        _a &= ~1;
}

void Unk_71025ae680::sub_71006EF05C(s32 condition) {
    _8.resetBit(condition);
    auto* chemicals = _10->getChemicalContainer();
    if (!chemicals)
        return;
    const s32 num = chemicals->_80;
    for (s32 i = 0; i < num; ++i) {
        auto* chemical = chemicals->sub_7100E380FC(i);
        if (!chemical)
            return;
        switch (condition) {
        case 2:
            chemical->sub_7100D90B78();
            break;
        case 3:
            chemical->sub_7100D8EEE0();
            break;
        case 4:
            chemical->sub_7100D945BC(chemical->sub_7100D945AC(), 1.0f, 1.0f);
            break;
        default:
            break;
        }
    }
}

void Unk_71025ae680::sub_71006EEFB4(s32 condition, s32 chemical_idx) {
    _8.resetBit(condition);
    if (chemical_idx < 0)
        return;
    auto* chemicals = _10->getChemicalContainer();
    if (!chemicals)
        return;
    auto* chemical = chemicals->sub_7100E380FC(chemical_idx);
    if (!chemical)
        return;
    switch (condition) {
    case 3:
        chemical->sub_7100D8EEE0();
        break;
    case 4:
        chemical->sub_7100D945BC(chemical->sub_7100D945AC(), 1.0f, 1.0f);
        break;
    case 2:
        chemical->sub_7100D90B78();
        break;
    default:
        break;
    }
}

void Unk_71025ae680::sub_71006DF750() {
    m13(11);
}

void Unk_71025ae680::sub_71006DF6EC() {
    m13(7);
    m13(8);
    m13(9);
    m13(10);
}

ksys::res::DamageParam* Unk_71025ae680::sub_71006DF5A4() {
    if (!_10 || !_10->getParam())
        return nullptr;
    return _10->getParam()->getRes().mDamageParam;
}

bool sub_71006DFB58() {
    auto* world = ksys::world::Manager::instance();
    if (!world)
        return false;
    auto* chemical_mgr = world->getChemicalMgr();
    if (!chemical_mgr)
        return false;
    auto* holder = chemical_mgr->_ae8;
    if (!holder)
        return false;
    return holder->_c8 & 0x100000;
}

}  // namespace uking::act
