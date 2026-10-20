#include "aal/aalAttenuationMgr.h"
#include <resource/seadResourceMgr.h>
#include <resource/seadSharcArchiveRes.h>
#include <basis/seadNew.h>
#include <codec/seadHashCRC32.h>
#include <filedevice/seadArchiveFileDevice.h>
#include <filedevice/seadPath.h>
#include "aal/aalAttenuationReader.h"
#include "aal/aalAttenuator.h"
#include "aal/aalCurveReader.h"
#include "aal/aalSystem.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b88620
AttenuationMgr::AttenuationMgr() = default;

// 0x7100b88794
AttenuationMgr::~AttenuationMgr() {
    finalize();
}

// 0x7100b88e7c
void AttenuationMgr::calc() {
    if (mPreviewEmitter) {
        if (mPreviewPlaying && _11d && !mPreviewHandle.isActive()) {
            mPreviewPlaying = false;
            _110 = 0;
            mPreviewHandle.stop(0.0f, 0.0f);
        }
        if (mPreviewHandle.isActive())
            mPreviewHandle.setVolume(mPreviewVolume);
    }
    _17c = false;
}

// NON_MATCHING: the operands of the node address calculation of the attenuator loop are swapped.
// 0x7100b89074
void AttenuationMgr::removeAndDeleteAllComponents_() {
    for (Attenuator& attenuator : mAttenuators.robustRange()) {
        mAttenuators.erase(&attenuator);
        attenuator.destroy();
    }
    for (Curve& curve : mCurves.robustRange()) {
        removeCurveInner_(&curve);
        delete &curve;
    }
    for (AttenuationDirectivity& directivity : mDirectivities.robustRange()) {
        removeAttenuationDirectivityInner_(&directivity);
        delete &directivity;
    }
    for (AttenuationCulling& culling : mCullings.robustRange()) {
        removeAttenuationCullingInner_(&culling);
        delete &culling;
    }
}

// 0x7100b8a944
void AttenuationMgr::makeResourcdFullPath_(sead::BufferedSafeString* out, const sead::SafeString& directory,
                                           const sead::SafeString& name, const sead::SafeString& extension) const {
    sead::Path::join(out, directory.cstr(), name.cstr());
    out->append(extension);
}

// 0x7100b873ec
Attenuator* AttenuationMgr::findAttenuator(const sead::SafeString& name) const {
    if (mAttenuatorHashTable.isBufferReady()) {
        const u32 hash = sead::HashCRC32::calcStringHash(name.cstr());
        s32 low = 0;
        s32 high = mAttenuatorHashTable.size();
        while (true) {
            const s32 mid = (low + high) / 2;
            const AttenuatorHashEntry& entry = mAttenuatorHashTable[mid];
            if (entry.hash == hash)
                return entry.attenuator;
            if (entry.hash < hash) {
                if (low == mid)
                    return nullptr;
                low = mid;
            } else {
                if (high == mid)
                    return nullptr;
                high = mid;
            }
        }
    }

    for (Attenuator& attenuator : mAttenuators) {
        if (attenuator.getObjName().isEqual(name))
            return &attenuator;
    }
    return nullptr;
}

// NON_MATCHING: the original handles the first element before the loop (without the index clamp), and does not
// share one heap sort with the other table (the sort of sead::Buffer is expanded here too, differently scheduled).
// 0x7100b875b0
void AttenuationMgr::createAttenuatorHashTable(sead::Heap* heap) {
    mAttenuatorHashTable.freeBuffer();
    const s32 num = mAttenuators.size();
    if (num < 1)
        return;
    if (!mAttenuatorHashTable.tryAllocBuffer(num, heap, 8))
        return;
    s32 i = 0;
    for (Attenuator& attenuator : mAttenuators) {
        AttenuatorHashEntry& entry = mAttenuatorHashTable[i];
        entry.hash = sead::HashCRC32::calcStringHash(attenuator.getObjName().cstr());
        entry.attenuator = &attenuator;
        ++i;
    }
    mAttenuatorHashTable.heapSort(0, num - 1);
}

// 0x7100b8b650
Attenuator* AttenuationMgr::getAttenuator(s32 index) const {
    if (index < 0 || index >= mAttenuators.size())
        return nullptr;
    return mAttenuators.nth(index);
}

// 0x7100b8b698
Attenuator* AttenuationMgr::findAttenuatorOrDefault(const sead::SafeString& name) const {
    Attenuator* attenuator = findAttenuator(name);
    return attenuator ? attenuator : mDefaultAttenuator;
}

