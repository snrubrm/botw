#pragma once

#include "Game/Actor/AI/aiAppearFromTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class AppearFromTargetFrontAfterChase : public AppearFromTarget {
    SEAD_RTTI_OVERRIDE(AppearFromTargetFrontAfterChase, AppearFromTarget)
public:
    explicit AppearFromTargetFrontAfterChase(const InitArg& arg);
    ~AppearFromTargetFrontAfterChase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m37(const sead::Vector3f& pos) override;
    // 0x710030f120 (placeholder name)
    void changeToSpawnAppear();

protected:
    // static_param at offset 0x90
    const float* mAppearDist_s{};
    ksys::Timer _98{0, 0};
};

}  // namespace uking::ai
