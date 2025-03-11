using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace csharp_test_client
{
    class PacketDef
    {
        public const Int16 PACKET_HEADER_SIZE = 4;
        public const int MAX_USER_ID_BYTE_LENGTH = 33;
        public const int MAX_CHAT_MSG_SIZE = 257;
        public const ushort MAX_ROOM_USER_COUNT = 3;
    }

    public enum PACKET_ID : ushort
    {
        // 로그인
        REQ_LOGIN = 201,
        ANS_LOGIN = 202,

        REQ_ROOM_ENTER = 206,
        ANS_ROOM_ENTER = 207,
        NOT_ROOM_ENTER = 208,

        REQ_ROOM_LEAVE = 215,
        ANS_ROOM_LEAVE = 216,
        NOT_ROOM_LEAVE = 217,

        REQ_ROOM_CHAT = 221,
        ANS_ROOM_CHAT = 222,
        NOT_ROOM_CHAT = 223,
    }


    public enum ERROR_CODE : ushort
    {
        NONE = 0,

        USER_MGR_INVALID_USER_INDEX = 11,
        USER_MGR_INVALID_USER_UNIQUEID = 12,

        LOGIN_USER_ALREADY = 31,
        LOGIN_USER_USED_ALL_OBJ = 32,

        NEW_ROOM_USED_ALL_OBJ = 41,
        NEW_ROOM_FAIL_ENTER = 42,

        ENTER_ROOM_NOT_FINDE_USER = 51,
        ENTER_ROOM_INVALID_USER_STATUS = 52,
        ENTER_ROOM_NOT_USED_STATUS = 53,
        ENTER_ROOM_FULL_USER = 54,

        ROOM_INVALID_INDEX = 61,
        ROOM_NOT_USED = 62,
        ROOM_TOO_MANY_PACKET = 63,

        LEAVE_ROOM_INVALID_ROOM_INDEX = 71,

        CHAT_ROOM_INVALID_ROOM_NUMBER = 81,

        INVALID_CLIENT_INDEX = 91,
    }
}
