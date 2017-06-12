namespace DriveControl.Service.Core
{
    public interface IArduinoInterface
    {
        void Reset();
        void SetMotorPower(int motorSpeed);
        void SetSteeringAngle(int steeringAngle);
    }
}
