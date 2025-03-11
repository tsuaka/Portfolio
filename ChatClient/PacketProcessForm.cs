using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace csharp_test_client
{
    public partial class mainForm
    {
        Dictionary<PACKET_ID, Action<byte[]>> PacketFuncDic = new Dictionary<PACKET_ID, Action<byte[]>>();

        void SetPacketHandler()
        {
            PacketFuncDic.Add(PACKET_ID.ANS_LOGIN, PacketProcess_LoginResponse);
            PacketFuncDic.Add(PACKET_ID.ANS_ROOM_ENTER, PacketProcess_RoomEnterResponse);
            PacketFuncDic.Add(PACKET_ID.NOT_ROOM_ENTER, PacketProcess_RoomEnterNotify);
            PacketFuncDic.Add(PACKET_ID.ANS_ROOM_LEAVE, PacketProcess_RoomLeaveResponse);
            PacketFuncDic.Add(PACKET_ID.NOT_ROOM_LEAVE, PacketProcess_RoomLeaveUserNotify);
            PacketFuncDic.Add(PACKET_ID.ANS_ROOM_CHAT, PacketProcess_RoomChatResponse);
            PacketFuncDic.Add(PACKET_ID.NOT_ROOM_CHAT, PacketProcess_RoomChatNotify);
        }

        void PacketProcess(PacketData packet)
        {
            var packetType = (PACKET_ID)packet.PacketID;
            //DevLog.Write("Packet Error:  PacketID:{packet.PacketID.ToString()},  Error: {(ERROR_CODE)packet.Result}");
            //DevLog.Write("RawPacket: " + packet.PacketID.ToString() + ", " + PacketDump.Bytes(packet.BodyData));

            if (PacketFuncDic.ContainsKey(packetType))
            {
                PacketFuncDic[packetType](packet.BodyData);
            }
            else
            {
                DevLog.Write("Unknown Packet Id: " + packet.PacketID.ToString());
            }         
        }

        void PacketProcess_LoginResponse(byte[] bodyData)
        {
            var responsePkt = new AnsLoginPacket();
            responsePkt.FromBytes(bodyData);

            DevLog.Write($"로그인 결과:  {(ERROR_CODE)responsePkt.Result}");
        }


        void PacketProcess_RoomEnterResponse(byte[] bodyData)
        {
            var ansPacket = new AnsRoomEnterPacket();
            ansPacket.FromBytes(bodyData);

            if( ansPacket.Result == (ushort)ERROR_CODE.NONE )
            {
                ClearRoomUserList();
                for( int i = 0; i < ansPacket.UserCount; ++i )
                {
                    AddRoomUserList(ansPacket.UserIDList[i]);
                }

                DevLog.Write($"방의 기존 유저 리스트 받음");
            }
            DevLog.Write($"방 입장 결과:  {(ERROR_CODE)ansPacket.Result}");
        }

        void PacketProcess_RoomEnterNotify(byte[] bodyData)
        {
            var ntfPacket = new NtfRoomEnterPacket();
            ntfPacket.FromBytes(bodyData);

           AddRoomUserList(ntfPacket.UserID);
            
            DevLog.Write($"방에 새로 들어온 유저 받음");
        }


        void PacketProcess_RoomLeaveResponse(byte[] bodyData)
        {
            var responsePkt = new AnsRoomLeavePacket();
            responsePkt.FromBytes(bodyData);

            ClearRoomUserList();
            ClearRoomChatMessageList();

            DevLog.Write($"방 나가기 결과:  {(ERROR_CODE)responsePkt.Result}");
        }

        void PacketProcess_RoomLeaveUserNotify(byte[] bodyData)
        {
            var ntfPacket = new NtfRoomLeaveUserPacket();
            ntfPacket.FromBytes(bodyData);

           RemoveRoomUserList(ntfPacket.UserID);

            DevLog.Write($"방에서 나간 유저 받음");
        }


        void PacketProcess_RoomChatResponse(byte[] bodyData)
        {
            var responsePkt = new AnsRoomChatPacket();
            responsePkt.FromBytes(bodyData);

            var errorCode = (ERROR_CODE)responsePkt.Result;
            var msg = $"방 채팅 요청 결과:  {(ERROR_CODE)responsePkt.Result}";
            if (errorCode == ERROR_CODE.NONE)
            {
                DevLog.Write(msg, LOG_LEVEL.ERROR);
            }
            else
            {
                AddRoomChatMessageList("", msg);
            }
        }


        void PacketProcess_RoomChatNotify(byte[] bodyData)
        {
            var responsePkt = new NtfRoomChatPacket();
            responsePkt.FromBytes(bodyData);

            AddRoomChatMessageList(responsePkt.UserID, responsePkt.Message);
        }

        void ClearRoomChatMessageList()
        {
            listBoxRoomChatMsg.Items.Clear();
        }
        void AddRoomChatMessageList(string userID, string megssage)
        {
            var msg = $"{userID}:  {megssage}";

            if (listBoxRoomChatMsg.Items.Count > 512)
            {
                listBoxRoomChatMsg.Items.Clear();
            }

            listBoxRoomChatMsg.Items.Add(msg);
            listBoxRoomChatMsg.SelectedIndex = listBoxRoomChatMsg.Items.Count - 1;
        }
    }
}
