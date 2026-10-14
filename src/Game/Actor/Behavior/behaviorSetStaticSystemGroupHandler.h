#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetStaticSystemGroupHandler : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetStaticSystemGroupHandler, ksys::act::ai::Behavior)
public:
    explicit SetStaticSystemGroupHandler(const InitArg& arg);
    ~SetStaticSystemGroupHandler() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mType_s{};
    /* 0x30 */ const bool* mOnLeaveReset_s{};
};
KSYS_CHECK_SIZE_NX150(SetStaticSystemGroupHandler, 0x38);

}  // namespace uking::behavior
