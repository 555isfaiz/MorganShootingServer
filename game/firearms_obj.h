#ifndef _ms_firearms_obj_
#define _ms_firearms_obj_

#include <string>
#include "ms_types.h"

namespace msgame
{
    namespace gameobject
    {
        class PlayerIngameInfo;

        class FirearmsObject
        {
        protected:
            PlayerIngameInfo* owner;
            int32 magazine_ammo;
            int32 total_ammo;
            bool fire_start = false;
            int32 fire_frequency;
            int64 nextFireTime;
            int32 reload_duration;

            bool CanShoot();

        public:
            FirearmsObject(PlayerIngameInfo* owner);
            void Pulse();
        };

        class AutoRifle : public FirearmsObject
        {
        public:
            AutoRifle(PlayerIngameInfo* owner);
            void Pulse();
        };
        
        class Bazooka : public FirearmsObject
        {
        public:
            Bazooka(PlayerIngameInfo* owner);
            void Pulse();
        };
    } // namespace gameobject
} // namespace msgame

#endif