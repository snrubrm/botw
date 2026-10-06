#include "KingSystem/System/Vibration.h"
#include <mc/seadCoreInfo.h>
#include "KingSystem/Event/evtUnk_7100dc816c.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(Vibration)

void Vibration::sub_71010BB36C() {
    for (auto& slot : _6c8)
        slot._4e = 8;
    _808 = {0, 0, 0};
    _814 = 0;
}

void Vibration::sub_71010BB428(const Unk2& request) {
    if (evt::sub_7100DC866C())
        return;
    sub_71010BB468(request, 0);
}

// NON_MATCHING: the original reads the volatile CoreId once more (discarded) before the first
// bank index
void Vibration::sub_71010BB468(const Unk2& request, s32 a2) {
    if (!request.isValid())
        return;

    const sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
    for (s32 i = 0; i < 4; ++i) {
        if (_2a8[core][i].isFree()) {
            _2a8[core][i].sub_71010BC19C(request, a2);
            return;
        }
    }
}

// NON_MATCHING: the original reads the volatile CoreId once more (discarded) before the first
// bank index
void Vibration::sub_71010BB5E0(const Unk1& request, s32 a2) {
    if (!request.isValid())
        return;

    const sead::CoreId core = sead::CoreInfo::getCurrentCoreId();
    for (s32 i = 0; i < 4; ++i) {
        if (_2a8[core][i].isFree()) {
            _2a8[core][i].x(request, a2);
            return;
        }
    }
}

void Vibration::sub_71010BB800(const Unk2& request) {
    sub_71010BB468(request, 1);
}

void Vibration::sub_71010BB808(const Unk1& request) {
    sub_71010BB5E0(request, 1);
}

void Vibration::sub_71010BB810(s32 idx) {
    if (idx >= 0 && idx < 4)
        _6c8[idx]._4e = 8;
}

// NON_MATCHING: the original keeps the two signed index checks (tbnz + b.gt); ours are merged into
// one unsigned compare
void Vibration::sub_71010BB82C(s32 idx, f32 damping) {
    if (idx < 0)
        return;
    if (idx > 3)
        return;
    if (damping < 0.0f)
        return;
    _6c8[idx]._48 = damping;
}

void Vibration::sub_71010BB85C(void* ptr) {
    _818 = ptr;
    for (auto& pattern : _28)
        pattern._40 = ptr;
}

Vibration::Unk2::Unk2()
    : Unk1(0, sead::Vector3f::zero, 0, nullptr, 1.0f, 100.0f, 1), _28(sead::Vector3f::ey) {}

Vibration::Unk2::Unk2(s32 a1, const sead::Vector3f& a2, u8 a3, void* a4, f32 a5, f32 a6,
                      const sead::Vector3f& a7, u8 a8)
    : Unk1(a1, a2, a3, a4, a5, a6, a8), _28(a7) {}

Vibration::Unk1::Unk1(s32 a1, const sead::Vector3f& a2, u8 a3, void* a4, f32 a5, f32 a6, u8 a7)
    : _0(a2), _10(a4), _18(a5), _1c(a6), _20(a1), _24(a7), _25(a3) {}

}  // namespace ksys
