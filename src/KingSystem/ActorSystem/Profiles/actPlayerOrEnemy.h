#pragma once

#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::act {
class Weapon;
struct WeaponModifierInfo;
struct Unk_71002eda38;
struct Unk_71002edaec;
}  // namespace uking::act

namespace uking::ui {
class OnUiActorMgr;
}

namespace ksys::act {

// TODO: incomplete. The vtable has 177 slots.
class PlayerOrEnemy;
// 0x71000083cc / 0x7100008468 (unnamed / CSV Player::updateResistThunderXXX): store the value in the
// damage manager's _74 / _78; the player is the second argument in the original.
void sub_71000083CC(f32 value, PlayerOrEnemy* player);
void sub_7100008468(f32 value, PlayerOrEnemy* player);

// 0x71002f06d0 (declaration only; CSV name): applies the weapon damage of the weapon in `accessor` to `actor`,
// with an optional modifier; called by PlayerOrEnemy::m176 and the weapon code.
void updateWeaponDamage(ksys::act::ActorLinkConstDataAccess* accessor, ksys::act::BaseProc* actor,
                        const ::uking::act::WeaponModifierInfo* modifier);

class PlayerOrEnemy : public DynamicActor {
    SEAD_RTTI_OVERRIDE(PlayerOrEnemy, DynamicActor)
    // OnUiActorMgr::sub_71009079EC sets _c34 of the pause menu player
    friend class uking::ui::OnUiActorMgr;

public:
    explicit PlayerOrEnemy(const CreateArg& arg);
    ~PlayerOrEnemy() override;

    // 0x71007b2724 (CSV Player::getWeapon; lane4 s45, name is a guess): the Weapon actor linked in slot `idx` (the
    // weapons object comes from the virtual getWeapons()).
    uking::act::Weapon* getWeaponActor(s32 idx);
    // 0x7100007844 (declared only; unnamed in the CSV; placeholder name): ActorWeapons::resetWeaponBaseProcLink(idx) on the
    // virtual getWeapons().
    void sub_7100007844(s32 idx);

protected:
    InitResult init_() override;
    bool startPreparingForPreDelete_() override;
    void onDeleteRequested_(DeleteReason reason) override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    f32 getGuardableAngle() override { return sead::Mathf::deg2rad(100.0f); }
    bool m49() override;
    bool m50() override;
    void m51(bool on) override;
    bool m55() override { return true; }
    void initMaybe() override;
    void calcMaybe() override;
    void m73() override;
    void m76(VFR::ScopedDeltaSetter* setter) override;
    bool m81(const Message& message) override;
    ActorWeapons* getWeapons() override { return &mWeapons; }
    void m116() override;
    void m117(Unk117* arg) override;
    void m147(sead::PtrArray<Actor>* actors) override;
    // 0x7100007e08: no active equipped actor derives from uking::act::Weapon.
    bool hasNoWeaponActors();

    void m149(int) override;
    void m150() override;
    bool m151(u16 bit) override;
    bool m152(u16 mask) override;
    f32 m153() override;
    bool m154() override;
    bool m155() override;
    void m160() override;
    // 0x7100008338 (unnamed in the CSV; placeholder name): stores `value` in the damage manager's _68
    // (the WolfLinkRoot timer). Called next to m160.
    void sub_7100008338(s32 value);

    // FIXME: figure out return types, parameters and names
    virtual bool m163(int idx);
    virtual bool m164(s32 idx, Actor* weapon, bool a3, bool a4);
    virtual bool m165(sead::BufferedSafeString* out);
    virtual bool isGuard();
    virtual bool isGuardJust();
    virtual s32 getBaseAtkPower();
    virtual bool m169() { return false; }
    virtual bool m170();
    virtual bool m171();
    virtual bool m172();
    virtual bool m173();
    virtual bool weaponDroppedByEnemy() { return true; }
    // The equipped item's actor name (null without one).
    virtual const char* getEquippedItem();
    virtual void m176();

    // 0x710073632c (CSV name): enemy attack power (0 for non-enemies); the base getBaseAtkPower.
    s32 getEnemyAtkPower();

