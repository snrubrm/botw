#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

// vtable 0x71023dcc38: unnamed sub-object of SimpleWildlifeRoot with a single virtual function
// (0x7100343a18) and a pointer to itself at +0x18.
class Unk_71023dcc38 {
public:
    virtual bool m0();

    u64 _8 = 0;
    u64 _10;
    Unk_71023dcc38* _18 = this;
    u64 _20 = 0;
    bool _28;
};

class SimpleWildlifeRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SimpleWildlifeRoot, ksys::act::ai::Ai)
public:
    explicit SimpleWildlifeRoot(const InitArg& arg);
    ~SimpleWildlifeRoot() override;

    void m9() override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34();
    virtual bool m35();
    virtual bool m36() { return true; }
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();

    void sub_7100343510();
    // 0x710034342c (declaration only; a FishRoot::m39 guard)
    bool sub_710034342C();

protected:
    Unk_71023dcc38 _38{};
    // static_param at offset 0x68
    const int* mInvalidTgtTimerVal_s{};
    // static_param at offset 0x70
    const int* mInvalidEscapeTimerVal_s{};
    // static_param at offset 0x78
    const bool* mIsDeleteWhenDead_s{};
    // static_param at offset 0x80
    const bool* mIsDeadWhenPut_s{};
    // static_param at offset 0x88
    const bool* mIsEscapeWhenPut_s{};
    // static_param at offset 0x90
    const bool* mIsDeadWhenDrop_s{};
    // map_unit_param at offset 0x98
    const bool* mIsPlayerPut_m{};
    // map_unit_param at offset 0xa0
    const bool* mIsLocatorCreate_m{};
    // map_unit_param at offset 0xa8
    const bool* mIsCreateDead_m{};
    bool* mIsDrop_a{};
    sead::Vector3f _b8;
    ksys::Timer _c4;
    ksys::Timer _d0;
    f32 _dc = 0;
    s32 _e0 = 0;
    s32 _e4 = 0;
    ksys::Timer _e8;
    bool _f4 = false;
    bool _f5 = false;
    bool _f6 = false;
};
KSYS_CHECK_SIZE_NX150(SimpleWildlifeRoot, 0xf8);

}  // namespace uking::ai
