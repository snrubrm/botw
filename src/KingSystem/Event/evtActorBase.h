#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>
#include <evfl/ResActor.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::evt {

class ActionBase;
class Query;

// The event-side actor (CSV evt::ActorBase; the 0x1d0-byte evt::Actor derives from it, ctor 0x7100da7ed8 takes an
// ActorBinding, the factory is ukingEventMgr::makeActor). Only the members used so far are modelled; the slots that
// are not decompiled yet are pure here.
class ActorBase {
public:
    SEAD_RTTI_BASE(ActorBase)

    virtual ~ActorBase();
    virtual void m4() = 0;
    virtual void m5() = 0;
    // 0x7100daaa10 (CSV evt::ActorBase::m6): state 0x15 -> 0x16, returns true
    virtual bool m6();
    virtual void m7() = 0;
    virtual void m8() = 0;
    // 0x7100dab5f8 (CSV evt::ActorBase::play)
    virtual void play();
    virtual void m10() = 0;
    virtual void m11() = 0;
    virtual void m12() = 0;

    // 0x7100da9c2c (CSV evt::ActorBase::getActionByName): the action whose resource is `res`
    ActionBase* getActionByName(const evfl::ResAction* res) const;

    /* 0x008 */ act::BaseProcLink mLink;
    /* 0x018 */ act::BaseProcHandle mHandle;
    /* 0x028 */ sead::FixedSafeString<64> mName;
    /* 0x080 */ sead::FixedSafeString<64> mSubName;
    /* 0x0d8 */ s32 mState;
    /* 0x0dc */ u8 _dc[0xe8 - 0xdc];
    /* 0x0e8 */ sead::PtrArray<ActionBase> mActions;
    /* 0x0f8 */ sead::PtrArray<Query> mQueries;
    /* 0x108 */ u8 _108[0x1b4 - 0x108];
    /* 0x1b4 */ bool _1b4;
    /* 0x1b5 */ u8 _1b5[0x1b8 - 0x1b5];
    /* 0x1b8 */ void* _1b8;
    /* 0x1c0 */ void* _1c0;
    /* 0x1c8 */ u32 mFlags;
};

}  // namespace ksys::evt
