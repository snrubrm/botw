#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/gameScene320.h"
#include "KingSystem/Utils/Types.h"

namespace uking {

class StageBinder;

// TODO
class GameScene {
public:
    // FIXME: figure out names (the m0-m3 variants queue a map / stage change request: the stage name is copied to
    // _8 and the flags / position / second name describe the request)
    virtual bool m0(const sead::SafeString& name);
    virtual bool m1(const sead::SafeString& name, bool flag);
    virtual bool m2(const sead::SafeString& name, const sead::Vector3f& pos);
    virtual bool m3(const sead::SafeString& name, const sead::SafeString& name2);
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
    // 0x71007aefac: source namespace and static spelling follow the CSV owner and callers.
    static void resetStage(s32 mode, bool flag);

    /// Get the current map type (e.g. MainFieldDungeon)
    static const sead::SafeString& getCurrentMapType();

    /// Get the current map name (e.g. RemainsWind, FinalTrial, ...)
    static const sead::SafeString& getCurrentMapName();

    void setFadeType(s32 type);
    bool hasStageBinder() const;
    void setStageBinder(StageBinder* binder);

    // 0x71007b5340 / 0x71007b5350: getters of the static flags below.
    static bool getIsInitialisingStage();
    // 0x71007b5350: static bool at 0x71025cb530.
    static bool getIsFirstLaunch();
    // 0x71007b7d78: `sInstance->sub_71007B4B50()`.
    static void sub_71007B7D78();
    // 0x71007b4b50 (declaration only).
    void sub_71007B4B50();
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
    /* 0x008 */ sead::FixedSafeString<0xff> _8;
    /* 0x120 */ bool _120;
    /* 0x121 */ bool _121;
    u8 _122[0x124 - 0x122];
    /* 0x124 */ sead::Vector3f _124;
    /* 0x130 */ sead::FixedSafeString<0x3f> _130;
    u8 _188[0x279 - 0x188];
    u8 _279;
    u8 _27a[0x2a8 - 0x27a];
    StageBinder* _2a8;
    u8 _2b0[0x320 - 0x2b0];
    /* 0x320 */ GameScene320 _320;
    u8 _348[0x93c - 0x348];
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
