#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {

u32 getAwarenessTerrorFlags(u32 hash);
u32 getAwarenessSensorFlags(u32 hash);
// 0x7100d7a93c (placeholder name): the factor for sensor `sense` (0-3) in `weather` (1 when the weather is
// invalid), limited by a second table when EnvMgr::returnFalse or EnvMgr::isInSandstorm.
f32 sub_7100D7A93C(s32 sense, s32 weather);
f32 sub_7100D7AA24(s32 idx);

}  // namespace ksys::act
