#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace ksys::eco {
enum class WeaponModifier;
}

namespace uking::act {
class OptionalWeapon;
}

namespace uking::action {
class EquipedAction;
}

namespace ksys::act {

class InstParamPack;
namespace acc {
class WeaponBase;
}

// 0x0000007100ef2808
eco::WeaponModifier getRandomWeaponModifier(eco::WeaponModifier modifier,
                                            const sead::SafeString& actor_name);

// TODO
class WeaponBase : public Actor {
    SEAD_RTTI_OVERRIDE(WeaponBase, Actor)
public:
    explicit WeaponBase(const CreateArg& arg);
    ~WeaponBase() override;
    Actor* m31() override;
    void calcMaybe() override;
    void m70() override;
    void updatePositionMaybe() override;
    bool m86() override;
    void m92(phys::RigidBody* body) override;
    bool m142() override { return false; }

    bool areExtraActorsReady() const;
    // 0x7100ef91b0 (lane4 s45, unnamed in the CSV): sets `_ab0` (and the OptionalWeapon's `_94c` when `propagate`).
    void sub_7100EF91B0(bool ready, bool propagate);

    // FIXME: figure out return types, parameters and names
    virtual Actor* getParentActor();
    Actor* m48() override;
    // Inline-only in the original (accessor wrappers in the Weapon TU read `_938` directly); name is a guess.
    BaseProcLink& getParentLink() { return _938; }
    virtual bool hasParentActor_() { return _938.hasProc(); }
    virtual bool hasParentActor() { return hasParentActor_(); }
    virtual bool isParentEqualToById(BaseProc* proc) { return _938.hasProcById(proc); }
    virtual bool isParentEqual(const BaseProcLink& link) { return _938 == link; }
    virtual bool m153() { return false; }
    // 0x7100ef5e3c: the actor linked at +0x938 passes ActorConstDataAccess::sub_7100D12E64.
    virtual bool m154();
    virtual bool m155() { return false; }
    virtual bool m156() { return false; }
    virtual bool isParentPlayer() { return false; }
    virtual bool isParentNpc() { return false; }
    virtual const sead::SafeString& m159() const;
    virtual const sead::SafeString& m160() const;
    virtual bool m161() { return _958.hasProc(); }
    // The OptionalWeapon linked at +0x958 (two getProc variants: m162 passes the other-proc argument).
    virtual uking::act::OptionalWeapon* m162();
    virtual uking::act::OptionalWeapon* m163();
    virtual const sead::SafeString& m164();
    // BowShoot::sub_710033BDB4 passes output vectors to slots 165/166 for RotOffset/TransOffset.
    virtual void m165(sead::Vector3f* out);
    virtual void m166(sead::Vector3f* out);
    virtual void m167(sead::Vector3f* out);
    virtual void m168(sead::Vector3f* out);
    // 0x7100ef57dc: the shield-affect rotation offset of the weapon type (SmallSword / LargeSword / Spear, the grab
    // variant of the spear when m155), zero when held by an unarmed owner or for the bow / shield types.
    virtual void m169(sead::Vector3f* out);
    // 0x7100ef598c: like m169 with mAffectTransOffsetShield (spear: mGrabAffectTransOffsetShield when m155).
    virtual void m170(sead::Vector3f* out);
    // 0x7100ef5b3c: like m169 with mAffectRotOffsetBow (no grab variant).
    virtual void m171(sead::Vector3f* out);
    // 0x7100ef5cbc: like m169 with mAffectTransOffsetBow (no grab variant).
    virtual void m172(sead::Vector3f* out);
    virtual bool m173(s32 index, Actor* actor, const char* name, const char* other_name,
                      bool a5, bool a6);
    virtual bool m174();
    // 0x7100ef61c4. Stores the position at _910 (+ _91c = -1, _920 = 2) and the three flags (a2 -> _924,
    // a3 -> _922, a5 -> _923) under _840; returns false if _925 is set. `a4` is an object of a class
    // whose RTTI is at 0x71025b1538 (Weapon::x_4 casts it; callers pass nullptr; the base ignores it).
    virtual bool m175(const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5);
    // 0x7100ef6304. Like m175 (the position goes to _910, the flags a3 -> _924, a4 -> _922, a6 -> _923), plus the
    // second position `target` (_928) and _936 = true; `a5` is unused.
    virtual bool m176(const sead::Vector3f& target, const sead::Vector3f& pos, bool a3, bool a4, void* a5,
                      bool a6);
    // 0x7100ef6464. Like m175 with the position zero and no flags, the second position `target` (_928) and
    // _934 = true; `a2` is unused.
    virtual bool m177(const sead::Vector3f& target, void* a2);
    virtual bool m178(const sead::Vector3f& pos);
    // 0x7100ef669c: resets the links and sets _920 = 3 (drops the optional weapon).
    virtual void m179();
    virtual void m180();
    virtual void m181() {}
    virtual bool m182();
    virtual bool m183() { return false; }
    virtual bool m184() { return false; }
    // Public accessors for the two fields Enemy::m141 reads directly (inline-only in the original).
    u8 get920() const { return _920; }
    // inline-only in the original (WeaponRootAI::sub_7100E1F34C stores 0xff); name is a guess
    void set920(u8 value) { _920 = value; }
    bool get921() const { return _921; }
    virtual bool m185() { return _920 == 0; }
    virtual bool m186() { return _921; }
    virtual bool m187() { return _925; }
    virtual bool m188() { return _920 == 1; }
    virtual bool m189() { return _920 == 2; }
    virtual bool m190() { return _920 == 3; }
    virtual bool m191() { return _920 == 4; }
    virtual bool m192() { return _922; }
    virtual bool m193() { return _923; }
    virtual bool m194() { return false; }
    virtual bool m195() { return false; }
    virtual bool m196();
    virtual bool m197(sead::SafeString* out);
    virtual bool m198();
    virtual void m199();
    virtual void m200();
    // 0x7100ee6afc (CSV WeaponBase::x_0): called by m200 (clears actor flags 0x21 and updates the model).
    void sub_7100EE6AFC();
    // Original weapon update helpers at 0xef345c and 0xef3664.
    void sub_7100EF345C();
    void sub_7100EF3664();
    virtual void m201();
    virtual void m202(bool on) { _9f4.change(1, on); }
    virtual bool m203() { return _9f4.isOn(1); }
    virtual bool m204() { return false; }
    virtual bool m205() { return false; }
    virtual void m206(bool play_sound) {}
    virtual void m207();
    // 0x7100ef4388 (lane4 s48: was Weapon::hasCanPullGiantObjectTag; the address is in the WeaponBase code, so Weapon::getMaxHp
    // calls it out of line).
    bool hasCanPullGiantObjectTag();
    virtual void m208();
    virtual void m209() {}
    virtual bool m210() { return false; }
    virtual bool m211() { return false; }
    virtual bool m212() { return false; }
    virtual bool m213() { return false; }
    virtual bool m214() { return true; }
    virtual void m215() {}
    virtual bool m216() { return false; }
    // 0x7100efbab8: takes an out SafeString (EquipedAction::calc_ passes a default-constructed one).
    virtual bool m217(sead::SafeString* out);
    virtual bool m218() { return false; }
    virtual bool isMasterSword() { return false; }
    virtual void masterSwordReturnToForest() {}
    virtual void* m221();
    virtual bool m222() { return false; }
    virtual bool m223(s32* out);
    virtual void m224(sead::Vector3f* out) { *out = sead::Vector3f::ones; }
    virtual bool m225() { return false; }
    virtual bool m226() { return false; }
    virtual bool m227() { return false; }
    virtual void m228(BaseProc* proc) {}
    virtual void m229(BaseProc* proc) {}
    virtual bool isWeaponType0Or1Or2() const;
    virtual bool m231() const;
    virtual bool m232() const;
    virtual bool m233() const;
    virtual bool isWeaponType4() const;
    virtual bool isWeaponType3() const;
    virtual bool isBoomerang() { return false; }
    // 0x7100ef9514 / 0x7100ef9570: whether `actor` has a profile the owner can hold the weapon with (see
    // sub_7100EFD700; m238: Player / PauseMenuPlayer) and the weapon has a name (m159 / m160).
    virtual bool m237(Actor* actor);
    virtual bool m238(Actor* actor);
    virtual bool m239() { return false; }
    // lane4 s51: m240 - m243 write an offset (Weapon: the one of the equipped weapon of a player parent through
    // acc::WeaponBase::m169 - m172).
    virtual void m240(sead::Vector3f* out) {}
    virtual void m241(sead::Vector3f* out) {}
    virtual void m242(sead::Vector3f* out) {}
    virtual void m243(sead::Vector3f* out) {}
    virtual void m244() {}
    // lane4 s51: Weapon writes the SquatPlayerHold{Trans,Rot}AddOffset of its weapon type (m245: Trans, m246: Rot).
    virtual void m245(sead::Vector3f* out) {}
    virtual void m246(sead::Vector3f* out) {}
    // lane4 s51: Weapon writes an offset of the parent player's armor (acc::Armor::sub_7100E2CD1C / sub_7100E2CBB8).
    virtual void m247(sead::Vector3f* out) {}
    virtual void m248(sead::Vector3f* out) {}
    virtual void m249(sead::Matrix34f* matrix, Actor* actor) {}
    virtual bool m250(Actor* actor);

