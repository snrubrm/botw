#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaterFallWithSound : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WaterFallWithSound, ksys::act::ai::Ai)
public:
    explicit WaterFallWithSound(const InitArg& arg);
    ~WaterFallWithSound() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void* _38 = nullptr;
    void* _40 = nullptr;
    u32 _48 = 0;
};
KSYS_CHECK_SIZE_NX150(WaterFallWithSound, 0x50);

}  // namespace uking::ai
