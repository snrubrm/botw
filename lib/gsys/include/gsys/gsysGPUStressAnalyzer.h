#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>

namespace sead {
class Heap;
template <typename T>
class PtrArray;
}  // namespace sead

namespace gsys {

class ModelScene;

// GPU stress-test driver. Constructor 0x7100c73d24 stores vtable 0x71024d0e40 (hostio::Node's
// type getter plus the destructor slots); initialize 0x7100c73d74 allocates the two 0x588-byte
// adjustor objects (the array at +0x10, count at +0x08) and sets the flags at +0x1c / +0x20.
// The class is 0x40 bytes: the game constructor 0x7100c01d84 constructs it at +0x70 of its owner
// and the next member starts at +0xb0.
//
// TODO: only the parts the adjustor rows use are modelled. The adjustor objects themselves
// (0x588 bytes each) and the initialize / calc bodies stay undecompiled.
class GPUStressAnalyzer : public sead::hostio::Node {
public:
    // The five virtuals of every adjustor, in vtable order (each adjustor's own table starts
    // with its init and then calc / preCalcImpl_ / postCalcImpl_ / restoreImpl_).
    class Adjustor {
    public:
        virtual void init(sead::Heap* heap) = 0;
        virtual void calc() = 0;
        virtual void preCalcImpl_(int index, ModelScene* scene, bool flag) = 0;
        virtual void postCalcImpl_(int index, ModelScene* scene) = 0;
        virtual void restoreImpl_(int index, ModelScene* scene) = 0;
    };

    // 0x7100c74044 / 0x7100c749f0 / 0x7100c749f4 / 0x7100c749f8 / 0x7100c749fc: empty.
    class AdjustorFrameScale : public Adjustor {
    public:
        void init(sead::Heap* heap) override;
        void calc() override;
        void preCalcImpl_(int index, ModelScene* scene, bool flag) override;
        void postCalcImpl_(int index, ModelScene* scene) override;
        void restoreImpl_(int index, ModelScene* scene) override;
    };

    // 0x7100c74048 / 0x7100c74a00 / 0x7100c74a04 / 0x7100c74a5c / 0x7100c74a60.
    class AdjustorFXAA : public Adjustor {
    public:
        void init(sead::Heap* heap) override;
        void calc() override;
        void preCalcImpl_(int index, ModelScene* scene, bool flag) override;
        void postCalcImpl_(int index, ModelScene* scene) override;
        void restoreImpl_(int index, ModelScene* scene) override;

    private:
        f32 _8;
        f32 _c;
        f32 _10;
        f32 _14;
    };

    // 0x7100c7404c / 0x7100c74a64 / 0x7100c74a68 / 0x7100c74a94 / 0x7100c74a98.
    class AdjustorLPP : public Adjustor {
    public:
        void init(sead::Heap* heap) override;
        void calc() override;
        void preCalcImpl_(int index, ModelScene* scene, bool flag) override;
        void postCalcImpl_(int index, ModelScene* scene) override;
        void restoreImpl_(int index, ModelScene* scene) override;

    private:
        f32 _8;
        f32 _c;
        f32 _10;
    };

    GPUStressAnalyzer();
    virtual ~GPUStressAnalyzer() = default;

    // 0x7100c73d74
    void initialize(sead::Heap* heap);
    // 0x7100c74050
    void calc(sead::PtrArray<ModelScene>* scenes);

private:
    /* 0x08 */ u32 mCount;
    /* 0x0c */ u8 _c[4];
    /* 0x10 */ Adjustor** mAdjustors;
    /* 0x18 */ u32 _18;
    /* 0x1c */ u32 _1c;
    /* 0x20 */ u32 mFlags;
    /* 0x24 */ f32 _24;
    /* 0x28 */ f32 _28;
    /* 0x2c */ f32 _2c;
    /* 0x30 */ f32 _30;
    /* 0x34 */ f32 _34;
    /* 0x38 */ f32 _38;
    /* 0x3c */ u8 _3c[4];
};
static_assert(sizeof(GPUStressAnalyzer) == 0x40);

// The per-frame adjustor step (-0.01f) the FXAA and LPP adjustors load from 0x7101da2618.
__attribute__((visibility("hidden"))) extern const f32 sUnk_7101da2618;

}  // namespace gsys
