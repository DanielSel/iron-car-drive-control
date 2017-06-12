using System;
using System.Collections.Generic;
using System.Text;

namespace DriveControl.Service.Core.Commands
{
    class ControlMotorCommand : ControlCommand
    {
        protected override int ControlCode { get; } = 1;

        public ControlMotorCommand(int controlValue) : base(controlValue)
        {
        }
    }
}
