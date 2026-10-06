#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace uking {

// TODO: Incomplete, but all getters should be there
class StageInfo {
public:
    // 0x71007cc08c / 0x71007cc098: out-of-line (defined in gameScene.cpp, so `sInfo` is reached through the GOT).
    static const sead::Vector3f& getPSavePosAngleForStageGen();
    static const sead::Vector3f& getPSavePosForStageGen();
    static bool isDebugOrDevMap() { return sInfo.mIsDebugOrDevMap; }
    static bool isViewerMapType() { return sInfo.mIsViewerMapType; }
    static bool isDungeon() { return sInfo.mIsDungeon; }
    static bool isCDungeon() { return sInfo.mIsCDungeon; }
    static bool isTestDungeon() { return sInfo.mIsTestDungeon; }
    static bool isMainFieldDungeon() { return sInfo.mIsMainFieldDungeon; }
    static bool isActorViewer() { return sInfo.mIsActorViewer; }
    static bool isStageDebug() { return sInfo.mIsStageDebug; }
    static bool isRemainsElectric() { return sInfo.mIsRemainsElectric; }
    static bool isRemainsFire() { return sInfo.mIsRemainsFire; }
    static bool isRemainsWater() { return sInfo.mIsRemainsWater; }
    static bool isRemainsWind() { return sInfo.mIsRemainsWind; }
    static bool isFinalTrial() { return sInfo.mIsFinalTrial; }
    static bool isAocField() { return sInfo.mIsAocField; }
    static bool isMainField() { return sInfo.mIsMainField; }

    static sead::FixedSafeString<256> sStr;

private:
    // 0x71025cc248 / 0x71025cc254: separate objects in the original (the getters return their GOT addresses).
    static sead::Vector3f sPSavePosAngleForStageGen;
    static sead::Vector3f sPSavePosForStageGen;
    static StageInfo sInfo;

    bool mIsDebugOrDevMap;
    bool mIsViewerMapType;
    bool mIsDungeon;
    bool mIsCDungeon;
    bool mIsTestDungeon;
    bool mIsMainFieldDungeon;
    bool mIsActorViewer;
    bool mIsStageDebug;
    bool mIsRemainsElectric;
    bool mIsRemainsFire;
    bool mIsRemainsWater;
    bool mIsRemainsWind;
    bool mIsFinalTrial;
    bool mIsAocField;
    bool mIsMainField;
};

}  // namespace uking
