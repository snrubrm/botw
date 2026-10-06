#pragma once

#include "Game/AI/AI/aiEnemyWatchKeepingWait.h"
#include "Game/AI/aiUnk_710038ffb8.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFortressWatchKeepingWait : public EnemyWatchKeepingWait {
    SEAD_RTTI_OVERRIDE(EnemyFortressWatchKeepingWait, EnemyWatchKeepingWait)
public:
    explicit EnemyFortressWatchKeepingWait(const InitArg& arg);
    ~EnemyFortressWatchKeepingWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool isChangeable() const override;

protected:
    /* 0x80 */ Unk_710038ffb8 _80;
    /* 0x448 */ u8 _448;  // bit 0: changeable, bit 3: cleared when the child ends
    u8 _449[0x450 - 0x449];
};

}  // namespace uking::ai
