#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <heap/seadExpHeap.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <mc/seadJobQueue.h>
#include <prim/seadRuntimeTypeInfo.h>

#include "Game/Damage/dmgInfoManager.h"
#include "Game/Damage/dmgStruct20.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actIDamageManager.h"

namespace ksys::res {
class DamageParam;
}  // namespace ksys::res

namespace ksys::phys {
class MaterialMask;
class RigidBody;
}  // namespace ksys::phys

namespace ksys::act {
class Actor;
class ActorParam;
}  // namespace ksys::act

namespace ksys {
class Message;
}

namespace uking::act {

class DamageCallback;
class DamageCallbackInfo;

// Placeholder name: a condition damage (burn / ice / electric ...) passed to slot 45, built on the stack by the
// condition handlers of uking::act::Unk_71025ae680 and its subclasses (sent through Unk_71025ae680::sub_71006DF5CC).
struct ConditionDamageInfo {
    s32 mKind;    // DamageManager::m45 switches on it (0-11)
    s32 mDamage;
    u32 _8 = 0;       // bit 6: DamageManager::_8c |= 4
    u32 mFlags = 0;   // bits 0-5, 8 tested by DamageManager::m45 / m54 / m55
    s32 _10 = -1;     // copied to DamageManager::_88 with bit 3 of mFlags
};

// FIXME: Unknown base 2. Helper functions maybe? Might also contain some of the fields from
// DamageManagerBase.
class DamageManagerBase_UnknownBase2 {
public:
    virtual ~DamageManagerBase_UnknownBase2() = default;
};

class DamageManagerBase : public ksys::act::IDamageManager, public DamageManagerBase_UnknownBase2 {
public:
    explicit DamageManagerBase(ksys::act::Actor* actor);
    ~DamageManagerBase() override = default;

    SEAD_RTTI_OVERRIDE(DamageManagerBase, ksys::act::IDamageManager)
public:
    virtual u32 getDamage();
    virtual s32 getField48() { return mField_48; }
    virtual s32 getMinDmg() { return mMinDmg; }
    virtual s32 getField50() { return mField_50; }
    virtual s32 getField54() { return mField_54; }
    virtual bool checkDamageFlags(s32 bit) { return false; }
    // lane4 s48: returns u64 (callers mask it with 64-bit instructions: ForceDispLifeGage; PlayerBase::getDeathReason
    // truncates it to 32 bits and widens it again: `and x0, x0, #0xffffffff`).
    virtual u64 getFlags2() { return mFlags2; }
    // lane1 s22: AssassinBossRoot sets the low nibble of mField_64 (name is a guess).
    void setField64LowNibble(u8 value) { mField_64 = (mField_64 & 0xf0) | value; }
    virtual f32 m13() { return 0.0f; }
    // Slot 14: writes the stasis blow direction (DamageMgr::m14) to `out`.
    virtual bool m14(sead::Vector3f* out) { return false; }
    virtual bool applyDamage(s32& life);
    // Slot 16: message handler (DamageManager::m16 forwards to its listeners).
    virtual bool m16(const ksys::Message& message) { return false; }
    virtual void m17() {}
    virtual s32 getNumCallbacks();
    virtual bool initCallbacks(sead::Heap* heap);

    // m20 (FIXME: incomplete)
    virtual void resetDamage();

    virtual void preDelete2() {}
    virtual void m22() {}
    virtual bool allocStruct20(sead::Heap* heap);
    virtual void preDelete1();
    virtual s64 m25() { return 0; }
    virtual s64 m26() { return 0; }
    // Slot 27: writes the damage position to `out` (SwarmDamaged::m34; DamageMgr::getPosition 0x71006d66fc).
    virtual bool getPosition(sead::Vector3f* out) { return false; }
    // Slot 28 (CSV DamageMgrSword::getAttackPos: AttackInfo position; DamageMgr::m28).
    virtual bool getAttackPos(sead::Vector3f* out) { return false; }

    // Slot 29 (0x71006e0158 DamageMgrBase::m29, DamageMgr::m29): writes a direction to `out` (callers test
    // the result; sub_71005E242C).
    virtual bool m29(sead::Vector3f* out);

    // 0x71006e029c (DamageMgrBase::m30): writes a direction to `out` (callers test the result).
    virtual bool m30(sead::Vector3f* out);

