#pragma once

#include "Game/AI/Action/actionAreaFireObserveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaFireObserve : public AreaFireObserveBase {
    SEAD_RTTI_OVERRIDE(AreaFireObserve, AreaFireObserveBase)
public:
    explicit AreaFireObserve(const InitArg& arg);

protected:
    // Overrides of the Unk_71024e5408 observer virtuals. Like the other AreaTagAction-family
    // classes (e.g. SandwichDetectionAreaTag), the implementations also occupy primary slots 32-34
    // in declaration order; the secondary slots hold the adjusted copies (the _ZThn32_ thunks,
    // which llvm folds into full copies for these small bodies).
    void m2() override;
    bool m15(const void* data) override;
    void m5() override;

    // Whether the observed fire is currently lit (set by m15, emitted by m5).
    bool _50 = false;
};
KSYS_CHECK_SIZE_NX150(AreaFireObserve, 0x58);

}  // namespace uking::action
