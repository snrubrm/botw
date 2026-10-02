#pragma once

#include "Game/AI/AI/aiSiteBossReflectArrowRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossArrowRainAttack : public SiteBossReflectArrowRoot {
    SEAD_RTTI_OVERRIDE(SiteBossArrowRainAttack, SiteBossReflectArrowRoot)
public:
    explicit SiteBossArrowRainAttack(const InitArg& arg);
    ~SiteBossArrowRainAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void m37() override;
    s32 m43() override;
    void m45(sead::Vector3f* out) override;
    bool m48() override;

protected:
};

}  // namespace uking::ai
