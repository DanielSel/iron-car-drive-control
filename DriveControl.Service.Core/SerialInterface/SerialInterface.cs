using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Extensions.Options;
using RJCP.IO.Ports;

namespace DriveControl.Service.Core.SerialInterface
{
    class SerialInterface : ISerialInterface
    {
        private readonly SerialPortStream _serialPortStream;
        public SerialInterface(IOptions<SerialConfiguration> serialConfiguration)
        {
            SerialConfiguration localSerialConfiguration = serialConfiguration.Value;
            _serialPortStream = new SerialPortStream(serialConfiguration.Value.Port, serialConfiguration.Value.Baudrate);
        }
        public void SendMessage(string msg)
        {
            _serialPortStream.WriteLine(msg);
        }

        public async Task<string> ReceiveMessage()
        {
            throw new NotImplementedException();
        }
    }
}
