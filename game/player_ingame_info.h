#ifndef _ms_player_ingame_info_
#define _ms_player_ingame_info_

#include <string>
#include "player.h"
#include "firearms_obj.h"

namespace msgame
{
    namespace gameobject
    {
        class PlayerIngameInfo
        {
        private:
            Player* owner;
            int32 hp_current;

            FirearmsObject* firearm_main;
            FirearmsObject* firearm_1;
            FirearmsObject* firearm_2;

        public:
            PlayerIngameInfo(Player* owner);
            void Pulse();
        };
    } // namespace gameobject
} // namespace msgame

#endif