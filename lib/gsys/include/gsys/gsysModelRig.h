#pragma once

#include <environment/aglEnvObj.h>
#include "gsys/gsysModelAccessKey.h"

namespace gsys {

// Constructor 0x7100c82f1c / named destructor 0x7100c8326c. The three real
// string parameters end at +0x260; the game light owner constructs its first
// owned CriticalSection there. No lifetime bodies are modelled here.
class ModelRig : public agl::env::EnvObj {
    SEAD_RTTI_OVERRIDE(ModelRig, agl::env::EnvObj)
public:
    ModelRig();
    ~ModelRig() override;

    s32 getTypeID() const override;

    // Nonvirtual helper called by the game light owner 0x7100f17e50,
    // which also passes this Context to ParameterBase::genMessageParameter.
    void sub_7100C83D44(sead::hostio::Context* context);

    // 0x7100c83d48: the game LocationalLightRig vtable slot 0x7100f17ff8 forwards here.
    // Event 0x2711 clears the three name filters; event 0x2710 registers every model that
    // is bound to a scene (Model +0xf0) through the virtual m23.
    void listenPropertyEventEnvObj(const sead::hostio::PropertyEvent* event);

    // Table 0x71024d1fd8, slots 23..26. The complete native traversal
    // 0x7100c8338c passes Model and its actual bone/material keys and names.
    virtual void m23(Model* model);
    virtual void m24(Model* model, const BoneAccessKey& key, const sead::SafeString& name);
    virtual void m25(Model* model, const MaterialAccessKey& key, const sead::SafeString& name);
    virtual void m26(Model* model, int unit_index);

protected:
    void initialize(int index, sead::Heap* heap) override;

    // Actual constructor parameter keys, each Parameter<FixedSafeString<64>>
    // has size 0x70 and is registered with this EnvObj's IParameterObj base.
    agl::utl::Parameter<sead::FixedSafeString<64>> mModelName;
    agl::utl::Parameter<sead::FixedSafeString<64>> mBonePrefix;
    agl::utl::Parameter<sead::FixedSafeString<64>> mMaterialPrefix;
};
static_assert(sizeof(ModelRig) == 0x260);

}  // namespace gsys
