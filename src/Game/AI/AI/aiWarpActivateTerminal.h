#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WarpActivateTerminal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WarpActivateTerminal, ksys::act::ai::Ai)
public:
    explicit WarpActivateTerminal(const InitArg& arg);
    ~WarpActivateTerminal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    bool sub_71005EABF4();

protected:
    // static_param at offset 0x38
    const float* mDoLimitAngle_s{};
    // static_param at offset 0x40
    const bool* mIsAbleToReboot_s{};
    // static_param at offset 0x48
    const bool* mIsCheckLimit_s{};
    // static_param at offset 0x50
    const bool* mIsRejectMsgForRemains_s{};
    // map_unit_param at offset 0x58
    const int* mRemainsTerminalType_m{};
    // map_unit_param at offset 0x60
    const int* mRemainsTerminalIndex_m{};
    Unk_7102450648 _68{0x1800029};
    bool _a8 = false;
};
KSYS_CHECK_SIZE_NX150(WarpActivateTerminal, 0xb0);

}  // namespace uking::ai
