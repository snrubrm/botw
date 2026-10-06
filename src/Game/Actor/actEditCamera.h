#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// Name from the CSV (EditCamera::*; the namespace is a guess). Factory 0x710079172c: new(0x8b8) + inlined ctor
// (zeroes 0x78 bytes at 0x840). RTTI static 0x71025c9718.
// TODO: incomplete (fields unknown; construct only the simple overrides).
class EditCamera : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(EditCamera, ksys::act::Actor)
public:
    explicit EditCamera(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

protected:
    InitResult init_() override;
    void onJobPush2_(ksys::act::JobType type) override;

public:
    int getCalcTiming() override;

    // The camera names copied from the CameraEdit action (7 consecutive strings).
    struct CameraNames {
        const char* names[7];
    };

    // 0x71007917bc: returns &_840._40.
    CameraNames* sub_71007917BC();

    // 8-aligned: a plain byte array would be placed in Actor's tail padding (0x83c).
    struct alignas(8) Unk840 {
        void* _0 = nullptr;
        u8 _8[0x38]{};
        CameraNames _40{};
    };
    /* 0x840 */ Unk840 _840{};
};
KSYS_CHECK_SIZE_NX150(EditCamera, 0x8b8);

}  // namespace uking::act
