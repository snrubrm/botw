#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actDropData.h"

namespace ksys::act {

uking::act::Weapon* PlayerOrEnemy::getWeaponActor(s32 idx) {
    auto* proc = getWeapons()->mWeapons[idx].link.getProc(nullptr, nullptr);
    return sead::DynamicCast<uking::act::Weapon>(sead::DynamicCast<WeaponBase>(proc));
}

// NON_MATCHING: the original builds the empty profile string only in the else branch and keeps the
// equipped-weapon slot in a callee-saved register; ours schedules both differently.
void PlayerOrEnemy::m116() {
    auto* as_list = mASList;
    auto* weapon =
        sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(0));

    sead::SafeString empty("");
    const sead::SafeString* profile = &empty;
    if (weapon && getWeapons()->mWeapons[0]._10 == false)
        profile = &weapon->getProfile();
    as_list->goLimpFromHeadShotMaybe(0x2c, *profile, 0);

    const s32 idx = sub_71005DB96C(this);
    bool has_weapon;
    if (idx < 0) {
        has_weapon = false;
    } else {
        const s32 i = idx < 6 ? idx : 0;
        has_weapon = getWeapons()->mWeapons[i]._10 == false;
    }
    as_list->x_2(0x42, 0x1e, has_weapon, 0);
}

bool PlayerOrEnemy::hasNoWeaponActors() {
    // The first virtual weapon-container query is discarded in the original at 0x7100007e28.
    getWeapons();
    for (int i = 0; i < 6; ++i) {
        if (sead::IsDerivedFrom<uking::act::Weapon>(getWeapons()->getEquippedWeapon(i)))
            return false;
    }
    return true;
}

void sub_71000083CC(f32 value, PlayerOrEnemy* player) {
    if (auto* damage_mgr = sead::DynamicCast<uking::act::DamageManager>(player->getDamageMgr()))
        damage_mgr->_74 = value;
}

void sub_7100008468(f32 value, PlayerOrEnemy* player) {
    if (auto* damage_mgr = sead::DynamicCast<uking::act::DamageManager>(player->getDamageMgr()))
        damage_mgr->_78 = value;
}

bool PlayerOrEnemy::sub_710000759C() {
    getWeapons();
    for (s32 i = 0; i < 6; ++i) {
        acc::Weapon weapon;
        auto& link = getWeapons()->mWeapons[i].link;
        if (link.hasProc())
            ksys::act::acquireActor(&link, &weapon);
        if (weapon.isShield())
            return true;
    }
    return false;
}

void PlayerOrEnemy::m176() {
    getWeapons();
    ksys::act::ActorLinkConstDataAccess accessor;
    for (s32 i = 0; i < 6; ++i) {
        auto& weapon = getWeapons()->mWeapons[i];
        if (weapon.link.hasProc()) {
            ksys::act::acquireActor(&weapon.link, &accessor);
            updateWeaponDamage(&accessor, this, nullptr);
        }
    }
    updateWeaponDamageCopyInfo();
    if (auto* weapons = getWeapons())
        weapons->m3();
}

void PlayerOrEnemy::sub_7100008338(s32 value) {
    auto* damage_mgr = sead::DynamicCast<uking::act::DamageManager>(getDamageMgr());
    if (damage_mgr)
        damage_mgr->_68 = value;
}

void PlayerOrEnemy::m160() {
    auto* damage_mgr = sead::DynamicCast<uking::act::DamageManager>(getDamageMgr());
    if (!damage_mgr)
        return;

    getWeapons();
    s32 guard_power = 0;
    for (s32 i = 0; i < 6; ++i) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(i));
        if (weapon && weapon->_cf0 == 4) {
            const s32 power = weapon->getShieldGuardPower();
            if (guard_power <= power)
                guard_power = power;
        }
    }
    damage_mgr->_70 = guard_power;
    damage_mgr->applyDamage(*getLife());
    const s32 damage = damage_mgr->getDamage();
    if (damage > 0) {
        if (auto* drop_data = sead::DynamicCast<DropData>(getDropData()))
            drop_data->sub_71006DA914(damage_mgr, true);
    }
}

f32 PlayerOrEnemy::m153() {
    if (auto* object = sead::DynamicCast<uking::act::Unk_710244dd20>(m159()))
        return object->sub_71006D1D48();
    return 1.0f;
}

bool PlayerOrEnemy::m154() {
    if (auto* object = sead::DynamicCast<uking::act::Unk_710244dd20>(m159()))
        return object->sub_71006D1D7C();
    return false;
}

