#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

namespace aal {

// TODO: the attenuation components are not modelled. Only what the reflexers need (a virtual destructor) is declared.
class Attenuator {
public:
    virtual ~Attenuator();
};

class Curve {
public:
    virtual ~Curve();
};

class AttenuationCulling {
public:
    virtual ~AttenuationCulling();
};

class AttenuationDirectivity {
public:
    virtual ~AttenuationDirectivity();
};

/// Exposes a list of attenuation components of type T to HostIO and owns the component that is being edited
/// (created and destroyed through HostIO).
template <typename T>
class AttenuationComponentListReflexer : public sead::hostio::Node {
public:
    virtual ~AttenuationComponentListReflexer() {
        if (mComponent) {
            delete mComponent;
            mComponent = nullptr;
        }
    }

    virtual void debugCreate_(const sead::SafeString&) {}
    virtual void debugDestroy_(const sead::SafeString&) {}

private:
    void* _8;
    T* mComponent;
};

}  // namespace aal
