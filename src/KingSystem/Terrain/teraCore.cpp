#include "KingSystem/Terrain/teraSystem.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelDrawObj.h>
#include <gsys/gsysModelRenderContext.h>
#include <common/aglGPUCache.h>
#include <cmath>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::tera {

ExtraInfoLayerMaybe* ExtraInfoMaybe::createLayer(s32 name_id, f32 ratio, f32 scale_min,
                                                 f32 scale_max) {
    const s32 index = layers.size();
    ExtraInfoLayerMaybe* layer = layers.emplaceBack();
    const ExtraInfoNamePoolMaybe* pool = Terrain::instance()->_370->_4ae8;
    if (u32(name_id) < pool->count) {
        const char* name = pool->names[name_id].name.cstr();
        layer->name_id = name_id;
        layer->name = name;
    } else {
        layer->name_id = -1;
        layer->name = sead::SafeString::cEmptyString;
    }
    layers[index]->ratio = ratio;
    layers[index]->scale_min = scale_min;
    layers[index]->range = scale_max - scale_min;
    layers[index]->_24 = 0;
    return layer;
}

ExtraInfoLayerMaybe* ExtraInfoMaybe::addLayer(f32 ratio, f32 scale_min, f32 scale_max,
                                              const sead::SafeString& name) {
    s32 name_id = -1;
    if (Terrain::instance()->_370->_4ae8->count != 0) {
        for (u32 i = 0; i < Terrain::instance()->_370->_4ae8->count; ++i) {
            const sead::SafeString entry_name =
                Terrain::instance()->_370->_4ae8->names[s32(i)].name.cstr();
            if (name == entry_name) {
                name_id = i;
                break;
            }
        }
    }
    return createLayer(name_id, ratio, scale_min, scale_max);
}

s32 ExtraInfoMaybe::findLayerIndex(const ExtraInfoLayerMaybe* layer) const {
    s32 index = -1;
    for (u32 i = 0; i < u32(layers.size()); ++i) {
        if (layers.at(i) == layer) {
            index = i;
            break;
        }
    }
    return index;
}

// Empty in this release (Terrain::m20 calls it).
void Core::sub_71013019B8() {}

void Core::sub_710130085C() {
    if (_37c & 1)
        mModel->requestUpdate(6);
    _360.exchange(0);
}

// NON_MATCHING: the compiler moves the flag load across the relaxed atomic exchange.
void Core::sub_710130089C() {
    if (_37c & 1)
        mModel->requestDraw();
    _360.exchange(0);
    _37c |= 4;
}

// NON_MATCHING: clang keeps two induction variables (an index and a byte offset) here and uses a
// 64-bit counter; the original keeps the 32-bit index and scales it in the address. The memset and
// the loop shapes are otherwise reproduced. The inner loop in the original runs mStates.size() times
// but always reads mStates[i] (the counter is not used as the index).
void Core::sub_7101300BF0() {
    u8 table[32];
    const s32 num_positions = mPositions.size();
    for (s32 i = 0; i != num_positions; ++i)
        table[i] = 0xff;
    const s32 num_states = mStates.size();
    for (s32 i = 0; i != num_states; ++i) {
        auto& state = mStates[i];
        if (!(state.mFlags & 1)) {
            state.mIndex = -1;
            state.mFlags &= ~u32(3);
        } else if (!(state.mFlags & 2)) {
            if (table[u8(state.mIndex)] == 0xff)
                table[u8(state.mIndex)] = 0xfe;
        } else if (table[u8(state.mIndex)] < 0xfe) {
            state.mFlags &= ~u32(2);
        } else {
            table[u8(state.mIndex)] = u8(i);
        }
    }
    for (s32 i = 0; i != num_positions; ++i) {
        if (table[i] != 0xfe)
            continue;
        for (s32 j = num_states - 1; j >= 0; --j) {
            auto& state = mStates[i];
            if (state.mIndex == s8(i)) {
                state.mIndex = -1;
                state.mFlags &= ~u32(3);
            }
        }
    }
}

