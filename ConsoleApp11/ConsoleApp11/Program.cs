using System;
using System.IO;
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

                TcpClient client = server.AcceptTcpClient();
                NetworkStream stream = client.GetStream();

                byte[] data = { 23 };
                stream.Write(data, 0, data.Length);
                Console.WriteLine($"Sent: {data[0]}");

                byte[] receivedData = new byte[1];
                stream.Read(receivedData, 0, receivedData.Length);
                Console.WriteLine($"Received: {receivedData[0]}");

                using var reader = new StreamReader("dataset_8_long.txt");
                string line;
                
                while ((line = reader.ReadLine()) != null)
                {
                    Console.WriteLine(line);
                    //line = line.Replace(',', '.');
                    string[] numbers = line.Split(' ');

                    if (numbers.Length < 3)
                    {
                        Console.WriteLine("Строка содержит недопустимое количество чисел.");
                        continue;
                    }

                    byte[] floatBytes = new byte[3 * sizeof(float)];

                    for (int i = 0; i < 3; i++)
                    {
                        if (!float.TryParse(numbers[i], out float value))
                        {
                            Console.WriteLine("Неверный формат числа.");
                            continue;
                        }

                        byte[] bytes = BitConverter.GetBytes(value);
                        Array.Copy(bytes, 0, floatBytes, i * sizeof(float), sizeof(float));
                    }

                    stream.Write(floatBytes, 0, floatBytes.Length);
                }
                while (true) { }
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
