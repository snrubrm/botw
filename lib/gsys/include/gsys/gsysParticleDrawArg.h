#pragma once

#include <basis/seadTypes.h>

namespace gsys {

// Particle pass selector; the enumerators are unrecovered.
enum class ParticlePass : int;

// The particle draw parameters of a ModelSceneContext (ModelScene 0x7100c21004 allocates 0x11e8 bytes on the heap,
// runs the constructor 0x7100c50554 and stores the object at context +0x3a0).
// TODO: incomplete. Only the particle group list is modelled.
class ParticleDrawArg {
    friend class ModelSceneContext;

public:
    explicit ParticleDrawArg(int index);
    virtual ~ParticleDrawArg();

    void addParticleGroup(int group);
    void clearParticleGroup();

private:
    u8 _8[0x564 - 0x8];
    /// The emitter groups drawn with this argument (addParticleGroup appends without a bounds check).
    s32 mParticleGroups[32];
    s32 mParticleGroupNum;
    u8 _5e8[0x11e8 - 0x5e8];
};
static_assert(sizeof(ParticleDrawArg) == 0x11e8);

}  // namespace gsys
