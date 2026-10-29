#pragma once

#include <environment/aglEnvObj.h>
#include "gsys/gsysIModelRigObj.h"
#include "gsys/gsysLightRig.h"
#include "gsys/gsysMaskedSpotLight.h"
#include "gsys/gsysPointLight.h"
#include "gsys/gsysSpotLight.h"

namespace gsys {

// The per-model rig object. The type-to-id allocate function 0x7100c57eec allocates 0x340 bytes
// for PointLight, constructs the light (0x300 bytes) at +0 and the model rig object at +0x300, so
// the record derives from the light type and from IModelRigObj. The manager keeps the owning rig
// pointer at +0x28 after those bases (0x328 for PointLight, 0x358 for SpotLight, 0x470 for
// MaskedSpotLight).
template <typename T>
class LightRigObj : public T, public IModelRigObj {
    SEAD_RTTI_OVERRIDE(LightRigObj, agl::env::EnvObj)
public:
    template <typename U>
    friend class LightResMgr;

    static const agl::env::TypeInfo* sTypeInfo;
    // The type info's first halfword is the type id; the rig getters load it the same way.
    s32 getTypeID() const { return sTypeInfo->id; }

private:
    // Zeroed by the allocate function; meaning not established yet.
    u64 _18 = 0;
    u64 _20 = 0;
    LightRig<T>* mRig;  // +0x28
    // The type-to-id allocate functions store -1 here, zero at +0x34, -1 at +0x3c and zero at
    // +0x3e (0x7100c57f48, 0x7100c62c2c and 0x7100c7c65c).
    s16 _30 = -1;
    s32 _34 = 0;
    u8 _38[4];
    u16 _3c = 0xffff;
    u8 _3e[2] = {};
};

extern template class LightRigObj<MaskedSpotLight>;
extern template class LightRigObj<PointLight>;
extern template class LightRigObj<SpotLight>;

static_assert(sizeof(LightRigObj<PointLight>) == 0x340);
static_assert(sizeof(LightRigObj<SpotLight>) == 0x370);
static_assert(sizeof(LightRigObj<MaskedSpotLight>) == 0x488);

}  // namespace gsys
