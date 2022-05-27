#include "ms_message.h"
#include "ms_logger.h"
#include "input_stream.h"
#include "output_stream.h"

namespace msmessage
{
    void CSMove::write(STREAM::OutputStream* out)
    {
        out->write(playerId);
        out->write(&curPos);
        out->write(&direction);
        out->write(timeStamp);

    }

    void CSMove::read(STREAM::InputStream* in)
    {
        playerId = in->ReadInt32();
        curPos = *reinterpret_cast<BVector3*>(in->ReadMsg());
        direction = *reinterpret_cast<BVector3*>(in->ReadMsg());
        timeStamp = in->ReadInt64();

    }

    void SCMove::write(STREAM::OutputStream* out)
    {
        out->write(playerId);
        out->write(&curPos);
        out->write(&direction);
        out->write(timeStamp);
        out->write(result);

    }

    void SCMove::read(STREAM::InputStream* in)
    {
        playerId = in->ReadInt32();
        curPos = *reinterpret_cast<BVector3*>(in->ReadMsg());
        direction = *reinterpret_cast<BVector3*>(in->ReadMsg());
        timeStamp = in->ReadInt64();
        result = in->ReadInt32();

    }

    void CSJump::write(STREAM::OutputStream* out)
    {
        out->write(playerId);
        out->write(jumpStart);

    }

    void CSJump::read(STREAM::InputStream* in)
    {
        playerId = in->ReadInt32();
        jumpStart = in->ReadInt64();

    }

    void SCJump::write(STREAM::OutputStream* out)
    {
        out->write(playerId);

    }

    void SCJump::read(STREAM::InputStream* in)
    {
        playerId = in->ReadInt32();

    }

    void CSDash::write(STREAM::OutputStream* out)
    {
        out->write(&direction);
        out->write(duration);

    }

    void CSDash::read(STREAM::InputStream* in)
    {
        direction = *reinterpret_cast<BVector3*>(in->ReadMsg());
        duration = in->ReadInt64();

    }

    void SCDashStart::write(STREAM::OutputStream* out)
    {
        out->write(playerId);
        out->write(&direction);

    }

    void SCDashStart::read(STREAM::InputStream* in)
    {
        playerId = in->ReadInt32();
        direction = *reinterpret_cast<BVector3*>(in->ReadMsg());

    }

    void SCDashStop::write(STREAM::OutputStream* out)
    {
        out->write(playerId);
        out->write(&finalPos);

    }

    void SCDashStop::read(STREAM::InputStream* in)
    {
        playerId = in->ReadInt32();
        finalPos = *reinterpret_cast<BVector3*>(in->ReadMsg());

    }

    void CSPlayerRotate::write(STREAM::OutputStream* out)
    {
        out->write(playerId);
        out->write(&rotation);
        out->write(timeStamp);

    }

    void CSPlayerRotate::read(STREAM::InputStream* in)
    {
        playerId = in->ReadInt32();
        rotation = *reinterpret_cast<BVector4*>(in->ReadMsg());
        timeStamp = in->ReadInt64();

    }

    void BVector2::write(STREAM::OutputStream* out)
    {
        out->write(x);
        out->write(y);

    }

    void BVector2::read(STREAM::InputStream* in)
    {
        x = in->ReadFloat();
        y = in->ReadFloat();

    }

    void BVector3::write(STREAM::OutputStream* out)
    {
        out->write(x);
        out->write(y);
        out->write(z);

    }

    void BVector3::read(STREAM::InputStream* in)
    {
        x = in->ReadFloat();
        y = in->ReadFloat();
        z = in->ReadFloat();

    }

    void BVector4::write(STREAM::OutputStream* out)
    {
        out->write(x);
        out->write(y);
        out->write(z);
        out->write(w);

    }

    void BVector4::read(STREAM::InputStream* in)
    {
        x = in->ReadFloat();
        y = in->ReadFloat();
        z = in->ReadFloat();
        w = in->ReadFloat();

    }

    void BPlayer::write(STREAM::OutputStream* out)
    {
        out->write(playerId);
        out->write(playerName);
        out->write(side);
        out->write(&curPos);
        out->write(&rotation);

    }

    void BPlayer::read(STREAM::InputStream* in)
    {
        playerId = in->ReadInt32();
        playerName = in->ReadString();
        side = in->ReadInt32();
        curPos = *reinterpret_cast<BVector3*>(in->ReadMsg());
        rotation = *reinterpret_cast<BVector4*>(in->ReadMsg());

    }

