#pragma once

namespace ksys::act {
class Actor;
class BaseProcHandle;
class InstParamPack;
}  // namespace ksys::act

// Unnamed free helper of the Swarm actor utility area (placeholder name; declared in the Swarm AIs).

// 0x710072a80c: requests the creation of the actor named by the Swarm parameter list's DeadActorName
// (nothing when it is empty).
void sub_710072A80C(ksys::act::Actor* actor, ksys::act::BaseProcHandle* handle,
                    ksys::act::InstParamPack* params);
