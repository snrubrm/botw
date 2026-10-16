#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class DisableBoneController : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(DisableBoneController, ksys::act::ai::Behavior)
public:
    explicit DisableBoneController(const InitArg& arg);
    ~DisableBoneController() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(DisableBoneController, 0x28);

}  // namespace uking::behavior
