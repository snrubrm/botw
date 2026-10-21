// The TU at 0x71012cd0bc .. 0x71012cd2a0: the sound group factory.
#include "KingSystem/Sound/sndGroupFactory.h"
#include <aal/aalGroup.h>
#include "Game/gameUnkRttiClasses.h"

namespace ksys::snd {

Unk_710251b6b8::Unk_710251b6b8() = default;

aal::SoundGroup* Unk_710251b6b8::createSoundGroup(const sead::SafeString& name, sead::Heap* heap) {
    auto* group = GroupFactory::createSoundGroup(name, heap);
    if (group) {
        if (auto* data = new (heap, 8) Unk_710251b678(group))
            group->set_98(data);
    }
    return group;
}

aal::GroupFolder* Unk_710251b6b8::createGroupFolder(const sead::SafeString& name,
                                                    sead::Heap* heap) {
    auto* group = GroupFactory::createGroupFolder(name, heap);
    if (group) {
        if (auto* data = new (heap, 8) Unk_710251b678(group))
            group->set_98(data);
    }
    return group;
}

void Unk_710251b6b8::destroyGroup(aal::Group* group) {
    if (group) {
        if (auto* data = static_cast<Unk_710251b678*>(group->get_98())) {
            group->set_98(nullptr);
            delete data;
        }
    }
    GroupFactory::destroyGroup(group);
}

}  // namespace ksys::snd
