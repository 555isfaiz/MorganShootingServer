#ifndef _ms_player_
#define _ms_player_

#include <string>
#include "ms_message.h"
#include "physics/ms_collider.h"
#include "ms_link_queue.h"
#include "ms_simple_task.h"
#include "LinearMath/btVector3.h"
#include "BulletCollision/CollisionDispatch/btCollisionObject.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"

#define GAMEOBJECT msgame::gameobject

static btCollisionShape *bt_sphere = new btSphereShape(btScalar(0.5f));

namespace msgame
{
    namespace gameobject
    {
        class Player
        {
        private:
            int32 id_;
            std::string name_;
            btCollisionObject *bt_cobj;
            
        public:
            

            int32 number_;
            Player(int32 id, std::string &name, int32 side);
            virtual ~Player() {}

            void Pulse();

            msmessage::BPlayer GetMsg();
            inline int32 id() { return id_; }
            inline void id(int32 id) { id_ = id; }

            void SetPosition(const btVector3 &position) 
            {
                bt_cobj->getWorldTransform().setOrigin(position);
            }

            btVector3 GetPosition() const
            {
                return bt_cobj->getWorldTransform().getOrigin(); 
            }

            void SetVelocity(const btVector3 &velocity)
            {
                bt_cobj->setInterpolationLinearVelocity(velocity);
            }

            btVector3 GetVelocity() const
            {
                return bt_cobj->getInterpolationLinearVelocity(); 
            }

            btCollisionObject *GetCollisionObject() const
            {
                return bt_cobj;
            }
        };
    } // namespace gameobject
} // namespace msgame

#endif