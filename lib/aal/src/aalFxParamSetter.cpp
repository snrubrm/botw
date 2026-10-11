#include "aal/aalFxParamSetter.h"
#include <heap/seadExpHeap.h>
#include "aal/aalXmlUtil.h"

namespace aal {

// 0x71014064fc
FxParamSetter::FxParamSetter() = default;

// 0x7101406514
void FxParamSetter::resetModifiedFlag() {
    mModifiedFlag = 0;
}

// 0x710140651c
void FxParamSetter::reset() {
    mModifiedFlag = 0;
    resetImpl_();
}

// 0x710140652c
bool FxParamSetter::isOnModifiedFlagBit(int bit) const {
    return (1 << bit) & mModifiedFlag;
}

// 0x7101406544
void FxParamSetter::setModifiedFlagBit_(int bit) {
    mModifiedFlag |= 1 << bit;
}

// 0x710140655c
void FxParamSetter::setupByResource(void* data, u32 size, sead::Heap* heap) {
    auto* work_heap = sead::ExpHeap::create(0, "fx_param_setter", heap, 8,
                                          sead::Heap::cHeapDirection_Forward, false);
    auto* document = XmlUtil::createTextDocument(data, size, work_heap);
    if (document) {
        setupByXmlDocument(document);
        work_heap->destroy();
    }
}

}  // namespace aal
