#pragma once

#include <mc/seadJobQueue.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

// Message 0x8000018 (sender Unk_7102416670): the owner's own actor link.
struct Unk_7102416670_Payload {
    ksys::act::BaseProcLink mLink;
    sead::JobQueueLock mLock;
};

// vtable 0x7102416670 (PullOutTree _48; functions next to PullOutTree's): sends message 0x8000018.
class Unk_7102416670 : public Unk_7102357d20 {
public:
    explicit Unk_7102416670(ksys::act::Actor* actor);
    void* m2() override { return &_18; }

    Unk_7102416670_Payload _18;
};

// vtable 0x7102416698 (PullOutTree _78): accepts message 0x800001a. The listener's m2 is inlined into
// PullOutTree::handleMessage_, so it is defined in PullOutTree's TU.
class Unk_7102416698 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

namespace uking::ai {

class PullOutTree : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PullOutTree, ksys::act::ai::Ai)
public:
    explicit PullOutTree(const InitArg& arg);
    ~PullOutTree() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    void calc_() override;

    // inline-only in the original; name is a guess. Evidence: the TargetPos accessor sequence repeats in
    // enter_ and the child-change helpers: the target actor's position.
    void getTargetPos(sead::Vector3f* out) const;

    // Each of these changes the child (rotating / moving / waiting for the tree to be created /
    // equipping it) with a TargetPos parameter.
    void sub_7100532CF8();
    void sub_7100532E04();
    void sub_7100533178();
    void sub_7100533314();

    // static_param at offset 0x38
    const float* mTurnAng_s{};
    // dynamic_param at offset 0x40
    ksys::act::BaseProcLink* mTargetActor_d{};
    Unk_7102416670 _48{mActor};
    Unk_7102416698 _78;
};
KSYS_CHECK_SIZE_NX150(PullOutTree, 0xb0);

}  // namespace uking::ai
