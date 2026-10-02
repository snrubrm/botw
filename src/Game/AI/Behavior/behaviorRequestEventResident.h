#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/Event/evtResidentEvent.h"

namespace uking::behavior {

class RequestEventResident : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(RequestEventResident, ksys::act::ai::Behavior)
public:
    explicit RequestEventResident(const InitArg& arg);
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m9() override;
    void loadParams() override;
    void m8() override;  // not decompiled yet (0x71006350e4)
    ~RequestEventResident() override;  // not decompiled yet

    /* 0x28 */ sead::SafeString mEventName_s{};
    /* 0x38 */ sead::SafeString mEntryPointName_s{};
    /* 0x48 */ ksys::evt::ResidentEvent _48;
};
KSYS_CHECK_SIZE_NX150(RequestEventResident, 0x218);

}  // namespace uking::behavior
