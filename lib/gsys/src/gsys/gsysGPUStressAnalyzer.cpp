#include <gsys/gsysGPUStressAnalyzer.h>

namespace gsys {

// NON_MATCHING: the +0x24/+0x28 pair (92.125f, 2.0f) takes three instructions to materialise
// where the original uses two (ORR of 0x4000000040000000 plus one MOVK).
GPUStressAnalyzer::GPUStressAnalyzer()
    : mCount(0), mAdjustors(nullptr), _18(0), _1c(0), mFlags(0), _24(92.125f), _28(2.0f),
      _2c(2.0f), _30(2.0f), _34(0.03f), _38(0.05f) {}

// 0x7100c74044
void GPUStressAnalyzer::AdjustorFrameScale::init(sead::Heap*) {}

// 0x7100c749f4
void GPUStressAnalyzer::AdjustorFrameScale::calc() {}

// 0x7100c749f0
void GPUStressAnalyzer::AdjustorFrameScale::preCalcImpl_(int, ModelScene*, bool) {}

// 0x7100c749f8
void GPUStressAnalyzer::AdjustorFrameScale::postCalcImpl_(int, ModelScene*) {}

// 0x7100c749fc
void GPUStressAnalyzer::AdjustorFrameScale::restoreImpl_(int, ModelScene*) {}

// 0x7100c74048
void GPUStressAnalyzer::AdjustorFXAA::init(sead::Heap*) {}

// 0x7100c74a04: ramps the factor up while it is positive and the interval back down to its floor.
void GPUStressAnalyzer::AdjustorFXAA::calc() {
    if (_8 > 0.0f) {
        _8 += _14;
        if (_8 > 1.0f)
            _8 = 1.0f;
    }
    if (_10 > _c) {
        _10 += sUnk_7101da2618;
        if (_10 < _c)
            _10 = _c;
    }
}

// 0x7100c74a00
void GPUStressAnalyzer::AdjustorFXAA::preCalcImpl_(int, ModelScene*, bool) {}

// 0x7100c74a5c
void GPUStressAnalyzer::AdjustorFXAA::postCalcImpl_(int, ModelScene*) {}

// 0x7100c74a60
void GPUStressAnalyzer::AdjustorFXAA::restoreImpl_(int, ModelScene*) {}

// 0x7100c7404c
void GPUStressAnalyzer::AdjustorLPP::init(sead::Heap*) {}

// 0x7100c74a68: the same interval step as the FXAA adjustor.
void GPUStressAnalyzer::AdjustorLPP::calc() {
    if (_10 > _c) {
        _10 += sUnk_7101da2618;
        if (_10 < _c)
            _10 = _c;
    }
}

// 0x7100c74a64
void GPUStressAnalyzer::AdjustorLPP::preCalcImpl_(int, ModelScene*, bool) {}

// 0x7100c74a94
void GPUStressAnalyzer::AdjustorLPP::postCalcImpl_(int, ModelScene*) {}

// 0x7100c74a98
void GPUStressAnalyzer::AdjustorLPP::restoreImpl_(int, ModelScene*) {}

}  // namespace gsys
