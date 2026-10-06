#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include "Game/gameScene320.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/StateMachine.h"
#include "KingSystem/Utils/Thread/Event.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class Resource;
}

namespace uking {

class OpenWorldStageBinder;
class StageBinder;

// 0x71025cb350 (a state object of the GameScene TU; only its id is read by GameScene::sub_71007B0D3C).
extern ksys::StateBase sUnk_71025cb350;

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

    // 0x71007b1c64 (placeholder name; called by genStage / doGenStageStep6): stores the stage-gen save position, its angle
    // and the current map type / name in the PlayerSavePos flags (unless this is a debug or dev map or the save system is
    // in one of the states 10-13).
    static void sub_71007B1C64();
    // 0x71007aef94 (placeholder name; RestartStageFromGameOver::enter_): `resetStage(SaveSystem::instance()->_30, true)`.
    static void sub_71007AEF94();

    /// Get the current map type (e.g. MainFieldDungeon)
    static const sead::SafeString& getCurrentMapType();

    /// Get the current map name (e.g. RemainsWind, FinalTrial, ...)
    static const sead::SafeString& getCurrentMapName();

    // 0x71007b0d88 (CSV GameScene::commonRun, declared only): shared body of the Run states.
    void commonRun(bool a1, bool a2);

    void setFadeType(s32 type);
    bool hasStageBinder() const;
    // 0x71007aef00 (CSV GameScene::getEnvArchive): the resource of the handle at 0x2c0 (DynamicCast to res::Resource).
    ksys::res::Resource* getEnvArchive() const;
    // 0x71007ba238 (CSV GameScene::createOpenWorldStageBinder): a new binder on the heap at 0x288 (null without heap).
    OpenWorldStageBinder* createOpenWorldStageBinder();
    void setStageBinder(StageBinder* binder);

    // 0x71007b5340 / 0x71007b5350: getters of the static flags below.
    static bool getIsInitialisingStage();
    // 0x71007b5350: static bool at 0x71025cb530.
    static bool getIsFirstLaunch();
    // 0x71007b7d78: `sInstance->sub_71007B4B50()`.
    static void sub_71007B7D78();
    // 0x71007b4b50: resets the small keys / reset position, clears the scene binder.
    void sub_71007B4B50();
    // 0x71007b4bb0 / 0x71007b4bbc (placeholder names from the free-function thunks 0x71007b7e14 / 0x71007b7e24).
    void setNeedStageGenFinalStepInPreCalc();
    bool isNotNeedStageGenFinalStepInPreCalc() const;
    // 0x71007b4bcc / 0x71007b4be4 / 0x71007b4c00 (placeholder names): atomic bit 0 of `_944` (set / clear + signal
    // `_950`) and bit 1 of `_948`.
    void sub_71007B4BCC();
    void sub_71007B4BE4();
    bool sub_71007B4C00() const;
    // 0x71007b4c28 (declared only; placeholder name): called by the appear-game-over thunk.
    void sub_71007B4C28();
    // 0x71007b0d3c (declared only): the current state of the state machine at 0x1d0 has the id of a global state.
    bool sub_71007B0D3C() const;
    // 0x71007b8db4 (placeholder name): `sInstance3->_8c9 = true`.
    static void sub_71007B8DB4();
    // 0x71007bea6c (CSV name; the namespace is a guess)
    static bool hasLoadingScreenStarted();
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

    friend void createTitleStageBinder(bool a1, bool a2);

private:
    static bool sIsOpenWorldDemo;

    // TODO
    /* 0x008 */ sead::FixedSafeString<0xff> _8;
    /* 0x120 */ bool _120;
    /* 0x121 */ bool _121;
    u8 _122[0x124 - 0x122];
    /* 0x124 */ sead::Vector3f _124;
    /* 0x130 */ sead::FixedSafeString<0x3f> _130;
    u8 _188[0x1d0 - 0x188];
    /* 0x1d0 */ ksys::StateMachine _1d0;
    u8 _1f8[0x279 - 0x1f8];
    u8 _279;
    u8 _27a[0x288 - 0x27a];
    /* 0x288 */ sead::Heap* _288;
    u8 _290[0x2a8 - 0x290];
    StageBinder* _2a8;
    u8 _2b0[0x2c0 - 0x2b0];
    /* 0x2c0 */ ksys::res::Handle _2c0;  // the env archive
    u8 _310[0x320 - 0x310];
    /* 0x320 */ GameScene320 _320;
    u8 _348[0x6e6 - 0x348];
    /* 0x6e6 */ bool _6e6;
    u8 _6e7[0x6e9 - 0x6e7];
    /* 0x6e9 */ bool _6e9;
    u8 _6ea[0x8c9 - 0x6ea];
    /* 0x8c9 */ bool _8c9;
    /* 0x8ca */ bool _8ca;
    /* 0x8cb */ bool _8cb;
    u8 _8cc[0x93c - 0x8cc];
    s32 _93c;
    u8 _940[0x944 - 0x940];
    /* 0x944 */ sead::Atomic<u32> _944;
    /* 0x948 */ sead::Atomic<u32> _948;
    u8 _94c[0x950 - 0x94c];
    /* 0x950 */ ksys::util::Event _950;
};

// Free functions of the GameScene TU (CSV names; the namespace is a guess).
// 0x71007b8bec (declared only): creates the title stage binder.
void createTitleStageBinder(bool a1, bool a2);
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
// 0x71007b7998 / 0x71007b7da4 / 0x71007b7e14..: thunks that call a member of
// GameScene::sInstance2 / sInstance3 (defined in gameStage.cpp: the originals do not inline the members).
bool gameSceneHasStageBinder();
void gameSceneSetNeedStageGenFinalStepInPreCalc();
bool gameSceneIsNotNeedStageGenFinalStepInPreCalc();
void gameSceneSetFadeType(s32 type);
// 0x71007beb20 (CSV appearGameOver_; placeholder name): `sInstance3->sub_71007B4C28()`.
void sub_71007BEB20();
void sub_71007B7E4C();
void sub_71007B7E5C();
bool sub_71007B7E6C();
// 0x71007bea94: restores the player's life and stamina to the maximum.
void recoverLifeAndStamina();
// 0x71007a8818 (CSV name): sets the byte at 0x71025cb0eb.
void setForceEnableGlidingSurfingRupee(bool value);

}  // namespace uking

// 0x71007b7da4 (CSV name; global namespace: E3Mgr declares it that way): `sInstance2->sub_71007B0D3C()`.
bool isStageSelectState();
