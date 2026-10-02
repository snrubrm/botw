#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

// TODO: `_28` is an object with vtable 0x710243b090 (RTTI, destructor, one more virtual); type not declared yet.
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

    /* 0x28 */ u8 _28[0x20];
    /* 0x48 */ const int* mSeqBank_s{};
    /* 0x50 */ const int* mTargetBone_s{};
    /* 0x58 */ sead::SafeString mPreFix_s{};
    /* 0x68 */ s32 _68 = -1;
};
KSYS_CHECK_SIZE_NX150(SyncBodyASAndAnimalUnitAS, 0x70);

}  // namespace uking::behavior
