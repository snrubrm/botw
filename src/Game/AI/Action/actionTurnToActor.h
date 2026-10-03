#pragma once

#include "Game/AI/Action/actionTurnToActorBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TurnToActor : public TurnToActorBase {
    SEAD_RTTI_OVERRIDE(TurnToActor, TurnToActorBase)
public:
    explicit TurnToActor(const InitArg& arg);
    ~TurnToActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // slots 32-38 (0x7100d34850 / d34cfc / d34e30 / ec184 / ec190 / ec19c / d34c84); signatures are guesses.
    void m32() override;
    virtual void m33();
    virtual f32 m34();
    virtual int m35() { return *mASSlot_d; }
    virtual int m36() { return *mSequenceBank_d; }
    virtual bool m37() { return *mIsIgnoreSame_d; }
    virtual const sead::SafeString& m38();

    // dynamic_param at offset 0x20
    int* mASSlot_d{};
    // dynamic_param at offset 0x28
    int* mSequenceBank_d{};
    // dynamic_param at offset 0x30
    bool* mIsIgnoreSame_d{};
    // dynamic_param at offset 0x38
    bool* mIsChangeable_d{};
    // dynamic_param at offset 0x40
    sead::SafeString mASName_d{};
    // dynamic_param at offset 0x50
    sead::SafeString mDemoASName_d{};
};

}  // namespace uking::action
