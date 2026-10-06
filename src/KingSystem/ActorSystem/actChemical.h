#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/Chemical/chmSystemConfig.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// Placeholder (lane1 s22): the object Chemical::_90 points to; only these two fields are read (ChmCheck).
struct Unk_ChemicalData {
    /* 0x00 */ u8 _0[0x12];
    /* 0x12 */ u8 _12;
    /* 0x13 */ u8 _13[0x7c - 0x13];
    /* 0x7c */ f32 _7c;
};

// The object returned by Actor::getChemicalStuff() (Actor vtable slot 97): the chemistry state of
// one actor element. Name from the existing forward declaration in actActor.h (placeholder).
// ctor 0x7100d8e5ec, D1 0x7100d8e7c4, D0 0x7100d8e9b8, vtable 0x71024dd1e8 (getNodeClassType, D1,
// D0). ActorChemicals (Actor::mChemical) holds an array of 0x2d8-byte elements whose second base
// (at +0x40) is this class.
// TODO: incomplete. Members are public: AI and actor code read them directly.
class Chemical : public sead::hostio::Node {
public:
    Chemical();
    virtual ~Chemical();

    void sub_7100D8EAB4(int value);
    void sub_7100D8EEE0();
    // 0x7100d945bc (declaration only, lane1 s39; placeholder name): ChemicalGiantArmorRoot passes the charge
    // rate, _1b8 and the delta frame.
    void sub_7100D945BC(f32 rate, f32 value, f32 delta_frame);
    // 0x7100d8f124: associates a chemical world holder (same incomplete type as _60).
    bool sub_7100D8F124(void* holder);
    void sub_7100D8F194();
    void sub_7100D907A8();
    void sub_7100D90858(bool a1, int a2, bool a3, bool a4, bool a5);
    void sub_7100D909A4();
    void sub_7100D90A40();
    void sub_7100D90AF4(bool on);
    // 0x7100d8f550 (CSV makeChmElementMaybe, 3.7 KB; declared only; lane4 s31): the argument is a bool / 0 (placeholder type).
    void makeChmElementMaybe(bool a1);
    void sub_7100D90B78();
    void sub_7100D90C2C(bool on);
    void sub_7100D90CD8(bool on);
    void sub_7100D90D7C(bool on);
    void sub_7100D90E40(bool on);
    void sub_7100D90ED0(bool on);
    void sub_7100D90F60(bool on);
    void sub_7100D90FF0(bool on);
    bool sub_7100D91080() const;
    bool sub_7100D9108C() const;
    void sub_7100D91098(bool on);
    void sub_7100D91158(bool on);
    f32 sub_7100D911F8() const;
    void sub_7100D91390(f32 value);
    bool sub_7100D913A8() const;
    int sub_7100D914C0() const;
    bool sub_7100D91508() const;
    // 0x7100d91360: `_1c8->_1a`, or byte 0x182 while _c0 is 2, else 0.
    u8 sub_7100D91360() const;
    sead::Vector3f sub_7100D9155C() const;
    // 0x7100d9472c (CSV: gsys::ModelSceneBuffer::isDeferredShadingEnabled, a mislabeled ICF body; AI code calls it on
    // getChemicalStuff()): `_60->byte 0x198 && _60->_1b0 == this`. Declared only.
    bool sub_7100D9472C() const;
    bool sub_7100D915A8() const;
    void sub_7100D91614(const Chemical& other);
    f32 sub_7100D91958() const;
    void sub_7100D91978(f32 value);
    f32 sub_7100D91A10(int a1, int a2) const;
    f32 sub_7100D91BE4(int a1, int a2) const;
    f32 sub_7100D945AC() const;
    // 0x7100d9153c (declared only): forwards to the owner (_18) with the matrix to fill.
    void sub_7100D9153C(sead::Matrix34f* out);

