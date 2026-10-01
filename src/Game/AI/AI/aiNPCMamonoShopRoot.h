#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCMamonoShopRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NPCMamonoShopRoot, NPCRoot)
public:
    explicit NPCMamonoShopRoot(const InitArg& arg);
    ~NPCMamonoShopRoot() override;
    bool hasPreDeleteCb() override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x238
    sead::SafeString mMamonoShopPlacement_m{};
    bool _248 = false;
};
KSYS_CHECK_SIZE_NX150(NPCMamonoShopRoot, 0x250);

}  // namespace uking::ai
