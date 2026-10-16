#include "KingSystem/Chemical/chmChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
#include <cmath>
#include <heap/seadExpHeap.h>

namespace ksys::chm {

void sub_7100D997B4(sead::Vector3f* out, const sead::Vector3f& value) {
    for (s32 i = 0; i < 3; ++i) {
        const f32 sign = out->e[i] >= 0.0f ? 1.0f : -1.0f;
        if (sign == (value.e[i] >= 0.0f ? 1.0f : -1.0f)) {
            out->e[i] = sign * sead::Mathf::max(sead::Mathf::abs(out->e[i]),
                                              sead::Mathf::abs(value.e[i]));
        } else {
            out->e[i] += value.e[i];
        }
    }
}

SEAD_SINGLETON_DISPOSER_IMPL(Chemical)

Chemical::~Chemical() {
    _68.freeBuffer();
    SystemConfig::deleteInstance();
}

void Chemical::createChmresAndHeap(sead::Heap* heap) {
    SystemConfig::createInstance(heap);
    SystemConfig::instance()->init(heap);
    _68.allocBuffer(8, heap, 8);
    _78 = sead::ExpHeap::create(0x300000, "chm::System", heap, 8,
                               sead::Heap::cHeapDirection_Forward, true);
}

void Chemical::sub_7100D99738(act::Unk_71024dd490* holder) {
    _68.pushBack(holder);
}

void Chemical::sub_7100D99760(act::Unk_71024dd490* holder) {
    s32 index = 0;
    for (auto it = _68.dataBegin(), end = _68.dataEnd(); it != end; ++it, ++index) {
        if (*it == holder) {
            _68.erase(index);
            return;
        }
    }
}

s32 Chemical::sub_7100D9979C() {
    return _80.increment();
}

// Scales a value into [1, 1000) by powers of 1000 (the mantissa for an SI prefix).
f32 sub_7100D99B74(f32 value) {
    f32 exponent = std::log10(value);
    if (exponent > 24.0f)
        exponent -= 24.0f;
    else if (exponent > 21.0f)
        exponent -= 21.0f;
    else if (exponent > 18.0f)
        exponent -= 18.0f;
    else if (exponent > 15.0f)
        exponent -= 15.0f;
    else if (exponent > 12.0f)
        exponent -= 12.0f;
    else if (exponent > 9.0f)
        exponent -= 9.0f;
    else if (exponent > 6.0f)
        exponent -= 6.0f;
    else if (exponent > 3.0f)
        exponent -= 3.0f;
    else if (exponent > 0.0f)
        ;
    else if (exponent > -3.0f)
        exponent += 3.0f;
    else if (exponent > -6.0f)
        exponent += 6.0f;
    else if (exponent > -9.0f)
        exponent += 9.0f;
    else if (exponent > -12.0f)
        exponent += 12.0f;
    else if (exponent > -15.0f)
        exponent += 15.0f;
    else if (exponent > -18.0f)
        exponent += 18.0f;
    else if (exponent > -21.0f)
        exponent += 21.0f;
    else if (exponent > -24.0f)
        exponent += 24.0f;
    return std::pow(10.0f, exponent);
}

// The SI prefix that goes with sub_7100D99B74.
const char* sub_7100D99CD4(f32 value) {
    const f32 exponent = std::log10(value);
    if (exponent > 24.0f)
        return "Y";
    if (exponent > 21.0f)
        return "Z";
    if (exponent > 18.0f)
        return "E";
    if (exponent > 15.0f)
        return "P";
    if (exponent > 12.0f)
        return "T";
    if (exponent > 9.0f)
        return "G";
    if (exponent > 6.0f)
        return "M";
    if (exponent > 3.0f)
        return "k";
    if (exponent > 0.0f)
        return " ";
    if (exponent > -3.0f)
        return "m";
    if (exponent > -6.0f)
        return "u";
    if (exponent > -9.0f)
        return "n";
    if (exponent > -12.0f)
        return "p";
    if (exponent > -15.0f)
        return "f";
    if (exponent > -18.0f)
        return "a";
    if (exponent > -21.0f)
        return "z";
    if (exponent > -24.0f)
        return "y";
    return "_";
}

}  // namespace ksys::chm
