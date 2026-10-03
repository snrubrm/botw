#pragma once

#include "Game/AI/aiUnk_71000b0800.h"
#include "Game/AI/aiUnk_71025b2aa8.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SimpleAtvUnitDlgStop : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SimpleAtvUnitDlgStop, ksys::act::ai::Behavior)
public:
    explicit SimpleAtvUnitDlgStop(const InitArg& arg);
    ~SimpleAtvUnitDlgStop() override;
    void m7() override;
    void m9() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;
    void m8() override;

    /* 0x28 */ void* mSimpleDialogUnit_a{};
    /* 0x30 */ Unk_71000b0800<Unk_71025b2aa8> _30;
};
KSYS_CHECK_SIZE_NX150(SimpleAtvUnitDlgStop, 0x38);

}  // namespace uking::behavior
