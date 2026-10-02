#pragma once

#include "Game/AI/aiMessage3DText.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class NpcTebaRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NpcTebaRoot, ksys::act::ai::Ai)
public:
    explicit NpcTebaRoot(const InitArg& arg);
    ~NpcTebaRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    bool handleMessage_(const ksys::Message& message) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mShowMessageLockonMinInterval_s{};
    // static_param at offset 0x40
    const float* mApproachPlayerHeight_s{};
    // static_param at offset 0x48
    const float* mShowMessageDoDist_s{};
    // set by message 0x800000e
    bool _50 = false;
    bool _51 = false;
    ksys::Timer _54;
    ksys::Timer _60;
    Message3DText _70;
};
KSYS_CHECK_SIZE_NX150(NpcTebaRoot, 0x148);

}  // namespace uking::ai
