#pragma once

namespace gsys {

class MaskedLight;

// The shadow component of a ModelScene. Only the masked-light shadow interface that
// MaskedLight::assignModelSceneShadow (0x7100c794c0) uses is declared; the layout is not modelled.
class ModelSceneShadow {
public:
    // 0x7100c3ad18: puts the light in the first free masked-light shadow slot; false if none.
    bool enableMaskedLightShadow(const MaskedLight* light);
    // 0x7100c3ad58: clears the slot that holds the light; false if there is none.
    bool disableMaskedLightShadow(const MaskedLight* light);
    // 0x7100c3ad9c
    bool isEnableMaskedLightShadow(const MaskedLight* light) const;
};

}  // namespace gsys
