#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SandwormTeraPach : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SandwormTeraPach, ksys::act::ai::Behavior)
public:
    explicit SandwormTeraPach(const InitArg& arg);
    ~SandwormTeraPach() override;
    bool m6(sead::Heap* heap) override;
    void m9() override;
    void loadParams() override;
    void m7() override;  // not decompiled yet (0x7100635e04)
    void m8() override;  // not decompiled yet (0x7100635ce0)

    /* 0x28 */ sead::SafeString mNode1_s{};
    /* 0x38 */ gsys::BoneAccessKeyEx _38;
    /* 0x70 */ f32 _70 = 1.0f;
};
KSYS_CHECK_SIZE_NX150(SandwormTeraPach, 0x78);

}  // namespace uking::behavior
