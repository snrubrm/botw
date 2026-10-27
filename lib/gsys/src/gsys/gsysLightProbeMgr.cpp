#include "gsys/gsysLightProbeMgr.h"

namespace gsys {

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

// 0x7100c76c3c
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
