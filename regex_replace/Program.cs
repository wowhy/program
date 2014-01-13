using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace regex_replace
{
    class Program
    {
        private static Dictionary<Command, string> options = new Dictionary<Command, string>();

        static void Help()
        {
            string help =
@"Usage:
    regex_replace [-d dir] [-t ext] [-s regex]|[-sf file] 
                  [-c content]|[-cf file] [-i size] [-b]

    -d dir     搜索的目录
    -t ext     搜索的文件类型
    -s regex   正则表达式规则
    -c content 替换文本
    -i size    忽略指定大小的文件
    -b         启动备份文件

Sample:
    regex_replace -d ""c:\test"" -t ""*.txt;*.xml"" -s ""[0-9]*"" -c ""test""
";

            Console.WriteLine(help);
        }

        static void Main(string[] args)
        {
            try
            {
                if (args.Length == 0)
                    throw new CommnadException();

                var options = REGEX_REPLACE.GetOptions(args);
                if (options.Count == 0)
                    throw new CommnadException();

                REGEX_REPLACE app = new REGEX_REPLACE(options);
                app.Start();
            }
            catch (CommnadException)
            {
                Help();
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error:");
                Console.WriteLine(ex.Message);
                Console.WriteLine("----------------------------------------------------------------");
                Help();
            }
        }
    }
}