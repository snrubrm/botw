#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetAttensionASEvent : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetAttensionASEvent, ksys::act::ai::Behavior)
public:
    explicit SetAttensionASEvent(const InitArg& arg);
    ~SetAttensionASEvent() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mAttKey_s{};
    /* 0x38 */ bool _38 = false;
};
KSYS_CHECK_SIZE_NX150(SetAttensionASEvent, 0x40);

}  // namespace uking::behavior
