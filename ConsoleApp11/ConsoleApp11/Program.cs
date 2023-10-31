using System;
using System.Net;
using System.IO;
using System.Net.Sockets;

namespace ConsoleApp11
{
    class Program
    {
        static void Main(string[] args)
        {
            /*TcpListener listener = new TcpListener(IPAddress.Any, 8080);
            TcpClient tcpClient = listener.AcceptTcpClient();
            NetworkStream networkStream = tcpClient.GetStream();
            StreamReader reader = new StreamReader(networkStream);
            StreamWriter writer = new StreamWriter("C:\\Users\\user\\source\\repos\\ConsoleApp11\\data.txt");
            string data;
            while ((data = reader.ReadLine()) != null) {
                writer.WriteLine();
                writer.Flush();
            }
            listener.Stop();*/


            int port = 8080;
            string filename = "C:\\Users\\user\\source\\repos\\ConsoleApp11\\data.txt"; 
            string filename1 = "C:\\Users\\user\\source\\repos\\ConsoleApp11\\data1.txt"; 
            IPAddress ipAddress = IPAddress.Any;
            IPEndPoint localEndPoint = new IPEndPoint(ipAddress, port);
            using (Socket listener = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp))
            {
                
                listener.Connect(IPAddress.Parse("192.168.150.3"), 9998);
                byte[] tmp = new byte[1];
                listener.Receive(tmp);
                Console.WriteLine(tmp[0].ToString());
                listener.Send(tmp);
                byte[] buffer = new byte[4];
                int bytesRead;
                using (StreamWriter writer = new StreamWriter(filename))
                {
                    while ((bytesRead = listener.Receive(buffer)) > 0)
                    {
                        Console.WriteLine(bytesRead);
                        byte[] data = new byte[bytesRead];
                        Array.Copy(buffer, data, bytesRead);
                        float fl = System.BitConverter.ToSingle(buffer, 0) * 180 / (float)Math.PI;
                        writer.WriteLine(fl);
                        writer.Flush();
                    }

                }
            }
        }

    }
}