void Core::sub_7101300B4C(u32 index, const sead::Vector3f* position, bool update) {
    if (_37c & 2) {
        sub_7101300BF0();
        _37c &= ~2;
    }
    mPositions[index].mPosition = *position;
    if (update)
        sub_7101300D50(index, true, true);
}

void Core::sub_7101300F1C(u32 index, const sead::Vector3f* position, bool update) {
    if (_37c & 2) {
        sub_7101300BF0();
        _37c &= ~2;
    }
    mPositions[index].mPosition = *position;
    sub_7101300D50(index, true, true);
    for (auto& system : mSystems)
        system.sub_7101117048(index, position, update);
}

void Core::sub_71013010D4(const Unk_71013010d4& state, s32 index) {
    mStates[index] = state;
    _37c |= 2;
}

}  // namespace ksys::tera

namespace ksys::tera {

// NON_MATCHING: one address computation (_180) is scheduled earlier.
Core::~Core() = default;

Core::Core() {
    mSystems.initOffset(0x1340);
    _37c = 9;
}

void Core::postCalcWorld(const gsys::ModelScene* scene, u32 a, u32 b,
                         const gsys::ModelViewData* model_view_data, int view_index) {
    if (mScene != scene)
        return;
    if ((~ksys::tera::Terrain::instance()->_a58 & 6) != 0)
        return;
    _378 = b;
    sub_71013019BC(model_view_data, view_index);
}

void Core::calcBeforeDraw(gsys::ModelScene* scene, const gsys::ModelViewData* model_view_data,
                          int view_index) {
    if (mScene != scene)
        return;
    if ((~ksys::tera::Terrain::instance()->_a58 & 6) != 0)
        return;
    sub_7101302080();
    sub_71013021E0(model_view_data, view_index);
}

void Core::sub_710130241C(agl::DrawContext* context, const gsys::ModelRenderContext* arg) {
    if ((~Terrain::instance()->_a58 & 6) != 0)
        return;

    const Unk_71013010d4& state = mStates[arg->getViewIndex()];
    const s8 material = state.mIndex;
    if ((state.mFlags & 2) && material != -1) {
        const Unk_7101300b4c& position = mPositions[material];
        if (_360.compareExchange(0, 1))
            Terrain::instance()->_370->sub_710113F374(context);
        if (Terrain::instance()->_460 == 0) {
            for (auto& system : mSystems) {
                if (system._8)
                    system.sub_710111486C(context, material, position._199, position._19a);
            }
            if (Terrain::instance()->_460 == 0 && !(Terrain::instance()->_a58 & 1)) {
                u32 flags = Terrain::instance()->_a50->_18;
                if ((~flags & 0x18) != 0) {
                    _138->sub_71011503CC(context, material, arg);
                    flags = Terrain::instance()->_a50->_18;
                }
                if (!(flags & 0x20))
                    _140->sub_71010819D4(context, material, arg);
            }
        }
    }

    agl::GPUCache::invalidateAll(context);
    _37c &= ~4u;
}


void Core::sub_7101301068(bool update) {
    for (auto& system : mSystems)
        system.sub_7101115158(update);
}

void Core::sub_71013008E4(sead::Heap* heap, System* system) {
    mSystems.pushBack(system);
    for (u32 i = 0; i <= 0xff; ++i) {
        system->_1334.slot = _374.fetchAdd(1);
        if (Terrain::instance()->mImageResourceMgr->sub_7101131CDC(system))
            break;
    }
    System::InitArgMaybe arg;
    arg.heap = heap;
    arg.model = mScene ? mModel : nullptr;
    arg.count = mStates.size();
    system->sub_7101112E78(arg);
}

void Core::sub_71013009C4(sead::Heap* heap) {
    if (!mScene)
        return;

    const u32 count = mModelUnits.size();
    for (u32 i = 0; i != count; ++i)
        mModel->sub_7100BF7114(mModelUnits[i].mUnit, true, heap);
    mModel->bind(mScene);
    mModel->sub_7100BF9CA8(sead::SafeString("テライン"));
    Terrain::instance()->sub_710107E900(mModel, false);
}

// 0x7101300aac: sets the visibility mask of every unit of the model (all bits when `visible`).
void Core::sub_7101300AAC(bool visible) {
    for (u32 i = 0; i < mModel->getUnits().size(); ++i) {
        gsys::ModelUnit* unit = mModel->getUnits()(i)->mModelUnit;
        if (unit != this)
            unit->setVisibilityMask(visible ? 0xffff : 0);
    }

    if (visible) {
        if (Terrain::instance()->_a58 & 0x10)
            Terrain::instance()->sub_710107E900(mModel, true);
        _37c |= 8;
    } else {
        _37c = _37c & 0xf7;
    }
}

// inline-only in the original (0x7101300d50 validates x, z and the squared length); name is a guess.
static bool isValidFloatMaybe(f32 value) {
    if (sead::Mathf::isNan(value))
        return false;
    if (sead::Mathf::abs(value) > 3.4028235e+38f)
        return false;
    if (sead::Mathf::abs(value) > 2147483648.0f)
        return false;
    return true;
}

// NON_MATCHING: the sead::Buffer index loads are ordered differently.
// 0x7101300d50 (unnamed in the CSV): validates the position of entry `index`, copies it to the
// entry's previous position, stores the two flags and appends the XZ position to Terrain's ring.
bool Core::sub_7101300D50(u32 index, bool a, bool b) {
    const f32 x = mPositions[index].mPosition.x;
    const f32 y = mPositions[index].mPosition.y;
    const f32 z = mPositions[index].mPosition.z;
    if (!isValidFloatMaybe(x))
        return false;
    if (!isValidFloatMaybe(z))
        return false;
    if (!isValidFloatMaybe(x * x + y * y + z * z))
        return false;

    mPositions[index]._14 = sead::Vector3f(x, y, z);
    mPositions[index]._199 = a;
    mPositions[index]._19a = b;

    auto* debug = Terrain::instance()->_a50;
    const sead::Vector2f* slot = &debug->mPositions[debug->mPosIndex % debug->mPosCount];
    const f32 dx = x - slot->x;
    const f32 dz = z - slot->y;
    if (dx * dx + dz * dz > 0.001f) {
        ++debug->mPosIndex;
        debug->mPositions[debug->mPosIndex % debug->mPosCount] = sead::Vector2f(x, z);
    }
    return true;
}

// 0x710130063c (unnamed): releases the model, the per-unit buffers and the grass / tree objects.
void Core::sub_710130063C() {
    if (mModel) {
        gsys::Model::sub_7100BF69F8(mModel);
        mModel = nullptr;
    }
    if (mModelDrawObjs.size() != 0)
        mModelDrawObjs.freeBuffer();
    if (_110.size() != 0)
        _110.freeBuffer();
    if (mModelUnits.size() != 0)
        mModelUnits.freeBuffer();
    if (_138) {
        _138->sub_710114EE20();
        delete _138;
        _138 = nullptr;
    }
    if (_140) {
        _140->sub_7101080A08();
        delete _140;
        _140 = nullptr;
    }
    if (mPositions.size() != 0) {
        for (s32 i = 0; i < mPositions.size(); ++i)
            mPositions[i].mBlock.destroy();
        mPositions.freeBuffer();
    }
    mStates.freeBuffer();
    mHeap = nullptr;
    mModelHeap = nullptr;
}

// 0x7101300800 (unnamed): runs the cleanup, deletes the core and destroys both of its heaps.
void Core::sub_7101300800() {
    sead::Heap* heap = mHeap;
    sead::Heap* model_heap = mModelHeap;
    sub_710130063C();
    delete this;
    model_heap->destroy();
    heap->destroy();
}

void Core::releaseAllNodeGroups() {
    for (auto& system : mSystems)
        system.sub_7101117874();
}

}  // namespace ksys::tera
