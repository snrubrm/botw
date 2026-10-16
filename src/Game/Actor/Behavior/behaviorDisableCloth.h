#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class DisableCloth : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(DisableCloth, ksys::act::ai::Behavior)
public:
    explicit DisableCloth(const InitArg& arg);
    ~DisableCloth() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(DisableCloth, 0x28);

}  // namespace uking::behavior
