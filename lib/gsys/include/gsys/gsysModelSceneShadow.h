#pragma once

#include <basis/seadTypes.h>

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
// MaskedLight::assignModelSceneShadow (0x7100c794c0) uses is declared; the layout is not modelled.
class ModelSceneShadow {
public:
    // 0x7100c382c8 (declared only)
    void calc(sead::WorkerMgr* wm);

    // 0x7100c3a898 / 0x7100c3acf4 / 0x7100c38558
    bool isSSAOEnabled() const;
    bool isDepthShadowEnabled() const;
    bool isShadowPrePassEnabled() const;
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

private:
    u8 _0[8];
    /* 0x8 */ ModelSceneConfig* mConfig;
    u8 _10[0x428 - 0x10];
    /* 0x428 */ agl::sdw::SSAO* mSSAO;
    /* 0x430 */ u8 _430[0x438 - 0x430];
    /* 0x438 */ agl::sdw::ShadowPrePass* mShadowPrePass;
    u8 _440[0x17a8 - 0x440];
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
