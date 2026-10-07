#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <container/seadOffsetList.h>
#include <prim/seadSafeString.h>
#include "aal/aalAttenuationCulling.h"
#include "aal/aalAttenuationDirectivity.h"
#include "aal/aalAttenuator.h"
#include "aal/aalCurve.h"

namespace aal {

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

    /// The list that is exposed (the nodes of its elements are at the offset of the list).
    void setList(sead::OffsetList<T>* list) { mList = list; }

    /// Tells HostIO that the list changed. The HostIO part is compiled out, what is left is the walk over the list
    /// (two loops: the children are detached, then appended again).
    void updateChildren() {
        if (!mList)
            return;
        for (T& component : *mList) {
        }
        for (T& component : *mList) {
        }
    }

private:
    sead::OffsetList<T>* mList = nullptr;
    T* mComponent = nullptr;
};

class AttenuatorListReflexer : public AttenuationComponentListReflexer<Attenuator> {
public:
    void debugCreate_(const sead::SafeString& name) override;
    void debugDestroy_(const sead::SafeString& name) override;
};

class AttenuationCurveListReflexer : public AttenuationComponentListReflexer<Curve> {
public:
    void debugDestroy_(const sead::SafeString& name) override;
};

class AttenuationDirectivityListReflexer : public AttenuationComponentListReflexer<AttenuationDirectivity> {
public:
    void debugCreate_(const sead::SafeString& name) override;
    void debugDestroy_(const sead::SafeString& name) override;
};

class AttenuationCullingListReflexer : public AttenuationComponentListReflexer<AttenuationCulling> {
public:
    void debugCreate_(const sead::SafeString& name) override;
    void debugDestroy_(const sead::SafeString& name) override;
};

}  // namespace aal
