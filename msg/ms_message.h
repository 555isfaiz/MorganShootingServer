#ifndef _ms_messages_
#define _ms_messages_

#include <vector>
#include <string>
#include "ms_types.h"

namespace msutils
{
    namespace msstream
    {
        class OutputStream;
        class InputStream;
    }
}

namespace msmessage
{
    class MessageBase
    {
    public:
        int64 id;
        virtual void write(msutils::msstream::OutputStream* out){}
        virtual void read(msutils::msstream::InputStream* in){}
        MessageBase(){}
        virtual ~MessageBase(){}
    };

    class BVector2 : public MessageBase 
    {
    public:
        float x;
        float y;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        BVector2(){ id = 102; }
        virtual ~BVector2(){}
    };

    class BVector3 : public MessageBase 
    {
    public:
        float x;
        float y;
        float z;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        BVector3(){ id = 103; }
        virtual ~BVector3(){}
    };

    class BVector4 : public MessageBase 
    {
    public:
        float x;
        float y;
        float z;
        float w;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        BVector4(){ id = 104; }
        virtual ~BVector4(){}
    };

    class CSMove : public MessageBase 
    {
    public:
        int32 playerId;
        BVector3 curPos;
        BVector3 direction;
        int64 timeStamp;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        CSMove(){ id = 2001; }
        virtual ~CSMove(){}
    };

    class SCMove : public MessageBase 
    {
    public:
        int32 playerId;
        BVector3 curPos;
        BVector3 direction;
        int64 timeStamp;
        int32 result;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        SCMove(){ id = 2002; }
        virtual ~SCMove(){}
    };

    class CSJump : public MessageBase 
    {
    public:
        int32 playerId;
        int64 jumpStart;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        CSJump(){ id = 2003; }
        virtual ~CSJump(){}
    };

    class SCJump : public MessageBase 
    {
    public:
        int32 playerId;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        SCJump(){ id = 2004; }
        virtual ~SCJump(){}
    };

    class CSDash : public MessageBase 
    {
    public:
        BVector3 direction;
        int64 duration;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        CSDash(){ id = 2005; }
        virtual ~CSDash(){}
    };

    class SCDashStart : public MessageBase 
    {
    public:
        int32 playerId;
        BVector3 direction;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        SCDashStart(){ id = 2006; }
        virtual ~SCDashStart(){}
    };

    class SCDashStop : public MessageBase 
    {
    public:
        int32 playerId;
        BVector3 finalPos;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        SCDashStop(){ id = 2007; }
        virtual ~SCDashStop(){}
    };

    class CSPlayerRotate : public MessageBase 
    {
    public:
        int32 playerId;
        BVector4 rotation;
        int64 timeStamp;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        CSPlayerRotate(){ id = 2008; }
        virtual ~CSPlayerRotate(){}
    };

    class BPlayer : public MessageBase 
    {
    public:
        int32 playerId;
        std::string playerName;
        int32 side;
        BVector3 curPos;
        BVector4 rotation;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        BPlayer(){ id = 101; }
        virtual ~BPlayer(){}
    };

    class CSLogin : public MessageBase 
    {
    public:

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        CSLogin(){ id = 1001; }
        virtual ~CSLogin(){}
    };

    class SCJoinGame : public MessageBase 
    {
    public:
        int32 sessionId;
        int32 mySide;
        std::vector<BPlayer> players;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        SCJoinGame(){ id = 1003; }
        virtual ~SCJoinGame(){}
    };

    class SCLogin : public MessageBase 
    {
    public:
        int32 playerId;
        int64 serverTimeZone;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        SCLogin(){ id = 1004; }
        virtual ~SCLogin(){}
    };

    class SCGameSync : public MessageBase 
    {
    public:
        int32 sessionId;
        std::vector<BPlayer> players;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        SCGameSync(){ id = 1005; }
        virtual ~SCGameSync(){}
    };

    class CSFireStart : public MessageBase 
    {
    public:
        bool isFire1;
        BVector3 direction;
        int64 timeStamp;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        CSFireStart(){ id = 3001; }
        virtual ~CSFireStart(){}
    };

    class SCFireSync : public MessageBase 
    {
    public:
        bool isFire1;
        bool isFire2;
        BVector3 direction;
        int32 f1Ammo;
        int32 f2Ammo;
        int64 timeStamp;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        SCFireSync(){ id = 3002; }
        virtual ~SCFireSync(){}
    };

    class CSFireStop : public MessageBase 
    {
    public:
        bool isFire1;
        int64 timeStamp;

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        CSFireStop(){ id = 3003; }
        virtual ~CSFireStop(){}
    };

    class CSSwitchWeapon : public MessageBase 
    {
    public:

        void write(msutils::msstream::OutputStream* out) override ;
        void read(msutils::msstream::InputStream* in) override ;
        CSSwitchWeapon(){ id = 3004; }
        virtual ~CSSwitchWeapon(){}
    };



    MessageBase* GetMsgById(int64 id);
}

#endif