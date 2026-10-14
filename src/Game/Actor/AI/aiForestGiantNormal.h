#pragma once

#include "Game/Actor/AI/aiEnemyNormal.h"
#include "Game/Actor/aiRandomTimer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(ForestGiantNormal, EnemyNormal)
public:
    explicit ForestGiantNormal(const InitArg& arg);
    ~ForestGiantNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void m34() override;
    bool m54() override;

    void m60(Unk3* out) override;
    bool m63(Unk3* result) override;
    bool m68(Unk2* out, Unk1* info) override;
protected:
    // static_param at offset 0x3d0
    const float* mSleepingHearAwnRatio_s{};
    bool _3d8 = false;
    RandomTimer _3dc;
};
KSYS_CHECK_SIZE_NX150(ForestGiantNormal, 0x3e8);

}  // namespace uking::ai
