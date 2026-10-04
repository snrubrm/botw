#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SubAS : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SubAS, ksys::act::ai::Behavior)
public:
    explicit SubAS(const InitArg& arg);
    ~SubAS() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    // Original out-of-line update helper; declaration only.
    void sub_7100643440(const sead::SafeString& name);

    /* 0x28 */ const int* mSeqBankIdx_s{};
    /* 0x30 */ const int* mTargetIdx_s{};
    /* 0x38 */ const bool* mIsIgnoreSame_s{};
    /* 0x40 */ sead::SafeString mEnterASName_s{};
    /* 0x50 */ sead::SafeString mLeaveASName_s{};
};
KSYS_CHECK_SIZE_NX150(SubAS, 0x60);

}  // namespace uking::behavior
