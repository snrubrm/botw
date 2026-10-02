#pragma once

#include "Game/AI/AI/aiAssassinNormal.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMiddleAzitoRoot : public AssassinNormal {
    SEAD_RTTI_OVERRIDE(AssassinMiddleAzitoRoot, AssassinNormal)
public:
    explicit AssassinMiddleAzitoRoot(const InitArg& arg);
    ~AssassinMiddleAzitoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x420
    sead::SafeString mEntryPoint_s{};
    // static_param at offset 0x430
    sead::SafeString mDemoName_s{};
    // static_param at offset 0x440
    sead::SafeString mLikeItem_s{};
    ksys::act::BaseProcLink _450;
    Unk_710235aba0 _460{mActor, 0x8000040};
    Unk_7102450678 _490;
    sead::SafeArray<ksys::act::BaseProcLink, 10> _4c8;
    bool _568 = false;
};

}  // namespace uking::ai
