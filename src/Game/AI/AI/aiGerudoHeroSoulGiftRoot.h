#pragma once

#include "Game/AI/AI/aiHeroSoulGiftRoot.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GerudoHeroSoulGiftRoot : public HeroSoulGiftRoot {
    SEAD_RTTI_OVERRIDE(GerudoHeroSoulGiftRoot, HeroSoulGiftRoot)
public:
    explicit GerudoHeroSoulGiftRoot(const InitArg& arg);
    ~GerudoHeroSoulGiftRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    bool m37() override { return _9c; }

protected:
    // static_param at offset 0x90
    const float* mMaxLength_s{};
    u32 _98 = 10;
    bool _9c = false;
    bool _9d = false;
    Unk_71023f31f8 _a0{mActor, 0x800009b};
    Unk_7102399748 _b8{mActor, 0x800001d};
};

}  // namespace uking::ai
