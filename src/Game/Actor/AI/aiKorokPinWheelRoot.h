#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::ai {

class KorokPinWheelRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokPinWheelRoot, ksys::act::ai::Ai)
public:
    explicit KorokPinWheelRoot(const InitArg& arg);
    ~KorokPinWheelRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRotSpd_s{};
    // static_param at offset 0x40
    const float* mLength_s{};
    ksys::VFRValue _48;
    sead::Matrix33f _54;
};
KSYS_CHECK_SIZE_NX150(KorokPinWheelRoot, 0x78);

}  // namespace uking::ai
