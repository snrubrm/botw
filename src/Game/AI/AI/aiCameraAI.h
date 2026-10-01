#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CameraAI, ksys::act::ai::Ai)
public:
    explicit CameraAI(const InitArg& arg);
    ~CameraAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34(sead::Heap* heap) { return true; }
    virtual void m35(ksys::act::ai::InlineParamPack* params) {}
    virtual void m36() {}
    virtual void m37() {}
    virtual void m38() {}

protected:
};

}  // namespace uking::ai
