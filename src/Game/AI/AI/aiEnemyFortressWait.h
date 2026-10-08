#pragma once

#include "Game/AI/AI/aiEnemyWaitViewItem.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "Game/AI/aiUnk_710038ffb8.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {


class EnemyFortressWait : public EnemyWaitViewItem {
    SEAD_RTTI_OVERRIDE(EnemyFortressWait, EnemyWaitViewItem)
public:
    explicit EnemyFortressWait(const InitArg& arg);
    ~EnemyFortressWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool isChangeable() const override;
    void m34() override;
    void m35() override;
    void m36() override;

protected:
    // inline-only in the original; name is a guess: starts the "食事" child with the creation handle (inlined twice
    // into enter_ and twice into calc_).
    void changeToEat();

    // map_unit_param at offset 0x40
    const int* mFortressEatPer_m{};
    // map_unit_param at offset 0x48
    sead::SafeString mFortressEatItem_m{};
    // static_param at offset 0x58
    const int* mEatPer_s{};
    // static_param at offset 0x60
    sead::SafeString mEatItem_s{};
    /* 0x70 */ Unk_710038ffb8 _70;
    /* 0x440 */ ksys::act::BaseProcHandle _440;
    /* 0x450 */ bool _450 = false;
    bool _451 = false;
};

}  // namespace uking::ai
