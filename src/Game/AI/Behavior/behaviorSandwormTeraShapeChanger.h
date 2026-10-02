#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SandwormTeraShapeChanger : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SandwormTeraShapeChanger, ksys::act::ai::Behavior)
public:
    explicit SandwormTeraShapeChanger(const InitArg& arg);
    ~SandwormTeraShapeChanger() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mEnterShapeIdx_s{};
    /* 0x30 */ const int* mLeaveShapeIdx_s{};
    /* 0x38 */ const bool* mIsSetCurrentShape_s{};
    /* 0x40 */ u32 _40 = 0x4;
};
KSYS_CHECK_SIZE_NX150(SandwormTeraShapeChanger, 0x48);

}  // namespace uking::behavior
