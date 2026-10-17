#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldDefines.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

constexpr u32 NumWeatherCycles = 3;

// This may be incorrect
struct ClimateWeathers {
    s32 weather[NumWeatherCycles];
};

// TODO
class WeatherMgr : public Job {
    SEAD_RTTI_OVERRIDE(WeatherMgr, Job)
public:
    WeatherMgr();
    ~WeatherMgr() override;

    JobType getType() const override { return JobType::Weather; }

    void reset();
    void onUnload();
    void rerollClimateWindPowers();

    static bool isExposureZero();
    void loadInfo();
    WeatherType rollNewWeather(Climate climate);
    bool x_0();
    // 0x71010eb4bc (CSV wm::WeatherMgr::calcNewWeathers): shifts every climate's weather table by one cycle and
    // rolls the six new entries (not in the test stage).
    void calcNewWeathers();
    WeatherType getWeather() const;

    // UI weather setup/frame callbacks pass the WeatherMgr receiver and use a float result.
    float getTime() const;
    u8 x_6(int idx) const;
    bool x_8() const;
    static bool x_7();
    // 0x71010edccc: emits Far_Lightning on the reaction actor 2000 units in front of the camera (random yaw
    // offset in [-0.65, 0.65]), at the camera height.
    static void x_10();
    void setWeatherEffect(int effect);
    void x_16();
    void x_17();
    WeatherType x_1(int climate) const;
    WeatherType x_2(int climate) const;
    WeatherType x_3(int climate) const;
    WeatherType x_4(int climate) const;
    WeatherType x_5(int climate) const;
    WeatherType x_18(int climate) const;
    // 10ED7B8 receives the lightning position; D9C0CC passes a Vector3f temporary.
    void x_12(const sead::Vector3f& position);
    void x_11(const sead::Vector3f& position);
    void x_13();
    void x_14();
    void sub_71010EDEBC(int value);
    f32 sub_71010ED5B4(const sead::Vector3f& position);
    int x() const;
    bool isRaining();
    bool isSnowing();

protected:
    void init_(sead::Heap* heap) override;
    void calcType2_() override;

public:

    u8 _20[0x24 - 0x20];
    float _24;
    // Unsure of the type / variable
    u8 weather;
    u8 _29;
    sead::SafeArray<sead::SafeArray<WeatherType, NumWeatherCycles * 6>, NumClimates> _2a;
    u8 _193;
    ClimateWeathers mClimateWeathers[NumClimates];  // 0x194
    sead::SafeArray<u8, 6> _284;
    u8 _28a[0x2ac - 0x28a];
    // Constructor sets (0, 1, 0); x_12 and x_9 write the camera-facing direction.
    sead::Vector3f _2ac;
    u8 _2b8[0x2d0 - 0x2b8];
    float _2d0;  // Puddle::enter_: 1 - _2d0 is subtracted from the home matrix height
    u8 _2d4[0x2d8 - 0x2d4];
    float _2d8;  // Puddle::calc_
    float _2dc;
    u8 _2e0[4];
    // calcType2_ interpolates these float values; the rainbow checks them for zero.
    f32 _2e4;
    f32 _2e8;
    f32 _2ec;
    f32 _2f0;
    f32 _2f4;
    f32 _2f8;
    f32 _2fc;
    u8 _300[0x314 - 0x300];
    int _314;
    float mTimeBlock;  // 0x318
    u32 mWeekDay;      // 0x31c
    int _320;
    int _324;
    int _328;
    u8 _32c[0x334 - 0x32c];
    int _334;
    int _338;
    int _33c;
    int _340;
    int _344;
    int _348;
    int _34c;
    int _350;
    u8 _354[0x36c - 0x354];
    int _36c;
    int _370;
    int _374;
    u8 _378[0x380 - 0x378];
    int _380;
    u8 _384[0x390 - 0x384];
    bool _390;
    bool _391;
    u8 _392[0x398 - 0x392];
};
KSYS_CHECK_SIZE_NX150(WeatherMgr, 0x398);
static_assert(offsetof(WeatherMgr, _2e4) == 0x2e4);
static_assert(offsetof(WeatherMgr, _2fc) == 0x2fc);

// 0x71010eb430 (CSV wm::isGetPlayerStole2): the TimeMgr's "plateau done" flag.
bool isGetPlayerStole2();

}  // namespace ksys::world

namespace wm {
ksys::world::WeatherMgr* getWeatherMgr();
}
