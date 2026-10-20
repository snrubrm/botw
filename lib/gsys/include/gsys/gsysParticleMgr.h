#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace sead::ptcl {
class PtclSystem;
}

namespace gsys {

class ParticleScene;

// createInstance 0x7100c50f8c allocates 0xd840 bytes and ctor 0x7100c5106c
// installs vtable 0x71024cefa0. The IPtclModelEnumerator interface base and
// later members are not modelled; only the destructor slots and singleton prefix are declared.
class ParticleMgr {
    SEAD_SINGLETON_DISPOSER(ParticleMgr)
public:
    ParticleMgr();
    virtual ~ParticleMgr();

    // initialize 0x7100c51694 constructs a sead::ptcl::PtclSystem (derived from
    // nn::vfx::System) at +0x28. Effect kill/updatePlayerPos 0x71011b7ee0 / 0x71011b8808 use it.
    sead::ptcl::PtclSystem* getSystem() const { return mSystem; }

    void clearGroupInfo();
    void addGroupInfo(int group, ParticleScene* scene);

private:
    // The scenes that use each emitter group (clearGroupInfo 0x7100c53000 clears all 64,
    // addGroupInfo 0x7100c53024 appends without a bounds check).
    struct GroupInfo {
        ParticleScene* mScenes[8];
        s32 mNum;
        u8 _44[0x50 - 0x44];
    };
    static_assert(sizeof(GroupInfo) == 0x50);

    sead::ptcl::PtclSystem* mSystem;  // +0x28
    u8 _30[0x8c - 0x30];
    // clearGroupInfo keeps the groups when this is 2.
    u32 _8c;
    u8 _90[0xc3d0 - 0x90];
    GroupInfo mGroupInfos[64];  // +0xc3d0
    u8 _d7d0[0xd840 - 0xd7d0];
};
static_assert(sizeof(ParticleMgr) == 0xd840);

}  // namespace gsys
