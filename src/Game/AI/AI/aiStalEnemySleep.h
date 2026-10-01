#pragma once

#include "Game/AI/AI/aiSpecialEnemySleep.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalEnemySleep : public SpecialEnemySleep {
    SEAD_RTTI_OVERRIDE(StalEnemySleep, SpecialEnemySleep)
public:
    explicit StalEnemySleep(const InitArg& arg);
    ~StalEnemySleep() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void* m37(int* x) override;
    bool m39(sead::Vector3f* pos) override;

protected:
    // static_param at offset 0x60
    const bool* mUseAwarenessWakeUp_s{};
    // static_param at offset 0x68
    const bool* mUseNoticeActiveWakeUp_s{};
    sead::Vector3f _70 = sead::Vector3f::zero;
    bool _7c = false;
};
KSYS_CHECK_SIZE_NX150(StalEnemySleep, 0x80);

}  // namespace uking::ai
