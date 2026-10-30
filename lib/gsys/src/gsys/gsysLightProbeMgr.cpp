#include "gsys/gsysLightProbeMgr.h"

namespace gsys {

// 0x7100c74a9c
LightProbeMgr::SHIndexBuffer::SHIndexBuffer()
    : mType(0, "type", this), mUsedIndexNum(0, "used_index_num", this),
      mMaxIndexNum(0, "max_index_num", this), mIndexBuffer("index_buffer", this) {}

// NON_MATCHING: freeBuffer checks the allocation flag again after the virtual ownership check;
// the original uses the result of the virtual call directly. The deleting destructor also differs.
// 0x7100c74c18
LightProbeMgr::SHIndexBuffer::~SHIndexBuffer() {
    mType = 0;
    // called through a pointer in the original (not devirtualised)
    if ((&mIndexBuffer)->isBinaryInternalBuffer())
        mIndexBuffer.freeBuffer();
    mUsedIndexNum = 0;
    mMaxIndexNum = 0;
}

// 0x7100c74d90
LightProbeMgr::SHDataBuffer::SHDataBuffer()
    : mType(0, "type", this), mMaxSHDataNum(0, "max_sh_data_num", this),
      mUsedDataNum(0, "used_data_num", this), mPerProbeFloatNum(27, "per_probe_float_num", this),
      mDataBuffer("data_buffer", this) {}

// NON_MATCHING: freeBuffer checks the allocation flag again after the virtual ownership check;
// the original uses the result of the virtual call directly. The deleting destructor also differs.
// 0x7100c74f4c
LightProbeMgr::SHDataBuffer::~SHDataBuffer() {
    // called through a pointer in the original (not devirtualised)
    if ((&mDataBuffer)->isBinaryInternalBuffer())
        mDataBuffer.freeBuffer();
    mUsedDataNum = 0;
}

// 0x7100c76ba8
void LightProbeMgr::calc() {
    _248 = 0;
}

// 0x7100c76bb0
void LightProbeMgr::calcView(u32, const sead::Matrix44f&, const sead::Matrix34f&) {}

// 0x7100c76bb4
void LightProbeMgr::calcGPU() {}

// 0x7100c76bb8
void LightProbeMgr::calcGPU(u32) {}

// 0x7100c76bbc
void LightProbeMgr::drawDebug(agl::DrawContext*, int) const {}

// 0x7100c7663c
void LightProbeMgr::ProbeVolumeMgr::postWrite_() const {}

// 0x7100c76634
bool LightProbeMgr::ProbeVolumeMgr::preWrite_() const {
    return true;
}

// 0x7100c76c3c
// 0x7100c76bc0
LightProbeMgr::DebugProbeInterp::~DebugProbeInterp() = default;

void LightProbeMgr::DebugProbeInterp::initialize(sead::Heap* heap) {
    if (!heap)
        return;
    mBlock0.startDeclare(1, heap);
    mBlock0.declare_(agl::UniformBlock::Type::cType_6, 1, 0, 1);
    mBlock1.startDeclare(1, heap);
    mBlock1.declare_(agl::UniformBlock::Type::cType_6, 7, 0, 1);
    mBlock0.create(heap, 1, 1);
    mBlock1.create(heap, 1, 1);
}

// 0x7100c77dc0
LightProbeMgr::ProbeVolumeMgr::InitArg::~InitArg() {}

}  // namespace gsys
