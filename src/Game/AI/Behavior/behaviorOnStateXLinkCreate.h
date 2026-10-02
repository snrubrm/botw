#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

class OnStateXLinkCreate : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OnStateXLinkCreate, ksys::act::ai::Behavior)
public:
    explicit OnStateXLinkCreate(const InitArg& arg);
    ~OnStateXLinkCreate() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    virtual bool m14() { return true; }
    // 0x7100631cac (not decompiled: xlink2 handle internals)
    void sub_7100631CAC();

    /* 0x28 */ const bool* mIsEndKill_s{};
    /* 0x30 */ const bool* mIsEndFade_s{};
    /* 0x38 */ sead::SafeString mKey_s{};
    /* 0x48 */ sead::SafeString mEndKey_s{};
    /* 0x58 */ Unk_71012419b4 _58;
};
KSYS_CHECK_SIZE_NX150(OnStateXLinkCreate, 0x78);

}  // namespace uking::behavior
