#pragma once

#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::act {
struct Unk_71002eda38;
struct Unk_71002edaec;
}  // namespace uking::act

namespace ksys::act {

// TODO: incomplete. The vtable has 177 slots.
class PlayerOrEnemy : public DynamicActor {
    SEAD_RTTI_OVERRIDE(PlayerOrEnemy, DynamicActor)
public:
    explicit PlayerOrEnemy(const CreateArg& arg);
    ~PlayerOrEnemy() override;

protected:
    InitResult init_() override;
    bool startPreparingForPreDelete_() override;
    void onDeleteRequested_(DeleteReason reason) override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    f32 getGuardableAngle() override { return sead::Mathf::deg2rad(100.0f); }
    void m49() override;
    bool m50() override;
    void m51() override;
    bool m55() override { return true; }
    void initMaybe() override;
    void calcMaybe() override;
    void m73() override;
    void m76(VFR::ScopedDeltaSetter* setter) override;
    bool m81(const Message& message) override;
    ActorWeapons* getWeapons() override { return &mWeapons; }
    void m116() override;
    void m117() override;
    void m147() override;

    void m149(int) override;
    void m150() override;
    bool m151(u16 bit) override;
    bool m152(u16 mask) override;
    f32 m153() override;
    bool m154() override;
    bool m155() override;
    void m160() override;

    // FIXME: figure out return types, parameters and names
    virtual bool m163(int idx);
    virtual void m164();
    virtual void m165();
    virtual bool isGuard();
    virtual bool isGuardJust();
    virtual void getBaseAtkPower();
    virtual bool m169() { return false; }
    virtual bool m170();
    virtual void m171();
    virtual void m172();
    virtual bool m173();
    virtual bool weaponDroppedByEnemy() { return true; }
    virtual void getEquippedItem();
    virtual void m176();

    // Forward a request to the equipped weapon in slot `idx` if it is a uking::act::Weapon
    // (Weapon::sub_71002EDA38 / sub_71002EDAEC). Placeholder names.
    void sub_7100007CA8(int idx, const uking::act::Unk_71002eda38& arg);
    void sub_7100007D58(int idx, const uking::act::Unk_71002edaec& arg);

protected:
    /* 0xb90 */ ActorWeapons mWeapons{this};
    /* 0xc30 */ f32 _c30 = 100.0;
    /* 0xc34 */ u32 _c34;  // not initialised by the ctor; Enemy members start at 0xc38
};
KSYS_CHECK_SIZE_NX150(PlayerOrEnemy, 0xc38);

namespace acc {

// Access to a PlayerOrEnemy through an ActorConstDataAccess (CSV: act::acc::PlayerOrEnemy).
// TODO: incomplete
class PlayerOrEnemy : public ActorConstDataAccess {
public:
    f32 getGuardableAngle() const;
    bool getWeapon(ActorConstDataAccess* accessor, int idx) const;
    bool isGuard() const;
    bool isGuardJust() const;

protected:
    act::PlayerOrEnemy* getPlayerOrEnemy() const;
};
KSYS_CHECK_SIZE_NX150(PlayerOrEnemy, 0x18);

}  // namespace acc

}  // namespace ksys::act