    void CSLogin::write(STREAM::OutputStream* out)
    {

    }

    void CSLogin::read(STREAM::InputStream* in)
    {

    }

    void SCJoinGame::write(STREAM::OutputStream* out)
    {
        out->write(sessionId);
        out->write(mySide);
        auto b = out->ResolveNumber(players.size());
        out->WriteTandVL(STREAM::TYPE_LIST, b[0], b + 1);
        for (auto t : players)
        {
            out->write(&t);
        }
    }

    void SCJoinGame::read(STREAM::InputStream* in)
    {
        sessionId = in->ReadInt32();
        mySide = in->ReadInt32();
        auto fb = in->readV(1)[0];
        int32 length = in->ResolveNumber((fb & 0xF0) >> 4);
        for (int32 i = 0; i < length; i++)
        {
            players.push_back(*reinterpret_cast<BPlayer*>(in->ReadMsg()));
        }

    }

    void SCLogin::write(STREAM::OutputStream* out)
    {
        out->write(playerId);
        out->write(serverTimeZone);

    }

    void SCLogin::read(STREAM::InputStream* in)
    {
        playerId = in->ReadInt32();
        serverTimeZone = in->ReadInt64();

    }

    void SCGameSync::write(STREAM::OutputStream* out)
    {
        out->write(sessionId);
        auto b = out->ResolveNumber(players.size());
        out->WriteTandVL(STREAM::TYPE_LIST, b[0], b + 1);
        for (auto t : players)
        {
            out->write(&t);
        }
    }

    void SCGameSync::read(STREAM::InputStream* in)
    {
        sessionId = in->ReadInt32();
        auto fb = in->readV(1)[0];
        int32 length = in->ResolveNumber((fb & 0xF0) >> 4);
        for (int32 i = 0; i < length; i++)
        {
            players.push_back(*reinterpret_cast<BPlayer*>(in->ReadMsg()));
        }

    }


    //InputStream.ReadMsg need a instance of the message
    //dont want to override operator '=' for all messages
    //so return a pointer here
    //should delete message manually afterward
    MessageBase *GetMsgById(int64 id)
    {
        switch (id)
        {
            case 2001:
            {
                msmessage::CSMove *csmove = new msmessage::CSMove;
                return csmove;
            }

            case 2002:
            {
                msmessage::SCMove *scmove = new msmessage::SCMove;
                return scmove;
            }

            case 2003:
            {
                msmessage::CSJump *csjump = new msmessage::CSJump;
                return csjump;
            }

            case 2004:
            {
                msmessage::SCJump *scjump = new msmessage::SCJump;
                return scjump;
            }

            case 2005:
            {
                msmessage::CSDash *csdash = new msmessage::CSDash;
                return csdash;
            }

            case 2006:
            {
                msmessage::SCDashStart *scdashstart = new msmessage::SCDashStart;
                return scdashstart;
            }

            case 2007:
            {
                msmessage::SCDashStop *scdashstop = new msmessage::SCDashStop;
                return scdashstop;
            }

            case 2008:
            {
                msmessage::CSPlayerRotate *csplayerrotate = new msmessage::CSPlayerRotate;
                return csplayerrotate;
            }

            case 102:
            {
                msmessage::BVector2 *bvector2 = new msmessage::BVector2;
                return bvector2;
            }

            case 103:
            {
                msmessage::BVector3 *bvector3 = new msmessage::BVector3;
                return bvector3;
            }

            case 104:
            {
                msmessage::BVector4 *bvector4 = new msmessage::BVector4;
                return bvector4;
            }

            case 101:
            {
                msmessage::BPlayer *bplayer = new msmessage::BPlayer;
                return bplayer;
            }

            case 1001:
            {
                msmessage::CSLogin *cslogin = new msmessage::CSLogin;
                return cslogin;
            }

            case 1003:
            {
                msmessage::SCJoinGame *scjoingame = new msmessage::SCJoinGame;
                return scjoingame;
            }

            case 1004:
            {
                msmessage::SCLogin *sclogin = new msmessage::SCLogin;
                return sclogin;
            }

            case 1005:
            {
                msmessage::SCGameSync *scgamesync = new msmessage::SCGameSync;
                return scgamesync;
            }


        }

        mLogError("can't find message by Id:" << id);
        return nullptr;
    }
}