#include "Game/gameSceneMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

SEAD_SINGLETON_DISPOSER_IMPL(SceneMgr)

SceneMgr::~SceneMgr() { ; }

void SceneMgr::setStageName(const sead::SafeString& name) {
    mStageName.copy(name);
}

void SceneMgr::setWarpDLCDestPosAndDegree(const sead::Vector3f& pos, const f32& degree) {
    ksys::gdt::setFlag_WarpDLC_DestPos(pos, true);
    ksys::gdt::setFlag_WarpDLC_DestDegree(degree, true);
}
