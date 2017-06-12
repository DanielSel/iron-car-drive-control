using System;
using System.Collections.Generic;
using System.Text;
using DriveControl.Service.Core.Commands;
using DriveControl.Service.Core.SerialInterface;
using Microsoft.Extensions.Options;

namespace DriveControl.Service.Core
{
    public class ArduinoInterface : IArduinoInterface
    {
        private readonly ISerialInterface _serialInterface;
        public ArduinoInterface(IOptions<SerialConfiguration> serialConfiguration)
        {
            _serialInterface = new SerialInterface.SerialInterface(serialConfiguration);
        }
        public void Reset()
        {
            ExecuteCommand(new ControlResetCommand());
        }

        public void SetMotorPower(int motorSpeed)
        {
            ExecuteCommand(new ControlMotorCommand(motorSpeed));
        }
        public void SetSteeringAngle(int steeringAngle)
        {
            ExecuteCommand(new ControlServoCommand(steeringAngle));
        }

        private void ExecuteCommand(ControlCommand command)
        {
            _serialInterface.SendMessage(command.Serialize());
        }

    }
}
