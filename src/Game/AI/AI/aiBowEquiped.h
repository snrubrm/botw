#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physDefines.h"

namespace uking::ai {

class BowEquiped : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BowEquiped, ksys::act::ai::Ai)
public:
    explicit BowEquiped(const InitArg& arg);
    ~BowEquiped() override = default;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;

protected:
    void sub_7100337E2C(ksys::phys::ContactLayer first, ksys::phys::ContactLayer second);
    // 0x710033788c (not decompiled): checks the actor (DynamicCast) and its state (_af8 == 2 / 3).
    bool sub_710033788C();
    // 0x71003377b8 (placeholder name): emits the "UnEquip" (m153 turned true) / "Equip" (turned false) xlink events.
    void sub_71003377B8();

    ksys::act::BaseProcHandle _38;
    bool _48{};
    bool _49{};
    ksys::act::BaseProcLink _50;
};

}  // namespace uking::ai
