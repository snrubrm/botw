#pragma once

#include <prim/seadEnum.h>

namespace aal {
/// The output devices (the Switch only has the TV).
SEAD_ENUM(DeviceType, TV);
/// The buses a sound can be routed to.
SEAD_ENUM(BusType, Main, AuxA, AuxB, AuxC);
}  // namespace aal
