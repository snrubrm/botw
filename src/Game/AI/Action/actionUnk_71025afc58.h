#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/ActorSystem/actAiActionBase.h"

namespace ksys::act {
class BaseProcHandle;
}

// Unnamed polymorphic helper object owned by an action (attack / ignite helpers embedded in Attack,
// AttackPartBind, FollowAttack, AssassinBossIronBallAtkWithRot, ForkIgniteCarriedActor,
// OctarockReloadWig, FollowIgniteToSelfPos, Throw, ...). Root of a family of sead RTTI classes
// (RTTI object 0x71025afc58; this class has no vtable or ctor of its own in the binary). The
// interface mirrors ActionBase: the flag getters (slots 4-6) test the same bits as
// ActionBase::isFailed/isFinished/isChangeable, and the owners call slots 7-11 from their own
// init_/enter_/calc_/leave_/loadParams_. Like ActionBase, the virtual slots are reached through
// non-virtual inline wrappers: owners always clear the flags right before calling slot 8, and calls
// on embedded helper objects are not devirtualized in the original. The derived classes are in the
// TU 0x71002a58e0 - 0x71002a8b00.
class Unk_71025afc58 {
    SEAD_RTTI_BASE(Unk_71025afc58)
public:
    enum class Flag : u8 {
        Finished = 1,
        Failed = 2,
        Changeable = 4,
    };

    explicit Unk_71025afc58(ksys::act::ai::ActionBase* owner) : mOwner(owner) {}
    virtual ~Unk_71025afc58() = default;

    bool init(sead::Heap* heap) { return init_(heap); }
    void enter(ksys::act::ai::InlineParamPack* params) {
        mFlags.makeAllZero();
        enter_(params);
    }
    void calc() { calc_(); }
    void leave() { leave_(); }
    void loadParams() { loadParams_(); }

    virtual bool isFailed() const { return mFlags.isOn(Flag::Failed); }
    virtual bool isFinished() const { return mFlags.isOn(Flag::Finished); }
    virtual bool isChangeable() const { return mFlags.isOn(Flag::Changeable); }

protected:
    virtual bool init_(sead::Heap* heap) { return true; }
    virtual void enter_(ksys::act::ai::InlineParamPack* params) = 0;
    virtual void calc_() = 0;
    virtual void leave_() = 0;
    virtual void loadParams_() = 0;

public:
    virtual bool m12() { return true; }

    // 0x71002a58e0 - 0x71002a5900: forward to the owner's getStaticParam.
    bool getStaticParam(sead::SafeString* value, const sead::SafeString& key) const;
    bool getStaticParam(const int** value, const sead::SafeString& key) const;
    bool getStaticParam(const float** value, const sead::SafeString& key) const;
    bool getStaticParam(const sead::Vector3f** value, const sead::SafeString& key) const;
    bool getStaticParam(const bool** value, const sead::SafeString& key) const;
    // 0x71002a5908 - 0x71002a59b8: forward to the owner's getDynamicParam.
    bool getDynamicParam(int** value, const sead::SafeString& key) const;
    bool getDynamicParam(sead::Vector3f** value, const sead::SafeString& key) const;
    bool getDynamicParam(ksys::act::BaseProcHandle*** value, const sead::SafeString& key) const;

    ksys::act::ai::ActionBase* mOwner;
    sead::TypedBitFlag<Flag> mFlags;
};
KSYS_CHECK_SIZE_NX150(Unk_71025afc58, 0x18);
