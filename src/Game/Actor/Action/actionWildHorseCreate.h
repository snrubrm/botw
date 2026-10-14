#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class WildHorseCreate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WildHorseCreate, ksys::act::ai::Action)
public:
    explicit WildHorseCreate(const InitArg& arg);
    ~WildHorseCreate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mMinCreateNum_s{};
    // static_param at offset 0x28
    const int* mMaxCreateNum_s{};
    // map_unit_param at offset 0x30
    const int* mWildHorseCreateNum_m{};
    sead::Buffer<ksys::act::BaseProcLink> _38;
    sead::Buffer<ksys::act::BaseProcHandle> _48;
    f32 _58 = 40000.0f;
    s32 _5c = 4;
};
KSYS_CHECK_SIZE_NX150(WildHorseCreate, 0x60);

}  // namespace uking::action
