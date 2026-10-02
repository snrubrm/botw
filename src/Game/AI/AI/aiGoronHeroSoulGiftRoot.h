#pragma once

#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GoronHeroSoulGiftRoot : public HeroSoulGiftRoot {
    SEAD_RTTI_OVERRIDE(GoronHeroSoulGiftRoot, HeroSoulGiftRoot)
public:
    explicit GoronHeroSoulGiftRoot(const InitArg& arg);
    ~GoronHeroSoulGiftRoot() override;
    void calc_() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool m35(sead::Matrix34f* mtx) override;

protected:
    ksys::Timer _8c;
};

}  // namespace uking::ai
