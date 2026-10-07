#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/ActorSystem/AS/asDungeonClearSelector.h"

namespace ksys::as {

Element* DungeonClearSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) DungeonClearSelector(arg, value, resource);
}


// The factory functions of the elements (one per class; the constructors live in the classes' own files, so they
// are not inlined here).
Element* BoneBlender::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) BoneBlender(arg, value, resource);
}

Element* BoolSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) BoolSelector(arg, value, resource);
}

Element* ComboSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) ComboSelector(arg, value, resource);
}

Element* ClearMatAnmAsset::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) ClearMatAnmAsset(arg, value, resource);
}

Element* AngleBlender::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) AngleBlender(arg, value, resource);
}

Element* AngleSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) AngleSelector(arg, value, resource);
}

Element* EventFlagSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) EventFlagSelector(arg, value, resource);
}

Element* GroundNormalBlender::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) GroundNormalBlender(arg, value, resource);
}

Element* GroundNormalSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) GroundNormalSelector(arg, value, resource);
}

Element* GroundNormalSideBlender::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) GroundNormalSideBlender(arg, value, resource);
}

Element* GroundNormalSideSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) GroundNormalSideSelector(arg, value, resource);
}

Element* NodePosSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) NodePosSelector(arg, value, resource);
}

Element* PreASSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) PreASSelector(arg, value, resource);
}

Element* PreExclusionRandomSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) PreExclusionRandomSelector(arg, value, resource);
}

Element* SequencePlayContainer::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) SequencePlayContainer(arg, value, resource);
}

Element* SpeedBlender::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) SpeedBlender(arg, value, resource);
}

Element* SpeedSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) SpeedSelector(arg, value, resource);
}

Element* SyncPlayContainer::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) SyncPlayContainer(arg, value, resource);
}

Element* TimeSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) TimeSelector(arg, value, resource);
}

Element* WeatherSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) WeatherSelector(arg, value, resource);
}

Element* WindVelocityBlender::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) WindVelocityBlender(arg, value, resource);
}

Element* YSpeedBlender::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) YSpeedBlender(arg, value, resource);
}

Element* YSpeedSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) YSpeedSelector(arg, value, resource);
}

Element* ZEx00ExposureBlender::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) ZEx00ExposureBlender(arg, value, resource);
}

Element* ZEx00ExposureSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) ZEx00ExposureSelector(arg, value, resource);
}

Element* IntSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) IntSelector(arg, value, resource);
}

// (CSV ASNoAnmAsset::make)
Element* AnmAsset::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) AnmAsset(arg, value, resource);
}

Element* SkeltalAsset::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) SkeltalAsset(arg, value, resource);
}

Element* RandomSelector::make(const CreateArg& arg, s32 value, const res::ASResource* resource) {
    return new (arg.heap, 8) RandomSelector(arg, value, resource);
}

}  // namespace ksys::as
