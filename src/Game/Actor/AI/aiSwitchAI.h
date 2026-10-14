#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwitchAI, ksys::act::ai::Ai)
public:
    explicit SwitchAI(const InitArg& arg);
    ~SwitchAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34();
    virtual bool m35() { return false; }
    virtual bool m36() { return false; }
    virtual bool m37() { return false; }
    virtual bool m38() { return false; }
    virtual void m39() {}
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();

protected:
};

}  // namespace uking::ai
