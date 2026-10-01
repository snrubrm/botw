#pragma once

#include "Game/AI/AI/aiAppearNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AppearNearTargetOutOfScrnGnd : public AppearNearTarget {
    SEAD_RTTI_OVERRIDE(AppearNearTargetOutOfScrnGnd, AppearNearTarget)
public:
    explicit AppearNearTargetOutOfScrnGnd(const InitArg& arg);
    ~AppearNearTargetOutOfScrnGnd() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m34(sead::Vector3f* out) override;
    void m35(sead::Vector3f* out) override;
    bool m36(const sead::Vector3f& pos) override;

protected:
};

}  // namespace uking::ai
