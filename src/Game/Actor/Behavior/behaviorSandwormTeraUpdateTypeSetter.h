#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SandwormTeraUpdateTypeSetter : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SandwormTeraUpdateTypeSetter, ksys::act::ai::Behavior)
public:
    explicit SandwormTeraUpdateTypeSetter(const InitArg& arg);
    ~SandwormTeraUpdateTypeSetter() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ const int* mUpdateType_s{};
};
KSYS_CHECK_SIZE_NX150(SandwormTeraUpdateTypeSetter, 0x30);

}  // namespace uking::behavior
