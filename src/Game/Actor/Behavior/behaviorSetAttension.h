#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetAttension : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetAttension, ksys::act::ai::Behavior)
public:
    explicit SetAttension(const InitArg& arg);
    ~SetAttension() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mSetState_s{};
    /* 0x30 */ sead::SafeString mAttKey_s{};
};
KSYS_CHECK_SIZE_NX150(SetAttension, 0x40);

}  // namespace uking::behavior
