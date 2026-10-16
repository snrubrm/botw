#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetXLinkProperty : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetXLinkProperty, ksys::act::ai::Behavior)
public:
    explicit SetXLinkProperty(const InitArg& arg);
    ~SetXLinkProperty() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const int* mPropertyIndex_s{};
    /* 0x30 */ const float* mValue_s{};
    /* 0x38 */ const float* mResetValue_s{};
};
KSYS_CHECK_SIZE_NX150(SetXLinkProperty, 0x40);

}  // namespace uking::behavior
