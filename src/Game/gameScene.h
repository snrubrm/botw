#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

class StageBinder;

// TODO
class GameScene {
public:
    // FIXME: figure out return types, parameters and names
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();

    SEAD_RTTI_BASE(GameScene)

public:
    virtual ~GameScene();
    virtual bool ret0();
    virtual void m11_null();

    virtual void StageMgrEnter();
    virtual void StageMgrRun();
    virtual void StageMgrLeave();
    virtual bool StageMgrReenter();
    virtual void StageSelectEnter();
    virtual void StageSelectRun();
    virtual void StageSelectLeave();
    virtual bool StageSelectReenter();
    virtual void StageTransitionEnter();
    virtual void StageTransitionRun();
    virtual void StageTransitionLeave();
    virtual bool StageTransitionReenter();
    virtual void LunchTitleEnter();
    virtual void LunchTitleRun();
    virtual void LunchTitleLeave();
    virtual bool LunchTitleReenter();
    virtual void NewSaveEnter();
    virtual void NewSaveRun();
    virtual void NewSaveLeave();
    virtual bool NewSaveReenter();
    virtual void PatchErrorEnter();
    virtual void PatchErrorRun();
    virtual void PatchErrorLeave();
    virtual bool PatchErrorReenter();

    static bool isOpenWorldDemo() { return sIsOpenWorldDemo; }

    /// Get the current map type (e.g. MainFieldDungeon)
    static const sead::SafeString& getCurrentMapType();

    /// Get the current map name (e.g. RemainsWind, FinalTrial, ...)
    static const sead::SafeString& getCurrentMapName();

    void setFadeType(s32 type);
    bool hasStageBinder() const;
    void setStageBinder(StageBinder* binder);

    // 0x71007b5340 / 0x71007b5350: getters of the static flags below.
    static bool getIsInitialisingStage();
    // 0x71007b7d88 / 0x71007beb30 (CSV GameScene::setInstance2 / setInstance3): copy sInstance to the other two
    // pointers.
    static void setInstance2();
    static void setInstance3();

    // Placeholder names for the globals of the GameScene TU (addresses are in the names).
    static GameScene* sInstance;                       // 0x71025cb0e0
    static bool sIsInitialisingStage;                  // 0x71025cb0ea
    static GameScene* sInstance2;                      // 0x71025cb720
    static GameScene* sInstance3;                      // 0x71025cb898
    static bool sFlag;                                 // 0x71025cb8ac

private:
    static bool sIsOpenWorldDemo;

    // TODO
    u8 _8[0x279 - 0x8];
    u8 _279;
    u8 _27a[0x2a8 - 0x27a];
    StageBinder* _2a8;
    u8 _2b0[0x93c - 0x2b0];
    s32 _93c;
};

// Free functions of the GameScene TU (CSV names; the namespace is a guess).
bool sceneStartEventReady();
void setSceneStartEventReady();
void setSceneStartEventNotReady();
bool isTransitionFromFarActorDone();
void setIsTransitionFromFarActorDone(bool value);
bool getIsStageUnloaded();
void setIsStageUnloaded(bool value);
void gameSceneSetFlag(bool value);
bool gameSceneGetFlag();
bool isGameSceneInitialized();

}  // namespace uking
