using System;
using Microsoft.Extensions.DependencyInjection;

using DriveControl.Service.Core;
using DriveControl.Service.Core.SerialInterface;
using Microsoft.Extensions.Configuration;

namespace DriveControl.Service.Console
{
    class Program
    {
        private static IArduinoInterface _driveControlInterface;

        static int Main(string[] args)
        {
            Startup();
            System.Console.WriteLine("Send commands in format <code>:<value>;");
            System.Console.WriteLine("Enter q or quit to exit");
            while (true)
            {
                // Read input
                string command = System.Console.ReadLine();

                // Exit on q
                if (command == "q" || command == "quit")
                {
                    return 0;
                }

                // Parse and Execute Command
                string[] commandArray = command.Substring(0, command.Length - 1).Split(':');
                if (commandArray.Length != 2)
                {
                    System.Console.WriteLine("Invalid Command Syntax!");
                    break;
                }

                int controlCode = Int32.Parse(commandArray[0]);
                int controlValue = Int32.Parse(commandArray[1]);

                switch (controlCode)
                {
                    case 0: _driveControlInterface.Reset(); break;
                    case 1: _driveControlInterface.SetMotorPower(controlValue); break;
                    case 2: _driveControlInterface.SetSteeringAngle(controlValue);  break;
                    default: System.Console.WriteLine("Invalid Control Code!"); break;
                }
            }
            return 0;
        }

        private static void Startup()
        {
            var Configuration = new ConfigurationBuilder()
                .AddJsonFile("config.json")
                .Build();

            IServiceCollection services = new ServiceCollection();

            services.AddOptions();
            services.Configure<SerialConfiguration>(Configuration.GetSection("SerialInterface"));
            services.AddSingleton<IArduinoInterface, ArduinoInterface>();

            IServiceProvider serviceProvider = services.BuildServiceProvider();

            //configure console logging
            //serviceProvider
            //    .GetService<ILoggerFactory>()
            //    .AddConsole(LogLevel.Debug);

            //var logger = serviceProvider.GetService<ILoggerFactory>()
            //    .CreateLogger<Program>();

            //logger.LogDebug("Logger is working!");

            
            _driveControlInterface = serviceProvider.GetService<IArduinoInterface>();
        }
    }
}