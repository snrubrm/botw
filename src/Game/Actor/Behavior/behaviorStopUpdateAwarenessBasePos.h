#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class StopUpdateAwarenessBasePos : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(StopUpdateAwarenessBasePos, ksys::act::ai::Behavior)
public:
    explicit StopUpdateAwarenessBasePos(const InitArg& arg);
    ~StopUpdateAwarenessBasePos() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(StopUpdateAwarenessBasePos, 0x28);

}  // namespace uking::behavior
