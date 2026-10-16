#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::behavior {

class TargetFindSpreadToTag : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(TargetFindSpreadToTag, ksys::act::ai::Behavior)
public:
    explicit TargetFindSpreadToTag(const InitArg& arg);
    ~TargetFindSpreadToTag() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void leave() override;
    void loadParams() override;
    void enter() override;

    /* 0x28 */ sead::SafeString mTagName_s{};
    /* 0x38 */ Unk_710235abc8 _38{mActor, 0x8000006};
};
KSYS_CHECK_SIZE_NX150(TargetFindSpreadToTag, 0x90);

}  // namespace uking::behavior
