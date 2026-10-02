#pragma once

#include "Game/AI/AI/aiSpecialEnemySleep.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MiniGolemSleep : public SpecialEnemySleep {
    SEAD_RTTI_OVERRIDE(MiniGolemSleep, SpecialEnemySleep)
public:
    explicit MiniGolemSleep(const InitArg& arg);
    ~MiniGolemSleep() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    bool m36() override;

protected:
    // aitree_variable at offset 0x60
    void* mGolemChemicalController_a{};
    Unk_7102450528 _68;
    sead::JobQueueLock _d8;
};
KSYS_CHECK_SIZE_NX150(MiniGolemSleep, 0xe0);

}  // namespace uking::ai
