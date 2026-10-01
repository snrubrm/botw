#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SimpleLiftable : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SimpleLiftable, ksys::act::ai::Ai)
public:
    explicit SimpleLiftable(const InitArg& arg);
    ~SimpleLiftable() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

    virtual void m34();
    virtual void m35();
    virtual bool m36();
    virtual void m37() {}

protected:
};

}  // namespace uking::ai
