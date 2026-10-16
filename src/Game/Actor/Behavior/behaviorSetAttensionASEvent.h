#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetAttensionASEvent : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetAttensionASEvent, ksys::act::ai::Behavior)
public:
    explicit SetAttensionASEvent(const InitArg& arg);
    ~SetAttensionASEvent() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mAttKey_s{};
    /* 0x38 */ bool _38 = false;
};
KSYS_CHECK_SIZE_NX150(SetAttensionASEvent, 0x40);

}  // namespace uking::behavior
