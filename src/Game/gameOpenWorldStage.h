#pragma once

#include "Game/gameOpenWorldStageMessage.h"
#include "Game/gameScene.h"
#include "Game/gameStageBinder.h"
#include "KingSystem/System/DebugBoard.h"
#include "KingSystem/Map/mapMapProperties.h"

namespace ksys {
class Unk_71024dd110;
}

namespace ksys::act {
class Actor;
}

namespace uking {

// Vtable 0x710245b2c8: MapProperties at 0, Stage at 8. StageFactory allocates 0x310 bytes.
// The constructor and unresolved lifecycle routines remain declaration-only.
class OpenWorldStage : public ksys::map::MapProperties, public Stage {
    SEAD_RTTI_OVERRIDE(OpenWorldStage, Stage)
public:
    OpenWorldStage();
    ~OpenWorldStage() override;

    s32 getType() override;
    bool init(StageArg* arg) override;
    void postInit(Unk_710245ac20* a, Unk_710245abf0* b) override;
    void preCalc() override;
    void calc() override;
    void postCalc() override;
    void unload() override;
    bool unloadOk() override;
    void initForStageGen() override;
    void m13() override;

    virtual bool ret0(void* arg);
    virtual void m27_null(void* arg);
    virtual void fieldEnter();
    virtual void fieldRun();
    virtual void fieldLeave();
    virtual bool fieldReenter(void* arg);

    int m0() override { return 0; }
    void getMapType(sead::BufferedSafeString* out) override;
    bool m2(sead::BufferedSafeString* out) override;
    bool getMapName(sead::BufferedSafeString* out, int col, int row) override;
    void m4(int* col, int* row, const sead::SafeString& name) override;

private:
    /* 0x10 */ Unk_710245b4f8 mTransceiver;
    u8 _d8[0xe0 - 0xd8];
    /* 0xe0 */ ksys::act::Actor* mPlayer;
    /* 0xe8 */ GameScene::sb mDrawMethods;
    u8 _110[0x1a0 - 0x110];
    /* 0x1a0 */ sead::FixedSafeString<32> mMapType;
    /* 0x1d8 */ ksys::Unk_71024dd110* mCamera;
    /* 0x1e0 */ u8 _1e0;
    u8 _1e1[0x300 - 0x1e1];
    /* 0x300 */ Unk_710246c458 _300;
};
static_assert(sizeof(OpenWorldStage) == 0x310);

}  // namespace uking
