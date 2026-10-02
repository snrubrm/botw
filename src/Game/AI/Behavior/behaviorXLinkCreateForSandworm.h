#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Behavior/behaviorOnStateXLinkCreate.h"

namespace uking::behavior {

class XLinkCreateForSandworm : public OnStateXLinkCreate {
    SEAD_RTTI_OVERRIDE(XLinkCreateForSandworm, OnStateXLinkCreate)
public:
    explicit XLinkCreateForSandworm(const InitArg& arg);
    ~XLinkCreateForSandworm() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m9() override;
    void loadParams() override;
    void m8() override;  // not decompiled yet (0x710064721c)
    // 0x7100647278
    void sub_7100647278();

    /* 0x78 */ const int* mPosType_s{};
    /* 0x80 */ sead::SafeString mBoneKey_s{};
    /* 0x90 */ gsys::BoneAccessKeyEx _90;
};
KSYS_CHECK_SIZE_NX150(XLinkCreateForSandworm, 0xc8);

}  // namespace uking::behavior
