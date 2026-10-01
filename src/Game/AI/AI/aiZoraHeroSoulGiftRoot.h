#pragma once

#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ZoraHeroSoulGiftRoot : public HeroSoulGiftRoot {
    SEAD_RTTI_OVERRIDE(ZoraHeroSoulGiftRoot, HeroSoulGiftRoot)
public:
    explicit ZoraHeroSoulGiftRoot(const InitArg& arg);
    ~ZoraHeroSoulGiftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    bool _89 = true;
    int _8c{};
};

}  // namespace uking::ai
