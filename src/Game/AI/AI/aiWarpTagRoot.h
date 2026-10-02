#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class WarpTagRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WarpTagRoot, ksys::act::ai::Ai)
public:
    explicit WarpTagRoot(const InitArg& arg);
    ~WarpTagRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    /* 0x38 */ ksys::VFRValue _38;
    /* 0x48 */ Unk_71012419b4 _48;
    /* 0x68 */ sead::Vector3f _68{0.0f, 999999.875f, 0.0f};
    /* 0x74 */ f32 _74 = 0;
    /* 0x78 */ bool _78 = false;
    /* 0x79 */ bool _79 = false;
};
KSYS_CHECK_SIZE_NX150(WarpTagRoot, 0x80);

}  // namespace uking::ai
