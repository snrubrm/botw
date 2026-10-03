#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemoteBomb : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemoteBomb, ksys::act::ai::Ai)
public:
    explicit RemoteBomb(const InitArg& arg);
    ~RemoteBomb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mWindRatio_s{};
    // static_param at offset 0x40
    sead::SafeString mXLinkKey_s{};
    // aitree_variable at offset 0x50
    bool* mIsIgniteCarriedBomb_a{};
    Unk_71024507c8 _58{0x1800004};
    Unk_71024506d8 _98;
    Unk_7102450798 _d0;
    Unk_7102450b58 _108;
    Unk_71023da100 _148;
    void* _198{};
    bool _1a0 = false;
};
KSYS_CHECK_SIZE_NX150(RemoteBomb, 0x1a8);

}  // namespace uking::ai
