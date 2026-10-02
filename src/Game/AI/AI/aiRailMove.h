#pragma once

#include <math/seadVector.h>
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RailMove, ksys::act::ai::Ai)
public:
    explicit RailMove(const InitArg& arg);
    ~RailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    virtual void m34();
    virtual f32 m35() = 0;
    virtual ksys::map::Rail* m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual bool m40();

    void sub_710032BCAC(f32 progress);
    void sub_710032C088();
    void sub_710032C0D4();
    void sub_710032C2B0();
    void sub_710032C56C();
    bool sub_710032C5AC() const;
    void sub_710032C5BC(sead::Vector3f* pos) const;
    void sub_710032C5F8();
    f32 sub_710032C97C() const;
    bool sub_710032C984(f32* progress, sead::Vector3f* pos, const sead::Vector3f& target) const;
    void sub_710032CA64();

protected:
    // static_param at offset 0x38
    const bool* mIsIgnoreNoWaitStopPoint_s{};
    Unk_71024f15c0 _40;
};
KSYS_CHECK_SIZE_NX150(RailMove, 0xa0);

}  // namespace uking::ai
