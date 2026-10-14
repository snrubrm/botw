#pragma once

#include <prim/seadSafeString.h>
#include "Game/Actor/actUnk_7102366570.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SyncBodyASAndAnimalUnitAS : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SyncBodyASAndAnimalUnitAS, ksys::act::ai::Behavior)
public:
    explicit SyncBodyASAndAnimalUnitAS(const InitArg& arg);
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    void m8() override;  // not decompiled yet (0x7100645c60)
    void m9() override;  // not decompiled yet (0x7100645d08)
    ~SyncBodyASAndAnimalUnitAS() override;  // not decompiled yet

    // 2026-10-07: vtable0x710243b090 inherits the root callback RTTI and owns its D1/D0.
    class Callback : public Unk_7102366570 {
    public:
        ~Callback() override;
        void call(ksys::act::Actor* actor) override;
        void sub_71006459BC(ksys::act::Actor* actor);
    };
    /* 0x28 */ Callback _28;
    /* 0x48 */ const int* mSeqBank_s{};
    /* 0x50 */ const int* mTargetBone_s{};
    /* 0x58 */ sead::SafeString mPreFix_s{};
    /* 0x68 */ s32 _68 = -1;
};
KSYS_CHECK_SIZE_NX150(SyncBodyASAndAnimalUnitAS, 0x70);

}  // namespace uking::behavior
