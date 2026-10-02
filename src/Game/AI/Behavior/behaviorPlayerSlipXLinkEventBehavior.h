#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class PlayerSlipXLinkEventBehavior : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PlayerSlipXLinkEventBehavior, ksys::act::ai::Behavior)
public:
    explicit PlayerSlipXLinkEventBehavior(const InitArg& arg);
    ~PlayerSlipXLinkEventBehavior() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ void* _28 = nullptr;
    /* 0x30 */ u32 _30 = 0;
    /* 0x38 */ void* _38 = nullptr;
    /* 0x40 */ u32 _40 = 0;
    /* 0x48 */ void* _48 = nullptr;
    /* 0x50 */ bool _50 = false;
    /* 0x51 */ bool _51 = false;
};
KSYS_CHECK_SIZE_NX150(PlayerSlipXLinkEventBehavior, 0x58);

}  // namespace uking::behavior
