#pragma once

#include <math/seadVector.h>
#include "Game/Actor/Behavior/behaviorXLinkCreate.h"

namespace uking::behavior {

class XLinkCreateModelTracks : public XLinkCreate {
    SEAD_RTTI_OVERRIDE(XLinkCreateModelTracks, XLinkCreate)
public:
    explicit XLinkCreateModelTracks(const InitArg& arg);
    ~XLinkCreateModelTracks() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m15(sead::Vector3f* out) override;
    void m16(sead::Vector3f* out) override;

    /* 0x78 */ sead::Vector3f _78;
};
KSYS_CHECK_SIZE_NX150(XLinkCreateModelTracks, 0x88);

}  // namespace uking::behavior
