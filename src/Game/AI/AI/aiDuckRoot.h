#pragma once

#include "Game/AI/AI/aiPreyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DuckRoot : public PreyRoot {
    SEAD_RTTI_OVERRIDE(DuckRoot, PreyRoot)
public:
    explicit DuckRoot(const InitArg& arg);
    ~DuckRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m34() override;
    bool m35() override;
    bool m37() override;
    void m41() override;

protected:
    void calc_() override;
    // Unnamed in the binary (0x7100374194): sub_7100504BF0(), then changes to the "滝接触" child with the
    // actor position.
    void sub_7100374194();
};

}  // namespace uking::ai