    /* 0x008 */ u8 _8 = 0;
    /* 0x00c */ u32 _c = 0;  // flags
    /* 0x010 */ int _10 = 0;
    /* 0x018 */ void* _18 = nullptr;  // owner (polymorphic; vtable slots 4, 5, 22, 23, 26, 32)
    /* 0x020 */ const chm::SystemConfig::Material* mMaterial = nullptr;
    /* 0x028 */ u8 _28[0x34 - 0x28];
    /* 0x034 */ f32 _34;
    /* 0x038 */ u8 _38[0x40 - 0x38];
    /* 0x040 */ f32 _40;
    /* 0x044 */ u8 _44[0x50 - 0x44];
    /* 0x050 */ f32 _50;
    /* 0x054 */ f32 _54;
    /* 0x058 */ f32 _58;
    /* 0x060 */ void* _60 = nullptr;  // chemical world object (methods 0x7100d9cb54, 0x7100d9a1c4, ...)
    /* 0x068 */ void* _68 = nullptr;
    // object with vtables 0x71024dd218 / 0x71024dd238 (D1 0x7100d8e968) and a 0x80-byte buffer
    /* 0x070 */ u8 _70[0x90 - 0x70];
    /* 0x090 */ Unk_ChemicalData* _90 = nullptr;  // read by ChmCheck (lane1 s22)
    /* 0x098 */ const char* _98;
    /* 0x0a0 */ u8 _a0 = 1;
    /* 0x0a1 */ u8 _a1 = 0;
    /* 0x0a2 */ u8 _a2 = 0xff;
    /* 0x0a4 */ u32 _a4 = 0;
    /* 0x0a8 */ f32 _a8;
    /* 0x0ac */ f32 _ac;
    /* 0x0b0 */ f32 _b0;
    /* 0x0b4 */ u8 _b4[0xb8 - 0xb4];
    /* 0x0b8 */ u8 _b8 = 0;  // flags
    /* 0x0b9 */ u8 _b9[0xbc - 0xb9]{};
    /* 0x0bc */ u16 _bc = 0;  // flags (bit 3: Actor::m50, bit 13: SwitchWindHit::calc_)
    /* 0x0be */ u8 _be = 0;  // flags
    /* 0x0bf */ u8 _bf = 0;  // flags
    /* 0x0c0 */ u8 _c0 = 0;  // state (ActorConstDataAccess::sub_7100D131D0; callers test 1 / 2)
    /* 0x0c1 */ u8 _c1 = 0;
    /* 0x0c2 */ u8 _c2 = 0;
    /* 0x0c3 */ u8 _c3 = 0;
    /* 0x0c4 */ f32 _c4 = 1.0;
    /* 0x0c8 */ u8 _c8[0xd8 - 0xc8];
    /* 0x0d8 */ sead::Vector3f _d8;  // read by BalloonBase::m33 unless _c bit 24 is set
    /* 0x0e4 */ sead::Vector3f _e4;
    /* 0x0f0 */ u8 _f0[0x10c - 0xf0];
    /* 0x10c */ f32 _10c;  // Player::m353: > 0
    /* 0x110 */ u8 _110[0x14c - 0x110];
    /* 0x14c */ f32 _14c;  // wind force scale (behavior SetWindForceScale)
    /* 0x150 */ u8 _150[0x170 - 0x150];
    /* 0x170 */ f32 _170;
    /* 0x174 */ f32 _174;
    /* 0x178 */ f32 _178;
    /* 0x17c */ f32 _17c;
    /* 0x180 */ u8 _180;
    /* 0x181 */ u8 _181[0x182 - 0x181];
    /* 0x182 */ u8 _182 = 2;
    /* 0x184 */ f32 _184;
    /* 0x188 */ f32 _188;
    /* 0x18c */ f32 _18c;
    /* 0x190 */ f32 _190;
    /* 0x194 */ f32 _194;
    /* 0x198 */ f32 _198;
    /* 0x19c */ f32 _19c;
    /* 0x1a0 */ u8 _1a0[0x1b4 - 0x1a0];
    /* 0x1b4 */ f32 _1b4;
    /* 0x1b8 */ f32 _1b8;
    /* 0x1bc */ f32 _1bc;
    /* 0x1c0 */ u8 _1c0[0x238 - 0x1c0];
};
KSYS_CHECK_SIZE_NX150(Chemical, 0x238);

}  // namespace ksys::act
