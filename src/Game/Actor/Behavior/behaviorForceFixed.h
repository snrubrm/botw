#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ForceFixed : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ForceFixed, ksys::act::ai::Behavior)
public:
    explicit ForceFixed(const InitArg& arg);
    ~ForceFixed() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    // Saved state (m8) restored by m9: the character controller's flag bits 0x400 / 0x800 / 4 (_28 - _2a), or
    // the main body's Fixed flag (_2b).
    /* 0x28 */ bool _28 = false;
    /* 0x29 */ bool _29 = false;
    /* 0x2a */ bool _2a = false;
    /* 0x2b */ bool _2b = false;
};
KSYS_CHECK_SIZE_NX150(ForceFixed, 0x30);

}  // namespace uking::behavior
