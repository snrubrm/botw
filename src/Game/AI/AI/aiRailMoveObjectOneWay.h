#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::map {
class Rail;
}

namespace uking::ai {

class RailMoveObjectOneWay : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RailMoveObjectOneWay, ksys::act::ai::Ai)
public:
    explicit RailMoveObjectOneWay(const InitArg& arg);
    ~RailMoveObjectOneWay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m9() override;

    void sub_710053479C();
    void sub_71005348DC();

protected:
    // 0x7100534f90: at the first / last rail point: play the off AS
    void sub_7100534F90();
    // static_param at offset 0x38
    sead::SafeString mASKeyName_On_s{};
    // static_param at offset 0x48
    sead::SafeString mASKeyName_Off_s{};
    ksys::map::Rail* _58 = nullptr;
    s32 _60 = 0;  // number of rail points
    f32 _64 = 0;
    f32 _68 = 0;
    u8 _6c = 0;
    bool _6d = false;
    bool _6e = false;
};
KSYS_CHECK_SIZE_NX150(RailMoveObjectOneWay, 0x70);

}  // namespace uking::ai
