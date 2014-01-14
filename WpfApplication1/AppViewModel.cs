using ReactiveUI;
using ReactiveUI.Legacy;
using System;
using System.Reactive;
using System.Reactive.Linq;
using System.Threading;
using System.Windows;

namespace WpfApplication1
{
    public class AppViewModel : ReactiveObject
    {
        private ObservableAsPropertyHelper<string> dataFromTheInternet;
        public string DataFromTheInternet
        {
            get { return dataFromTheInternet.Value; }
        }

        public ReactiveAsyncCommand GetDataFromTheInternet { get; protected set; }

        public AppViewModel()
        {
            GetDataFromTheInternet = new ReactiveAsyncCommand();
            var furtureData = GetDataFromTheInternet.RegisterAsyncFunction(s =>
            {
                var minutes = default(int);
                if (!int.TryParse((string)s, out minutes) ||
                    minutes <= 0)
                    return "请输入正整数";
                                
                MessageBus.Current.SendMessage("启动");
                Thread.Sleep(minutes * 1000);                
                return string.Format("{0}秒执行完毕!", s);
            });

            dataFromTheInternet = furtureData.ToProperty(this, k => k.DataFromTheInternet);
            furtureData.Subscribe(result => 
            {
                MessageBus.Current.SendMessage("结束");
                MessageBox.Show(result); 
            });
        }
    }
}