// 0x7100b8aae8
Attenuator* AttenuationMgr::createAndAddAttenuator(const sead::SafeString& name, sead::Heap* heap) {
    if (name.getStringTop()[0] == sead::SafeString::cNullChar || findAttenuator(name))
        return nullptr;

    Attenuator* attenuator = Attenuator::create(name, heap);
    if (attenuator) {
        mAttenuators.pushBack(attenuator);
        if (mAttenuatorReflexer)
            mAttenuatorReflexer->updateChildren();
        if (mDefaultAttenuatorName)
            mDefaultAttenuator = findAttenuator(*mDefaultAttenuatorName);
    }
    return attenuator;
}

// 0x7100b8abe8
RollOffCurve* AttenuationMgr::createAndAddRollOffCurve(const sead::SafeString& name, sead::Heap* heap) {
    if (name.getStringTop()[0] == sead::SafeString::cNullChar || findCurve(name))
        return nullptr;

    RollOffCurve* curve = new (heap, std::nothrow) RollOffCurve(name);
    if (curve) {
        addCurveInner_(curve);
        if (mCurveReflexer)
            mCurveReflexer->updateChildren();
    }
    return curve;
}

// 0x7100b8adc8
CustomCurve* AttenuationMgr::createAndAddCustomCurve(const sead::SafeString& name, sead::Heap* heap) {
    if (name.getStringTop()[0] == sead::SafeString::cNullChar || findCurve(name))
        return nullptr;

    CustomCurve* curve = new (heap, std::nothrow) CustomCurve(name);
    if (curve) {
        addCurveInner_(curve);
        if (mCurveReflexer)
            mCurveReflexer->updateChildren();
    }
    return curve;
}

// 0x7100b8afa8
UnitDistanceCurve* AttenuationMgr::createAndAddUnitDistanceCurve(const sead::SafeString& name, sead::Heap* heap) {
    if (name.getStringTop()[0] == sead::SafeString::cNullChar || findCurve(name))
        return nullptr;

    UnitDistanceCurve* curve = new (heap, std::nothrow) UnitDistanceCurve(name);
    if (curve) {
        addCurveInner_(curve);
        if (mCurveReflexer)
            mCurveReflexer->updateChildren();
    }
    return curve;
}

// 0x7100b8b188
AttenuationDirectivity* AttenuationMgr::createAndAddAttenuationDirectivity(const sead::SafeString& name,
                                                                           sead::Heap* heap) {
    if (name.getStringTop()[0] == sead::SafeString::cNullChar || findAttenuationDirectivity(name))
        return nullptr;

    AttenuationDirectivity* directivity = new (heap, std::nothrow) AttenuationDirectivity(name);
    if (directivity) {
        addAttenuationDirectivityInner_(directivity);
        if (mDirectivityReflexer)
            mDirectivityReflexer->updateChildren();
    }
    return directivity;
}

// 0x7100b8b368
AttenuationCulling* AttenuationMgr::createAndAddAttenuationCulling(const sead::SafeString& name, sead::Heap* heap) {
    if (name.getStringTop()[0] == sead::SafeString::cNullChar || findAttenuationCulling(name))
        return nullptr;

    AttenuationCulling* culling = new (heap, std::nothrow) AttenuationCulling(name);
    if (culling) {
        addAttenuationCullingInner_(culling);
        if (mCullingReflexer)
            mCullingReflexer->updateChildren();
    }
    return culling;
}

// 0x7100b8b548
void AttenuationMgr::setDefaultAttenuatorName(const sead::SafeString& name) {
    if (mDefaultAttenuatorName)
        mDefaultAttenuatorName->copy(name);
    if (mDefaultAttenuatorName)
        mDefaultAttenuator = findAttenuator(*mDefaultAttenuatorName);
}

// 0x7100b8b6c0
void AttenuationMgr::addCurveInner_(Curve* curve) {
    if (!curve)
        return;
    mCurves.pushBack(curve);
    for (Attenuator& attenuator : mAttenuators)
        attenuator.solveNameToInstance();
    if (mAttenuatorReflexer)
        mAttenuatorReflexer->updateChildren();
}

// 0x7100b8b7a0
void AttenuationMgr::removeCurveInner_(Curve* curve) {
    mCurves.erase(curve);
    for (Attenuator& attenuator : mAttenuators)
        attenuator.solveNameToInstance();
    if (mAttenuatorReflexer)
        mAttenuatorReflexer->updateChildren();
}

