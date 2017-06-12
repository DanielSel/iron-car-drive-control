using System;
using System.Collections.Generic;
using System.Text;

namespace DriveControl.Service.Core.Commands
{
    public abstract class ControlCommand
    {
        protected abstract int ControlCode { get; }
        protected int ControlValue { get; }

        protected ControlCommand(int controlValue)
        {
            ControlValue = controlValue;
        }

        public string Serialize()
        {
            return String.Format("{0}:{1};", ControlCode, ControlValue);
        }
    }
}
