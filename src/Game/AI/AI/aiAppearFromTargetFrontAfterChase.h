#pragma once

#include "Game/AI/AI/aiAppearNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class AppearFromTargetFrontAfterChase : public AppearNearTarget {
    SEAD_RTTI_OVERRIDE(AppearFromTargetFrontAfterChase, AppearNearTarget)
public:
    explicit AppearFromTargetFrontAfterChase(const InitArg& arg);
    ~AppearFromTargetFrontAfterChase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void m37(const sead::Vector3f& pos) override;
    // 0x710030f120 (placeholder name)
    void sub_710030F120();

protected:
    // static_param at offset 0x90
    const float* mAppearDist_s{};
    ksys::Timer _98{0, 0};
};

}  // namespace uking::ai
