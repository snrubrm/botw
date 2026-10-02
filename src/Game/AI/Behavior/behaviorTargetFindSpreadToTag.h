#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::behavior {

class TargetFindSpreadToTag : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(TargetFindSpreadToTag, ksys::act::ai::Behavior)
public:
    explicit TargetFindSpreadToTag(const InitArg& arg);
    ~TargetFindSpreadToTag() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m9() override;
    void loadParams() override;
    void m8() override;  // not decompiled yet (0x7100646268)

    /* 0x28 */ sead::SafeString mTagName_s{};
    /* 0x38 */ Unk_710235abc8 _38{mActor, 0x8000006};
};
KSYS_CHECK_SIZE_NX150(TargetFindSpreadToTag, 0x90);

}  // namespace uking::behavior
