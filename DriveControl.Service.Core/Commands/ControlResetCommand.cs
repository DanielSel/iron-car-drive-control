using System;
using System.Collections.Generic;
using System.Text;

namespace DriveControl.Service.Core.Commands
{
    class ControlResetCommand : ControlCommand
    {
        protected override int ControlCode { get; } = 0;
        public ControlResetCommand() : base(0)
        {
        }
    }
}
