using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Final_Project_Web_Server
{
    // UI Interface.
    // Enumeration for commands to send
    public enum UICommand
    { 
        DisplayRemoteIP,
        DisplayRemotePort,
        DisplayLocalIP,
        DisplayLocalPort,
        DisplayRootDirectory,
        DisplayResponse
    }

    // Delegate for function to process UI commands.
    public delegate void vProcessUIComm(UICommand uicCommand, string strText);

    // Form constructor.
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private Server servWebServer;

        // The actual function to process UI commands.
        private void vProcUIComm(UICommand uicCmd, string strText)
        {
            // Check whether we have to use Invoke to let some other thread handle
            // the processing of this command.
            if (this.InvokeRequired)
            {
                // Create a delegate for this function.
                vProcessUIComm delThisFcn = new vProcessUIComm(vProcUIComm);
                // Create an array of the arguments that are passed in, so we can 
                // pass them on when the function is reinvoked using INvoke.
                Object[] objArgs = new Object[] { uicCmd, strText };
                // Invoke execuation of this function using a different thread.
                this.Invoke(delThisFcn, objArgs);
            }
            else
            {
                switch (uicCmd)
                {
                    case UICommand.DisplayRemoteIP:
                        txtRemoteIP.Text = strText;
                        break;
                    case UICommand.DisplayRemotePort:
                        txtRemotePort.Text = strText;
                        break;
                    case UICommand.DisplayLocalIP:
                        txtLocalIP.Text = strText;
                        break;
                    case UICommand.DisplayLocalPort:
                        txtLocalPort.Text = strText;
                        break;
                    case UICommand.DisplayRootDirectory:
                        txtRootDir.Text = strText;
                        break;
                    case UICommand.DisplayResponse:
                        // Display the response in the rich text box
                        rtbRequests.AppendText(strText);
                        break;
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Create a new Server object.
            servWebServer = new Server(new vProcessUIComm(vProcUIComm));
            servWebServer.vConnect(txtRootDir.Text);
            // Clear out the rich text box and move the focus to it.
            rtbRequests.Clear();
            rtbRequests.Focus();
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            servWebServer.vDisconnect();
        }
    }
}
