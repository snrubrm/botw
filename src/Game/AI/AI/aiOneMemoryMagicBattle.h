#pragma once

#include "Game/AI/AI/aiOneMemoryMagicBattleBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OneMemoryMagicBattle : public OneMemoryMagicBattleBase {
    SEAD_RTTI_OVERRIDE(OneMemoryMagicBattle, OneMemoryMagicBattleBase)
public:
    explicit OneMemoryMagicBattle(const InitArg& arg);
    ~OneMemoryMagicBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool m45() override;

protected:
    // static_param at offset 0xe0
    sead::SafeString mMemoryPartsName_s{};
};

}  // namespace uking::ai
