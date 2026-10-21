#pragma once

#include <basis/seadTypes.h>

namespace sead {
class WorkerMgr;
}

namespace gsys {

class MaskedLight;
class ModelSceneConfig;

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

private:
    u8 _0[8];
    /* 0x8 */ ModelSceneConfig* mConfig;
    u8 _10[0x428 - 0x10];
    /* 0x428 */ void* mSSAO;
    /* 0x430 */ u8 _430[0x438 - 0x430];
    /* 0x438 */ void* mShadowPrePass;
    u8 _440[0x480 - 0x440];
};

}  // namespace gsys
