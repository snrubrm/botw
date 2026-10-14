#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class WeaponRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponRootAI, ksys::act::ai::Ai)
public:
    explicit WeaponRootAI(const InitArg& arg);
    ~WeaponRootAI() override;
    bool isChangeable() const override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual bool m41();
    virtual bool m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();

    // 0x7100e21228 (declaration only; called by MasterSwordRoot::enter_).
    void sub_7100E21228();

protected:
    // 0x7100e1f34c: weapon: if m196() continue with sub_7100E21228, else reset the state byte _920
    void sub_7100E1F34C();
    // 0x7100e1ee94: sets the motion type of the "Body" rigid body
    void sub_7100E1EE94(ksys::phys::MotionType type);
    // 0x7100e21100: true if nothing blocks the ray from the actor to 1.5 times the way to the main body's center of mass
    bool sub_7100E21100();
    // 0x7100e20db4: the weapon sticks into something: attack clients off, bodies removed from the world, "ChangeColor", then the "刺さる" child
    void sub_7100E20DB4();
    // 0x7100e1f710: fixes the weapon in place: the body becomes Fixed, ground contact layers on, "ChangeColor", then the "Fixed配置" child
    void sub_7100E1F710();
    // 0x7100e1ed2c: unequips the weapon: resets the timers, "ChangeColor" animation, then the "非装備" child
    void sub_7100E1ED2C();
    // 0x7100e1f3fc: switches the weapon to the hanging state: "ChangeColor" animation, then the "吊るす" child
    void sub_7100E1F3FC();
    void sub_7100E1FC5C();
    void sub_7100E20C2C();

    bool _38 = false;
    bool _39 = false;
    u32 _3c = 1;
    ksys::Timer _40{0, 0};
    ksys::Timer _4c{0, 0};
    ksys::Timer _58{0, 0};
    ksys::Timer _64{0, 0};
    ksys::Timer _70{0, 0};
    // static_param at offset 0x80
    const float* mBlinkFrame_s{};
    // static_param at offset 0x88
    const float* mFallOutSpeed_s{};
    // static_param at offset 0x90
    const float* mLandNoiseLevel_s{};
    // map_unit_param at offset 0x98
    const bool* mIsFixedPlace_m{};
    // map_unit_param at offset 0xa0
    const bool* mIsEmitLandNoise_m{};
    bool _a8 = false;
    bool _a9 = false;
    bool _aa = false;
    bool _ab = false;
    bool _ac = false;
    f32 _b0 = 0;  // max angular velocity
    u8 _b4[0xc4 - 0xb4]{};
    bool _c4 = false;
    bool _c5 = true;
    Unk_71012419b4 _c8;
};
KSYS_CHECK_SIZE_NX150(WeaponRootAI, 0xe8);

}  // namespace uking::ai
