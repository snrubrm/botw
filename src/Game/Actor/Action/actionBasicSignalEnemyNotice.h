#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BasicSignalEnemyNotice : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BasicSignalEnemyNotice, ksys::act::ai::Action)
public:
    explicit BasicSignalEnemyNotice(const InitArg& arg);
    ~BasicSignalEnemyNotice() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();

    bool _1c = false;
};

}  // namespace uking::action
