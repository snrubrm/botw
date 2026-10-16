#pragma once

#include <container/seadListImpl.h>
#include <container/seadPtrArray.h>
#include <container/seadTList.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace agl {
class TextureData;
}
namespace sead {
class Heap;
}
namespace nn::g3d {
class ResMaterial;
}
namespace nn::gfx {
class ResTexture;
}

class Unk_710250db28;
class Unk_710250dbc8;
class Unk_710250dc50;
class Unk_710250dd60;

namespace ksys::tera {

// Placeholder name: the kind of a terrain image (type 0 - 3, and an index for type 3). The
// resources Unk_710250db28 / dbc8 / dc50 / dd60 answer their virtuals m4 - m8 through it.
// A union: Unk_710250db28 builds it as one word (3 | index << 16).
union ImageTypeMaybe {
    // 0x710114a5a0 (placeholder name)
    s32 sub_710114A5A0() const;
    // 0x710114a5a8 (placeholder name)
    s32 sub_710114A5A8() const;
    // 0x710114a5cc (placeholder name)
    s32 sub_710114A5CC() const;
    // 0x710114a62c (placeholder name): the type is not 1.
    s32 sub_710114A62C() const;
    // 0x710114a650 (declared only; 1672 B): a value cached per type, size and `a3`.
    u16 sub_710114A650(u32 size, s32 a3) const;

    struct {
        u16 type;
        u16 index;
    };
    u32 raw;
};

// inline-only in the original; name is a guess. Builds a key as one word (0x7101118908, and the
// getImageType helpers).
inline ImageTypeMaybe makeImageTypeMaybe(u16 type, u16 index) {
    ImageTypeMaybe key;
    key.type = type;
    key.index = index;
    return key;
}

// Offsets of the four children of an area node, in units of the child size (x right for bit 0, y for
// bit 1).
// 0x7101ec503c
extern const sead::Vector2f sUnk_7101EC503C[4];

// Constants passed by address to many terrain functions (CreateTeraSystem, 0x71011074a0, ...).
// 0x7101ec54ac
extern const ImageTypeMaybe sUnk_7101EC54AC;
// 0x7101ec54b4
extern const ImageTypeMaybe sUnk_7101EC54B4;
// 0x7101ec54b8 / 0x7101ec54bc: type 3 index 0 (grass) / 1 (water).
extern const ImageTypeMaybe sUnk_7101EC54B8;
extern const ImageTypeMaybe sUnk_7101EC54BC;
// 0x7101ec54a8: type 0xff (no image); System::x resets the ring entries to it.
extern const ImageTypeMaybe sUnk_7101EC54A8;

// Placeholder: a material and a texture index (returned by a virtual of the object at
// Terrain::_370->_4ae0 + 0x10; getters at 0x7101140610 - 0x710114065c).
struct MaterialTextureMaybe {
    // 0x7101140610 (placeholder name)
    nn::gfx::ResTexture* getTexture() const;

    nn::g3d::ResMaterial* material;
    s32 index;
};

// Placeholder name: an index into a table of image sizes (32 - 1024).
enum class ImageSizeMaybe : u32 {};

// 0x710114a63c (placeholder name): the size for `size`.
u32 getImageSizeMaybe(const ImageSizeMaybe& size);

// Placeholder: per-mip-level CPU addresses and sizes of a texture (built on the stack by 0x7101109bd8,
// 0x710110a468, 0x710110a740, 0x710110bd78).
struct TextureMipTableMaybe {
    struct Level {
        u8* address;
        // Level 0: TextureData +0x4c; other levels: byte size / height (a row pitch).
        u32 pitch;
        u16 width;
        u16 height;
        f32 half_texel_x;
        f32 half_texel_y;
    };
    Level levels[14];
    u32 _150;
    u32 _154;
    u32 num_levels;
};

// Placeholder: what 0x710110979c samples (0x7101109bd8 builds it on the stack: {table, 0, true}).
struct TextureSamplerArgMaybe {
    const TextureMipTableMaybe* table;
    u32 _8;
    bool _c;
};

// 0x710110979c (placeholder name): bilinear sample (0 - 1) of the 8-bit texture of `arg` at `uv`
// (texture coordinates of mip `level`, wrapped once into range).
f32 sub_710110979C(f32 u, f32 v, const TextureSamplerArgMaybe* arg, u32 level);

// 0x710110b814 (placeholder name): samples a four-byte texel of mip `level` at `uv`: bytes 0, 1 and 3 from
// the nearest texel, byte 2 bilinearly filtered; returned as (b0 << 24) | (b1 << 16) | (b2 << 8) | b3.
u32 sub_710110B814(f32 u, f32 v, const TextureSamplerArgMaybe* arg, u32 level);

// 0x710110de64 (placeholder name): fills `table` from `texture` (image and mip addresses, level sizes);
// unused levels are cleared.
void sub_710110DE64(TextureMipTableMaybe* table, const agl::TextureData& texture);
// 0x710114add4 (declared only; placeholder name; 5176 B): writes two sizes for an image of `type` (cached
// in function-local statics per type and `c`); called twice by 0x7101132fe0 with the image's m9 / m10 and
// then m4 or m5.
void sub_710114ADD4(u32* out_a, u32* out_b, const ImageTypeMaybe& type, s32 a, u32 b, s32 c);

// Placeholder (ctor 0x710110d278, init 0x710110d2c4; size 0xa8). _8 points to the key the managers
// search by (first u16 is its id); _a0 is compared with epsilon by 0x7101108624.
class Unk_710110d278 {
public:
    // Placeholder: an entry of Key::_a8 (0x710110d320 reads its weight at 0x18).
    struct Layer {
        u8 _0[0x18];
        f32 weight;
    };
    struct Key {
        u16 id;
        u8 _2[0xa4 - 0x2];
        // Texel count per square unit (0x710110d320 multiplies it by _a0 squared).
        f32 _a4;
        sead::PtrArray<Layer> _a8;
    };
    // Placeholder: 16-byte entries of the buffer allocated by 0x710110d320.
    struct Entry {
        u8 _0[0x10];
    };
    struct InitArg {
        sead::Heap* heap;
        Unk_710250dbc8* image;
        Key* key;
        f32 _18;
    };

