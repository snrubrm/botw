#pragma once

#include "Game/AI/AI/aiAssassinMiddleAzitoRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// Awareness filter of AssassinMiddleAzitoDlcRoot::m74 (vtable 0x71023d8428; m2 0x710031d380,
// D0 0x710031d6dc).
class Unk_71023d8428 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

class AssassinMiddleAzitoDlcRoot : public AssassinMiddleAzitoRoot {
    SEAD_RTTI_OVERRIDE(AssassinMiddleAzitoDlcRoot, AssassinMiddleAzitoRoot)
public:
    explicit AssassinMiddleAzitoDlcRoot(const InitArg& arg);
    ~AssassinMiddleAzitoDlcRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

    bool m74(Unk2* out, Unk1* info) override;

protected:
};

}  // namespace uking::ai
