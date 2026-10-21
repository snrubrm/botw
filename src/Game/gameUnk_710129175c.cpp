#include "Game/gameGraphics.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelScene.h>
#include <gsys/gsysModelUnit.h>

// Graphics' render-record TUs (0x71012915bc .. 0x71012955xx). Unk_710129175c and Unk_710129421c
// are constructed by gameGraphics.cpp's initializer but their methods live here.

// 0x71012938a0: agl::sdw::ShadowPrePass::Context's destructor (declaration only).
void sub_71012938A0(void* context);

Unk_710129175c::Record::~Record() {
    sub_71012938A0(this);
}

Unk_710129175c::Unk_710129175c() : _8(0), mRecords(), mPage(), _260() {}

// NON_MATCHING: the record count is loaded one instruction later and the loop increments the
// count before the record pointer; the teardown sequence matches.
Unk_710129175c::~Unk_710129175c() {
    auto delete_block = [](const agl::GPUMemAddrBase& block) {
        agl::GPUMemVoidAddr copy(block);
        copy.deleteGPUMemBlock();
    };
    Record* record = mRecords.getBufferPtr();
    for (u64 i = u64(mRecords.size()); i != 0; ++record, --i) {
        delete_block(record->_12c8);
        delete_block(record->_13f0);
        delete_block(record->_1518);
        delete_block(record->_1b60);
        delete_block(record->_1c88);
        delete_block(record->_1db0);
    }
    mRecords.freeBuffer();
    mPage.~DebugTexturePage();
}

Unk_7101293bac::Unk_7101293bac() : _8(0), mFlags(2), mPage(), _250(0), _254(0) {}
// NON_MATCHING: the inlined DebugTexturePage teardown stores only the IDisposer vtable, not the
// hostio::Node vtable at +0x30; the cleanUp / base-destructor calls match.
Unk_7101293bac::~Unk_7101293bac() {
    mPage.~DebugTexturePage();
}

void Unk_7101293bac::sub_7101293C9C(s32, sead::Heap* heap) {
    mPage.setUp(1, "ItemFilter", heap);
}

void Unk_7101293bac::sub_7101293D68(u32 index, gsys::ModelScene* scene) {
    auto* model = scene->mSceneModel;
    const char* names[4] = {"none", "DeferredTypeA", "DeferredTypeC", "DeferredTypeD"};
    gsys::ModelUnit* units[4];
    for (s32 i = 0; i < 4; ++i) {
        const s32 unit_index = model->searchUnitIndex(names[i]);
        auto* unit = unit_index == -1 ? nullptr : model->getUnits()(unit_index)->mModelUnit;
        units[i] = unit;
        if (unit) {
            unit->enableRenderOption(static_cast<gsys::ModelEnum::RenderOption>(0x12), false);
            unit->enableRenderViewOption(static_cast<gsys::ModelEnum::RenderViewOption>(4), false, -1);
            unit->sub_7100C3ECF0(_250, false);
            unit->setVisibilityMask(0);
        }
    }
    if (auto* unit = units[index]) {
        unit->sub_7100C3ECF0(_250, true);
        unit->setVisibilityMask(0xffff);
    }
}

// 0x7100f00018: clears bit 3 of the object's flag word (defined in gameGraphics.cpp to stay out of line).
void sub_7100F00018(Unk_7100efd9b8Obj* object);

Unk_7100efd9b8::Unk_7100efd9b8() = default;

Unk_7100efd9b8::~Unk_7100efd9b8() {
    if (_a8) {
        ::operator delete[](_a8);
        _a8 = nullptr;
        _a0 = 0;
    }
    if (_110) {
        ::operator delete[](_110);
        _110 = nullptr;
        _108 = 0;
    }
    if (_20) {
        ::operator delete[](_20);
        _20 = nullptr;
        _18 = 0;
    }
    if (_10) {
        ::operator delete[](static_cast<u8*>(_10) - 8);
        _10 = nullptr;
        _8 = 0;
    }
    if (_120) {
        _120->m2();
        _120 = nullptr;
    }
}

void Unk_7100efd9b8::sub_7100EFE030() {
    if (_120)
        sub_7100F00018(_120);
}

void Unk_710129175c::sub_71012920C4(s32 index) {
    mRecords[index]._1ff4 = 1;
}

// NON_MATCHING: the original stores the four bounds floats directly; sead::BoundBox2::set (our only
// public way in) also normalises min / max, which costs four fcmp/fcsel.
void Unk_710129175c::sub_710129276C(s32 index, Result* result) {
    const Record& record = mRecords[index];
    result->_0 = record._1f98;
    result->bounds.set(record._1fa0, record._1fa4, record._1fa8, record._1fac);
    result->_18 = record._1fc8;
    result->_1c._0.x = record._1fd0;
    result->_1c._0.y = record._1fd4;
    result->_1c._0.z = record._1fd8;
    result->_1c._c = record._1fdc;
    result->_2c = record._1fcc;
}

void Unk_710129421c::sub_7101295560(s32 index, const sead::Color4f& color) {
    mEntries[index]._7d0 = color;
}

void Unk_710129421c::sub_710129558C(f32 value, s32 index) {
    mEntries[index]._7e0 = value;
}

void Unk_710129421c::sub_71012955AC(f32 value, s32 index) {
    mEntries[index]._7e4 = value;
}

