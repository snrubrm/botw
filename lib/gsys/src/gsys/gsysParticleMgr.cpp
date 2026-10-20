#include <gsys/gsysParticleMgr.h>
#include <prim/seadMemUtil.h>

namespace gsys {

SEAD_SINGLETON_DISPOSER_IMPL(ParticleMgr)

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

}  // namespace gsys
