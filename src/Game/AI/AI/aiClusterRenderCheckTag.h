#pragma once

#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ClusterRenderCheckTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ClusterRenderCheckTag, ksys::act::ai::Ai)
public:
    explicit ClusterRenderCheckTag(const InitArg& arg);
    ~ClusterRenderCheckTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // Placeholder (type unknown): the cluster passed to the delegate; only the byte at +0x80 is read.
    struct ClusterInfo {
        u8 _0[0x80];
        bool _80;
    };

    // 0x710035404c (unnamed in the binary): the delegate bound in enter_.
    bool sub_710035404C(ClusterInfo* cluster);

protected:
    sead::Delegate1R<ClusterRenderCheckTag, ClusterInfo*, bool> _38;
    bool _58 = false;
    bool _59 = false;
};
KSYS_CHECK_SIZE_NX150(ClusterRenderCheckTag, 0x60);

}  // namespace uking::ai
