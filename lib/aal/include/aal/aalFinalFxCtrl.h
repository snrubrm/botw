#pragma once

#include <hostio/seadHostIONode.h>
#include "aal/aalDeviceType.h"

namespace aal {

/// The control of the final effects of a device. TODO: incomplete.
class FinalFxCtrl : public sead::hostio::Node {
public:
    explicit FinalFxCtrl(DeviceType device);
    virtual ~FinalFxCtrl();

private:
    u8 _8[0x68 - 8];
};
static_assert(sizeof(FinalFxCtrl) == 0x68, "aal::FinalFxCtrl size mismatch");

}  // namespace aal
