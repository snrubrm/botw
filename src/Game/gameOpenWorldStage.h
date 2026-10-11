#pragma once

#include "Game/gameStageBinder.h"
#include "KingSystem/Map/mapMapProperties.h"

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
    u8 _10[0xe0 - 0x10];
    /* 0xe0 */ ksys::act::Actor* mPlayer;
    u8 _e8[0x1a0 - 0xe8];
    /* 0x1a0 */ sead::FixedSafeString<32> mMapType;
    u8 _1d8[0x310 - 0x1d8];
};
static_assert(sizeof(OpenWorldStage) == 0x310);

}  // namespace uking
