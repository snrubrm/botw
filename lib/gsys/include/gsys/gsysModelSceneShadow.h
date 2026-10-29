#pragma once

#include <basis/seadTypes.h>
#include "shadow/aglStaticDepthShadow.h"

namespace sead {
class WorkerMgr;
namespace hostio {
class Node;
}
}

namespace agl::sdw {
class ShadowPrePass;
class SSAO;
}

namespace gsys {

class MaskedLight;
class ModelSceneConfig;
class ModelSceneContext;

// The shadow component of a ModelScene. Only the masked-light shadow interface that
// MaskedLight::assignModelSceneShadow (0x7100c794c0) uses and the projection shadow record
// are declared; the rest of the layout is not modelled.
class ModelSceneShadow {
public:
    // The per-view projection shadow record the scene owns at +0x17a0 (ModelScene +0x3168):
    // ksys::world::SkyMgr::sub_71010E386C stores 0 at +0x408 and two floats at +0x488 / +0x48c,
    // and getDensity reads the per-view densities at +0x558 / +0x578 and +0x634 / +0x638.
    // Only the offsets the two callers use are modelled.
    class ProjectionShadowInfo {
    public:
        // 0x7100c3a06c
        f32 getDensity(int view) const;

    private:
        // One of the two per-view density records getDensity picks.
        struct ViewInfo {
            u8 _0[0x18];
            /* 0x18 */ f32 mDensity;
            u8 _1c[4];
        };
        static_assert(sizeof(ViewInfo) == 0x20);

        u8 _0[0x408];
        /* 0x408 */ u64 _408;
        u8 _410[0x488 - 0x410];
        /* 0x488 */ f32 _488;
        /* 0x48c */ u32 _48c;
        u8 _490[0x558 - 0x490];
        /* 0x558 */ ViewInfo mViewInfo0;
        /* 0x578 */ ViewInfo mViewInfo1;
        u8 _598[0x5b0 - 0x598];
        // Non-zero: view 1 uses the second record.
        /* 0x5b0 */ u8 _5b0;
        u8 _5b1[0x634 - 0x5b1];
        /* 0x634 */ f32 _634;
        /* 0x638 */ f32 _638;
        u8 _63c[4];
        /* 0x640 */ u8 _640;
    };

    // 0x7100c382c8 (declared only)
    void calc(sead::WorkerMgr* wm);

    // 0x7100c3a898 / 0x7100c3acf4 / 0x7100c38558
    bool isSSAOEnabled() const;
    bool isDepthShadowEnabled() const;
    bool isShadowPrePassEnabled() const;
    // 0x7100c3a8bc: releases the view's shadow pre-pass and pops its pass texture.
    void releaseShadowPrePass(ModelSceneContext* context) const;
    // 0x7100c3ad18: puts the light in the first free masked-light shadow slot; false if none.
    bool enableMaskedLightShadow(const MaskedLight* light);
    // 0x7100c3ad58: clears the slot that holds the light; false if there is none.
    bool disableMaskedLightShadow(const MaskedLight* light);
    // 0x7100c3ad9c
    bool isEnableMaskedLightShadow(const MaskedLight* light) const;
    // 0x7100c3ab50: frees the view's SSAO texture when the feature is enabled.
    void releaseSSAO(ModelSceneContext* context) const;
    // 0x7100c3adf0: nothing in the retail build.
    void attachHostIO(sead::hostio::Node* node);
    // 0x7100c3ab74: draws the static depth shadow of the first view.
    void drawDebug(agl::DrawContext* draw_context, const ModelSceneContext& context) const;

    // Inline in the original; ModelScene +0x3168 is the same pointer.
    ProjectionShadowInfo* getProjectionShadowInfo() const { return mProjectionShadowInfo; }

private:
    u8 _0[8];
    /* 0x8 */ ModelSceneConfig* mConfig;
    u8 _10[0x428 - 0x10];
    /* 0x428 */ agl::sdw::SSAO* mSSAO;
    /* 0x430 */ u8 _430[0x438 - 0x430];
    /* 0x438 */ agl::sdw::ShadowPrePass* mShadowPrePass;
    u8 _440[0x444 - 0x440];
    // Bit 0 is tested by drawDebug before it forwards to the static depth shadow.
    /* 0x444 */ u8 _444;
    u8 _445[0x570 - 0x445];
    /* 0x570 */ agl::sdw::StaticDepthShadow mStaticDepthShadow;
    // The projection shadow record the scene allocates; ModelScene +0x3168 is this pointer
    // (ksys::world::SkyMgr::sub_71010E386C and ProjectionShadowInfo::getDensity's caller).
    /* 0x17a0 */ ProjectionShadowInfo* mProjectionShadowInfo;
    // Masked-light shadow slots; enable / disable / isEnable 0xc3ad18 .. 0xc3ad9c walk this array
    // with a 0x68 stride and the MaskedLight pointer at +0x30.
    struct MaskedLightShadow {
        u8 _0[0x30];
        const MaskedLight* mLight;
        u8 _38[0x68 - 0x38];
    };
    static_assert(sizeof(MaskedLightShadow) == 0x68);
    /* 0x17a8 */ s32 mMaskedLightShadowNum;
    u8 _17ac[0x17b0 - 0x17ac];
    /* 0x17b0 */ MaskedLightShadow* mMaskedLightShadows;
};

}  // namespace gsys
