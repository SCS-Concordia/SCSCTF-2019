using System;

namespace WeAreNotInKansasAnymore
{
    class Program
    {

        private const string OkMessage = "Flag OK!";
        private const string ErrMessage = "Bad Flag!";

        static void Main(string[] args)
        {
            Console.Write("Flag: ");
            string input = Console.ReadLine();

            Logic logic = new Logic();
            logic.V1 = true;
            logic.V2 = false;
            logic.V3 = true;
            logic.V4 = false;
            logic.V5 = true;

            bool result;
            try
            {
                result = logic.BonMatin(input);
            }
            catch (Exception e)
            {
                result = false;
            }

            Console.WriteLine(result ? ErrMessage : OkMessage );
        }
    }
}
