#pragma once

#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

// vtable 0x71023e02c0: rail follower used by DragonRootBase (no RTTI; overrides only the
// destructor, its D0 is at 0x7100357d24). Placeholder name.
class Unk_71023e02c0 : public Unk_71024f15c0 {
public:
    ~Unk_71023e02c0() override = default;
};

class DragonRootBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DragonRootBase, ksys::act::ai::Ai)
public:
    explicit DragonRootBase(const InitArg& arg);
    ~DragonRootBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;
    void calc_() override;

    virtual f32 m34() = 0;
    virtual ksys::map::Rail* m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual bool m39();

    void sub_7100356764(ksys::map::Rail* rail, f32 progress);
    void sub_7100356A7C();
    void sub_7100356CFC();
    void changeToMove();
    void sub_7100356F30();
    bool sub_7100357314(f32 progress);
    bool sub_7100357414(f32 progress);
    void sub_7100357440(f32 wait_frame);
    bool sub_710035797C(f32* out_progress, sead::Vector3f* out_pos, const sead::Vector3f& pos);
    void sub_7100357A5C();

protected:
    Unk_71023e02c0 _38;
};
KSYS_CHECK_SIZE_NX150(DragonRootBase, 0x98);

}  // namespace uking::ai
