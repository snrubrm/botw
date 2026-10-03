#pragma once

#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::ai {

class ClusterRenderCheckTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ClusterRenderCheckTag, ksys::act::ai::Ai)
public:
    explicit ClusterRenderCheckTag(const InitArg& arg);
    ~ClusterRenderCheckTag() override;

    bool init_(sead::Heap* heap) override;
    void calc_() override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool sub_710035404C(ksys::map::Unk_71012497f8Entry* entry);

protected:
    sead::Delegate1R<ClusterRenderCheckTag, ksys::map::Unk_71012497f8Entry*, bool> _38;
    bool _58 = false;
    bool _59 = false;
};

}  // namespace uking::ai
