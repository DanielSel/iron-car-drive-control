namespace DriveControl.Service.Core.Commands
{
    public class ControlServoCommand : ControlCommand
    {
        protected override int ControlCode { get; } = 2;

        public ControlServoCommand(int controlValue) : base(controlValue)
        {
        }
        
    }
}