    // Forward a request to the equipped weapon in slot `idx` if it is a uking::act::Weapon
    // (Weapon::sub_71002EDA38 / sub_71002EDAEC). Placeholder names.
    void sub_7100007CA8(int idx, const uking::act::Unk_71002eda38& arg);
    void sub_7100007D58(int idx, const uking::act::Unk_71002edaec& arg);
    // 0x7100007a1c (declared only, lane1 s23; placeholder name): forwards to the actor's ActorWeapons
    // (0xefc3d4: drops the weapons with the given velocity). LandHumEnemyFindBait::leave_ passes
    // (Vector3f::zero, false, false, nullptr, false); `a4` is an object of unknown type.
    bool sub_7100007A1C(const sead::Vector3f& velocity, bool a2, bool a3, void* a4, bool a5);
    // 0x7100007870 (CSV PlayerOrEnemy::dropWeapon): forwards to ActorWeapons::dropWeapon.
    bool dropWeapon(int idx, const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5);
    // lane4 s46 (placeholder names, unnamed in the CSV). 0x7100007a78 / 0x7100007adc: forward to
    // ActorWeapons::dropAllWeaponsToTarget / dropWeaponM177.
    bool sub_7100007A78(const sead::Vector3f& target, const sead::Vector3f& pos, bool a3, bool a4, void* a5,
                        bool a6);
    bool sub_7100007ADC(int idx, const sead::Vector3f& target, void* a2);
    // 0x7100007b4c / 0x7100007bf8: Weapon::sub_71002ED434() / sub_71002ED730(false) of the weapon in slot `idx`
    // if it is a uking::act::Weapon (0 otherwise).
    f32 sub_7100007B4C(int idx);
    f32 sub_7100007BF8(int idx);
    // 0x7100007b20 (CSV Player::releaseWeapon): forwards to ActorWeapons::dropWeaponM179.
    bool releaseWeapon(int idx);
    // 0x710000759c (declaration only): weapon-state prerequisite checked by isGuard().
    bool sub_710000759C();
    // Name from CSV 0x7100007084.
    void updateWeaponDamageCopyInfo();
    // 0x7100009c5c: forget equipped weapons whose life is depleted.
    void sub_7100009C5C();
    // Name/signature from CSV 0x71000078d4 and its original argument/return use.
    bool dropAllWeapons(const sead::Vector3f& pos);

protected:
    /* 0xb90 */ ActorWeapons mWeapons{this};
    /* 0xc30 */ f32 _c30 = 100.0;
    /* 0xc34 */ bool _c34;  // not initialised by the ctor (lane2 s47: a byte flag, read by PauseMenuPlayerRoot::calc_)
public:
    // 2026-10-07: OnUiActorMgr 907190 writes the inverse player flag; 907738/907C10 clear/set it.
    // PauseMenuPlayerRoot 4F548C and actor helpers 6E9C24/6E9E34 pass it to ASList.
    bool _c35;

protected:
    u8 _c36[2];  // Enemy members start at 0xc38

public:
    // name is a guess
    bool getFlagC34() const { return _c34; }
};
KSYS_CHECK_SIZE_NX150(PlayerOrEnemy, 0xc38);

namespace acc {

// Access to a PlayerOrEnemy through an ActorLinkConstDataAccess (CSV: act::acc::PlayerOrEnemy).
// TODO: incomplete
class PlayerOrEnemy : public ActorLinkConstDataAccess {
public:
    f32 getGuardableAngle() const;
    bool getWeapon(ActorLinkConstDataAccess* accessor, int idx) const;
    bool isGuard() const;
    bool isGuardJust() const;
    // 0x7100009860 (lane4 s44; names are guesses): the number of weapon slots (the weapons object is fetched through
    // its virtual getter and discarded), 0 without a PlayerOrEnemy.
    s32 getNumWeaponSlots() const;
    // 0x71000095a0 (CSV name): the highest shield mirror level among the player's weapons, 0 without one.
    s32 getMirrorLevel() const;
    // 0x7100009aa8: the flag `_10` of the weapon slot `idx`.
    bool sub_7100009AA8(int idx) const;

protected:
    act::PlayerOrEnemy* getPlayerOrEnemy() const;
};
KSYS_CHECK_SIZE_NX150(PlayerOrEnemy, 0x18);

}  // namespace acc

}  // namespace ksys::act
