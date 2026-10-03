#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Stole : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Stole, ksys::act::ai::Ai)
public:
    explicit Stole(const InitArg& arg);

    bool isChangeable() const override { return true; }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual void m34() {}

protected:
};

}  // namespace uking::ai
