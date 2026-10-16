#include "KingSystem/Chemical/chmChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
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

}  // namespace ksys::chm
