using System;
using System.Net;
using System.Net.Sockets;

namespace ConsoleApp11
{
    class Program
    {
        static void Main(string[] args)
        {
            TcpListener server = null;

            try
            {
                int port = 9998;
                IPAddress localAddr = IPAddress.Parse("127.0.0.1");

                server = new TcpListener(localAddr, port);
                server.Start();

                while (true)
                {
                    TcpClient client = server.AcceptTcpClient();
                    NetworkStream stream = client.GetStream();

                    byte[] data = { 23 };
                    stream.Write(data, 0, data.Length);
                    Console.WriteLine($"Sent: {data[0]}");

                    byte[] receivedData = new byte[1];
                    stream.Read(receivedData, 0, receivedData.Length);
                    Console.WriteLine($"Received: {receivedData[0]}");

                    float[] floatData = { 1.1f, 2.2f, 3.3f };
                    byte[] floatBytes = new byte[floatData.Length * sizeof(float)];
                    Buffer.BlockCopy(floatData, 0, floatBytes, 0, floatBytes.Length);
                    stream.Write(floatBytes, 0, floatBytes.Length);

                    client.Close();
                }
            }
            catch (Exception e)
            {
                Console.WriteLine($"Ошибка: {e.Message}");
            }
            finally
            {
                server?.Stop();
            }
        }

    }
}
