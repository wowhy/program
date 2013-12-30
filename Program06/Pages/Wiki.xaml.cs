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

namespace Program06
{
    /// <summary>
    /// Wiki.xaml 的交互逻辑
    /// </summary>
    public partial class Wiki : Page
    {
        public Wiki()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new Uri("\\Pages\\Index.xaml", UriKind.Relative), true);
        }
    }
}
