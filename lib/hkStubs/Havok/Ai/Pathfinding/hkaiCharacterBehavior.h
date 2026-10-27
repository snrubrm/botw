#pragma once

#include <Havok/Common/Base/hkBase.h>

// Partial model. The native vtables at 0x25a55e0 + 0x10 / + 0xf8 place
// getNumCharacters at slot +0x80 and getCharacter at +0x88.
class hkaiCharacterBehavior : public hkReferencedObject {
public:
    virtual int getNumCharacters() const = 0;
};

class hkaiSingleCharacterBehavior : public hkaiCharacterBehavior {
public:
    int getNumCharacters() const override;
};