    // 0x710110d278
    Unk_710110d278();
    // 0x710110d28c
    ~Unk_710110d278();
    // 0x710110d2c4: frees the buffer, takes the image, key and _18 of `arg` and runs sub_710110D320.
    void init(const InitArg& arg);
    // 0x710110d320 (declaration only; placeholder name; 520 B): allocates the buffer from `heap`.
    void sub_710110D320(sead::Heap* heap);

    // inline-only in the original; name is a guess: the same release sequence is in the destructor
    // 0x710110d28c and init 0x710110d2c4.
    void freeBufferMaybe() {
        if (_10 && _18) {
            delete[] _18;
            _18 = nullptr;
            _10 = 0;
        }
    }

    Unk_710250dbc8* mImage = nullptr;
    Key* _8 = nullptr;
    // Freed by init (count, then buffer).
    u32 _10 = 0;
    Entry* _18 = nullptr;
    // Per layer of the key: the first entry index (by weight) and a counter.
    u32 _20[16];
    u32 _60[16];
    f32 _a0 = 0.0f;
    u8 _a4[0xa8 - 0xa4];
};

// Placeholder name (inline ctor in the factory 0x7101108460; size 0x30): a list node that is its own
// list data; the factory links it into the list at +0x88 of its owner.
class Unk_7101108460 : public sead::TListNode<Unk_7101108460*> {
public:
    Unk_7101108460() : sead::TListNode<Unk_7101108460*>(this) {}
    // Inlined into 0x7101106fd0.
    ~Unk_7101108460() {
        if (mA) {
            delete mA;
            mA = nullptr;
        }
        delete mB;
    }

    // 0x7101107e90
    Unk_710250dbc8* getA();
    // 0x710110860c
    const Unk_710250dbc8* getA() const;
    // 0x7101107760
    Unk_710110d278* getB() const;
    // inline-only in the original; name is a guess. The type-2 image key (2 | id << 16, built as one
    // word in 0x71011176bc).
    ImageTypeMaybe getImageType() const {
        ImageTypeMaybe type;
        type.type = 2;
        type.index = getB()->_8->id;
        return type;
    }
    // 0x7101108614 (placeholder name): id of the key of B.
    u16 sub_7101108614() const;
    // 0x7101108624 (placeholder name): B's _a0 is above epsilon.
    bool sub_7101108624() const;

    Unk_710250dbc8* mA = nullptr;
    Unk_710110d278* mB = nullptr;
};

}  // namespace ksys::tera

namespace ksys::tera {

// Placeholder: the flags 0x7101108ae8 reads (both low bits of _0 must be set; _2 is a level limit).
struct Unk_7101108AE8Flags {
    u8 _0;
    u8 _1;
    u8 _2;
    u8 _3[0x8 - 0x3];
    u8 _8;
    u8 _9;
    u8 _a[0xe - 0xa];
    // Texel count of the area table (0x710110adf8 divides it by an area's _18).
    u16 _e;
    u8 _10[0x438 - 0x10];
    // The area texel table (Unk_71010FEDBC + 0x458; 0x71011094a0, 0x710110b38c, 0x710110aa5c).
    const struct Unk_710110AC74Table* table;
};

// Placeholder: what Unk_7101108AE8Flags::table (record + 0x458) points to: per level a row pitch, a texel count and a
// coordinate offset (0x710110ac74, 0x7101108c44), then the texel data of each area per level.
struct Unk_710110AC74Table {
    struct Level {
        u16 pitch;
        u16 size;
        f32 offset;
        u32 _8;
    };
    struct AreaData {
        const u8* levels[17];
    };
    u8 _0[0x18];
    Level levels[14];
    AreaData areas[16];
    u32 _940;
    // Bytes per texel.
    u32 texel_size;
};

// Placeholder (callers 0x7101108ae8, 0x7101109bd8, 0x710110a468, 0x710110a740, 0x7101105b2c,
// 0x7100f289f0): an array of 0x528-byte areas at _8 with a base size at _18 and a level in the top
// three bits of _1e.
struct Unk_71010FEDBC {
    struct Area {
        // 0x71010fe480 (declaration only; placeholder name; 372 B): resets the area.
        void sub_71010FE480();

