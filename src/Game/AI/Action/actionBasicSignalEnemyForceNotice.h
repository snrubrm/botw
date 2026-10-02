#pragma once
#include "Game/AI/aiUnk_7102357d20.h"

#include "Game/AI/Action/actionBasicSignalEnemy.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BasicSignalEnemyForceNotice : public BasicSignalEnemy {
    SEAD_RTTI_OVERRIDE(BasicSignalEnemyForceNotice, BasicSignalEnemy)
public:
    explicit BasicSignalEnemyForceNotice(const InitArg& arg);
    ~BasicSignalEnemyForceNotice() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    void m32() override;
    void m34() override;

    void sub_71000BA308();

    // static_param at offset 0x20
    const int* mInterval_s{};
    Unk_710235abc8 _28{mActor, 0x8000006};
    f32 _80 = 0;
};

}  // namespace uking::action
