#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class StopUpdateAwarenessBasePos : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(StopUpdateAwarenessBasePos, ksys::act::ai::Behavior)
public:
    explicit StopUpdateAwarenessBasePos(const InitArg& arg);
    ~StopUpdateAwarenessBasePos() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(StopUpdateAwarenessBasePos, 0x28);

}  // namespace uking::behavior
