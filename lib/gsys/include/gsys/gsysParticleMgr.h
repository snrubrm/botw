#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace sead::ptcl {
class PtclSystem;
}

namespace gsys {

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

private:
    sead::ptcl::PtclSystem* mSystem;  // +0x28
    u8 _30[0xd840 - 0x30];
};
static_assert(sizeof(ParticleMgr) == 0xd840);

}  // namespace gsys
