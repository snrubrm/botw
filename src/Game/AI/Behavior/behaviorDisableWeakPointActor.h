#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class DisableWeakPointActor : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(DisableWeakPointActor, ksys::act::ai::Behavior)
public:
    explicit DisableWeakPointActor(const InitArg& arg);
    ~DisableWeakPointActor() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    void m8() override;  // not decompiled yet (0x710061ffd8)
    void m9() override;  // not decompiled yet (0x7100620094)

    /* 0x28 */ sead::SafeString mWeakPointKey_s{};
    /* 0x38 */ Unk_7102357d48 _38{mActor, 0x800002f};
    /* 0x50 */ Unk_7102357d70 _50{mActor, 0x8000030};
};
KSYS_CHECK_SIZE_NX150(DisableWeakPointActor, 0x68);

}  // namespace uking::behavior