        // Placeholder: fixed-point (1 / 8192) bounds of a cell.
        struct Rect {
            s16 minX;
            s16 maxX;
            s16 minY;
            s16 maxY;
            u8 _8[0x10 - 0x8];
        };
        struct Cell {
            s16 _0;
            s16 _2;
            s16 _4;
            s16 _6;
            u8 _8;
            u8 _9;
            u8 _a;
            u8 _b[0x10 - 0xb];
            void* _10;
            sead::Vector2f _18;
        };
        struct Offset {
            s16 _0;
            s16 _2;
        };

        sead::Vector2f center;
        sead::Vector2f _8;
        sead::Vector2f origin;
        f32 size;
        // low nibble: a type (< 4 has bounds in mRects), high nibble: another value.
        u8 mCellFlags[5][5];
        u8 _35;
        // low nibble: x offset index, high nibble: y offset index.
        u8 mOffsetIndex;
        u8 _37;
        Offset mOffsetsX[5];
        Offset mOffsetsY[5];
        Cell mCells[5][5];
        Rect mRects[5][5];
        u8 _510[0x528 - 0x510];
    };
    // 0x71010fedbc (placeholder name): the last of the first `count` areas whose distance from `pos`
    // (plus `margin`) is in range of the current level, or -1.
    s32 sub_71010FEDBC(const sead::Vector2f& pos, u32 count, f32 margin) const;

    // Placeholder: what sub_71010FE920 writes for an area.
    struct Result {
        sead::Vector2f pos;
        void* _8;
        u32 _10;
        u8 _14;
        u8 _15;
        bool _16;
    };
    // inline-only in the original; name is a guess. Unless _1f is set, false if one of the first `level`
    // areas (at most _20._2) has neither bit of 0xc in _35. Inlined four times into 0x71011020c0.
    bool areAreasReadyMaybe(u32 level) const {
        if (_1f)
            return true;
        for (u32 i = level < _20._2 ? level : _20._2; i != 0; --i) {
            if (!(mAreas[i - 1]._35 & 0xc))
                return false;
        }
        return true;
    }

    // 0x71010fe920 (placeholder name): false if `pos` is outside area `index`; otherwise writes the
    // position relative to the area and the data of the cell it falls in.
    bool sub_71010FE920(Result* result, const sead::Vector2f& pos, u32 index) const;

    // 0x71010feb94 (placeholder name): resets the areas from `start` on (sub_71010FE480) and sets _10 / _14
    // to 1000000.
    void sub_71010FEB94(s32 start);

    // Placeholder: per-area positions (0x1c bytes each) compared with the areas by 0x71010fcfd0.
    struct AreaPos {
        sead::Vector2f pos;
        sead::Vector2f _8;
        u8 _10[0x1c - 0x10];
    };

    // 0x71010fcb04 (placeholder name): clears the record (_10 / _14 = 1000000, _18 = 1).
    void sub_71010FCB04();
    // 0x71010fcfd0 (placeholder name): whether area `index` has moved away from its position record
    // (squared distances against 2^-19, the second one scaled by the largest coordinate, at least 1).
    bool sub_71010FCFD0(u32 index) const;

    AreaPos* _0;
    Area* mAreas;
    f32 _10;
    f32 _14;
    f32 _18;
    // Scene::sub_7101100260 writes it for eight of the Scene records.
    u16 _1c;
    // Signed bitfields: the area count (0x71010feb94 sign-extends the low five bits) and the level.
    s8 mNumAreas : 5;
    s8 mLevel : 3;
    u8 _1f;
    // The query helpers receive a pointer to this sub-object; its table is at +0x438 (record + 0x458).
    Unk_7101108AE8Flags _20;
};
// The same objects as the nine 0x460-byte records at the start of a Scene (System::sub_710111F4F0 /
// sub_710111F504 return one; 0x71011094a0 passes one as both arguments of 0x7101108ae8).
KSYS_CHECK_SIZE_NX150(Unk_71010FEDBC, 0x460);


// 0x7101108ae8 (placeholder name): searches the areas from the highest usable level down for one
// whose position for `pos` is in [-1, 2); returns 2 (or 1 if its _10 is set) and writes the position
// and area index, or returns 0.
u32 sub_7101108AE8(sead::Vector2f* out_pos, s32* out_index, const sead::Vector2f& pos,
                   const Unk_7101108AE8Flags& flags, const Unk_71010FEDBC& areas, u32 max_level);

}  // namespace ksys::tera
