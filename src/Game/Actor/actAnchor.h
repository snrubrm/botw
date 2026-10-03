#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace sead {
class Camera;
class DrawContext;
class Projection;
class Viewport;
}  // namespace sead

namespace uking::act {

// Placeholder (the argument of the debug draw virtual in the slot after Actor's last one; only the fields
// Anchor::m148 reads are modelled).
struct DebugDrawArg {
    /* 0x00 */ u8 _0[0x28];
    /* 0x28 */ sead::Camera* camera;
    /* 0x30 */ sead::Projection* projection;
    /* 0x38 */ sead::Viewport* viewport;
    /* 0x40 */ u8 _40[8];
    /* 0x48 */ sead::DrawContext* draw_context;
};

// Name from the CSV (Anchor::*; the namespace is a guess). Factory 0x7100e21abc: new(0x840) + inlined ctor (clears
// job handler 2, sets _1c0 = 2, rebinds the Calc1 job to job1_2). RTTI static 0x7102602268. One new virtual (slot 148,
// a debug draw that projects the actor's position; not written yet).
class Anchor : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(Anchor, ksys::act::Actor)
public:
    explicit Anchor(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    void calcMaybe() override;

    /* 148 */ virtual void m148(DebugDrawArg* arg);

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
};
KSYS_CHECK_SIZE_NX150(Anchor, 0x840);

}  // namespace uking::act