bool PlayerOrEnemy::m155() {
    if (auto* object = sead::DynamicCast<uking::act::Unk_710244dd20>(m159()))
        return object->sub_71006D1DA0();
    return false;
}

PlayerOrEnemy::PlayerOrEnemy(const CreateArg& arg) : DynamicActor(arg) {
    _1c0 = 2;
}

PlayerOrEnemy::~PlayerOrEnemy() = default;

BaseProc::InitResult PlayerOrEnemy::init_() {
    return weaponDroppedByEnemy() ? InitResult::Ok : InitResult::Failed;
}

bool PlayerOrEnemy::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    if (!constructActorAtk(heap))
        return false;
    initField868(heap);
    if (!initField858(heap))
        return false;
    if (m126() && _858 && !_858->m4(heap, nullptr))
        return false;
    return m157(heap);
}

void PlayerOrEnemy::onDeleteRequested_(DeleteReason reason) {
    DynamicActor::onDeleteRequested_(reason);
    if (sub_71011CBC28())
        getWeapons()->sub_7100EFCD98(this);
    else
        getWeapons()->sub_7100EFCC20(DeleteReason::_0);
}

s32 PlayerOrEnemy::getBaseAtkPower() {
    return getEnemyAtkPower();
}

const char* PlayerOrEnemy::getEquippedItem() {
    return nullptr;
}

void PlayerOrEnemy::m150() {
    if (auto* a = m159()) {
        for (int i = 0; i < 12; ++i)
            a->m13(i);
    }
}

void PlayerOrEnemy::m149(int index) {
    if (auto* a = m159())
        a->m13(index);
}

bool PlayerOrEnemy::startPreparingForPreDelete_() {
    return DynamicActor::startPreparingForPreDelete_();
}

void PlayerOrEnemy::initMaybe() {
    DynamicActor::initMaybe();
}

void PlayerOrEnemy::m51(bool on) {
    Actor::m51(on);
    getWeapons()->sub_7100EFCF10(on);
}

bool PlayerOrEnemy::m164(s32 idx, Actor* weapon, bool a3, bool a4) {
    return getWeapons()->equipWeapon(idx, weapon, a3, a4);
}

void PlayerOrEnemy::m117(Unk117* arg) {
    mWeapons.sub_7100EFD458(arg);
}

void PlayerOrEnemy::sub_7100007844(s32 idx) {
    getWeapons()->resetWeaponBaseProcLink(idx);
}

bool PlayerOrEnemy::isGuardJust() {
    return isGuard() && mActorFlags2.isOn(ActorFlag2::_10000000);
}

bool PlayerOrEnemy::m50() {
    if (Actor::m50())
        return true;
    return mWeapons.sub_7100EFD1F8();
}

bool PlayerOrEnemy::dropWeapon(int idx, const sead::Vector3f& pos, bool a2, bool a3, void* a4,
                               bool a5) {
    return getWeapons()->dropWeapon(idx, pos, a2, a3, a4, a5);
}

bool PlayerOrEnemy::sub_7100007A1C(const sead::Vector3f& velocity, bool a2, bool a3, void* a4,
                                   bool a5) {
    return getWeapons()->dropAllWeapons(velocity, a2, a3, a4, a5);
}

bool PlayerOrEnemy::sub_7100007A78(const sead::Vector3f& target, const sead::Vector3f& pos, bool a3, bool a4,
                                   void* a5, bool a6) {
    return getWeapons()->dropAllWeaponsToTarget(target, pos, a3, a4, a5, a6);
}

bool PlayerOrEnemy::sub_7100007ADC(int idx, const sead::Vector3f& target, void* a2) {
    return getWeapons()->dropWeaponM177(idx, target, a2);
}

f32 PlayerOrEnemy::sub_7100007B4C(int idx) {
    if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(idx)))
        return weapon->sub_71002ED434();
    return 0.0f;
}

f32 PlayerOrEnemy::sub_7100007BF8(int idx) {
    if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(idx)))
        return weapon->sub_71002ED730(false);
    return 0.0f;
}

bool PlayerOrEnemy::releaseWeapon(int idx) {
    return getWeapons()->dropWeaponM179(idx);
}

void PlayerOrEnemy::sub_7100007CA8(int idx, const uking::act::Unk_71002eda38& arg) {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(idx));
    if (weapon)
        weapon->sub_71002EDA38(arg);
}

void PlayerOrEnemy::sub_7100007D58(int idx, const uking::act::Unk_71002edaec& arg) {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(idx));
    if (weapon)
        weapon->sub_71002EDAEC(arg);
}

}  // namespace ksys::act

