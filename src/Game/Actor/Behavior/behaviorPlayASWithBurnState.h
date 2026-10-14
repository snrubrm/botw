#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class PlayASWithBurnState : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PlayASWithBurnState, ksys::act::ai::Behavior)
public:
    explicit PlayASWithBurnState(const InitArg& arg);
    ~PlayASWithBurnState() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void sub_7100632B48(s8 state);
    s8 sub_7100632CD8();

    // inline-only in the original; name is a guess (the same sequence is inlined four times into sub_7100632CD8).
    bool isASFinished() {
        auto* list = mActor->getASList();
        return list && list->x_4(*mTargetIdx_s, *mSeqBankIdx_s);
    }

    // inline-only in the original; name is a guess (the same sequence is inlined three times into sub_7100632B48).
    void playAS(const sead::SafeString& name) {
        if (name.isEmpty())
            return;
        if (auto* list = mActor->getASList())
            list->startAnimationMaybe(-1.0f, -1.0f, name, *mTargetIdx_s, *mSeqBankIdx_s, true);
    }

    /* 0x28 */ const int* mTargetIdx_s{};
    /* 0x30 */ const int* mSeqBankIdx_s{};
    /* 0x38 */ sead::SafeString mOnWaitASName_s{};
    /* 0x48 */ sead::SafeString mOnToOffASName_s{};
    /* 0x58 */ sead::SafeString mOffToOnASName_s{};
    /* 0x68 */ u8 _68 = 0;
};
KSYS_CHECK_SIZE_NX150(PlayASWithBurnState, 0x70);

}  // namespace uking::behavior
