#pragma once

#include "Game/AI/Action/actionBasicSignalEnemy.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BasicSignalBossAwakeSleep : public BasicSignalEnemy {
    SEAD_RTTI_OVERRIDE(BasicSignalBossAwakeSleep, BasicSignalEnemy)
public:
    explicit BasicSignalBossAwakeSleep(const InitArg& arg);
    ~BasicSignalBossAwakeSleep() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32() override;
    void m33() override;
    // 0x71000b9770 (declared only): called by enter_ when `_1c` is set.
    void sub_71000B9770();

    Unk_710236acc8 _20{mActor, 0x800007d};
    Unk_710236acf0 _38{mActor, 0x800007e};
    s32 _50 = 0;
    bool _54 = false;
};
KSYS_CHECK_SIZE_NX150(BasicSignalBossAwakeSleep, 0x58);

}  // namespace uking::action
