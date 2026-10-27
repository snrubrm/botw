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

}  // namespace gsys
