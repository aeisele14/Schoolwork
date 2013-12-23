namespace Final_Project_Web_Server
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.rtbRequests = new System.Windows.Forms.RichTextBox();
            this.lblRootDir = new System.Windows.Forms.Label();
            this.txtRootDir = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.gbxConnection = new System.Windows.Forms.GroupBox();
            this.txtLocalPort = new System.Windows.Forms.TextBox();
            this.txtLocalIP = new System.Windows.Forms.TextBox();
            this.lblLocalPort = new System.Windows.Forms.Label();
            this.lblLocalIP = new System.Windows.Forms.Label();
            this.lblRemotePort = new System.Windows.Forms.Label();
            this.lblRemoteIP = new System.Windows.Forms.Label();
            this.txtRemotePort = new System.Windows.Forms.TextBox();
            this.txtRemoteIP = new System.Windows.Forms.TextBox();
            this.gbxConnection.SuspendLayout();
            this.SuspendLayout();
            // 
            // rtbRequests
            // 
            this.rtbRequests.Location = new System.Drawing.Point(16, 242);
            this.rtbRequests.Name = "rtbRequests";
            this.rtbRequests.ReadOnly = true;
            this.rtbRequests.Size = new System.Drawing.Size(386, 180);
            this.rtbRequests.TabIndex = 0;
            this.rtbRequests.Text = "";
            // 
            // lblRootDir
            // 
            this.lblRootDir.AutoSize = true;
            this.lblRootDir.Location = new System.Drawing.Point(13, 187);
            this.lblRootDir.Name = "lblRootDir";
            this.lblRootDir.Size = new System.Drawing.Size(82, 13);
            this.lblRootDir.TabIndex = 2;
            this.lblRootDir.Text = "Document Root";
            // 
            // txtRootDir
            // 
            this.txtRootDir.Location = new System.Drawing.Point(16, 203);
            this.txtRootDir.Name = "txtRootDir";
            this.txtRootDir.Size = new System.Drawing.Size(386, 20);
            this.txtRootDir.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 226);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Responses";
            // 
            // gbxConnection
            // 
            this.gbxConnection.AutoSize = true;
            this.gbxConnection.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.gbxConnection.Controls.Add(this.txtLocalPort);
            this.gbxConnection.Controls.Add(this.txtLocalIP);
            this.gbxConnection.Controls.Add(this.lblLocalPort);
            this.gbxConnection.Controls.Add(this.lblLocalIP);
            this.gbxConnection.Controls.Add(this.lblRemotePort);
            this.gbxConnection.Controls.Add(this.lblRemoteIP);
            this.gbxConnection.Controls.Add(this.txtRemotePort);
            this.gbxConnection.Controls.Add(this.txtRemoteIP);
            this.gbxConnection.Location = new System.Drawing.Point(42, 36);
            this.gbxConnection.Name = "gbxConnection";
            this.gbxConnection.Size = new System.Drawing.Size(231, 114);
            this.gbxConnection.TabIndex = 5;
            this.gbxConnection.TabStop = false;
            this.gbxConnection.Text = "Connection";
            // 
            // txtLocalPort
            // 
            this.txtLocalPort.Location = new System.Drawing.Point(122, 75);
            this.txtLocalPort.Name = "txtLocalPort";
            this.txtLocalPort.ReadOnly = true;
            this.txtLocalPort.Size = new System.Drawing.Size(100, 20);
            this.txtLocalPort.TabIndex = 8;
            // 
            // txtLocalIP
            // 
            this.txtLocalIP.Location = new System.Drawing.Point(9, 75);
            this.txtLocalIP.Name = "txtLocalIP";
            this.txtLocalIP.ReadOnly = true;
            this.txtLocalIP.Size = new System.Drawing.Size(100, 20);
            this.txtLocalIP.TabIndex = 7;
            // 
            // lblLocalPort
            // 
            this.lblLocalPort.AutoSize = true;
            this.lblLocalPort.Location = new System.Drawing.Point(119, 59);
            this.lblLocalPort.Name = "lblLocalPort";
            this.lblLocalPort.Size = new System.Drawing.Size(95, 13);
            this.lblLocalPort.TabIndex = 6;
            this.lblLocalPort.Text = "Local Port Number";
            // 
            // lblLocalIP
            // 
            this.lblLocalIP.AutoSize = true;
            this.lblLocalIP.Location = new System.Drawing.Point(6, 59);
            this.lblLocalIP.Name = "lblLocalIP";
            this.lblLocalIP.Size = new System.Drawing.Size(87, 13);
            this.lblLocalIP.TabIndex = 5;
            this.lblLocalIP.Text = "Local IP Address";
            // 
            // lblRemotePort
            // 
            this.lblRemotePort.AutoSize = true;
            this.lblRemotePort.Location = new System.Drawing.Point(119, 16);
            this.lblRemotePort.Name = "lblRemotePort";
            this.lblRemotePort.Size = new System.Drawing.Size(106, 13);
            this.lblRemotePort.TabIndex = 3;
            this.lblRemotePort.Text = "Remote Port Number";
            // 
            // lblRemoteIP
            // 
            this.lblRemoteIP.AutoSize = true;
            this.lblRemoteIP.Location = new System.Drawing.Point(6, 16);
            this.lblRemoteIP.Name = "lblRemoteIP";
            this.lblRemoteIP.Size = new System.Drawing.Size(98, 13);
            this.lblRemoteIP.TabIndex = 2;
            this.lblRemoteIP.Text = "Remote IP Address";
            // 
            // txtRemotePort
            // 
            this.txtRemotePort.Location = new System.Drawing.Point(122, 32);
            this.txtRemotePort.Name = "txtRemotePort";
            this.txtRemotePort.ReadOnly = true;
            this.txtRemotePort.Size = new System.Drawing.Size(100, 20);
            this.txtRemotePort.TabIndex = 1;
            // 
            // txtRemoteIP
            // 
            this.txtRemoteIP.Location = new System.Drawing.Point(9, 32);
            this.txtRemoteIP.Name = "txtRemoteIP";
            this.txtRemoteIP.ReadOnly = true;
            this.txtRemoteIP.Size = new System.Drawing.Size(100, 20);
            this.txtRemoteIP.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(414, 434);
            this.Controls.Add(this.gbxConnection);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtRootDir);
            this.Controls.Add(this.lblRootDir);
            this.Controls.Add(this.rtbRequests);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.gbxConnection.ResumeLayout(false);
            this.gbxConnection.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox rtbRequests;
        private System.Windows.Forms.Label lblRootDir;
        private System.Windows.Forms.TextBox txtRootDir;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox gbxConnection;
        private System.Windows.Forms.TextBox txtLocalPort;
        private System.Windows.Forms.TextBox txtLocalIP;
        private System.Windows.Forms.Label lblLocalPort;
        private System.Windows.Forms.Label lblLocalIP;
        private System.Windows.Forms.Label lblRemotePort;
        private System.Windows.Forms.Label lblRemoteIP;
        private System.Windows.Forms.TextBox txtRemotePort;
        private System.Windows.Forms.TextBox txtRemoteIP;
    }
}

