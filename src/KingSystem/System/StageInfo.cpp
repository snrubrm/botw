#include "KingSystem/System/StageInfo.h"

namespace ksys {

static sead::Atomic<int> sUnused;
void (*StageInfo::sChangeScene)(const sead::SafeString& map_name, const sead::SafeString& pos_name,
                                int x, bool triggered_by_stage_select);
bool StageInfo::sIsNotDebugStageAndNotDungeon;
bool StageInfo::sIsMainFieldDungeon;
bool StageInfo::sIsDungeon;
bool StageInfo::sIsCDungeon;
bool StageInfo::sIsMainFieldDungeon2;
bool StageInfo::sIsActorViewer;
bool StageInfo::sIsStageDebug;
bool StageInfo::sIsTestDungeon;
bool StageInfo::sIsDebugOrDevMap;
bool StageInfo::sIsRemainsElectric;
bool StageInfo::sIsRemainsFire;
bool StageInfo::sIsRemainsWater;
bool StageInfo::sIsRemainsWind;
bool StageInfo::sIsFinalTrial;
bool StageInfo::sIsAocField;
bool StageInfo::sIsMainField;
sead::FixedSafeString<32> StageInfo::sCurrentMapType;
sead::FixedSafeString<32> StageInfo::sCurrentMapName;

void StageInfo::sub_7100ED8C64(const sead::SafeString& map_name,
                                const sead::SafeString& pos_name, s32 type, bool stage_select) {
    if (sChangeScene)
        sChangeScene(map_name, pos_name, type, stage_select);
}

const sead::SafeString& StageInfo::getCurrentMapName() {
    return sCurrentMapName;
}

const sead::SafeString& StageInfo::getCurrentMapType() {
    return sCurrentMapType;
}

void StageInfo::setCurrentMap(const sead::SafeString& type, const sead::SafeString& name) {
    sCurrentMapName = name;
    sCurrentMapType = type;
}

void StageInfo::setCurrentMapNameForFieldPos(const sead::Vector3f& pos) {
    if (!sIsNotDebugStageAndNotDungeon)
        return;

    sead::FixedSafeString<32> name;
    name.format("%c-%c", (int(pos.x) + 5000) / 1000 + 'A', (int(pos.z) + 4000) / 1000 + '1');
    sCurrentMapName = name;
}

}  // namespace ksys
