#pragma once

#include "Game/gameNpcShopData.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCMakeArtifact : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCMakeArtifact, ksys::act::ai::Action)
public:
    explicit NPCMakeArtifact(const InitArg& arg);
    ~NPCMakeArtifact() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    NpcShopData _20;
    bool _40 = false;
    bool _41 = false;
    u8 _42[0x6];
};
KSYS_CHECK_SIZE_NX150(NPCMakeArtifact, 0x48);

}  // namespace uking::action