    static void requestCreateWeaponActor(const char* actor, const sead::Matrix34f& matrix,
                                         f32 scale, sead::Heap* heap,
                                         ksys::act::BaseProcHandle* handle, s32 life,
                                         ksys::act::InstParamPack* params, s32 task_lane_id);

protected:
    // EquipedAction binds the weapon through `_a00` (lane3 s23).
    friend class uking::action::EquipedAction;
    friend class acc::WeaponBase;

    // lane4 s30: BaseProc / Actor overrides of the weapon (slots 22, 23, 12, 13).
    IsSpecialJobTypeResult isSpecialJobType_(JobType type) override;
    bool canWakeUp_() override;
    void onSleepRequested_(SleepWakeReason reason) override;
    void onWakeUpRequested_(SleepWakeReason reason) override;
    void onDeleteRequested_(DeleteReason reason) override;
    void onEnterDelete_() override;

    // TODO
    sead::CriticalSection _840;
    BaseProcLink _880;
    BaseProcLink _890;
    sead::FixedSafeString<32> _8a0;
    sead::FixedSafeString<32> _8d8;
    sead::Vector3f _910{0, 0, 0};
    s32 _91c = -1;
    u8 _920 = 0xff;
    bool _921 = false;
    bool _922 = false;
    bool _923 = false;
    u8 _924 = 0;
    bool _925 = false;
    u8 _926[0x928 - 0x926];
    sead::Vector3f _928{0, 0, 0};
    bool _934 = false;
    u8 _935 = 0;
    bool _936 = false;
    u8 _937;
    BaseProcLink _938;
    BaseProcLink _948;
    BaseProcLink _958;
    sead::FixedSafeString<32> _968;
    sead::FixedSafeString<32> _9a0;
    u64 _9d8 = 0;
    u64 _9e0 = 0;
    u64 _9e8 = 0;
    s32 _9f0 = -1;
    sead::BitFlag8 _9f4;
    u8 _9f5[0x9f8 - 0x9f5];
    s32 _9f8 = -1;
    u8 _9fc[0xa00 - 0x9fc];
    ModelBindInfo _a00;
    BaseProcHandle mExtraActorHandle;
    u8 _ab0 = 0;
};
KSYS_CHECK_SIZE_NX150(WeaponBase, 0xab8);

}  // namespace ksys::act

