#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <mc/seadJob.h>
#include <prim/seadBitFlag.h>
#include <prim/seadLongBitFlag.h>

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

    // Inline in the original: ksys::eft::Effect 0x71011b8584 / 0x71011b8658 store +0x90 and set or reset
    // bits 0..60 of +0x58 (re-reading the singleton for every bit). Names are ours.
    sead::LongBitFlag<64>& get_58() { return _58; }
    void set_90(bool value) { _90 = value; }
    // Inline in the original: ksys::eft::Effect::initParticleGroups 0x71011b6154 sets bit 2 (mask 4) of +0x68.
    sead::BitFlag32& get_68() { return _68; }
    // Inline in the original; ksys::CalcParticleAndBaseProcMgr 0x7100f3d864 sets bit 17 through it.
    // Name is a guess.
    u32& getCalcFlags() { return _d7d0; }

    void manualCalcEmitter();
    void clearGroupInfo();
    void addGroupInfo(int group, ParticleScene* scene);
    // 0x7100c53dc8 (declared only)
    bool isNeedDraw(const int* groups, int group_num, u32 mask) const;

private:
    // Emitter calculation job at +0xc1d8 (invoke 0x7100c524c8, D0 0x7100c542b0).
    // manualCalcEmitter clears the two words below before running it directly.
    class ParticleCalcJob : public sead::Job {
    public:
        void invoke() override;

        u8 _18[0x20 - 0x18];
        u32 _20;
        void* _28;
        u8 _30[0x38 - 0x30];
    };
    static_assert(sizeof(ParticleCalcJob) == 0x38);

    // The scenes that use each emitter group (clearGroupInfo 0x7100c53000 clears all 64,
    // addGroupInfo 0x7100c53024 appends without a bounds check).
    struct GroupInfo {
        ParticleScene* mScenes[8];
        s32 mNum;
        u8 _44[0x50 - 0x44];
    };
    static_assert(sizeof(GroupInfo) == 0x50);

    sead::ptcl::PtclSystem* mSystem;  // +0x28
    u8 _30[0x58 - 0x30];
    sead::LongBitFlag<64> _58;
    u8 _60[0x68 - 0x60];
    sead::BitFlag32 _68;
    u8 _6c[0x8c - 0x6c];
    // clearGroupInfo keeps the groups when this is 2.
    u32 _8c;
    bool _90;
    u8 _91[0xc1d8 - 0x91];
    ParticleCalcJob mCalcJob;  // +0xc1d8
    u8 _c210[0xc3d0 - 0xc210];
    GroupInfo mGroupInfos[64];  // +0xc3d0
    /* 0xd7d0 */ u32 _d7d0;
    u8 _d7d4[0xd840 - 0xd7d4];
};
static_assert(sizeof(ParticleMgr) == 0xd840);

}  // namespace gsys
