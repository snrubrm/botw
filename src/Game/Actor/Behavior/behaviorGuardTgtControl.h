#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class GuardTgtControl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(GuardTgtControl, ksys::act::ai::Behavior)
public:
    explicit GuardTgtControl(const InitArg& arg);
    ~GuardTgtControl() override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mGuardTgtName_s{};
    /* 0x38 */ bool _38 = false;
};
KSYS_CHECK_SIZE_NX150(GuardTgtControl, 0x40);

}  // namespace uking::behavior