// 0x7100b8b878
void AttenuationMgr::addAttenuationDirectivityInner_(AttenuationDirectivity* directivity) {
    if (!directivity)
        return;
    mDirectivities.pushBack(directivity);
    for (Attenuator& attenuator : mAttenuators)
        attenuator.solveNameToInstance();
    if (mAttenuatorReflexer)
        mAttenuatorReflexer->updateChildren();
}

// 0x7100b8b958
void AttenuationMgr::removeAttenuationDirectivityInner_(AttenuationDirectivity* directivity) {
    mDirectivities.erase(directivity);
    for (Attenuator& attenuator : mAttenuators)
        attenuator.solveNameToInstance();
    if (mAttenuatorReflexer)
        mAttenuatorReflexer->updateChildren();
}

// 0x7100b8ba30
void AttenuationMgr::addAttenuationCullingInner_(AttenuationCulling* culling) {
    if (!culling)
        return;
    mCullings.pushBack(culling);
    for (Attenuator& attenuator : mAttenuators)
        attenuator.solveNameToInstance();
    if (mAttenuatorReflexer)
        mAttenuatorReflexer->updateChildren();
}

// 0x7100b8bb10
void AttenuationMgr::removeAttenuationCullingInner_(AttenuationCulling* culling) {
    mCullings.erase(culling);
    for (Attenuator& attenuator : mAttenuators)
        attenuator.solveNameToInstance();
    if (mAttenuatorReflexer)
        mAttenuatorReflexer->updateChildren();
}


// 0x7100b879bc
Curve* AttenuationMgr::findCurve(const sead::SafeString& name) const {
    for (Curve& curve : mCurves) {
        if (curve.getObjName().isEqual(name))
            return &curve;
    }
    return nullptr;
}

// 0x7100b87e7c
AttenuationDirectivity* AttenuationMgr::findAttenuationDirectivity(const sead::SafeString& name) const {
    for (AttenuationDirectivity& directivity : mDirectivities) {
        if (directivity.getObjName().isEqual(name))
            return &directivity;
    }
    return nullptr;
}

// 0x7100b8833c
AttenuationCulling* AttenuationMgr::findAttenuationCulling(const sead::SafeString& name) const {
    for (AttenuationCulling& culling : mCullings) {
        if (culling.getObjName().isEqual(name))
            return &culling;
    }
    return nullptr;
}

// 0x7100b872cc
void AttenuatorListReflexer::debugCreate_(const sead::SafeString& name) {
    AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
    if (!mgr)
        return;
    if (name.getStringTop()[0] == sead::SafeString::cNullChar || mgr->findAttenuator(name))
        return;

    Attenuator* attenuator = Attenuator::create(name, System::sInstance->mDebugHeap);
    if (!attenuator)
        return;
    mgr->mAttenuators.pushBack(attenuator);
    if (mgr->mAttenuatorReflexer)
        mgr->mAttenuatorReflexer->updateChildren();
    if (mgr->mAttenuatorHashTable.isBufferReady()) {
        mgr->mAttenuatorHashTable.freeBuffer();
        mgr->createAttenuatorHashTable(System::sInstance->mDebugHeap);
    }
}

// 0x7100b878d4
void AttenuatorListReflexer::debugDestroy_(const sead::SafeString& name) {
    AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
    if (!mgr)
        return;
    Attenuator* attenuator = mgr->findAttenuator(name);
    if (!attenuator)
        return;

    mgr->mAttenuators.erase(attenuator);
    if (mgr->mAttenuatorReflexer)
        mgr->mAttenuatorReflexer->updateChildren();
    attenuator->destroy();
    if (mgr->mAttenuatorHashTable.isBufferReady()) {
        mgr->mAttenuatorHashTable.freeBuffer();
        mgr->createAttenuatorHashTable(System::sInstance->mDebugHeap);
    }
}

// 0x7100b87ca0
void AttenuationDirectivityListReflexer::debugCreate_(const sead::SafeString& name) {
    AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
    if (!mgr)
        return;
    if (name.getStringTop()[0] == sead::SafeString::cNullChar || mgr->findAttenuationDirectivity(name))
        return;

    AttenuationDirectivity* component = new (System::sInstance->mDebugHeap, std::nothrow) AttenuationDirectivity(name);
    if (!component)
        return;
    mgr->addAttenuationDirectivityInner_(component);
    if (mgr->mDirectivityReflexer)
        mgr->mDirectivityReflexer->updateChildren();
}