namespace ksys::act {

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

bool ActorLinkConstDataAccess::isPlayerOrEnemy() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    return sead::IsDerivedFrom<PlayerOrEnemy>(actor);
}

// NON_MATCHING: the original keeps the "result | 4" test as a 3-bit mask (and #7) and lays the loop
// increment out on the skip path; ours folds it to a compare after the & 1.
bool sub_7100007ED0(act::PlayerOrEnemy* player, act::Actor* arg) {
    player->getWeapons();
    for (u32 i = 0; i < 6; ++i) {
        auto* weapons = player->getWeapons();
        if (weapons->mWeapons[i]._10 == false) {
            auto* weapon =
                sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(i));
            u32 result = 4;
            if (weapon)
                result = weapon->sub_71002EDCE8(arg) & 1;
            if ((result | 4) != 4)
                return true;
        }
    }
    return false;
}


namespace acc {

inline act::PlayerOrEnemy* PlayerOrEnemy::getPlayerOrEnemy() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    return sead::DynamicCast<act::PlayerOrEnemy>(actor);
}

f32 PlayerOrEnemy::getGuardableAngle() const {
    if (auto* poe = getPlayerOrEnemy())
        return poe->getGuardableAngle();
    return sead::Mathf::deg2rad(100.0f);
}

bool PlayerOrEnemy::isGuard() const {
    auto* poe = getPlayerOrEnemy();
    if (!poe)
        return false;
    debugLog(0, "isGuard");
    return poe->isGuard();
}

bool PlayerOrEnemy::isGuardJust() const {
    auto* poe = getPlayerOrEnemy();
    if (!poe)
        return false;
    debugLog(0, "isGuardJust");
    return poe->isGuardJust();
}

bool PlayerOrEnemy::getWeapon(ActorLinkConstDataAccess* accessor, int idx) const {
    auto* poe = getPlayerOrEnemy();
    if (!poe)
        return false;
    auto& link = poe->getWeapons()->mWeapons[idx].link;
    if (!link.hasProc())
        return false;
    act::acquireActor(&link, accessor);
    return true;
}

bool PlayerOrEnemy::sub_710000975C(act::Actor* arg) const {
    auto* poe = getPlayerOrEnemy();
    if (!poe)
        return false;
    return ksys::act::sub_7100007ED0(poe, arg);
}

s32 PlayerOrEnemy::getMirrorLevel() const {
    auto* poe = getPlayerOrEnemy();
    if (!poe)
        return 0;
    debugLog(0, "getMirrorLevel");

    const s32 num = poe->getWeapons()->mWeapons.size();
    s32 result = 0;
    for (s32 i = 0; i < num; ++i) {
        Weapon weapon;
        auto& link = poe->getWeapons()->mWeapons[i].link;
        if (link.hasProc())
            act::acquireActor(&link, &weapon);
        const s32 level = getShieldMirrorLevel(weapon);
        if (weapon.isShield() && level > result)
            result = level;
    }
    return result;
}

s32 PlayerOrEnemy::getNumWeaponSlots() const {
    auto* poe = getPlayerOrEnemy();
    if (!poe)
        return 0;
    return poe->getWeapons()->mWeapons.size();
}

bool PlayerOrEnemy::sub_7100009AA8(int idx) const {
    auto* poe = getPlayerOrEnemy();
    if (!poe)
        return false;
    return poe->getWeapons()->mWeapons[idx]._10;
}

}  // namespace acc

}  // namespace ksys::act

namespace ksys::act {

bool PlayerOrEnemy::m81(const Message& message) {
    if (DynamicActor::m81(message))
        return true;
    auto* obj = m159();
    if (!obj)
        return false;
    return obj->m8(message);
}

bool PlayerOrEnemy::m151(u16 bit) {
    auto* obj = m159();
    if (!obj)
        return false;
    return obj->_8.isOnBit(bit);
}

bool PlayerOrEnemy::m152(u16 mask) {
    auto* obj = m159();
    if (!obj)
        return false;
    return obj->_8.isOn(mask);
}

bool PlayerOrEnemy::m170() {
    getWeapons();
    for (int i = 0; i < 6; ++i) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(i));
        if (weapon && weapon->x_6())
            return true;
    }
    return false;
}

}  // namespace ksys::act

namespace ksys::act {

bool PlayerOrEnemy::m171() {
    getWeapons();
    for (int i = 0; i < 6; ++i) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(i));
        if (weapon && actorCheckIsGuard(weapon))
            return true;
    }
    return false;
}

