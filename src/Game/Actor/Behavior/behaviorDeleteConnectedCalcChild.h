#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class DeleteConnectedCalcChild : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(DeleteConnectedCalcChild, ksys::act::ai::Behavior)
public:
    explicit DeleteConnectedCalcChild(const InitArg& arg);
    ~DeleteConnectedCalcChild() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(DeleteConnectedCalcChild, 0x28);

}  // namespace uking::behavior
