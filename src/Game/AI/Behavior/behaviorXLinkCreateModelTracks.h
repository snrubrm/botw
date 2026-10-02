#pragma once

#include <math/seadVector.h>
#include "Game/AI/Behavior/behaviorXLinkCreate.h"

namespace uking::behavior {

class XLinkCreateModelTracks : public XLinkCreate {
    SEAD_RTTI_OVERRIDE(XLinkCreateModelTracks, XLinkCreate)
public:
    explicit XLinkCreateModelTracks(const InitArg& arg);
    ~XLinkCreateModelTracks() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    void m15(sead::Vector3f* out) override;
    void m16(sead::Vector3f* out) override;  // TODO 0x7100647ae4

    /* 0x78 */ sead::Vector3f _78;
};
KSYS_CHECK_SIZE_NX150(XLinkCreateModelTracks, 0x88);

}  // namespace uking::behavior
