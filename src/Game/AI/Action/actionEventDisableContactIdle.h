#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

namespace uking::action {

class EventDisableContactIdle : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventDisableContactIdle, ksys::act::ai::Action)
public:
    explicit EventDisableContactIdle(const InitArg& arg);
    ~EventDisableContactIdle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // Local contact callback (vtable in this TU, `invoke` 0x7100117f54): disables the contacts with
    // rigid bodies whose contact layer is in `mLayerMask` and drops them from the recorded points.
    class DisableContactCallback : public ksys::phys::ContactPointInfo::ContactCallback {
    public:
        bool invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                    const ksys::phys::ContactPointInfo::Event& event) override;

        s32 mLayerMask = -1857;
    };

    // dynamic_param at offset 0x20
    int* mContactType_d{};
    ksys::phys::ContactPointInfo* mContactPointInfo{};
    ksys::phys::ContactPointInfo* mOriginalContactPointInfo{};
    DisableContactCallback mCallback;
};
KSYS_CHECK_SIZE_NX150(EventDisableContactIdle, 0x48);

}  // namespace uking::action
