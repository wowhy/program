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
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Program06
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private Storyboard storyboard;

        public MainWindow()
        {
            InitializeComponent();

            this.frame.RenderTransform = new RotateTransform();

            var opacity = new DoubleAnimation(0, 1, new Duration(TimeSpan.FromSeconds(1)));
            Storyboard.SetTarget(opacity, this.frame);
            Storyboard.SetTargetProperty(opacity, new PropertyPath(Frame.OpacityProperty));

            var angle = new DoubleAnimation(0, 360, new Duration(TimeSpan.FromSeconds(1)));
            Storyboard.SetTarget(angle, this.frame);
            Storyboard.SetTargetProperty(angle, 
                new PropertyPath(
                    "(0).(1)", 
                    Frame.RenderTransformProperty, 
                    RotateTransform.AngleProperty));

            this.storyboard = new Storyboard();

            storyboard.AutoReverse = false;
            storyboard.RepeatBehavior = new RepeatBehavior(1);
            storyboard.Children.Add(opacity);
            storyboard.Children.Add(angle);

            this.listbox.SelectedIndex = 0;
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems.Count != 0 && this.frame != null)
            {
                var item = e.AddedItems[0] as ListBoxItem;
                var uri = new Uri("\\Pages\\" + item.Content + ".xaml", UriKind.Relative);
                this.frame.Navigate(uri);                   
            }
        }

        private void frame_Navigated(object sender, NavigationEventArgs e)
        {
            if (e.ExtraData != null &&
                e.ExtraData.GetType() == typeof(bool) &&
                (bool)e.ExtraData)
            {
                this.listbox.SelectionChanged -= ListBox_SelectionChanged;
                this.listbox.SelectedIndex = 0;
                this.listbox.SelectionChanged += ListBox_SelectionChanged;
            }
        }

        private void frame_Navigating(object sender, NavigatingCancelEventArgs e)
        {
            if (storyboard != null)
            {
                storyboard.Stop();
                storyboard.Begin();
            }
        }
    }
}
