using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace DriveControl.Service.Core.SerialInterface
{
    interface ISerialInterface
    {
        void SendMessage(string msg);
        Task<string> ReceiveMessage();
    }
}
