#pragma once

#include "Game/Actor/Action/actionUnk_7102451ba0.h"
#include "Game/Actor/Action/actionTackleMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TackleAttack : public TackleMove {
    SEAD_RTTI_OVERRIDE(TackleAttack, TackleMove)
public:
    explicit TackleAttack(const InitArg& arg);
    ~TackleAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m36();
    virtual void m37();
    virtual bool m38();

    // static_param at offset 0x88
    sead::SafeString mAtkSensorName_s{};
    Unk_7102451ba0 _98;
};

}  // namespace uking::action
