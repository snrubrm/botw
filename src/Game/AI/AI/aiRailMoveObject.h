#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::map {
class Rail;
}

namespace uking::ai {

class RailMoveObject : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RailMoveObject, ksys::act::ai::Ai)
public:
    explicit RailMoveObject(const InitArg& arg);
    ~RailMoveObject() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void m9() override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;

    virtual ksys::map::Rail* m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();

    void sub_7100533C58();
    void sub_7100533DB0();

protected:
    // static_param at offset 0x38
    sead::SafeString mASKeyName_On_s{};
    // static_param at offset 0x48
    sead::SafeString mASKeyName_Off_s{};
    // map_unit_param at offset 0x58
    const float* mRailMoveSpeed_m{};
    ksys::map::Rail* _60 = nullptr;
    s32 _68 = 0;  // number of rail points
    f32 _6c = 0;  // position on the rail
    f32 _70 = 0;
    u8 _74 = 0xff;
};
KSYS_CHECK_SIZE_NX150(RailMoveObject, 0x78);

}  // namespace uking::ai
