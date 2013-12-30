using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

namespace regex_replace
{
    public class CommnadException : Exception
    { }

    public enum Command
    {
        NONE,
        DIR,
        EXT,
        REGEX,
        REGEX_IN_FILE,
        CONTENT,
        CONTENT_IN_FILE,
        BACKUP,
        IGNORE
    }

    public class REGEX_REPLACE
    {
        private static Dictionary<string, Command> commands = new Dictionary<string, Command>() 
        {
            {"-d", Command.DIR},
            {"-t", Command.EXT},
            {"-s", Command.REGEX},
            {"-sf", Command.REGEX_IN_FILE},
            {"-c", Command.CONTENT},
            {"-cf", Command.CONTENT_IN_FILE},
            {"-b", Command.BACKUP},
            {"-i", Command.IGNORE}
        };

        private Dictionary<Command, string> options;

        public REGEX_REPLACE(Dictionary<Command, string> options)
        {
            this.options = options;
            Check();
        }

        public static Dictionary<Command, string> GetOptions(params string[] args)
        {
            var options = new Dictionary<Command, string>();
            var i = 0;
            while (i < args.Length)
            {
                var cmd = GetCommand(args[i].ToLower());
                if (cmd == Command.NONE)
                    throw new CommnadException();

                if (cmd == Command.BACKUP)
                {
                    options[cmd] = string.Empty;
                    i++;
                }
                else
                {
                    options[cmd] = args[i + 1];
                    i += 2;
                }
            }

            return options;
        }

        public void Start()
        {
            var size = options.ContainsKey(Command.IGNORE) ? int.Parse(options[Command.IGNORE]) : 20480000;
            var searchDir = options[Command.DIR];
            var ext = options[Command.EXT];
            var regex = GetRegex();
            var toReplace = GetReplaceContent();
            var backup = options.ContainsKey(Command.BACKUP);

            var dir = new DirectoryInfo(searchDir);
            if (!dir.Exists) throw new DirectoryNotFoundException();

            var files = dir.GetFiles(ext, SearchOption.AllDirectories);
            foreach (var file in files)
            {
                try
                {
                    using (var fs = file.Open(FileMode.Open, FileAccess.ReadWrite))
                    using (var sr = new StreamReader(fs))
                    using (var sw = new StreamWriter(fs))
                    {
                        var content = sr.ReadToEnd();
                        if (regex.IsMatch(content))
                        {
                            if (backup)
                            {
                                using (var bak = File.Create(file.FullName + ".bak"))
                                {
                                    var buffer = new byte[4096000];
                                    int len = 0;
                                    fs.Seek(0, SeekOrigin.Begin);
                                    while ((len = fs.Read(buffer, 0, 4096000)) > 0)
                                    {
                                        bak.Write(buffer, 0, len);
                                    }

                                    bak.Flush();
                                    bak.SetLength(bak.Position);
                                }
                            }

                            var result = regex.Replace(content, toReplace);
                            fs.Seek(0, SeekOrigin.Begin);
                            sw.Write(result);
                            fs.SetLength(fs.Position);

                            Console.WriteLine("Success: {0}", file.FullName);
                        }
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error: {0}, File: {1}", ex.Message, file.FullName);
                }
            }
        }

        private static Command GetCommand(string input)
        {
            Command result = Command.NONE;
            if (!commands.TryGetValue(input, out result))
                return Command.NONE;

            return result;
        }

        private Regex GetRegex()
        {
            if (options.ContainsKey(Command.REGEX))
                return new Regex(options[Command.REGEX]);
            
            return new Regex(File.ReadAllText(options[Command.REGEX_IN_FILE]));
        }

        private string GetReplaceContent()
        {
            if (options.ContainsKey(Command.CONTENT))
                return options[Command.CONTENT];

            return File.ReadAllText(options[Command.CONTENT_IN_FILE]);
        }

        private void Check()
        {
            if (this.options == null ||
                this.options.Count == 0)
            {
                throw new CommnadException();
            }

            if (!this.options.ContainsKey(Command.DIR) ||
                 this.options[Command.DIR] == string.Empty)
            {
                this.options[Command.DIR] = Directory.GetCurrentDirectory();
            }

            if (!this.options.ContainsKey(Command.EXT) ||
                 this.options[Command.EXT] == string.Empty)
            {
                this.options[Command.EXT] = "*.txt";
            }

            if (!this.options.ContainsKey(Command.REGEX) &&
                !this.options.ContainsKey(Command.REGEX_IN_FILE))
            {
                throw new CommnadException();
            }

            if (!this.options.ContainsKey(Command.CONTENT) &&
                !this.options.ContainsKey(Command.CONTENT_IN_FILE))
            {
                throw new CommnadException();
            }
        }

        private void Replace()
        {
 
        }
    }
}