namespace ksys::act::acc {

// Accessor for WeaponBase actors (lane4 s44; the 0x7100ef9bb8-0x7100efb798 functions in the WeaponBase TU, unnamed in
// the CSV; class and method names are guesses). Each one casts the accessor's proc to a WeaponBase (null / not an
// actor / not a weapon: the default value) and forwards to a virtual function of the weapon (named after it).
class WeaponBase : public ActorConstDataAccess {
public:
    bool m153() const;
    bool isWeaponType0Or1Or2() const;
    bool isWeaponType3() const;
    void m167(sead::Vector3f* out) const;
    void m168(sead::Vector3f* out) const;
    void m169(sead::Vector3f* out) const;
    void m170(sead::Vector3f* out) const;
    void m171(sead::Vector3f* out) const;
    void m172(sead::Vector3f* out) const;
    bool m222() const;
    // 0x7100efa6b8: the weapon has a name (m159) and either no optional weapon (m161) or one that does not have the
    // flag 2 of its `mSpecialJobTypesMaskOverride`; false without a weapon.
    bool sub_7100EFA6B8() const;
    // 0x7100efa910: acquires the parent actor (`_938`) into `out`.
    bool acquireParentActor(ActorConstDataAccess* out) const;
    bool hasParentActor_() const;
    Actor* getParentActor() const;
    bool m188() const;
    bool m186() const;
    bool m154() const;
    bool m155() const;
    bool m156() const;
    bool m223(s32* out) const;
    // 0x7100efb240: `_a00` of the weapon.
    ModelBindInfo* getBindInfo() const;
    // 0x7100efb338: the actor member at +0x4d0 is set.
    bool sub_7100EFB338() const;
    void m228(BaseProc* proc) const;
    // 0x7100efb53c: forwards to Actor::sub_71011C5630.
    void sub_7100EFB53C(gsys::Model* model) const;
    // 0x7100efb798: `_ab0` is set.
    bool sub_7100EFB798() const;

protected:
    ksys::act::WeaponBase* getWeapon() const;
};

}  // namespace ksys::act::acc
