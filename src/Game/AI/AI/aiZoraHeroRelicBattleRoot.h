#pragma once

#include "Game/AI/aiUnk_7102433970.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ZoraHeroRelicBattleRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ZoraHeroRelicBattleRoot, ksys::act::ai::Ai)
public:
    explicit ZoraHeroRelicBattleRoot(const InitArg& arg);
    ~ZoraHeroRelicBattleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // aitree_variable at offset 0x38
    void* mZoraHeroShowMsgUnit_a{};
    bool _40 = false;
    bool _41 = false;
    bool _42 = false;
    bool _43 = false;
    bool _44 = false;
    bool _45 = false;
    Unk_7102433970 _48;
};
KSYS_CHECK_SIZE_NX150(ZoraHeroRelicBattleRoot, 0x198);

}  // namespace uking::ai