bool PlayerOrEnemy::m172() {
    getWeapons();
    for (int i = 0; i < 6; ++i) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(i));
        if (weapon && actorCheckIsGuardJust(weapon))
            return true;
    }
    return false;
}

}  // namespace ksys::act

namespace ksys::act {

bool PlayerOrEnemy::m163(int idx) {
    auto* weapons = getWeapons();
    if (idx >= 0) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(weapons->getEquippedWeapon(idx));
        return weapon && weapon->sub_71002E4374();
    }
    for (int i = 0; i < 6; ++i) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(i));
        if (weapon && !weapon->sub_71002E4374())
            return false;
    }
    return true;
}

}  // namespace ksys::act

namespace ksys::act {

void PlayerOrEnemy::preDelete2_(const PreDeleteArg& arg) {
    if (_858) {
        _858->m6();
        delete _858;
        _858 = nullptr;
    }
    sub_71006DC81C();
    m158();
    sub_71006DC864();
}

}  // namespace ksys::act

namespace ksys::act {

bool PlayerOrEnemy::isGuard() {
    if (!sub_710000759C() || !getASList())
        return false;
    return getASList()->sub_710115FBC8(14, nullptr, &as::ASList::Unk2::sub_71011638DC, true);
}

void PlayerOrEnemy::calcMaybe() {
    DynamicActor::calcMaybe();
    if (auto* chemical = getChemicalStuff()) {
        if (isGuard())
            chemical->sub_7100D91158(true);
        else
            chemical->sub_7100D91158(false);
    }
}

}  // namespace ksys::act

namespace ksys::act {

void PlayerOrEnemy::updateWeaponDamageCopyInfo() {
    getWeapons();
    for (s32 i = 0; i < 6; ++i) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(i));
        if (weapon && hasAttackInfo(weapon)) {
            sub_71007A3F34(this, weapon);
            return;
        }
    }
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: the tag result returns directly instead of passing through a shared loop result.
bool PlayerOrEnemy::m173() {
    getWeapons();
    for (s32 i = 0; i < 6; ++i) {
        auto* weapon = sead::DynamicCast<WeaponBase>(
            getWeapons()->mWeapons[i].link.getProc(nullptr, nullptr));
        if (weapon && hasTag(weapon, tags::WatchmanEquip))
            return true;
    }
    return false;
}

// NON_MATCHING: compiler folds the result/tag condition into one branch; the original
// retains an intermediate boolean and two tests before the same drop call.
bool PlayerOrEnemy::dropAllWeapons(const sead::Vector3f& pos) {
    getWeapons();
    bool result = true;
    for (s32 i = 0; i < 6; ++i) {
        auto* weapon = sead::DynamicCast<WeaponBase>(
            getWeapons()->mWeapons[i].link.getProc(nullptr, nullptr));
        if (weapon) {
            const bool isWatchmanEquip = hasTag(weapon, tags::WatchmanEquip);
            result = result && (!isWatchmanEquip ||
                                getWeapons()->dropWeapon(i, pos, false, false, nullptr, false));
        }
    }
    return result;
}

}  // namespace ksys::act

namespace ksys::act {

void PlayerOrEnemy::m76(VFR::ScopedDeltaSetter* setter) {
    DynamicActor::m76(setter);
    sub_7100009C5C();
}

void PlayerOrEnemy::sub_7100009C5C() {
    getWeapons();
    for (s32 i = 0; i < 6; ++i) {
        auto* weapon = sead::DynamicCast<uking::act::Weapon>(getWeapons()->getEquippedWeapon(i));
        if (weapon && *weapon->getLife() <= 0)
            getWeapons()->dropWeapon(i, sead::Vector3f::zero, false, false, nullptr, false);
    }
}

}  // namespace ksys::act

namespace ksys::act {

bool PlayerOrEnemy::m165(sead::BufferedSafeString* out) {
    return false;
}

// Moves this actor in front of its listed weapons: when it comes after the first listed weapon, the two swap.
void PlayerOrEnemy::m147(sead::PtrArray<Actor>* actors) {
    const s32 num = actors->size();
    s32 index = -1;
    for (s32 i = 0; i < num; ++i) {
        if (actors->at(i) == this) {
            index = i;
            break;
        }
    }
    if (index < 0)
        return;
    const s32 weapon = mWeapons.sub_7100EFD524(actors);
    if (index > weapon && u32(actors->size()) > u32(index) && u32(actors->size()) > u32(weapon))
        actors->swap(weapon, index);
}

}  // namespace ksys::act
