using System.Net;
using System.Net.Sockets;

IPAddress ipAddress = IPAddress.Any;
string filename = "dataset_11_all_coords.txt";
string ip = "127.0.0.1";
int port = 9998;
int bytesRead;
int c = 0;
byte[] tmp = new byte[1];
byte[] buffer = new byte[4];

using var listener = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

listener.Connect(IPAddress.Parse(ip), port);
listener.Receive(tmp);

Console.WriteLine("Received: " + tmp[0].ToString());

listener.Send(tmp);

using var writer = new StreamWriter(filename);
while ((bytesRead = listener.Receive(buffer)) > 0)
{
    byte[] data = new byte[bytesRead];
    Array.Copy(buffer, data, bytesRead);
    float fl = BitConverter.ToSingle(buffer, 0);

    if (c != 2)
    {
        Console.Write(fl + " ");
        writer.Write(fl + " ");
        c++;
        writer.Flush();
    }
    else
    {
        Console.WriteLine(fl + " ");
        writer.WriteLine(fl + " ");
        c = 0;
        writer.Flush();
    }
}
