#pragma once

#include <aal/aalListenerPoser.h>
#include <aal/aalTimedFader.h>
#include <gfx/seadCamera.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {

// Concrete poser built by sub_71012C5810 (0x160 bytes, vtable 0x710251b1f0).
class Unk_710251b1f0 : public aal::ListenerPoser {
    SEAD_RTTI_OVERRIDE(Unk_710251b1f0, aal::ListenerPoser)
public:
    // Inlined in the factory at 0x71012c5810; no separate constructor in the original.
    explicit Unk_710251b1f0(const sead::SafeString& name)
        : aal::ListenerPoser(name), _70(sead::Vector3f::zero), _7c(true), _7d(false),
          _80(sead::Vector3f::zero), _8c(sead::Vector3f::ez), _98(sead::Vector3f::ey),
          _a4(sead::Vector3f::zero), _b0(1.0f, aal::FadeCurveType::Linear, 1.0f),
          _d8(1), _dc(0.0f), _e0(_7c), _148(0.0f), _14c(0.0f), _150(50.0f),
          _154(400.0f), _158(1.0f) {
        _b0.setValueImmediate(1.0f);
    }
    ~Unk_710251b1f0() override;

    void reset() override;
    void calcListenerMatrix(sead::Matrix34f* local_matrix,
                            sead::Matrix34f* local_matrix_for_angle) override;

    void sub_71012C6090(const sead::Vector3f& position);
    void sub_71012C60C0(f32 value);

    sead::Vector3f _70;
    bool _7c;
    bool _7d;
    u8 _7e[2];
    sead::Vector3f _80;
    sead::Vector3f _8c;
    sead::Vector3f _98;
    sead::Vector3f _a4;
    aal::TimedFader _b0;
    s32 _d8;
    f32 _dc;
    bool _e0;
    u8 _e1[7];
    sead::LookAtCamera _e8;
    f32 _148;
    f32 _14c;
    f32 _150;
    f32 _154;
    f32 _158;
};
KSYS_CHECK_SIZE_NX150(Unk_710251b1f0, 0x160);

}  // namespace ksys::snd

ksys::snd::Unk_710251b1f0* sub_71012C5810(const sead::SafeString& name, sead::Heap* heap);