    // lane4 s51: takes an out direction (DamageManager::m31; the base returns false).
    virtual bool m31(sead::Vector3f* out) { return false; }
    // Signature from IceSplinterRoot::m43 (lane2): takes an out vector (a direction), result is tested.
    virtual bool m32(sead::Vector3f* out) { return false; }
    virtual ksys::phys::MaterialMask* m33() { return nullptr; }
    virtual ksys::phys::MaterialMask* tgSensorMaterialOnHitMaybe() { return nullptr; }
    // Slot 35: overrides write a matrix (DamageMgr::m35: the attacker's actor matrix).
    virtual bool m35(sead::Matrix34f* out) { return false; }

    // 2026-10-07: both base slots return the canonical dummy BaseProcLink.
    virtual ksys::act::BaseProcLink* getAttacker();

    virtual ksys::act::BaseProcLink* m37();

    // lane2 s42: takes a rigid body (the Sandworm damage callback calls it with the actor's "Body" body).
    virtual bool m38(ksys::phys::RigidBody* body) { return false; }

    // FIXME: Incomplete. Call isSlowTimeMaybe
    virtual bool isSlowTime();

    // Signature from the AssassinBossRoot damage callbacks (lane2): takes an out value; DamageMgr::m40 writes -1 first
    // and returns whether it found a value.
    virtual bool m40(s32* out) { return false; }
    virtual bool m41() { return false; }
    virtual bool m42() { return false; }
    virtual void m43() {}
    virtual bool canTakeDamage();
    virtual void m45(const ConditionDamageInfo& info) {}
    virtual void handleDamageForPlayer(u32* a2, u32* a3, u32* a4, u32* a5, u32* a6);
    virtual bool addDamage(s32 type, s32 damage, s32 df48, s32 minDmg, s32 f50, s32 f54, s32 f40);
    virtual void onApplyDamage() {}

    // Something depending on damage type?
    virtual s32 m49(s32 damageTypeMaybe);

    // 0x71006e1288 (CSV DamageMgr::getActorDamageParam; in the DamageManagerBase TU): the actor's
    // DamageParam resource (null without an ActorParam).
    ksys::res::DamageParam* getActorDamageParam();

    // 0x71006e0bc... family (lane4 s47; placeholder names): predicates over the DamageInfoMgr entry of the manager's
    // reaction table index (`mCanTakeDamageFromType[type]`), the `type` being the argument or m49(getField50()).
    // Bit 5 / bit 0 of the entry.
    bool sub_71006E0BD4(s32 type) const;
    bool sub_71006E0CC0(s32 type) const;
    // Bit 1 / bit 3 and not m42().
    bool sub_71006E0D24();
    bool sub_71006E0DE8(s32 type) const;
    bool sub_71006E0E78();
    bool sub_71006E0F24(s32 type) const;
    // mField_64 bits 0 / 1 force true / false, else bit 2 of the entry (0x71006e0fb4 / 0x71006e1050).
    bool sub_71006E0FB4();
    bool sub_71006E1050(s32 type) const;
    // mField_64 bits 2 / 3 force true / false, else bit 4 of the entry (0x71006e10d0 / 0x71006e11f4).
    bool sub_71006E10D0();
    bool sub_71006E11F4(s32 type) const;

    void clearCallbacks();
    void resetStuff();
    void callDamageCallbacks(s32 event_id, s32* a1, s32* a2, u32* a3, u32* a4, s32* a5,
                             DamageCallbackInfo* a6);
    void calcMaybe();

    // Read inline by the damage callback 0x710074a584 (compares it with 9).
    s32 getDamageType() const { return mDamageType; }

    inline void tryBuffDamage(s32& damage);
    inline void tryApplyDamageRecovery(s32& damage);

protected:
    s32 mField_40 = 0;
    s32 mDamage = 0;
    s32 mField_48 = 0;
    // u32: DamageMgrSword::m22 passes the addresses of mMinDmg / mField_50 as the `u32*` arguments of
    // callDamageCallbacks.
    u32 mMinDmg = 0;
    u32 mField_50 = -1;
    s32 mField_54 = -1;
    u32 mFlags2 = 0;
    s32 mDamageType = 0;
    s32 mDamageReactionTableStuff = -1;
    u8 mField_64 = 0;
    bool mIsOwnedByPlayer;
};
KSYS_CHECK_SIZE_NX150(DamageManagerBase, 0x68);

}  // namespace uking::act
