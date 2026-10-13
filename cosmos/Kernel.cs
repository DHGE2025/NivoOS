using System;
using Sys = Cosmos.System;

namespace NivoOS
{
    // shortcut: text desktop; add a graphics canvas after Cosmos toolchain validation.
    public class Kernel : Sys.Kernel
    {
        protected override void BeforeRun()
        {
            Console.BackgroundColor = ConsoleColor.DarkBlue;
            Console.ForegroundColor = ConsoleColor.White;
            Console.Clear();
            Console.SetCursorPosition(2, 0);
            Console.Write("Nivo OS     Desktop");
            Console.SetCursorPosition(19, 11);
            Console.Write("Willkommen bei Nivo OS");
            Console.SetCursorPosition(19, 13);
            Console.Write("Ein ruhiger Ort fuer neue Ideen.");
            Console.SetCursorPosition(24, 23);
            Console.Write("[ Finder ]  [ Terminal ]  [ Info ]");
        }

        protected override void Run()
        {
            Sys.CPU.Halt();
        }
    }
}
