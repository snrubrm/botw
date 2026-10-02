#pragma once

#include "Game/AI/Behavior/behaviorNeckControl.h"

namespace uking::act {
class NPC;
}

namespace uking::behavior {

class NPCTerrorNeckControl : public NeckControl {
    SEAD_RTTI_OVERRIDE(NPCTerrorNeckControl, NeckControl)
public:
    explicit NPCTerrorNeckControl(const InitArg& arg);
    ~NPCTerrorNeckControl() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m15(sead::Vector3f* out) override;

    /* 0x38 */ act::NPC* _38 = nullptr;
};
KSYS_CHECK_SIZE_NX150(NPCTerrorNeckControl, 0x40);

}  // namespace uking::behavior
