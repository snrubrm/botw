#pragma once

#include "Game/AI/AI/aiRemainsRoot.h"
#include "Game/AI/aiUnk_7102419cb0.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWaterRoot : public RemainsRoot {
    SEAD_RTTI_OVERRIDE(RemainsWaterRoot, RemainsRoot)
public:
    explicit RemainsWaterRoot(const InitArg& arg);
    ~RemainsWaterRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35(bool x) override;
    void m36() override;

protected:
    void sub_710054BAC8(bool x);
    // 0: 水中待機, 1: 水上待機, 2: 遺物戦中, 3: 通常行動 (from the game data flags).
    s32 sub_710054BD54(bool x);

    // aitree_variable at offset 0x50
    void* mRemainsWaterBattleInfo_a{};
    Unk_7102419cb0 _58;
};
KSYS_CHECK_SIZE_NX150(RemainsWaterRoot, 0x98);

}  // namespace uking::ai
