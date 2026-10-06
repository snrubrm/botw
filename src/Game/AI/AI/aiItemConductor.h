#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::ai {

class ItemConductor : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ItemConductor, ksys::act::ai::Ai)
public:
    explicit ItemConductor(const InitArg& arg);
    ~ItemConductor() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    bool sub_710044EC60();
    void sub_710044ED64();
    void sub_710044EF44();
    // 0x710044f2dc / 0x710044f408 / 0x710044f514 (placeholder names): gives the current child the armor's bind offsets
    // / the owner (a player) answers PlayerBase::m287 / one of the rune items is selected.
    void sub_710044F2DC();
    bool sub_710044F408();
    bool sub_710044F514();

    Unk_71012419b4 _38;
    Unk_71012419b4 _58;
    bool _78 = false;
};
KSYS_CHECK_SIZE_NX150(ItemConductor, 0x80);

}  // namespace uking::ai
