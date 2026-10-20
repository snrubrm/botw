#include "gsys/gsysIModelProcedural.h"
#include <basis/seadNew.h>
#include <new>

namespace gsys {

IModelProcedural::IModelProcedural() = default;

int IModelProcedural::getMaterialNum() const {
    return mRenderUnits.size();
}

int IModelProcedural::getShapeNum() const {
    return mRenderUnits.size();
}

int IModelProcedural::getViewNum() const {
    return _c8;
}

sead::SafeString IModelProcedural::getName() const {
    return "gsys::IModelProcedural";
}

void IModelProcedural::setProcedualPassName(int index, const sead::SafeString& name) {
    mRenderUnits[index].mName = name;
}

bool IModelProcedural::isMaterialVisible(int index) const {
    return mRenderUnits[index]._30 & 1;
}

ModelRenderUnit* IModelProcedural::getModelRenderUnit(int index) {
    return &mRenderUnits[index];
}

const ModelRenderUnit* IModelProcedural::getModelRenderUnit(int index) const {
    return &mRenderUnits[index];
}

// The two priorities are stored biased (+8 and +0x20) in bit fields of the render unit option word.
void IModelProcedural::setProcedualPassPriority(int index, int a, int b) {
    u32& flags_a = getModelRenderUnit(index)->getFlags10();
    flags_a = (flags_a & 0xc3ffffff) | ((a + 8) << 26);
    u32& flags_b = getModelRenderUnit(index)->getFlags10();
    flags_b = (flags_b & 0xffc0ffff) | ((b + 0x20) << 16);
}

void IModelProcedural::setMaterialVisible(int index, bool visible) {
    if (!visible)
        mRenderUnits[index]._30 &= ~1;
    else
        mRenderUnits[index]._30 |= 1;
    gatherVisibleModelRenderUnit();
}

// NON_MATCHING: the original keeps the RenderUnit vtable store before each element's base destructor; our
// RenderUnit destructor has a trivial body, so Clang skips it. What makes the original body non-trivial is unknown.
IModelProcedural::~IModelProcedural() {
    mRenderUnits.freeBuffer();
}

void IModelProcedural::initRenderUnits_(s32 count, s32 value, sead::Heap* heap) {
    if (count >= 1) {
        auto* units = new (heap, 8, std::nothrow) RenderUnit[count];
        if (units)
            mRenderUnits.setBuffer(count, units);
    }

    _c8 = value;

    const u32 num = mRenderUnits.size();
    RenderUnit* unit = mRenderUnits.getBufferPtr();
    for (size_t i = 0; i != num; ++i, ++unit)
        unit->initialize(this, i, heap);

    sub_7100C3D634(heap);
    setLodThreshold(-1.0f, -1, mNumLods - 1);
    mCalcWeight = 1000;
}

}  // namespace gsys
