#pragma once

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

// TODO
class TempMgr : public Job {
    SEAD_RTTI_OVERRIDE(TempMgr, Job)
public:
    TempMgr();
    ~TempMgr() override;

    JobType getType() const override { return JobType::Temp; }

    void reset();
    void setInstantTemperature();
    void x();

    // Lane2 request (s49): the temperatures set by calc1() (`_3c`: `_20` after the clamp offset; `_40`: `_44`).
    // Placeholder names (address-named like the members).
    f32 get_3c() const { return _3c; }
    f32 get_40() const { return _40; }

protected:
    void init_(sead::Heap* heap) override;
    void calc_() override;
    void calcType2_() override;

    f32 calcTemperature();

private:
    f32 sub_71010E58C0();
    void calc2();
    void calc1();
    f32 sub_71010E5F00() const;

    friend class WeatherMgr;

    f32 _20;
    VFRValue _24;
    f32 _30;
    f32 _34;
    f32 _38;
    f32 _3c;
    f32 _40;
    f32 _44;
    VFRValue _48;
    f32 _54;
    f32 _58;
    f32 _5c;
    f32 _60;
    s32 _64;
    s32 _68;
    s32 _6c;
    f32 _70;
    f32 _74;
    f32 _78;
    s32 _7c;
    f32 _80;
    f32 _84;
    f32 _88;
};
KSYS_CHECK_SIZE_NX150(TempMgr, 0x90);

}  // namespace ksys::world
