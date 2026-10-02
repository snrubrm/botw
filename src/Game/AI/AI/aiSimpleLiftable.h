#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

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
    Unk_71024507c8 _38{0x1800004};
    Unk_71023da100 _78;
};

}  // namespace uking::ai
