using System;
using System.Collections.Generic;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace WeAreNotInKansasAnymore
{
    internal class Logic
    {
        private const string SuperSecret = "SuperSecret.txt";
        private const string NotSoSecret = "3041304430363641353633383130334230393133303232463044363136353635363130313632374630393138304336303030374531453043364330373637304130363642363030423139373736333031303732393030";

        public bool V1 { get; set; }
        public bool V2 { get; set; }
        public bool V3 { get; set; }
        public bool V4 { get; set; }
        public bool V5 { get; set; }

        private string h(byte[] data)
        {
            StringBuilder sb = new StringBuilder();
            foreach (byte b in data)
            {
                sb.Append(b.ToString("X2"));
            }

            return sb.ToString();
        }

        public bool BonMatin(string flag)
        {

            byte[] intermediate = Encoding.UTF8.GetBytes(flag);
            if (V1)
            {
                intermediate = Stage1(intermediate);
            }

            if (V2)
            {
                intermediate = Stage2(intermediate);
            }

            if (V3)
            {
                intermediate = Stage3(intermediate);
            }

            if (V4)
            {
                intermediate = Stage4(intermediate);
            }

            if (V5)
            {
                intermediate = Stage5(intermediate);
            }

            return !string.Equals(NotSoSecret, h(intermediate));
        }

        private byte[] Stage1(byte[] intermediate)
        {
            byte[] flag2 = new byte[intermediate.Length];
            for (int i = 0; i < intermediate.Length - 1; ++i)
            {
                byte p1 = intermediate[i];
                byte p2 = intermediate[i + 1];
                flag2[i] = (byte)(p1 ^ p2);
            }

            return flag2;
        }

        private byte[] Stage2(byte[] intermediate)
        {
            using (SHA1Managed sha1 = new SHA1Managed())
            {
                var hash = sha1.ComputeHash(intermediate);
                var sb = new StringBuilder(hash.Length * 2);

                return Encoding.UTF8.GetBytes(h(hash));
            }
        }

        private byte[] Stage3(byte[] intermediate)
        {
            using (StreamWriter outputFile = new StreamWriter(SuperSecret))
            {
                outputFile.WriteLine(h(intermediate));
                outputFile.WriteLine(h(Stage2(intermediate)));
                outputFile.WriteLine(h(Stage2(Encoding.UTF8.GetBytes("Oh hello there, I see what you are trying to do... good luck! Signed. FLAFL"))));
            }

            using (var alg = MD5.Create())
            {
                alg.ComputeHash(intermediate);
                return alg.Hash;
            }
        }

        private byte[] Stage4(byte[] intermediate)
        {
            using (var alg = MD5.Create())
            {
                alg.ComputeHash(intermediate);
                return alg.Hash;
            }
        }

        private byte[] Stage5(byte[] intermediate)
        {
            string thing = "";
            string thing2 = "";
            string thing3 = "";

            using (StreamReader inputFile = new StreamReader(SuperSecret))
            {
                thing = inputFile.ReadLine();
                thing2 = inputFile.ReadLine();
                thing3 = inputFile.ReadLine();
            }

            byte[] arr1 = Encoding.UTF8.GetBytes(thing2.Length < thing3.Length ? thing2 : thing3);
            byte[] arr2 = Encoding.UTF8.GetBytes(thing2.Length < thing3.Length ? thing3 : thing2);
            byte[] arr3 = Encoding.UTF8.GetBytes(string.IsNullOrEmpty(thing) ? "FLAG" : thing);
            
            for (int i = 0; i < arr1.Length - 1; ++i)
            {
                arr1[i] = (byte)(arr1[i] ^ arr2[i]);
            }

            return arr3;
        }


    }
}
