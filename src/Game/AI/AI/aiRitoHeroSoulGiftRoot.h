#pragma once

#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class RitoHeroSoulGiftRoot : public HeroSoulGiftRoot {
    SEAD_RTTI_OVERRIDE(RitoHeroSoulGiftRoot, HeroSoulGiftRoot)
public:
    explicit RitoHeroSoulGiftRoot(const InitArg& arg);
    ~RitoHeroSoulGiftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

    void m36() override;
    bool m37() override;

    void setPosition();

protected:
    // static_param at offset 0x90
    sead::SafeString mActorName_s{};
    // static_param at offset 0xa0
    const sead::Vector3f* mScale_s{};
    ksys::act::BaseProcLink _a8;
    bool _b8 = false;
};
KSYS_CHECK_SIZE_NX150(RitoHeroSoulGiftRoot, 0xc0);

}  // namespace uking::ai