// 0x7100b87fa4
void AttenuationDirectivityListReflexer::debugDestroy_(const sead::SafeString& name) {
    AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
    if (!mgr)
        return;
    AttenuationDirectivity* component = mgr->findAttenuationDirectivity(name);
    if (!component)
        return;

    mgr->removeAttenuationDirectivityInner_(component);
    if (mgr->mDirectivityReflexer)
        mgr->mDirectivityReflexer->updateChildren();
    delete component;
}

// 0x7100b88160
void AttenuationCullingListReflexer::debugCreate_(const sead::SafeString& name) {
    AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
    if (!mgr)
        return;
    if (name.getStringTop()[0] == sead::SafeString::cNullChar || mgr->findAttenuationCulling(name))
        return;

    AttenuationCulling* component = new (System::sInstance->mDebugHeap, std::nothrow) AttenuationCulling(name);
    if (!component)
        return;
    mgr->addAttenuationCullingInner_(component);
    if (mgr->mCullingReflexer)
        mgr->mCullingReflexer->updateChildren();
}

// 0x7100b88464
void AttenuationCullingListReflexer::debugDestroy_(const sead::SafeString& name) {
    AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
    if (!mgr)
        return;
    AttenuationCulling* component = mgr->findAttenuationCulling(name);
    if (!component)
        return;

    mgr->removeAttenuationCullingInner_(component);
    if (mgr->mCullingReflexer)
        mgr->mCullingReflexer->updateChildren();
    delete component;
}

// 0x7100b87ae4
void AttenuationCurveListReflexer::debugDestroy_(const sead::SafeString& name) {
    AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr();
    if (!mgr)
        return;
    Curve* component = mgr->findCurve(name);
    if (!component)
        return;

    mgr->removeCurveInner_(component);
    if (mgr->mCurveReflexer)
        mgr->mCurveReflexer->updateChildren();
    delete component;
}

// NON_MATCHING: native string comparisons and temporary storage differ.
void AttenuationMgr::createComponentFromResourceName_(sead::SafeString name, sead::Heap* heap) {
    AttenuationMgr* manager = SystemAccessor::getAttenuationMgr();
    if (!manager)
        return;
    sead::FixedSafeString<64> extension;
    if (!sead::Path::getExt(&extension, name))
        return;
    sead::FixedSafeString<64> full_extension(".");
    full_extension.append(extension);
    sead::FixedSafeString<32> base_name;
    if (!sead::Path::getBaseFileName(&base_name, name))
        return;
    if (full_extension == ".baatn")
        manager->createAndAddAttenuator(base_name, heap);
    else if (full_extension == ".baroc")
        manager->createAndAddRollOffCurve(base_name, heap);
    else if (full_extension == ".bactc")
        manager->createAndAddCustomCurve(base_name, heap);
    else if (full_extension == ".baudc")
        manager->createAndAddUnitDistanceCurve(base_name, heap);
    else if (full_extension == ".baadr")
        manager->createAndAddAttenuationDirectivity(base_name, heap);
    else if (full_extension == ".baacl")
        manager->createAndAddAttenuationCulling(base_name, heap);
}

