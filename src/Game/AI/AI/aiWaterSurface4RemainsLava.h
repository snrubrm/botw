#pragma once

#include "Game/AI/AI/aiWaterSurface.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaterSurface4RemainsLava : public WaterSurface {
    SEAD_RTTI_OVERRIDE(WaterSurface4RemainsLava, WaterSurface)
public:
    explicit WaterSurface4RemainsLava(const InitArg& arg);
    ~WaterSurface4RemainsLava() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m34() override;
    void m35() override;

protected:
    int _a4 = 0;
    bool _a8 = false;
};
KSYS_CHECK_SIZE_NX150(WaterSurface4RemainsLava, 0xb0);

}  // namespace uking::ai
