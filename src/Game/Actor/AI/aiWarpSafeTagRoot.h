#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class WarpSafeTagRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WarpSafeTagRoot, ksys::act::ai::Ai)
public:
    explicit WarpSafeTagRoot(const InitArg& arg);
    ~WarpSafeTagRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    /* 0x38 */ ksys::VFRValue _38;
    /* 0x48 */ Unk_71012419b4 _48;
    /* 0x68 */ bool _68 = false;
    /* 0x69 */ u8 _69 = 0;  // 0 / 1: the return fog is shown
    /* 0x6a */ bool _6a = false;
};
KSYS_CHECK_SIZE_NX150(WarpSafeTagRoot, 0x70);

}  // namespace uking::ai
