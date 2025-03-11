using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace csharp_test_client
{
    struct PacketData
    {
        public Int16 DataSize;
        public Int16 PacketID;
        public byte[] BodyData;
    }

    public class PacketDump
    {
        public static string Bytes(byte[] byteArr)
        {
            StringBuilder sb = new StringBuilder("[");
            for( int i = 0; i < byteArr.Length; ++i )
            {
                sb.Append(byteArr[i] + " ");
            }
            sb.Append("]");
            return sb.ToString();
        }
    }


    public class ErrorNtfPacket
    {
        public ERROR_CODE Error;

        public bool FromBytes(byte[] bodyData)
        {
            Error = (ERROR_CODE)BitConverter.ToInt16(bodyData, 0);
            return true;
        }
    }


    public class ReqLoginPacket
    {
        byte[] UserID = new byte[PacketDef.MAX_USER_ID_BYTE_LENGTH];

        public void SetValue(string userID)
        {
            Encoding.UTF8.GetBytes(userID).CopyTo(UserID, 0);
        }

        public byte[] ToBytes()
        {
            List<byte> dataSource = new List<byte>();
            dataSource.AddRange(UserID);
            return dataSource.ToArray();
        }
    }

    public class AnsLoginPacket
    {
        public UInt16 Result;

        public bool FromBytes(byte[] bodyData)
        {
            Result = BitConverter.ToUInt16(bodyData, 0);
            return true;
        }
    }


    public class ReqRoomEnterPacket
    {
        int RoomNumber;
        public void SetValue(int roomNumber)
        {
            RoomNumber = roomNumber;
        }

        public byte[] ToBytes()
        {
            List<byte> dataSource = new List<byte>();
            dataSource.AddRange(BitConverter.GetBytes(RoomNumber));
            return dataSource.ToArray();
        }
    }

    public class AnsRoomEnterPacket
    {
        public UInt16 Result;
        public Int32 UserCount = 0;
        public List<string> UserIDList = new List<string>();

        public bool FromBytes(byte[] bodyData)
        {
            var readPos = 0;
            Result = BitConverter.ToUInt16(bodyData, 0);
            readPos += 2;
            UserCount = BitConverter.ToInt32(bodyData, readPos);
            readPos += 4;

            for( int i = 0; i < UserCount; ++i )
            {
                var id = Encoding.UTF8.GetString(bodyData, readPos, PacketDef.MAX_USER_ID_BYTE_LENGTH);
                readPos += PacketDef.MAX_USER_ID_BYTE_LENGTH;

                UserIDList.Add(id);
            }


            return true;
        }
    }

    public class NtfRoomEnterPacket
    {
        public string UserID;

        public bool FromBytes(byte[] bodyData)
        {
            var readPos = 0;

            UserID = Encoding.UTF8.GetString(bodyData, readPos, PacketDef.MAX_USER_ID_BYTE_LENGTH);
            readPos += PacketDef.MAX_USER_ID_BYTE_LENGTH;

            return true;
        }
    }


    public class ReqRoomChatPacket
    {
        byte[] Msg = new byte[PacketDef.MAX_CHAT_MSG_SIZE];

        public void SetValue(string message)
        {
            Encoding.UTF8.GetBytes(message).CopyTo(Msg, 0);
        }

        public byte[] ToBytes()
        {
            List<byte> dataSource = new List<byte>();
            dataSource.AddRange(Msg);
            return dataSource.ToArray();
        }
    }

    public class AnsRoomChatPacket
    {
        public UInt16 Result;

        public bool FromBytes(byte[] bodyData)
        {
            Result = BitConverter.ToUInt16(bodyData, 0);
            return true;
        }
    }

    public class NtfRoomChatPacket
    {
        public Int32 UserIDLength;
        public string UserID;
        public string Message;

        public bool FromBytes(byte[] bodyData)
        {
            UserIDLength = BitConverter.ToInt32(bodyData, 0);
            UserID = Encoding.UTF8.GetString(bodyData, 4, UserIDLength);
            UserID = UserID.Trim();
            Message = Encoding.UTF8.GetString(bodyData, 4 + PacketDef.MAX_USER_ID_BYTE_LENGTH, PacketDef.MAX_CHAT_MSG_SIZE);
            Message = Message.Trim();

            return true;
        }
    }

    public class AnsRoomLeavePacket
    {
        public UInt16 Result;

        public bool FromBytes(byte[] bodyData)
        {
            Result = BitConverter.ToUInt16(bodyData, 0);
            return true;
        }
    }

    public class NtfRoomLeaveUserPacket
    {
        public string UserID;

        public bool FromBytes(byte[] bodyData)
        {
            var readPos = 0;
            UserID = Encoding.UTF8.GetString(bodyData, readPos, PacketDef.MAX_USER_ID_BYTE_LENGTH);
            readPos += PacketDef.MAX_USER_ID_BYTE_LENGTH;
            return true;
        }
    }
}
