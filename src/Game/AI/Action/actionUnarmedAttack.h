#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class UnarmedAttack : public ActionEx {
    SEAD_RTTI_OVERRIDE(UnarmedAttack, ActionEx)
public:
    explicit UnarmedAttack(const InitArg& arg);
    ~UnarmedAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual int m32();
    virtual float m33();
    virtual void m34();
};

}  // namespace uking::action
