#include "KingSystem/Chemical/chmChemical.h"
#include "KingSystem/Chemical/chmSystemConfig.h"
#include <heap/seadExpHeap.h>

namespace ksys::chm {

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

void Chemical::sub_7100D99738(act::Chemical* chemical) {
    _68.pushBack(chemical);
}

void Chemical::sub_7100D99760(act::Chemical* chemical) {
    s32 index = 0;
    for (auto it = _68.dataBegin(), end = _68.dataEnd(); it != end; ++it, ++index) {
        if (*it == chemical) {
            _68.erase(index);
            return;
        }
    }
}

s32 Chemical::sub_7100D9979C() {
    return _80.increment();
}

}  // namespace ksys::chm
