#include "player_ingame_info.h"

namespace msgame
{
    namespace gameobject
    {
        PlayerIngameInfo::PlayerIngameInfo(Player* owner)
        :owner(owner)
        {
            hp_current = HP_MAX;

            firearm_main = firearm_1 = new AutoRifle(this);
            firearm_2 = new Bazooka(this);
        }

        void PlayerIngameInfo::Pulse()
        {
        }
    }
}