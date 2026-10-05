#pragma once

#include "Game/AI/AI/aiAssassinMiddleRoot.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMiddleAzitoRootAccept : public AssassinMiddleRoot {
    SEAD_RTTI_OVERRIDE(AssassinMiddleAzitoRootAccept, AssassinMiddleRoot)
public:
    explicit AssassinMiddleAzitoRootAccept(const InitArg& arg);
    ~AssassinMiddleAzitoRootAccept() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    // static_param at offset 0x340
    sead::SafeString mEntryPoint_s{};
    // static_param at offset 0x350
    sead::SafeString mDemoName_s{};
    Unk_7102450678 _360;
};
KSYS_CHECK_SIZE_NX150(AssassinMiddleAzitoRootAccept, 0x398);

}  // namespace uking::ai
