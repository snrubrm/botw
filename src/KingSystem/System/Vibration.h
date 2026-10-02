#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// Name from the CSV (Vibration::createInstance 0x71010baeb4, ctor 0x71010baf3c, calc, __auto0-3):
// controller rumble. Instance 0x710261f558.
// TODO: incomplete (ctor, dtor, calc, the message handler and the rumble pattern / player types are
// not decompiled; only the members used by the decompiled functions are declared).
class Vibration {
    SEAD_SINGLETON_DISPOSER(Vibration)
    Vibration();
    virtual ~Vibration();

public:
    // A rumble request (built on the stack by the callers). Copied into Unk3 as a base subobject.
    struct Unk1 {
        // 0x71010bc444
        Unk1(s32 a1, const sead::Vector3f& a2, u8 a3, void* a4, f32 a5, f32 a6, u8 a7);
        Unk1() = default;

        bool isValid() const {
            if (_18 == 0.0f)
                return false;
            if (!(_25 & 4) && _1c <= 0.0f)
                return false;
            if ((_25 & 1) && _24 == 0)
                return false;
            return _20 <= 7;
        }

        sead::Vector3f _0;
        void* _10;
        f32 _18;  // must be non-zero
        f32 _1c;  // must be positive unless bit 2 of _25 is set
        s32 _20;  // 0-7
        u8 _24;   // must be non-zero if bit 0 of _25 is set
        u8 _25;   // flags
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x28);

    // A rumble request with a direction (CameraRumble; read by sub_71010BB468).
    struct Unk2 : Unk1 {
        // 0x71010bc3b8
        Unk2();
        // 0x71010bc408
        Unk2(s32 a1, const sead::Vector3f& a2, u8 a3, void* a4, f32 a5, f32 a6,
             const sead::Vector3f& a7, u8 a8);

        bool isValid() const {
            if (_28.x == 0.0f && _28.y == 0.0f && _28.z == 0.0f)
                return false;
            return Unk1::isValid();
        }

        sead::Vector3f _28;  // must be non-zero
    };
    KSYS_CHECK_SIZE_NX150(Unk2, 0x38);

    // A playing rumble (12 per Vibration: 3 banks of 4, one bank per core). Free while _20 >= 8.
    struct Unk3 : Unk1 {
        bool isFree() const { return _20 >= 8; }

        // 0x71010bc19c
        void sub_71010BC19C(const Unk2& request, s32 a2);
        // Inline only (in sub_71010BB5E0); placeholder name.
        void x(const Unk1& request, s32 a2) {
            if (!request.isValid())
                return;
            static_cast<Unk1&>(*this) = request;
            _28 = sead::Matrix33f::ident;
            _4c = 1;
            _50 = a2;
        }

        sead::Matrix33f _28;
        s32 _4c;
        s32 _50;
        u8 _54[0x58 - 0x54];
    };
    KSYS_CHECK_SIZE_NX150(Unk3, 0x58);

    struct Unk4 {
        u8 _0[0x48];
        f32 _48;  // damping (sub_71010BB82C)
        u8 _4c[0x4e - 0x4c];
        u8 _4e;  // 8 = stopped
        u8 _4f;
    };
    KSYS_CHECK_SIZE_NX150(Unk4, 0x50);

    struct Unk5 {
        u8 _0[0x40];
        void* _40;
        u8 _48[0x50 - 0x48];
    };
    KSYS_CHECK_SIZE_NX150(Unk5, 0x50);

    // 0x71010bb36c (CSV __auto0): stops everything.
    void sub_71010BB36C();
    // 0x71010bb428 (CSV __auto2): sub_71010BB468(request, false) unless an event says otherwise.
    void sub_71010BB428(const Unk2& request);
    void sub_71010BB468(const Unk2& request, s32 a2);
    void sub_71010BB5E0(const Unk1& request, s32 a2);
    void sub_71010BB800(const Unk2& request);
    void sub_71010BB808(const Unk1& request);
    // 0x71010bb810: stops slot `idx` (0-3).
    void sub_71010BB810(s32 idx);
    // 0x71010bb82c (CSV __auto1): sets the damping of slot `idx`.
    void sub_71010BB82C(s32 idx, f32 damping);
    void sub_71010BB85C(void* ptr);

    /* 0x028 */ sead::SafeArray<Unk5, 8> _28;
    /* 0x2a8 */ sead::SafeArray<sead::SafeArray<Unk3, 4>, 3> _2a8;
    /* 0x6c8 */ sead::SafeArray<Unk4, 4> _6c8;
    /* 0x808 */ sead::Vector3f _808;
    /* 0x814 */ u32 _814;
    /* 0x818 */ void* _818;
    /* 0x820 */ u8 _820[0x8c0 - 0x820];
};
KSYS_CHECK_SIZE_NX150(Vibration, 0x8c0);

}  // namespace ksys
