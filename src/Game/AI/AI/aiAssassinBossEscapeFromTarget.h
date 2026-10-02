#pragma once

#include <math/seadVector.h>
#include "Game/AI/AI/aiSimpleEscapeFromTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossEscapeFromTarget : public SimpleEscapeFromTarget {
    SEAD_RTTI_OVERRIDE(AssassinBossEscapeFromTarget, SimpleEscapeFromTarget)
public:
    explicit AssassinBossEscapeFromTarget(const InitArg& arg);
    ~AssassinBossEscapeFromTarget() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m34() override;
    void m35(bool finished) override;
    // 0x7100315788 (not decompiled)
    void m36(sead::Vector3f* dir) override;
    void m37() override;
    // 0x7100315580 (not decompiled)
    void m38(sead::Vector3f* dir, s32 idx) override;
    // 0x7100315c74 (not decompiled: calls the unnamed AI util 0x710072fd0c)
    bool m39(const sead::Vector3f& dir) override;

    // 0x7100315244: _80 = position of the linked map object named AnchorName (else the home position).
    void sub_7100315244();

protected:
    // static_param at offset 0x68
    const float* mCheckDist_s{};
    // static_param at offset 0x70
    sead::SafeString mAnchorName_s{};
    sead::Vector3f _80;
};
KSYS_CHECK_SIZE_NX150(AssassinBossEscapeFromTarget, 0x90);

}  // namespace uking::ai
