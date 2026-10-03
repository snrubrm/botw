#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoVisibleOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoVisibleOff, ksys::act::ai::Action)
public:
    explicit DemoVisibleOff(const InitArg& arg);
    ~DemoVisibleOff() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    sead::FixedSafeString<32> _20;
};
KSYS_CHECK_SIZE_NX150(DemoVisibleOff, 0x58);

}  // namespace uking::action
