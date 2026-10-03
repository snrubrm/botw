#include "Game/UI/uiUnkSingletons.h"
#include <prim/seadSafeString.h>
#include "Game/UI/uiUtils.h"

// UI wrapper functions around unidentified UI singletons (the 0x7100a94000 TU).
namespace uking::ui {

// Free helpers called by the wrappers below (placeholder names, declared only).
void sub_71009F8420(s32 a1);
void sub_71009D3FB0(s32 a1, s32 a2, const sead::SafeString* name);
void sub_71009E7CE8(s32 a1);
void sub_71009FD6C0();
bool sub_71009F8450();
bool sub_71009D3E0C();
bool sub_71009E2E94();

// 0x7100a94af0
void sub_7100A94AF0() {
    if (auto* s = Unk_71025d6578::instance())
        s->_3c = 0;
}

// 0x7100a94ac8
bool sub_7100A94AC8() {
    if (auto* s = Unk_71025d6578::instance())
        return s->_3c != 13;
    return false;
}

// 0x7100a94b08
void sub_7100A94B08() {
    if (auto* s = Unk_71025d6578::instance())
        s->_3c = 2;
}

// 0x7100a94b24
void sub_7100A94B24() {
    if (auto* s = Unk_71025d6578::instance())
        s->_3c = 3;
}

// 0x7100a94b40
void sub_7100A94B40(bool a0, bool a1, bool a2) {
    if (auto* s = Unk_71025d6578::instance())
        s->sub_710094B844(a0, a1, a2);
}

// 0x7100a94b70
void sub_7100A94B70(bool a0) {
    if (auto* s = Unk_71025d6578::instance())
        s->sub_710094B8A4(a0);
}

// 0x7100a94b90
void sub_7100A94B90() {
    if (auto* s = Unk_71025d6578::instance())
        s->_49 = 1;
}

// 0x7100a9b584
void sub_7100A9B584(const sead::Vector3f* a0) {
    if (auto* s = Unk_71025d6550::instance())
        s->_80 = *a0;
}

// 0x7100a9d0b4
void sub_7100A9D0B4(const void* a0) {
    if (auto* s = Unk_71025d6550::instance())
        s->sub_7100948CC4(a0);
}

// 0x7100a9d0d4
void sub_7100A9D0D4(const void* a0) {
    if (auto* s = Unk_71025d6550::instance())
        s->sub_71009489C0(a0);
}

// 0x7100a9d0f4
bool sub_7100A9D0F4() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b64 < 0;
    return false;
}

// 0x7100a9d118
bool sub_7100A9D118() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b64 > 0;
    return false;
}

// 0x7100a9d140
bool sub_7100A9D140() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b64 == 0;
    return false;
}

// 0x7100a9d168
void sub_7100A9D168(f32 a0, f32 a1, f32 a2) {
    f32 values[10];
    values[0] = a0;
    values[1] = a1;
    values[2] = a2;
    if (auto* s = Unk_71025d6550::instance())
        s->sub_7100948F0C(values);
}

// 0x7100a9d1a0
void sub_7100A9D1A0(const f32* a0) {
    if (auto* s = Unk_71025d6550::instance())
        s->sub_7100948F0C(a0);
}

// 0x7100a9d1c0
bool sub_7100A9D1C0() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b6c == 0;
    return false;
}

// 0x7100a9d1e8
bool sub_7100A9D1E8() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b6c == 1;
    return false;
}

// 0x7100a9d210
void sub_7100A9D210(f32 a0, f32 a1) {
    f32 values[10];
    values[0] = a0;
    values[1] = a1;
    if (auto* s = Unk_71025d6550::instance())
        s->sub_7100948F0C(values);
}

// 0x7100a9d290
s32 sub_7100A9D290() {
    if (auto* s = Unk_71025d6550::instance())
        return s->_b74;
    return 0;
}

// 0x7100a9d2b0
void sub_7100A9D2B0(const void* a0) {
    if (auto* s = Unk_71025d6550::instance())
        s->sub_7100948E44(a0);
}

// 0x7100a9d308
bool sub_7100A9D308(s32 idx) {
    if (auto* s = Unk_71025d6550::instance())
        return s->_d54[idx - 24] == 0;
    return false;
}

// 0x7100a9d344
bool sub_7100A9D344(s32 idx) {
    if (auto* s = Unk_71025d6550::instance())
        return s->_d54[idx - 24] == 3;
    return false;
}

// 0x7100a9d380
bool sub_7100A9D380(s32 idx) {
    if (auto* s = Unk_71025d6550::instance())
        return s->_d54[idx - 24] == 2;
    return false;
}

// 0x7100a9d3bc
bool sub_7100A9D3BC(s32 idx) {
    if (auto* s = Unk_71025d6550::instance())
        return s->_d54[idx - 24] == 1;
    return false;
}

// 0x7100a9d748
void sub_7100A9D748() {
    if (auto* s = Unk_71025d6550::instance())
        s->sub_71009482FC();
}

// 0x7100a9ebec
bool sub_7100A9EBEC() {
    if (auto* s = Unk_71025d69f0::instance())
        return s->sub_710094E920();
    return false;
}

// 0x7100a9f038
void sub_7100A9F038() {
    Unk_71025d69f0::instance()->sub_710094E0A0();
}

// 0x7100a9f000
void sellPictureBookUIEnd() {
    sub_71009F8420(2);
    Unk_71025d69f0::instance()->sub_710094D9F4(3, 1, 0, 0);
}

// 0x7100a9f08c
void sub_7100A9F08C(const sead::SafeString& name) {
    sub_71009D3FB0(3, -1, &name);
    Unk_71025d69f0::instance()->sub_710094D9F4(2, 1, 0, 0);
}

// 0x7100a9f108
void sub_7100A9F108() {
    sub_71009F8420(1);
    Unk_71025d69f0::instance()->sub_710094DCC4(3, 0);
}

// 0x7100a9f46c
void sub_7100A9F46C(bool a0) {
    sub_71009E7CE8(0);
    Unk_71025d69f0::instance()->sub_710094D9F4(1, 1, 0, a0);
}

// 0x7100a9bfa8 (CSV return0)
bool return0() {
    return false;
}

// 0x7100a9ed74
void sub_7100A9ED74() {
    sub_71009FD6C0();
}

// 0x7100a9f034
void sellPictureBookUIEnd2() {
    sub_71009F8450();
}

// 0x7100a9f104
bool sub_7100A9F104() {
    return sub_71009D3E0C();
}

// 0x7100a9f134
bool sub_7100A9F134() {
    return sub_71009F8450();
}

// 0x7100a9f4ac
bool sub_7100A9F4AC() {
    return !sub_71009E2E94();
}

// Empty functions of the TU (CSV nullsub_NNNN).
// 0x7100a9b1b0
void sub_7100A9B1B0() {}
// 0x7100a9b1b4
void sub_7100A9B1B4() {}
// 0x7100a9b1b8
void sub_7100A9B1B8() {}
// 0x7100a9f528
void sub_7100A9F528() {}
// 0x7100a9fd7c
void sub_7100A9FD7C() {}
// 0x7100a9fd80
void sub_7100A9FD80() {}
// 0x7100a9fd84
void sub_7100A9FD84() {}
// 0x7100a9fd88
void sub_7100A9FD88() {}
// 0x7100a9fd8c
void sub_7100A9FD8C() {}
// 0x7100a9fd90
void sub_7100A9FD90() {}

}  // namespace uking::ui
