using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace Final_Project_Web_Server
{
    class Server
    {
        // Data Members
        // Encode the string
        private Encoding enCharEncoder = Encoding.UTF8;
        // Time limit for data transfers.
        private int timeout = 8;
        // Create the socket
        private Socket socServerSocket;
        // Function we call to manipulate the user interface.
        private vProcessUIComm vProcessCommand;
        // Root path of our contents
        private string strContentPath;

        // Content types supported
        private Dictionary<string, string> dicExtensions = new Dictionary<string, string>()
        {
            {"htm", "text/html"},
            {"html", "text/html"},
            {"css", "text/css"},
            {"js", "text/javascript"},
            {"gif", "image/gif"},
            {"jpeg", "image/jpeg"},
            {"png", "image/png"}
        };

        // Methods
        // Constructor.
        public Server(vProcessUIComm vProcComm)
        {
            // Set up so we can manipulate the user interface.
            vProcessCommand = vProcComm;

            // Create the socket.
            socServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        }    

        // Connect to the remote host.
        public void vConnect(string contentPath)
        { 
            // Try to connect. If we cannot the "Connect" method throws and exception.
            try
            {
                // Bind to an IP Address and port number.
                // Set up the endpoint for the IP address and port number.
                IPEndPoint ipeBindEP = new IPEndPoint(IPAddress.Any, 8080); // Always listen on port 8080
                socServerSocket.Bind(ipeBindEP);
                vProcessCommand(UICommand.DisplayLocalIP, ipeBindEP.Address.ToString());
                vProcessCommand(UICommand.DisplayLocalPort, ipeBindEP.Port.ToString());
                // Tell the OS we are ready to listen for incoming connection requests, with
                // the maximum number of pending requests set at 5.
                socServerSocket.Listen(5);
                socServerSocket.ReceiveTimeout = timeout;
                socServerSocket.SendTimeout = timeout;
                this.strContentPath = "C:\\";
                vProcessCommand(UICommand.DisplayRootDirectory, this.strContentPath);
            }
            catch (Exception e)
            {
                // Thell the user what the error is.
                System.Windows.Forms.MessageBox.Show(e.Message);
            }

            // Our thread that will listen for connection requests and create new threads to handle them.
            Thread tRequestListener = new Thread(() =>
            {
                while (true)
                {
                    Socket socClientSocket;
                    try
                    {
                        // Accept the next connection request, which returns a socket to be
                        // used for the communication.
                        socClientSocket = socServerSocket.Accept();
                        vProcessCommand(UICommand.DisplayRemoteIP, ((IPEndPoint)socClientSocket.RemoteEndPoint).Address.ToString());
                        vProcessCommand(UICommand.DisplayRemotePort, ((IPEndPoint)socClientSocket.RemoteEndPoint).Port.ToString());
                        // Create new thread to handle the request and continue to listen to the socket.
                        Thread tRequestHandler = new Thread(() =>
                        {
                            socClientSocket.ReceiveTimeout = timeout;
                            socClientSocket.SendTimeout = timeout;
                            try { vHandleConnReqs(socClientSocket, contentPath); }
                            catch
                            {
                                try { socClientSocket.Close(); }
                                catch { }
                            }
                        });
                        tRequestHandler.Start();
                    }
                    catch { }
                }
            });
            tRequestListener.Start();
        }

        // Function that handles incoming connection requests.
        private void vHandleConnReqs(Socket socClientSocket, string contentPath)
        {

            //TO-DO: Check for and respond to 400 Bad Request

            // An array to put the incoming bytes into. 10Kb
            byte[] buffer = new byte[10240]; 
            // The number of bytes actually received and receiving the request
            int iNumBytesRcvd = socClientSocket.Receive(buffer);
            // The message received, as a string (after converstion from UTF-8).
            string strMessageRcvd = enCharEncoder.GetString(buffer, 0, iNumBytesRcvd);

            strContentPath = contentPath;
            vProcessCommand(UICommand.DisplayRootDirectory, strContentPath);

            string strMessageSendToUI = "Date: " + DateTime.Now.ToString() + "\r\n"
                                        + "IP address: " + ((IPEndPoint)socClientSocket.RemoteEndPoint).Address.ToString() + "\r\n"
                                        + "Port Number: " + ((IPEndPoint)socClientSocket.RemoteEndPoint).Port.ToString() + "\r\n"
                                        + "Request Line: " + strMessageRcvd + "\r\n\r\n";
            vProcessCommand(UICommand.DisplayResponse, strMessageSendToUI);            

            // Parse the method of the request
            string strHttpMethod = strMessageRcvd.Substring(0, strMessageRcvd.IndexOf(" "));

            int iStart = strMessageRcvd.IndexOf(strHttpMethod) + strHttpMethod.Length + 1;
            int iLength = strMessageRcvd.LastIndexOf("HTTP") - iStart - 1;
            string strRequestUrl = strMessageRcvd.Substring(iStart, iLength);

            string strReqestedFile = "";
            if (strHttpMethod.Equals("GET") || strHttpMethod.Equals("OPTIONS"))
                strReqestedFile = strRequestUrl.Split('?')[0];
            else
                vNotAllowed(socClientSocket);

            strReqestedFile = strReqestedFile.Replace("/", "\\").Replace("\\..", "");
            iStart = strReqestedFile.LastIndexOf('.') + 1;
            if (iStart > 0)
            {
                iLength = strReqestedFile.Length - iStart;
                string strExtension = strReqestedFile.Substring(iStart, iLength);
                // Check if this is a MIME type extension we support from the dictionary above
                if (dicExtensions.ContainsKey(strExtension))
                    // Check for the file in the folder set up for our server
                    if (File.Exists(strContentPath + strReqestedFile))
                        // Reach this point, everything is okay, send file with correct MIME type
                        vSendOKResponse(socClientSocket, File.ReadAllBytes(strContentPath + strReqestedFile), dicExtensions[strExtension], strHttpMethod);
                else
                    // Since this isn't supported, assume file does not exist.
                    vNotFound(socClientSocket);
            }
             else
            {
                // If file is not specified try to send index.htm or index.html
                // You can add more (for example "default.html")
                if (strReqestedFile.Substring(iLength - 1, 1) != "\\")
                    strReqestedFile += "\\";
                if (File.Exists(strContentPath + strReqestedFile + "index.htm"))
                    vSendOKResponse(socClientSocket, File.ReadAllBytes(strContentPath + strReqestedFile + "\\index.htm"), "text/html", "");
                else if (File.Exists(strContentPath + strReqestedFile + "index.html"))
                    vSendOKResponse(socClientSocket, File.ReadAllBytes(strContentPath + strReqestedFile + "\\index.html"), "text/html", "");
                else
                    vNotFound(socClientSocket);
            }
        }

        private void vNotAllowed(Socket clientSocket)
        {
            vSendResponse(clientSocket, "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Alex & Tyler's Web Server\r\n</h2><div>405 - Method Not Allowed</div></body></html>", "405 Method Not Allowed", "text/html");
        }

        private void vNotFound(Socket clientSocket)
        {
            vSendResponse(clientSocket, "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Alex & Tyler's Web Server\r\n</h2><div>404 - Not Found</div></body></html>", "404 Not Found", "text/html");
        }

        private void vSendOKResponse(Socket clientSocket, byte[] bContent, string contentType, string strHttpMethod)
        {
            vSendResponse(clientSocket, bContent, "200 OK", contentType, strHttpMethod);
        }

        // For strings and error handling requests
        private void vSendResponse(Socket clientSocket, string strContent, string responseCode, string contentType)
        {
            byte[] bContent = enCharEncoder.GetBytes(strContent);
            vSendResponse(clientSocket, bContent, responseCode, contentType, "");
        }

        // For byte arrays
        private void vSendResponse(Socket clientSocket, byte[] bContent, string responseCode, string contentType, string strHttpMethod)
        {
            
            if (strHttpMethod.Equals("GET"))
            {
                try
                {
                    string strGet = "HTTP/1.1 " + responseCode + "\r\n"
                                      + "Connection: close\r\n"
                                      + "Content-Length: " + bContent.Length.ToString() + "\r\n"
                                      + "Content-Type: " + contentType + "\r\n\r\n"
                                      + "Date: " + DateTime.Now.ToString() + "\r\n"
                                      + "Server: Alex & Tyler's Web Server\r\n";
                    byte[] bHeader = enCharEncoder.GetBytes(strGet);
                    clientSocket.Send(bHeader);
                    clientSocket.Send(bContent);
                    clientSocket.Close();
                }
                catch { }
            }
            if (strHttpMethod.Equals("OPTION"))
            {
                try
                {
                    string strOption = "HTTP/1.1 " + responseCode + "\r\n"
                                        + "Date: " + DateTime.Now.ToString() + "\r\n"
                                        + "Server: Alex & Tyler's Web Server\r\n"
                                        + "Allow: GET OPTIONS\r\n\r\n";
                    byte[] bHeader = enCharEncoder.GetBytes(strOption);
                    clientSocket.Send(bHeader);
                    clientSocket.Close();
                }
                catch { }
            }
            else
            {
                try
                {
                    string strOther = "HTTP/1.1 " + responseCode + "\r\n\r\n";
                    byte[] bHeader = enCharEncoder.GetBytes(strOther);
                    clientSocket.Send(bHeader);
                    clientSocket.Send(bContent);
                    clientSocket.Close();
                }
                catch { }
            }
        }

        public void vDisconnect()
        {
            socServerSocket.Shutdown(SocketShutdown.Both);
            socServerSocket.Close();
        }
    }
}
