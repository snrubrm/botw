#pragma once

#include <container/seadSafeArray.h>
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
    WeatherType getWeather() const;

    u8 x_6(int idx) const;
    bool x_8() const;
    static bool x_7();
    void setWeatherEffect(int effect);
    void x_16();
    void x_17();
    WeatherType x_1(int climate) const;
    WeatherType x_2(int climate) const;
    WeatherType x_3(int climate) const;
    WeatherType x_4(int climate) const;
    WeatherType x_5(int climate) const;
    WeatherType x_18(int climate) const;
    void x_13();
    void x_14();
    void sub_71010EDEBC(int value);
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
    u8 _28a[0x2d0 - 0x28a];
    float _2d0;  // Puddle::enter_: 1 - _2d0 is subtracted from the home matrix height
    u8 _2d4[0x2d8 - 0x2d4];
    float _2d8;  // Puddle::calc_
    float _2dc;
    u8 _2e0[0x314 - 0x2e0];
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

// 0x71010eb430 (CSV wm::isGetPlayerStole2): the TimeMgr's "plateau done" flag.
bool isGetPlayerStole2();

}  // namespace ksys::world

namespace wm {
ksys::world::WeatherMgr* getWeatherMgr();
}
