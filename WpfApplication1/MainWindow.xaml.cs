using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Reactive.Linq;
using System.Reactive;
using ReactiveUI;

namespace WpfApplication1
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Observable.FromEventPattern<RoutedEventArgs>(this.btn3, "Click")
                .Do((x) =>
                {
                    ((Button)x.Sender).IsEnabled = false;
                })
                .Delay(new TimeSpan(0, 0, 3))
                .Subscribe((x) =>
                {
                    this.Dispatcher.Invoke(() =>
                    {
                        var btn = (Button)x.Sender;
                        btn.IsEnabled = true;
                        this.lstMain.Items.Clear();
                    });
                });

            this.btn4.ClickAsObservable()
                     .Do(k => ((Button)k.Sender).IsEnabled = false)
                     .Delay(new TimeSpan(0, 0, 3))
                     .SubscribeDispatcher(this, k =>
                     {
                         var btn = (Button)k.Sender;
                         btn.IsEnabled = true;
                         this.lstMain.Items.Clear();
                     });
        }

        private void btn1_Click(object sender, RoutedEventArgs e)
        {
            Observable.Range(1, 10)
                .Subscribe(x => lstMain.Items.Add(x));
        }

        private void btn2_Click(object sender, RoutedEventArgs e)
        {
            var observer = Observer.Create<int>(
                x => lstMain.Items.Add(x),
                ex => { lstMain.Items.Add(-1); },
                () => { MessageBox.Show("Complete"); });
            Observable.Range(1, 10)                
                .Subscribe(observer);
        }
    }
}
