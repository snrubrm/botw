#include <gsys/gsysParticleMgr.h>
#include <prim/seadMemUtil.h>

namespace gsys {

SEAD_SINGLETON_DISPOSER_IMPL(ParticleMgr)

void ParticleMgr::manualCalcEmitter() {
    mCalcJob._28 = nullptr;
    mCalcJob._20 = 0;
    mCalcJob.invoke();
}

void ParticleMgr::clearGroupInfo() {
    if (_8c == 2)
        return;
    sead::MemUtil::fillZero(mGroupInfos, sizeof(mGroupInfos));
}

void ParticleMgr::addGroupInfo(int group, ParticleScene* scene) {
    GroupInfo& info = mGroupInfos[group];
    for (s32 i = 0; i < info.mNum; ++i) {
        if (info.mScenes[i] == scene)
            return;
    }
    info.mScenes[info.mNum++] = scene;
}

// NON_MATCHING: the compiler combines the mask checks and traversal differently.
bool ParticleMgr::isEnableDrawInfo(const int* groups, int group_num, ParticleDrawInfo info) const {
    const u32 mask = static_cast<u32>(info);
    for (int i = 0; i < group_num; ++i) {
        const GroupInfo& group = mGroupInfos[groups[i]];
        if ((group.mDrawFlags[0] & mask) || (group.mDrawFlags[1] & mask) ||
            (group.mDrawFlags[2] & mask))
            return true;
    }
    const GroupInfo& common = mGroupInfos[63];
    return (common.mDrawFlags[0] & mask) || (common.mDrawFlags[1] & mask) ||
           (common.mDrawFlags[2] & mask);
}

}  // namespace gsys
