#pragma once

#include <math/seadVector.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

class ShootingStarMgr : public Job {
    SEAD_RTTI_OVERRIDE(ShootingStarMgr, Job)
public:
    ShootingStarMgr();
    ~ShootingStarMgr() override;

    JobType getType() const override { return JobType::ShootingStar; }

    void init_(sead::Heap* heap) override;
    void calc_() override;
    virtual void spawnStar();

    static void setScheduled(bool enable);
    // 0x71010dce38 (placeholder name; called by ShootingStartFlying::calc_): `sStarProperty`. (0x71010dce2c, the getter of
    // the byte at 0x71026200e8 right before it, needs that file-local flag's writer.)
    static const sead::Vector3f& getStarProperty();
    void initSchedule();
    static bool isScheduledTime();

    bool tryGetStarPosition(sead::Vector3f* out) const;
    static void setStarPosition(f32 x, f32 y, f32 z);
    static void spawnShootingStar();

    static bool checkCamera();
    bool isStarPositionValid();
    static void setShootingStarHours(int start, int end, int hr_unk);
    static void resetStarPosition();
    static void resetStarProperty();

    s32 mFallHour = 0;
    s32 mFallMinute = 0;
    bool mInitialised = false;
    bool mNeedSpawnStar = false;
    bool mIsMainField = false;
    bool _2b = false;
};
KSYS_CHECK_SIZE_NX150(ShootingStarMgr, 0x30);

}  // namespace ksys::world
