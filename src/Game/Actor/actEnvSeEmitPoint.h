#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (EnvSeEmitPoint::*; the namespace is a guess). Factory 0x7101029388: new(0x860) + inlined ctor
// (clears job handler 2, sets _1c0 = 15, rebinds the Calc1 job to job1_2). RTTI static 0x260ec68.
class EnvSeEmitPoint : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(EnvSeEmitPoint, ksys::act::Actor)
public:
    explicit EnvSeEmitPoint(const CreateArg& arg);
    ~EnvSeEmitPoint() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    void calcMaybe() override;

    // 2026-10-07: sound manager passes the actor directly to these three original methods.
    void sub_7101029620(bool enabled);
    void sub_7101029658();
    void sub_71010296B0();

    /* 0x83c */ s32 _83c = -1;
    /* 0x840 */ f32 _840 = 0;
    /* 0x844 */ bool _844 = false;
    /* 0x845 */ bool _845 = false;
    /* 0x848 */ f32 _848 = 0;
    /* 0x84c */ bool _84c = false;
    /* 0x84d */ u8 _84d = 0;
    /* 0x850 */ void* _850 = nullptr;
    /* 0x858 */ void* _858 = nullptr;
};
KSYS_CHECK_SIZE_NX150(EnvSeEmitPoint, 0x860);

}  // namespace uking::act
