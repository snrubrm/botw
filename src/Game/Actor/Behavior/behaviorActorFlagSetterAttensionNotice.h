#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ActorFlagSetterAttensionNotice : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ActorFlagSetterAttensionNotice, ksys::act::ai::Behavior)
public:
    explicit ActorFlagSetterAttensionNotice(const InitArg& arg);
    ~ActorFlagSetterAttensionNotice() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mMode_s{};
    /* 0x30 */ const bool* mSetValue_s{};
};
KSYS_CHECK_SIZE_NX150(ActorFlagSetterAttensionNotice, 0x38);

}  // namespace uking::behavior
