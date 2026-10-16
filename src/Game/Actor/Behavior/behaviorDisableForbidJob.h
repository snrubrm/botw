#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class DisableForbidJob : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(DisableForbidJob, ksys::act::ai::Behavior)
public:
    explicit DisableForbidJob(const InitArg& arg);
    ~DisableForbidJob() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(DisableForbidJob, 0x28);

}  // namespace uking::behavior
