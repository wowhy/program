using ReactiveUI;
using ReactiveUI.Legacy;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reactive;
using System.Reactive.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WpfApplication1
{
    /// <summary>
    /// AppView.xaml 的交互逻辑
    /// </summary>
    public partial class AppView : Window
    {
        public AppViewModel ViewModel { get; protected set; }

        public AppView()
        {
            this.ViewModel = new AppViewModel();
            InitializeComponent();

            MessageBus.Current.Listen<string>().Subscribe(message =>
            {
                this.Title = message;
                //MessageBox.Show(message);
            });
        }
    }
}
