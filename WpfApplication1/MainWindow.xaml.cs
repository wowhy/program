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
using ReactiveUI.Legacy;

namespace WpfApplication1
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private MainWindowModel model;

        public MainWindow()
        {
            InitializeComponent();
            this.DataContext = this.model = new MainWindowModel();
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
                        this.model.DataList.Clear();
                    });
                });

            this.btn4.ClickAsObservable()
                     .Do(k => ((Button)k.Sender).IsEnabled = false)                     
                     .Delay(new TimeSpan(0, 0, 3))
                     .SubscribeDispatcher(this, k =>
                     {
                         var btn = (Button)k.Sender;
                         btn.IsEnabled = true;
                         this.model.DataList.Clear();
                     });
        }

        private void btn1_Click(object sender, RoutedEventArgs e)
        {
            Observable.Range(1, 10)
                .Subscribe(x => this.model.DataList.Add(new MainWindowDataObject() { Id = x }));
        }

        private void btn2_Click(object sender, RoutedEventArgs e)
        {
            var observer = Observer.Create<int>(
                x => this.model.DataList.Add(new MainWindowDataObject() { Id = x }),
                ex => { this.model.DataList.Add(new MainWindowDataObject() { Id = -1 }); },
                () => { MessageBox.Show("Complete"); });
            Observable.Range(1, 10)
                .Subscribe(observer);
        }

        private async void btn5_Click(object sender, RoutedEventArgs e)
        {
            this.btn5.IsEnabled = false;
            await Task.Delay(3000);
            this.model.DataList.Clear();
            this.btn5.IsEnabled = true;
        }
    }
}
