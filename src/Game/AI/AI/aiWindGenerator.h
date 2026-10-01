#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WindGenerator : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WindGenerator, ksys::act::ai::Ai)
public:
    explicit WindGenerator(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    virtual void m34();
    virtual void m35();

protected:
};

}  // namespace uking::ai
