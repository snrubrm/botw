#pragma once

#include <basis/seadTypes.h>

namespace agl::env {
class Fog;
}

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
    // 0x7100c50b68 / 0x7100c50bb0
    void setZFog(const agl::env::Fog* fog);
    void setYFog(const agl::env::Fog* fog);

private:
    u8 _8[0x564 - 0x8];
    /// The emitter groups drawn with this argument (addParticleGroup appends without a bounds check).
    s32 mParticleGroups[32];
    s32 mParticleGroupNum;
    u8 _5e8[0x5f0 - 0x5e8];
    /* 0x5f0 */ const agl::env::Fog* mZFog;
    /* 0x5f8 */ const agl::env::Fog* mYFog;
    u8 _600[0x610 - 0x600];
    /* 0x610 */ f32 mZFogOffset;
    /* 0x614 */ f32 mZFogScale;
    /* 0x618 */ f32 mYFogOffset;
    /* 0x61c */ f32 mYFogScale;
    u8 _620[0x11e8 - 0x620];
};
static_assert(sizeof(ParticleDrawArg) == 0x11e8);

}  // namespace gsys
