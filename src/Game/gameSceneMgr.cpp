#include "Game/gameSceneMgr.h"
#include <devenv/seadGameConfig.h>
#include <prim/seadSafeString.h>
#include "Game/gameMapStaticLoadMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {
void sub_7100A9F4F8();
void sub_7100A9F528();
void loadMapMainFieldLocationMubin();
}  // namespace uking::ui

// 0x71025ce528: the field types the static mubin table covers. The original builds it in this
// TU's static initialiser (0x7100895164) and registers the array's destructor.
sead::SafeString sFieldTypeStrings[] = {"MainField", "CDungeon", "MainFieldDungeon", "AocField"};

// 0x710089531c: clears the "do not build the static mubin table" flag when the game asks for map
// statics, then runs the UI's (empty) hook. Placeholder name.
void sub_710089531C() {
    if (sead::GameConfig::instance()->get_82d())
        ksys::map::sUnk_7102603DD8 = false;
    uking::ui::sub_7100A9F528();
}

// 0x7100895340: the UI's static-info loader. Placeholder name.
void sub_7100895340() {
    uking::ui::sub_7100A9F4F8();
}

// 0x7100895344: the main field location mubin loader. Placeholder name.
void sub_7100895344() {
    uking::ui::loadMapMainFieldLocationMubin();
}

// 0x71008952bc
void initMapStaticResources(sead::Heap* heap) {
    if (sead::GameConfig::instance()->get_82d())
        ksys::map::sUnk_7102603DD8 = false;
    ksys::map::MapStaticLoadMgr::loadStaticFiles(sFieldTypeStrings, 4, heap, sub_710089531C,
                                                 sub_7100895340);
    setLoadLocationMubinCallback(sub_7100895344);
}

SEAD_SINGLETON_DISPOSER_IMPL(SceneMgr)

SceneMgr::~SceneMgr() { ; }

void SceneMgr::setStageName(const sead::SafeString& name) {
    mStageName.copy(name);
}

void SceneMgr::setWarpDLCDestPosAndDegree(const sead::Vector3f& pos, const f32& degree) {
    ksys::gdt::setFlag_WarpDLC_DestPos(pos, true);
    ksys::gdt::setFlag_WarpDLC_DestDegree(degree, true);
}
