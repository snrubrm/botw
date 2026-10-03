#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>

namespace uking::act {

// Horse animation state names (placeholder names = address; the real names are unknown). Defined in
// actHorseStrings.cpp in address order; initialised by the static initializer 0x7100e71764.
extern sead::SafeString sUnk_7102603110;  // "Wait"
extern sead::SafeString sUnk_7102603120;  // "Wait_Curve_L"
extern sead::SafeString sUnk_7102603130;  // "Wait_Curve_R"
extern sead::SafeString sUnk_7102603140;  // "TurnBack"
extern sead::SafeString sUnk_7102603150;  // "Move_Back"
extern sead::SafeString sUnk_7102603160;  // "Move_Shift"
extern sead::SafeString sUnk_7102603170;  // "Move_Shift_Brake"
extern sead::SafeString sUnk_7102603180;  // "Courbette"
extern sead::SafeString sUnk_7102603190;  // "Courbette_For_Rodeo"
extern sead::SafeString sUnk_71026031a0;  // "Crying"
extern sead::SafeString sUnk_71026031b0;  // "Crash"
extern sead::SafeString sUnk_71026031c0;  // "Surprised"
extern sead::SafeString sUnk_71026031d0;  // "Rodeo"
extern sead::SafeString sUnk_71026031e0;  // "Fall"
extern sead::SafeString sUnk_71026031f0;  // "FallDown"
extern sead::SafeString sUnk_7102603200;  // "Dislike"
extern sead::SafeString sUnk_7102603210;  // "Dislike_For_Charge"
extern sead::SafeString sUnk_7102603220;  // "Damage"
extern sead::SafeString sUnk_7102603230;  // "Wait_Search"
extern sead::SafeString sUnk_7102603240;  // "AttackFront"
extern sead::SafeString sUnk_7102603250;  // "KickBack"
extern sead::SafeString sUnk_7102603260;  // "KickBackWait"
extern sead::SafeString sUnk_7102603270;  // "Slip"
extern sead::SafeString sUnk_7102603280;  // "SlipPost"
extern sead::SafeString sUnk_7102603290;  // "Sprain_Gear1"
extern sead::SafeString sUnk_71026032a0;  // "Dead"
extern sead::SafeString sUnk_71026032b0;  // "Drown"
extern sead::SafeString sUnk_71026032c0;  // "Swim"
extern sead::SafeString sUnk_71026032d0;  // "Eat"
extern sead::SafeString sUnk_71026032e0;  // "Eat_High"
extern sead::SafeString sUnk_71026032f0;  // "Shake"
extern sead::SafeString sUnk_7102603300;  // "GotOff_From_Wild"
extern sead::SafeString sUnk_7102603310;  // "Hit_BottomArea"
extern sead::SafeString sUnk_7102603320;  // "Stagger"
extern sead::SafeString sUnk_7102603330;  // "Appear_Epona"
extern sead::SafeString sUnk_7102603340;  // "Before_Event"
extern sead::SafeString sUnk_7102603350;  // "Wait_Light"
extern sead::SafeString sUnk_7102603360;  // "Warp_In"
extern sead::SafeArray<sead::SafeString, 5> sUnk_7102603370;  // "", "", "", "Jump_Gear3_S", "Jump_Gear4_S"
extern sead::SafeArray<sead::SafeString, 5> sUnk_71026033c0;  // "", "", "", "Jump_Gear3", "Jump_Gear4"
extern sead::SafeArray<sead::SafeString, 3> sUnk_7102603410;  // "Collar_Shader", "Collar_Shader_Coward", "Collar_Shader_Impatient"
extern sead::SafeArray<sead::SafeString, 3> sUnk_7102603440;  // "Collar", "Collar_Coward", "Collar_Impatient"
extern sead::SafeString sUnk_7102603470;  // "Collar_Shader_ZeldaHorse"
extern sead::SafeString sUnk_7102603480;  // "Collar_ZeldaHorse"
extern sead::SafeString sUnk_7102603490;  // "Collar_Shader_EponaHorse"
extern sead::SafeString sUnk_71026034a0;  // "Collar_EponaHorse"
extern sead::SafeString sUnk_71026034b0;  // "Collar_Animal"

}  // namespace uking::act
