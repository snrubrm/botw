#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/World/worldManager.h"

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

void Unk_710244ebc8::m13(int index) {
    if (index == 4)
        _20.fadeXLink();
    _8.resetBit(index);
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
