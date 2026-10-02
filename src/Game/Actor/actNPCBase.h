#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Types.h"

namespace uking::act {

// Name from the CSV (NPCBase::*): base class of NPC. vtable 0x71024ee5c0 (148 slots, no new
// virtuals), RTTI static 0x71025aebd0 (parent: Actor). ctor 0x7100e937cc.
// TODO: incomplete. Size 0xc78 (NPC's first member is at 0xc78).
class NPCBase : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(NPCBase, ksys::act::Actor)
public:
    explicit NPCBase(const CreateArg& arg);
    ~NPCBase() override;

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    void m63() override;
    void initMaybe() override;
    void m66() override;
    void calcMaybe() override;
    void updatePositionMaybe() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;

    /* 0x840 */ void* _840 = nullptr;
    /* 0x848 */ u8 _848[0x8a8 - 0x848];  // object with ctor 0x7100eebaac (CSV Rail::ctor)
    /* 0x8a8 */ sead::SafeString _8a8;
    /* 0x8b8 */ u16 _8b8 = 0;
    /* 0x8c0 */ sead::FixedSafeString<64> _8c0;
    /* 0x918 */ sead::FixedSafeString<128> _918;
    /* 0x9b0 */ sead::FixedSafeString<16> _9b0;
    /* 0x9d8 */ sead::FixedSafeString<128> _9d8;
    /* 0xa70 */ sead::FixedSafeString<64> _a70;
    /* 0xac8 */ sead::FixedSafeString<32> _ac8;
    /* 0xb00 */ sead::FixedSafeString<256> _b00;
    /* 0xc18 */ sead::FixedSafeString<64> _c18;
    /* 0xc70 */ void* _c70 = nullptr;
};
KSYS_CHECK_SIZE_NX150(NPCBase, 0xc78);

}  // namespace uking::act