// NON_MATCHING: native list sorting, string temporaries and registers differ.
void AttenuationMgr::setupFromFileDevice_(sead::ArchiveFileDevice* device,
                                         const sead::SafeString& directory,
                                         sead::Heap* heap, sead::Heap* load_heap) {
    if (!device || !device->isAvailable())
        return;
    sead::DirectoryHandle handle;
    if (!device->tryOpenDirectory(&handle, "/"))
        return;
    sead::DirectoryEntry entry;
    u32 entries_read = 0;
    while (device->tryReadDirectory(&entries_read, &handle, &entry, 1)) {
        if (!entries_read)
            break;
        if (!entry.is_directory)
            createComponentFromResourceName_(entry.name, heap);
        entries_read = 0;
    }
    device->tryCloseDirectory(&handle);
    const auto compare_names = [](const auto* a, const auto* b) {
        return a->getObjName().compare(b->getObjName());
    };
    mAttenuators.insertionSort(compare_names);
    if (mAttenuatorReflexer)
        mAttenuatorReflexer->updateChildren();
    mCurves.insertionSort(compare_names);
    if (mCurveReflexer)
        mCurveReflexer->updateChildren();
    mDirectivities.insertionSort(compare_names);
    if (mDirectivityReflexer)
        mDirectivityReflexer->updateChildren();
    mCullings.insertionSort(compare_names);
    if (mCullingReflexer)
        mCullingReflexer->updateChildren();
    for (Curve& curve : mCurves) {
        if (auto* roll_off = sead::DynamicCast<RollOffCurve>(&curve)) {
            sead::FixedSafeString<256> path;
            makeResourcdFullPath_(&path, directory, curve.getObjName(), ".baroc");
            sead::FileDevice::LoadArg arg;
            arg.path = path;
            arg.heap = load_heap;
            arg.alignment = -0x20;
            if (u8* data = device->tryLoad(arg)) {
                RollOffCurveReader reader(data);
                roll_off->setupFromResourceReader(reader, heap);
                ::operator delete(data);
            }
        } else if (auto* custom = sead::DynamicCast<CustomCurve>(&curve)) {
            sead::FixedSafeString<256> path;
            makeResourcdFullPath_(&path, directory, curve.getObjName(), ".bactc");
            sead::FileDevice::LoadArg arg;
            arg.path = path;
            arg.heap = load_heap;
            arg.alignment = -0x20;
            if (u8* data = device->tryLoad(arg)) {
                CustomCurveReader reader(data);
                custom->setupFromResourceReader(reader, heap);
                ::operator delete(data);
            }
        } else if (auto* unit_distance = sead::DynamicCast<UnitDistanceCurve>(&curve)) {
            sead::FixedSafeString<256> path;
            makeResourcdFullPath_(&path, directory, curve.getObjName(), ".baudc");
            sead::FileDevice::LoadArg arg;
            arg.path = path;
            arg.heap = load_heap;
            arg.alignment = -0x20;
            if (u8* data = device->tryLoad(arg)) {
                UnitDistanceCurveReader reader(data);
                unit_distance->setupFromResourceReader(reader, heap);
                ::operator delete(data);
            }
        }
    }
    for (AttenuationDirectivity& directivity : mDirectivities) {
        sead::FixedSafeString<256> path;
        makeResourcdFullPath_(&path, directory, directivity.getObjName(), ".baadr");
        sead::FileDevice::LoadArg arg;
        arg.path = path;
        arg.heap = load_heap;
        arg.alignment = -0x20;
        if (u8* data = device->tryLoad(arg)) {
            AttenuationDirectivityReader reader(data);
            directivity.setupFromResourceReader(reader);
            ::operator delete(data);
        }
    }
    for (AttenuationCulling& culling : mCullings) {
        sead::FixedSafeString<256> path;
        makeResourcdFullPath_(&path, directory, culling.getObjName(), ".baacl");
        sead::FileDevice::LoadArg arg;
        arg.path = path;
        arg.heap = load_heap;
        arg.alignment = -0x20;
        if (u8* data = device->tryLoad(arg)) {
            AttenuationCullingReader reader(data);
            culling.setupFromResourceReader(reader);
            ::operator delete(data);
        }
    }
    for (Attenuator& attenuator : mAttenuators) {
        sead::FixedSafeString<256> path;
        makeResourcdFullPath_(&path, directory, attenuator.getObjName(), ".baatn");
        sead::FileDevice::LoadArg arg;
        arg.path = path;
        arg.heap = load_heap;
        arg.alignment = -0x20;
        if (u8* data = device->tryLoad(arg)) {
            AttenuatorReader reader(data);
            attenuator.setupFromResourceReader(reader);
            ::operator delete(data);
        }
    }
}

// The native static initializer B8CA98 constructs this Sharc factory.
extern sead::DirectResourceFactory<sead::SharcArchiveRes> sUnk_71025fbfa0;

// NON_MATCHING: native argument construction and register allocation differ.
void AttenuationMgr::setupFromArchiveResource(const void* data, size_t size,
                                               sead::Heap* heap, sead::Heap* load_heap) {
    if (!data)
        return;
    if (!load_heap)
        load_heap = heap;
    removeAndDeleteAllComponents_();
    sead::ResourceMgr::CreateArg arg;
    arg.buffer = const_cast<u8*>(static_cast<const u8*>(data));
    arg.file_size = size;
    arg.buffer_size = size;
    arg.factory = &sUnk_71025fbfa0;
    arg.heap = load_heap;
    arg.alignment = -0x20;
    auto* archive = sead::DynamicCast<sead::ArchiveRes>(sead::ResourceMgr::instance()->create(arg));
    if (!archive)
        return;
    auto* device = new (load_heap, -0x20) sead::ArchiveFileDevice(archive);
    setupFromFileDevice_(device, "Attenuation", heap, load_heap);
    delete device;
    delete archive;
}

}  // namespace aal
