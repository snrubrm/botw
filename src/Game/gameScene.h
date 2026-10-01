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

}  // namespace uking
