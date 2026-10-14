#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetXLinkProperty : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetXLinkProperty, ksys::act::ai::Behavior)
public:
    explicit SetXLinkProperty(const InitArg& arg);
    ~SetXLinkProperty() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mPropertyIndex_s{};
    /* 0x30 */ const float* mValue_s{};
    /* 0x38 */ const float* mResetValue_s{};
};
KSYS_CHECK_SIZE_NX150(SetXLinkProperty, 0x40);

}  // namespace uking::behavior
