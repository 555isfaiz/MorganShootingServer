#include "firearms_obj.h"

namespace msgame
{
    namespace gameobject
    {
        AutoRifle::AutoRifle(PlayerIngameInfo* owner)
        : FirearmsObject(owner)
        {
        }

        void AutoRifle::Pulse()
        {
        }
    }
}