namespace csharp_test_client
{
    partial class mainForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            btnDisconnect = new System.Windows.Forms.Button();
            btnConnect = new System.Windows.Forms.Button();
            groupBox5 = new System.Windows.Forms.GroupBox();
            textBoxPort = new System.Windows.Forms.TextBox();
            label10 = new System.Windows.Forms.Label();
            checkBoxLocalHostIP = new System.Windows.Forms.CheckBox();
            textBoxIP = new System.Windows.Forms.TextBox();
            label9 = new System.Windows.Forms.Label();
            labelStatus = new System.Windows.Forms.Label();
            listBoxLog = new System.Windows.Forms.ListBox();
            label1 = new System.Windows.Forms.Label();
            textBoxUserID = new System.Windows.Forms.TextBox();
            button2 = new System.Windows.Forms.Button();
            Room = new System.Windows.Forms.GroupBox();
            btnRoomChat = new System.Windows.Forms.Button();
            textBoxRoomSendMsg = new System.Windows.Forms.TextBox();
            listBoxRoomChatMsg = new System.Windows.Forms.ListBox();
            label4 = new System.Windows.Forms.Label();
            listBoxRoomUserList = new System.Windows.Forms.ListBox();
            btn_RoomLeave = new System.Windows.Forms.Button();
            btn_RoomEnter = new System.Windows.Forms.Button();
            textBoxRoomNumber = new System.Windows.Forms.TextBox();
            label3 = new System.Windows.Forms.Label();
            groupBox5.SuspendLayout();
            Room.SuspendLayout();
            SuspendLayout();
            // 
            // btnDisconnect
            // 
            btnDisconnect.Font = new System.Drawing.Font("맑은 고딕", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, 129);
            btnDisconnect.Location = new System.Drawing.Point(842, 117);
            btnDisconnect.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            btnDisconnect.Name = "btnDisconnect";
            btnDisconnect.Size = new System.Drawing.Size(176, 69);
            btnDisconnect.TabIndex = 29;
            btnDisconnect.Text = "접속 끊기";
            btnDisconnect.UseVisualStyleBackColor = true;
            btnDisconnect.Click +=  btnDisconnect_Click ;
            // 
            // btnConnect
            // 
            btnConnect.Font = new System.Drawing.Font("맑은 고딕", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, 129);
            btnConnect.Location = new System.Drawing.Point(840, 43);
            btnConnect.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            btnConnect.Name = "btnConnect";
            btnConnect.Size = new System.Drawing.Size(176, 69);
            btnConnect.TabIndex = 28;
            btnConnect.Text = "접속하기";
            btnConnect.UseVisualStyleBackColor = true;
            btnConnect.Click +=  btnConnect_Click ;
            // 
            // groupBox5
            // 
            groupBox5.Controls.Add(textBoxPort);
            groupBox5.Controls.Add(label10);
            groupBox5.Controls.Add(checkBoxLocalHostIP);
            groupBox5.Controls.Add(textBoxIP);
            groupBox5.Controls.Add(label9);
            groupBox5.Location = new System.Drawing.Point(24, 32);
            groupBox5.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            groupBox5.Name = "groupBox5";
            groupBox5.Padding = new System.Windows.Forms.Padding(6, 8, 6, 8);
            groupBox5.Size = new System.Drawing.Size(806, 139);
            groupBox5.TabIndex = 27;
            groupBox5.TabStop = false;
            groupBox5.Text = "Socket 더미 클라이언트 설정";
            // 
            // textBoxPort
            // 
            textBoxPort.Location = new System.Drawing.Point(450, 53);
            textBoxPort.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            textBoxPort.MaxLength = 6;
            textBoxPort.Name = "textBoxPort";
            textBoxPort.Size = new System.Drawing.Size(98, 39);
            textBoxPort.TabIndex = 18;
            textBoxPort.Text = "65535";
            textBoxPort.WordWrap = false;
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Location = new System.Drawing.Point(326, 64);
            label10.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            label10.Name = "label10";
            label10.Size = new System.Drawing.Size(123, 32);
            label10.TabIndex = 17;
            label10.Text = "포트 번호:";
            // 
            // checkBoxLocalHostIP
            // 
            checkBoxLocalHostIP.AutoSize = true;
            checkBoxLocalHostIP.Checked = true;
            checkBoxLocalHostIP.CheckState = System.Windows.Forms.CheckState.Checked;
            checkBoxLocalHostIP.Location = new System.Drawing.Point(570, 64);
            checkBoxLocalHostIP.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            checkBoxLocalHostIP.Name = "checkBoxLocalHostIP";
            checkBoxLocalHostIP.Size = new System.Drawing.Size(197, 36);
            checkBoxLocalHostIP.TabIndex = 15;
            checkBoxLocalHostIP.Text = "localhost 사용";
            checkBoxLocalHostIP.UseVisualStyleBackColor = true;
            // 
            // textBoxIP
            // 
            textBoxIP.Location = new System.Drawing.Point(136, 51);
            textBoxIP.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            textBoxIP.MaxLength = 16;
            textBoxIP.Name = "textBoxIP";
            textBoxIP.Size = new System.Drawing.Size(170, 39);
            textBoxIP.TabIndex = 11;
            textBoxIP.Text = "0.0.0.0";
            textBoxIP.WordWrap = false;
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Location = new System.Drawing.Point(12, 61);
            label9.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            label9.Name = "label9";
            label9.Size = new System.Drawing.Size(123, 32);
            label9.TabIndex = 10;
            label9.Text = "서버 주소:";
            // 
            // labelStatus
            // 
            labelStatus.AutoSize = true;
            labelStatus.Location = new System.Drawing.Point(20, 1554);
            labelStatus.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            labelStatus.Name = "labelStatus";
            labelStatus.Size = new System.Drawing.Size(220, 32);
            labelStatus.TabIndex = 40;
            labelStatus.Text = "서버 접속 상태: ???";
            // 
            // listBoxLog
            // 
            listBoxLog.FormattingEnabled = true;
            listBoxLog.HorizontalScrollbar = true;
            listBoxLog.Location = new System.Drawing.Point(20, 1020);
            listBoxLog.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            listBoxLog.Name = "listBoxLog";
            listBoxLog.Size = new System.Drawing.Size(990, 484);
            listBoxLog.TabIndex = 41;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new System.Drawing.Point(38, 246);
            label1.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            label1.Name = "label1";
            label1.Size = new System.Drawing.Size(90, 32);
            label1.TabIndex = 42;
            label1.Text = "UserID:";
            // 
            // textBoxUserID
            // 
            textBoxUserID.Location = new System.Drawing.Point(154, 238);
            textBoxUserID.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            textBoxUserID.MaxLength = 6;
            textBoxUserID.Name = "textBoxUserID";
            textBoxUserID.Size = new System.Drawing.Size(170, 39);
            textBoxUserID.TabIndex = 43;
            textBoxUserID.Text = "user";
            textBoxUserID.WordWrap = false;
            // 
            // button2
            // 
            button2.Font = new System.Drawing.Font("맑은 고딕", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, 129);
            button2.Location = new System.Drawing.Point(662, 230);
            button2.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            button2.Name = "button2";
            button2.Size = new System.Drawing.Size(290, 69);
            button2.TabIndex = 46;
            button2.Text = "Login";
            button2.UseVisualStyleBackColor = true;
            button2.Click +=  button2_Click ;
            // 
            // Room
            // 
            Room.Controls.Add(btnRoomChat);
            Room.Controls.Add(textBoxRoomSendMsg);
            Room.Controls.Add(listBoxRoomChatMsg);
            Room.Controls.Add(label4);
            Room.Controls.Add(listBoxRoomUserList);
            Room.Controls.Add(btn_RoomLeave);
            Room.Controls.Add(btn_RoomEnter);
            Room.Controls.Add(textBoxRoomNumber);
            Room.Controls.Add(label3);
            Room.Location = new System.Drawing.Point(24, 313);
            Room.Margin = new System.Windows.Forms.Padding(6, 5, 6, 5);
            Room.Name = "Room";
            Room.Padding = new System.Windows.Forms.Padding(6, 5, 6, 5);
            Room.Size = new System.Drawing.Size(990, 667);
            Room.TabIndex = 47;
            Room.TabStop = false;
            Room.Text = "Room";
            // 
            // btnRoomChat
            // 
            btnRoomChat.Font = new System.Drawing.Font("맑은 고딕", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, 129);
            btnRoomChat.Location = new System.Drawing.Point(874, 565);
            btnRoomChat.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            btnRoomChat.Name = "btnRoomChat";
            btnRoomChat.Size = new System.Drawing.Size(100, 69);
            btnRoomChat.TabIndex = 53;
            btnRoomChat.Text = "chat";
            btnRoomChat.UseVisualStyleBackColor = true;
            btnRoomChat.Click +=  btnRoomChat_Click ;
            // 
            // textBoxRoomSendMsg
            // 
            textBoxRoomSendMsg.Location = new System.Drawing.Point(26, 573);
            textBoxRoomSendMsg.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            textBoxRoomSendMsg.MaxLength = 32;
            textBoxRoomSendMsg.Name = "textBoxRoomSendMsg";
            textBoxRoomSendMsg.Size = new System.Drawing.Size(834, 39);
            textBoxRoomSendMsg.TabIndex = 52;
            textBoxRoomSendMsg.Text = "test1";
            textBoxRoomSendMsg.WordWrap = false;
            // 
            // listBoxRoomChatMsg
            // 
            listBoxRoomChatMsg.FormattingEnabled = true;
            listBoxRoomChatMsg.Location = new System.Drawing.Point(288, 173);
            listBoxRoomChatMsg.Margin = new System.Windows.Forms.Padding(6, 5, 6, 5);
            listBoxRoomChatMsg.Name = "listBoxRoomChatMsg";
            listBoxRoomChatMsg.Size = new System.Drawing.Size(682, 356);
            listBoxRoomChatMsg.TabIndex = 51;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new System.Drawing.Point(20, 136);
            label4.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            label4.Name = "label4";
            label4.Size = new System.Drawing.Size(111, 32);
            label4.TabIndex = 50;
            label4.Text = "User List:";
            // 
            // listBoxRoomUserList
            // 
            listBoxRoomUserList.FormattingEnabled = true;
            listBoxRoomUserList.Location = new System.Drawing.Point(26, 176);
            listBoxRoomUserList.Margin = new System.Windows.Forms.Padding(6, 5, 6, 5);
            listBoxRoomUserList.Name = "listBoxRoomUserList";
            listBoxRoomUserList.Size = new System.Drawing.Size(242, 356);
            listBoxRoomUserList.TabIndex = 49;
            // 
            // btn_RoomLeave
            // 
            btn_RoomLeave.Font = new System.Drawing.Font("맑은 고딕", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, 129);
            btn_RoomLeave.Location = new System.Drawing.Point(432, 51);
            btn_RoomLeave.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            btn_RoomLeave.Name = "btn_RoomLeave";
            btn_RoomLeave.Size = new System.Drawing.Size(132, 69);
            btn_RoomLeave.TabIndex = 48;
            btn_RoomLeave.Text = "Leave";
            btn_RoomLeave.UseVisualStyleBackColor = true;
            btn_RoomLeave.Click +=  btn_RoomLeave_Click ;
            // 
            // btn_RoomEnter
            // 
            btn_RoomEnter.Font = new System.Drawing.Font("맑은 고딕", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, 129);
            btn_RoomEnter.Location = new System.Drawing.Point(288, 48);
            btn_RoomEnter.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            btn_RoomEnter.Name = "btn_RoomEnter";
            btn_RoomEnter.Size = new System.Drawing.Size(132, 69);
            btn_RoomEnter.TabIndex = 47;
            btn_RoomEnter.Text = "Enter";
            btn_RoomEnter.UseVisualStyleBackColor = true;
            btn_RoomEnter.Click +=  btn_RoomEnter_Click ;
            // 
            // textBoxRoomNumber
            // 
            textBoxRoomNumber.Location = new System.Drawing.Point(196, 53);
            textBoxRoomNumber.Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            textBoxRoomNumber.MaxLength = 6;
            textBoxRoomNumber.Name = "textBoxRoomNumber";
            textBoxRoomNumber.Size = new System.Drawing.Size(72, 39);
            textBoxRoomNumber.TabIndex = 44;
            textBoxRoomNumber.Text = "1";
            textBoxRoomNumber.WordWrap = false;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new System.Drawing.Point(10, 67);
            label3.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            label3.Name = "label3";
            label3.Size = new System.Drawing.Size(179, 32);
            label3.TabIndex = 43;
            label3.Text = "Room Number:";
            // 
            // mainForm
            // 
            AutoScaleDimensions = new System.Drawing.SizeF(14F, 32F);
            AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            AutoSize = true;
            ClientSize = new System.Drawing.Size(1048, 1625);
            Controls.Add(Room);
            Controls.Add(button2);
            Controls.Add(textBoxUserID);
            Controls.Add(label1);
            Controls.Add(labelStatus);
            Controls.Add(listBoxLog);
            Controls.Add(btnDisconnect);
            Controls.Add(btnConnect);
            Controls.Add(groupBox5);
            FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            Margin = new System.Windows.Forms.Padding(6, 8, 6, 8);
            Name = "mainForm";
            Text = "네트워크 테스트 클라이언트";
            FormClosing +=  mainForm_FormClosing ;
            Load +=  mainForm_Load ;
            groupBox5.ResumeLayout(false);
            groupBox5.PerformLayout();
            Room.ResumeLayout(false);
            Room.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private System.Windows.Forms.Button btnDisconnect;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.TextBox textBoxPort;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.CheckBox checkBoxLocalHostIP;
        private System.Windows.Forms.TextBox textBoxIP;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.ListBox listBoxLog;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxUserID;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.GroupBox Room;
        private System.Windows.Forms.Button btn_RoomLeave;
        private System.Windows.Forms.Button btn_RoomEnter;
        private System.Windows.Forms.TextBox textBoxRoomNumber;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnRoomChat;
        private System.Windows.Forms.TextBox textBoxRoomSendMsg;
        private System.Windows.Forms.ListBox listBoxRoomChatMsg;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ListBox listBoxRoomUserList;
    }
}

