#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class CharacterControllerFormChange : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(CharacterControllerFormChange, ksys::act::ai::Behavior)
public:
    explicit CharacterControllerFormChange(const InitArg& arg);
    ~CharacterControllerFormChange() override;
    void m7() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;  // not decompiled yet (0x710061c430)
    void m8() override;  // not decompiled yet (0x710061c4e8)
    void m9() override;  // not decompiled yet (0x710061c540)

    /* 0x28 */ const int* mEnterState_s{};
    /* 0x30 */ const bool* mIsRestoreWhenLeave_s{};
    /* 0x38 */ s32 _38 = -1;
    /* 0x3c */ s32 _3c = -1;
};
KSYS_CHECK_SIZE_NX150(CharacterControllerFormChange, 0x40);

}  // namespace uking::behavior
