#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TerminalEnduranceWarpRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TerminalEnduranceWarpRoot, ksys::act::ai::Ai)
public:
    explicit TerminalEnduranceWarpRoot(const InitArg& arg);
    ~TerminalEnduranceWarpRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    Unk_7102450648 _38{0x1800029};
};

}  // namespace uking::ai
