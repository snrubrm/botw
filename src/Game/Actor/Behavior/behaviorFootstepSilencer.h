#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class FootstepSilencer : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(FootstepSilencer, ksys::act::ai::Behavior)
public:
    explicit FootstepSilencer(const InitArg& arg);
    ~FootstepSilencer() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(FootstepSilencer, 0x28);

}  // namespace uking::behavior
