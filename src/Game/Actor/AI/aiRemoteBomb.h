#pragma once

#include "Game/gameRuneMgrStructX.h"

#include "Game/Actor/aiUnk_7102357210.h"
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
    void calc_() override;
    bool handleMessage_(const ksys::Message* message) override;
    void loadParams_() override;

protected:
    // 0x710054fef4 (unnamed in the CSV): marks the bomb as exploding in the rune slots, disables its attention clients
    // and starts "爆発予約"; 0x7100550260: the same without ActorFlag 0x1c, starting "爆発".
    void sub_710054FEF4();
    void sub_7100550260();

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
    Unk_710067e0a8* _198{};  // RuneMgr::StructX (remote bomb slots)
    bool _1a0 = false;
};
KSYS_CHECK_SIZE_NX150(RemoteBomb, 0x1a8);

}  // namespace uking::ai
