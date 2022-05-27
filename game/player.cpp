#include "player.h"
#include "ms_message.h"

namespace msgame
{
    namespace gameobject
    {
        Player::Player(int32 id, std::string& name, int32 number)
        :id_(id)
        ,name_(name)
        ,number_(number)
        {
            btVector3 v;
            if (number_ == 0)
            {
                v.setX(0.0f);
                v.setZ(-6.0f);
            } 
            else 
            {
                v.setX(0.0f);
                v.setZ(6.0f);
            }
            
            v.setY(5.0f);
            bt_cobj = new btCollisionObject();
            bt_cobj->setCollisionShape(bt_sphere);
            bt_cobj->setUserPointer(this);
            SetPosition(v);
        }

        void Player::Pulse()
        {
        }

        msmessage::BPlayer Player::GetMsg()
        {
            msmessage::BPlayer m;
            m.playerId = id_;
            m.playerName = name_;
            m.side = number_ % 2 == 0 ? 1 : 2;
            auto pos = GetPosition();
            m.curPos.x = pos.getX();
            m.curPos.y = pos.getY();
            m.curPos.z = pos.getZ();
            auto rot = GetRotation();
            m.rotation.x = rot.getX();
            m.rotation.y = rot.getY();
            m.rotation.z = rot.getZ();
            m.rotation.w = rot.getW();
            return m;
        }
    }
}