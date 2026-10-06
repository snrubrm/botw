#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace sead {
class Heap;
class XmlDocument;
}  // namespace sead

namespace aal {

/// Base class of the parameter sets of the audio effects (delay, reverb...). Setters store the new
/// value and flag the parameter as modified so that the effect re-applies it on its next update.
class FxParamSetter {
    SEAD_RTTI_BASE(FxParamSetter)
public:
    FxParamSetter();
    virtual ~FxParamSetter() = default;

    void resetModifiedFlag();
    /// Clears the modified flags and resets all parameters to their defaults (resetImpl_).
    void reset();
    bool isOnModifiedFlagBit(int bit) const;

    virtual void resetImpl_() {}
    virtual void setupByXmlDocument(sead::XmlDocument* document) {}
    virtual void save() {}
    virtual void load() {}

    void setupByResource(void* data, u32 size, sead::Heap* heap);

protected:
    void setModifiedFlagBit_(int bit);

    u32 mModifiedFlag = 0;
};

}  // namespace aal
